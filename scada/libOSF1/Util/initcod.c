/**********************************************************************
*
*       C Source:               initcod.c
*       Subsystem:              1
*       Description:
*       %created_by:    ciccotel %
*       %date_created:  Mon Dec 16 16:25:57 2002 %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: initcod.c-3 %  (%full_filespec: initcod.c-3:csrc:1 %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*->initcod
	la function initcod inizializzza le strutture
	delle code definite nell'include code.inc
*/
#include <pthread.h>
#include <code.h>

/*
        definizione dei canali utilizzati: code
*/
short c_digor, c_visall, c_stamp, c_tabul, c_cval, c_ut_rx, c_ut_tx;
short c_dua_tx, c_dua_rx;
short c_mmii, c_mmio;
short c_comani, c_comano;
short c_aggcfgi, c_aggcfgo;
short CHPERIF_00;
short c_acquii, c_acquio;
short mbox_inet;
short mbox_dua;
short c_prnrem0;
short qperif_00;
short qperif_01;
short qperif_02;
short qperif_03;
short qperif_04;
short qperif_05;
short qperif_06;
short qperif_07;
short c_hcwin;
short c_rep;

initcod()
{
int i ;

cd[0].dim=dim_0 ;  cd[0].passo=0;
cd[1].dim=dim_1 ;  cd[1].passo=0;
cd[2].dim=dim_2 ;  cd[2].passo=0;
cd[3].dim=dim_3 ;  cd[3].passo=0;
cd[4].dim=dim_4 ;  cd[4].passo=0;
cd[5].dim=dim_5 ;  cd[5].passo=0;
cd[6].dim=dim_6 ;  cd[6].passo=0;
cd[7].dim=dim_7 ;  cd[7].passo=0;
cd[8].dim=dim_8 ;  cd[8].passo=0;	
cd[9].dim=dim_9 ;  cd[9].passo=0;	  		
cd[10].dim=dim_10; cd[10].passo=0;
cd[11].dim=dim_11; cd[11].passo=0;
cd[12].dim=dim_12; cd[12].passo=0;
cd[13].dim=dim_13; cd[13].passo=0;
cd[14].dim=dim_14; cd[14].passo=0;
cd[15].dim=dim_15; cd[15].passo=0;
cd[16].dim=dim_16; cd[16].passo=0;
cd[17].dim=dim_17; cd[17].passo=0;
cd[18].dim=dim_18; cd[18].passo=0;
cd[19].dim=dim_19; cd[19].passo=0;
cd[20].dim=dim_20; cd[20].passo=0;
cd[21].dim=dim_21; cd[21].passo=0;
cd[22].dim=dim_22; cd[22].passo=0;
cd[23].dim=dim_23; cd[23].passo=0;
cd[24].dim=dim_24; cd[24].passo=0;
cd[25].dim=dim_25; cd[25].passo=0;
cd[26].dim=dim_26; cd[26].passo=0;
cd[27].dim=dim_27; cd[27].passo=0;
cd[28].dim=dim_28; cd[28].passo=0;
cd[29].dim=dim_29; cd[29].passo=0;
cd[30].dim=dim_30; cd[30].passo=0;
cd[31].dim=dim_31; cd[31].passo=0;
cd[32].dim=dim_32; cd[32].passo=0;
cd[33].dim=dim_33; cd[33].passo=0;
cd[34].dim=dim_34; cd[34].passo=0;
cd[35].dim=dim_35; cd[35].passo=0;
cd[36].dim=dim_36; cd[36].passo=0;
cd[37].dim=dim_37; cd[37].passo=0;
cd[38].dim=dim_38; cd[38].passo=0;
cd[39].dim=dim_39; cd[39].passo=0;

cd[0].init=0 ;
cd[0].fine=cd[0].dim ;
cd[0].occup=0 ;
cd[0].acc=0;
cd[0].sco=0;
for(i=1;i<num_code;i++)
{
/*
	inizializzo i vettori per le code
*/
	cd[i].occup=0 ;
	cd[i].init=cd[i-1].init+cd[i-1].dim ;
	cd[i].fine=cd[i].init+cd[i].dim  ;
        cd[i].acc=cd[i].init   ;
        cd[i].sco=cd[i].init   ;
}
for(i=0;i<num_code;i++)
	{
        pthread_mutex_init(&(cd[i].mutex),pthread_mutexattr_default);
        pthread_mutex_init(&(cd[i].mutex_condition_r),
			pthread_mutexattr_default);
	pthread_cond_init(&(cd[i].condition_r),pthread_condattr_default);
        pthread_mutex_init(&(cd[i].mutex_condition_s),
			pthread_mutexattr_default);
	pthread_cond_init(&(cd[i].condition_s),pthread_condattr_default);
	}

/*
	assegnazione delle code
*/
c_digor = 0;
c_visall = 1;
c_stamp = 2;
c_tabul = 3;
c_cval = 4;
c_ut_rx = 5;
c_ut_tx= 6;
c_dua_tx = 7;
c_dua_rx= 8;
c_mmii = 9;
c_mmio= 10;
c_aggcfgi = 11;
c_aggcfgo= 12;
CHPERIF_00= 13;
c_acquii = 14;
c_acquio= 15;
mbox_inet= 16;
mbox_dua= 17;
c_prnrem0= 18;
qperif_00= 19;
qperif_01= 20;
qperif_02= 21;
qperif_03= 22;
qperif_04= 23;
qperif_05= 24;
qperif_06= 25;
qperif_07= 26;
c_hcwin= 27;
c_rep=28;
c_comani = 29;
c_comano= 30;
}

