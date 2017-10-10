/**+**************************************************************************
* NAME           :  command.c                                                 *
* DESCRIPTION    :  This example demonstrates a way of self learning the     *
*                   site ID and the link ID. By pushing PB1, the RTU sends a *
*                   broadcast message to inform the other RTU about its      *
*                   own site ID and link ID. After this stage, each RTU may  *
*                   send a message to the other RTU and expects to get an    *
*                   echo which will be logged in the error logger.           *
*                   By pushing PB2, the RTU sends the string "THE QUICK.." to*
*                   the designated RTU. The designated RTU echoes the same   *
*                   string as an answer. The source RTU logs the message in  *
*                   the error logger.                                        *
* PROCESS        :  The example includes three functions -                   *
*                                                                            *
*                   tx_new_site:- The function sets the first line in the    *
*                   static site table with site id 0 (using                  *
*                   MOSCAD_set_sitetable), and sends its own site/link as a  *
*                   a broadcast.                                             *
*                                                                            *
*                   tx:- The function sends the string "THE QUICK.." to      *
*                   designated RTU.                                          *
*                                                                            *
*                   rx- should be called all the time.  rx may receive three *
                    types of messages:                                       *
*                       1) TxFrm message- This means that PB1 was pushed and *
*                          the receiving buffer contains the site ID and     *
*                          the link ID of the sender.                        *
*                       2) SndFrm message-This means that PB2 was pushed and *
*                          the receiving buffer contains the string. It      *
*                          echoes it as an answer.                           *
*                       3) AnsFrm Message-The receiving buffer contains echo.*
*                          It logs it in the error logger.                   *
*                                                                            *
* [C] Copyright Zsolt Gergely,  2003.  All Rights Reserved                 *
*                                                                            *
* REV    DATE     PROGRAMMER         REVISION HISTORY                        *
*****************************************************************************/

#include "CAPPLIC.H"
#include <stdio.h>
/* Parameterek strukturaja */
#include "strPar.H"

#define  BYTE					unsigned char



/*--------------------------------------------------------------------------*/
/* Prototypes and defines                                                   */
/*--------------------------------------------------------------------------*/
void fnWriteNM( int nIECOffset,unsigned int nData);
void fnSPTblIndx(int nIEC_Offset, int *nSPTblIndx, int *nIndx);
void fnNMTblIndx(int nIECOffset, int *nNMTblIndx, int *nIndx);
void fnDPTblIndx(int nIECOffset, int *nDPTblIndx, int *nIndx);
void fnWriteSPData(int nIEC_Offset, int nData, int nMS1, int nMS2, int nMin, int nCTAct);
int fnReadSPData(int nIEC_Offset);
void fnDCTblIndx(int nIECOffset, int *nDCTblIndx, int *nOffset, short **p_col_DCAct);
void fnSCTblIndx(int nIECOffset, int *nSCTblIndx, int *nOffset, short **p_col_SCAct);
void fnWriteNMStatus(int nIEC_Offset, int nData);
void fnWriteSPStatus(int nIEC_Offset, int nData);
void fnWriteDPStatus(int nIEC_Offset, int nData);




/****************************************************************************/
/* Beir egy adatot a SP adatok koze											*/
/*																			*/
/****************************************************************************/
void fnWriteSPData(int nIEC_Offset, int nData, int nMS1, int nMS2, int nMin, int nCTAct)
{
short          *p_col_SPAct;
short          *p_col_SP_CTAct;
short          *p_col_SP_MINAct;
short          *p_col_SP_MS1Act;
short          *p_col_SP_MS2Act;
char			message[300];



CB_TABLE_INFO   table_SPAct;

int				nSPTblIndx;
int				nIndx;



					/*Elõállítja a tábla indexet, és offstet */	
					fnSPTblIndx(nIEC_Offset, &nSPTblIndx, &nIndx);		
						
					
						
					if (MOSCAD_get_table_info (nSPTblIndx,&table_SPAct)!=0 )
   					{
					       MOSCAD_sprintf(message,"No valid information in table: %d",nSPTblIndx);
					       MOSCAD_error(message );
					       return;
   					}
   					
   					
				   	p_col_SPAct     	= (short *)(table_SPAct.ColDataPtr[0]);
				   	p_col_SP_MS1Act     = (short *)(table_SPAct.ColDataPtr[1]);
				   	p_col_SP_MS2Act  	= (short *)(table_SPAct.ColDataPtr[2]); 	
				   	p_col_SP_MINAct     = (short *)(table_SPAct.ColDataPtr[3]);
				   	p_col_SP_CTAct  	= (short *)(table_SPAct.ColDataPtr[4]); 	


				
					if (nData > 0)
					{
						p_col_SPAct[nIndx]= 1;
					}
					else
					{
						p_col_SPAct[nIndx]= 0;
					}
					
					
					/* A kapott idõt kell használni */
					if (nCTAct == 1)
					{						
						/* Perc beirasa */		
						p_col_SP_MINAct[nIndx] = nMin;	
															
						/* MS1 beirasa */		
						p_col_SP_MS1Act[nIndx] = nMS1;
						
						/* MS2 beirasa */		
						p_col_SP_MS2Act[nIndx] = nMS2;
					}/*end if*/
							
					
						
					p_col_SP_CTAct[nIndx] = nCTAct;	
			

} /* end fnWriteSPData()*/
/****************************************************************************/
/* Kiolvas egy adatot a SP adatok kozul											*/
/*																			*/
/****************************************************************************/
int fnReadSPData(int nIEC_Offset)
{
short          *p_col_SPAct;
short          *p_col_SP_CTAct;
CB_TABLE_INFO   table_SPAct;	


int				nData;
char			message[100];
int				nSPTblIndx;
int				nIndx;


						
					/*Elõállítja a tábla indexet, és offstet */	
					fnSPTblIndx(nIEC_Offset, &nSPTblIndx, &nIndx);						
						
					if (MOSCAD_get_table_info (nSPTblIndx,&table_SPAct)!=0 )
   					{
					       MOSCAD_sprintf(message,"No valid information in table: %d",nSPTblIndx);
					       MOSCAD_error(message );
					       return;
   					}
   					
   					
				   	p_col_SPAct     = (short *)(table_SPAct.ColDataPtr[0]);
				   	p_col_SP_CTAct  = (short *)(table_SPAct.ColDataPtr[4]); 	


					nData = p_col_SPAct[nIndx];
				

return(nData);

} /* end fnReadSPData()*/
/****************************************************************************/
/* NM data beiras										*/
/****************************************************************************/
void fnWriteNM( int nIECOffset,unsigned int nData)
{
				

int		nNMTblIndx;
char	message[200];
int		nIndx;


CB_TABLE_INFO   table_NM;


short          *p_col_NM;


	/* Egesz parameterek */
	

	fnNMTblIndx(nIECOffset, &nNMTblIndx, &nIndx);

 

   	if (MOSCAD_get_table_info (nNMTblIndx,&table_NM)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",nNMTblIndx);
        MOSCAD_error(message );
        return;
   		}

	/* Mérések feldolgozása ----------------------------------------------------------------------------------------*/
	/*  !!!!! Ha LiveZero = 1, akkor azt a letra programban kell jelezni !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!*/
	
	
		if (nIECOffset>0)
		{		
	   		p_col_NM     = (short *)(table_NM.ColDataPtr[0]);
			p_col_NM[nIndx] = nData;
		}	
} /* end fnWriteNM */
/****************************************************************************/
/* Beir egy statuszt (TOPICAL/NOT TOPICAL) az SP adatok koze						*/
/*	Bemenetek:																*/
/*	nIEC_Offset: az adott SP adat IEC sorszama								*/
/*	nData: TOPICAL/NOT TOPICAL													*/
/*																			*/
/*																			*/
/****************************************************************************/
void fnWriteSPStatus(int nIEC_Offset, int nData)
{
short          *p_col_SPStatus;

char			message[300];


CB_TABLE_INFO   table_SPAct;	

int				nSPTblIndx;
int				nIndx;



					/*Elõállítja a tábla indexet, és offsetet */	
					fnSPTblIndx(nIEC_Offset, &nSPTblIndx, &nIndx);		
						
					
						
					if (MOSCAD_get_table_info (nSPTblIndx,&table_SPAct)!=0 )
   					{
					       MOSCAD_sprintf(message,"No valid information in table: %d",nSPTblIndx);
					       MOSCAD_error(message );
					       return;
   					}
   					
   					
				   	p_col_SPStatus     	= (short *)(table_SPAct.ColDataPtr[6]);


				
					if (nData == TOPICAL)
					{
						p_col_SPStatus[nIndx]= TOPICAL;
					}
					else if (nData == NOT_TOPICAL)
					{
						p_col_SPStatus[nIndx]= NOT_TOPICAL;
					}
					
					

} /* end fnWriteSPStatus()*/
/****************************************************************************/
/* Beir egy statuszt (TOPICAL/NOT TOPICAL) a DP adatok koze						*/
/*	Bemenetek:																*/
/*	nIEC_Offset: az adott DP adat IEC sorszama								*/
/*	nData: TOPICAL/NOT TOPICAL													*/
/*																			*/
/*																			*/
/****************************************************************************/
void fnWriteDPStatus(int nIEC_Offset, int nData)
{
short          *p_col_DPStatus;

char			message[300];



CB_TABLE_INFO   table_DPAct;	

int				nDPTblIndx;
int				nIndx;
int				nOffset;



					/*Elõállítja a tábla indexet, és offsetet */	
					fnDPTblIndx(nIEC_Offset, &nDPTblIndx, &nOffset);	
	
					
						
					if (MOSCAD_get_table_info (nDPTblIndx,&table_DPAct)!=0 )
   					{
					       MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
					       MOSCAD_error(message );
					       return;
   					}

   					   					
				   	p_col_DPStatus     	= (short *)(table_DPAct.ColDataPtr[6]);
				
					
					nIndx = nIEC_Offset - nOffset;
				
					if (nData == TOPICAL)
					{
						p_col_DPStatus[nIndx]= TOPICAL;

					}
					else if (nData == NOT_TOPICAL)
					{
						p_col_DPStatus[nIndx]= NOT_TOPICAL;
					}										

} /* end fnWriteDPStatus()*/
/****************************************************************************/
/* Beir egy statuszt (TOPICAL/NOT TOPICAL) az NM adatok koze						*/
/*	Bemenetek:																*/
/*	nIEC_Offset: az adott NM adat IEC sorszama								*/
/*	nData: TOPICAL/NOT TOPICAL													*/
/*																			*/
/*																			*/
/****************************************************************************/
void fnWriteNMStatus(int nIEC_Offset, int nData)
{
short          *p_col_NMStatus;

char			message[300];



CB_TABLE_INFO   table_NMAct;	

int				nNMTblIndx;
int				nIndx;



					/*Elõállítja a tábla indexet, és offsetet */	
					fnNMTblIndx(nIEC_Offset, &nNMTblIndx, &nIndx);		
						
					
						
					if (MOSCAD_get_table_info (nNMTblIndx,&table_NMAct)!=0 )
   					{
					       MOSCAD_sprintf(message,"No valid information in table: %d",nNMTblIndx);
					       MOSCAD_error(message );
					       return;
   					}
   					
   					
				   	p_col_NMStatus     	= (short *)(table_NMAct.ColDataPtr[3]);


				
					if (nData == TOPICAL)
					{
						p_col_NMStatus[nIndx]= TOPICAL;
					}
					else if (nData == NOT_TOPICAL)
					{
						p_col_NMStatus[nIndx]= NOT_TOPICAL;
					}
					
					

} /* end fnWriteNMStatus()*/

/****************************************************************************/
/* Elloallitja az adott IEC SP cimhez tartozó MOSCAD tábla indexét, és offsetet */
/****************************************************************************/
void fnSPTblIndx(int nIEC_Offset, int *nSPTblIndx, int *nIndx)
{





char			message[300];

CB_TABLE_INFO   table_parInt;
short          *p_col_parInt;





	/* Egesz parameterek */
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	



		/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=0 && nIEC_Offset<250)
					{
												
						/* Single point 1. */
						*nSPTblIndx = p_col_parInt[8];	/* Itt van az SP tábla sorszáma */
						*nIndx = nIEC_Offset;

						
						
					}/*end if SP1 */

					/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=250 && nIEC_Offset<500)
					{
												
						/* Single point 2. */
						*nSPTblIndx = p_col_parInt[36];	/* Itt van az SP2 tábla sorszáma */
						*nIndx = nIEC_Offset - 250;
					}/*end if SP2 */
					
					/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=500 && nIEC_Offset<750)
					{
												
						/* Single point 3. */
						*nSPTblIndx = p_col_parInt[37];	/* Itt van az SP3 tábla sorszáma */
						*nIndx = nIEC_Offset - 500;
					}/*end if SP3 */

					/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=750 && nIEC_Offset<1000)
					{
												
						/* Single point 4. */
						*nSPTblIndx = p_col_parInt[38];	/* Itt van az SP4 tábla sorszáma */
						*nIndx = nIEC_Offset - 750;
					}/*end if SP4 */

					/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=1000 && nIEC_Offset<1250)
					{
												
						/* Single point 5. */
						*nSPTblIndx = p_col_parInt[39];	/* Itt van az SP5 tábla sorszáma */
						*nIndx = nIEC_Offset - 1000;
					}/*end if SP5 */			

					/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=1250 && nIEC_Offset<1500)
					{
												
						/* Single point 6. */
						*nSPTblIndx = p_col_parInt[40];	/* Itt van az SP6 tábla sorszáma */
						*nIndx = nIEC_Offset - 1250;
					}/*end if SP6 */			
					
					/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=1500 && nIEC_Offset<1750)
					{												
						/* Single point 7. */
						*nSPTblIndx = p_col_parInt[41];	/* Itt van az SP7 tábla sorszáma */
						*nIndx = nIEC_Offset - 1500;
					}/*end if SP7 */
										/* A címtartománytól függ az SP tábla */
					if (nIEC_Offset>=1750 && nIEC_Offset<2000)
					{
												
						/* Single point 8. */
						*nSPTblIndx = p_col_parInt[42];	/* Itt van az SP8 tábla sorszáma */
						*nIndx = nIEC_Offset - 1750;
					}/*end if SP8 */
								
					if (nIEC_Offset>=2000 && nIEC_Offset<2250)
					{											
						/* Single point 9. */
						*nSPTblIndx = p_col_parInt[47];	/* Itt van az SP9 tábla sorszáma */
						*nIndx = nIEC_Offset - 2000;
					}/*end if SP9 */			
			
					if (nIEC_Offset>=2250 && nIEC_Offset<2500)
					{											
						/* Single point 10. */
						*nSPTblIndx = p_col_parInt[48];	/* Itt van az SP10 tábla sorszáma */
						*nIndx = nIEC_Offset - 2250;
					}/*end if SP10 */			

					if (nIEC_Offset>=2500 && nIEC_Offset<2750)
					{											
						/* Single point 11. */
						*nSPTblIndx = p_col_parInt[49];	/* Itt van az SP11 tábla sorszáma */
						*nIndx = nIEC_Offset - 2500;
					}/*end if SP11 */			

					if (nIEC_Offset>=2750 && nIEC_Offset<3000)
					{											
						/* Single point 12. */
						*nSPTblIndx = p_col_parInt[50];	/* Itt van az SP12 tábla sorszáma */
						*nIndx = nIEC_Offset - 2750;
					}/*end if SP12 */			

					if (nIEC_Offset>=3000 && nIEC_Offset<3250)
					{											
						/* Single point 13. */
						*nSPTblIndx = p_col_parInt[51];	/* Itt van az SP13 tábla sorszáma */
						*nIndx = nIEC_Offset - 3000;
					}/*end if SP13 */			

					if (nIEC_Offset>=3250 && nIEC_Offset<3500)
					{											
						/* Single point 14. */
						*nSPTblIndx = p_col_parInt[52];	/* Itt van az SP14 tábla sorszáma */
						*nIndx = nIEC_Offset - 3250;
					}/*end if SP14 */			

					if (nIEC_Offset>=3500 && nIEC_Offset<3750)
					{											
						/* Single point 15. */
						*nSPTblIndx = p_col_parInt[53];	/* Itt van az SP15 tábla sorszáma */
						*nIndx = nIEC_Offset - 3500;
					}/*end if SP15 */			

					if (nIEC_Offset>=3750 && nIEC_Offset<4000)
					{											
						/* Single point 16. */
						*nSPTblIndx = p_col_parInt[54];	/* Itt van az SP16 tábla sorszáma */
						*nIndx = nIEC_Offset - 3750;
					}/*end if SP16 */	
					if (nIEC_Offset>=4000 && nIEC_Offset<4250)
					{											
						/* Single point 17. */
						*nSPTblIndx = p_col_parInt[60];	/* Itt van az SP17 tábla sorszáma */
						*nIndx = nIEC_Offset - 4000;
					}/*end if SP17 */			
					if (nIEC_Offset>=4250 && nIEC_Offset<4500)
					{											
						/* Single point 18. */
						*nSPTblIndx = p_col_parInt[61];	/* Itt van az SP18 tábla sorszáma */
						*nIndx = nIEC_Offset - 4250;
					}/*end if SP18 */			
					if (nIEC_Offset>=4500 && nIEC_Offset<4750)
					{											
						/* Single point 19. */
						*nSPTblIndx = p_col_parInt[62];	/* Itt van az SP19 tábla sorszáma */
						*nIndx = nIEC_Offset - 4500;
					}/*end if SP19 */			
					if (nIEC_Offset>=4750 && nIEC_Offset<5000)
					{											
						/* Single point 20. */
						*nSPTblIndx = p_col_parInt[63];	/* Itt van az SP20 tábla sorszáma */
						*nIndx = nIEC_Offset - 4750;
					}/*end if SP20 */
								
					if (nIEC_Offset>=5000 && nIEC_Offset<5250)
					{											
						/* Single point 21. */
						*nSPTblIndx = p_col_parInt[70];	/* Itt van az SP21 tábla sorszáma */
						*nIndx = nIEC_Offset - 5000;
					}/*end if SP21 */			

					if (nIEC_Offset>=5250 && nIEC_Offset<5500)
					{											
						/* Single point 22. */
						*nSPTblIndx = p_col_parInt[71];	/* Itt van az SP22 tábla sorszáma */
						*nIndx = nIEC_Offset - 5250;
					}/*end if SP22 */			

					if (nIEC_Offset>=5500 && nIEC_Offset<5750)
					{											
						/* Single point 23. */
						*nSPTblIndx = p_col_parInt[72];	/* Itt van az SP23 tábla sorszáma */
						*nIndx = nIEC_Offset - 5500;
					}/*end if SP23 */		
					
					if (nIEC_Offset>=5750 && nIEC_Offset<6000)
					{											
						/* Single point 24. */
						*nSPTblIndx = p_col_parInt[73];	/* Itt van az SP24 tábla sorszáma */
						*nIndx = nIEC_Offset - 5750;
					}/*end if SP24 */			
						

if (*nIndx>249)
{
	*nIndx = 0;
}


} /* end fnSPTblIndx()*/

/********************************************************************************/
/* Elloallitja az adott IEC NM cimhez tartozó MOSCAD tábla indexét, és offsetet */
/********************************************************************************/
void fnNMTblIndx(int nIECOffset, int *nNMTblIndx, int *nIndx)
{





char			message[300];

CB_TABLE_INFO   table_parInt;
short          *p_col_parInt;



	/* Egesz parameterek */
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	


		/* A címtartománytól függ az NM tábla */
		if (nIECOffset>=0 && nIECOffset<240)
		{
			/* NM 1. */
			*nNMTblIndx = p_col_parInt[18]; 	/* Itt van az NM1 tábla sorszáma */
			*nIndx = nIECOffset -0;				
		}
		else if (nIECOffset>=240 && nIECOffset<480)
		{
			/* NM 2. */
			*nNMTblIndx = p_col_parInt[44]; 	/* Itt van az NM2 tábla sorszáma */
			*nIndx = nIECOffset -240;				
		}
		else if (nIECOffset>=480 && nIECOffset<720)
		{
			/* NM 3. */
			*nNMTblIndx = p_col_parInt[56]; 	/* Itt van az NM3 tábla sorszáma */
			*nIndx = nIECOffset - 480;				
		}

		else if (nIECOffset>=720 && nIECOffset<960)
		{
			/* NM 4. */
			*nNMTblIndx = p_col_parInt[65]; 	/* Itt van az NM4 tábla sorszáma */
			*nIndx = nIECOffset - 720;				
		}
		else if (nIECOffset>=960 && nIECOffset<1200)
		{
			/* NM 5. */
			*nNMTblIndx = p_col_parInt[75]; 	/* Itt van az NM5 tábla sorszáma */
			*nIndx = nIECOffset - 960;				
		}


if (*nIndx>239)
{
	*nIndx = 0;
}

} /* end fnNMTblIndx()*/

/********************************************************************************/
/* Elloallitja az adott IEC DP cimhez tartozó MOSCAD tábla indexét, és offsetet */
/********************************************************************************/
void fnDPTblIndx(int nIECOffset, int *nDPTblIndx, int *nOffset)
{

CB_TABLE_INFO   table_parInt;
short          *p_col_parInt;
	
	
char			message[300];

	/* Egesz parameterek */
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	



	/* A címtartománytól függ az DP tábla */
	if (nIECOffset>=0 && nIECOffset<250)
	{								
		/* Double point 1. */
		*nDPTblIndx = p_col_parInt[13];	/* Itt van az DP1 tábla sorszáma */
		*nOffset = 0;
	}/*end if DP1 */
	else if (nIECOffset>=250 && nIECOffset<500)
	{								
		/* Double point 2. */
		*nDPTblIndx = p_col_parInt[43];	/* Itt van az DP2 tábla sorszáma */
		*nOffset =  250;
	}/*end if DP2 */
	else if (nIECOffset>=500 && nIECOffset<750)
	{								
		/* Double point 3. */
		*nDPTblIndx = p_col_parInt[55];	/* Itt van az DP2 tábla sorszáma */
		*nOffset =  500;
	}/*end if DP3 */
	else if (nIECOffset>= 750 && nIECOffset<1000)
	{								
		/* Double point 4. */
		*nDPTblIndx = p_col_parInt[67];	/* Itt van az DP2 tábla sorszáma */
		*nOffset =  750;
	}/*end if DP4 */
	else if (nIECOffset>= 1000 && nIECOffset<1250)
	{								
		/* Double point 5. */
		*nDPTblIndx = p_col_parInt[76];	/* Itt van az DP5 tábla sorszáma */
		*nOffset =  1000;
	}/*end if DP5 */
	else if (nIECOffset>= 1250 && nIECOffset<1500)
	{								
		/* Double point 6. */
		*nDPTblIndx = p_col_parInt[85];	/* Itt van az DP6 tábla sorszáma */
		*nOffset =  1250;
	}/*end if DP6 */


} /* end fnDPTblIndx()*/
/********************************************************************************/
/* Elloallitja az adott IEC DC cimhez tartozó MOSCAD tábla indexét, és offsetet */
/********************************************************************************/
void fnDCTblIndx(int nIECOffset, int *nDCTblIndx, int *nOffset, short **p_col_DCAct)
{

CB_TABLE_INFO   table_parInt;
CB_TABLE_INFO   table_DC;
short          *p_col_parInt;
	

char			message[100];

	/* Egesz parameterek */
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	



	/* A címtartománytól függ az DC tábla */
	if (nIECOffset>=0 && nIECOffset<250)
	{								
		/* Double command 1. */
		*nDCTblIndx = p_col_parInt[23];	/* Itt van az DC1 tábla sorszáma */
		*nOffset = 0;
	}/*end if DC1 */
	else if (nIECOffset>=250 && nIECOffset<500)
	{								
		/* Double command 2. */
		*nDCTblIndx = p_col_parInt[45];	/* Itt van az DC2 tábla sorszáma */
		*nOffset =  250;
	}/*end if DC2 */
	else if (nIECOffset>=500 && nIECOffset<750)
	{								
		/* Double command 3. */
		*nDCTblIndx = p_col_parInt[57];	/* Itt van az DC3 tábla sorszáma */
		*nOffset =  500;
	}/*end if DC3 */
	else if (nIECOffset>=750 && nIECOffset<1000)
	{								
		/* Double command 4. */
		*nDCTblIndx = p_col_parInt[68];	/* Itt van az DC4 tábla sorszáma */
		*nOffset =  750;
	}/*end if DC4 */

	/* Double command */
	
	if (MOSCAD_get_table_info (*nDCTblIndx,&table_DC)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",*nDCTblIndx);
        MOSCAD_error(message );
        return;
   		}
	*p_col_DCAct = (short *)(table_DC.ColDataPtr[0]);


} /* end fnDCTblIndx()*/
/********************************************************************************/
/* Elloallitja az adott IEC SC cimhez tartozó MOSCAD tábla indexét, és offsetet */
/********************************************************************************/
void fnSCTblIndx(int nIECOffset, int *nSCTblIndx, int *nOffset, short **p_col_SCAct)
{

CB_TABLE_INFO   table_parInt;
short          *p_col_parInt;


char			message[300];

CB_TABLE_INFO   table_SC;

	/* Egesz parameterek */
   	if (MOSCAD_get_table_info (2,&table_parInt)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",2);
        MOSCAD_error(message );
        return;
   		}
	p_col_parInt = (short *)(table_parInt.ColDataPtr[0]);	



	/* A címtartománytól függ az SC tábla */
	if (nIECOffset>=0 && nIECOffset<250)
	{								
		/* Single command 1. */
		*nSCTblIndx = p_col_parInt[31];	/* Itt van az SC1 tábla sorszáma */
		*nOffset = 0;
	}/*end if SC1 */
	else if (nIECOffset>=250 && nIECOffset<500)
	{								
		/* Single command  2. */
		*nSCTblIndx = p_col_parInt[46];	/* Itt van az SC2 tábla sorszáma */
		*nOffset =  250;
	}/*end if SC2 */
	else if (nIECOffset>=500 && nIECOffset<750)
	{								
		/* Single command  3. */
		*nSCTblIndx = p_col_parInt[58];	/* Itt van az SC3 tábla sorszáma */
		*nOffset =  500;
	}/*end if SC3 */

	else if (nIECOffset>=750 && nIECOffset<1000)
	{								
		/* Single command  4. */
		*nSCTblIndx = p_col_parInt[69];	/* Itt van az SC4 tábla sorszáma */
		*nOffset =  750;
	}/*end if SC4 */


	if (MOSCAD_get_table_info (*nSCTblIndx,&table_SC)!=0 )
   		{
        MOSCAD_sprintf(message,"No valid information in table: %d",*nSCTblIndx);
        MOSCAD_error(message );
        return;
   		}
	*p_col_SCAct = (short *)(table_SC.ColDataPtr[0]);


} /* end fnSCTblIndx()*/

/****************************************************************************/
/* Beir egy adatot a DP adatok koze											*/
/*	nData: 0,1,2,3																		*/
/****************************************************************************/
void fnWriteDPData(int nIEC_Offset, int nData, int nMS1, int nMS2, int nMin, int nCTAct)
{
	

short          *p_col_DP_CTAct;
short          *p_col_DP_Valid;

short			*p_col_DPH;			/* DPH -> CLOSE  TILTVA */
short			*p_col_DPL;			/* DPL -> OPEN   ENGEDÉLYEZVE */

CB_TABLE_INFO   table_DPAct;	


char			message[200];
int				nDPTblIndx;
int				nOffset;


						
					/*Elõállítja a tábla indexet, és offsetet */	
					fnDPTblIndx(nIEC_Offset, &nDPTblIndx, &nOffset);						
						
					if (MOSCAD_get_table_info (nDPTblIndx,&table_DPAct)!=0 )
   					{
					       MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
					       MOSCAD_error(message );
					       return;
   					}
   					
					p_col_DPH     = (short *)(table_DPAct.ColDataPtr[0]);			/* DPH -> CLOSE  TILTVA */
					p_col_DPL     = (short *)(table_DPAct.ColDataPtr[1]);			/* DPL -> OPEN   ENGEDÉLYEZVE */
				   	p_col_DP_CTAct  = (short *)(table_DPAct.ColDataPtr[5]); 
				   	p_col_DP_Valid  = (short *)(table_DPAct.ColDataPtr[6]); 
				   	
				   	
				   	p_col_DPL[nIEC_Offset-nOffset] = (nData >> 0)   & 1;
			 		p_col_DPH[nIEC_Offset-nOffset] = (nData >> 1) & 1;
	 				p_col_DP_CTAct[nIEC_Offset-nOffset]= nCTAct;
	 				p_col_DP_Valid[nIEC_Offset-nOffset]= 1;
	 				


	
				


} /* end fnWriteDPData()*/

/****************************************************************************/
/* Kiolvas egy adatot a DP adatok közül											*/
/* A visszatérõ érték: 0,1,2,3														*/
/****************************************************************************/
int fnReadDPData(int nIEC_Offset, int nMS1, int nMS2, int nMin, int nCTAct)
{
	

short          *p_col_DP_CTAct;
short          *p_col_DP_Valid;

short			*p_col_DPH;			/* DPH -> CLOSE  TILTVA */
short			*p_col_DPL;			/* DPL -> OPEN   ENGEDÉLYEZVE */

CB_TABLE_INFO   table_DPAct;	


char			message[200];
int				nDPTblIndx;
int				nOffset;


						
					/*Elõállítja a tábla indexet, és offsetet */	
					fnDPTblIndx(nIEC_Offset, &nDPTblIndx, &nOffset);						
						
					if (MOSCAD_get_table_info (nDPTblIndx,&table_DPAct)!=0 )
   					{
					       MOSCAD_sprintf(message,"No valid information in table: %d",nDPTblIndx);
					       MOSCAD_error(message );
					       return 0;
   					}
   					
					p_col_DPH     = (short *)(table_DPAct.ColDataPtr[0]);			/* DPH -> CLOSE  TILTVA */
					p_col_DPL     = (short *)(table_DPAct.ColDataPtr[1]);			/* DPL -> OPEN   ENGEDÉLYEZVE */
				   	p_col_DP_CTAct  = (short *)(table_DPAct.ColDataPtr[5]); 
				   	p_col_DP_Valid  = (short *)(table_DPAct.ColDataPtr[6]); 
				   	
				   	
	return( 2 * p_col_DPH[nIEC_Offset-nOffset] + p_col_DPL[nIEC_Offset-nOffset]);		/* Ha 2, akkor tiltva van, ha 1 akkor engedélyezve */

				


} /* end fnReadDPData()*/



