/**********************************************************************
*
*       C Header:               menu_graf.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:07:03 1996 %
*
**********************************************************************/
/*           FILE menu_graf.h                 */
/*       File contenente parametri di uso     */
/*        comune alle routine del menu_graf   */

#ifndef _MENU_GRAF
#define _MENU_GRAF

#define MAX_VAR_RECORDED  15 /* Numero massimo di variabili memorizzabili
				in un file ascii  */

#define ERRORE		1    /* Identif errore generico    */
#define GIUSTO		0    /* Identif operazione eseguita correttamente  */

#define MULTIPLO        1    /* Identif find a selezione multipla  */
#define SINGOLO         0    /* Identif find a selezione singola  */

#define NORMAL_SAVE     1    /* Salvataggio normale del file f22  */
#define ASCII_SAVE      2    /* Salvataggio in formato ascii del file f22  */

#define MODIFICATO	1    /* Variabile per modifica avvenuta   */
#define NON_MODIFICATO	0    /* Variabile per modifica non avvenuta  */
#define SALVATO		1    /* Variabile per salvataggio effettuato  */
#define NON_SALVATO     0    /* Variabile per salvataggio non effettuato  */

#define EXTRACT_TIME    1    /* Identif sel extract dal menu principale  */
#define SHIFT_TIME      2    /* Identif sel shift dal menu principale */

#define CAMP_UGUALI	1    /* Var identif camp f22 in modo uniforme */
#define CAMP_DISUGUALI  0    /* Var identif camp f22 in modo non uniforme */

#define BESSEL		3    /* Filtro di tipo BESSEL */
#define BUTTERWORTH  	4    /* Filtro di tipo BUTTERWORTH */

#define ELAB_LINEARE	1    /* Variabile per Ax+B per menu Calc  */
#define SOMMA_ALGEBRICA 2    /* Variabile per x+y per menu Calc   */

#endif
