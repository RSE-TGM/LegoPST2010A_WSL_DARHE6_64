/**********************************************************************
*
*       C Header:               XlAllarmi.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Mon Nov  2 17:26:37 1998 %
*
**********************************************************************/
/*
   modulo XlAllarmi.h
   tipo 
   release 5.1
   data 11/13/95
   reserved @(#)XlAllarmi.h	5.1
*/
/*
 * XlAllarmi.h - file di include pubblico per l'utilizzo del widget
 *             allarmi
 */
#ifndef _XlAllarmi_h
#define _XlAllarmi_h



/*
 nomi di risorse utilizzate internamente al allarmi
*/
#define XlNnormalFont "normalFont"
#define XlCNormalFont "NormalFont"
#define XlDnormalFont "Font"
#define XlNtitoloFont "titoloFont"
#define XlCTitoloFont "TitoloFont"
#define XlDtitoloFont "Font big"

#define XlNdatabaseAllarmi "databaseAllarmi"
#define XlCDatabaseAllarmi "DatabaseAllarmi"
#define XlDdatabaseAllarmi "Database allarmi n."

#define XlNtroughScrollBar "troughScrollBar"
#define XlCTroughScrollBar "TroughScrollBar"
#define XlDtroughScrollBar "Color of the slider trough"

#define XlOzona0_31 "No,Yes"
#define XlNzona0 "zona0"
#define XlCZona0 "Zona0"
#define XlDzona0 "Zona di impianto n. 0"
#define XlNzona1 "zona1"
#define XlCZona1 "Zona1"
#define XlDzona1 "Zona di impianto n. 1"
#define XlNzona2 "zona2"
#define XlCZona2 "Zona2"
#define XlDzona2 "Zona di impianto n. 2"
#define XlNzona3 "zona3"
#define XlCZona3 "Zona3"
#define XlDzona3 "Zona di impianto n. 3"
#define XlNzona4 "zona4"
#define XlCZona4 "Zona4"
#define XlDzona4 "Zona di impianto n. 4"
#define XlNzona5 "zona5"
#define XlCZona5 "Zona5"
#define XlDzona5 "Zona di impianto n. 5"
#define XlNzona6 "zona6"
#define XlCZona6 "Zona6"
#define XlDzona6 "Zona di impianto n. 6"
#define XlNzona7 "zona7"
#define XlCZona7 "Zona7"
#define XlDzona7 "Zona di impianto n. 7"
#define XlNzona8 "zona8"
#define XlCZona8 "Zona8"
#define XlDzona8 "Zona di impianto n. 8"
#define XlNzona9 "zona9"
#define XlCZona9 "Zona9"
#define XlDzona9 "Zona di impianto n. 9"
#define XlNzona10 "zona10"
#define XlCZona10 "Zona10"
#define XlDzona10 "Zona di impianto n. 10"
#define XlNzona11 "zona11"
#define XlCZona11 "Zona11"
#define XlDzona11 "Zona di impianto n. 11"
#define XlNzona12 "zona12"
#define XlCZona12 "Zona12"
#define XlDzona12 "Zona di impianto n. 12"
#define XlNzona13 "zona13"
#define XlCZona13 "Zona13"
#define XlDzona13 "Zona di impianto n. 13"
#define XlNzona14 "zona14"
#define XlCZona14 "Zona14"
#define XlDzona14 "Zona di impianto n. 14"
#define XlNzona15 "zona15"
#define XlCZona15 "Zona15"
#define XlDzona15 "Zona di impianto n. 15"
#define XlNzona16 "zona16"
#define XlCZona16 "Zona16"
#define XlDzona16 "Zona di impianto n. 16"
#define XlNzona17 "zona17"
#define XlCZona17 "Zona17"
#define XlDzona17 "Zona di impianto n. 17"
#define XlNzona18 "zona18"
#define XlCZona18 "Zona18"
#define XlDzona18 "Zona di impianto n. 18"
#define XlNzona19 "zona19"
#define XlCZona19 "Zona19"
#define XlDzona19 "Zona di impianto n. 19"
#define XlNzona20 "zona20"
#define XlCZona20 "Zona20"
#define XlDzona20 "Zona di impianto n. 20"
#define XlNzona21 "zona21"
#define XlCZona21 "Zona21"
#define XlDzona21 "Zona di impianto n. 21"
#define XlNzona22 "zona22"
#define XlCZona22 "Zona22"
#define XlDzona22 "Zona di impianto n. 22"
#define XlNzona23 "zona23"
#define XlCZona23 "Zona23"
#define XlDzona23 "Zona di impianto n. 23"
#define XlNzona24 "zona24"
#define XlCZona24 "Zona24"
#define XlDzona24 "Zona di impianto n. 24"
#define XlNzona25 "zona25"
#define XlCZona25 "Zona25"
#define XlDzona25 "Zona di impianto n. 25"
#define XlNzona26 "zona26"
#define XlCZona26 "Zona26"
#define XlDzona26 "Zona di impianto n. 26"
#define XlNzona27 "zona27"
#define XlCZona27 "Zona27"
#define XlDzona27 "Zona di impianto n. 27"
#define XlNzona28 "zona28"
#define XlCZona28 "Zona28"
#define XlDzona28 "Zona di impianto n. 28"
#define XlNzona29 "zona29"
#define XlCZona29 "Zona29"
#define XlDzona29 "Zona di impianto n. 29"
#define XlNzona30 "zona30"
#define XlCZona30 "Zona30"
#define XlDzona30 "Zona di impianto n. 20"
#define XlNzona31 "zona31"
#define XlCZona31 "Zona31"
#define XlDzona31 "Zona di impianto n. 31"


/*
	define e struture usate nell'oggetto
*/
#define NUMERO_ALLARMI_VIS      16
#define LUN_TESTO_ALLARMI       120
#define LUN_DATA_ALLARMI        12
#define NUMERO_ZONE		32
#define NUMERO_DATABASE_ALLARMI  4

struct dati_allarmi_st
        {
        int colore_astr;
	int blink_astr;
        int colore_testo;
	int blink_testo;
        char testo[LUN_TESTO_ALLARMI+1+LUN_DATA_ALLARMI+1];
        char data[LUN_DATA_ALLARMI+1];
        float valore;
        int esiste_valore;
        };

typedef struct dati_allarmi_st DATI_ALLARMI;

#define OFFSET_FORM_ESTERNA	6
#define HEIGHT_FORM_TASTI	100

typedef struct _s_xlallarmi {
	Widget  XLtop_allarmi;
        Widget  XLform_allarmi;
        Widget  XLform_tasti;
        Widget  XLform_tasto_riconosci;
        Widget  XLtasto_riconosci;
        Widget  XLseparatorGadget1;
        Widget  XLlabel_da;
        Widget  XLlabel_a;
        Widget  XLform_altri_tasti;
        Widget  XLtasto_archivio;
        Widget  XLtasto_cong;
        Widget  XLtasto_sing;
        Widget  XLseparatorGadget2;
        Widget  XLform_label;
        Widget  XLlabel_titolo;
        Widget  XLlabel1;
        Widget  XLlabel2;
        Widget  XLform_testo;
        Widget  XLscrollBar_allarmi;
        Widget  XLseparatorGadget3;
        Widget  XLscrolledWindow_allarmi;
        Widget  XLform_testi_allarmi;
        Widget  XLlabel_titoli;
        Widget  XLtesto_1;
        Widget  XLtesto_2;
        Widget  XLtesto_3;
        Widget  XLtesto_4;
        Widget  XLtesto_5;
        Widget  XLtesto_6;
        Widget  XLtesto_7;
        Widget  XLtesto_8;
        Widget  XLtesto_9;
        Widget  XLtesto_10;
        Widget  XLtesto_11;
        Widget  XLtesto_12;
        Widget  XLtesto_13;
        Widget  XLtesto_14;
        Widget  XLtesto_15;
        Widget  XLtesto_16;
        Widget  XLseparatorGadget4;
        Widget  XLvalore_1;
        Widget  XLvalore_2;
        Widget  XLvalore_3;
        Widget  XLvalore_4;
        Widget  XLvalore_5;
        Widget  XLvalore_6;
        Widget  XLvalore_7;
        Widget  XLvalore_8;
        Widget  XLvalore_9;
        Widget  XLvalore_10;
        Widget  XLvalore_11;
        Widget  XLvalore_12;
        Widget  XLvalore_13;
        Widget  XLvalore_14;
        Widget  XLvalore_15;
        Widget  XLvalore_16;
        Widget  XLtoggle_1;
        Widget  XLtoggle_2;
        Widget  XLtoggle_3;
        Widget  XLtoggle_4;
        Widget  XLtoggle_5;
        Widget  XLtoggle_6;
        Widget  XLtoggle_7;
        Widget  XLtoggle_8;
        Widget  XLtoggle_9;
        Widget  XLtoggle_10;
        Widget  XLtoggle_11;
        Widget  XLtoggle_12;
        Widget  XLtoggle_13;
        Widget  XLtoggle_14;
        Widget  XLtoggle_15;
        Widget  XLtoggle_16;
        Widget  XLled_1;
        Widget  XLled_2;
        Widget  XLled_3;
        Widget  XLled_4;
        Widget  XLled_5;
        Widget  XLled_6;
        Widget  XLled_7;
        Widget  XLled_8;
        Widget  XLled_9;
        Widget  XLled_10;
        Widget  XLled_11;
        Widget  XLled_12;
        Widget  XLled_13;
        Widget  XLled_14;
        Widget  XLled_15;
        Widget  XLled_16;
        int     XLmodo;
        int     XLmodo_cong;
        int     XLdb_allarmi;
        int     XLcodiceAll;
        int     XLall_da;
        int     XLall_a;
        int     XLall_da_ric;
        int     XLall_in_arch;
        DATI_ALLARMI    XLdati_allarmi[16];
	int     XLzone_impianto[NUMERO_ZONE];
        Pixel   XLpix_all[8];
	Pixel   XLbackground_allarmi;
	Pixel   XLforeground_allarmi;
	Pixel   XLtrough_allarmi;
        Pixmap  XLpixmap_all[8];
	Pixmap  XLpixmap_spento;
	XmFontList XLfont_normale;
	XmFontList XLfont_titolo;
	Dimension XLh_font_normale;
	Dimension XLw_font_normale;
	Dimension XLh_font_titolo;
	Dimension XLw_font_titolo;
	Dimension XLform_width;
	Dimension XLform_height;
	Dimension XLlabel_height;
	Dimension XLw_form_ric;
	Dimension XLw_form_arch;
	OlDatabasePuntiObject XLdatabasePunti;
} S_XLALLARMI;


#define top_allarmi		pXlAllarmi->XLtop_allarmi
#define form_allarmi		pXlAllarmi->XLform_allarmi
#define form_tasti		pXlAllarmi->XLform_tasti
#define form_tasto_riconosci		pXlAllarmi->XLform_tasto_riconosci
#define tasto_riconosci		pXlAllarmi->XLtasto_riconosci
#define separatorGadget1		pXlAllarmi->XLseparatorGadget1
#define label_da		pXlAllarmi->XLlabel_da
#define label_a		pXlAllarmi->XLlabel_a
#define form_altri_tasti		pXlAllarmi->XLform_altri_tasti
#define tasto_archivio		pXlAllarmi->XLtasto_archivio
#define tasto_cong		pXlAllarmi->XLtasto_cong
#define tasto_sing		pXlAllarmi->XLtasto_sing
#define separatorGadget2		pXlAllarmi->XLseparatorGadget2
#define form_label		pXlAllarmi->XLform_label
#define label_titolo		pXlAllarmi->XLlabel_titolo
#define label1		pXlAllarmi->XLlabel1
#define label2		pXlAllarmi->XLlabel2
#define form_testo		pXlAllarmi->XLform_testo
#define scrollBar_allarmi		pXlAllarmi->XLscrollBar_allarmi
#define separatorGadget3		pXlAllarmi->XLseparatorGadget3
#define scrolledWindow_allarmi		pXlAllarmi->XLscrolledWindow_allarmi
#define form_testi_allarmi		pXlAllarmi->XLform_testi_allarmi
#define label_titoli		pXlAllarmi->XLlabel_titoli
#define testo_1		pXlAllarmi->XLtesto_1
#define testo_2		pXlAllarmi->XLtesto_2
#define testo_3		pXlAllarmi->XLtesto_3
#define testo_4		pXlAllarmi->XLtesto_4
#define testo_5		pXlAllarmi->XLtesto_5
#define testo_6		pXlAllarmi->XLtesto_6
#define testo_7		pXlAllarmi->XLtesto_7
#define testo_8		pXlAllarmi->XLtesto_8
#define testo_9		pXlAllarmi->XLtesto_9
#define testo_10		pXlAllarmi->XLtesto_10
#define testo_11		pXlAllarmi->XLtesto_11
#define testo_12		pXlAllarmi->XLtesto_12
#define testo_13		pXlAllarmi->XLtesto_13
#define testo_14		pXlAllarmi->XLtesto_14
#define testo_15		pXlAllarmi->XLtesto_15
#define testo_16		pXlAllarmi->XLtesto_16
#define separatorGadget4		pXlAllarmi->XLseparatorGadget4
#define valore_1		pXlAllarmi->XLvalore_1
#define valore_2		pXlAllarmi->XLvalore_2
#define valore_3		pXlAllarmi->XLvalore_3
#define valore_4		pXlAllarmi->XLvalore_4
#define valore_5		pXlAllarmi->XLvalore_5
#define valore_6		pXlAllarmi->XLvalore_6
#define valore_7		pXlAllarmi->XLvalore_7
#define valore_8		pXlAllarmi->XLvalore_8
#define valore_9		pXlAllarmi->XLvalore_9
#define valore_10		pXlAllarmi->XLvalore_10
#define valore_11		pXlAllarmi->XLvalore_11
#define valore_12		pXlAllarmi->XLvalore_12
#define valore_13		pXlAllarmi->XLvalore_13
#define valore_14		pXlAllarmi->XLvalore_14
#define valore_15		pXlAllarmi->XLvalore_15
#define valore_16		pXlAllarmi->XLvalore_16
#define toggle_1		pXlAllarmi->XLtoggle_1
#define toggle_2		pXlAllarmi->XLtoggle_2
#define toggle_3		pXlAllarmi->XLtoggle_3
#define toggle_4		pXlAllarmi->XLtoggle_4
#define toggle_5		pXlAllarmi->XLtoggle_5
#define toggle_6		pXlAllarmi->XLtoggle_6
#define toggle_7		pXlAllarmi->XLtoggle_7
#define toggle_8		pXlAllarmi->XLtoggle_8
#define toggle_9		pXlAllarmi->XLtoggle_9
#define toggle_10		pXlAllarmi->XLtoggle_10
#define toggle_11		pXlAllarmi->XLtoggle_11
#define toggle_12		pXlAllarmi->XLtoggle_12
#define toggle_13		pXlAllarmi->XLtoggle_13
#define toggle_14		pXlAllarmi->XLtoggle_14
#define toggle_15		pXlAllarmi->XLtoggle_15
#define toggle_16		pXlAllarmi->XLtoggle_16
#define led_1		pXlAllarmi->XLled_1
#define led_2		pXlAllarmi->XLled_2
#define led_3		pXlAllarmi->XLled_3
#define led_4		pXlAllarmi->XLled_4
#define led_5		pXlAllarmi->XLled_5
#define led_6		pXlAllarmi->XLled_6
#define led_7		pXlAllarmi->XLled_7
#define led_8		pXlAllarmi->XLled_8
#define led_9		pXlAllarmi->XLled_9
#define led_10		pXlAllarmi->XLled_10
#define led_11		pXlAllarmi->XLled_11
#define led_12		pXlAllarmi->XLled_12
#define led_13		pXlAllarmi->XLled_13
#define led_14		pXlAllarmi->XLled_14
#define led_15		pXlAllarmi->XLled_15
#define led_16		pXlAllarmi->XLled_16
#define modo		pXlAllarmi->XLmodo
#define modo_cong		pXlAllarmi->XLmodo_cong
#define db_allarmi		pXlAllarmi->XLdb_allarmi
#define codiceAll		pXlAllarmi->XLcodiceAll
#define all_da		pXlAllarmi->XLall_da
#define all_a		pXlAllarmi->XLall_a
#define all_da_ric		pXlAllarmi->XLall_da_ric
#define all_in_arch		pXlAllarmi->XLall_in_arch
#define dati_allarmi		pXlAllarmi->XLdati_allarmi
#define zone_impianto		pXlAllarmi->XLzone_impianto
#define pix_all		pXlAllarmi->XLpix_all
#define pixmap_all		pXlAllarmi->XLpixmap_all
#define pixmap_spento		pXlAllarmi->XLpixmap_spento
#define background_allarmi		pXlAllarmi->XLbackground_allarmi
#define foreground_allarmi		pXlAllarmi->XLforeground_allarmi
#define trough_allarmi          pXlAllarmi->XLtrough_allarmi
#define font_normale		pXlAllarmi->XLfont_normale
#define font_titolo		pXlAllarmi->XLfont_titolo
#define h_font_normale		pXlAllarmi->XLh_font_normale
#define w_font_normale		pXlAllarmi->XLw_font_normale
#define h_font_titolo		pXlAllarmi->XLh_font_titolo
#define w_font_titolo		pXlAllarmi->XLw_font_titolo
#define form_width		pXlAllarmi->XLform_width
#define form_height		pXlAllarmi->XLform_height
#define label_height		pXlAllarmi->XLlabel_height
#define w_form_ric		pXlAllarmi->XLw_form_ric
#define w_form_arch		pXlAllarmi->XLw_form_arch
#define databasePunti		pXlAllarmi->XLdatabasePunti


/*  Dichiarazione del tipo per la lettura dal context degli oggetti il
        puntatore alla struttura delle variabili globali  */
typedef struct
        {
        S_XLALLARMI *UxPXlAllarmi;
        }FALSO_CTX_ALLARMI;


static char * tabella_colori_allarmi[8]=
        {"black","red","green","yellow","blue","magenta","turquoise","white"};

/* declare the class constant */
extern WidgetClass xlAllarmiWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Allarmi */
typedef struct _XlAllarmiClassRec *XlAllarmiWidgetClass;
typedef struct _XlAllarmiRec *XlAllarmiWidget;

/*
Prototype Metodo richiamabile da esterno
*/
int XlAllarmiGetDb(Widget w);
#endif /* _XlAllarmi_h */

