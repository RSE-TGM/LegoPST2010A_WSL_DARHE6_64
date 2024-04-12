/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/**********************************************************************
    File di Include: CONVERTI.INC

        Costanti che determinano i fattori di scala tra le classi
        di scansione (le colonne) e le periodicita' delle misure.
        Le righe :
          riga 1: secondi su secondi/classe: da 1/1 a 60/1;
          riga 2: secondi su secondi/minuto: da 1/60 a 60/60;
          riga 3: secondi su secondi/ora : da 1/60*60 a 60/60*60;
          riga 4: secondi su secondi/giorno:da 1/60*60*24 a 60/60*60*24;

**********************************************************************/

float convertempo[4][5]={
        1.0,        5.0,       15.0,        30.0,        60.0,
        0.016666,   0.08333,    0.25     ,   0.5,         1.0,
        0.0002777,  0.0013888,  0.0041666,   0.0083333,   0.016666,
        0.000011574,0.00005787, 0.000173611, 0.000347222, 0.000694444};


