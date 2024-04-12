/*
 * XlCaiAll.h - file di include pubblico per l'utilizzo del widget
 *             caiAll
 */
#ifndef _XlCaiAll_h
#define _XlCaiAll_h

#include <stdlib.h>
/*
Valore da porre a 1 se seconda var di blink defined
*/
#define NORM_DEF 0
/*
 definisco i colori da utilizzare
*/
#define RED 0x29
#define WHITE 0x1
#define YELLOW 0x10
#define BLACK 0x0
#define BLUE 0x33
#define GREEN 0x48
/*
Definizioni tipo di CAIALL
*/
#define CAIALL_UNIVERSAL   0		/* CaiAll con A,W,T,S */
#define CAIALL_A		65              /* CaiAll per all A   */
#define CAIALL_W		87              /* CaiAll per all W   */
#define CAIALL_T		84              /* CaiAll per all T   */
#define CAIALL_S		83              /* CaiAll per all S   */
#define CAIALL_M		77              /* CaiAll per all M   */
#define CAIALL_F		70              /* CaiAll per all F   */

#define ALLARM_CAIALL 'A'
#define WARNING_CAIALL 'W'
#define TOLERANCE_CAIALL 'T'
#define SIMUL_CAIALL 'S'
#define MANUAL_CAIALL 'M'
#define FAULT_CAIALL 'F'
#define NULL_CAIALL  '0'
/*
Numero max di CaiAll su riga per pull-down menu' in teleperm.i
*/
#define MAXNUMCAIALLXLINE		5
#define LEFTOFFSET		10
#define TOPOFFSET		6
/*
 nomi di risorse utilizzate internamente al caiAll
 */
#define XlNtipoCaiAll "tipoCaiAll"
#define XlCTipoCaiAll "TipoCaiAll"
#define XlDtipoCaiAll "CaiAll type"
#define XlOtipoCaiAll "All Allarm Types,Alarm-Only,Warning-Only,Tolerace-Only,S-Only,Manual-Only,Fault-Only"

/* costanti utilizzabili per settare il tipo di XlIndic */

#define CAIALL_RETTANGOLARE  0
#define CAIALL_ROTONDO  1
#define CAIALL_DEFAULT  CAIALL_RETTANGOLARE
#define _CAIALL_MAX     1
#define FREQUENZA1	"0.5"
#define FREQUENZA2	"2.0"
/* definizioni delle variabili risorse */

#define XlNfrequenza1   "frequenza1"
#define XlCFrequenza1   "Frequenza1"
#define XlDfrequenza1   "Variabile 1a frequenza(Hz) [max.4Hz]"
#define XlNfrequenza2   "frequenza2"
#define XlCFrequenza2   "Frequenza2"
#define XlDfrequenza2   "Variabile 2a frequenza(Hz) [max.4Hz]"


#define XlNvarGerarchia     "alarmsHierarchy"
#define XlCVarGerarchia     "AlarmsHierarchy"
#define XlDvarGerarchia     "Alarms Hierarchy Situation"
#define XlNvarString_A      "stringAlarm_A"
#define XlCVarString_A      "StringAlarm_A"
#define XlNvarString_W      "stringAlarm_W"
#define XlCVarString_W      "StringAlarm_W"
#define XlNvarString_T      "stringAlarm_T"
#define XlCVarString_T      "StringAlarm_T"
#define XlNvarString_S      "stringAlarm_S"
#define XlCVarString_S      "StringAlarm_S"
#define XlNvarString_M      "stringAlarm_M"
#define XlCVarString_M      "StringAlarm_M"
#define XlNvarString_F      "stringAlarm_F"
#define XlCVarString_F      "StringAlarm_F"

/*
Definizione RISORSE colori per allarmi principali
*/

#define        XlNcolorA_FG  "foreAllTypeA"
#define        XlCColorA_FG  "ForeAllTypeA"
#define        XlDcolorA_FG  "Foreground allarm A type"
#define        XlNcolorA_BG  "backAllTypeA"
#define        XlCColorA_BG  "BackAllTypeA"
#define        XlDcolorA_BG  "Background allarm A type"
#define        XlNcolorW_FG  "foreAllTypeW"
#define        XlCColorW_FG  "ForeAllTypeW"
#define        XlDcolorW_FG  "Foreground allarm W type"
#define        XlNcolorW_BG  "backAllTypeW"
#define        XlCColorW_BG  "BackAllTypeW"
#define        XlDcolorW_BG  "Background allarm W type"
#define        XlNcolorT_FG  "foreAllTypeT"
#define        XlCColorT_FG  "ForeAllTypeT"
#define        XlDcolorT_FG  "Foreground allarm T type"
#define        XlNcolorT_BG  "backAllTypeT"
#define        XlCColorT_BG  "BackAllTypeT"
#define        XlDcolorT_BG  "Background allarm T type"
#define        XlNcolorS_FG  "foreAllTypeS"
#define        XlCColorS_FG  "ForeAllTypeS"
#define        XlDcolorS_FG  "Foreground allarm S type"
#define        XlNcolorS_BG  "backAllTypeS"
#define        XlCColorS_BG  "BackAllTypeS"
#define        XlDcolorS_BG  "Background allarm S type"

#define        XlNcolorM_FG  "foreAllTypeM"
#define        XlCColorM_FG  "ForeAllTypeM"
#define        XlDcolorM_FG  "Foreground allarm M type"
#define        XlNcolorM_BG  "backAllTypeM"
#define        XlCColorM_BG  "BackAllTypeM"
#define        XlDcolorM_BG  "Background allarm M type"

#define        XlNcolorF_FG  "foreAllTypeF"
#define        XlCColorF_FG  "ForeAllTypeF"
#define        XlDcolorF_FG  "Foreground allarm F type"
#define        XlNcolorF_BG  "backAllTypeF"
#define        XlCColorF_BG  "BackAllTypeF"
#define        XlDcolorF_BG  "Background allarm F type"

#define        XlNcolorBord  "colorBord"
#define        XlCColorBord  "ColorBord"
#define        XlDcolorBord  "Border Color"

/*
definizioni dei colori degli allarmi principali
*/
#define MAXLUNCOLORNAME	100
#define MAXLUNSTRIGHIER	100
#define A_FG	"white"
#define A_BG    "red"
#define W_FG    "black"
#define W_BG	"yellow"
#define T_FG    "black"
#define T_BG    "blue"
#define S_FG    "red"
#define S_BG    "black"
/*
eventuali altri tipi di allarme
*/
#define M_FG    "black"
#define M_BG    "green"
#define N_FG    "black"
#define N_BG    "white"
#define F_FG    "red"
#define F_BG    "black"

/*
Define tipica di CaiAll
*/
#define XlNstatus       "status"
#define XlCStatus       "Status"
#define EMISSIONE       1
#define RIENTRO         0
#define RICONOSCIUTO    2
#define SPENTO    	3


/* declare the class constant */
extern WidgetClass xlCaiAllWidgetClass;

/* dichiarazione tipi per Classe e Instanziazione di CaiAll */
typedef struct _XlCaiAllClassRec *XlCaiAllWidgetClass;
typedef struct _XlCaiAllRec *XlCaiAllWidget;

#endif /* _XlCaiAll_h */

