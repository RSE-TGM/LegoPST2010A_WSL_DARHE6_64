/**********************************************************************
*
*       C Header:               refresh.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed May 21 17:43:47 1997 %
*
**********************************************************************/
/*
 * refresh.h
 *
 * dati da visualizzare e flags di variazione;
 */
/*
 * valori attualmente in display o da displayare
 */
struct val_act_st
	{
	int stato_sim;
	float tempo_sim;	
	float tempo_ritardo;
	float timescaling_sim;
	float max_time;
	float stepscaling_sim;
	int grandezze_mem;
	float passo_reg_cr;
	float passo_reg_bt;
	int passo_pres_bt;
	float tempo[MAX_MODEL];
	float t_cpu[MAX_SLAVE];
	float stato_task[MAX_MODEL];
	float stato_sked[MAX_SLAVE];
	int operazione_eseguita;
	int num_operazione;
	};
typedef struct val_act_st VAL_ACTUAL;

/*
 * flags di variazione
 */
struct flags_val_display_st
	{
	char stato_sim;
	char tempo_sim;  
   char tempo_ritardo;
   char timescaling_sim;
	char max_time;
   char stepscaling_sim;
   char grandezze_mem;
   char passo_reg_cr;
   char passo_reg_bt;
   char passo_pres_bt;
   char tempo[MAX_MODEL];
   char t_cpu[MAX_SLAVE];
   char stato_task[MAX_MODEL];
   char stato_sked[MAX_SLAVE];
   char operazione_eseguita;
   char num_operazione;
	};
typedef struct flags_val_display_st FLAGS_VAL_DISPLAY;

struct val_display_st
	{
	VAL_ACTUAL actual;
	FLAGS_VAL_DISPLAY flags;
	};
typedef struct val_display_st VAL;
/************************************************************************/
