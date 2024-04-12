/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef _db_h
#define _db_h

#define MAX_CAMPI_TABELLA	200
#define MAX_LUN_NOME_CAMPO	255
#define MAX_LUN_CAMPO	255


struct struct_table_st
        {
	char *nome_campo;
	int tipo;
	int int_default;
	char *char_default;
        };

typedef struct struct_table_st STRUCT_TABLE;

struct record_st
        {
	STRUCT_TABLE *tab;
        int tipo[MAX_CAMPI_TABELLA];
        int valore_int[MAX_CAMPI_TABELLA];
        char valore_char[MAX_CAMPI_TABELLA][MAX_LUN_CAMPO];
        };

typedef struct record_st RECORD;

struct rcord_st2
        {
        STRUCT_TABLE *tab;
        int tipo[MAX_CAMPI_TABELLA];
        int valore_int[MAX_CAMPI_TABELLA];
        char valore_char[MAX_CAMPI_TABELLA][MAX_LUN_CAMPO];
        };

typedef struct rcord_st2 RECORD2;


#ifdef ASCII_DB
#define ESTENSIONE_TABELLA ".txt"
#define MAXRIGA    5000
#define FILE_TABLE	0
#define MEM_TABLE	1
#define MAX_SIZE_MEM    1000000
#define TIPO_CHAR	0
#define TIPO_INT	1
#define TIPO_BOOLEAN	2
#define TIPO_FLOAT	3


#define NumRecord(tabella)	tabella->num_record
#define NumCampi(tabella)	tabella->num_campi
#define NomeCampo(tabella,n)	tabella->campi[n]

struct id_table_st
        {
        FILE *fp;
	int tipo_table;
	char *table;
	char *table_start;
	char *table_old;
	char **point_record;
	int size;
	int num_campi;
	int num_record;
	char campi[MAX_CAMPI_TABELLA][MAX_LUN_NOME_CAMPO];
	int tipo[MAX_CAMPI_TABELLA];
	int record_save;
	char riga_save[MAXRIGA];
        };

typedef struct id_table_st ID_TABLE;

typedef struct 
	{
	float float_val;
	int   int_val;
	char  char_val[MAX_LUN_CAMPO];
	} VAL_RET;


#endif

ID_TABLE * OpenTable(char *);
ID_TABLE * OpenTablePath(char *,char *);
int CloseTable(ID_TABLE *);
int ConnectDb();
int DisconnectDb();
int GetNumRecord(ID_TABLE *);
char * GetCampi(ID_TABLE *);
int GetVal(ID_TABLE *, char *, int, VAL_RET*);

#endif
