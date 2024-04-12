C******************************************************************************
C modulo rec24.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)rec24.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE REC24(NEQSIS,XY,NU,UU)
      DIMENSION A(20),XY(*),UU(*)
C
      CHARACTER*32 F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR
      COMMON/LG3FLS/ F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR
C
      DATA EOF/'EOF'/,XLG/'*LG*'/,ISSO/'SI'/
C
C_________ SALVATAGGIO DEI RISULTATI SU FILE 24.
C
C
      REWIND (84)
      OPEN(UNIT=24,FILE=F24DAT,STATUS='UNKNOWN',FORM='FORMATTED')
C
 1000 FORMAT(20A4)
      DO 1 I=1,4
      READ(84,1000)A
      WRITE(24,1000)A
    1 CONTINUE
      DO 10 I=1,NEQSIS
      READ(84,1000)(A(J),J=1,20)
      IF(XY(I).LT.0.)GO TO 8
      WRITE(24,1001)(A(J),J=1,4),XY(I),(A(J),J=7,20)
 1001 FORMAT(3A4,A2,G10.5,14A4)
      GO TO 10
    8 WRITE(24,1002)(A(J),J=1,4),XY(I),(A(J),J=7,20)
 1002 FORMAT(3A4,A2,G10.4,14A4)
   10 CONTINUE
      READ(84,1000)A
      WRITE(24,1000)A
      DO 20 I=1,NU
      READ(84,1000)(A(J),J=1,20)
      IF(UU(I).LT.0.)GO TO 18
      WRITE(24,1001)(A(J),J=1,4),UU(I),(A(J),J=7,20)
      GO TO 20
   18 WRITE(24,1002)(A(J),J=1,4),UU(I),(A(J),J=7,20)
   20 CONTINUE
   30 READ(84,1000,END=100)(A(I),I=1,20)
      WRITE(24,1000)(A(I),I=1,20)
      GO TO 30
C
  100 CLOSE (24)
      RETURN
      END
