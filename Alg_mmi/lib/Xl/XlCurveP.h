/**********************************************************************
*
*	C Header:		XlCurveP.h
*	Instance:		1
*	Description:	
*	%created_by:	mauric %
*	%date_created:	Wed Jun 24 14:44:37 1998 %
*
**********************************************************************/
#ifndef _XlCurveP_h
#define _XlCurveP_h
/*
	Inclusione degli header file privati delle classi superiori
*/

#include <Xm/XmP.h>
#include <Xl/XlP.h>
#include <Xl/XlManagerP.h>
#include <Xl/XlCurve.h>

#include "f22_circ.h"


/*
	Strutture relative alla nuova Classe
*/
typedef struct {
        int dummy;
        } XlCurveClassPart;


/*
	Dichiarazione del record completo della classe
*/
typedef struct _XlCurveClassRec {
         CoreClassPart     core_class;
         CompositeClassPart  composite_class;
         XlManagerClassPart   xlmanager_class;
         XlCurveClassPart   xlcurve_class;
        } XlCurveClassRec;


extern XlCurveClassRec xlCurveClassRec;

 
typedef struct _s_xlcurve {
/*
	Risorse oggetto XlCurve
*/
   int     timePeriodKeys;
   int     valueRangeKeys;
   int     configurationButton;
   int     saveButton;
   int     saveGroupsButton;
   int     groupsButton;
   int     legend;
   int     numCurvesInd;
   Pixel   curveFieldColor;
   Pixel   gridColor;
   Pixel   refcursColor;
   Pixel   graphAreaColor;
   Pixel   legendColor;
   Pixel   mainColor;
   Pixel   keysColor;
   char    *legendFont;
   char    *timeAxisFont;
   char    *valueAxisFont;
   int     legendHeight;
   int     curveSourceType;
   char	   *curveSource;
   char    *varInfoStart[NUMMAXVAR];
   float   factScaleValue;
   char	   *rangeTimeZoom;
   int	   rangeTimeStart;
   Pixel   col_trend[NUMMAXVAR];
/*
	Variabili di stato (privato)
*/
   Pixmap  stip_fluctua;
   GC      grid_gc;
   GC      trends_gc[NUMMAXVAR];
   GC 	   trends_fluct_gc[NUMMAXVAR];
   GC	   lines_gc;

   XFontStruct  *font_info_time;
   XmFontList   font_list_time;
   XFontStruct  *font_info_value;
   XmFontList   font_list_value;
   XFontStruct  *font_info_legend;
   XmFontList   font_list_legend;

   int          numCurves;
   char         *varInfoChange[NUMMAXVAR];
   char         *colTrendString[NUMMAXVAR];
   int          change_conf_OK;

   Boolean      configur_error;

   int          cur_line_pos_f22;
   Boolean      curs_pos_OK;
   Boolean      seldata_OK;
   int          hour_sel;
   int          minute_sel;
   int          x_pix_start;
   Boolean      first_refresh;		
   char	        *var_lego_cod[NUMMAXVAR];
   int          ind_var_sel[NUMMAXVAR];
   PUNT_FILE_F22 file_f22;
   SIMULATOR     simpar;
   F22CIRC_HD    header_f22;
   F22CIRC_VAR   *name_desc_var;
   int           num_var_f22;
   SCIRC_SEL_NEW *buffer_f22;
   SCIRC_SEL_NEW *dati_f22;
   XPoint        *points_to_draw[NUMMAXVAR];
   XPoint	 *points_fluctua[NUMMAXVAR];
   int	         n_points[NUMMAXVAR];
   float	 t_start;
   float	 t_end;
   int	         n_last_val;
   int           pos_start_visual;
   int           pos_end_visual;
   float         interv_camp;
   int           range_zoom[N_MAX_RANGE_Z];
   int           rangeTimeDef;               /* Ampiezza dell'intervallo di
                                                tempo visualizzato alla
                                                partenza                    */
   int           num_range_zoom;             /* Numero di range temporali
                                                disponibili per lo zoom     */
   char          str_time[NUMDIVWIDTH+1][30];
   char	         unit_fis[NUMMAXVAR][NUMCHARUNIT];  /* Array contenente
                                                       le unita di misura   */
   char          tipo_unit[NUMMAXVAR][10];   /* Array contenente il tipo di
                                                unita' di misura delle var. 
						configurate                 */
   S_MIN_MAX_NEW min_max[NUMMAXVAR];         /* Array di strutture contenente
                                                i limiti fisici delle var.
                                                configurate                 */
   S_MIN_MAX_NEW min_max_oper[NUMMAXVAR];    /* Array si strutture contenente
                                                i limiti fisici delle var
                                                configurate modificati dalle
                                                operazioni sulle ordinate   */
   S_MIN_MAX_NEW min_max_perc;
   float         last_val_displ[NUMMAXVAR];  /* Array contenente l'ultimo
                                                valore visualizzato per le per
                                                le variabili configurate    */
   float         curs_val_displ[NUMMAXVAR];  /* Array contenente il valore
                                                sulla cursor line per le
                                                variabili configurate       */
   int	         toggle_state[NUMMAXVAR];    /* Indica quale toggle e'
                                                selezionato per le var.
                                                configurate                 */
   int           curve_inv_state[NUMMAXVAR];
   int           fis_sca_app;
   int	         fis_sca_displ;		     /* Indice della variabile con
                                                scala fisica visualizzata   */
   char          flood_name[MAXPATHNAME];
   char          hatch_name[MAXPATHNAME];
   Pixmap        pix_hatch;
	} S_XLCURVE;


typedef struct
{
        Widget  Uxtop_curve;
	Widget  Uxcontenitore1;
	Widget  UxgraphicArea;
	Widget  UxdateTime;
	Widget  UxsourceData;
	Widget  UxcurveField;
	Widget  UxchangeTime;
	Widget  UxincreaseTime;
	Widget  UxtimeLeft;
	Widget  UxselData;
	Widget  UxtimeRight;
	Widget  UxdecreaseTime;
	Widget  UxabsTime;
	Widget  Uxflow;
	Widget  UxchangeValue;
	Widget  UxincreaseValue;
	Widget  UxrangeUp;
	Widget  UxdefaultSet;
	Widget  UxrangeDown;
	Widget  UxdecreaseValue;
	Widget  UxformValue;
	Widget  UxlabVal1;
	Widget  UxlabVal2;
	Widget  UxlabVal3;
	Widget  UxlabVal4;
	Widget  UxlabVal5;
	Widget  UxlabVal6;
	Widget  UxformScaFis;
	Widget  UxlabScaFis0;
	Widget  UxlabScaFis1;
	Widget  UxlabScaFis2;
	Widget  UxlabScaFis3;
	Widget  UxlabUnitFis;
	Widget  UxformTime;
	Widget  UxlabTime1;
	Widget  UxlabTime2;
	Widget  UxlabTime3;
	Widget  UxlabTime4;
	Widget  UxlabTime5;
	Widget  UxlabTime6;
	Widget  UxlabValUn;
	Widget  UxlegendArea;
	Widget  UxrowColBut;
	Widget  UxpushButList[NUMMAXVAR];
	Widget  UxlabelCodList[NUMMAXVAR+1];
	Widget  UxrowColCod;
        Widget  UxlabelDescrList[NUMMAXVAR+1];
	Widget  UxrowColDescr;
        Widget  UxlabelLowLimList[NUMMAXVAR+1];
	Widget  UxrowColLowLim;
        Widget  UxlabelValueList[NUMMAXVAR+1];
	Widget  UxrowColVal;
        Widget  UxlabelHighLimList[NUMMAXVAR+1];
	Widget  UxrowColHighLim;
        Widget  UxlabelUnitList[NUMMAXVAR+1];
	Widget  UxrowColUnit;
        Widget  UxlabelCursorList[NUMMAXVAR+1];
	Widget  UxrowColCurs;
        Widget  Uxconfigur;
        Widget  Uxsave;
        Widget  UxsaveGr;
        Widget  Uxgroups;
        int     Uxto_right_border;
        int     Uxto_up_border;
        int     Uxto_half_right;
        int     Uxi;
        int     Uxnum_scale_act;
        float   Uxcursor_line_pos;
        float   Uxref_line_pos;
        int     Uxrefer_pos_pixel;
        int     Uxcurs_pos_pixel;
        Boolean Uxstatic_status;
        Boolean Uxstatic_status_app;
        Boolean Uxstart_point;
        Boolean Uxabs_time_flag;
        Dimension Uxwidth_curvefield;
        Dimension Uxheight_curvefield;
        GC      Uxrefcurs_gc;
} _UxCtopLevelCurve;


/*
	Nuovi campi per il record del widget XlCurve
*/
typedef struct {
        _UxCtopLevelCurve *contesto;   /*var dell' oggetto*/
        S_XLCURVE s_XLcurve;
        } XlCurvePart;


/*
	Dichiarazione completa del record per instanziazione
*/
typedef struct _XlCurveRec {
        CorePart   core;
        CompositePart  composite;
        XlManagerPart  xlmanager;
        XlCurvePart  curve;
        } XlCurveRec;


_UxCtopLevelCurve       *UxTopLevelCurveContext;

#define top_curve		UxTopLevelCurveContext->Uxtop_curve
#define contenitore1            UxTopLevelCurveContext->Uxcontenitore1
#define graphicarea		UxTopLevelCurveContext->UxgraphicArea
#define datetime		UxTopLevelCurveContext->UxdateTime
#define sourcedata		UxTopLevelCurveContext->UxsourceData
#define curvefield		UxTopLevelCurveContext->UxcurveField
#define changetime		UxTopLevelCurveContext->UxchangeTime
#define increasetime		UxTopLevelCurveContext->UxincreaseTime
#define timeleft		UxTopLevelCurveContext->UxtimeLeft
#define seldata			UxTopLevelCurveContext->UxselData
#define timeright		UxTopLevelCurveContext->UxtimeRight
#define decreasetime		UxTopLevelCurveContext->UxdecreaseTime
#define abstime			UxTopLevelCurveContext->UxabsTime
#define flow			UxTopLevelCurveContext->Uxflow
#define changevalue		UxTopLevelCurveContext->UxchangeValue
#define increasevalue		UxTopLevelCurveContext->UxincreaseValue
#define rangeup			UxTopLevelCurveContext->UxrangeUp
#define defaultset		UxTopLevelCurveContext->UxdefaultSet
#define rangedown		UxTopLevelCurveContext->UxrangeDown
#define decreasevalue		UxTopLevelCurveContext->UxdecreaseValue
#define formvalue		UxTopLevelCurveContext->UxformValue
#define labval1			UxTopLevelCurveContext->UxlabVal1
#define labval2			UxTopLevelCurveContext->UxlabVal2
#define labval3			UxTopLevelCurveContext->UxlabVal3
#define labval4			UxTopLevelCurveContext->UxlabVal4
#define labval5			UxTopLevelCurveContext->UxlabVal5
#define labval6			UxTopLevelCurveContext->UxlabVal6
#define formscafis		UxTopLevelCurveContext->UxformScaFis
#define labscafis0		UxTopLevelCurveContext->UxlabScaFis0
#define labscafis1		UxTopLevelCurveContext->UxlabScaFis1
#define labscafis2		UxTopLevelCurveContext->UxlabScaFis2
#define labscafis3		UxTopLevelCurveContext->UxlabScaFis3
#define labunitfis		UxTopLevelCurveContext->UxlabUnitFis
#define formtime		UxTopLevelCurveContext->UxformTime
#define labtime1		UxTopLevelCurveContext->UxlabTime1
#define labtime2		UxTopLevelCurveContext->UxlabTime2
#define labtime3		UxTopLevelCurveContext->UxlabTime3
#define labtime4		UxTopLevelCurveContext->UxlabTime4
#define labtime5		UxTopLevelCurveContext->UxlabTime5
#define labtime6		UxTopLevelCurveContext->UxlabTime6
#define labvalun		UxTopLevelCurveContext->UxlabValUn
#define legendarea              UxTopLevelCurveContext->UxlegendArea
#define rowColBut		UxTopLevelCurveContext->UxrowColBut
#define pushButList		UxTopLevelCurveContext->UxpushButList
#define labelCodList		UxTopLevelCurveContext->UxlabelCodList
#define labelDescrList		UxTopLevelCurveContext->UxlabelDescrList
#define labelLowLimList		UxTopLevelCurveContext->UxlabelLowLimList
#define labelValueList		UxTopLevelCurveContext->UxlabelValueList
#define labelHighLimList	UxTopLevelCurveContext->UxlabelHighLimList
#define labelUnitList		UxTopLevelCurveContext->UxlabelUnitList
#define labelCursorList		UxTopLevelCurveContext->UxlabelCursorList
#define rowColCod		UxTopLevelCurveContext->UxrowColCod
#define rowColdescr		UxTopLevelCurveContext->UxrowColDescr
#define rowColLimLow		UxTopLevelCurveContext->UxrowColLowLim
#define rowColVal		UxTopLevelCurveContext->UxrowColVal
#define rowColLimHigh		UxTopLevelCurveContext->UxrowColHighLim
#define rowColUnit		UxTopLevelCurveContext->UxrowColUnit
#define rowColCursor		UxTopLevelCurveContext->UxrowColCurs
#define configur                UxTopLevelCurveContext->Uxconfigur
#define save                    UxTopLevelCurveContext->Uxsave
#define savegr                  UxTopLevelCurveContext->UxsaveGr
#define groups                  UxTopLevelCurveContext->Uxgroups
#define to_right_border         UxTopLevelCurveContext->Uxto_right_border
#define to_up_border            UxTopLevelCurveContext->Uxto_up_border
#define to_half_right           UxTopLevelCurveContext->Uxto_half_right
#define num_scale_act           UxTopLevelCurveContext->Uxnum_scale_act
#define cursor_line_pos         UxTopLevelCurveContext->Uxcursor_line_pos
#define ref_line_pos            UxTopLevelCurveContext->Uxref_line_pos
#define refer_pos_pixel         UxTopLevelCurveContext->Uxrefer_pos_pixel
#define curs_pos_pixel          UxTopLevelCurveContext->Uxcurs_pos_pixel
#define static_status           UxTopLevelCurveContext->Uxstatic_status
#define static_status_app       UxTopLevelCurveContext->Uxstatic_status_app
#define start_point             UxTopLevelCurveContext->Uxstart_point
#define abs_time_flag           UxTopLevelCurveContext->Uxabs_time_flag
#define width_curvefield        UxTopLevelCurveContext->Uxwidth_curvefield
#define height_curvefield       UxTopLevelCurveContext->Uxheight_curvefield
#define refcurs_gc              UxTopLevelCurveContext->Uxrefcurs_gc
#endif	/* _XlCurveP_h */
