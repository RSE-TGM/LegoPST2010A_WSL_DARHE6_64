C*********************************************************************
C       Fortran Source:             filpos.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:23:30 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_filpos_f
      CHARACTER*80  RepoID
      COMMON /CM_filpos_f / RepoID
      DATA RepoID/'@(#)1,fsrc,filpos.f,2'/
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

      SUBROUTINE FILPOS(NF1,TF1,NN,IER)
C
C     POSIZIONAMENTO ALLA FINE DI UN FILE DI OUTPUT GRAFICO
C
      REAL T1R
      REWIND NF1
      READ(NF1)
      READ(NF1)N1
      IF(N1.EQ.NN)GO TO 1
      WRITE(6,1000)NF1,N1,NF1,NN
 1000 FORMAT(///10X,'ERRORE DI RESTART'/10X,
     $   'NUMERO GRANDEZZE SU FILE ',I3,'  = ',I6/10X,
     $   'NUMERO GRANDEZZE RICHIESTE IN OUTPUT SU FILE ',I3,' = ',I6)
      IER=1
      RETURN
C
C     POSIZIONAMENTO ALLA FINE DEL FILE
C
    1 READ(NF1,END=4)T1R
      T1 = T1R
C---la copiatura di T1R (imposto REAL) serve per la doppia precisione
      IF(T1.GT.TF1)GO TO 3
      AT=ABS(T1-TF1)
      IF(AT.GT.1.E-3)GO TO 1
      RETURN
C
    3 BACKSPACE NF1
      RETURN
    4 WRITE(6,*)'SUL FILE 22 NON SONO STATI REGISTRATI I RISULTATI '
      WRITE(6,*)'FINO AL TEMPO ',TF1,' (SEC)'
      WRITE(6,*)'ESECUZIONE DEL CASO DI RESTART INTERROTTA'
      CALL LGABRT
      STOP
      END
C            
