/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef h_editallarliv_h
#define h_editallarliv_h


STRUCT_TABLE editallarliv[]={
        {"Indice",          TIPO_INT,0,     "" },
        {"ColSev1",          TIPO_CHAR,0,     "" },
        {"ColSev2",          TIPO_CHAR,0,     "" },
        {"ColSev3",          TIPO_CHAR,0,     "" },
        {"Emissione",          TIPO_CHAR,0,     "" },
        {"Rientro",          TIPO_CHAR,0,     "" },
	};

#define NUM_CAMPI_EDITALLARLIV sizeof(editallarliv)/sizeof(STRUCT_TABLE)

#define DEF_ALLARLIV_COL	3
#define DEF_ALLARLIV_DES	9

typedef struct _DEF_ALLARLIV {
    int Indice;
    char ColSev1[DEF_ALLARLIV_COL];
    char ColSev2[DEF_ALLARLIV_COL];
    char ColSev3[DEF_ALLARLIV_COL];
    char Emissione[DEF_ALLARLIV_DES];
    char Rientro[DEF_ALLARLIV_DES];
} DEF_ALLARLIV;

DEF_ALLARLIV default_allarliv[]={
	{1,"RO","MA","GI","________","________"},
	{2,"BI","MA","GI","DIAGNOST","DIAGNOST"},
	{3,"RO","BI","VE","________","STRINGA_"},
	{4,"RO","BI","GI","________","COM.ESEG"},
	{5,"RO","MA","GI","NO_ALTMO","ALTIS.MO"},
	{6,"RO","MA","GI","NO_BASMO","BASSI.MO"},
	{7,"RO","MA","GI","NO_ALTO_","ALTO____"},
	{8,"RO","MA","GI","NO_BASSO","BASSO___"},
	{9,"RO","BI","VE","IN_SCANS","FORZATO_"},
	{10,"RO","BI","VE","ATTENDIB","INATTEND"},
	{11,"RO","BI","VE","IN_SCANS","NO_SCANS"},
	{12,"RO","BI","VE","NO_GR.VA","GRA.VAR."},
	{13,"RO","BI","VE","IN_SC_AL","SCALA_AL"},
	{14,"RO","BI","VE","IN_SC_BA","SCALA_BA"},
	{15,"RO","BI","VE","TRSDT.OK","TRSDT.KO"},
	{16,"RO","BI","VE","GI.FR.OK","GI.FR.KO"},
	{17,"VE","VE","VE","________","________"},
	{18,"RO","BI","VE","________","COMANDO_"},
	{19,"RO","BI","VE","________","ERR.CONF"},
	{20,"BI","MA","GI","________","________"},
	{21,"RO","BI","VE","________","VAR.ORG."},
	{22,"RO","BI","VE","________","COM.FALL"},
	{23,"RO","BI","VE","________","PRO.FALL"},
	{24,"RO","BI","VE","________","COM.OPER"},
	{25,"RO","BI","VE","________","COM.PROG"},
	{26,"RO","BI","VE","________","LI.ALTMO"},
	{27,"RO","BI","VE","________","LI.ALTO_"},
	{28,"RO","BI","VE","________","LI.BASMO"},
	{29,"RO","BI","VE","________","LI.BASSO"},
	{30,"RO","BI","VE","SIGNAL_A","NO_SIG_A"},
	{31,"RO","BI","VE","SIGNAL_B","NO_SIG_B"},
	{32,"RO","BI","VE","SIGNAL_C","NO_SIG_C"},
	{33,"RO","BI","VE","SIGNAL_D","NO_SIG_D"},
	{34,"RO","BI","VE","SIGNAL_E","NO_SIG_E"},
	{35,"RO","BI","VE","SIGNAL_F","NO_SIG_F"},
	{36,"RO","BI","VE","SIGNAL_G","NO_SIG_G"},
	{37,"RO","BI","VE","SIGNAL_H","NO_SIG_H"},
	{38,"RO","BI","VE","SIGNAL_I","NO_SIG_I"},
	{39,"RO","BI","VE","SIGNAL_J","NO_SIG_J"},
	{40,"RO","BI","VE","SIGNAL_K","NO_SIG_K"},
	{41,"RO","BI","VE","SIGNAL_L","NO_SIG_L"},
	{42,"RO","BI","VE","SIGNAL_M","NO_SIG_M"},
	{43,"RO","BI","VE","SIGNAL_N","NO_SIG_N"},
	{44,"RO","BI","VE","SIGNAL_O","NO_SIG_O"},
	{45,"RO","BI","VE","SIGNAL_P","NO_SIG_P"},
	{46,"RO","BI","VE","SIGNAL_Q","NO_SIG_Q"},
	{47,"RO","BI","VE","SIGNAL_R","NO_SIG_R"},
	{48,"RO","BI","VE","SIGNAL_S","NO_SIG_S"},
	{49,"RO","BI","VE","SIGNAL_T","NO_SIG_T"},
	{50,"RO","BI","VE","SIGNAL_U","NO_SIG_U"},
	{51,"RO","BI","VE","SIGNAL_V","NO_SIG_V"},
	{52,"RO","BI","VE","SIGNAL_W","NO_SIG_W"},
	{53,"RO","BI","VE","SIGNAL_X","NO_SIG_X"},
	{54,"RO","BI","VE","SIGNAL_Y","NO_SIG_Y"},
	{55,"RO","BI","VE","SIGNAL_Z","NO_SIG_Z"},
	};

#define NUM_CAMPI_DEFAULTALLARLIV sizeof(default_allarliv)/sizeof(DEF_ALLARLIV)

#endif
