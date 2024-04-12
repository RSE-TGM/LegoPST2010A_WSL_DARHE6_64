/**********************************************************************
*
*       C Header:               option.h
*       Subsystem:              1
*       Description:
*       %created_by:    zanna %
*       %date_created:  Sat Jun  7 11:05:39 1997 %
*
**********************************************************************/
/*
 * option.h
 */
#ifndef OPTION_H
#define OPTION_H
/*************************************************************/
#define OPTION_FILE			".bi_options"
#define MAX_DISPLAY        5         /* numero max display configurabili */
#define MAX_DISPLAY_NAME   100       /* max lungh. display               */
#define DEFAULT_DISPLAY   "localdisplay:0.0" /* display locale           */

#define MAX_USERPROG       8         /* max numero utente configurabili */
#define MAX_USERPROG_LUN   100       /* lunghezza max comando           */

#define OPTION_INIT			0
#define OPTION_SNAPSHOT		1
#define OPTION_RECORDING	2
#define OPTION_MFFR			3
#define OPTION_ARCHIVE		4
#define OPTION_SHOW			5
#define OPTION_DISPLAY		6
#define OPTION_USERPROG		7
#define OPTION_ICPROTECT	8

/*
 * flags 
 */
struct options_init_st
	{
	Boolean clear;
	Boolean from_bt;
	Boolean from_ci;
	};
typedef struct options_init_st OPTIONS_INIT;

struct options_snapshot_st
	{
	Boolean active;
	Boolean save;
	Boolean delete;
	Boolean copy_and_paste;
	};
typedef struct options_snapshot_st OPTIONS_SNAPSHOT;

struct options_recording_st
	{
	Boolean active;
	Boolean backtrack;
	Boolean cr;
	Boolean ital;
	Boolean performance;
	Boolean archive;
	};
typedef struct options_recording_st OPTIONS_RECORDING;

struct options_mffr_st
	{
	Boolean active;
	};
typedef struct options_mffr_st OPTIONS_MFFR;

struct options_archive_st
	{
	Boolean active;
	};
typedef struct options_archive_st OPTIONS_ARCHIVE;

struct options_show_st
	{
	Boolean active;
	};
typedef struct options_show_st OPTIONS_SHOW;

struct options_environment_st
	{
	Boolean active;
	};
typedef struct options_environment_st OPTIONS_ENVIRONMENT;

struct options_display_st
	{
	char display_name[MAX_DISPLAY][MAX_DISPLAY_NAME];
	};
typedef struct options_display_st OPTIONS_DISPLAY;

struct options_userprog_st
   {
   char userprog[MAX_USERPROG][MAX_USERPROG_LUN];
   };
typedef struct options_userprog_st OPTIONS_USER_PROGS;
/* non piu' usata perche' l' area diventa parametrica */
/* flag ic protetta */
/*******
struct options_icprotect_st 
	{
	Boolean prot[MAX_SNAP_SHOT];     
	};
typedef struct options_icprotect_st OPTIONS_ICPROTECT;

********************************************************/
struct options_filterCr_st
	{
	Boolean ByAllVar;
	Boolean ByModBlock;
	Boolean ByMod;
	Boolean ByKks;
	Boolean ByType;
	};
typedef struct options_filterCr_st OPTIONS_FILTERCR;

struct options_filterAing_st
   {
   Boolean ByAllVar;
   Boolean ByModBlock;
   Boolean ByMod;
   Boolean ByKks;
   Boolean ByType;
   };
typedef struct options_filterAing_st OPTIONS_FILTERAING;

struct options_filterMalf_st
   {
   Boolean ByAllVar;
   Boolean ByModBlock;
   Boolean ByMod;
   Boolean ByKks;
   Boolean ByType;
   };
typedef struct options_filterMalf_st OPTIONS_FILTERMALF;

struct options_filterFrem_st
   {
   Boolean ByAllVar;
   Boolean ByModBlock;
   Boolean ByMod;
   Boolean ByKks;
   Boolean ByType;
   };
typedef struct options_filterFrem_st OPTIONS_FILTERFREM;
/*
 * generale
 */
struct options_flags_st
	{
	OPTIONS_INIT options_init;
	OPTIONS_SNAPSHOT options_snapshot;
	OPTIONS_RECORDING options_recording;
	OPTIONS_MFFR options_mffr;
	OPTIONS_ARCHIVE options_archive;
	OPTIONS_SHOW options_show;
	OPTIONS_ENVIRONMENT options_environment;
	OPTIONS_DISPLAY options_display;
	OPTIONS_USER_PROGS options_user_progs;
	OPTIONS_FILTERCR optionsFilterCr;
	OPTIONS_FILTERAING optionsFilterAing;
	OPTIONS_FILTERMALF optionsFilterMalf;
   OPTIONS_FILTERFREM optionsFilterFrem;
	};
typedef struct options_flags_st OPTIONS_FLAGS;
/*************************************************************/
#endif
