/**********************************************************************
*
*       C Header:               messaggi.h
*       Subsystem:              4
*       Description:
*       %created_by:    mauric %
*       %date_created:  Tue Jul 14 10:47:05 1998 %
*
**********************************************************************/
/*
 *  messaggi.h
 *
 *  contiene tutte le stringhe di messaggio del sistema
 *  (divisione per lingua)
 */
#ifndef MESSAGGI_H
#define MESSAGGI_H
/************************************************************************/
#define DEFAULT_TITLE   " INIT FROM STEADY STATE "  
#define DEFAULT_INIT    " STEADY STATE "
#define INIT_SIM        " INITIALIZING SIMULATOR "
#define SEL_VAR_TITLE   " Selected file "
#define LOAD_FILESEL    " FILE LOAD "
#define SAVE_FILESEL    " FILE SAVE "
#define IC_COMMENT_REQ  " Enter the I.C. description: "
/************************************************************************/
/* ERRORI */
#define OPER_FALLITA    ">>>>> FAILED <<<<<"
#define FALLITA         ">>>>>      FAILED      <<<<<"
#define ABORT_TASK      ">>>>> TASK ABORTED : <<<<<"
#define RESTART_TASK    ">>>>> TASK RESTARTED : <<<<<"
#define START_TASK      "TASK ACTIVATED : "
#define ABORTING        "        PROGRAM STOP         "
#define ERRORE_INIT     " INSTRUCTOR STATION NOT CONNECTED "
#define ERRORE_AGGANCIO "  ERROR WHILE CONNECTING TO DISPATCHER  "
#define ERROR_SIM       " SIMULATOR ERROR "
#define REINIT          " REINIT THE SIMULATOR "
#define NOT_EXECUTABLE  "    REQUEST NOT EXECUTABLE "
#define BAD_STATE       " SIMULATOR STATE NOT CONSISTENT "
#define NO_BT_LIST      " No recorded backtrack "
#define NAME_RESERVED   "Reserved file"
#define NOT_EXISTENT    "Not existent file"
#define NOT_ACCESSIBLE  "File not reachable"
#define VAR_NOT_EXIST   "Variable not existent"
#define ENTRY_NOT_SEL   "UNSELECTED TARGET "
#define NO_MORE_ENTRIES "No more available entries"
#define NOT_PERMITTED   "Operation not permitted"
#define OUT_OF_PATH     "User not allowed "
#define FIELD_NOT_VALID "Field not valid "
#define ALREADYIN 		"ALREADY LOADED"
#define STARTUP_ERR		"STARTUP ERRORS"
/************************************************************************/
/* INITIAL CONDITIONS & BT */
#define WARN_CUT_CI	   "    REMOVE I.C.     "
#define WARN_REPLACE_CI	" REPLACED I.C. " 
#define RESTORE_DEF_CI  " BACK TO THE PREVIOUS SESSION "
#define CUT_CI          "Deletion C.I. "
#define COPY_CI         "Copying C.I. "
#define CHECK_CI        "Accepting C.I. "
#define PASTE_CI        "Paste buffer in C.I. "
#define SAVE_CI         "Snapshot in C.I. "
#define EMPTY_IC        "<<< AVAILABLE >>>"
#define SAVE_BT         "Record B.T. "
#define LOAD_CI         "Load C.I. "
#define LOAD_BT         "Load BT "
#define DEFAULT_SNAP    "Default snapshot"

/************************************************************************/
/* CAMBI DI STATO */
#define RUN_SIM         "Switch to RUN"
#define FREEZE_SIM      "Switch to FREEZE"
#define BACKTRACK_SIM   "Switch to BACKTRACK"
#define REPLAY_SIM      "Switch to REPLAY"
#define STEP_SIM        "Executing STEP"
#define SHUTDOWN_SIM    "SIMULATOR SHUTDOWN"

/************************************************************************/
/* headers interfacce  e labels interfacce */
#define AING_SELECTION  " VARIABLE SELECTION FOR AING "
#define NEW_SESSION_NAME  "New session title"
#define NEW_STAT_REQ    "New statistcs request "
#define NEW_DELTAT_BT   "Changing BT recording step "
#define NEW_SPEED       "Changing simulator speed "
#define MAX_SIM_TIME    "Set Max Simulation Time"
#define ENTRY_AVAILABLE "<<< AVAILABLE ENTRY >>>"

/************************************************************************/
/* messaggi per lista */
#define CLEAR_SIM       "Reset simulation time & recordings "
#define READ_SNAP_VIEW  " Reading data from snap "
#define READ_BT_VIEW    " Reading data from bt "
#define STEPSCALE       "Step Scaling"
#define LAST_BT_READ    "Reading last recorded B.T. "
#define VALIDATE_BT_OK  "Validating database loaded from BT "
#define NEW_VAR_CR      "Updating variable list for recording "
#define NEW_STEP_CR     "Changing CR step "
#define PROGRAM_ACT     "Program activated "
#define SAVE_FILE_CR    "Save configuration on file "
#define SAVE_FILE_PREV  "Save configuration on file "
#define SAVE_FILE_SCEN  "Save scenario on file "
#define LOAD_FILE_CR    "Load configuration from file "
#define LOAD_FILE_PREV  "Load configuration from file "
#define LOAD_FILE_SCEN  "Load scenario from file "
#define ENTRY_NUMBER    "Record n. "
/************************************************************************/
/*
 * edit pert
 */
#define ACT_PERT_LABEL	"Active Pert"
#define UNACT_PERT_LABEL	"Not Active Pert"
#define PERT_FREQ_UPD	"Update period: "
#define PERTRATE			"Updating Pert Rate Refresh"
/************************************************************************/
#define RUN_LABEL       "RUN"
#define FREEZE_LABEL    "FREEZE"
#define STEP_LABEL      "STEP"
/************************************************************************/
#define SIMTIME_LABEL   "Sim. Time  "
#define RITARDO_LABEL   "Delay Time "
#define SPEED_LABEL     "Speed      "
/************************************************************************/
#define REPLAY_MODE_LABEL "Replay mode"
#define REPLAY_ACTIVE   "Replay mode activated "
#define REPLAY_STOP     "Replay mode terminated "
#define BT_ACT_LOAD     "BT loaded "
/************************************************************************/
#define DELTAT_REC_BT   "DELAY BT RECORDING"
/************************************************************************/
#define MALF				"MALFUNCTION "
#define NOT_CONFIGURED	"NOT CONFIGURED VARIABLE"
#define FREM				"REMOTE FUNCTION "
#define MALF_CONF_READ  "READING CONFIGURATION "
#define FREM_CONF_READ  "READING REMOTE FUNCTIONS CONFIGURATION "
#define MALF_SUMMARY    "Active malfunction summary"
#define FREM_SUMMARY    "Active remote functions summary"
#define TYPE_NOT_EXIST  "Not existent type "
#define MALF_SCEN_LIST  "MALFUNCTIONS SCENARIOS LIST"
#define FREM_SCEN_LIST  "REMOTE FUNCTIONS SCENARIOS LIST"
#define MALF_SCEN_TITLE "Scenario comment: "
#define DELAY_LABEL		"Delay:"
#define DURATION_LABEL	"Duration:"
#define RAMP_LABEL		"Ramp:"
#define MALF_LIST			"MALFUNCTIONS SUMMARY LIST"
#define FREM_LIST			"REMOTE FUNCTIONS SUMMARY LIST"
#define NEW_MALF_SCEN   "NEW MALFUNCTIONS SCENARIO"
#define NEW_FREM_SCEN   "NEW REMOTE FUNCTIONS SCENARIO"
#define MALF_SELECTION  " MALFUNCTION SELECTION "
#define FREM_SELECTION  " REMOTE FUNCTION SELECTION "
#define VAL_ACT_LABEL   " Actual value: "
/************************************************************************/
/* labels selVarCr e selVar */
#define SYSTEM_LIST     "Systems"
#define BLOCK_LIST      "Blocks"
#define VAR_TO_SELECT   "Selectable variables"
#define VAR_SELECTED    "Selected variables"
#define CONF_ACCEPT     "SAVE"
#define SELVAR_CONFIRM  "SELECT"
#define CONF_DISCARD    "QUIT"
#define SELECT_ALL      "All"
#define SELECT_VAR      "Add"
#define UNSELECT_VAR    "Remove"
#define SAVEFILTER		"Save Filter"
#define APPLYFILTER		"Apply Filter"

#define NEW_FILTER		"NEW FILTER SELECTION"
#define ATTN_FILTER1		"THIS SELECTION MAY TAKE A LONG TIME"
#define ATTN_FILTER2		"        FOR ACTUATION              "

/*
 * filtro kks
 */
#define KKS_NIMP_LABEL	"N."
#define KKS_SYST_LABEL  "System"
#define KKS_SSYST_LABEL "Sottosist"
#define KKS_COMP_LABEL  "Component"
#define KKS_PROG_LABEL  "Progress"
#define KKS_APPLY_FILTER "APPLY"
/*
 * filtro per tipo
 */
#define TIPO_PRESSIONE	"Pressure"
#define TIPO_TEMPERATURA "Temperature"
#define TIPO_ENTALPIA    "Entalpy"
#define TIPO_PORTATA     "Flow"
#define TIPO_POTENZA     "Power"
#define TIPO_GIRI        "R.P.M."
#define TIPO_ALZVALV     "Valve lift"
#define TIPO_AINGABLE    "Not conn. input"
#define TIPO_INPUT       "Input"
#define TIPO_OUTPUT      "Output"

/************************************************************************/
/*
 * process start
 */
#define PROC_START_OK	 "Continue"
#define PROC_START_Quit  "Quit"
#define PROC_START_LABEL "Start process: "
#define PROC_START_DISPLAY "on display: "
/************************************************************************/
/*
 * label generali
 */
#define OPTION_APPLY_LABEL  "APPLY"
#define APPLYLABEL		"APPLY"
#define QUITLABEL			"QUIT"
#define EXITLABEL			"EXIT"
#define ACT_LABEL			"ACTIVATE"
#define DEACT_LABEL		"REMOVE"

/************************************************************************/
/*
 * label generali per menu
 */
#define	FileMenuLabel			"File"
#define  EditMenuLabel			"Edit"
#define  ShowMenuLabel			"Show"
#define  HelpMenuLabel			"Help"

#define  SaveMenuLabel			"Save"
#define  SaveMenuLabel2			"Save ..."
#define  OpenMenuLabel			"Open"
#define  OpenMenuLabel2			"Open ..."
#define  QuitMenuLabel			"Quit"
#define  NewMenuLabel			"New ..."
#define  CutMenuLabel			"Cut"
#define  AddItemLabel			"Add ..."
#define  AddItemLabel2			"Add"
#define  ClearLabel	   		"Clear ..."
#define  MaxTimeLabel	   	"Max Sim. Time ..."
#define  MaxSpeedLabel	   	"Max Speed"
#define  SetSpeedLabel	   	"Speed ..."
#define  StepScalingLabel	   "Step Scaling ..."
#define  SnapshotLabel	   	"Snapshot ..."
#define  BacktrackLabel	   	"Backtrack ..."
#define  ContRecLabel	   	"Cont. Recording"
#define  IandTactionLog	   	"Instr. & Trainee A.L."
#define  PerformanceLabel	   "Performance analisys"
#define  ShutdownLabel	   	"Simulator Shutdown ..."
#define  InitIcLabel  	   	"Init from Snapshot ..."
#define  InitBtLabel				"Init from Backtrack ..."

#define  CompressLabel        "Compress Interface"
#define  ExpandLabel          "Expand Interface"
#define  MasterMenuLabel      "Master Menu"
#define  PrintMenuLabel       "Print"
#define  CopyMenuLabel        "Copy"
#define  PasteMenuLabel       "Paste"
#define  ViewMenuLabel        "View"
#define  LoadMenuLabel        "Load"
#define  CheckMenuLabel       "Check"

#define  LoadDefaultLabel		"Load default"
#define  SelectNewLabel  		"Select new ..."
#define  ClearAllLabel	   	"Clear all "
#define  CheckAllLabel        "Check all"
#define  LOADLABEL        		"LOAD"
#define  SAVELABEL        		"SAVE"
#define  VIEWLABEL        		"VIEW"
#define  INITLABEL        		"INIT"
#define  InitMenuLabel        "Init"


#endif
