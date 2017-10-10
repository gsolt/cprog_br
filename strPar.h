/* ---------------------------------------------------------------------------------------*/
/* IEC FIU parameterek strukturai														  */
/* ---------------------------------------------------------------------------------------*/
#define  TYP_TAL		1
#define  TYP_MOT		2
#define  TYP_TMOK		3
#define  TYP_TAL_EVENT	4
#define  TYP_MOT2		5
#define  TYP_SEP		6
#define  TYP_ARKAD		7
#define  TYP_TMOK2		8
#define  TYP_FRONTEND	11

#define	TOPICAL			1
#define NOT_TOPICAL		0


#define  MAX_RTU		350

#define	LINE1			21
#define	LINE2			22
#define	LINE11			81
#define	LINE12			82


#define	ALL_LINK		0
#define	RSLINK1			51
#define	RSLINK2			52
#define	RSLINK3			53
#define	RSLINK4			54
#define	RSLINK5			55
#define	RSLINK6			56
#define	RSLINK7			57
#define	RSLINK8			58
#define	RSLINK9			59
#define	RSLINK10		60
#define	RSLINK11		61
#define	RSLINK12		62
#define	RSLINK13		63
#define	RSLINK14		64
#define	RSLINK15		65
#define	RSLINK16		66
#define	RSLINK17		67
#define	RSLINK18		68
#define	RSLINK19		69

#define	RADIO1			110
#define	RADIO1_1		111
#define	RADIO1_2		112
#define	RADIO1_3		113
#define	RADIO1_4		114
#define	RADIO1_5		115
#define	RADIO1_6		116
#define	RADIO1_7		117
#define	RADIO1_8		118
#define	RADIO1_9		119

#define	RADIO2			120
#define	RADIO2_1		121
#define	RADIO2_2		122
#define	RADIO2_3		123
#define	RADIO2_4		124
#define	RADIO2_5		125
#define	RADIO2_6		126
#define	RADIO2_7		127
#define	RADIO2_8		128
#define	RADIO2_9		129

#define	RADIO3			130
#define	RADIO3_1		131
#define	RADIO3_2		132
#define	RADIO3_3		133
#define	RADIO3_4		134
#define	RADIO3_5		135
#define	RADIO3_6		136
#define	RADIO3_7		137
#define	RADIO3_8		138
#define	RADIO3_9		139

#define	RADIO4			140
#define	RADIO4_1		141
#define	RADIO4_2		142
#define	RADIO4_3		143
#define	RADIO4_4		144
#define	RADIO4_5		145
#define	RADIO4_6		146
#define	RADIO4_7		147
#define	RADIO4_8		148
#define	RADIO4_9		149

#define	RADIO5			150
#define	RADIO5_1		151
#define	RADIO5_2		152
#define	RADIO5_3		153
#define	RADIO5_4		154
#define	RADIO5_5		155
#define	RADIO5_6		156
#define	RADIO5_7		157
#define	RADIO5_8		158
#define	RADIO5_9		159

#define	RADIO6			160
#define	RADIO6_1		161
#define	RADIO6_2		162
#define	RADIO6_3		163
#define	RADIO6_4		164
#define	RADIO6_5		165
#define	RADIO6_6		166
#define	RADIO6_7		167
#define	RADIO6_8		168
#define	RADIO6_9		169

#define	RADIO7			170
#define	RADIO7_1		171
#define	RADIO7_2		172
#define	RADIO7_3		173
#define	RADIO7_4		174
#define	RADIO7_5		175
#define	RADIO7_6		176
#define	RADIO7_7		177
#define	RADIO7_8		178
#define	RADIO7_9		179

#define	RADIO8			180
#define	RADIO8_1		181
#define	RADIO8_2		182
#define	RADIO8_3		183
#define	RADIO8_4		184
#define	RADIO8_5		185
#define	RADIO8_6		186
#define	RADIO8_7		187
#define	RADIO8_8		188
#define	RADIO8_9		189

#define	RADIO9			190
#define	RADIO9_1		191
#define	RADIO9_2		192
#define	RADIO9_3		193
#define	RADIO9_4		194
#define	RADIO9_5		195
#define	RADIO9_6		196
#define	RADIO9_7		197
#define	RADIO9_8		198
#define	RADIO9_9		199



typedef	struct
	{

		unsigned short			nSite ;	  /* Front end index */
		unsigned short			nDP_ID ;	/* DP azonosítója a táviratban */
	}	DP_PAR ;	



typedef	struct
	{

		unsigned short			nSite ;	/* RTU site cimek*/
		unsigned short			nLink ;	/* RTU linkek */
	}	RTU_SITE_PAR ;	


typedef	struct
	{

		unsigned short			nDCStart ;	/* DC parancs IEC kezdõcím */
		unsigned short			nDCNum ;	/* Darabszam */
		unsigned short			nSCStart ;	/* SC parancs IEC kezdõcím */
		unsigned short			nSCNum ;	/* Darabszam */
		unsigned short			nSPOffsetLek;/* Lekerdezes folyamatban SP adat IEC offsete */		
		unsigned short			nSPOffsetCS; /* Komm. hiba SP adat IEC offsete */					
		unsigned short			nAckStart ;	/* Ack SC parancs IEC kezdõcím */
		unsigned short			nAckNum ;	/* Ack Darabszam */
		unsigned short			nSPOffsetLek2;/* Lekerdezes folyamatban SP adat IEC offsete, iker TMOK */		
		unsigned short			nSPOffsetCS2; /* Komm. hiba SP adat IEC offsete, iker TMOK */					

	}	COM_PAR_RTU ;	


typedef	struct
	{
	unsigned short			nRtuNum ;	/* Osszes RTU szama */

	COM_PAR_RTU		sCPR[MAX_RTU];
	}	COM_PAR ;
	
	
	
/* MOSCAD állomás IEC adat leiró szerkezete */
typedef	struct
	{
	/*unsigned short				nTableNumPar;		Egesz paraméterek tábla sorszáma */	
	int							nIEC_SP;			/* Egybites értékek IEC kezdõcíme*/
	int							nIEC_SP_NUM;		/* Egybites értékek száma*/	
	/*int							nIEC_SP_FLAG;		 Egybites FLAG értékek IEC kezdõcíme*/
	/*int							nIEC_SP_FLAG_NUM;	 Egybites FLAG értékek száma*/
	int							nIEC_DP;			/* Kétbites értékek IEC kezdõcíme*/
	int							nIEC_DP_NUM;   		/* Két bites értékek száma*/	
	/*int							nIEC_DP_FSZ1;		1. földelõ szakaszoló IEC címe*/
	/*int							nIEC_DP_FSZ_NUM;	 Földelõ szakaszolók száma*/
	int							nIEC_NM;			/* Mérések IEC kezdõcíme */		
	int							nNMNum;				/* Analóg mérések száma*/
	int							nIEC_NM2;			/*  Egyeb mérések IEC kezdõcíme */		
	int							nNMNum2;			 /*Egyeb analóg mérések száma*/
	
	
		
	}	STATION_DESC_MOT ;		
	
	/* TALUS-os állomás leiró szerkezete */
typedef	struct
	{
	int							nIEC_SP;			/* Egybites értékek IEC kezdõcíme*/
	int							nIEC_DP;			/* Kétbites értékek IEC kezdõcíme*/
	int							nIEC_DP_FSZ1;		/* 1. földelõ szakaszoló IEC címe*/
	int							nNMNum;				/* Analóg jelek száma*/
	/* int							dummy2;				 3. földelõ szakaszoló IEC címe*/
	/* int							dummy3;				 4. földelõ szakaszoló IEC címe*/
	int							nIEC_DP_2BIT1;		/* 1. kétbites képzett jel IEC címe*/
	int							nIEC_DP_2BIT2;		/* 2. kétbites képzett jel IEC címe*/
	int							nIEC_DP_2BIT3;		/* 3. kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT1;		/* 1. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT2;		/* 2. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT3;		/* 3. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT4;		/* 4. egy bitbõl képzett kétbites képzett jel IEC címe*/
	/*int							nIEC_DP_12BIT5;		 5. egy bitbõl képzett kétbites képzett jel IEC címe*/
	/*int							nIEC_DP_12BIT6;		 6. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_2BIT_KINT1;	/* 1. kétbites képzett jel KINT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BENT1;	/* 1. kétbites képzett jel BENT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_KINT2;	/* 2. kétbites képzett jel KINT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BENT2;	/* 2. kétbites képzett jel BENT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_KINT3;	/* 3. kétbites képzett jel KINT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BENT3;	/* 3. kétbites képzett jel BENT jelzés TALUS bemenet sorszáma */	
	/*int							nTableNumPar;		 Egesz paraméterek tábla sorszáma */
	int							nIEC_NM;			/* Mérések IEC kezdõcíme */	
	int							nIEC_OsszevontHiba;	/* Összevont zárlati hiba IEC címe */
	int							nIEC_MT_KommHiba;	/* MOSCAD-TALUS kommunikációs hiba IEC címe */
	int							nKommStatusNum;		/* MOSCAD-TALUS kommunikációs hiba statuszok szama  */
	/*int							nIEC_ElsoZarlatCim;  Zárlati hibák kezdõ IEC címe */
	/* unsigned short				nDataTable;			 Tabla sorszama, ahová az adatok erkeztek */
	/* unsigned short				nDataColoumn;		 Oszlop sorszáma, ahová az adatok érkeztek */
	int							nIEC_DP_2BIT_BK1;	/* 1. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK2;	/* 2. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK3;	/* 3. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK4;	/* 4. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	/*int							nIEC_DP_2BIT_BK5;	 5. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	/*int							nIEC_DP_2BIT_BK6;	 6. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nSP_EXTRA_NUM;		/* Extra 1 bites darabszam  */
	int							nSP_EXTRA_OFFSET;	/* Extra 1 bites cim  */
	int							nDP_EXTRA_NUM;		/* Extra 2 bites darabszam  */
	int							nDP_EXTRA_OFFSET;	/* Extra 2 bites cim  */
	int							nLeagNum;			/* Leadazasok szama: 4,8 */
		
	}	STATION_DESC_TALUS ;	
	
/* Megadja, hogy az egyes RTU-k milyen tipusúak, és hogy az adatleiro tombben mi az indexük*/	
typedef struct
{
	int							nType;				/* 1=TALUS, 2=MOTOROLA, 3=TMOK */

} STATION_TYPE_INDEX;

/*  Az egyes RTU-k kommunikáció jellemzõi*/
typedef struct
{
	unsigned short				nError;				/* Hibaszámláló */
	/*unsigned short				nState;				 1 = Kommunikáció hibás  */
	/*unsigned char				byLekIndult;		 1 = Lekérdezés indult az adott RTU-ra  */
	/*unsigned short				nCtrComm;			 Bejelentkezések száma az adott RTU-tól*/
	/*unsigned short				nCtrLek;			 Lekérdezések száma az adott RTU-ra*/
	
	
} STATION_COMM_DATA;

typedef struct 
{
	unsigned short			nRtuNumRad ;			/* Osszes RTU szama Radio linken*/
	unsigned short			nIndx[MAX_RTU];			/* RTU-k indexei a site tablaban */
} RTU_RAD;

typedef struct 
{
	unsigned short			nRtuNumRad ;			/* Osszes RTU szama Radio linken*/
	unsigned short			nIndx[110]; 			/* RTU-k indexei a site tablaban */
} RTU_RAD_NEW;

typedef struct 
{
	unsigned short			nRtuNumLin ;			/* Osszes RTU szama RS linken*/
	unsigned short			nIndx[MAX_RTU];			/* RTU-k indexei a site tablaban */
} RTU_LIN;



typedef	struct
	{
	int							nIEC_SP;			/* Egybites értékek IEC kezdõcíme*/
	int							nIEC_DP;			/* Kétbites értékek IEC kezdõcíme*/
	int							nIEC_DP_FSZ1;		/* 1. földelõ szakaszoló IEC címe*/
	int							nNMNum;				/* Analóg jelek száma*/
	int							dummy2;				/* 3. földelõ szakaszoló IEC címe*/
	int							dummy3;				/* 4. földelõ szakaszoló IEC címe*/
	int							nIEC_DP_2BIT1;		/* 1. kétbites képzett jel IEC címe*/
	int							nIEC_DP_2BIT2;		/* 2. kétbites képzett jel IEC címe*/
	int							nIEC_DP_2BIT3;		/* 3. kétbites képzett jel IEC címe*/
	int							nIEC_DP_2BIT4;		/* 4. kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT1;		/* 1. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT2;		/* 2. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT3;		/* 3. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT4;		/* 4. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT5;		/* 5. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_12BIT6;		/* 6. egy bitbõl képzett kétbites képzett jel IEC címe*/
	int							nIEC_DP_2BIT_KINT1;	/* 1. kétbites képzett jel KINT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BENT1;	/* 1. kétbites képzett jel BENT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_KINT2;	/* 2. kétbites képzett jel KINT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BENT2;	/* 2. kétbites képzett jel BENT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_KINT3;	/* 3. kétbites képzett jel KINT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BENT3;	/* 3. kétbites képzett jel BENT jelzés TALUS bemenet sorszáma */	
	int							nIEC_DP_2BIT_KINT4;	/* 4. kétbites képzett jel KINT jelzés TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BENT4;	/* 4. kétbites képzett jel BENT jelzés TALUS bemenet sorszáma */	
	int							nTableNumPar;		/* Egesz paraméterek tábla sorszáma */	
	int							nIEC_NM;			/* Mérések IEC kezdõcíme */	
	int							nIEC_OsszevontHiba;	/* Összevont zárlati hiba IEC címe */
	int							nIEC_MT_KommHiba;	/* MOSCAD-TALUS kommunikációs hiba IEC címe */
	int							nKommStatusNum;		/* MOSCAD-TALUS kommunikációs hiba statuszok szama  */
	int							nIEC_ElsoZarlatCim; /* Zárlati hibák kezdõ IEC címe */
	unsigned short				nDataTable;			/* Tabla sorszama, ahová az adatok erkeztek */
	unsigned short				nDataColoumn;		/* Oszlop sorszáma, ahová az adatok érkeztek */
	int							nIEC_DP_2BIT_BK1;	/* 1. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK2;	/* 2. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK3;	/* 3. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK4;	/* 4. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK5;	/* 5. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nIEC_DP_2BIT_BK6;	/* 6. egy bitbõl képzett kétbites jel TALUS bemenet sorszáma */		
	int							nSP_EXTRA_NUM;		/* Extra 1 bites darabszam  */
	int							nSP_EXTRA_OFFSET;	/* Extra 1 bites cim  */
	int							nDP_EXTRA_NUM;		/* Extra 2 bites darabszam  */
	int							nDP_EXTRA_OFFSET;	/* Extra 2 bites cim  */
		
	}	STATION_DESC_SEPAM ;	


typedef struct 
{
	COM_PAR					*sCP;			/* Parancskuldes parameterei */
	STATION_DESC_MOT		*sMOT;			/* Moscad allomasok IEC adatcimei*/
	STATION_DESC_TALUS		*sTAL;			/* Talus allomasok IEC adatcimei*/
	STATION_TYPE_INDEX		*sTI;			/* Allomas tipusa */ /* 1=TALUS, 2=MOTOROLA, 3=TMOK */
	RTU_RAD_NEW				*sRAD_K1;		/* Radios RTU-k indexei*/
	RTU_RAD_NEW				*sRAD_K2;		/* Radios RTU-k indexei*/
	RTU_RAD_NEW				*sRAD_K3;		/* Radios RTU-k indexei*/
	RTU_LIN					*sLIN;			/* Radios RTU-k indexei*/
	unsigned short			*nNumOfSites;	/* Osszes RTU szama */
	unsigned short			*nSiteList;		/* RTU-k Site cimei*/
	unsigned short			*nLinkList;		/* RTU-k linkjei */
	STATION_DESC_SEPAM		*sSep;			/* Auchan */
	
} TOTAL_PAR;

/* TALUS esemeny szerkezete */
typedef	struct
	{
	int				n800H ;
	unsigned int	nTalusAddr ;
	int				nDummy ;	
	int				nValue;
	int				nMin;
	int				nMs1;
	int				nMs2;
	}	STR_TALUS_EVENT ;
	
	
