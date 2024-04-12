C**********************************************************************
C modulo adev.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)adev.f	5.2
C**********************************************************************
C
       SUBROUTINE ADEVI3(IFO,IOB,DEBL)
C*****************************************************************************
C
C        SIGNALS DEFLECTOR BLOCK
C
C*****************************************************************************
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/ADEV01/IBLOC
      COMMON/ADEV02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'ADEV'/
C
      CALL ADEVI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 1
      NINGRE = 3
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
      WRITE(IFO,3001)IOB
 3001 FORMAT('UDEV',A4,2X,
     &'--UA-- ANALOG SIGNAL DEFLECTOR OUTPUT')
      WRITE(IFO,3003)IOB
 3003 FORMAT('I1DE',A4,2X,
     &'--IN-- SIGNAL ONE DEFLECTOR INPUT')
      WRITE(IFO,3004)IOB
 3004 FORMAT('I2DE',A4,2X,
     &'--IN-- SIGNAL TWO DEFLECTOR INPUT')
      WRITE(IFO,3005)IOB
 3005 FORMAT('JDEV',A4,2X,
     &'--IN-- DEFLECTOR POSITION (0 = SIGNAL 1, 1 = SIGNAL 2)')
C
      RETURN
      END
      SUBROUTINE ADEVI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/ADEV01/IBLOC
      COMMON/ADEV02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
      RETURN
      END
      SUBROUTINE ADEVI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     &  IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
C*******************************************
C
C____ ADEV - BLOCCO DEVIATORE DI DUE SEGNALI
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      GO TO(100,200), IFUN
 100  CONTINUE
      WRITE(14,3000)
 3000 FORMAT('    GUAD     =',10X,'*')
      RETURN
C
C____ LETTURA DA FILE14 DEL NOME DEL BLOCCO
C
  200 READ(14,1000)
 1000 FORMAT(A)
      READ(14,3001)GUAD
 3001 FORMAT(14X,F10.0)
C
      DATI(ID1)=GUAD
      ID2=ID1
C
C____ COSTANTI DI NORMALIZZAZIONE
C
      CNXYU(IV1 ) =1.
      CNXYU(IV1+1)=1.
      CNXYU(IV1+2)=1.
      CNXYU(IV1+3)=1.
C
C____ TOLLERANZE 1 PER MILLE
C
      TOL(1)=1.E-3
C
      RETURN
      END
      SUBROUTINE ADEVC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM,J1,JFLOLOG
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT
C*******************************************
C
C____ ADEV - DEVIATORE DI DUE SEGNALI
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      GO TO (1,100,2),IFUN
C
C____ TOPOLOGIA JACOBIANO
C
 1    AJAC(1,1)=1.
      AJAC(1,2)=1.
      AJAC(1,3)=1.
      AJAC(1,4)=1.
      RETURN
C
C____ COEFFICIENTI JACOBIANO
C
 2    CONTINUE
      UU = XYU(IXYU +  0)
      E1 = XYU(IXYU +  1)
      E2 = XYU(IXYU +  2)
      J1 = JFLOLOG( XYU(IXYU +  3) )
      GUAD=DATI(IPD)
C
      IF(J1)THEN
	 AK=1.
      ELSE
	 AK=0.
      ENDIF
C
	 AJAC(1,1)=-1.
	 AJAC(1,2)=(1.-AK)*GUAD
	 AJAC(1,3)=AK*GUAD
	 AJAC(1,4)=-GUAD*E1+GUAD*E2
      RETURN
C
C____ CALCOLO DELLA RISPOSTA DEI REGOLATORI
C
 100  CONTINUE
C
C____ DECODIFICA DELLE VARIABILI
C
      UU = XYU(IXYU +  0)
      E1 = XYU(IXYU +  1)
      E2 = XYU(IXYU +  2)
      J1 = JFLOLOG( XYU(IXYU +  3) )
      GUAD=DATI(IPD)
C
      IF(J1)THEN
	 AK=1.
      ELSE
	 AK=0.
      ENDIF
C
      RNI(  1) = UU - GUAD*((1.-AK)*E1 + AK*E2)
      RETURN
      END
CC
      SUBROUTINE ADEVD1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $     IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
