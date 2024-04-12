/**********************************************************************
*
*       C Header:               messages.h
*       Subsystem:              4
*       Description:
*       %created_by:    zanna %
*       %date_created:  Wed Jun 11 13:50:07 1997 %
*
**********************************************************************/
/*
 *  messages.h
 *
 *  contiene tutte le stringhe di messaggio del sistema
 *  (divisione per lingua)
 */
#ifndef MESSAGES_H
#define MESSAGES_H

#define MAX_NOME_LEN       100   /* max lung. nome label    */
#define MAX_STRINGA_LEN    100   /* max lung. stringa       */

/************************************************************************/
#define DEFAULT_TEXT			0
#define ENGLISH_TEXT			1
#define ITALIAN_TEXT			2
/************************************************************************/
struct messagesSt
	{
	char label[MAX_NOME_LEN];
	char *string;				/* contiene il valore della stringa		*/
	int indx;					/* indice identificativo					*/
	};
typedef struct messagesSt MESSAGES;
/************************************************************************/

char *DEFAULT_TITLE_;
char *DEFAULT_INIT_;
char *INIT_SIM_;
char *SEL_VAR_TITLE_;
char *LOAD_FILESEL_;
char *SAVE_FILESEL_;
char *IC_COMMENT_REQ_;
char *OPER_FALLITA_;
char *FALLITA_;
char *ABORT_TASK_;
char *START_TASK_;
char *ABORTING_;
char *ERRORE_INIT_;
char *ERRORE_AGGANCIO_;
char *ERROR_SIM_;
char *REINIT_;
char *NOT_EXECUTABLE_;
char *BAD_STATE_;
char *NO_BT_LIST_;
char *NAME_RESERVED_;
char *NOT_EXISTENT_;
char *NOT_ACCESSIBLE_;
char *VAR_NOT_EXIST_;
char *ENTRY_NOT_SEL_;
char *NO_MORE_ENTRIES_;
char *NOT_PERMITTED_;
char *OUT_OF_PATH_;
char *FIELD_NOT_VALID_;
char *ALREADYIN_;
char *WARN_CUT_CI_;
char *WARN_REPLACE_CI_;
char *RESTORE_DEF_CI_;
char *CUT_CI_;
char *COPY_CI_;
char *CHECK_CI_;
char *PASTE_CI_;
char *SAVE_CI_;
char *EMPTY_IC_;
char *SAVE_BT_;
char *LOAD_CI_;
char *LOAD_BT_;
char *DEFAULT_SNAP_;
char *RUN_SIM_;
char *FREEZE_SIM_;
char *BACKTRACK_SIM_;
char *REPLAY_SIM_;
char *STEP_SIM_;
char *SHUTDOWN_SIM_;
char *AING_SELECTION_;
char *NEW_SESSION_NAME_; 
char *NEW_STAT_REQ_;
char *NEW_DELTAT_BT_;
char *NEW_SPEED_;
char *MAX_SIM_TIME_;
char *ENTRY_AVAILABLE_;
char *CLEAR_SIM_;
char *READ_SNAP_VIEW_;
char *READ_BT_VIEW_;
char *STEPSCALE_;
char *LAST_BT_READ_;
char *VALIDATE_BT_OK_;
char *NEW_VAR_CR_;
char *NEW_STEP_CR_;
char *PROGRAM_ACT_;
char *SAVE_FILE_CR_;
char *SAVE_FILE_PREV_;
char *SAVE_FILE_SCEN_;
char *LOAD_FILE_CR_;
char *LOAD_FILE_PREV_;
char *LOAD_FILE_SCEN_;
char *ENTRY_NUMBER_;
char *ACT_PERT_LABEL_;
char *UNACT_PERT_LABEL_;
char *PERT_FREQ_UPD_;
char *PERTRATE_;
char *RUN_LABEL_;
char *FREEZE_LABEL_;
char *STEP_LABEL_;
char *SIMTIME_LABEL_;
char *RITARDO_LABEL_;
char *SPEED_LABEL_;
char *REPLAY_MODE_LABEL_;
char *REPLAY_ACTIVE_;
char *REPLAY_STOP_;
char *BT_ACT_LOAD_;
char *DELTAT_REC_BT_;
char *MALF_;
char *NOT_CONFIGURED_;
char *FREM_;
char *MALF_CONF_READ_;
char *FREM_CONF_READ_;
char *MALF_SUMMARY_;
char *FREM_SUMMARY_;
char *TYPE_NOT_EXIST_;
char *MALF_SCEN_LIST_;
char *FREM_SCEN_LIST_;
char *MALF_SCEN_TITLE_;
char *DELAY_LABEL_;
char *DURATION_LABEL_;
char *RAMP_LABEL_;
char *MALF_LIST_;
char *FREM_LIST_;
char *NEW_MALF_SCEN_;
char *NEW_FREM_SCEN_;
char *SYSTEM_LIST_;
char *BLOCK_LIST_;
char *VAR_TO_SELECT_;
char *VAR_SELECTED_;
char *CONF_ACCEPT_;
char *SELVAR_CONFIRM_;
char *CONF_DISCARD_;
char *SELECT_ALL_;
char *SELECT_VAR_;
char *UNSELECT_VAR_;
char *SAVEFILTER_;
char *APPLYFILTER_;
char *NEW_FILTER_;
char *ATTN_FILTER1_;
char *ATTN_FILTER2_;
char *KKS_NIMP_LABEL_;
char *KKS_SYST_LABEL_;
char *KKS_SSYST_LABEL_;
char *KKS_COMP_LABEL_;
char *KKS_PROG_LABEL_;
char *KKS_APPLY_FILTER_;
char *TIPO_PRESSIONE_;
char *TIPO_TEMPERATURA_;
char *TIPO_ENTALPIA_;
char *TIPO_PORTATA_;
char *TIPO_POTENZA_;
char *TIPO_GIRI_;
char *TIPO_ALZVALV_;
char *TIPO_AINGABLE_;
char *TIPO_INPUT_;
char *TIPO_OUTPUT_;
char *PROC_START_OK_;
char *PROC_START_Quit_;
char *PROC_START_LABEL_;
char *PROC_START_DISPLAY_;
char *OPTION_APPLY_LABEL_;
char *APPLYLABEL_;
char *QUITLABEL_;
char *EXITLABEL_;
char *ACT_LABEL_;
char *DEACT_LABEL_;
char *FileMenuLabel_;
char *EditMenuLabel_;
char *ShowMenuLabel_;
char *HelpMenuLabel_;
char *SaveMenuLabel_;
char *SaveMenuLabel2_;
char *OpenMenuLabel_;
char *OpenMenuLabel2_;
char *QuitMenuLabel_;
char *NewMenuLabel_;
char *CutMenuLabel_;
char *AddItemLabel_;
char *AddItemLabel2_;
char *ClearLabel_;
char *MaxTimeLabel_;
char *MaxSpeedLabel_;
char *SetSpeedLabel_;
char *StepScalingLabel_;
char *SnapshotLabel_;
char *BacktrackLabel_;
char *ContRecLabel_;
char *IandTactionLog_;
char *PerformanceLabel_;
char *ShutdownLabel_;
char *InitIcLabel_;
char *InitBtLabel_;
char *STARTUP_ERR_;
char *MALF_SELECTION_;
char *FREM_SELECTION_;
char *CompressLabel_;
char *ExpandLabel_;
char *MasterMenuLabel_;
char *PrintMenuLabel_;
char *CopyMenuLabel_;
char *PasteMenuLabel_;
char *ViewMenuLabel_;
char *LoadMenuLabel_;
char *CheckMenuLabel_;
char *VAL_ACT_LABEL_;

#define _DEFAULT_TITLE					1
#define _DEFAULT_INIT					2
#define _INIT_SIM							3
#define _SEL_VAR_TITLE					4
#define _LOAD_FILESEL					5
#define _SAVE_FILESEL					6
#define _IC_COMMENT_REQ					7
#define _OPER_FALLITA					8
#define _FALLITA							9
#define _ABORT_TASK						10
#define _START_TASK						11
#define _ABORTING							12 
#define _ERRORE_INIT						13
#define _ERRORE_AGGANCIO				14
#define _ERROR_SIM						15
#define _REINIT							16
#define _NOT_EXECUTABLE					17
#define _BAD_STATE						18
#define _NO_BT_LIST						19
#define _NAME_RESERVED					20
#define _NOT_EXISTENT					21
#define _NOT_ACCESSIBLE					22
#define _VAR_NOT_EXIST					23
#define _ENTRY_NOT_SEL					24
#define _NO_MORE_ENTRIES				25
#define _NOT_PERMITTED					26
#define _OUT_OF_PATH						27
#define _FIELD_NOT_VALID				28
#define _ALREADYIN						29
#define _WARN_CUT_CI						30
#define _WARN_REPLACE_CI				31	
#define _RESTORE_DEF_CI					32
#define _CUT_CI							33
#define _COPY_CI							34
#define _CHECK_CI							35
#define _PASTE_CI							36
#define _SAVE_CI							37
#define _EMPTY_IC							38
#define _SAVE_BT							39
#define _LOAD_CI							40
#define _LOAD_BT							41
#define _DEFAULT_SNAP					42
#define _RUN_SIM							43
#define _FREEZE_SIM						44
#define _BACKTRACK_SIM					45
#define _REPLAY_SIM 						46
#define _STEP_SIM							47
#define _SHUTDOWN_SIM					48
#define _AING_SELECTION 				49
#define _NEW_SESSION_NAME				50 
#define _NEW_STAT_REQ					51
#define _NEW_DELTAT_BT					52
#define _NEW_SPEED						53
#define _MAX_SIM_TIME					54
#define _ENTRY_AVAILABLE				55
#define _CLEAR_SIM						56
#define _READ_SNAP_VIEW					57
#define _READ_BT_VIEW					58
#define _STEPSCALE						59
#define _LAST_BT_READ					60
#define _VALIDATE_BT_OK					61
#define _NEW_VAR_CR						62
#define _NEW_STEP_CR						63
#define _PROGRAM_ACT 					64
#define _SAVE_FILE_CR					65
#define _SAVE_FILE_PREV					66
#define _SAVE_FILE_SCEN					67
#define _LOAD_FILE_CR					68
#define _LOAD_FILE_PREV					69
#define _LOAD_FILE_SCEN					70
#define _ENTRY_NUMBER					71
#define _ACT_PERT_LABEL					72
#define _UNACT_PERT_LABEL				73
#define _PERT_FREQ_UPD					74
#define _PERTRATE							75
#define _RUN_LABEL						76
#define _FREEZE_LABEL					77
#define _STEP_LABEL						78
#define _SIMTIME_LABEL					79
#define _RITARDO_LABEL					80
#define _SPEED_LABEL						81
#define _REPLAY_MODE_LABEL			   82		
#define _REPLAY_ACTIVE					83
#define _REPLAY_STOP						84
#define _BT_ACT_LOAD						85
#define _DELTAT_REC_BT					86
#define _MALF								87
#define _NOT_CONFIGURED					88
#define _FREM								89
#define _MALF_CONF_READ					90
#define _FREM_CONF_READ					91
#define _MALF_SUMMARY					92
#define _FREM_SUMMARY					93
#define _TYPE_NOT_EXIST					94
#define _MALF_SCEN_LIST					95
#define _FREM_SCEN_LIST					96
#define _MALF_SCEN_TITLE				97
#define _DELAY_LABEL						98
#define _DURATION_LABEL					99	
#define _RAMP_LABEL						100
#define _MALF_LIST						101
#define _FREM_LIST						102
#define _NEW_MALF_SCEN 					103
#define _NEW_FREM_SCEN 					104
#define _SYSTEM_LIST 					105
#define _BLOCK_LIST 						106
#define _VAR_TO_SELECT					107
#define _VAR_SELECTED					108
#define _CONF_ACCEPT						109
#define _SELVAR_CONFIRM					110
#define _CONF_DISCARD					111
#define _SELECT_ALL						112
#define _SELECT_VAR						113
#define _UNSELECT_VAR					114
#define _SAVEFILTER						115
#define _APPLYFILTER						116
#define _NEW_FILTER						117
#define _ATTN_FILTER1					118
#define _ATTN_FILTER2					119
#define _KKS_NIMP_LABEL					120
#define _KKS_SYST_LABEL					121
#define _KKS_SSYST_LABEL				122
#define _KKS_COMP_LABEL					123
#define _KKS_PROG_LABEL					124
#define _KKS_APPLY_FILTER				125
#define _TIPO_PRESSIONE					126
#define _TIPO_TEMPERATURA				127
#define _TIPO_ENTALPIA					128
#define _TIPO_PORTATA					129
#define _TIPO_POTENZA					130
#define _TIPO_GIRI						131
#define _TIPO_ALZVALV					132
#define _TIPO_AINGABLE 					133
#define _TIPO_INPUT						134
#define _TIPO_OUTPUT 					135
#define _PROC_START_OK					136
#define _PROC_START_Quit				137
#define _PROC_START_LABEL				138
#define _PROC_START_DISPLAY	 		139
#define _OPTION_APPLY_LABEL			140
#define _APPLYLABEL						141
#define _QUITLABEL						142
#define _EXITLABEL						143
#define _ACT_LABEL						144
#define _DEACT_LABEL						145
#define _FileMenuLabel					146
#define _EditMenuLabel					147
#define _ShowMenuLabel					148
#define _HelpMenuLabel					149
#define _SaveMenuLabel					150
#define _SaveMenuLabel2					151
#define _OpenMenuLabel					152
#define _OpenMenuLabel2					153
#define _QuitMenuLabel					154
#define _NewMenuLabel					155
#define _CutMenuLabel					156
#define _AddItemLabel					157
#define _AddItemLabel2					158
#define _ClearLabel						159
#define _MaxTimeLabel					160
#define _MaxSpeedLabel					161
#define _SetSpeedLabel					162
#define _StepScalingLabel				163
#define _SnapshotLabel	 				164
#define _BacktrackLabel					165
#define _ContRecLabel					166
#define _IandTactionLog					167
#define _PerformanceLabel				168
#define _ShutdownLabel					169
#define _InitIcLabel						170
#define _InitBtLabel						171
#define _STARTUP_ERR						172
#define _MALF_SELECTION					173
#define _FREM_SELECTION					174

#define _CompressLabel					175
#define _ExpandLabel						176
#define _MasterMenuLabel				177
#define _PrintMenuLabel					178
#define _CopyMenuLabel					179
#define _PasteMenuLabel					180
#define _ViewMenuLabel					181
#define _LoadMenuLabel					182
#define _CheckMenuLabel					183
#define _VAL_ACT_LABEL					184

#define _LoadDefaultLabel  			185
#define _SelectNewLabel   				186
#define _ClearAllLabel   				187
#define _CheckAllLabel  				188
#define _LOADLABEL     					189
#define _SAVELABEL    					190
#define _VIEWLABEL   					191
#define _INITLABEL  						192
#define _InitMenuLabel					193

/*** tenere aggiornato		*/
#define maxIndxMessages	200

#endif
