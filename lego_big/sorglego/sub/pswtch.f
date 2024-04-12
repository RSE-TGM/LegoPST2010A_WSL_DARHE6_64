C*********************************************************************
C       Fortran Source:             pswtch.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:29:41 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_pswtch_f
      CHARACTER*80  RepoID
      COMMON /CM_pswtch_f / RepoID
      DATA RepoID/'@(#)1,fsrc,pswtch.f,2'/
      END
C**********************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE PSWTCH(K)
C
C     ELENCA LE STAMPE SOTTO SSWTCH DEI VARII LEGO
C
      GO TO(1,10,30,30,40,50,60),K
C
    1 WRITE(6,1001)
 1001 FORMAT(5X,'SSWTCH * 1 *  STAMPE INTERMEDIE DATI TOPOLOGICI')
C
   10 WRITE(6,2001)
 2001 FORMAT(5X,'SSWTCH * 1 *  STAMPA DELLE MATRICI TOPOLOGICHE ',
     $   'DIRETTA E INVERSA '/19X,'RELATIVE AL SISTEMA DIFF.-ALG. ',
     $   'DA RISOLVERE IN TRANSITORIO ')
      GO TO 100
C
C
   30 WRITE(6,3401)
 3401 FORMAT(5X,'SSWTCH * 1 * STAMPA L'' ORDINAMENTO DELLE EQUAZIONI ',
     $   'E DELLE INCOGNITE')
      WRITE(6,3402)
 3402 FORMAT(5X,'SSWTCH * 2 * STAMPA DEL VETTORE RESIDUI AD OGNI ',
     $   'ITERAZIONE ')
      WRITE(6,3403)
 3403 FORMAT(5X,'SSWTCH * 3 * STAMPA MATRICE JACOBIANA DEL SISTEMA ',
     $   'DI REGIME')
      WRITE(6,3404)
 3404 FORMAT(5X,'SSWTCH * 4 * STAMPA DELLE MATRICI TOPOLOGICHE DIRETTA',
     $   ' E INVERSA '/18X,'RELATIVE AL SISTEMA ALG. DA RISOLVERE')
      GO TO 100
C
   40 WRITE(6,4001)
 4001 FORMAT(5X,'SSWTCH * 1 * PARAMETRI PER INTEGRAZIONE PASSO PASSO')
      WRITE(6,4002)
 4002 FORMAT(5X,'SSWTCH * 2 * DATI DELLE PERTURBAZIONI ASSEGNATE ')
      WRITE(6,4003)
 4003 FORMAT(5X,'SSWTCH * 3 * DATI DEL MODELLO LINEARIZZATO')
      GO TO 100
C
   50 WRITE(6,5001)
 5001 FORMAT(5X,'SSWTCH * 1 * VALORI DEGLI INGRESSI AD OGNI PASSO DI ',
     $   'INTEGRAZIONE ')
      WRITE(6,5002)
 5002 FORMAT(5X,'SSWTCH * 2 * MATRICE JACOBIANA DEL SISTEMA ALG.',
     $   '-DIFF. AD OGNI CAMBIO ')
      WRITE(6,5003)
 5003 FORMAT(5X,'SSWTCH * 3 * NUMERO DI ITERAZIONI FATTE AD OGNI ',
     $   'RISOL. DEL SISTEMA ALG.-DIFF.')
      WRITE(6,5004)
 5004 FORMAT(5X,'SSWTCH * 4 * MATRICE TOPOLOGICA DELLO JACOBIANO ')
      WRITE(6,5005)
 5005 FORMAT(5X,'SSWTCH * 5 * STAMPA DEL VETTORE RESIDUI AD OGNI ',
     $   'ITERAZIONE PER OGNI PASSO DI INTEGRAZIONE')
      GO TO 100
C
   60 WRITE(6,6001)
 6001 FORMAT(5X,'SSWTCH * 1 * MATRICE JACOBIANA RETTANGOLARE INIZIALE')
      WRITE(6,6002)
 6002 FORMAT(5X,'SSWTCH * 2 * MATRICE JAC. RETT. DOPO LA ELIMIN.',
     $   ' DELLE VARIABILI INTERMEDIE')
      WRITE(6,6003)
 6003 FORMAT(5X,'SSWTCH * 3 * MATRICE DEL SISTEMA LINEARIZZATO')
  100 RETURN
      END
C            
