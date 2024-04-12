C*********************************************************************
C       Fortran Source:             aggforaus.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Wed Jun  7 12:35:35 2006 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_aggforaus_f
      CHARACTER*80  RepoID
      COMMON /CM_aggforaus_f / RepoID
      DATA RepoID/'@(#)1,fsrc,aggforaus.f,2'/
      END
C**********************************************************************
C******************************************************************************
C modulo aggforaus.f
C tipo 
C release 1.3
C data 7/21/94
C reserver @(#)aggforaus.f	1.3
C******************************************************************************
C
C
C
C
      PROGRAM AGGFORAUS
      CHARACTER*80 LINE
      CHARACTER*4  MODULO
      CHARACTER*4  FORMOD(100)
C
C
C
C
C
      OPEN(UNIT=1,FILE='foraus.for',FORM='FORMATTED',
     $     STATUS='UNKNOWN')
      OPEN(UNIT=2,FILE='forausbase.f',FORM='FORMATTED',
     $     STATUS='OLD')
      OPEN(UNIT=3,FILE='foraus.f',FORM='FORMATTED',
     $     STATUS='UNKNOWN')
C
C   INCLUDE FORAUS.FOR IN FORAUSBASE.FOR SCRIVENDO
C   IL FILE FORAUS.F    
C
C
C______ COPIATURA DEL FORAUS.FOR
C
 1    READ(1,1000,END=50)LINE
 1000 FORMAT(A)
      IF(LINE(1:9).EQ.'C~FORAUS_') THEN
       MODULO=LINE(10:13)
       IF(KMOD.EQ.0) GO TO 10
         DO I=1,KMOD
         IF(FORMOD(I).EQ.MODULO) GO TO 20
         END DO
 10    KMOD=KMOD+1
       FORMOD(KMOD)=MODULO
 20    CONTINUE
      ENDIF
C
      WRITE(3,1000)LINE             
      GO TO 1
C
C______ COPIATURA DEL FORAUSBASE.FOR
C       ESCLUSO IL FORTRAN AUSILIARIO DEI MODULI PRESENTI IN FORAUS.FOR
C
 50   READ(2,1000,END=100)LINE
      IF(LINE(1:9).EQ.'C~FORAUS_') THEN
       MODULO=LINE(10:13)
       IF(KMOD.EQ.0) GO TO 60
         DO I=1,KMOD
         IF(FORMOD(I).EQ.MODULO) GO TO 55
         END DO
       GO TO 60 
 55    CONTINUE
C
C______ LETTURA A VUOTO DEL FORTRAN AUSILIARIO DI BASE
C
 58    READ(2,1000,END=100)LINE
       IF(LINE(1:9).EQ.'C~FORAUS_'
     $    .AND.LINE(10:13).EQ.MODULO)GO TO 50
       GO TO 58
C      
      ENDIF
C
 60   WRITE(3,1000)LINE             
      GO TO 50
 100  PRINT *,'FINE SCRITTURA FORAUS.F '
      STOP
      END


