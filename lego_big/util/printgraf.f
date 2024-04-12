C*********************************************************************
C       Fortran Source:             printgraf.f
C       Subsystem:              1
C       Description:
C       %created_by:    famgr %
C       %date_created:  Mon Apr 29 09:08:11 1996 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_printgraf_f
      CHARACTER*80  RepoID
      COMMON /CM_printgraf_f / RepoID
      DATA RepoID/'@(#)1,fsrc,printgraf.f,2'/
      END
C**********************************************************************
C******************************************************************************
C modulo printgraf.f
C tipo 
C release 1.3
C data 7/21/94
C reserver @(#)printgraf.f	1.3
C******************************************************************************
C
C     File modificato da Villa Giovanni Walter, Gruppo Informatica
C     presso ENEL D.C.O. Milano.
C     Modifiche effettuate: Eliminata la keyword SHARED da una OPEN. 
C
      CHARACTER*80 TITOLO
      CHARACTER*8 SIMB1(1000),SY,SSI,BL
      CHARACTER*50 IN_FIL,OUT_FIL
      DIMENSION COURBE1(1000),ISY(1000)
      DATA SSI/'SI'/,BL/' '/
      PRINT *,'PROGRAMMA PER LA SCRITTURA DI UN FILE ASCII'
      PRINT *,'CONTENENTE IL TEMPO E ALCUNE GRANDEZZE RELATIVE'
      PRINT *,'AD UN TRANSITORIO USCITA-LEGO'
      PRINT 1000,' nome file grafici uscita-LEGO ? '
      READ(5,1001) IN_FIL
      OPEN (UNIT=1,FILE=IN_FIL,STATUS='OLD',FORM='UNFORMATTED')
  201 REWIND 1 
      PRINT 1000,' nome file di uscita ASCII ? '
      READ(5,1001) OUT_FIL
      OPEN (UNIT=2,FILE=OUT_FIL,STATUS='UNKNOWN'
     &,FORM='FORMATTED')
      REWIND 2 
      READ(1) TITOLO
      READ(1) NG,(SIMB1(I),I=1,NG)
      PRINT *,'TITOLO DEL TRANSITORIO'
      PRINT *,TITOLO
      KMX=1000
      K=0
      PRINT *,'FORNISCI I NOMI DELLE GRANDEZZE CHE VUOI REGISTRARE 
     &IN ASCII'
   15 PRINT *,'NOME GRANDEZZA? ( * equivale a tutte le grandezze)'
      READ 1001,SY
      DO 1 I=1,NG
      IF(SY.EQ.BL)GO TO 6
      IF(SY.EQ.'*') GO TO 7
      IF(SIMB1(I).EQ.SY)GO TO 5
  1   CONTINUE
      PRINT *,'IL SIMBOLO NON ESISTE'
      PRINT *,'ELENCO DEI SIMBOLI' 
      WRITE(6,4343)(SIMB1(I),I=1,NG)
 4343 FORMAT(10(2X,A)/) 
      GO TO 15 
   5  K=K+1   
      ISY(K)=I
      IF(K.LT.KMX)GO TO 15
   6  PRINT *,'FINE ASSEGNAZIONE GRANDEZZE'
      IF(K.EQ.0)STOP
      KG=K
      GO TO 19
  7   KG=NG
      DO I=1,KG
      ISY(I)=I
      END DO
 19   CONTINUE 
      WRITE(2,4345)TITOLO
      WRITE(2,4346)KG
 4346 FORMAT(1X,'NUMERO DI GRANDEZZE REGISTRATE = ',I5)
      WRITE(2,4343)(SIMB1(ISY(J)),J=1,KG)
 4345 FORMAT(A)
      PRINT *,'DARE TINIZ. E TFIN'
      READ *,TIN,TFI
  99  READ (1,END=100) TT1,(COURBE1(I),I=1,NG)           
      IF(TT1.LT.TIN)GO TO 99
      IF(TT1.GT.TFI)GO TO 200
      WRITE(2,3000)TT1,
     & (COURBE1(ISY(K)),K=1,KG)
 3000 FORMAT(5(1X,E15.8))
      GO TO 99
100   CONTINUE 
1000  FORMAT(5X,A,$)
1001  FORMAT(A)
  200 STOP
      END
