/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

#define l_Descrizione	80
#define l_CodiceFile	80

typedef struct _VOCI_ALLARME {
    int Indice;
    char Descrizione[l_Descrizione];
    char CodiceFile[l_CodiceFile];
} VOCI_ALLARME;


#define NUMERO_VOCI_ALLARME	55

static VOCI_ALLARME voci_allarme[] = {
	{1,"Allarme_Digitale","allarme_digitale"},
	{2,"Allarme_Diagnostica","allarme_diagnostica"},
	{3,"Modifica_Stringa","modifica_stringa"},
	{4,"Comando_OK","comando_ok"},
	{5,"Sicurezza_Alta","sicurezza_alta"},
	{6,"Sicurezza_Bassa","sicurezza_bassa"},
	{7,"Conduzione_Alta","conduzione_alta"},
	{8,"Conduzione_Bassa","conduzione_bassa"},
	{9,"spare","spare"},
	{10,"Punto_non_Attendibile","punto_non_attendibile"},
	{11,"Punto_Fuori_Scansione","punto_fuori_scansione"},
	{12,"Grande_Variazione","grande_variazione"},
	{13,"Fuori_Range_Alto","fuori_range_alto"},
	{14,"Fuori_Range_Basso","fuori_range_basso"},
	{15,"Canale_Fuori_Servizio","canale_fuori_servizio"},
	{16,"Giunto_Freddo","giunto_freddo"},
	{17,"Misura_Normale","misura_normale"},
	{18,"Invio_Comando","invio_comando"},
	{19,"Non_Esiste","non_esi"},
	{20,"ADPERARCHIVI","ADPERARCHIVI"},
	{21,"Organo_Variato","organo_variato"},
	{22,"Comando_Fallito","comando_fallito"},
	{23,"Protezione_Fallita","protezione_fallita"},
	{24,"spare","spare"},
	{25,"spare","spare"},
	{26,"Modifica_Limite_Alto_Sicurezza","modifica_hs"},
	{27,"Modifica_Limite_Alto_Conduzione","modifica_hc"},
	{28,"Modifica_Limite_Basso_Sicurezza","modifica_ls"},
	{29,"Modifica_Limite_Basso_Conduzione","modifica_lc"},
	{30,"Segnale_Tipo_A","segnale_tipo_A"},
	{31,"Segnale_Tipo_B","segnale_tipo_B"},
	{32,"Segnale_Tipo_C","segnale_tipo_C"},
	{33,"Segnale_Tipo_D","segnale_tipo_D"},
	{34,"Segnale_Tipo_E","segnale_tipo_E"},
	{35,"Segnale_Tipo_F","segnale_tipo_F"},
	{36,"Segnale_Tipo_G","segnale_tipo_G"},
	{37,"Segnale_Tipo_H","segnale_tipo_H"},
	{38,"Segnale_Tipo_I","segnale_tipo_I"},
	{39,"Segnale_Tipo_J","segnale_tipo_J"},
	{40,"Segnale_Tipo_K","segnale_tipo_K"},
	{41,"Segnale_Tipo_L","segnale_tipo_L"},
	{42,"Segnale_Tipo_M","segnale_tipo_M"},
	{43,"Segnale_Tipo_N","segnale_tipo_N"},
	{44,"Segnale_Tipo_O","segnale_tipo_O"},
	{45,"Segnale_Tipo_P","segnale_tipo_P"},
	{46,"Segnale_Tipo_Q","segnale_tipo_Q"},
	{47,"Segnale_Tipo_R","segnale_tipo_R"},
	{48,"Segnale_Tipo_S","segnale_tipo_S"},
	{49,"Segnale_Tipo_T","segnale_tipo_T"},
	{50,"Segnale_Tipo_U","segnale_tipo_U"},
	{51,"Segnale_Tipo_V","segnale_tipo_V"},
	{52,"Segnale_Tipo_W","segnale_tipo_W"},
	{53,"Segnale_Tipo_X","segnale_tipo_X"},
	{54,"Segnale_Tipo_Y","segnale_tipo_Y"},
	{55,"Segnale_Tipo_Z","segnale_tipo_Z"}
};
