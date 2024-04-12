/**********************************************************************
*
*       C Header:               XlGrafico.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Mon Dec 14 10:56:56 1998 %
*
**********************************************************************/
/*
   modulo XlGrafico.h
   tipo 
   release 5.2
   data 11/13/95
   reserved @(#)XlGrafico.h	5.2
*/
/*
 * XlGrafico.h - file di include pubblico per l'utilizzo del widget
 *		   Grafico
 */
#ifndef _XlGrafico_h
#define _XlGrafico_h

#ifndef VMS
#include <Xl/SourceGrafica/grsf22.h>
#include <Xl/SourceGrafica/grafics.h>
#else
#include <SourceGrafica/grsf22.h>
#include <SourceGrafica/grafics.h>
#endif
#include <uni_mis.h>

#define MAX_WIDGETS    87
#define NUM_BOOLEAN_MIS  4
#define NUM_BOOLEAN_ZOOM 5
#define NUM_BOOLEAN_UMIS 4
#define NUM_BOOLEAN_FSCA 2
#define NUM_BOOLEAN_DIR  4

#define RISO 100.0  /* risoluzione ascisse in frazioni di secondo */
#define ZOOM_END  0  /* fine modalita' di definizione rettangolo */
#define ZOOM_WAIT 1  /* in attesa del primo click del mouse */
#define ZOOM_DRAG 2  /* fase di definizione rettangolo tramite
                         dragging del mouse */

#define MAX_LEN_BUFDATI  4*60*60 

/*
 nomi di risorse utilizzate internamente al grafico
 */

#define XlNgraficoType       "graficoType"
#define XlCGraficoType       "GraficoType"
#define XlDgraficoType       "Grafic Type"
#define XlOgraficoType       "Archive variables,Circular archive variables,RunTime variables (4 Var),RunTime variable (1 Var)"
#define XlNcolorTrend1	     "colorTrend1"
#define XlCColorTrend1	     "ColorTrend1"
#define XlDcolorTrend1	     "First color trend"
#define XlNcolorTrend2	     "colorTrend2"
#define XlCColorTrend2	     "ColorTrend2"
#define XlDcolorTrend2	     "Second color trend"
#define XlNcolorTrend3	     "colorTrend3"
#define XlCColorTrend3	     "ColorTrend3"
#define XlDcolorTrend3	     "Third color trend"
#define XlNcolorTrend4	     "colorTrend4"
#define XlCColorTrend4	     "ColorTrend4"
#define XlDcolorTrend4	     "Fourth color trend"
#define XlNcolorGrid	     "colorGrid"
#define XlCColorGrid	     "ColorGrid"
#define XlDcolorGrid	     "Grid Color"
#define XlNarchiveFile	     "archiveFile"
#define XlCArchiveFile	     "ArchiveFile"
#define XlDarchiveFile	     "Path and archive file name (f22)"
#define XlNvarName1	     "varName1"
#define XlCVarName1	     "VarName1"
#define XlDvarName1	     "First variable name"
#define XlNvarName2          "varName2"
#define XlCVarName2          "VarName2"
#define XlDvarName2          "Second variable name"
#define XlNvarName3          "varName3"
#define XlCVarName3          "VarName3"
#define XlDvarName3          "Third variable name"
#define XlNvarName4          "varName4"
#define XlCVarName4          "VarName4"
#define XlDvarName4          "Fourth variable name"
#define XlNvarDescr1	     "varDescr1"
#define XlCVarDescr1	     "VarDescr1"
#define XlDvarDescr1	     "First variable description"
#define XlNvarDescr2	     "varDescr2"
#define XlCVarDescr2	     "VarDescr2"
#define XlDvarDescr2	     "Second variable description"
#define XlNvarDescr3	     "varDescr3"
#define XlCVarDescr3	     "VarDescr3"
#define XlDvarDescr3	     "Third variable description"
#define XlNvarDescr4	     "varDescr4"
#define XlCVarDescr4	     "VarDescr4"
#define XlDvarDescr4	     "Fourth variable description"
#define XlNdeltaTime	     "deltaTime"
#define XlCDeltaTime	     "DeltaTime"
#define XlDdeltaTime	     "Run Time: repr. time interval(sec.)"
#define XlNmaxSamples	     "maxSamples"
#define XlCMaxSamples	     "MaxSamples"
#define XlDmaxSamples	     "Archives: max no. of samples"
#define XlNgraphTitle	     "graphTitle"
#define XlCGraphTitle	     "GraphTitle"
#define XlDgraphTitle	     "Graphic title label"
#define XlNautoScaling1	     "autoScaling1"
#define XlCAutoScaling1	     "AutoScaling1"
#define XlDautoScaling1	     "Autoscaling first variable"
#define XlOautoScaling1	     "No,Yes"
#define XlNmaxVal1	     "maxVal1"
#define XlCMaxVal1	     "MaxVal1"
#define XlDmaxVal1	     "First variable max scale value"
#define XlNminVal1	     "minVal1"
#define XlCMinVal1	     "MinVal1"
#define XlDminVal1	     "First variable min scale value"
#define XlNautoScaling2	     "autoScaling2"
#define XlCAutoScaling2	     "AutoScaling2"
#define XlDautoScaling2	     "Autoscaling second variable"
#define XlOautoScaling2	     "No,Yes"
#define XlNmaxVal2	     "maxVal2"
#define XlCMaxVal2	     "MaxVal2"
#define XlDmaxVal2	     "Second variable max scale value"
#define XlNminVal2	     "minVal2"
#define XlCMinVal2	     "MinVal2"
#define XlDminVal2	     "Second variable min scale value"
#define XlNautoScaling3	     "autoScaling3"
#define XlCAutoScaling3	     "AutoScaling3"
#define XlDautoScaling3	     "Autoscaling third variable"
#define XlOautoScaling3	     "No,Yes"
#define XlNmaxVal3	     "maxVal3"
#define XlCMaxVal3	     "MaxVal3"
#define XlDmaxVal3	     "Third variable max scale value"
#define XlNminVal3	     "minVal3"
#define XlCMinVal3	     "MinVal3"
#define XlDminVal3	     "Third variable min scale value"
#define XlNautoScaling4	     "autoScaling4"
#define XlCAutoScaling4	     "AutoScaling4"
#define XlDautoScaling4	     "Autoscaling fourth variable"
#define XlOautoScaling4	     "No,Yes"
#define XlNmaxVal4	     "maxVal4"
#define XlCMaxVal4	     "MaxVal4"
#define XlDmaxVal4	     "Fourth variable max scale value"
#define XlNminVal4	     "minVal4"
#define XlCMinVal4	     "MinVal4"
#define XlDminVal4	     "Fourth variable min scale value"
#define XlNfirstRefresh	     "firstRefresh"
#define XlCFirstRefresh	     "FirstRefresh"

#define ARCH_GRAF	0  /* Grafico che legge da file f22 */
#define ARCH_CIRC_GRAF	1  /* Grafico che legge da file f22circ.dat */
#define RUN_GRAF	2  /* Grafico che legge da memoria su 4 variabili */
#define PLOT_GRAF	3  /* Grafico che legga da memoria su una variabile */

/* declare the class constant */
extern WidgetClass xlGraficoWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di Grafico */
typedef struct _XlGraficoClassRec *XlGraficoWidgetClass;
typedef struct _XlGraficoRec *XlGraficoWidget;

/*
 definizione della struttura che contiene le variabili di stato
 del grafico: erano in origine le variabili in common della grafics
*/
typedef struct _s_xlgrafico {
	int	      XLtipo_graf;	/*  Variabile per identificazione
					    del tipo di grafico:
					    ARCH_GRAF;
					    ARCH_CIRC_GRAF;
					    RUN_GRAF;
					    PLOT_GRAF;    */
        /*
          variabili di stato (privato)
        */
        /*
        1. variabili di stato
           relative a oggetti motif usati internamente
        */
        Widget        XLtoplevel_widget;            /* Root widget ID of the
                                                       application. */
        Widget        XLmain_window_widget;         /* Root widget ID of main
                                                       MRM fetch */
        Widget        XLwidget_array[MAX_WIDGETS];  /* Place to keep all other
                                                       widget IDs */
        Widget        XLwcollima;    /* IDs di bottoni che cambiano label
                                        durante l'applicazione */
        Widget        XLwzoomord;
        Widget        XLwtempo_sec;

        XmString      XLx_collima_on;  /* compound strings utilizzate per
                                          le etichette */
        XmString      XLx_zoomord_on;
        XmString      XLx_secondi_on;
        XmString      XLx_collima_off;
        XmString      XLx_zoomord_off;
	XmString      XLx_secondi_off;

        /*
         2. variabili di stato
            variabili dipendenti dallo stato corrente dell'oggetto
            (stato dei toggle buttons stato dei grafici)
        */

        /* a) stato dei toggle buttons   */

        char          XLtoggle_mis[NUM_BOOLEAN_MIS];
        char          XLtoggle_zoom[NUM_BOOLEAN_ZOOM];
        char          XLtoggle_umis[NUM_BOOLEAN_UMIS];
        char          XLtoggle3_mis[NUM_BOOLEAN_MIS];
        char          XLtoggle_fsca[NUM_BOOLEAN_FSCA];
        char          XLtoggle2_umis[NUM_BOOLEAN_UMIS];
        char          XLtoggle_dir[NUM_BOOLEAN_DIR];


        /* b) stato dei grafici             */

        int           XLresize;
        int           XLnofile;          /* indica che non e' stato ancora
                                            selezionato il file
                                            dati ( N.B. era settato a 1 ) */
        int           XLscala_unica;     /* flag che indica che si desidera
                                            una unica scala
                                            per le variabili   */
        float         XLt_ultimo;        /* tempo trascorso dall'inizio della
                                            simulazione */
        float         XLt_old;           /* ultimo tempo letto */
        int           XLHC_on;

        int           XLvar_attiva;      /* variabile su cui si sta operando */
        int           XLindice_gruppo;   /* indice gruppo che si sta 
                                            selezionando */
        int           XLindice_umis;     /* indice unita' di misura che si sta
                                            selezionando */
        int           XLapp_umis_sel[4]; /* memorizzazione di appoggio durante
                                            la scelta delle unita' di misura */
        int           *XLumis_defsel;
        int           XLautoscalingG[4]; /* mem. di appoggio per i valori di
                                            fondo scala */
        char          *XLapp_min[4];     /* stringhe di appoggio per settaggio
                                            minimi e massimi */
        char          *XLapp_max[4];

	/*
	 * Struttura che definisce lo stato di ogni grafico presente
	 */

        S_GRAFICO     XLsg;

	/*
	 * Dati globali necessari per le routines di grafica
	 */

        int           XLscreen_num;
        Display       *XLDisplay;
	XtAppContext  XLAppContext;
	Widget        XLTopLevel;
        XtIntervalId  XLtimer;        /* ID del timer utilizzato per la 
			                 temporizzazione del refresh grafici */
        GC            XLgc[4];        /* e' presente un GC per ogni misura 
                                         all'interno del singolo gruppo */
        GC            XLgc2[4];       /* GC per hard copy in b/n */
        GC            XLgc_grid1;     /* GC per disegno griglia */
        GC            XLgc_grid2;
        GC            XLgc_zoom;
        XFontStruct   *XLfont_info_gr;
        float         XLtz_iniziale;
        float         XLtz_finale;
        Dimension     XLfont_height;
        Dimension     XLfont_width;
        Dimension     XLdraw_width;
        Dimension     XLdraw_height;  /* dimensionamento aree di disegno
                                         grafici */
        Dimension     XLord_height;
        float         XLpix_step;     /* step in pixels tra un campione ed
			                 il successivo */
	/*
	 * variabili per la gestione di zoom e collimazione
	 */

        int           XLfreeza;
        int           XLstato_zoom;
        int           XLiniz_rect;  /* indica il primo disegno del rettangolo */

	/*
	  origine e dimensioni del rettangolo di selezione per zoom
	*/

        XPoint        XLorigine;
        Dimension     XLwidthGraf;
	Dimension     XLheightGraf;


        Cursor        XLcursor_coll; /* cursore per collimazione */
        Cursor        XLcursor_zoom; /* cursore per zoom  */
        Cursor        XLcursor_wait; /* cursore per attesa */
        int           XLcollima;
        int           XLzoomord;
        int           XLtempo_sec;   /* indica se si vogliono i tempi
                                        sull'asse delle ascisse in secondi */
        int           XLx_collima;

	/*
	 * Dati per bufferizzazione valori per disegno grafici
	 */

        float         XLt_iniziale;
        float         XLt_finale;
	float 	      XLt_corrente;
        S_DATI        XLdato;
	Boolean	      XLnotify_overflow;		/* variabile per
							   identificazione della
							   notifica dell'overflow
							   di bufdati  */
        S_SEL_DATI    *XLbufdati;
	S_SEL_DATI    *XLbufdati_zoom;
        int 	      XLn_elementi_bufdati;
        int           XLn_last;                         /* posizione all'interno
                                                           del buffer del 
                                                           prossimo */
        float         XLt_restore;                      /* istante di tempo in cui si
                                                           interrompe la sessione di 
                                                           simulazione per caricare un
                                                           backtrack o attivare il
                                                           replay.                  */ 
        XPoint        XLz_ini;
	XPoint        XLz_fin;
        XPoint        *XLpoints[4];                     /* vettore contenente
                                                           le coordinate
                                                           in pixel del grafico
                                                           visualizzato */
        int           XLnpp[4];

	/*
	 * dati per selezione variabili
	 * QUESTA SEZIONE DOVRA' ESSERE MODIFICATA
	 */

        XmString      *XLx_simboli;
        XmString      *XLx_nomi_misure;
        XmString      XLx_sel_var[4];

        S_HEAD1       XLheader1;
        S_HEAD2       XLheader2;
        char          XLdescr_vuota[LUN_SIMB+1];
        char          **XLsimboli;                          /* tabella dei 
                                                               simboli (viene
                                                               allocata
                                                               dinamicamente) */
	/* per selezione gruppi */

        char          XLlista_gruppi[NUM_GRUPPI][LUN_SIMB+1];
        XmString      XLx_gruppi[NUM_GRUPPI+1];
        REC_GRUPPO    XLgruppi[NUM_GRUPPI];

	/* per selezione defaults delle unita' di misura */

        XmString      *XLx_codumis;  /* codici delle unita' di misura */

	/* per ridisegno ascisse    */
	char 	      XLstr_tim[7][20];
	char 	      XLstr_tims[7][20];

	/* per ridisegno nome file visualizzato  */
	char  	      XLfile_vis[150];

	/* Path e nome file visualizzato  */
	char 	      *XLpath_22dat;
	char 	      XLpath[NUM_PATH_FILES][LUN_PATH_FILES];
	FILE 	      *XLfpDAT;
	FILE 	      *XLfpGR;
	int 	      XLinizio_dati;
	fpos_t 	      XLposizione_iniziale;
	int 	      XLfine_dati;          /* posizione ultimo dato */
	char 	      XLpath_name[101];
	float         XLtsec;               /* tempo in secondi da memorizzare
					       nel buffer dati; viene 
					       incrementato di INC_SEC secondi
					       per ogni dato che viene inserito
					       nel buffer */
	int           XLoff_f22;
	int           XLlun_rec_dati;       /* lunghezza record dati */
	int           XLlun_parziale;       /* lunghezza lettura parziale dati*/
	int           XLnum_complete;       /* numero di letture complete */
	int           XLb_wait;             /* segnala che e' stato settato
                                               il cursore di wait */
	FILE          *XLfpPATH;

	} S_XLGRAFICO;

#define tipo_graf		pXlGraf->XLtipo_graf
#define toplevel_widget 	pXlGraf->XLtoplevel_widget      
#define main_window_widget    	pXlGraf->XLmain_window_widget  
#define widget_array       	pXlGraf->XLwidget_array
#define wcollima       		pXlGraf->XLwcollima  
#define wzoomord       		pXlGraf->XLwzoomord
#define wtempo_sec       	pXlGraf->XLwtempo_sec

#define x_collima_on       	pXlGraf->XLx_collima_on 
#define x_zoomord_on       	pXlGraf->XLx_zoomord_on
#define x_secondi_on       	pXlGraf->XLx_secondi_on
#define x_collima_off       	pXlGraf->XLx_collima_off
#define x_zoomord_off       	pXlGraf->XLx_zoomord_off
#define x_secondi_off       	pXlGraf->XLx_secondi_off

#define toggle_mis       	pXlGraf->XLtoggle_mis
#define toggle_zoom       	pXlGraf->XLtoggle_zoom
#define toggle_umis       	pXlGraf->XLtoggle_umis
#define toggle3_mis       	pXlGraf->XLtoggle3_mis
#define toggle_fsca       	pXlGraf->XLtoggle_fsca
#define toggle2_umis       	pXlGraf->XLtoggle2_umis
#define toggle_dir       	pXlGraf->XLtoggle_dir

#define resize                  pXlGraf->XLresize
#define nofile                  pXlGraf->XLnofile 
#define scala_unica             pXlGraf->XLscala_unica
#define t_ultimo                pXlGraf->XLt_ultimo
#define t_old                   pXlGraf->XLt_old 
#define HC_on                   pXlGraf->XLHC_on

#define var_attiva              pXlGraf->XLvar_attiva
#define indice_gruppo           pXlGraf->XLindice_gruppo
#define indice_umis             pXlGraf->XLindice_umis
#define app_umis_sel            pXlGraf->XLapp_umis_sel
#define umis_defsel             pXlGraf->XLumis_defsel
#define autoscalingG            pXlGraf->XLautoscalingG
#define app_min                 pXlGraf->XLapp_min
#define app_max                 pXlGraf->XLapp_max

#define sg                      pXlGraf->XLsg

#define screen_num              pXlGraf->XLscreen_num
#define display_set             pXlGraf->XLDisplay
#define appContext_set          pXlGraf->XLAppContext
#define topLevel_set            pXlGraf->XLTopLevel
#define timer                   pXlGraf->XLtimer

#define gc                      pXlGraf->XLgc

#define gc2                     pXlGraf->XLgc2
#define gc_grid1                pXlGraf->XLgc_grid1
#define gc_grid2                pXlGraf->XLgc_grid2
#define gc_zoom                 pXlGraf->XLgc_zoom
#define font_info_gr            pXlGraf->XLfont_info_gr
#define tz_iniziale             pXlGraf->XLtz_iniziale
#define tz_finale               pXlGraf->XLtz_finale

#define font_height             pXlGraf->XLfont_height
#define font_width              pXlGraf->XLfont_width
#define draw_width              pXlGraf->XLdraw_width
#define draw_height             pXlGraf->XLdraw_height

#define ord_height              pXlGraf->XLord_height
#define pix_step                pXlGraf->XLpix_step

#define freeza                  pXlGraf->XLfreeza
#define stato_zoom              pXlGraf->XLstato_zoom
#define iniz_rect               pXlGraf->XLiniz_rect

#define origine                 pXlGraf->XLorigine
#define widthGraf               pXlGraf->XLwidthGraf
#define heightGraf              pXlGraf->XLheightGraf

#define cursor_coll             pXlGraf->XLcursor_coll
#define cursor_zoom             pXlGraf->XLcursor_zoom
#define cursor_wait             pXlGraf->XLcursor_wait
#define collima                 pXlGraf->XLcollima
#define zoomord                 pXlGraf->XLzoomord
#define tempo_sec               pXlGraf->XLtempo_sec

#define x_collima               pXlGraf->XLx_collima

#define t_iniziale              pXlGraf->XLt_iniziale
#define t_finale                pXlGraf->XLt_finale
#define t_corrente		pXlGraf->XLt_corrente
#define dato                    pXlGraf->XLdato
#define notify_overflow		pXlGraf->XLnotify_overflow
#define bufdati                 pXlGraf->XLbufdati
#define bufdati_zoom		pXlGraf->XLbufdati_zoom
#define n_elementi_bufdati	pXlGraf->XLn_elementi_bufdati
#define n_last                  pXlGraf->XLn_last
#define t_restore		pXlGraf->XLt_restore
#define z_ini                   pXlGraf->XLz_ini
#define z_fin                   pXlGraf->XLz_fin
#define points                  pXlGraf->XLpoints

#define npp                     pXlGraf->XLnpp
#define x_simboli               pXlGraf->XLx_simboli
#define x_nomi_misure           pXlGraf->XLx_nomi_misure
#define x_sel_var               pXlGraf->XLx_sel_var

#define header1                 pXlGraf->XLheader1
#define header2                 pXlGraf->XLheader2

#define descr_vuota             pXlGraf->XLdescr_vuota
#define simboli                 pXlGraf->XLsimboli

#define lista_gruppi            pXlGraf->XLlista_gruppi
#define x_gruppi                pXlGraf->XLx_gruppi
#define gruppi                  pXlGraf->XLgruppi

#define x_codumis               pXlGraf->XLx_codumis

#define str_tim			pXlGraf->XLstr_tim
#define str_tims		pXlGraf->XLstr_tims

#define file_vis		pXlGraf->XLfile_vis

#define path_22dat	        pXlGraf->XLpath_22dat
#define path			pXlGraf->XLpath
#define fpDAT			pXlGraf->XLfpDAT
#define fpGR			pXlGraf->XLfpGR
#define inizio_dati             pXlGraf->XLinizio_dati
#define posizione_iniziale      pXlGraf->XLposizione_iniziale
#define fine_dati		pXlGraf->XLfine_dati
#define path_name		pXlGraf->XLpath_name
#define tsec		        pXlGraf->XLtsec
#define off_f22		        pXlGraf->XLoff_f22
#define lun_rec_dati            pXlGraf->XLlun_rec_dati
#define lun_parziale		pXlGraf->XLlun_parziale
#define num_complete		pXlGraf->XLnum_complete
#define b_wait			pXlGraf->XLb_wait
#define fpPATH			pXlGraf->XLfpPATH

/*  Dichiarazione del tipo per la lettura dal context degli oggetti il
	puntatore alla struttura delle variabili globali  */
typedef struct
	{
	S_XLGRAFICO *UxPXlGrafico;
	}FALSO_CTX;
 
/*  Define degli indici per il vettore "widget_array"  */
#define k_form                     	 1
#define k_popgraf               	 2
#define k_popmis                	 3
#define k_nyi                   	 4
#define k_draw0                 	 5
#define k_draw1                 	 6
#define k_mis1                  	 7
#define k_tim1                  	 8
#define k_ord1                  	 9
#define k_popup                 	10
#define k_mis2                  	11
#define k_tim2                  	12
#define k_ord2                  	13
#define k_val1                  	14
#define k_val2                  	15
#define k_tempo                 	16

#define k_selmis_dialog         	20
#define k_toggle_mis1           	21
#define k_toggle_mis2           	22
#define k_toggle_mis3           	23
#define k_toggle_mis4           	24
#define k_selmis_box            	25
#define k_selzoom_dialog        	26
#define k_toggle_zoom1          	27
#define k_toggle_zoom2          	28
#define k_toggle_zoom3          	29
#define k_toggle_zoom4          	30
#define k_toggle_zoom5          	31
#define k_umis_dialog           	32
#define k_toggle_umis1          	33
#define k_toggle_umis2          	34
#define k_toggle_umis3          	35
#define k_toggle_umis4          	36
#define k_toggle2_mis1          	37
#define k_toggle2_mis2          	38
#define k_toggle2_mis3          	39
#define k_toggle2_mis4          	40
#define k_fsca_dialog           	41
#define k_toggle3_mis1          	42
#define k_toggle3_mis2          	43
#define k_toggle3_mis3          	44
#define k_toggle3_mis4          	45
#define k_text_max              	46
#define k_text_min              	47
#define k_toggle_man            	48
#define k_toggle_auto           	49
#define k_selgr_dialog          	50
#define k_text_nomegr           	51
#define k_list_gr               	52
#define k_label_grmis1            	53
#define k_label_grmis2            	54
#define k_label_grmis3            	55
#define k_label_grmis4            	56
#define k_memgr_dialog            	57
#define k_list_memgr              	58
#define k_text_memgr              	59

#define k_find_text               	65
#define k_find_next               	66
#define k_find_previous           	67
#define k_selmis_elimina          	68
#define k_defumis_dialog          	69
#define k_list_defumis            	70
#define k_toggle2_umis1           	71
#define k_toggle2_umis2           	72
#define k_toggle2_umis3           	73
#define k_toggle2_umis4           	74
#define k_dir_dialog              	75
#define k_text_dir1               	76
#define k_text_dir2               	77
#define k_text_dir3               	78
#define k_text_dir4               	79
#define k_toggle_dir1             	80
#define k_toggle_dir2             	81
#define k_toggle_dir3             	82
#define k_toggle_dir4             	83
#define k_grafici_menu_entry      	84
#define k_misure_menu_entry       	85
#define k_max_widget             	86

/*
	definizioni di funzioni esterne
*/
Boolean XlSetVarGrafico(Widget, char *,int ,int, int);

#endif 
