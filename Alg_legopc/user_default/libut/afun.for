C**********************************************************************
C modulo afun.f
C tipo 
C release 5.2
C data 4/12/95
C reserver @(#)afun.f	5.2
C**********************************************************************
C
      SUBROUTINE AFUNI3(IFO,IOB,DEBL)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/AFUN01/IBLOC
      COMMON/AFUN02/NCEL,NPAR
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'AFUN'/
C
      CALL AFUNI4(IOB,MOD)
      NSTATI = 0
      NUSCIT = 1
      NINGRE = 1
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
      WRITE(IFO,3001)IOB
 3001 FORMAT('UFUN',A4,2X,
     $'--UA-- FUNCTION GENERATOR OUTPUT VARIABLE')
      WRITE(IFO,3002)IOB
 3002 FORMAT('IFUN',A4,2X,
     $'--IN-- FUNCTION GENERATOR INPUT VARIABLE')
      RETURN
      END
      SUBROUTINE AFUNI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/AFUN01/IBLOC
      COMMON/AFUN02/NCEL,NPAR
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
C
      WRITE(IBLOC,1000)MOD,IOB
 1000 FORMAT(2A4)
      RETURN
      END
C
      SUBROUTINE AFUNI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,
     &  IBL1,IBL2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      INTEGER VAR
      DIMENSION VAR(MX1,*),XYU(*),DATI(*),CNXYU(*),TOL(*)
C*******************************************
C
C____ REGOLATORE AFUN - GENERATORE DI FUNZIONE DATA PER PUNTI
C
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      GO TO(100,200), IFUN
 100  CONTINUE
C
C____ CHIAMATA A GFUN PER SCRIVERE I DATI
C
      IDP=ID1
      CALL AFUNSI(IFUN,DATI,IDP)
C
      ID2=IDP
      RETURN
C
C____ LETTURA DA FILE14 DEL NOME DEL BLOCCO
C
  200 READ(14,1000)
 1000 FORMAT(A)
C
C____ CHIAMATA A GFUN PER LEGGERE I DATI
C
      IDP=ID1
      CALL AFUNSI(IFUN,DATI,IDP)
C
      ID2=IDP
C
C---costanti di normalizzazione
C
      CNXYU(IV1  ) = 1.
      CNXYU(IV1+1) = 1.
C
C---tolleranze 1 per mille
C
      TOL(1)=1.E-3
      RETURN
      END
      SUBROUTINE AFUNC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBL1,IBL2)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)
      LOGICAL KREGIM
      COMMON/REGIME/KREGIM
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT                          !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT
C*******************************************
C
C____ REGOLATORE AFUN - GENERATORE DI FUNZIONE DATA PER PUNTI
C
C*********** INIZIO ISTRUZIONI DICHIARATIVE
C
C______ USCITE REGOLATORE
C
C      REAL UA01
C
C______ INGRESSI REGOLATORE
C
      REAL II01                                                         !SNGL
C      DOUBLE PRECISION II01                                             !DBLE
C
C*********** INIZIO ISTRUZIONI ESECUTIVE
C
      GO TO (1,100,2),IFUN
C
C_____ topologia JACOBIANO
C
 1    AJAC(1,1)=1.
      AJAC(1,2)=1.
      RETURN
C
C_____ JACOBIANO
C
 2    AJAC(1,1)=1.
      UA01 = XYU(IXYU +  0)
      II01 = XYU(IXYU +  1)
C
      IDD=IPD
      CALL AFUNSR(UA01C,GRAD,II01,IDD,DATI)
      AJAC(1,2)=-GRAD
C
      RETURN
C
C____ CALCOLO DELLA RISPOSTA DEI REGOLATORI
C
 100  CONTINUE
C
C____ DECODIFICA DELLE VARIABILI
C
      UA01 = XYU(IXYU +  0)
      II01 = XYU(IXYU +  1)
C
C____ CHIAMATE AI**** MODULOTTI DI REGOLAZIONE
C
      IDD=IPD
      CALL AFUNSR(UA01C,GRAD,II01,IDD,DATI)
C
C____ RESIDUI
C
      RNI(  1) = (UA01C-UA01)
      RETURN
      END
      SUBROUTINE AFUNSI(IFUN,DATI,ID)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*)
      DIMENSION X(10),Y(10)
C
      GO TO (100,200),IFUN
C
C____ SCRITTURA SUL FILE 14 DEI DATI DI GFUN
C
  100 WRITE(14,501)
  501 FORMAT('    NPUNTI   =          *')
C
      DO I=1,10
      WRITE(14,504)I,I
  504 FORMAT(
     & '    X  ',I2,'    =          *',
     & '    Y  ',I2,'    =          *')
      ENDDO
C
      RETURN
C
C____ LETTURA DA FILE 14 DEI DATI DI GFUN
C
  200 CONTINUE
C
C_______ LETTURA DEL NUMERO DI PUNTI
      READ(14,503)FP
  503 FORMAT(2(14X,F10.0,1X))
      IF(FP.GT.10) FP=10
      NP=FP
      DATI(ID)=NP
C     C_______ LETTURA DELLE COORDINATE
C
      DO I=1,10
      READ(14,503)X(I),Y(I)
      ENDDO
C
      KK=ID+1
C
C_______ MEMORIZZAZIONE DELLE COORDINATE
C
      DO I=1,NP
      J1=KK+(I-1)*2
      J2=J1+1
      DATI(J1)=X(I)
      DATI(J2)=Y(I)
      ENDDO
      ID=ID+2*NP+1
C
      RETURN
      END
      SUBROUTINE AFUNSR(U,GRAD,E,ID,DATI)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*)
      DIMENSION X(10),Y(10)
C
      NP=DATI(ID)
      KK=ID+1
C
      DO I=1,NP
      J1=KK+(I-1)*2
      J2=J1+1
      X(I) = DATI(J1)
      Y(I) = DATI(J2)
      ENDDO
C
      IF(E.LE.X(1)) THEN
	   U=Y(1)
	   GRAD= 0.
      ELSE IF(E.GE.X(NP)) THEN
	   U=Y(NP)
	   GRAD= 0.
      ELSE
	   DO I=2,NP
	   IF(E.LT.X(I))GO TO 1
	   ENDDO
	   RETURN
 1         U= Y(I-1) + (Y(I)-Y(I-1))*(E-X(I-1))/(X(I)-X(I-1))
	   GRAD= (Y(I)-Y(I-1))/(X(I)-X(I-1))
      ENDIF
C
      ID=ID+2*NP+1
      RETURN
      END


CC
      SUBROUTINE AFUND1(BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                  IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
      RETURN
      END
