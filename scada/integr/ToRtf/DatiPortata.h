/*
   modulo DatiPortata.h
   tipo 
   release 2.3
   data 6/7/96
   reserved @(#)DatiPortata.h	2.3
*/
/****************************************************************
**
**      Datiportata.inc stabilisce le costanti di conversione
**      per il calcolo delle portate UNI e AGA.
**      Il range dei valori di M varia da 0.05 a 0.74;
**      un errore superiore al massimi o inferiore al minimo
**      provoca una uscita per errore.
**      Il valore di [a] nel calcolo della costante_a della
**      portata UNI viene fatto per interpolazione dai dati
**      della tabella.
**
****************************************************************/

static float prange[16][2]= {
			0.5980,         0.325,
                        0.6020,         0.325,
                        0.6080,         0.325,
                        0.6150,         0.335,
                        0.6240,         0.335,
                        0.6340,         0.345,
                        0.6460,         0.345,
                        0.6600,         0.365,
                        0.6760,         0.365,
                        0.6950,         0.395,
                        0.7116,         0.395,
                        0.7400,         0.430,
                        0.7680,         0.450,
                        0.8020,         0.475,
                        1.0032,         0.683,
                        1.0006,         0.000  };

