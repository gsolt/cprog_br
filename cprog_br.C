/**+**************************************************************************
* NAME           :  cprog_br.c                                                *
* DESCRIPTION    :  a redundancia CPU-ban fut                                                          	*
* PROCESS        :  															*
*                                                                             	*
* [C] Copyright Zsolt Gergely,  2015.  All Rights Reserved                    	*
*                                                                             	*
* REV    DATE     PROGRAMMER         REVISION HISTORY                         	*
* V1.1	2015.09.25 Gergely Zsolt	*p_col_RxBuf: unsigned short

*****************************************************************************/

#include "CAPPLIC.H"
#include <stdio.h>
#include <string.h>

/* Parameterek strukturaja */
#include "strPar.H"



#define  BYTE					unsigned char
#define  RSlink1  				51
#define  AllLinks 				0
#define  SetCall  				0
#define  VALID  				1
#define  LEKERDEZES_TIMEOUT		100
#define  COMMAND_LENGTH			14


/*--------------------------------------------------------------------------*/
/* Prototypes and defines                                                   */
/*--------------------------------------------------------------------------*/
void fnReadPar(void);
void fnSetStatus(int nI, int nValue);
extern void fnSetStatSiteTable(void);
extern void fnSetComPar(void);
extern void fnSetDataPar(void);
extern void fnWriteSPData(int nIEC_Offset, int nData, int nMS1, int nMS2, int nMin, int nCTAct);
extern int  fnReadSPData(int nIEC_Offset);
extern void fnDPTblIndx(int nIECOffset, int *nDPTblIndx, int *nIndx);
void MOT_DATA(STATION_DESC_MOT	*pMOT, unsigned char *buf);
void MOT_DATA2(STATION_DESC_MOT	*pMOT, unsigned char *buf);
void TALUS_EVENT(STATION_DESC_TALUS *pTAL, unsigned char *rx_buf);
void TALUS_DAT(STATION_DESC_TALUS *pTAL, unsigned char *rx_buf);
void TMOK_DATA(STATION_DESC_MOT	*pMOT, unsigned char *buf);
void TMOK_DATA2(STATION_DESC_MOT	*pMOT, unsigned char *buf);
void ARKAD_EVENT( unsigned char *rx_buf);
void ARKAD_DAT(unsigned char *rx_buf);
void RUDOLPH_EVENT(STATION_DESC_TALUS *pTAL, unsigned char *rx_buf);
void RUDOLPH_DAT(STATION_DESC_TALUS	*pTAL, unsigned char *rx_buf);

extern void fnWriteNM( int nIECOffset,unsigned int nData);
extern void fnWriteDPStatus(int nIEC_Offset, int nData);
extern void fnWriteNMStatus(int nIEC_Offset, int nData);

extern void com_check();
extern void rx();
extern void tx_command(); 
extern void fnLekR(void);
extern void fnSetDinamicSiteTable(void);
void fnDCTblIndx(int nIECOffset, int *nDCTblIndx, int *nOffset, short **p_col_DCAct);
void rx(void);
int value_BX(int );
int value_CErrX(int nI);
int value_CComX(int nI);
int value_CRcvdX(int nI);
int value_CLekX(int nI);
void setvalue_LiX(int, int );
void setvalue_CErrX(int nI, int nValue);
void setvalue_CStatusX(int nI, int nValue);
void setvalue_CComX(int nI, int nValue);
void setvalue_CRcvdX(int nI, int nValue);
void setvalue_CLekX(int nI, int nValue);
void tx_command(void);
void com_check(void);
extern void setdat2(unsigned char *input);
extern void setdat(unsigned char *input);
extern void fnSCTblIndx(int nIECOffset, int *nSCTblIndx, int *nOffset, short **p_col_SCAct);
extern void fnWriteSPStatus(int nIEC_Offset, int nData);

/* 2017.09*/
extern void fnWriteDPData(int nIEC_Offset, int nData, int nMS1, int nMS2, int nMin, int nCTAct);
extern int fnReadDPData(int nIEC_Offset, int nMS1, int nMS2, int nMin, int nCTAct);

/**********************************************/
/* Globals                                     */
/**********************************************/
int             nReteszNum = 0;         /* Reteszes TMOK-k száma */
DP_PAR          dpPars[80];         /* Reteszes TMOK-k adatai */



CB_TABLE_INFO   table_parInt;
CB_TABLE_INFO   table_Stat;
/* MOSCAD tablak oszlopai */
short          *p_col_DP_B;	
short          *p_col_DP_A;	




unsigned short          *p_col_RxBuf;  /* 2015.09.25 */


			


unsigned short current_site;
unsigned char  current_link;
unsigned short dest_site;
unsigned short dest_inx;
unsigned char  dest_link;

int				nRxLen;
int				nTxLen;


unsigned short		nNumOfSites;
unsigned short		nSiteList[MAX_RTU];
unsigned short		nLinkList[MAX_RTU];
unsigned char		byComStat[MAX_RTU];
char 				message[200];

unsigned char		*p_flash;
unsigned long		lSize;
STR_TALUS_EVENT		strTE[4];

COM_PAR				sCP;
STATION_TYPE_INDEX 	sTI[MAX_RTU];
/*STATION_DESC_MOT	sMOT[250];*/
STATION_DESC_TALUS	sTAL[MAX_RTU];
STATION_COMM_DATA	sCD[MAX_RTU];
/*RTU_RAD				sRAD;*/

RTU_RAD_NEW			sRAD_K1;
RTU_RAD_NEW			sRAD_K2;
RTU_RAD_NEW			sRAD_K3;


RTU_LIN				sLIN;
STATION_DESC_SEPAM	sSep[3];


STATION_DESC_MOT	sMOT[MAX_RTU];

TOTAL_PAR			sT;
int					nTotalRTU;
BYTE			nMoscadHours;

long    lTick=0;
short   prValue = 100;
/*--------------------------------------------------------------------------*/
/* The list of the function included in this block                          */
/*--------------------------------------------------------------------------*/
const CB_JUMPTBL user_jumptable[]=
{
   {"Rx"   , rx},
   {0      , 0 }
};
/*-------------------------------------*/
/* For the use of MOSCAD_find_func     */
/*-------------------------------------*/
/*static CB_FUNC setdat;
static CB_FUNC setdat2;*/
/*--------------------------------------------------------------------------*/
/* 'C' Block Initialization and Completion                                  */
/*--------------------------------------------------------------------------*/
void user_control_function(int control)
{
int					nI;	
int 			nOffset;


	
	
   switch(control)
      {
         case CB_INIT :
         
        MOSCAD_sprintf(message,"B redndancia program version 1.0");
        MOSCAD_error(message );

         	
         	 
         	 /* sT struktura feltoltese*/
         	 sT.sCP  = &sCP;
         	 sT.sMOT = sMOT;
         	 sT.sTAL = sTAL;
         	 sT.sTI  = sTI;
         	 sT.sRAD_K1 = &sRAD_K1;
         	 sT.sRAD_K2 = &sRAD_K2;
         	 sT.sRAD_K3 = &sRAD_K3;
         	 sT.sLIN = &sLIN;
         	 sT.nNumOfSites =&nNumOfSites;	
			 sT.nSiteList   =nSiteList;	
			 sT.nLinkList	=nLinkList;	
			 sT.sSep		= sSep; 

			setdat2( (unsigned char *)&sT );
			setdat( (unsigned char *)&sT);
         	          	


             fnReadPar();  
             
     		 
      		 MOSCAD_set_sitetable(250,nSiteList,nLinkList,byComStat);
      		 

      		                     
            break;

         case CB_EXIT :
         	


         break;
      }
}
/*--------------------------------------------------------------------------*/
/* functions.                                                               */
/*--------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------*/
/* Táviratok fogadása és adatfeldolgozás                                    */
/*--------------------------------------------------------------------------*/
void rx(void)
{

   unsigned short site_inx;

   unsigned char  rx_buffer[CB_MAX_MDLC_BUF_SIZE];

   unsigned short buff_len;
   unsigned	char  type;
   int			  nType;

   unsigned short *nRxBuf;
   int			  nTemp;
   
   unsigned char  nTxBuf[CB_MAX_MDLC_BUF_SIZE];
   
    /* Kommunikáció ellenõrzés */
   lTick++;
   if (lTick > 250)
   {
      if (p_col_DP_A[69] == prValue)
        {
          p_col_DP_B[68] = 1;
        }
      else
        {
        p_col_DP_B[68] = 0;
        }
      prValue = p_col_DP_A[69]; 
      lTick = 0; 
   }

   
   
   buff_len=sizeof(rx_buffer);
   
   nRxBuf = (unsigned short *)rx_buffer;
 

   /*---------------------*/
   /* Receive the frame.  */
   /*---------------------*/
   if(MOSCAD_RcvFrm(&site_inx, rx_buffer, &buff_len, &type) == 0)
   {
   			/*	MOSCAD_sprintf(message,"Frame received, index: %d",site_inx);
   			 	MOSCAD_error(message );*/ 				

   	if(site_inx<=MAX_RTU)
   	{
   	   	

      switch (type)
      {
      	

        case CB_GROUPCALL_TYPE:
            break;

        case CB_ORIGINATE_TYPE:
        	
        	
        		nTxBuf[0] = 0;
				MOSCAD_sprintf(message,"ORIGIN TYPE received");
   				MOSCAD_error(message ); 				
        		
        		
        		if (MOSCAD_AnsFrm(nTxBuf, 2) !=0 )
 			  	{
					MOSCAD_sprintf(message,"Could not send answer frame ");
   				 	MOSCAD_error(message ); 				
   				}

        	
          

        case CB_ANSWER_TYPE:
			
			
		
			
        case CB_MSG_TYPE:
	
			
			/* Elvégzi az adatfeldolgozást */
 			nType = sTI[site_inx].nType;
 			
 			MOSCAD_sprintf(message,"Frame received, index: %d, type: %d, rx_buffer[0]: %d,rx_buffer[1]: %d, rx_buffer[2]: %d, length: %d",site_inx,nType,nRxBuf[0],nRxBuf[1],nRxBuf[2],buff_len);
   			 	MOSCAD_error(message ); 				
 
			if (nType == TYP_FRONTEND && nRxBuf[0] == 100 )
 			{
 				FRONTEND_DATA(rx_buffer);
 			} 	


 			
 			else
 			{
				MOSCAD_sprintf(message,"Type parameter error: index: %d, type: %d",site_inx,nType);
   			 	MOSCAD_error(message ); 				
 			} 			

           break;

      } /*end switch*/
   	} /*end if site_inx<MAX_RTU*/
   }/*end if == 0*/

   fnTx();
   
}

/****************************************************************************/
/* Parameter tabla kiolvasas												*/
/****************************************************************************/
void fnReadPar(void)
{
char 				message[300];

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
/*  Reteszes RTU-k paraméterei 																	*/
/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
nReteszNum = 2;         /* Reteszes TMOK-k száma */

dpPars[0].nSite   = 3;       /* TMOK: 71-28, H front end */
dpPars[0].nDP_ID  = 1263;    /* DP6, 14. */

dpPars[1].nSite   = 3;       /* TMOK: 32-34, H front end */
dpPars[1].nDP_ID  = 1264;    /* DP6, 14. */

/*!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/




	/* DP-k */
   	if (MOSCAD_get_table_info (0,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",0);
        MOSCAD_error(message );
        return;
   		}
	p_col_DP_B = (short *)(table_parInt.ColDataPtr[0]);	
	p_col_DP_A = (short *)(table_parInt.ColDataPtr[1]);	



} /* end fnReadPar()*/





/****************************************************************************/
/* Front end adatfogadás egy másik front endbõl, az új típusú reteszkezelés miatt										*/
/****************************************************************************/
void FRONTEND_DATA( unsigned char *rx_buf)
{
int		nI;	

int		nIEC_Offset;

int		nDPTblIndx;
int		nMOSCAD_OffsetDP;

int		nNMStart;

int		nDPStart;
unsigned int		nData;

int		nVal;

int		nMin;
int		nMs1;
int		nMs2;







	p_col_RxBuf = (short *)(rx_buf);	

       /* MOSCAD_sprintf(message,"Front end data: %d %d %d",p_col_RxBuf[0],p_col_RxBuf[1],p_col_RxBuf [2]);
        MOSCAD_error(message ); */


/* Kétbites állásjelzések, feldolgozása ----------------------------------------------------------------------------------------*/
/* A program feltetelezi, hogy a ketbites jelzesek a 1. szotol kezdodnek az RxBuf-ban, a DP offset pedig a 2. szóban van*/

		
	nDPStart = 	p_col_RxBuf[2];


if (nDPStart<70 && nDPStart>=0)
{	

	nData = p_col_RxBuf[1];	
	

  p_col_DP_B[nDPStart]= nData;	
	

	MOSCAD_sprintf(message,"Front end data: nDPStart: %d nData: %d",nDPStart,nData);
        MOSCAD_error(message );
					

} /* end if */


} /* FRONTEND data*/
/*-----------------------------------------------------------------------------------------------*/


/****************************************************************************/
/* Ha változik egy adat a másik rendszerbõl frissülõ DP táblában, elküldi a megfelelõ front endnek											
Paraméter:  Cél front end indexe
            DP azonosítója
/****************************************************************************/
void fnTx(void)
{
int                 nI;
static int          nDPOld[80];
unsigned short      nTxBuf[80];             

for (nI=0;nI<nReteszNum && nI<80 ;nI++)
{
  if(p_col_DP_B[nI] != nDPOld[nI])
  {
     		nTxBuf[0] = 100; /* Ugyanaz, mintha TMOK lenne */				
   		   	nTxBuf[1] = p_col_DP_B[nI]; /* << 14;     DP értéke  Nem szabad forgatni!*/    	
   		   	nTxBuf[2] = dpPars[nI].nDP_ID; /* DP azonosítója */ 
              	
 		   	  MOSCAD_sprintf(message,"Állásjelzés küldése, index: %d, Value: %d, DP azonosító: %d, site index: %d",nI,p_col_DP_B[nI],dpPars[nI].nDP_ID,dpPars[nI].nSite  );
   			  MOSCAD_error(message ); 
 
   		   	
			/* Tavirat elkuldese */
			
	 		  	if (MOSCAD_TxFrm(dpPars[nI].nSite, nTxBuf, 3*2) !=0 )
 			  	{
					   MOSCAD_sprintf(message,"Could not send parancs ,index: %d",dpPars[nI].nSite);
   				 	 MOSCAD_error(message ); 				
   				}     		    			

  
  }
  nDPOld[nI] =  p_col_DP_B[nI];


}




} /* end fnTx **********************************************************************************/