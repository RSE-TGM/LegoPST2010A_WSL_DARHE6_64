/**********************************************************************
*
*	C Header:		XlCurve.h
*	Instance:		1
*	Description:	
*	%created_by:	mauric %
*	%date_created:	Wed Jun 24 14:31:59 1998 %
*
**********************************************************************/
#ifndef _XlCurve_h
#define _XlCurve_h


#define NUMINFOVAR	7     /* Numero di campi presenti nella risorsa
                                 'varInfo' associata ad ogni variabile     */ 
#define MAXLENINFOVAR	300   /* Lunghezza massima della risorsa 'varInfo' */
#define CHAR_LEGO_COD   8     /* Lunghezza del codice lego                 */
#define NUMCHARUNIT     20    /* Lunghezza massima della stringa che
                                 specifica l'unita' di misura              */

#define N_MAX_RANGE_Z   10    /* Numero massimo dei range sull'asse dei
                                 tempi per lo zoom                         */

#define NUMDIVWIDTH	6     /* Numero di divisioni (griglia) sull'asse
                                 delle ascisse                             */
#define NUMDIVHEIGHT	5     /* Numero di divisioni (griglia) sull'asse
                                 delle ordinate                            */
#define NUMLIMLAYOUT	4     /* Numero minimo di righe visualizzate nella
                                 legend area                               */
#define MAXPATHNAME	300   /* Lunghezza massima dei path                */

#define TUTTI_CAMP	0     /* Flag che impone la lettura di tutti i
                                 campioni dal file                         */ 
#define AGGIORNA_CAMP	1     /* Flag che impone la lettura solo dei
                                 campioni nuovi dal file                   */

#define REF_LIN_DEFAULT 45.0  /* Posizione di default della reference line
                                 espressa in %                             */
#define CUR_LIN_DEFAULT 55.0  /* Posizione di default della cursor line
                                 espressa in %                             */
#define SKIP_GRID       2

#define LIM_INF_SCA_VAL 1.0   /* Valore minimo del fattore di scalamento
                                 sull'asse delle ordinate                  */ 
#define DEFAULT_SCA_VAL 2     /* Valore di default del fatt. di scalamento
                                 sull'asse delle ordinate                  */
#define DEF_TIME_RANGE 3600   /* Valore di default del range sull'asse
                                 dei tempi                                 */

#define CONF_NO_CHANGE     0  /* Flag che indica che non e' stata cambiata
                                 la situazione delle variabili runtime     */
#define CURVE_CHANGE       1  /* Flag che indica che e' cambiata almeno
                                 una variabile runtime                     */
#define PARAM_CHANGE       2  /* Flag che indica che sono cambiati i
                                 parametri di almeno una variabile runtime */

#define DEF_LL_DISPL  0.0     /* Limite minimo di default visualizzato
                                 sull'asse dei valori                      */
#define DEF_HL_DISPL  100.0   /* Limite massimo di default visualizzato
                                 sull'asse dei valori                      */
#define DEF_DIV_DISPL 20.0    /* Ampiezza della singola divisione
                                 sull'asse dei valori                      */ 

/*
   Tipologie di unita' di misura associabili alle singole variabili da
   visualizzare.
*/ 
#define PERCENT            "PC"
#define PERUNIT            "PU"
#define ENGINEER           "ENG"

/*
	Nomi di risorse utilizzate internamente al curve
*/

#define XlNtimePeriodKeys "timePeriodKeys"
#define XlCTimePeriodKeys "TimePeriodKeys"
#define XlDtimePeriodKeys "Time period keys"
#define XlOtimePeriodKeys "No,Yes"

#define XlNvalueRangeKeys "valueRangeKeys"
#define XlCValueRangeKeys "ValueRangeKeys"
#define XlDvalueRangeKeys "Value range keys"
#define XlOvalueRangeKeys "No,Yes"

#define XlNconfigurationButton "configurationButton"
#define XlCConfigurationButton "ConfigurationButton"
#define XlDconfigurationButton "Configuration Button"
#define XlOconfigurationButton "No,Yes"

#define XlNsaveButton "saveButton"
#define XlCSaveButton "SaveButton"
#define XlDsaveButton "Save Button"
#define XlOsaveButton "No,Yes"

#define XlNsaveGroupsButton "saveGroupsButton"
#define XlCSaveGroupsButton "SaveGroupsButton"
#define XlDsaveGroupsButton "Save Groups Button"
#define XlOsaveGroupsButton "No,Yes"

#define XlNgroupsButton "groupsButton"
#define XlCGroupsButton "GroupsButton"
#define XlDgroupsButton "Groups Button"
#define XlOgroupsButton "No,Yes"

#define XlNlegend "legend"
#define XlCLegend "Legend"
#define XlDlegend "Legend display"
#define XlOlegend "No,Yes"

#define XlNnumCurvesInd "numCurvesInd"
#define XlCNumCurvesInd "NumCurvesInd"
#define XlDnumCurvesInd "Number of curves"
#define XlOnumCurvesInd "1,2,3,4,5,6,7,8,9,10"

#define XlNcurveFieldColor "curveFieldColor"
#define XlCcurveFieldColor "CurveFieldColor"
#define XlDcurveFieldColor "Curve background color"

#define XlNgridColor "gridColor"
#define XlCgridColor "GridColor"
#define XlDgridColor "Grid color"

#define XlNrefcursColor "refcursColor"
#define XlCrefcursColor "RefcursColor"
#define XlDrefcursColor "Reference-cursor lines color"

#define XlNgraphAreaColor "graphAreaColor"
#define XlCgraphAreaColor "GraphAreaColor"
#define XlDgraphAreaColor " Graphic area color"

#define XlNlegendFieldColor "legendColor"
#define XlClegendFieldColor "LegendColor"
#define XlDlegendFieldColor "Legend background color"

#define XlNmainFieldColor "mainColor"
#define XlCmainFieldColor "MainColor"
#define XlDmainFieldColor "Main window background color"

#define XlNkeysColor "keysColor"
#define XlCkeysColor "KeysColor"
#define XlDkeysColor "Keys background color"

#define XlNfontLegend "legendFont"
#define XlCfontLegend "LegendFont"
#define XlDfontLegend "Legend font"

#define XlNtimeAxisFont "timeAxisFont"
#define XlCtimeAxisFont "TimeAxisFont"
#define XlDtimeAxisFont "Time axis font"

#define XlNvalueAxisFont "valueAxisFont"
#define XlCvalueAxisFont "ValueAxisFont"
#define XlDvalueAxisFont "Value axis font"

#define XlNlegendHeight "legendHeight"
#define XlCLegendHeight "LegendHeight"
#define XlDlegendHeight "Autoscaling first variable"
#define XlOlegendHeight "No,Yes"

#define XlNcurveDataSourceType "curveSourceType"
#define XlCcurveDataSourceType "CurveSourceType"
#define XlDcurveDataSourceType "Data source type"
#define XlOcurveDataSourceType "Circular archive variables,RunTime variables"

#define XlNcurveDataSource "curveSourcePath"
#define XlCcurveDataSource "CurveSourcePath"
#define XlDcurveDataSource "Path  and archive file name (f22)"

#define XlNvar1Info "var1Info"
#define XlCvar1Info "Var1Info"
#define XlDvar1Info "First variable info"

#define XlNvar2Info "var2Info"
#define XlCvar2Info "Var2Info"
#define XlDvar2Info "Second variable info"

#define XlNvar3Info "var3Info"
#define XlCvar3Info "Var3Info"
#define XlDvar3Info "Third variable info"

#define XlNvar4Info "var4Info"
#define XlCvar4Info "Var4Info"
#define XlDvar4Info "Forth variable info"

#define XlNvar5Info "var5Info"
#define XlCvar5Info "Var5Info"
#define XlDvar5Info "Fifth variable info"

#define XlNvar6Info "var6Info"
#define XlCvar6Info "Var6Info"
#define XlDvar6Info "Sixth variable info"

#define XlNvar7Info "var7Info"
#define XlCvar7Info "Var7Info"
#define XlDvar7Info "Seventh variable info"

#define XlNvar8Info "var8Info"
#define XlCvar8Info "Var8Info"
#define XlDvar8Info "Eighth variable info"

#define XlNvar9Info "var9Info"
#define XlCvar9Info "Var9Info"
#define XlDvar9Info "Ninth variable info"

#define XlNvar10Info "var10Info"
#define XlCvar10Info "Var10Info"
#define XlDvar10Info "Tenth variable info"

#define XlNfactScaleValue "factScaleValue"
#define XlCfactScaleValue "FactScaleValue"
#define XlDfactScaleValue "Scale factor axis value (>=1.0)"

#define XlNrangeTimeZoom "rangeTimeZoom"
#define XlCrangeTimeZoom "RangeTimeZoom"
#define XlDrangeTimeZoom "Time scales (sec)"

#define XlNrangeTimeStart "rangeTimeStart"
#define XlCrangeTimeStart "RangeTimeStart"
#define XlDrangeTimeStart "Display time period (sec)"

#define XlNcurveColor1 "curveColor1"
#define XlCcurveColor1 "CurveColor1"
#define XlDcurveColor1 "First variable color"

#define XlNcurveColor1 "curveColor1"
#define XlCcurveColor1 "CurveColor1"
#define XlDcurveColor1 "First variable color"

#define XlNcurveColor2 "curveColor2"
#define XlCcurveColor2 "CurveColor2"
#define XlDcurveColor2 "Second variable color"

#define XlNcurveColor3 "curveColor3"
#define XlCcurveColor3 "CurveColor3"
#define XlDcurveColor3 "Third variable color"

#define XlNcurveColor4 "curveColor4"
#define XlCcurveColor4 "CurveColor4"
#define XlDcurveColor4 "Forth variable color"

#define XlNcurveColor5 "curveColor5"
#define XlCcurveColor5 "CurveColor5"
#define XlDcurveColor5 "Fifth variable color"

#define XlNcurveColor6 "curveColor6"
#define XlCcurveColor6 "CurveColor6"
#define XlDcurveColor6 "Sixth variable color"

#define XlNcurveColor7 "curveColor7"
#define XlCcurveColor7 "CurveColor7"
#define XlDcurveColor7 "Seventh variable color"

#define XlNcurveColor8 "curveColor8"
#define XlCcurveColor8 "CurveColor8"
#define XlDcurveColor8 "Eigth variable color"

#define XlNcurveColor9 "curveColor9"
#define XlCcurveColor9 "CurveColor9"
#define XlDcurveColor9 "Ninth variable color"

#define XlNcurveColor10 "curveColor10"
#define XlCcurveColor10 "CurveColor10"
#define XlDcurveColor10 "Tenth variable color"

#define ARCH_CIRC_XLCURVE	0
#define RUN_TIME		1

extern WidgetClass xlCurveWidgetClass;

/*
	Dichiarazione tipi per Classe e Instanziazione di Curve 
*/
typedef struct _XlCurveClassRec *XlCurveWidgetClass;
typedef struct _XlCurveRec *XlCurveWidget;



#endif
