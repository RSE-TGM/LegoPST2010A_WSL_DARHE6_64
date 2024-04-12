C**********************************************************************
C modulo disn.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)disn.f	5.2
C**********************************************************************
      SUBROUTINE DISNI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     1                 IBL1,IBL2,IER,CNXYU,TOL)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*),CNORM(8)
C
      CHARACTER*10 NORMA
      CHARACTER*4  NORSIM(11)
      LOGICAL KREGIM
      REAL  NORM                                                        !SNGL
C      DOUBLE PRECISION  NORM                                            !DBLE
      EQUIVALENCE (CNORM(1),P0)
C
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE
C
      DATA NORSIM/'P0  ','H0  ','T0  ','W0  ','RO0 ',
     $            'AL0 ','V0  ','DP0 ','Q0  ','OM0 ','    '/
C
C---COPIA UN INGRESSO SU N USCITE
C
       GO TO(100,200), IFUN
C
  100  WRITE(14,500)'NORM        ','COEF        '
       RETURN
C
C---lettura e memorizzazione dati
C
  200  READ(14,501)
C
C-------------------- CISE  18-06-1990 -----------------------------
C
C
C     Assegnazione automatico della costante di normalizzazione
C     e del coefficiente da utilizzare nella combinazione lineare
C
       READ(14,501) NORMA, COEF
  501  FORMAT(14X,A10,15X,G10.5,1X)
C
      DO 25 J=1,11
      IF(NORMA(1:4).EQ.NORSIM(J)) GOTO 26
   25 CONTINUE
      READ(NORMA,24,ERR=27) NORM
   24 FORMAT(G10.5)
      IF(NORM.LT..1) GOTO 27
      GOTO 28
   27 WRITE(6,203) NORMA
  203 FORMAT(5X,'THE SYMBOL ',A10,'IS NOT CONTEMPLATED OR IS < .1')
      IER=1
      GOTO 40
   26 NORM=1.
      IF(J.LE.8) NORM=CNORM(J)
      IF(J.EQ.9) NORM=W0*H0
      IF(J.EQ.10) NORM=314.1592
C
   28 CONTINUE
C
C------------------------------------------------
C
       IF(COEF.EQ.0.) COEF=1.
C
  500  FORMAT(3(4X,A8,' =',10X,'*'))
C
       DATI(ID2   ) = NORM
       DATI(ID2+1 ) = NUSCIT
       DATI(ID2+2 ) = COEF
       ID2 = ID2+3
C
C---costanti di normalizzazione
C
       DO I=1,NUSCIT+NINGRE
	 CNXYU(IV1+I-1  ) = NORM
       ENDDO
C
C-------------------- CISE  18-06-1990 -----------------------------
C
      WRITE(6,111) NORMA, NORM, COEF
      WRITE(6,1111)
  111 FORMAT(4X,'NORM = ',A10,' = ',G10.5,'     COEF = ',G10.5)
 1111 FORMAT(A4)
C
C-------------------------------------------------------------------
C
   40 CONTINUE
C
      RETURN
      END
      SUBROUTINE DISNC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                         !SNGL
C       COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                  !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
C
C---COPIA UN INGRESSO SU N USCITE
C
      GO TO(100,200,300),IFUN
C
C---topologia jacobiano
C
  100 CONTINUE
      CALL DISNJAC(1,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
C
C---calcolo residui
C
  200 CALL DISN(IFUN,IXYU,XYU,IPD,DATI,RNI)
      RETURN
C
C---calcolo jacobiano
C
  300 CONTINUE
      CALL DISNJAC(2,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
      RETURN
      END
      SUBROUTINE DISNJAC(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
C
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                         !SNGL
C       COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                  !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
      parameter (MAXUSC=30)
C
      NUSC = DATI(IPD+1)
      COEF = DATI(IPD+2)
C
      GOTO(1,2,2),IFUN
C
C---topologia jacobiano
C
  1   CONTINUE
C
      DO 11 I=1,NUSC
      AJAC(I,I)=1.
      AJAC(I,NUSC+1)=1.
 11   CONTINUE
C
      RETURN
C
C      calcolo jacobiano analitico
C
  2   CONTINUE
C
      DO 13 I=1,NUSC
      AJAC(I,I)=-1.
      AJAC(I,NUSC+1)=COEF
 13   CONTINUE
      RETURN
      END
      SUBROUTINE DISN(IFUN,IXYU,XYU,IPD,DATI,RNI)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION XYU(*),DATI(*),RNI(*)
C
C
      LOGICAL KREGIM
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                         !SNGL
C       COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                  !DBLE
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C
C
      PARAMETER (MAXUSC=30)
      REAL  NORM                                                       !SNGL
C       DOUBLE PRECISION NORM                                            !DBLE
      DIMENSION U(MAXUSC)
C
C---COPIA UN INGRESSO SU N USCITE
C
      NUSC = DATI(IPD+1)
      DO 11 I=1,NUSC
      U(I)       = XYU(IXYU+I-1)
 11   CONTINUE
      AING     = XYU(IXYU+NUSC )
C
      NORM      = DATI(IPD   )
      COEF      = DATI(IPD+2 )
C
      DO 12 I=1,NUSC
      RNI(I) = U(I)-COEF*AING
 12   CONTINUE
      RETURN
      END
      SUBROUTINE DISNI3(IFO,IOB,DEBL)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/DISN01/IBLOC
      COMMON/DISN02/NCEL,NPAR
      COMMON/DISNUS1/NUSC
      COMMON/DISNUS2/CAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      CHARACTER*4 USC
      CHARACTER*1 CAR
      DATA MOD/'DISN'/
C
      CALL DISNI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = NUSC
      NINGRE = 1
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      DO 10 I=1,NUSC
      WRITE(USC,1000) CAR,I
 1000 FORMAT(A1,I2)
      WRITE(IFO,3001)USC,IOB,I
 10   CONTINUE
C
C
 3001 FORMAT(A4,A4,2X,'--UA-- DISN: OUTPUT VARIABLE NUM. ',I2)
      WRITE(IFO,3002)IOB
 3002 FORMAT('AING',A4,2X,'--IN-- DISN: INPUT VARIABLE')
      RETURN
      END
      SUBROUTINE DISNI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/DISN01/IBLOC
      COMMON/DISN02/NCEL,NPAR
      COMMON/DISNUS1/NUSC
      COMMON/DISNUS2/CAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      CHARACTER*1 CAR
C
      parameter (MAXUSC=30)
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
 100  WRITE(6,1011) MAXUSC
      READ(5,1010) NUSC
      IF(NUSC.GT.MAXUSC) GOTO 100
 1010 FORMAT(I2)
 1011 FORMAT(1X,'OUTPUTS NUMBER ? (MAX=',I3,')')
C
      CAR=' '
      WRITE(6,1012)
      READ(5,1013) CAR
 1012 FORMAT(1X,'INITIAL CHARACTER OF THE NAMES OF THE OUTPUTS ?')
 1013 FORMAT(A1)
C
      IF((CAR.LT.'A') .OR. (CAR.GT.'Z')) CAR='U'
      IF(CAR.EQ.'%')CAR='%'
C
      RETURN
      END
CC
      SUBROUTINE DISND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,
     $    XYU,IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
