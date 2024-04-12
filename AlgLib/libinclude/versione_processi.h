/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
   modulo versione_processi.h
   tipo 
   release 5.1
   data 11/16/95
   reserved @(#)versione_processi.h	5.1
*/
struct nomi_processi_st
	{
	char nome[30];
	char versione[30];
	char data[30];
	};

typedef struct nomi_processi_st NOMI_PROCESSI;


static NOMI_PROCESSI nomi_processi[] = 
    {
	{
	"net_monit", "2.0","2 giugno 1993"
	},
	{
	"net_sked", "2.0","2 giugno 1993"
	},
	{
	"net_prepf22", "2.0","2 giugno 1993"
	},
	{
	"demone", "2.0","2 giugno 1993"
	},
	{
	"net_read", "2.0","2 giugno 1993"
	},
	{
	"net_updbase", "2.0","2 giugno 1993"
	},
	{
	"agg_legograf", "2.0","2 giugno 1993"
	},
	{
	"agg_perturba", "2.0","2 giugno 1993"
	},
	{
	"acq_perturba", "1.0","2 giugno 1993"
	},
	{
	"acq_perturba", "1.0","2 giugno 1993"
	},
	{
	"acq", "1.0","2 giugno 1993"
	},
	{
	"set_legograf", "1.0","2 giugno 1993"
	},
	{
	"comp", "1.0","2 giugno 1993"
	},
	{
	"net_compi", "2.0","2 giugno 1993"
	},
	{
	"net_compvar", "2.0","2 giugno 1993"
	},
	{
	"grafics", "1.0","2 giugno 1993"
	},
	{
	"xgraf", "1.0","2 giugno 1993"
	},
	{
	"xaing", "2.0","2 giugno 1993"
	},
	{
	"xplot", "2.0","2 giugno 1993"
	},
        {
        "prepf22shr", "1.0","2 giugno 1993"
        },
	{
	"xstaz", "2.0","2 giugno 1993"
	},
	{
	"dispatcher", "2.0","2 giugno 1993"
	},
	{
	"mandb", "1.0","2 giugno 1993"
	},
	{
	"acqmandb", "1.0","2 giugno 1993"
	},
	{
	"banco_bridge", "2.0","2 giugno 1993"
	},
	{
	"bridge", "2.0","2 giugno 1993"
	},
	{
	"killsim", "1.0","2 giugno 1993"
	},
	{
	"agg_scada", "1.0","2 giugno 1993"
	},
	{
	"agg_manovra", "1.0","2 giugno 1993"
	},
	{
	"mmi", "1.0","2 gennaio 1995"
	},
	{
	"config", "2.0","5 luglio 1995"
	},
	{
	"draw", "1.0","2 gennaio 1995"
	},
	{
	"client_scada", "1.0","2 gennaio 1995"
	},
	{
	"client_mmi", "1.0","2 gennaio 1995"
	},
	{
	"server_mmi", "1.0","2 gennaio 1995"
	},
	{
	"undefined", "0.0","01 gennaio 1900"
	}
    };

