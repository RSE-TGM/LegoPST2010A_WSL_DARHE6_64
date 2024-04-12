/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef _h_installa_variabili_h
#define _h_installa_variabili_h



#define LUN_SIGNAL	2   // senza terminatore
#define TAG_SIGNAL	"$"


struct struct_app_tag_st
        {
	int TAG_ID;
	int TAG_SCADA_USE;
        char TAG_NAME[SCD_SIGLA+1];
	char TAG_ALARM;
	int HDR_CODE;
        };
typedef struct struct_app_tag_st APP_TAG;

struct struct_allaras_st
        {
        char *CodiceAll;
        char *DescrAll;
        char TipoCalc;
        char PeriodoCalc;
        };

typedef struct struct_allaras_st STRUCT_ALLARAS;

#endif
