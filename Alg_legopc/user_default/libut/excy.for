C**********************************************************************
C modulo excy.f
C tipo 
C release 5.16
C data 18/6/03
C reserver @(#)excy.f	5.16
C**********************************************************************
C----------------------------------------------------------------------------
C
C        MODULO EXCY
C      
C      - scambiatore di calore con parete metallica senza separazione tra
C        idrodinamica e termica
C
C----------------------------------------------------------------------------
C
      SUBROUTINE EXCYI3(IFO,IOB,DEBL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NCELMAX=6)
      INTEGER NZF(NCELMAX)
      CHARACTER*80 DEBL
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
      DATA MOD/'EXCY'/
      COMMON/EXCY01/IBLOC
      COMMON/EXCY02/NCEL,NZF,NZFTOT
C
      CALL EXCYI4(IOB,MOD)
C
      WRITE(IFO,2999)IBLOC,IOB,MOD,DEBL
 2999 FORMAT(A,2X,'BL.-',A4,'- **** MODULO ',A4,' - ',A)
C
    5 NSTATI= 0
      NUSCIT= 6*NCEL
      NINGRE= 5+2*NZFTOT
C
      DO 20 K=1,NCEL
      WRITE(IFO,3000)K,IOB,K
 3000 FORMAT('HM',I2,A4,2X,'--UA-- AVERAGE FLUID ENTHALPY', 
     1' CELL ',I2)
   20 CONTINUE
C
      DO 30 K=1,NCEL-1
      WRITE(IFO,3001)K,IOB,K
 3001 FORMAT('PU',I2,A4,2X,'--UA-- FLUID PRESSURE', 
     1' AT CELL ',I2,' OUTLET')
   30 CONTINUE
C
      WRITE(IFO,3007)IOB
 3007 FORMAT('WITU',A4,2X,'--UA-- TUBE INLET MASS FLOW' )
C
      DO 40 K=1,NCEL-1
      WRITE(IFO,3201)K,IOB,K
 3201 FORMAT('WI',I2,A4,2X,'--UA-- FLUID MASS FLOW', 
     1' AT CELL ',I2,' INLET')
   40 CONTINUE
      WRITE(IFO,3102)IOB
 3102 FORMAT('WUTU',A4,2X,'--UA-- TUBE OUTLET MASS FLOW')
C
      DO 50 K=1,NCEL
      WRITE(IFO,3003)K,IOB,K
 3003 FORMAT('QTI',I1,A4,2X,'--UA-- POWER EXCYANGED BETWEEN', 
     1' METAL AND FLUID INSIDE CELL ',I2)
   50 CONTINUE
C
      DO 45 K=1,NCEL-1
      WRITE(IFO,3221)K,IOB,K
 3221 FORMAT('HU',I2,A4,2X,'--UA-- TOTAL ENTHALPY AT CELL ', 
     1I2,' OUTLET')
   45 CONTINUE
      WRITE(IFO,3004)IOB
 3004 FORMAT('HUTU',A4,2X,'--UA-- TUBE OUTLET TOTAL ENTHALPY')
C
      DO K=1,NCEL
	 WRITE(IFO,3025)K,IOB,K
      ENDDO
 3025 FORMAT('TPE',I1,A4,2X,'--UA-- EXTERNAL WALL TEMPERATURE ',
     &'AT CELL ',I2)
C
      WRITE(IFO,3005)IOB
 3005 FORMAT('HITU',A4,2X,'--IN-- TUBE INLET TOTAL ENTHALPY')
C
      WRITE(IFO,3101)IOB
 3101 FORMAT('PITU',A4,2X,'--IN-- TUBE INTLET FLUID PRESSURE')
C
      WRITE(IFO,3006)IOB
 3006 FORMAT('PUTU',A4,2X,'--IN-- TUBE OUTLET FLUID PRESSURE')
C
      WRITE(IFO,3008)IOB
 3008 FORMAT('HVAL',A4,2X,'--IN-- TUBE OUTLET FLUID ENTHALPY',
     1' (FLOW INVERSION)')
C
      WRITE(IFO,3009)IOB
 3009 FORMAT('ATTR',A4,2X,'--IN-- TUBE FRICTION COEFFICIENT')
C
      DO I=1,NCEL
	 DO J=1,NZF(I)
	    WRITE(IFO,3010)I,J,IOB,I,J
	 ENDDO
      ENDDO
 3010 FORMAT('TF',I1,I1,A4,2X,'--IN-- EXTERNAL FLUID TEMPERATURE',
     &' CELL ',I1,' ZONE ',I1)
C
      DO I=1,NCEL
	 DO J=1,NZF(I)
	    WRITE(IFO,3011)I,J,IOB,I,J
	 ENDDO
      ENDDO
 3011 FORMAT('GE',I1,I1,A4,2X,'--IN-- CONVECTIVE COEFF. EXTERNAL',
     &' FLUID CELL ',I1,' ZONE ',I1)
C
      RETURN
      END
C**************************************************************************
      SUBROUTINE EXCYI4(IOB,MOD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NZFMAX=6,NCELMAX=6,NZTMAX=32)
      INTEGER NZF(NCELMAX)
      COMMON/EXCY01/IBLOC
      COMMON/EXCY02/NCEL,NZF,NZFTOT
      CHARACTER*8 IBLOC
      CHARACTER*4 IOB
      CHARACTER*4 MOD
C
    1 WRITE(6,1000)
 1000 FORMAT(//10X,'EXCYANGING TUBE WITH METAL WALL'//)
      WRITE(6,1003) NCELMAX
 1003 FORMAT(//10X,'NUMBER OF CELLS (02 -',I3,') ?')
      READ(5,*) NCEL
 1001 FORMAT(I2)
      IF(NCEL.GE.2.AND.NCEL.LE.NCELMAX) GO TO 2
      WRITE(6,1002) NCEL
 1002 FORMAT(/10X,'ERROR  - CELLS NUMBER=',I3,/)
      GO TO 1
C
    2 CONTINUE
      NZFTOT=0
      DO J=1,NCEL
    3   WRITE(6,1032) J,NZFMAX,NZTMAX
C ! NZF(J)
        READ(5,*) NF
        IF(NF.LT.1.OR.NF.GT.NZFMAX) THEN
          WRITE(6,1033)
          GOTO 3
        ENDIF
        NZFTOT=NZFTOT+NF
        NZF(J) = NF
      ENDDO
      IF(NZFTOT.GT.NZTMAX) THEN
         WRITE(6,1034)NZTMAX
         GO TO 2
      END IF
 1032 FORMAT(2X,' NUMBER OF ZONES OF THERMAL EXCHANGE',/,
     $       2X,' WITH EXTERNAL',
     $          ' FLUID OF THE CELL ',I1,' (1-',I1,')'//,
     $       2X,' MAXIMUM ALLOWED TOTAL NUMBER OF ZONES = ',I2)
 1033 FORMAT(//,2X,' WRONG NUMBER. REPEAT THE CHOICE!!'//)
 1034 FORMAT(//,2X,' WRONG TOTAL ZONES NUMBER',/,
     $          2X,' MAXIMUM ALLOWED NUMBER '
     $          ,I2,//,3(2X,' REPEAT !!'),//)
C
      WRITE(IBLOC,5000)MOD,IOB
 5000 FORMAT(2A4)
C
      RETURN
      END
C**************************************************************************
      SUBROUTINE EXCYI2(IFUN,VAR,MX1,IV1,IV2,XYU,DATI,ID1,ID2,IBLOC1,   
     $                  IBLOC2,IER,CNXYU,TOL)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NZFMAX=6,NCELMAX=6)
      INTEGER VAR
      DIMENSION VAR(MX1,2),XYU(*),DATI(*),CNXYU(*),TOL(*)               
      DIMENSION TUBI(NCELMAX),DIAI(NCELMAX),HLU(NCELMAX)
      DIMENSION DZE(NCELMAX),CRIG(NCELMAX),NZON(NCELMAX)
      DIMENSION DIAE(NCELMAX),VOLM(NCELMAX),RAME(NCELMAX)
      DIMENSION SUP(NZFMAX,NCELMAX),TAUQ(NCELMAX) 
      DIMENSION SUPINT(NCELMAX)
      DIMENSION B(NCELMAX),D(NCELMAX),FDR(NCELMAX)
      CHARACTER*4 NT,DI,NL,NZ,NR,SP(3),PC,DE,RM,CAPM,CD,IS 
      CHARACTER*7 VM,FLGDR
      CHARACTER*4 SUPXES
      COMMON/AUSIL1/NSTATI,NUSCIT,NINGRE                                
      COMMON/NORM/P0,H0,T0,W0,RO0,AL0,V0,DP0                            
      DATA PIGR/3.1415926/                                              
      DATA NT/'NTUB'/,DI/'DIAI'/,NL/'LUNG'/,NZ/'DELZ'/,PC/'PACO'/        
      DATA NR/'CRIG'/,VM/'VOL.M.C'/,IS/'    '/,DE/'DIAE'/,RM/'ROM '/
      DATA CAPM/'CM  '/,CD/'COND'/SUPXES/'SUP.'/,FLGDR/'DRN_FLG'/
C                                                                       
      NCEL=NUSCIT/6
      NZFTOT=(NINGRE-5)/2.                                             
C                                                                       
      NN0=IV1-1                                                         
      NN1=NN0+NCEL                                                    
      NN2=NN1+NCEL                                                  
      NN3=NN2+NCEL 
      NN4=NN3+NCEL
      NN5=NN4+NCEL
      NEQ=NN5+NCEL                                          
C                                                                       
      GO TO (1,10),IFUN                                                 
C                                                                       
C-----SCRITTURA SIMBOLI DEI DATI                                        
C     
 1    CONTINUE
      WRITE(14,1010)
 1010 FORMAT('*   GENERAL DATA ',60X)
      WRITE(14,1011) PC,IS,RM,IS,CAPM,IS,CD,IS                                 
 1011 FORMAT(3(4X,2A4,' =',10X,'*'))
      DO 5 I=1,NCEL                                                     
         WRITE(14,1002)I                                                   
         WRITE(14,1003) NT,I,DI,I,DE,I,NL,I,NZ,I,NR,I
         WRITE(14,4000) VM,I,FLGDR,I
         WRITE(14,4001) (SUPXES,J,I,J=1,NZFMAX)        
    5 CONTINUE                                                          
 1001 FORMAT(4X,A4,I4,' =',10X,'*')
 1002 FORMAT('*   DATA FOR CELL ',I3,'*',55X)                        
 1003 FORMAT(3(4X,A4,I4,' =',10X,'*'),5X)      
 4000 FORMAT(3(4X,A,I1,' =',10X,'*'),5X)                         
 4001 FORMAT(3(4X,A,I1,' C',I1,' =',10X,'*'),5X)                         
C                                                                       
      RETURN                                                            
C                                                                       
C-----LETTURA DEI DATI                                                  
C                                                                       
   10 READ(14,1004)                                                     
      READ(14,1004)
      READ(14,1004) PACO,ROM,CM,COND
C                                                                       
      DO 15 I=1,NCEL                                                    
       READ(14,1004)                                                     
       READ(14,1004) TUBI(I) ,DIAI(I),DIAE(I),HLU(I),DZE(I),CRIG(I),           
     $               VOLM(I),FDR(I)
       READ(14,1004) (SUP(J,I),J=1,NZFMAX)            
   15 CONTINUE                                                          
 1004 FORMAT(3(14X,F10.0,1X),5X)                                        
C                
      IF (TUBI(1).EQ.0) THEN
	 WRITE(6,*) 'ERROR. SOME F14 DATA ARE MISSING!!'
         STOP
      ENDIF                                                  
      DO 21 I=2,NCEL                                                    
         IF(TUBI(I).GT.0) GOTO 21                                          
         TUBI(I)=TUBI(I-1)                                                 
         DIAI(I)=DIAI(I-1)                                                 
         DIAE(I)=DIAE(I-1)                                                 
         HLU(I)=HLU(I-1)                                                   
         DZE(I)=DZE(I-1)                                                   
         CRIG(I)=CRIG(I-1)                                                 
         VOLM(I)=VOLM(I-1)
         FDR(I)=FDR(I-1)
         SUPINT(I)=SUPINT(I-1)
         DO J=1,NZFMAX
	    SUP(J,I)=SUP(J,I-1)
         ENDDO
   21 CONTINUE      
C
      DO I=1,NCEL
	 SUPINT(I)=PIGR*DIAI(I)*HLU(I)*TUBI(I) !si assume una zona sola
	 IF (VOLM(I).EQ.0)
     &      VOLM(I)=PIGR*HLU(I)*TUBI(I)*
     &              (DIAE(I)**2-DIAI(I)**2)/4.0
         IF (SUP(1,I).EQ.0) THEN
	    SUP(1,I)=PIGR*DIAE(I)*HLU(I)*TUBI(I) !si assume una zona sola
            DO J=2,NZFMAX
               SUP(J,I)=0.
            ENDDO
         ENDIF
      ENDDO
C
      NZTASS=0.
      DO I=1,NCEL
         NZON(I)=0. 
      ENDDO
      DO I=1,NCEL
         DO J=1,NZFMAX
           IF(SUP(J,I).GT.0.) THEN
             NZON(I)=NZON(I)+1
             NZTASS = NZTASS+1
           END IF
         END DO
      END DO
      IF(NZTASS.NE.NZFTOT) THEN
         WRITE(6,222)NZTASS,NZFTOT
 222     FORMAT(3(5X,'---- ERROR ------',/),/,5X,
     $             '----------  OVERALL ASSIGNED SURFACES',
     $             ' NUMBER (',I2,') NOT COMPATIBLE WITH THE ONE',
     $             ' PROVIDED WITH TOPOLOGY (',I2,')  ----------')
         IER=1
         RETURN
      END IF
C
      DO I=1,NCEL   !calcolo raggi medi per strati equimassici
	 RAME(I)=SQRT(((DIAI(I)/2)**2+(DIAE(I)/2)**2)/2.0)
      ENDDO
      DO I=1,NCEL !calcolo coefficienti metallo
	 B(I)=2*PIGR*HLU(I)*TUBI(I)/
     &        ((1/COND)*ALOG(2*RAME(I)/DIAI(I)))
         D(I)=2*PIGR*HLU(I)*TUBI(I)/
     &        ((1/COND)*ALOG(DIAE(I)/(2*RAME(I))))
      ENDDO
C                                                       
C-----MEMORIZZAZIONE  DATI GEOMETRICI                                   
C                                                                       
      DATI(ID2)=NCEL                                                    
      DO I=1,NCEL
         DATI(ID2+I)=NZON(I)
      ENDDO                                                  
C           
      K=ID2+NCEL                                                            
      DO 25 I=1,NCEL                                                                                                      
       S=PIGR*DIAI(I)*HLU(I)*TUBI(I)                                     
       V=S*DIAI(I)/4.                                                    
       A=V/HLU(I)                                                        
       TAUQ(I)=HLU(I)/A
       DATI(K+1)=S                                                  
       DATI(K+2)=V                                                       
       DATI(K+3)=B(I)                                                  
       DATI(K+4)=A                                                       
       DATI(K+5)=DIAI(I)                                                 
       DATI(K+6)=D(I)                                                 
       DATI(K+7)=2.*HLU(I)/(DIAI(I)*A*A)                                 
       DATI(K+8)=DZE(I)*9.81                                             
       DATI(K+9)=CRIG(I)                                                 
       DO J=1,NZON(I)
	  DATI(K+9+J)=SUP(J,I)
       ENDDO
       K=K+9+NZON(I)
   25 CONTINUE                                                          
C
       ID2=ID2+10*NCEL+NZFTOT
       DATI(ID2+1)=PACO                                          
       ID2=ID2+1
C
C INCREMENTO DI ID2 DOPO MEMORIZZAZIONE DI TAU2H,TAU1H,TAU2P,TAU1P IN EXCYTAU
      ID2 = ID2+4*NCEL                                               
C INCREMENTO DI ID2 DOPO MEMORIZZAZIONE DI GAMMA(NCEL) IN EXCYRES
      ID2 = ID2+NCEL
C---- MEMORIZZAZIONE PRESSIONI ED ENTALPIE DEL PASSO DI TEMPO PRECEDENTE
      DO I=1,NCEL+1
        DATI(ID2+I)=0.
      ENDDO
      DO I=1,NCEL
        DATI(ID2+NCEL+1+I)=0.
      ENDDO
      ID2 = ID2+2*NCEL+1
C---- MEMORIZZAZIONE DH , DR E RO ( TERMINI DI DRIFT )
      DO I=1,NCEL+1
        DATI(ID2+I)=0.
        DATI(ID2+NCEL+1+I)=0.
        DATI(ID2+2*NCEL+2+I)=0.
      ENDDO
      ID2 = ID2+3*NCEL+3
C---- MEMORIZZAZIONE DEL MOLTIPLICATORE D'ATTRITO FIQLO(NCEL+1)
      DO I=1,NCEL+1
        DATI(ID2+I)=1.
      ENDDO
      ID2 = ID2+NCEL+1
C---- MEMORIZZAZIONE CAPACITA' TERMICA METALLO
      DO I=1,NCEL
	 DATI(ID2+I)=ROM*VOLM(I)*CM
      ENDDO         
      ID2=ID2+NCEL
C---- MEMORIZZAZIONE REGISTRO A SCORRIMENTO TM(I)
      DO I=1,2*NCEL
	 DATI(ID2+I)=0.
      ENDDO
      ID2=ID2+2*NCEL
C---- MEMORIZZAZIONE FLAG PER DRENAGGIO CONDENSA
       DO I=1,NCEL
         DATI(ID2+I)=FDR(I)
       ENDDO                                                                                                      
       ID2=ID2+NCEL
C$$$SPEL
C      WRITE(6,*)' EXCYI2 DATA '
C      DO I=ID1,ID2
C      WRITE(6,*)I,DATI(I)
C      ENDDO
C      WRITE(6,*)'   ******* END OF EXCYI2 DATA'
C$$$SPEL
C                             
C-----COSTANTI DI NORMALIZZAZIONE                                       
C                                                                       
C---- USCITE
      DO 35 I=1,NCEL                                                    
       CNXYU(NN0+I)=H0                                                   
       CNXYU(NN1+I)=P0                                                   
       CNXYU(NN2+I)=W0                                                   
       CNXYU(NN3+I)=W0*H0                                                   
       CNXYU(NN4+I)=H0   
       CNXYU(NN5+I)=T0                                                 
C                                                                      
C---- INGRESSI                                                         
       CNXYU(NEQ+1)=H0                                                   
       CNXYU(NEQ+2)=P0                                                   
       CNXYU(NEQ+3)=P0                                                   
       CNXYU(NEQ+4)=H0                                                   
       CNXYU(NEQ+5)=1.
 35   CONTINUE
C
      CNXYU(NN2)=W0
C	                                                   
      K=1.
      DO J=1,NZFTOT
         CNXYU(NEQ+5+K)=T0
         CNXYU(NEQ+5+NZFTOT+K)=1000.
         K=K+1
      ENDDO
C                                                                       
C-----STAMPE                                                            
C                                                                       
      WRITE(6,3000)                                                     
C                                                                       
      K=ID1+NCEL                                                  
      DO 60 I=1,NCEL                                                    
      V= DATI(K+2) 
      A= DATI(K+4)                                                      
      DD=DATI(K+5)                                                       
      C=DATI(K+8)/9.81                                                       
      SPE=0.
      DO J=1,NZON(I)
	  SPE=DATI(K+9+J)+SPE
      ENDDO
      K=K+9+NZON(I)
      WRITE(6,3001) I,V,A,DD,C,SPE,SUPINT(I)
   60 CONTINUE                                                          
C                                                                       
C*****
      WRITE(6,'(/)')
      IF(PACO.EQ.1)
     & WRITE(6,*) '   *****  EXCY  -  ZUBER_DIX correlation *****'
      IF(PACO.EQ.2)
     & WRITE(6,*) '   *****  EXCY  -  BANKOFF correlation *****'
      IF(PACO.EQ.3)
     & WRITE(6,*)'  ***  EXCY  -  CHEXAL_LELLOUCHE correlation ***'
      IF(PACO.EQ.4)
     & WRITE(6,*) '   ***  EXCY  -  ZUBER-ROUHANY correlation ***'
      IF(PACO.EQ.0)
     & WRITE(6,*) '   *****  EXCY  -  Omogeneous Model  *****'
C
      RETURN                                                            
 3000 FORMAT(6X,'CELLA',4X,'VOLUME      SECTION     ',      
     $           'INT.DIAM.  HEIGHT DIFF.  EXT.SURFACE  INT.SURFACE'//)                             
 3001 FORMAT(6X,I3,5X,6(E11.4,1X)/)                                     
 3010 FORMAT(6X,3E11.4/)                                                
      END                                                               
C**************************************************************************
      SUBROUTINE EXCYC1(IFUN,AJAC,MX5,IXYU,XYU,IPD,DATI,RNI,IBLOC1,     
     $                  IBLOC2)                                         
C$$$$$     !!!!!!! INIZIO ISTRUZIONI PER SCCS !!!!!!!
       CHARACTER*100 SccsID
       DATA SccsID/'%W%\t %I%\t %G% Puerpro libut'/
C$$$$$     !!!!!!! FINE ISTRUZIONI PER SCCS !!!!!!!
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NZFMAX=6,NCELMAX=6)
      DIMENSION AJAC(MX5,*),XYU(*),DATI(*),RNI(*)                       
      CHARACTER*4 IBLOC1,IBLOC2,IBLOX1,IBLOX2
      COMMON/EXCY03/CF,PACO,NCEL,NZFTOT,NZON(NCELMAX),NEQ 
      COMMON/EXCY04/H(NCELMAX+1),P(NCELMAX+1),Q(NCELMAX+1),
     $              RO(NCELMAX+1),PN(NCELMAX+1),
     $              HN(NCELMAX+1),HI,HUINV
      COMMON/EXCY05/HM(NCELMAX),TF(NCELMAX),ROM(NCELMAX),
     $            DRDH(NCELMAX),DRDP(NCELMAX),GAMMA(NCELMAX),  
     $            SM(NCELMAX),TITOL(NCELMAX),QTI(NCELMAX),
     $            TPE(NCELMAX),TFL(NZFMAX,NCELMAX),
     $            GE(NZFMAX,NCELMAX)
      COMMON/EXCY06/V(NCELMAX),B(NCELMAX),AREA(NCELMAX),DIAI(NCELMAX),
     $              SUP(NZFMAX,NCELMAX),CKF(NCELMAX),DZG(NCELMAX),
     $              CRIG(NCELMAX),SS(NCELMAX),D(NCELMAX),CM(NCELMAX)             
      COMMON/EXCY07/TAU1H(NCELMAX),TAU2H(NCELMAX),TAU1P(NCELMAX),
     $              TAU2P(NCELMAX),TAU3(NCELMAX)    
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0                             
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT                                         
      COMMON/REGIME/KREGIM
      COMMON/EXCY11/ALF0(NCELMAX+1),SL(NCELMAX+1),C00(NCELMAX+1),
     $             VGJ0(NCELMAX+1),FLU(NCELMAX+1)            
      COMMON/EXCY08/DR(NCELMAX+1),DH(NCELMAX+1),HT(NCELMAX+1)      
      COMMON/EXCY10/IBLOX1,IBLOX2
      LOGICAL KREGIM                                         
C
      NCEL=DATI(IPD)
      DO I=1,NCEL                                                    
         NZON(I)=DATI(IPD+I)
      ENDDO                                                  
C
      NZFTOT=0.
      DO I=1,NCEL
	 NZFTOT=NZFTOT+NZON(I)
      ENDDO
      NEQ=6*NCEL                                          
      NVAR=6*NCEL+2*NZFTOT+5                                              
C                                                                       
      GO TO (10,30,60),IFUN                                             
C                                                                       
C                                                                       
C      TOPOLOGIA JACOBIANO                                             
C      (TUTTO PIENO)                                                    
C                                                                       
   10 DO 12 I=1,NEQ                                                     
         DO 12 J=1,NVAR                                                    
            AJAC(I,J)=1.                                                      
   12 CONTINUE                                                          
      RETURN                                                            
C                                                                       
C-----DECODIFICA VARIABILI E DATI                                       
C                                                                       
   30 CALL EXCYDEC (XYU,IXYU,DATI,IPD,IFUN)                              
C                                                                       
C-----CALCOLO COEFFICIENTI DERIVATE H,P                                 
C                                                                       
      CALL EXCYTAU(IFUN,DATI,IPD)                                                       
C                                                                       
C-----CALCOLO DEI RESIDUI                                               
C                                                                       
      IBLOX1=IBLOC1 !indicatori per stampe di controllo
      IBLOX2=IBLOC2
C
      CALL EXCYRES (IFUN,RNI,DATI,IPD)                                 
C
      RETURN
C                                                                       
 60   CALL EXCYJC(AJAC,MX5,IXYU,XYU,DATI,IPD,RNI,IFUN)                                                                                       
      RETURN                                                            
      END                                                               
C**************************************************************************
      SUBROUTINE EXCYJC(AJAC,MX5,IXYU,XYU,DATI,IPD,RNI,IFUN)            
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION RNI(*),AJAC(MX5,*),DATI(*),XYU(*)        
      PARAMETER (NZFMAX=6,NCELMAX=6,NZTMAX=32)
      DIMENSION G1(6*NCELMAX),G2(6*NCELMAX),VAR(6*NCELMAX+2*NZTMAX+5)
      COMMON/EXCY03/CF,PACO,NCEL,NZFTOT,NZON(NCELMAX),NEQ                         
      COMMON/EXCY04/H(NCELMAX+1),P(NCELMAX+1),Q(NCELMAX+1),
     $              RO(NCELMAX+1),PN(NCELMAX+1),HN(NCELMAX+1),HI,
     $              HUINV
      COMMON/EXCY07/TAU1H(NCELMAX),TAU2H(NCELMAX),TAU1P(NCELMAX),
     $              TAU2P(NCELMAX),TAU3(NCELMAX)    
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0                             
      COMMON/REGIME/KREGIM
      LOGICAL KREGIM
C                                                                       
C*** CALCOLO JACOBIANO NUMERICO                                          
C                                                                
      NSTATI=0
      NEQ=6*NCEL                                               
      NVAR=6*NCEL+2*NZFTOT+5                                              
C                                                                       
      CALL EXCYDEC(XYU,IXYU,DATI,IPD,IFUN)                                  
C                                                                       
      CALL EXCYTAU(IFUN,DATI,IPD)                                                       
C
      CALL EXCYRES (IFUN,G1,DATI,IPD)
C                                                                       
      DO J=1,NEQ                                                     
      IF(J.GT.NSTATI) THEN
       G1(J)=-G1(J)                                       
      ENDIF
      ENDDO
C
      EPSPLIM=50./P0
      EPSLIM=1.E-4
      DO 30 I=1,NVAR                                                    
      EPS=XYU(IXYU+I-1)*1.E-3                                           
      IF(I.GT.NCEL.AND.I.LE.2*NCEL.OR.I.EQ.NEQ+2)THEN
        IF(ABS(EPS).LT.EPSPLIM)EPS=EPSPLIM
      ELSE 
        IF(ABS(EPS).LT.EPSLIM)EPS=EPSLIM
      ENDIF
C                                                                       
      DO 15 J=1,NVAR                                                    
      VAR(J)=XYU(IXYU+J-1)                                              
      IF(J.EQ.I)VAR(J)=VAR(J)+EPS                                       
   15 CONTINUE                                                          
C                                                                       
      CALL EXCYDEC(VAR,1,DATI,IPD,IFUN)                                  
C                                                                       
      CALL EXCYRES (IFUN,G2,DATI,IPD)
C                                                                       
      DO 45 J=1,NEQ                                                     
      IF(J.GT.NSTATI) THEN
       G2(J)=-G2(J)                                       
      ENDIF
      AJAC(J,I)=(G2(J)-G1(J))/EPS                                      
   45 CONTINUE                                                          
C
   30 CONTINUE                                                          
C
      RETURN                                                            
      END           
C**************************************************************************    
      SUBROUTINE EXCYRES (IFUN,RNI,DATI,IPD)                      
C                                                                       
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NZFMAX=6,NCELMAX=6)
      PARAMETER (PI=3.14159)
      PARAMETER (GAMIN=5.)   !parametro di saturazione del valore di GAMMA(I)
      PARAMETER (WEIGHT=0.5) !coeff. pesatura portate estreme cella eq. momento
      PARAMETER (UMIN=0.01) !valore limite per calcolare G (protezione da G=0)
      PARAMETER (NSTILL=0) !parametro per calcolare stazion. semplif. a fermo 
      DIMENSION RNI(*),DATI(*)                                    
      REAL TM(NCELMAX),TMN(NCELMAX),QTE(NCELMAX)
      REAL TPI(NCELMAX),FM(NCELMAX),F(6*NCELMAX)
      COMMON/EXCY03/CF,PACO,NCEL,NZFTOT,NZON(NCELMAX),NEQ
      COMMON/EXCY04/H(NCELMAX+1),P(NCELMAX+1),Q(NCELMAX+1),
     $              RO(NCELMAX+1),PN(NCELMAX+1),HN(NCELMAX+1),
     $              HI,HUINV                         
      COMMON/EXCY05/HM(NCELMAX),TF(NCELMAX),ROM(NCELMAX),
     $            DRDH(NCELMAX),DRDP(NCELMAX),GAMMA(NCELMAX),
     $            SM(NCELMAX),TITOL(NCELMAX),QTI(NCELMAX),
     $            TPE(NCELMAX),TFL(NZFMAX,NCELMAX),
     $            GE(NZFMAX,NCELMAX)
      COMMON/EXCY06/V(NCELMAX),B(NCELMAX),AREA(NCELMAX),
     $              DIAI(NCELMAX),SUP(NZFMAX,NCELMAX),CKF(NCELMAX),
     $              DZG(NCELMAX),CRIG(NCELMAX),SS(NCELMAX),
     $              D(NCELMAX),CM(NCELMAX)             
      COMMON/EXCY07/TAU1H(NCELMAX),TAU2H(NCELMAX),TAU1P(NCELMAX),
     $              TAU2P(NCELMAX),TAU3(NCELMAX)    
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0                             
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT                                         
      COMMON/EXCY08/DR(NCELMAX+1),DH(NCELMAX+1),HT(NCELMAX+1)
      COMMON/EXCY09/FIQLO(NCELMAX+1),ROLS(NCELMAX+1)
      COMMON/EXCY10/IBLOX1,IBLOX2
      COMMON/REGIME/KREGIM                                              
      COMMON/CEL01/ NTCEL,IVER,ICEL                                     
      CHARACTER*4 IBLOX1,IBLOX2
      LOGICAL KREGIM
C--------------------------------------------------------------------------
C       IL VALORE DI IGAM (INTERO) SERVE PER CALCOLARE O MENO
C       IL COEFFICIENTE DI SCAMBIO CON LA SUB. GAM01 :                    
C       SE IGAM =0  NON SI CALCOLA                                      
C       SE IGAM >0   SI CALCOLA                                         
C                                                                          
      IGAM=EXCYG9(IFUN)                                                 
C--------------------------------------------------------------------------
      NNN=NCEL+1                                                        
      NN2=2*NCEL                                                        
      NN3=NN2+NCEL
      NN4=NN3+NCEL
      NN5=NN4+NCEL
C
C---- PASST DI INTEGRAZIONE
      DELTAT=DTINT
      IF(DELTAT.EQ.0.)DELTAT=1.
         KK=IPD+14*NCEL+NZFTOT+1
         DO I=1,NCEL                                                    
            GAMMA(I)=DATI(KK+I)
            IF(CRIG(I).EQ.30.) THEN
               PMI=(P(I)+P(I+1))/2.
               GMIN=UMIN*ROEV(PMI,SHEV(PMI,HM(I),1),1)
               G=AMAX1(GMIN,ABS(Q(I))/AREA(I)) !protezione da G=0
               GAMMA(I)=DATI(KK+I)*G**(0.8)        
            END IF
         ENDDO                                                         
C
C-------- CALCOLO RESIDUI METALLO (FM), TEMPERATURA PARETE INTERNA (TPI)
C                 E POTENZA SCAMBIATA ATTRAVERSO PARETE ESTERNA (QTE)
C
      CALL EXCYMET(TM,TMN,TPI,QTE,FM,DATI,IPD,IFUN,DELTAT)
C                                                                       
C-------- RIPRISTINO DEL COEFF. DI SCAMBIO PRESO DAL VETTORE DATI       
C                                                                       
         NTCEL=NCEL
         IF(IGAM.EQ.0) GOTO 9
C**********************************************************
C
C___ CALCOLO COEFFICIENTI DI SCAMBIO
C
C**********************************************************
C                                                                       
C  IVER= 1 ===> NELLA GAM01 SI FA IL TEST DI CRISI DALL'ULTIMA CELLA    
C  IVER=-1 ===> NELLA GAM01 SI FA IL TEST DI CRISI DALLA PRIMA CELLA    
C  IVER=-2 ===> NELLA GAM01 SI FA IL TEST DI CRISI SU TUTTE LE CELLE,   
C               A PARTIRE DALLA PRIMA 
C                                  
C******************TABELLA DEI SIGNIFICATI DI CRIG*****************************
C  CRIG<0  => chiamata alla routine utente EXCYGAMUT
C  CRIG=0  => utilizzo correlazioni semplificate (EXCYGTERT)
C  CRIG>0 and CRIG<10 => GAM01, tubo liscio, CRIG moltiplicativo coeff. scambio
C  CRIG>10 and CRIG<20 => GAM01, tubo rigato, CRIG moltiplicativo coeff. scambio
C  CRIG=20 => coeff. scambio costante pari a 50000 (bollente)  
C  CRIG=30 => coeff. scambio convettivo (dipendente da portata)
C  CRIG>30 => coeff. scambio costante pari al valore di CRIG 
C****************************************************************************** 
C
       DO 7 K=1,NCEL                                                    
           IF ((Q(1).GT.0.).AND.(Q(NCEL).GT.0.)) THEN                      
         IVER=1                                                            
         I=NCEL-K+1                                                        
           ELSE IF ((Q(1).LT.0.).AND.(Q(NCEL).LT.0.)) THEN                 
         IVER=-1                                                           
         I=K                                                               
           ELSE                                                            
         IVER=-2                                                           
         I=K                                                               
           END IF                                                          
         ICEL=I                                                            
C
         PMI=(P(I)+P(I+1))/2.
         GMIN=UMIN*ROEV(PMI,SHEV(PMI,HM(I),1),1)
         G=AMAX1(GMIN,ABS(Q(I))/AREA(I)) !protezione da G=0
C
         IF (CRIG(I).EQ.0.) THEN !routine correlazioni semplificate
         CALL EXCYGTERT(PMI,HM(I),SM(I),TF(I),ROM(I),TITOL(I),
     $           TPI(I),DIAI(I),CRIG(I),G,QTI(I),SS(I),GAMMA(I))
         ELSE IF (CRIG(I).LT.0.) THEN ! routine utente
            CALL EXCYGAMUT(PMI,HM(I),SM(I),TF(I),ROM(I),TITOL(I), 
     $           TPI(I),DIAI(I),CRIG(I),G,QTI(I),SS(I),GAMMA(I))        
         ELSE IF (CRIG(I).EQ.20.) THEN ! coefficiente costante (caso bollente)
            GAMMA(I)=50000.
         ELSE IF (CRIG(I).EQ.30.) THEN ! coeff. dipendente solo da portata G
            IF(KREGIM) THEN
              CRI=0.
              CALL GAM01(PMI,HM(I),SM(I),TF(I),ROM(I),TITOL(I),         
     $           TPI(I),DIAI(I),CRI,G,QTI(I),SS(I),GAMMA(I))        
            END IF
         ELSE IF (CRIG(I).GT.30.) THEN ! coefficiente costante
           GAMMA(I)=CRIG(I)
         ELSE ! generico set di correlazioni
           CALL GAM01(PMI,HM(I),SM(I),TF(I),ROM(I),TITOL(I),
     $           TPI(I),DIAI(I),CRIG(I),G,QTI(I),SS(I),GAMMA(I))
         ENDIF
C
    7  CONTINUE
C
C-------- STAMPE DI CONTROLLO
C
       IF (KREGIM.AND.IFUN.EQ.2.)THEN
          WRITE(6,*)
          WRITE(6,*)
          WRITE(6,*)'BLOCCO =',IBLOX1,IBLOX2
              WRITE(6,1928)(I,GAMMA(I),I=1,NCEL)
       ENDIF
1928   FORMAT(/20X,5('GAMMA =(',I2,')',F12.3:10X))
C                                                                       
C-------- SALVATAGGIO DEL COEFF. DI SCAMBIO NEL VETTORE DATI            
C                                                                       
         KK=IPD+14*NCEL+NZFTOT+1
         DO 6 I=1,NCEL                                                    
            IF(KREGIM) GOTO 30
            IF(CRIG(I).EQ.30.)GOTO 6
            GAMMA(I)=(DATI(KK+I)+CDT/ALFADT/2.*GAMMA(I))
     $               /(1.+CDT/ALFADT/2.)
            DATI(KK+I)=GAMMA(I)
            GOTO 6
   30       IF(CRIG(I).EQ.30.) THEN
               PMI=(P(I)+P(I+1))/2.
               GMIN=UMIN*ROEV(PMI,SHEV(PMI,HM(I),1),1)
               G=AMAX1(GMIN,ABS(Q(I))/AREA(I)) !protezione da G=0
               DATI(KK+I)=GAMMA(I)/(G**(0.8))        
            ELSE
               DATI(KK+I)=GAMMA(I)
            ENDIF
    6    CONTINUE                                                          
    9 CONTINUE                                                          
C                                                                       
C-----CALCOLO SECONDO MEMBRO EQUAZIONI DIFFERENZIALI                    
C
C 1) EQQ. SCAMBI TERMICI ==> NCEL                                      
C 2) EQU. ENERGIA        ==> NCEL                                           
C 3) EQU. MOMENTO        ==> NCEL
C 4) EQU. CONTINUITA'    ==> NCEL
C 5) EQU. METALLO        ==> NCEL                                              
C                                                                       
      DO 20 I=1,NCEL
C
C---- DETERMINAZIONE DEL VERSO DEL FLUSSO DI MASSA
C
        IF(Q(I).GE.0.) THEN
           IF (I.EQ.1.) THEN
              H1=HI
           ELSE
              H1=HM(I-1)
           ENDIF
        ELSE
           H1=HM(I)
        ENDIF
C
        IF (Q(I+1).LE.0) THEN
           IF (I.EQ.NCEL) THEN
              H2=HUINV
           ELSE
              H2=HM(I+1)
           ENDIF
        ELSE
           H2=HM(I)
        ENDIF
C
           DEH=DH(I)
           DUH=DH(I+1)
C
C---- PROTEZIONE DA VALORI DI GAMMA(I) NEGATIVI O MINORI DI GAMIN
        IGAMMA=1          !variabile di lock sulla saturazione di GAMMA(I)
        IF(IGAMMA.NE.0.AND.GAMMA(I).LT.GAMIN) GAMMA(I)=GAMIN
C
C---- CALCOLO FUNZIONALI EQUAZIONI POTENZE SCAMBIATE                  
        F(NN3+I)=QTI(I)-GAMMA(I)*SS(I)*(TPI(I)-TF(I))
        CMOLT2=1.
        TFC=TF(I)-273.
        IF(TFC.LT.170.) CMOLT2=-0.058*TFC+10.937
        IF(KREGIM) THEN
C******************************************** Calcolo regime
C---- CALCOLO FUNZIONALI EQUAZIONI ENERGIA 
        F(I) =Q(I)*H1-Q(I+1)*H2
     $         - HM(I)*(Q(I)-Q(I+1))
     $         + DEH - DUH + QTI(I)
        IF(ABS(Q(I)).LT.1.E-3.AND.NSTILL.EQ.1) THEN
           IF(P(I).LT.221.1E+05)THEN
              CALL SATUR(P(I),7,TSAT,ZOT,1)
           ELSE
              CALL SATUR(221.1E+05,7,TSAT,ZOT,1)
           ENDIF
           F(I)=HM(I)-HEV(P(I),ENTROP(P(I),TPE(I),TSAT,1),1)
        ENDIF
C____ CALCOLO EQUAZIONE DEL MOMENTO
        F(NCEL+I)= -P(I+1)+P(I)+DR(I)-DR(I+1)-ROM(I)*DZG(I)
     &           -CKF(I)*CF*FIQLO(I+1)*Q(I)*ABS(Q(I))/ROLS(I)
     &           -CMOLT2*CKF(I)*AREA(I)*CF*Q(I)/10.
C
C____ CALCOLO EQUAZIONE CONTINUITA`
        F(2*NCEL+I)=Q(I)-Q(I+1)                                             
C
      ELSE
       DELTAP=P(I+1)-PN(I+1)
       DELTAH=HM(I)-HN(I)
C******************************************** Calcolo transitorio
       PMIN=1.E+05
       SPREC=SHEV(PN(I+1),HN(I),1)
       SNEW=SHEV(P(I+1),HM(I),1)
       TITPREC=YEV(PN(I+1),SPREC,1)
       ROPREC=ROEV(PN(I+1),SPREC,1)
       RONEW=ROEV(P(I+1),SNEW,1)
       TAUPREC=ROPREC*V(I)/W0
       TAUCOND=5.
       QCOND=0.
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
C   MODIFICA PER LA GESTIONE DEL DRAINFLAG
C   27/06/97
C
       IF(DATI(IPD+24*NCEL+NZFTOT+6+I).EQ.0.) THEN
          DATI(IPD+24*NCEL+NZFTOT+6+I) = 0.
       ELSE IF (P(I+1).GT.5.5E5) THEN
          DATI(IPD+24*NCEL+NZFTOT+6+I) = -1.
       ELSE IF (P(I+1).LT.1.E5) THEN
          DATI(IPD+24*NCEL+NZFTOT+6+I) = 1.
       ENDIF
       DRAINFLAG=DATI(IPD+24*NCEL+NZFTOT+6+I)
C
C   FINE MODIFICA
C$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
C
C      
CCC    if(IBLOX2.eq.'HEXB'.and.itert.eq.0.and.ifun.eq.2)then
CCC     write(6,*)'blocco=',IBLOX2
CCC     write(6,*)'DRAINFLAG=',DRAINFLAG
CCC     write(6,*)'ROPREC=',ROPREC
CCC     write(6,*)'V(I)=',V(I)
CCC     write(6,*)'TAUPREC=',TAUPREC
CCC     write(6,*)'DELTAT=',DELTAT
CCC    endif
       IF(P(I+1).LT.221.1E+05)THEN
           CALL SATUR(P(I+1),2,HHLS,HHVS,1)
       ELSE
           CALL SATUR(221.1E+05,2,HHLS,HHVS,1)
       ENDIF
       IF(DRAINFLAG.GT.0.)THEN
         QCOND=ROPREC*V(I)*(1.-TITPREC)/TAUCOND
       ENDIF
C_____ CALCOLO EQUAZIONE ENERGIA
CCC   IF(TAUPREC.GT.DELTAT)THEN
CCC        F(I) =(Q(I)*H1-Q(I+1)*H2
CCC  $            - HM(I)*(Q(I)-Q(I+1))
CCC  $            + DEH - DUH + QTI(I) ) * DELTAT            
CCC  $           - TAU1P(I)*DELTAP - TAU1H(I)*DELTAH
CCC  $           - QCOND*HHLS* DELTAT
CCC   ELSE
           F(I) =(Q(I)*H1-Q(I+1)*H2
     $            - HM(I)*(Q(I)-Q(I+1))
     $            + DEH-DUH+QTI(I))*DELTAT/TAU1H(I)      
     $           - TAU1P(I)/TAU1H(I)*DELTAP - DELTAH
     $           - QCOND*HHLS*DELTAT/TAU1H(I)
CCC   ENDIF
C
C____ CALCOLO EQUAZIONE DEL MOMENTO
        F(NCEL+I)= -P(I+1)+P(I)+DR(I)-DR(I+1)-ROM(I)*DZG(I)
     &           -CKF(I)*CF*FIQLO(I+1)*Q(I)*ABS(Q(I))/ROLS(I)
     &           -CMOLT2*CKF(I)*AREA(I)*CF*Q(I)/10.
C____ CALCOLO EQUAZIONE CONTINUITA`
      IF(PN(I+1).GT.PMIN)THEN
        F(NN2+I)=(Q(I)-Q(I+1))*DELTAT - TAU2P(I)*DELTAP-TAU2H(I)*DELTAH
     $    -QCOND*DELTAT
      ELSE
        F(NN2+I)=Q(I)-Q(I+1)-V(I)*(RONEW-ROPREC)/DELTAT
     $    -QCOND
      ENDIF
      ENDIF
   20 CONTINUE
C
      DO 23 I=1,NCEL                                                    
C---- RESIDUI EQUAZIONI ENERGIA (--> ENTALPIE MEDIE STATICHE DI CELLA)
        IF(KREGIM)THEN
CC      IF(KREGIM.OR.(TAUPREC.GT.DELTAT))THEN
        RNI(I)=F(I)/W0/H0
      ELSE
C       IF(TAUPREC.GT.DELTAT)THEN
C         RNI(I)=F(I)/W0/H0
C       ELSE
          RNI(I)=F(I)/H0
C       ENDIF
      ENDIF
C---- RESIDUI EQUAZIONI MOMENTO (--> PRESSIONI USCITA CELLA)
C
      RNI(NCEL+I) =F(NCEL+I)/P0                                                
C
C---- RESIDUI EQUAZIONI CONTINUITA' (--> PORTATE INGRESSO CELLA) 
C
        RNI(NN2+I)  =F(NN2+I)/W0                                             
C
C---- RESIDUI EQUAZIONI SCAMBIO TERMICO (--> POTENZE SCAMBIATE)            
      RNI(NN3+I) =F(NN3+I)/W0/H0
C
C-----CALCOLO RESIDUO EQUAZIONE ENTALPIA TOTALE DI USCITA                       
      IF(Q(I+1).GT.0.) THEN
      RNI(NN4+I)=(Q(I+1)*(HT(I+1)-HM(I))-DH(I+1))/W0/H0
      ELSE
      RNI(NN4+I)=(HT(I+1)-HM(I))/H0
      ENDIF
C
C---- RESIDUO METALLO
      IF(KREGIM)THEN
        RNI(NN5+I)=FM(I)/(W0*H0)
      ELSE
        RNI(NN5+I)=FM(I)/T0
      ENDIF
  23  CONTINUE
C                                                                       
C____ IN STAZIONARIO SI MEMORIZZANO LE PRESSIONI E LE ENTALPIE NEL VETTORE DATI
C
      IF(KREGIM) THEN
       KS=IPD+15*NCEL+NZFTOT+1
       DO I=1,NCEL+1
       DATI(KS+I)=P(I)
       ENDDO
       DO I=1,NCEL
       DATI(KS+NCEL+1+I)=HM(I)
       ENDDO
      ENDIF
      RETURN                                                            
      END
C**************************************************************************
      SUBROUTINE EXCYDEC(XYU,IXYU,DATI,IPD,IFUN)                         
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION XYU(*),DATI(*)                                          
      PARAMETER (NZFMAX=6,NCELMAX=6)
      COMMON/EXCY03/CF,PACO,NCEL,NZFTOT,NZON(NCELMAX),NEQ                         
      COMMON/EXCY04/H(NCELMAX+1),P(NCELMAX+1),Q(NCELMAX+1),
     $              RO(NCELMAX+1),PN(NCELMAX+1),HN(NCELMAX+1),
     $              HI,HUINV
      COMMON/EXCY05/HM(NCELMAX),TF(NCELMAX),ROM(NCELMAX),
     $            DRDH(NCELMAX),DRDP(NCELMAX),GAMMA(NCELMAX),
     $            SM(NCELMAX),TITOL(NCELMAX),QTI(NCELMAX),
     $            TPE(NCELMAX),TFL(NZFMAX,NCELMAX),
     $            GE(NZFMAX,NCELMAX)
      COMMON/EXCY06/V(NCELMAX),B(NCELMAX),AREA(NCELMAX),
     $              DIAI(NCELMAX),SUP(NZFMAX,NCELMAX),
     $              CKF(NCELMAX),DZG(NCELMAX),CRIG(NCELMAX),
     $              SS(NCELMAX),D(NCELMAX),CM(NCELMAX)             
      COMMON/EXCY07/TAU1H(NCELMAX),TAU2H(NCELMAX),TAU1P(NCELMAX),
     $              TAU2P(NCELMAX),TAU3(NCELMAX)    
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0                             
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT                                         
      COMMON/REGIME/KREGIM                                              
      COMMON/EXCY08/DR(NCELMAX+1),DH(NCELMAX+1),HT(NCELMAX+1)
      COMMON/EXCY11/ALF0(NCELMAX+1),SL(NCELMAX+1),C00(NCELMAX+1),
     $             VGJ0(NCELMAX+1),FLU(NCELMAX+1)            
      COMMON/EXCY09/FIQLO(NCELMAX+1),ROLS(NCELMAX+1)
C
      COMMON/TOLEG00/TOLIN(100)
C
      LOGICAL KREGIM                                                  
      DATA PCRIT /2.212E+07/
C                                                                       
C$$$SPEL
C       IF(IFUN.EQ.2) THEN
C      WRITE(6,*)'   ************ EXCYDEC'
C      NPD=IPD+24*NCEL+NZFTOT+7
C      DO I=IPD,NPD
C      WRITE(6,*)I,DATI(I)
C      ENDDO
C      WRITE(6,*)'   ************* END  EXCYDEC'
C       ENDIF
C$$$SPEL
      NFL=1                                                             
      NNN=NCEL+1                                                        
C                                                                       
C        DATI                                                           
C
      K3=IPD+NCEL                                                                       
      DO 10 I=1,NCEL                                                    
       SS(I)=DATI(K3+1)                                                 
       V(I)=DATI(K3+2)                                                   
       B(I)=DATI(K3+3)                                                 
       AREA(I)=DATI(K3+4)                                                
       DIAI(I)=DATI(K3+5)
       D(I)=DATI(K3+6)                                                
       CKF(I)=DATI(K3+7)                                                 
       DZG(I)=DATI(K3+8)                                                 
       CRIG(I)=DATI(K3+9)
       K3=K3+9
       DO J=1,NZON(I)
	  SUP(J,I)=DATI(K3+J)
       ENDDO                                                
       K3=K3+NZON(I)
   10 CONTINUE                                                          
      KD=K3 
      PACO=DATI(KD+1)
      DO I=1,NCEL
	 CM(I)=DATI(IPD+21*NCEL+NZFTOT+6+I)
      ENDDO                                   
C
C     DECODIFICO I TERMINI DI DRIFT
C
C       KS=IPD+17*NCEL+NZFTOT+2
C       DO I=1,NCEL+1
C        DH(I)=DATI(KS+I)
C        DR(I)=DATI(KS+NCEL+1+I)
C        RO(I)=DATI(KS+2*NCEL+2+I)
C       ENDDO
C
C        VARIABILI ESTREME                                              
C                                        
      HI    =XYU(IXYU+NEQ  )*H0                                                
      P(1)  =XYU(IXYU+NEQ+1)*P0                                              
      P(NNN)=XYU(IXYU+NEQ+2)*P0                                              
      Q(1)  =XYU(IXYU+2*NCEL-1)*W0                                            
      Q(NNN)=XYU(IXYU+3*NCEL-1)*W0                                            
      HUINV =XYU(IXYU+NEQ+3)*H0                                                
      CF    =XYU(IXYU+NEQ+4)*1.                                      
      HT(1) =HI
      H(1)  =HI
C
C     DEFINIZIONE DELLA TOLLERANZA PER L'EQUAZIONE DI CONTINUITA`
C
      WW=(ABS(Q(NNN))+ABS(Q(1)))/2.
      IF(WW.GT.1000.)WW=1000.
      IF(WW.LT.0.1)WW=0.1
      DELTAT=DTINT
      IF(DELTAT.LE.0.)DELTAT=1.
      WWTOL=WW*.01*DELTAT/W0
      IF(WWTOL.LT.1.E-06)WWTOL=1.E-06
C
C     DEFINIZIONE DELLA TOLLERANZA PER L'EQUAZIONE DEL MOMENTO
C
      PPTOL=50./P0
C                                                                      
      NN0=IXYU-1                                                         
      NN1=NN0+NCEL                                                        
      NN2=NN1+NCEL                                                        
      NN3=NN2+NCEL                                                        
      NN4=NN3+NCEL            
      NN5=NN4+NCEL
      NN6=NN5+NCEL+4                                                       
C
C        VARIABILI INTERNE
C
      DO 61 I=1,NCEL-1                                                                                                 
       P(I+1) = XYU(NN1+I)*P0  
  61  CONTINUE
      DO 62 I=1,NCEL-1                                                                                                 
       Q(I+1) = XYU(NN2+I)*W0
  62  CONTINUE
C                    
      NZN=0.                                                 
      DO 60 I=1,NCEL                                                    
       TOLIN(2*NCEL+I)=WWTOL
       TOLIN(  NCEL+I)=PPTOL
       HM(I)  =XYU(NN0+I)*H0                                                                                                  
       QTI(I) =XYU(NN3+I)*W0*H0
       HT(I+1)=XYU(NN4+I)*H0
       TPE(I) =XYU(NN5+I)*T0
       KMET=IXYU+6*NCEL+4+NZN
       DO J=1,NZON(I)
	  TFL(J,I)=XYU(KMET+J)*T0
          GE(J,I) =XYU(KMET+NZFTOT+J)*1000. !compatibile con FUMN
       ENDDO
       NZN=NZN+NZON(I)
C
C----- CALCOLO ENTALPIE DI CONFINE STATICHE 
       H(I+1)  =HM(I)
C
       SM(I)   =SHEV(P(I+1),HM(I),NFL)
       TF(I)   =TEV (P(I+1),SM(I),NFL)
       TITOL(I)=YEV (P(I+1),SM(I),NFL) 
C
C-- CALCOLO DEL MOLTIPLICATORE D'ATTRITO DI MARTINELLI-NELSON SECONDO BECKER
C        
C---- MODELLO OMOGENEO 
C---- ESAME I-ESIMO CONFINE (I=1,NCEL)
      IF (PACO.EQ.0.) THEN
        IF(P(I).LT.221.1E+05)THEN
          CALL SATUR (P(I),3,RL,RV,1)
        ELSE
          CALL SATUR (221.1E+05,3,RL,RV,1)
        ENDIF
       SMI   =SHEV(P(I),H(I),NFL)
       TITOLI=YEV (P(I),SMI,NFL)
       RO(I)=ROEV(P(I),SMI,NFL)
       FIQLO(I)=1.
       ROLS(I)=RO(I)
       DR(I)=0.
       DH(I)=0.
       ALF0(I)=0.
       IF(TITOLI.GT.0.)
     &       ALF0(I)=1./(1.+(1.-TITOLI)/TITOLI*RV/RL)
      ELSE
C
C---- MODELLO DI "DRIFT" (correzioni di POLLACHINI 05/12/1991)
C---- ESAME I-ESIMO CONFINE (I=1,NCEL)
         SI=SHEV(P(I),H(I),NFL) 
         TIF =TEV(P(I),SI,NFL)                                             
         DIAH=DIAI(I)
         ARE=AREA(I)
      CALL EXCYNOM(TIF,ARE,DIAH,IFUN,PACO,Q(I),H(I),P(I),HT(I),
     &             RM,DRD,DHD,ALFN,SLN,C0,VGJ,FL,I,FIQLOI,RL)       
C---- MEMORIZZAZIONE DELLE GRANDEZZE DI "DRIFT"
         RO(I)=RM
         DR(I)=DRD
         DH(I)=DHD
         ALF0(I)=ALFN
         SL(I)=SLN
         C00(I)=C0
         VGJ0(I)=VGJ
         FLU(I)=FL
         FIQLO(I)=FIQLOI
         IF(FIQLO(I).GT.1.) THEN
             ROLS(I)=RL
         ELSE
             ROLS(I)=RO(I)
         ENDIF            
CC         ENDIF
      ENDIF
  60  CONTINUE
C---- ESAME CONFINE NNN=NCEL+1
C
C-- CALCOLO DEL MOLTIPLICATORE D'ATTRITO DI MARTINELLI-NELSON SECONDO BECKER
C       
      IF(PACO.EQ.0.) THEN
        IF(P(NNN).LT.221.1E+05)THEN
         CALL SATUR (P(NNN),3,RL,RV,1)
        ELSE
          CALL SATUR (221.1E+05,3,RL,RV,1)
        ENDIF
         SM1=SHEV(P(NNN),H(NNN),NFL)
         TITOL1=YEV (P(NNN),SM1,NFL)
         RO(NNN)=ROEV(P(NNN),SM1,NFL)
         ALF0(NNN)=0.
         IF(TITOL1.GT.0.)
     &     ALF0(NNN)=1./(1.+(1.-TITOL1)/TITOL1*RV/RL)
         FIQLO(NNN)=1.
         ROLS(NNN)=RO(NNN)
         DR(NNN)=0.
         DH(NNN)=0.
      ELSE
         SI1=SHEV(P(NNN),H(NNN),NFL) 
         TIF1 =TEV(P(NNN),SI1,NFL)                                             
         ARE=AREA(NCEL)
         DIAH=DIAI(NCEL)
       CALL EXCYNOM(TIF1,ARE,DIAH,IFUN,PACO,Q(NNN),H(NNN),P(NNN),
     &           HT(NNN),RM,DRD,DHD,ALFN,SLN,C0,VGJ,FL,NNN,FIQLOI,RL)       
         RO(NNN)=RM
         DR(NNN)=DRD
         DH(NNN)=DHD
         ALF0(NNN)=ALFN
         SL(NNN)=SLN
         C00(NNN)=C0
         VGJ0(NNN)=VGJ
         FLU(NNN)=FL
         FIQLO(NNN)=FIQLOI
             IF(FIQLO(NNN).GT.1.) THEN
             ROLS(NNN)=RL
             ELSE
             ROLS(NNN)=RO(NNN)
             ENDIF            
CC         ENDIF
      ENDIF
C---- CALCOLO DELLA DENSITA' MEDIA DI CELLA 
      DO 70 I=1,NCEL
      ROLS(I)=2.*ROLS(I)*ROLS(I+1)/(ROLS(I)+ROLS(I+1))
   70 ROM(I)=2.*RO(I)*RO(I+1)/(RO(I)+RO(I+1))
C
C----- MEMORIZZAZZIONE NEL VETTORE DATI DEL CORRETTORE D'ATTRITO DI 
C      MARTINELLI-NELSON ALL'INIZIO DI OGNI PASSO DI TEMPO   
C      (L. POLLACHINI 13/05/1993)
C
       IF(KREGIM.OR.(.NOT.KREGIM.AND.IFUN.EQ.2.AND.ITERT.EQ.0))
     &  THEN
          KS=IPD+20*NCEL+NZFTOT+5
          DO I=1,NCEL+1
             DATI(KS+I)=FIQLO(I)     
          ENDDO
       ENDIF
C
C----- CARICAMENTO DEL MOLTIPLICATORE D'ATTRITO DI MARTINELLI-NELSON    
C      RELATIVO ALLA ITERAZIONE PRECEDENTE
C    
       IF(.NOT.KREGIM) THEN
       KS=IPD+20*NCEL+NZFTOT+5
       DO I=1,NCEL+1       
       FIQLO(I)=DATI(KS+I) 
       ENDDO
       ENDIF
C
C----- ESCLUSIONE DEL CORRETTORE D'ATTRITO DI MARTINELLI-NELSON (IFIQLO=0)
       IFIQLO=1
       IF(IFIQLO.EQ.0) THEN
         DO 77 I=1,NCEL
            FIQLO(I)=1.
            ROLS(I)=ROM(I)
   77    CONTINUE
         FIQLO(NCEL+1)=1.
       ENDIF
C
C     MEMORIZZO I TERMINI DI DRIFT
C
C       KS=IPD+17*NCEL+NZFTOT+2
C       DO I=1,NCEL+1
C       DATI(KS+I)       =DH(I)
C       DATI(KS+NCEL+1+I)  =DR(I)
C       DATI(KS+2*NCEL+2+I)=RO(I)
C       ENDDO
C
      IF(.NOT.KREGIM.AND.IFUN.EQ.2.AND.ITERT.EQ.0) THEN
C
C---- IN TRANSITORIO , ALL'INIZIO DI OGNI PASSO DI TEMPO,
C     MEMORIZZA LE PRESSIONI E LE ENTALPIE ATTUALI NEL VETTORE DATI 
C
       KS=IPD+15*NCEL+NZFTOT+1
       DO I=1,NCEL+1
       DATI(KS+I)= P(I)
       ENDDO
       DO I=1,NCEL
       DATI(KS+NCEL+1+I)= HM(I)
       ENDDO
      ENDIF
C
C____ CARICAMENTO DEI VETTORI PRESSIONI ED ENTALPIE DEL PASSO PRECEDENTE 
C     DA USARE PER CALCOLARE LE P_PUNTO IN TRANSITORIO
C
      KS=IPD+15*NCEL+NZFTOT+1
      IF(.NOT.KREGIM) THEN
       DO I=1,NCEL+1
       PN(I) = DATI(KS+I)
       ENDDO
       DO I=1,NCEL
       HN(I) = DATI(KS+NCEL+1+I)
       ENDDO
      ENDIF
C
      IF (Q(1).GT.0.)  H(1)=H(1)-DH(1)/Q(1)
C
C
C_______ STAMPE
C
C     IF (KREGIM.AND.IFUN.EQ.2) THEN
C      WRITE(6,*)'HM ',(HM(I),I=1,NCEL)
C      WRITE(6,*)'ROM ',(ROM(I),I=1,NCEL)
C      WRITE(6,*)'HT ',(HT(I),I=1,NCEL+1)
C      WRITE(6,*)'DH ',(DH(I),I=1,NCEL+1)
C      WRITE(6,*)'DR ',(DR(I),I=1,NCEL+1)
C      WRITE(6,*)'FIQLO ',(FIQLO(I),I=1,NCEL+1)
C      WRITE(6,*)'ROLS ',(ROLS(I),I=1,NCEL)
C     ENDIF
C
      RETURN                                                            
      END 
C**************************************************************************
      SUBROUTINE EXCYTAU(IFUN,DATI,IPD)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      DIMENSION DATI(*)
      PARAMETER (NZFMAX=6,NCELMAX=6)
      COMMON/EXCY03/CF,PACO,NCEL,NZFTOT,NZON(NCELMAX),NEQ                         
      COMMON/EXCY04/H(NCELMAX+1),P(NCELMAX+1),Q(NCELMAX+1),
     $              RO(NCELMAX+1),PN(NCELMAX+1),HN(NCELMAX+1),
     $              HI,HUINV
      COMMON/EXCY05/HM(NCELMAX),TF(NCELMAX),ROM(NCELMAX),
     $            DRDH(NCELMAX),DRDP(NCELMAX),GAMMA(NCELMAX),
     $            SM(NCELMAX),TITOL(NCELMAX),QTI(NCELMAX),
     $            TPE(NCELMAX),TFL(NZFMAX,NCELMAX),
     $            GE(NZFMAX,NCELMAX)
      COMMON/EXCY06/V(NCELMAX),B(NCELMAX),AREA(NCELMAX),
     $              DIAI(NCELMAX),SUP(NZFMAX,NCELMAX),
     $              CKF(NCELMAX),DZG(NCELMAX),CRIG(NCELMAX),
     $              SS(NCELMAX),D(NCELMAX),CM(NCELMAX)
      COMMON/EXCY07/TAU1H(NCELMAX),TAU2H(NCELMAX),TAU1P(NCELMAX),
     $              TAU2P(NCELMAX),TAU3(NCELMAX)    
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0                             
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT                                         
      COMMON/REGIME/KREGIM                                              
      LOGICAL KREGIM                                                    
C                                                                       
C       CALCOLO DELLE TAU (MASSA-ENERGIA)               
C                                                                       
      NFL=1                                                             
      KTAU=IPD+10*NCEL+NZFTOT+1
C
      DO 10 I=1,NCEL                                                    
C
C____ IL CALCOLO DELLE COSTANTI DI TEMPO VIENE FATTO SOLO
C     ALLA PRIMA ITERAZIONE
C
      IF(ITERT.EQ.0.AND.IFUN.EQ.2) THEN
C
        PV=P(I+1)                                               
        S =SM(I)
        T =TF(I)
        BB =BEV (PV,S ,NFL)                                                
        A =A2EV(PV,S ,NFL)                                                
        DRDH(I)=BB/T                                               
        DRDP(I)=1./A-BB/(ROM(I)*T)                                 
C
        TAU2H(I)=V(I)*DRDH(I)                                             
        ROMIN=0.1
        IF(ROM(I).GT.ROMIN)THEN
           TAU1H(I)=V(I)*ROM(I)                                              
        ELSE
           TAU1H(I)=V(I)*ROMIN                                              
        ENDIF
        TAU2P(I)=V(I)*DRDP(I)                                             
        TAU1P(I)=-V(I)                                                    
C
        DATI(KTAU+(I-1)*4 +1)=TAU2H(I)        
        DATI(KTAU+(I-1)*4 +2)=TAU1H(I)        
        DATI(KTAU+(I-1)*4 +3)=TAU2P(I)        
        DATI(KTAU+(I-1)*4 +4)=TAU1P(I)        
      ELSE
        TAU2H(I)=DATI(KTAU+(I-1)*4 +1)
        TAU1H(I)=DATI(KTAU+(I-1)*4 +2)
        TAU2P(I)=DATI(KTAU+(I-1)*4 +3)
        TAU1P(I)=DATI(KTAU+(I-1)*4 +4)
      ENDIF
C
      TAU3(I)=0.
   10 CONTINUE                                                          
      RETURN                                                            
      END                                                               
C**************************************************************************
      SUBROUTINE EXCYMET(TM,TMN,TPI,QTE,FM,DATI,IPD,IFUN,DELTAT)
      PARAMETER (NZFMAX=6,NCELMAX=6)
      PARAMETER (PI=3.14159)
      DIMENSION TM(*),TMN(*),TPI(*),QTE(*),FM(*),DATI(*)
      COMMON/EXCY03/CF,PACO,NCEL,NZFTOT,NZON(NCELMAX),NEQ                         
      COMMON/EXCY05/HM(NCELMAX),TF(NCELMAX),ROM(NCELMAX),
     $            DRDH(NCELMAX),DRDP(NCELMAX),GAMMA(NCELMAX),
     $            SM(NCELMAX),TITOL(NCELMAX),QTI(NCELMAX),
     $            TPE(NCELMAX),TFL(NZFMAX,NCELMAX),
     $            GE(NZFMAX,NCELMAX)
      COMMON/EXCY06/V(NCELMAX),B(NCELMAX),AREA(NCELMAX),
     $              DIAI(NCELMAX),SUP(NZFMAX,NCELMAX),
     $              CKF(NCELMAX),DZG(NCELMAX),CRIG(NCELMAX),
     $              SS(NCELMAX),D(NCELMAX),CM(NCELMAX)
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT                   !SNGL
C      COMMON/INTEG1/TSTOP,TEMPO,DTINT,CDT,ALFADT,NPAS                   !DBLE
      COMMON/PARPAR/NUL(7),ITERT                                         
      COMMON/REGIME/KREGIM               
      LOGICAL KREGIM
      REAL A(NCELMAX),C(NZFMAX,NCELMAX),
     $     CTF(NCELMAX),CTOT(NCELMAX)
C
C****** a. calcolo potenza esterna QTE(I)      
      DO I=1,NCEL
	 QTE(I)=0.
	 DO J=1,NZON(I)
	    QTE(I)=QTE(I)+GE(J,I)*SUP(J,I)*(TFL(J,I)-TPE(I))
	 ENDDO
      ENDDO	 
C****** b. calcolo temperatura metallo TMN(I) data TPE(I)
      DO I=1,NCEL
	 DO J=1,NZON(I)
	    C(J,I)=GE(J,I)*SUP(J,I)
         ENDDO
      ENDDO
      DO I=1,NCEL
         CTF(I)=0.
         CTOT(I)=0.
      ENDDO
      DO I=1,NCEL
         DO J=1,NZON(I)
	    CTF(I)=CTF(I)+C(J,I)*TFL(J,I)
	    CTOT(I)=CTOT(I)+C(J,I)
         ENDDO
      ENDDO
      DO I=1,NCEL
	 TMN(I)=((D(I)+CTOT(I))*TPE(I)-CTF(I))/D(I)
      ENDDO
C****** c. calcolo temperatura parete interna TPI(I)
      IF(KREGIM) THEN
         DO I=1,NCEL
            TPI(I)=TMN(I)- QTE(I)/B(I)
         ENDDO
      ELSE
         DO I=1,NCEL
            A(I)=GAMMA(I)*SS(I)
         ENDDO
         DO I=1,NCEL
	    TPI(I)=(A(I)*TF(I)+B(I)*TMN(I))/(A(I)+B(I))
         ENDDO
      ENDIF
C
      IF (KREGIM) GO TO 100
C--------------------------------------CALCOLO TRANSITORIO
C****** a. shift registro a scorrimento ad inizio nuovo passo integrazione
      KK=IPD+22*NCEL+NZFTOT+7 
      IF(ITERT.EQ.0.AND.IFUN.EQ.2) THEN
         DO I=1,NCEL
    	    DATI(KK+NCEL+I-1)=DATI(KK+I-1)
	 ENDDO
      ENDIF
C****** b. lettura TM(I) del precedente passo
      DO I=1,NCEL
         TM(I)=DATI(IPD+23*NCEL+NZFTOT+6+I)
      ENDDO
C****** c. salvataggio di TMN(I) nel registro a scorrimento
      DO I=1,NCEL
	 DATI(IPD+22*NCEL+NZFTOT+6+I)=TMN(I)
      ENDDO
C****** d. calcolo residuo metallo
      DO I=1,NCEL
        FM(I)=TMN(I)-TM(I)-(QTE(I)-QTI(I))*DELTAT/CM(I)
C       FM(I)=QTE(I)-QTI(I)-CM(I)*(TMN(I)-TM(I))/DELTAT
      ENDDO
      RETURN
C-------------------------------------CALCOLO REGIME
100   CONTINUE
C****** a. salvataggio TMN(I) nel registro a scorrimento in DATI
      DO I=1,NCEL
	 DATI(IPD+22*NCEL+NZFTOT+6+I)=TMN(I)
         DATI(IPD+23*NCEL+NZFTOT+6+I)=TMN(I)
      ENDDO
C****** b. calcolo residui
      DO I =1, NCEL
         FM(I)=QTE(I)-QTI(I)
      ENDDO
      RETURN  
      END
C
C**************************************************************************
C
      SUBROUTINE EXCYGTERT(P,H,S,T,RO,TIT,TP,D,CRIG,G,Q,SUP,HTC)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C
C**************** G. Migliavacca 22.11.1996
C
C**************** correlazioni: Dittus-Boelter per acqua (X<=X1)
C                               Hadaller per vapore (X>=X4)
C                               Valore costante GCONST per X2=<X<=X3
C                               Raccordo lineare per X1<X<X2 e X3<X<X4
C                               ALPHA stabilisce la temperatura di film
C**************** E. Tassi  25.11.96
C                       
C                             -X2 vale 0.1 (da0.3)
C                             -GCONST vale 50000 (da 15000)
C                             -tra X3(escluso) ed X4 raccordo lineare
C                                  tra Hadaller calc. in X4 ed Had/2
C                                  posto in X3
C
      PARAMETER (ALPHA=1.)
      DATA X1/0./,X2/0.1/,X3/0.7/,X4/1./  !titoli di confine tra le correl.
C
      IF (TIT.GE.X1.AND.TIT.LE.X4) THEN !sotto la campana di Mollier
         IF(P.GT.1.E+05) THEN
            GCONST=50000.
         ELSE !protez. da condens. celle non riscaldate con W=0
            GCONST=.4995E-05*P*P+50. 
         ENDIF
      ENDIF
      IF (TIT.LT.X2) THEN
         DB=EXCYDB(P,S,T,RO,TIT,TP,D,G,X1,ALPHA)
      ELSE IF (TIT.GT.X3) THEN
         HAD=EXCYHAD(P,S,T,RO,TIT,TP,D,G,X4,ALPHA)
      ENDIF
C        
      IF (TIT.LE.X1) THEN
         HTC=DB
      ELSE IF (TIT.GT.X1.AND.TIT.LE.X2) THEN
         A=(GCONST-DB)/(X2-X1)
         B=DB-A*X1
         HTC=A*TIT+B
      ELSE IF (TIT.GT.X2.AND.TIT.LT.X3) THEN
         HTC=GCONST
      ELSE IF (TIT.GT.X3.AND.TIT.LT.X4) THEN
         HTC=0.5*HAD*(1+ (TIT-X3)/(X4-X3))
      ELSE
         HTC=HAD
      ENDIF
      RETURN
      END
C
C**************************************************************************
      REAL FUNCTION EXCYDB(P,S,T,RO,TIT,TP,D,G,X1,ALPHA)
C
      REAL MU,LAM,MUMIN,LAMMIN
      DATA MUMIN/9.E-06/,LAMMIN/18.E-03/,CPMIN/1000./
C
      NFL=1
      IF (P.LT.221.2E5) THEN !caso sottocritico
         CALL SATUR(P,1,SW,SV,1)
         CALL SATUR(P,3,ROW,ROV,NFL)
         RWV=ROW/ROV
         IF (TIT.LE.X1) THEN
            SS=S
            RR=RO
            TT=TIT
         ELSE 
            SS=SW
            RR=ROW
            TT=0.
         ENDIF
      ELSE      !caso supercritico
         RWV=1.
         SS=S
         RR=RO
         TT=TIT
      ENDIF
C
      TF=ALPHA*T+(1-ALPHA)*TP
      CP=CPEV(P,SS,TT,0.5,NFL)
      MU=ETEV(P,TF,RR,RWV,TT,0.5,NFL)
      LAM=ALEV(P,TF,RR,RWV,TT,0.5,NFL)
      IF(MU.LT.MUMIN)MU=MUMIN
      IF(LAM.LT.LAMMIN)LAM=LAMMIN
      IF(CP.LT.CPMIN)CP=CPMIN
      RE=G*D/MU
      PR=CP*MU/LAM
      EXCYDB=.023*LAM*RE**.8*PR**.4/D
C
      RETURN
      END
C
C**************************************************************************
      REAL FUNCTION EXCYHAD(P,S,T,RO,TIT,TP,D,G,X4,ALPHA)
C
      REAL MU,LAM,MUMIN,LAMMIN
      DATA MUMIN/9.E-06/,LAMMIN/18.E-03/,CPMIN/1000./
C
      NFL=1
      IF (P.LT.221.2E5) THEN !caso sottocritico
         CALL SATUR(P,1,SW,SV,1)
         CALL SATUR(P,3,ROW,ROV,NFL)
         RWV=ROW/ROV
         IF (TIT.GE.X4) THEN
            SS=S
            RR=RO
            TT=TIT
         ELSE
            SS=SV
            RR=ROV
            TT=1.
         ENDIF
      ELSE      !caso supercritico
         RWV=1.
         SS=S
         RR=RO
         TT=TIT
      ENDIF
C
      TF=ALPHA*T+(1-ALPHA)*TP
      CP=CPEV(P,SS,TT,0.5,NFL)
      MU=ETEV(P,TF,RR,RWV,TT,0.5,NFL)
      LAM=ALEV(P,TF,RR,RWV,TT,0.5,NFL)
      IF(MU.LT.MUMIN)MU=MUMIN
      IF(LAM.LT.LAMMIN)LAM=LAMMIN
      IF(CP.LT.CPMIN)CP=CPMIN
      RE=G*D/MU
      PR=CP*MU/LAM
      EXCYHAD=.008348*LAM*RE**.8774*PR**.6112/D
C
      RETURN
      END
C        
C**************************************************************************
      SUBROUTINE EXCYD1 (BLOCCO,NEQUAZ,NSTATI,NUSCIT,NINGRE,SYMVAR,XYU,
     $                   IXYU,DATI,IPD,SIGNEQ,UNITEQ,COSNOR,ITOPVA,MXT)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                             !DBLE
C
C----significato delle variabili di uscita
C   SIGNEQ = DESCRIZIONE DELL'EQUAZIONE (IN STAZIONARIO) - 50 CAR.
C   UNITEQ = UNITA` DI MISURA DEL RESIDUO - 10 CAR.
C   COSNOR = COSTANTE DI NORMALIZZAZIONE DEL RESIDUO IN STAZIONARIO
C   ITOPVA = TOPOLOGIA JACOBIANO DI REGIME - matrice di INTEGER
C
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0
      CHARACTER *8 BLOCCO, SYMVAR(*)
      CHARACTER *(*) SIGNEQ(*), UNITEQ(*)
      DIMENSION DATI(*), XYU(*), COSNOR(*), ITOPVA(MXT,*)
C
      NCEL=DATI(IPD)
C
C--- Equazione di conservazione dell'energia fluido
      SIGNEQ ( 1) = 'fluid energy conservation' 
      UNITEQ ( 1) = 'power'
      COSNOR ( 1) = W0*H0 
      DO I=1,NCEL
       ITOPVA ( 1, I) = 1
      ENDDO
C
C--- Equazione di conservazione del momento del fluido
      SIGNEQ ( 2) = 'momentum equation' 
      UNITEQ ( 2) = 'pressure'
      COSNOR ( 2) = P0
      DO I=1,NCEL
       ITOPVA ( 2, I) = 1
      ENDDO
C
C--- Equazione di conservazione della massa del fluido
      SIGNEQ ( 3) = 'fluid mass conservation' 
      UNITEQ ( 3) = 'mass flow'
      COSNOR ( 3) = W0
      DO I=1,NCEL
       ITOPVA ( 3, I) = 1
      ENDDO
C
C--- Equazione di calcolo della potenza attraverso la superficie interna
      SIGNEQ ( 4) = 'inner surface transient power calculation'
      UNITEQ ( 4) = 'power'
      COSNOR ( 4) = W0*H0
      DO I=1,NCEL
       ITOPVA ( 4, I) = 1
      ENDDO
C
C--- Equazione di calcolo dell'entalpia totale d'uscita cella
      SIGNEQ ( 5) = 'cell total outlet enthalpy calculation'
      UNITEQ ( 5) = 'power'
      COSNOR ( 5) = W0*H0
      DO I=1,NCEL
       ITOPVA ( 5, I) = 1
      ENDDO
C
C--- Equazione di conservazione dell'energia del metallo
      SIGNEQ ( 6) = 'metal energy conservation equation'
      UNITEQ ( 6) = 'power'
      COSNOR ( 6) = W0*H0
      DO I=1,NCEL
       ITOPVA ( 6, I) = 1
      ENDDO
      RETURN
      END
C**************************************************************************
      REAL FUNCTION EXCYISTA09(IFUN)
C      DOUBLE PRECISION FUNCTION EXCYISTA09(IFUN)                            !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/REGIME/KREGIM                                              
      COMMON/PARPAR/NUL(6),KSTP,ITERT                                   
      LOGICAL KREGIM                                                    
C                                                                       
C------ISTA=0,1                                                         
C                                                                       
      EXCYISTA09=0                                                          
      IF(KREGIM) EXCYISTA09=1                                               
      IF((KSTP.EQ.1).AND.(ITERT.EQ.0)) EXCYISTA09=1                      
C
      RETURN                                                            
      END                                                               
C**************************************************************************
      SUBROUTINE EXCYTA(ISTA)                                           
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      PARAMETER (NZFMAX=6,NCELMAX=6)
      COMMON/EXCY03/CF,PACO,NCEL,NZFTOT,NZON(NCELMAX),NEQ                         
      COMMON/EXCY04/H(NCELMAX+1),P(NCELMAX+1),Q(NCELMAX+1),
     $              RO(NCELMAX+1),PN(NCELMAX+1),
     $              HN(NCELMAX+1),HI,HUINV
      COMMON/EXCY05/HM(NCELMAX),TF(NCELMAX),ROM(NCELMAX),
     $            DRDH(NCELMAX),DRDP(NCELMAX),GAMMA(NCELMAX),  
     $            SM(NCELMAX),TITOL(NCELMAX),QTI(NCELMAX), 
     $            TPE(NCELMAX),TFL(NZFMAX,NCELMAX),
     $            GE(NZFMAX,NCELMAX)
      COMMON/EXCY06/V(NCELMAX),B(NCELMAX),AREA(NCELMAX),
     $              DIAI(NCELMAX),SUP(NZFMAX,NCELMAX),
     $              CKF(NCELMAX),DZG(NCELMAX),CRIG(NCELMAX),
     $              SS(NCELMAX),D(NCELMAX),CM(NCELMAX)
      COMMON/EXCY07/TAU1H(NCELMAX),TAU2H(NCELMAX),TAU1P(NCELMAX),
     $              TAU2P(NCELMAX),TAU3(NCELMAX)    
      COMMON/NORM/P0,H0,T0,W0,R0,AL0,V0,DP0  
      DIMENSION AM(NCELMAX)                           
      WRITE(6,1001)
      AMT=0.                                                     
      DO 10 I=1,NCEL
       AM(I)=ROM(I)*V(I)                                        
        G=Q(I)/AREA(I)                                                      
        T=TF(I)-273.16                                                    
        WRITE(6,1002) I,Q(I),HM(I),P(I+1),AM(I),ROM(I),TITOL(I),G,T
      AMT=AMT+AM(I)          
   10 CONTINUE                               
      DO 20 I=1,NCEL                                                    
       T=TF(I)-273.16                                                  
       WRITE(6,1004) I,T,GAMMA(I),QTI(I)                             
   20 CONTINUE
C      WRITE(6,1850)AMT                                           
 1001 FORMAT(//1X,'CELLA',4X,'PORTATA',8X,'ENTALPIA',7X,'PRESSIONE',    
     $       6X,'MASSA TOT.',5X,'DENS.MEDIA',7X,'TITOLO',8X,            
     $       'PORT.SPEC.',4X,'TEMPERATURA',4X/)                        
 1002 FORMAT(1X,I3,5X,8(E12.5,3X))                                      
 1003 FORMAT(//1X,'CELLA',4X,'TEMP.PAR.',I2,7X,'COEFF.SCAMBIO',I2,      
     $       3X,'POT. TERM.',I2,7X/)                                   
 1004 FORMAT(1X,I3,5X,8(E12.5,6X))
 1850 FORMAT(/,1X,' MASSA DEL TRONCONE COMPLETO:  ',F12.6)                     
      RETURN 
      END                                                               
      FUNCTION EXCYG9(IFUN)                                             !SNGL
C      DOUBLE PRECISION FUNCTION EXCYG9(IFUN)                            !DBLE
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
      COMMON/REGIME/KREGIM                                              
      COMMON/PARPAR/NUL(6),KSTP,ITERT                                   
      LOGICAL KREGIM                                                    
C                                                                       
C-----EXCYG9=0 NON CALCOLA IL COEFFICIENTE DI SCAMBIO                   
C-----EXCYG9=1 CALCOLA IL COEFFICIENTE DI SCAMBIO                       
C                                                                       
    1 EXCYG9=1                                                          
      IF(KREGIM)RETURN                                                  
      IF(ITERT.NE.0)EXCYG9=0                                            
      IF(IFUN.NE.2)EXCYG9=0                                             
      RETURN                                                            
      END                                                               
C**************************************************************************
       SUBROUTINE EXCYNOM(TIF,AREA,DIAH,IFUN,PACO,QQI,HHI,PPI,HTI,
     &                   RM,DRD,DHD,ALFN,SLN,C0,VGJ,FL,I,FIQLOJ,RL)       
C****************************************************************************
C    Alla subroutine EXCYNOM il modulo si rivolge sempre tranne che per 
C    il caso di modello omogeneo (PACO=0.).
C    Lo schema utilizzato  e' il seguente :
C
C          - dal valore di PACO si sceglie la correlazione per il 
C            calcolo di VGJ e C0;
C          - dalla routine della correlazione particolare scelta si
C            chiama la EXCYUGJALF che calcola UGJ e ALF;
C          - tornando alla EXCYNOM e' ora possibile calcolare i valori
C            dei termini di drift ed inserirli in opportuni vettori.
C
C            Attualmente si ha:
C       
C      PACO=1.: ZUBER-DIX    
C      PACO=2 : BANKOFF
C      PACO=3 : CHEXAL-LELLOUCHE
C      PACO=4 : ZUBER-ROUHANY
C  
C      AGGIORNARE IL COMMENTO SE SI INSERISCONO ALTRE CORRELAZIONI
C
C>>>>  Versione di "EXCYNOM" modificata da L. POLLACHINI il 05/12/1991  <<<<
C>>>>  Introduzione del calcolo del coefficiente d'attrito di Martinelli-Nelson
C      (Pollachini 31/03/1993)
C
C****************************************************************************
C
C********** CALCOLO TERMINI UGUALI PER QUALUNQUE CORRELAZIONE *************
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        DATA PCRIT /2.212E+07/
        G=QQI/AREA
C
C----- PROTEZIONE SULLA PORTATA SPECIFICA MINIMA        
        IF(G.LT.10.) G=10. 
C----- INIZIALIZZAZIONE DEL MOLTIPLICATORE DI MARTINELLI-NELSON
        FIQLO=1.
        FIQLOJ=1.
        OMEGAJ=1.
C
        IF(PPI.LT.221.1E+05)THEN
           CALL SATUR (PPI,2,HL,HV,1)
           CALL SATUR (PPI,3,RL,RV,1)
        ELSE
           CALL SATUR (221.1E+05,2,HL,HV,1)
           CALL SATUR (221.1E+05,3,RL,RV,1)
        ENDIF
C        IF(HTI.LE.HL) GOTO 100
C        IF(HTI.GE.HV) GOTO 200
        IF(HHI.LE.HL) GOTO 100
        IF(HHI.GE.HV) GOTO 200
        HLAT =HV-HL 
C----- CALCOLO DEL GRADO DI VUOTO TRAMITE LE ENTALPIE DI CONFINE 
C----- STATICHE AGGIORNATE HHI
        ALF=RL*(HL-HHI)/(RV*(HHI-HV)+(HL-HHI)*RL)    
C        IF(ALF.LT.0.) ALF=0.
C        IF(ALF.GT.1.) ALF=1.
C
C*****************************************************************************  
C   Calcolo titolo volumetrico (fraz. di vuoto omogenea) XV,  
C   densita' omogenea RH, flusso FL e titolo massico XP 
C
        XV=RL*(HL-HTI)/(RV*(HTI-HV)+(HL-HTI)*RL)
        RH=XV*RV+(1.-XV)*RL
        FL=G/RH
        XP=XV*RV/RL/(1.-XV*(1.-RV/RL))
C
C-- CALCOLO DEL MOLTIPLICATORE D'ATTRITO DI MARTINELLI-NELSON SECONDO BECKER
C        
        PI=PPI
        IF(PPI.LE.10.E+05) PI=10.E+05
        FIQLO=1.+10.*PCRIT/PI*XP
C
C-- FATTORE CORRETTIVO DI JONES (PER PORTARE IN CONTO LA PORTATA SPECIFICA)
C
C         PB=PPI/1.E+05
C         IF(G.LE.950.) THEN
C         OMEGAJ=1.36 + 0.0073*PB + 0.074*G/1000. - 0.0076*PB*G/1000. 
C         ELSE
C         OMEGAJ=1.26 - 0.0058*PB + 0.161*1000./G - 0.0055*PB*1000./G
C         ENDIF
C
         FIQLOJ=FIQLO*OMEGAJ
C
C        IF (IFUN.EQ.2) THEN         
C         WRITE(6,*) 'G= ',G,' OMEGA= ',OMEGAJ,' FIQLOJ= ',FIQLOJ
C        WRITE(6,*)' ALF   XV   XP  HHI   HTI  HL  HV'
C        WRITE(6,'(I2,2X,7G12.5)') I,ALF,XV,XP,HHI,HTI,HL,HV
C        ENDIF
C****************************************************************************
C
        DTK=647.3-TIF
        SIG=EXCYTENSUP(DTK) 
C 
        IF (PACO.EQ.1.)  CALL EXCYZD(RL,RV,XV,FL,SIG,AREA,
     $                               UGJ,ALFN,C0,VGJ,XP)
C
        IF (PACO.EQ.2.)  CALL EXCYBKO(PPI,XV,FL,UGJ,ALFN,C0,VGJ)
C
        IF (PACO.EQ.3.)  CALL EXCYCHELEL(PPI,XV,FL,ALF,SIG,RV,RL,TIF,
     $                               DIAH,UGJ,ALFN,C0,VGJ) 
C
        IF (PACO.EQ.4.)  CALL EXCYZUBROU(RL,RV,FL,XV,SIG,G,DIAH,
     $                               UGJ,ALFN,C0,VGJ,XP)
C        IF (IFUN.EQ.2) THEN         
C        WRITE(6,*)' ALFN  SLN  VGJ  C0'
C        WRITE(6,*)ALFN,SLN,VGJ,C0
C        ENDIF
        ALF=ALFN     
        RM=ALF*RV+(1.-ALF)*RL
        DRD =ALF/(1.-ALF)*RL*RV/RM*UGJ*UGJ
        DHD =DRD/UGJ*HLAT*(1.-ALF)*AREA
        SLN=(1.-ALF)/ALF*XP/(1.-XP)*RL/RV
        GOTO 950
 100    DRD=0.
        DHD=0.
        SSI=SHEV(PPI,HHI,1)
        RM =ROEV(PPI,SSI,1)                                                   
        FL=G/RM
        ALFN=0.
        XP=0.
        SLN=1.
        C0=0.
        VGJ=0.
        GO TO 950
 200     DRD=0.
         DHD=0.
         SSI=SHEV(PPI,HHI,1)
         RM =ROEV(PPI,SSI,1)                                                   
         FL=G/RM
         ALFN=1.
         XP=1.
         SLN=1.
         C0=1.
         VGJ=0.
 950    RETURN      
        END
C
        SUBROUTINE EXCYZD(RL,RV,XV,FL,SIG,AREA,UGJ,ALFN,C0,VGJ,XP)
C
C------ CORRELAZIONE DI ZUBER-DIX
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        B=(RV/RL)**0.1
        VGJ=2.9*(9.81*SIG*(RL-RV)/RL**2)**.25*(1.- XP **4.)
        SG=(1./XV-1.)/ABS(1./XV-1.)
        C0= XV*(1.+SG*(ABS(1./XV-1.))**B)
        CALL EXCYUGJALF(C0,FL,VGJ,XV,UGJ,ALF) 
        ALFN=ALF
        RETURN
        END
C
        SUBROUTINE EXCYBKO(P,XV,FL,UGJ,ALFN,C0,VGJ)
C
C------ CORRELAZIONE DI BANKOFF       
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        C0= 1./(.71+1.45E-08*P)
        UGJ=(C0-1.)*FL
        VGJ=0.
        ALFN=XV/C0 
        RETURN
        END 
C
        SUBROUTINE EXCYCHELEL(PPI,XV,FL,ALF,SIG,RV,RL,TIF,
     $             DIAH,UGJ,ALFN,C0,VGJ)
C
C------ CORRELAZIONE DI CHEXAL-LELLOUCHE
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        PR=PPI
        RA=RV/RL
        VG=FL*XV/ALF
        VL=FL*(1.-XV)/(1.-ALF)
C
C       
C    CALCOLO VISCOSITA'
C
        CALL EXCYVISCO(TIF,UL,UV) 
C
  50    CALL EXCYRECHEX(RL,RV,VG,VL,DIAH,UL,UV,REG,REL,RE)
        CALL EXCYC0CHEX(RE,RA,PR,ALF,B1,C0)
        C3= 2.*EXP(-ABS(REL/60000.))
        IF (C3.LT.0.5) C3=.5
        TK1= B1
C
        C2=1.
        C5 =SQRT (150.*RA)
         IF (C5.LT.1.) THEN        
         C6 = C5/(1.-C5) 
         C2=1./(1.-EXP(-C6))
         ENDIF
C
        C7= (.0914/DIAH)**.6
C       C7=1.
        C4=1.
        IF(C7.LT.1.) THEN
         C8=C7/(1.-C7)
         C4=1./(1.-EXP(-C8))
        ENDIF
C
        VGJP=.43*((RL-RV)*SIG*9.81/RL**2.)**.25
C
        VGJ= VGJP*(1.-ALF)**TK1*C2*C3*C4
        CALL EXCYUGJALF(C0,FL,VGJ,XV,UGJ,ALF)  
        ALFN=ALF
        RETURN
        END
C
        SUBROUTINE EXCYUGJALF(C0,FL,VGJ,XV,UGJ,ALF)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        UGJ=(C0-1.)*FL+VGJ
        ALF= XV/(C0+VGJ/FL)
        RETURN
        END
C
        SUBROUTINE EXCYC0CHEX (RE,RA,P,ALF,B1,C0)
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        REAL K0,L                                                       !SNGL
C        DOUBLE PRECISION K0,L                                           !DBLE
        DATA PCRIT /2.212E07/
C
        A1=1./(1.+EXP(-RE/60000.))
        B1=.8
        IF(A1.LT.0.8) B1=A1
        R= (1.+1.57*RA)/(1.-B1)
        K0= B1+(1.-B1)*RA**.25
        C1=4.*PCRIT**2./(P*(PCRIT-P))
        L=(1.-EXP(-C1*ALF))/(1.-EXP(-C1))
        C0=L/(K0+(1.-K0)*ALF**R)
        RETURN
        END
C
        SUBROUTINE EXCYRECHEX(RL,RV,VG,VL,DIAH,UL,UV,REG,REL,RE)
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        REL= VL*RL*DIAH/UL 
        REG= VG*RV*DIAH/UV
        IF (REG.GT.REL) RE=REG
        IF (REG.LE.REL) RE=REL
        IF (REG.LT.0.) RE=REG
        RETURN
        END
C
        SUBROUTINE EXCYVISCO(TK,UL,UV)
C
C  Calcolo VISCOSITA` di liquido e vapore saturi
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        DIMENSION VISVAP(39)
        DIMENSION VISLIQ(39)
        DATA VISLIQ
     $/1750,1300,1000,797,651,544,463,400,351,311,279,252,
     $230,211,195,181,169,159,149,141,134,127,122,116,111,
     $107,103,99.4,96.1,93,90.1,86.5,83,79.4,75.4,70.9,65.3,
     $56.0,45./
C
        DATA VISVAP
     $/8.02,8.42,8.82,9.22,9.62,10.02,10.42,10.82,11.22,
     $11.62,12.02,12.42,12.80,13.17,13.54,13.90,14.25,14.61,
     $14.96,15.30,15.65,15.99,16.34,16.70,17.07,17.45,
     $17.85,18.28,18.75,19.27,19.84,20.7,21.7,23.1,24.7,
     $26.6,29.2,34.0,45./
C
        T=TK-273.16
        IND=T/10. +1
        IF (IND.GT.38) WRITE(6,1000)
1000    FORMAT (2X,'ERROR ,YOU ARE IN A HYPERCRITICAL FIELD')
        FRA =T/10.-(IND-1)
C      
        IF (IND.EQ.38)FRA=FRA/.415
        UL=VISLIQ(IND+1)+FRA*(VISLIQ(IND+2)-VISLIQ(IND+1))
        UV=VISVAP(IND+1)+FRA*(VISVAP(IND+2)-VISVAP(IND+1))
C
        RETURN
        END
C 
        REAL FUNCTION EXCYTENSUP(T)                                         !SNGL
C        DOUBLE PRECISION FUNCTION EXCYTENSUP(T)                             !DBLE
C
C                   calcolo tensione superficiale
C 
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        EXCYTENSUP=.001*((.1161*T**2.)/(1.+.83*T)+(1.121E-03)*T**2.
     $           -(5.752E-06)*T**3.+(1.286E-08)*T**4.
     $           -(1.149E-11)*T**5.) 
        RETURN
        END
        SUBROUTINE EXCYZUBROU(RL,RV,FL,XV,SIG,G,DE,UGJ,ALFN,C0,VGJ,XP)
C
C------ CORRELAZIONE DI ZUBER-ROUHANY
C
C      IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
        VGJ=1.18*(1.-XP)*(9.81*SIG*(RL-RV)/RL**2.)**.25
        C0 = 1. +0.2 * (1.-XP) * (9.81*DE)**.25 / (G/RL)**.5 
        CALL EXCYUGJALF(C0,FL,VGJ,XV,UGJ,ALF) 
        ALFN=ALF
        RETURN
        END
C
C~FORAUS_EXCY~C
C
C FORTRAN AUSILIARIO DEL MODULO CANALE BOLLENTE A PIU` PARETI DI SCAMBIO
C PER LA SUA SCRITTURA VEDERE MANUALE D'USO O 
C UTILIZZARE L'APPOSITO COMANDO DI LEGOCAD.
C
C*********** BREVE SPIEGAZIONE DEI PARAMETRI DELLA SUBROUTINE ******************
C
C    SUBROUTINE EXCYGAMUT(P,H,S,TF,RO,TITOL,TP,DIA,CRIG,G,Q,SUP,HTC)
C
C  Calcolo di HTC = coefficiente di scambio termico in [W/m**2/K]   
C    
C__________ SE VUOI CHE LA SUBROUTINE EXCYGAMUT SIA CHIAMATA DA EXCY
C           RICORDATI DI METTERE NEI DATI DEL MODULO SU FILE F14
C
C                   CRIG < 0.
C
C  La subroutine fornisce al modulo EXCY il coefficiente di scambio 
C  termico HTC fra parete metallica e fluido ; quest'ultimo puo` essere
C  calcolato in funzione dei parametri di ingresso della subroutine il cui
C  significato e' il seguente:
C
C   P     pressione del fluido                    [Pa]          
C   H     entalpia specifica del fluido           [J/kg]        
C   S     entropia specifica del fluido           [J/kg/C] 
C   TF    temperatura del fluido                  [K]
C   RO    densita' del fluido                     [kg/m**3]     
C   TITOL titolo della miscela
C   TP    temperatura di parete                   [K]
C   DIA   diametro idraulico del condotto         [m]
C   CRIG  dato fornito dall'utente nel file F14
C         per ogni cella del canale.
C         In questa subroutine puo` essere usato 
C         come si vuole.
C         RICORDATI CHE CRIG E` NEGATIVO !!!
C   G     portata specifica di fluido             [kg/m**2/s]   
C   Q     potenza totale scambiata                [W]           
C   SUP   superficie di scambio                   [m**2]        
C
C************ INIZIO DEL TESTO FORTRAN DA SCRIVERE *****************************
C
C      SUBROUTINE EXCYGAMUT(P,H,S,TF,RO,TITOL,TP,DIA,CRIG,G,Q,SUP,HTC)
CC     IMPLICIT DOUBLE PRECISION (A-H, O-Z)                              !DBLE
C      IF (CRIG.EQ.-1.) THEN
CC
C       HTC=Q/(SUP*(TP-TF))
CC
C      ELSE
CC
C       CALL SATUR(P,2,HLS,HVS,1)
C       HLV=HVS-HLS
CC
C       HTCSOT=15000.
C       HTCBIF=50000.
C       HTCSUR=15000.
CC
C       IF (H.LE.0.9*HLS) HTC=HTCSOT
C       IF (H.GT.0.9*HLS.AND.H.LT.HLS)
C     $    HTC=HTCSOT+(HTCBIF-HTCSOT)*(H-0.9*HLS)/(0.1*HLS)
C       IF (H.GE.HLS.AND.H.LE.(HVS-0.1*HLV)) HTC=HTCBIF
C       IF (H.GT.(HVS-0.1*HLV).AND.H.LT.HVS)
C     $    HTC=HTCBIF+(HTCSUR-HTCBIF)*(H-HVS+0.1*HLV)/(0.1*HLV)
C       IF (H.GE.HVS) HTC=HTCSUR
CC
C      ENDIF
CC
C      RETURN
C      END
CC~FORAUS_EXCY~C 
