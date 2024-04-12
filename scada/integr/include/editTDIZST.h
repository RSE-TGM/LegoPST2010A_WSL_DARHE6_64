/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#ifndef h_editTDIZST_h
#define h_editTDIZST_h

STRUCT_TABLE editTDIZSTnocab[]={
        {"Stato",          TIPO_CHAR,0,     "" },
        {"codice",    TIPO_INT,0,     ""},
        };

#define NUM_CAMPI_EDITTDIZST_NOCAB sizeof(editTDIZSTnocab)/sizeof(STRUCT_TABLE)

struct struct_table_cab_st
        {
        char *riga;
        };

typedef struct struct_table_cab_st STRUCT_TABLE_CAB;

STRUCT_TABLE_CAB editTDIZST[]={
{"\"Stato\";\"codice\""},
{"\"TRANS.\";0"},
{"\"INCONG.\";1"},
{"\"APERTA\";2"},
{"\"CHIUSA\";3"},
{"\"MARCIA\";4"},
{"\"ARRESTO\";5"},
{"\"APERTE\";6"},
{"\"CHIUSE\";7"},
{"\"SPENTE\";8"},
{"\"ACCESE\";9"},
{"\"SPENTO\";10"},
{"\"ACCESO\";11"},
{"\"ASSENTE\";12"},
{"\"PRESENTE\";13"},
{"\"IN.SERV\";14"},
{"\"F..SERV.\";15"},
{"\"A.SELEZ.\";16"},
{"\"B.SELEZ.\";17"},
{"\"SPENTI\";18"},
{"\"ACCESI\";19"},
{"\"A\";20"},
{"\"B\";21"},
{"\"X\";22"},
{"\"F\";23"},
{"\"EROGAZ.\";24"},
{"\"STOCC.\";25"},
{"\"BLOCCO\";26"},
{"\"APERTO\";27"},
{"\"CHIUSO\";28"},
{"\"SBLOCCO\";29"},
{"\"ANOMALIA\";30"},
{"\"NORMALE\";31"},
{"\"MASSIMA\";32"},
{"\"MINIMA\";33"},
{"\"CHIUSURA\";34"},
{"\"APERTURA\";35"},
{"\"INTERMED\";36"},
{"\"RUNNING\";37"},
{"\"STOPPED\";38"},
{"\"OVERLOAD\";39"},
{"\"OPEN\";40"},
{"\"CLOSED\";41"},
{"\"OUT PROC\";42"},
{"\"IN PROC.\";43"},
{"\"OUT TOL.\";44"},
{"\"REACHED\";45"},
{"\"ALLARM\";46"},
{"\"ACTIVED\";47"},
{"\"SUSPEND\";48"},
{"\"END\";49"},
{";50"},
{";51"},
{";52"},
{";53"},
{";54"},
{";55"},
{";56"},
{";57"},
{";58"},
{";59"},
{";60"},
{";61"},
{";62"},
{";63"},
};

#define NUM_RECORD_EDITTDIZST sizeof(editTDIZST)/sizeof(STRUCT_TABLE_CAB)
#endif
