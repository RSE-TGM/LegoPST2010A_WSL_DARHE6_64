C*************
C   Calcoli relativi alle tavole del vapore
C*************
        PROGRAM H2O_TABLES
C
        REAL*4 ARG1, ARG2, ARG3, RISULTATO, RISULTATO2
C
C     common per diagnostica calcoli sulle tavole
C
      COMMON/LGTV01/LGTEMPO,ILEGO,ICOUNT,ICOUNTMX
      COMMON/LGTV02/LGMODULO,LGBLOCCO
      CHARACTER*8 LGMODULO,LGBLOCCO
      REAL LGTEMPO
C
       DATA YC/.57/
       DATA IPRI/1/
C
       IF(IPRI.EQ.1)THEN
       ICOUNTMX=10
       ICOUNT=0
       ILEGO=0
        CALL INITSM
       IPRI=0
       ENDIF
        ID=1
       RISULTATO=0.
       RISULTATO2=0.
       OPEN(UNIT=51,FILE='tables.inp')
       READ(51,*)NUM_FUNZ
       READ(51,*)ARG1
       READ(51,*)ARG2
       READ(51,*)ARG3
C
       GO TO (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,
     $        16,17,18,19,20,21,22,23,24,25,26,27,28) NUM_FUNZ
C    
C---- Calcolo temperatura
C    
   1  CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       T=TEV(P,S,ID)
       T=T-273.15
       RISULTATO=T
       GO TO 100
C    
   2  CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S1=SHEV(P,H,ID)
       T=TEV(P,S1,ID)
       T=T-273.15
       RISULTATO=T
       GO TO 100
C    
   3  CONTINUE
C
       P=ARG1
       P=P*1.E5
       CALL SATUR(P,7,T,PIPPO,ID)
       T=T-273.15
       RISULTATO=T
       GO TO 100
C    
C---- Calcolo entropia
C    
   4  CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S=SHEV(P,H,ID)
       S=S*1.E-3
       RISULTATO=S
       GO TO 100
C    
   5  CONTINUE
C
       P=ARG1
       T=ARG2
       Y=ARG3
       P=P*1.E5
       T=T+273.15
       S=STEV(P,T,Y,ID)
       S=S*1.E-3
       RISULTATO= S
       GO TO 100
C    
C     Calcolo entropia liquido e vapore saturo
C    
   6  CONTINUE
C
       P=ARG1
       P=P*1.E5
       CALL SATUR(P,1,SWAT,SVAP,ID)
       SWAT=SWAT*1.E-3
       SVAP=SVAP*1.E-3
       RISULTATO=SWAT
       RISULTATO2=SVAP
       GO TO 100
C    
C---- Calcolo entalpia
C    
   7  CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       H=HEV(P,S,ID)
       H=H*1.E-3
       RISULTATO= H
       GO TO 100
C    
   8  CONTINUE
C
       P=ARG1
       T=ARG2
       Y=ARG3
       P=P*1.E5
       T=T+273.15
       S=STEV(P,T,Y,ID)
       H=HEV(P,S,ID)
       H=H*1.E-3
       RISULTATO=H
       GO TO 100
C    
C     Calcolo entalpia liquido e vapore saturo
C    
   9  CONTINUE
C
       P=ARG1
       P=P*1.E5
       CALL SATUR(P,2,HWAT,HVAP,ID)
       HWAT=HWAT*1.E-3
       HVAP=HVAP*1.E-3
       RISULTATO=HWAT
       RISULTATO2=HVAP
       GO TO 100
C    
C---- Densita`
C    
   10 CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       RO=ROEV(P,S,ID)
       RISULTATO=RO
       GO TO 100
C    
   11 CONTINUE
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S=SHEV(P,H,ID)
       RO=ROEV(P,S,ID)
       RISULTATO=RO
       GO TO 100
C     
   12 CONTINUE
C
       P=ARG1
       T=ARG2
       Y=ARG3
       P=P*1.E5
       T=T+273.15
       S=STEV(P,T,Y,ID)
       RO=ROEV(P,S,ID)
       RISULTATO=RO
       GO TO 100
C     
C     Calcolo densita` liquido e vapore saturo
C     
   13 CONTINUE
C
       P=ARG1
       P=P*1.E5
       CALL SATUR(P,3,ROWAT,ROVAP,ID)
       RISULTATO=ROWAT
       RISULTATO2=ROVAP
       GO TO 100
C     
C---- Calcolo derivata della densità (@) fatta rispetto all'entropia
C     specifica, a pressione costante
C     
   14 CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       DRODS=BEV(P,S,ID)
       RISULTATO=DRODS
       GO TO 100
C
   15 CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S=SHEV(P,H,ID)
       DRODS=BEV(P,S,ID)
       RISULTATO=DRODS
       GO TO 100
C
C     
C---- Calcolo derivata della densità fatta rispetto alla pressione
C     a entropia specifica costante
C     
   16 CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       DRODP=1./A2EV(P,S,ID)
       RISULTATO=DRODP
       GO TO 100
C     
   17 CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S=SHEV(P,H,ID)
       DRODP=1./A2EV(P,S,ID)
       RISULTATO=DRODP
       GO TO 100
C
C
C---- Calcolo titolo miscela
C
   18 CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       Y=YEV(P,S,ID)
       RISULTATO=Y
       GOTO 100
C
   19 CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S1=SHEV(P,H,ID)
       Y=YEV(P,S1,ID)
       RISULTATO=Y
       GOTO 100
C
C
C---- Calcolo calore specifico
C
   20 CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       Y=YEV(P,S,ID)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       CP=CPEV(P,S,Y,YC,ID)
       RISULTATO=CP
       GO TO 100
C
   21 CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S=SHEV(P,H,ID)
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       Y=YEV(P,S,ID)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       CP=CPEV(P,S,Y,YC,ID)
       RISULTATO=CP
       GO TO 100
C
   22 CONTINUE
C
       P=ARG1
       T=ARG2
       Y=ARG3
       P=P*1.E5
       T=T+273.15
       S=STEV(P,T,Y,ID)
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       CP=CPEV(P,S,Y,YC,ID)
       RISULTATO=CP
       GO TO 100
C
   23 CONTINUE
C
C---- Calcolo viscosita' Mu
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       T=TEV(P,S,ID)
       RO=ROEV(P,S,ID)
       CALL SATUR(P,3,ROSL,ROSS,ID)
       RA=ROSL/ROSS
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       Y=YEV(P,S,ID)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       XMU=ETEV(P,T,RO,RA,Y,YC,ID)
       RISULTATO=XMU
       GO TO 100
C
   24 CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S=SHEV(P,H,ID)
       T=TEV(P,S,ID)
       RO=ROEV(P,S,ID)
       CALL SATUR(P,3,ROSL,ROSS,ID)
       RA=ROSL/ROSS
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       Y=YEV(P,S,ID)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       XMU=ETEV(P,T,RO,RA,Y,YC,ID)
       RISULTATO=XMU
       GO TO 100
C
   25 CONTINUE
C
       P=ARG1
       T=ARG2
       Y=ARG3
       P=P*1.E5
       T=T+273.15
       S=STEV(P,T,Y,ID)
       RO=ROEV(P,S,ID)
       CALL SATUR(P,3,ROSL,ROSS,ID)
       RA=ROSL/ROSS
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       XMU=ETEV(P,T,RO,RA,Y,YC,ID)
       RISULTATO=XMU
       GO TO 100
C
C---- Calcolo conducibilita'
C
   26 CONTINUE
C
       P=ARG1
       S=ARG2
       P=P*1.E5
       S=S*1.E3
       T=TEV(P,S,ID)
       RO=ROEV(P,S,ID)
       CALL SATUR(P,3,ROSL,ROSS,ID)
       RA=ROSL/ROSS
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       Y=YEV(P,S,ID)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       XK=ALEV(P,T,RO,RA,Y,YC,ID)
       RISULTATO=XK
       GO TO 100
C
   27 CONTINUE
C
       P=ARG1
       H=ARG2
       P=P*1.E5
       H=H*1.E3
       S=SHEV(P,H,ID)
       T=TEV(P,S,ID)
       RO=ROEV(P,S,ID)
       CALL SATUR(P,3,ROSL,ROSS,ID)
       RA=ROSL/ROSS
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       Y=YEV(P,S,ID)
       IF(Y.GT.0..AND.Y.LE.YC)RISULTATO2=1.
       IF(Y.GT.YC.AND.Y.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       XK=ALEV(P,T,RO,RA,Y,YC,ID)
       RISULTATO=XK
       GO TO 100
C
   28 CONTINUE
C
       P=ARG1
       T=ARG2
       Y=ARG3
       P=P*1.E5
       T=T+273.15
       S=STEV(P,T,Y,ID)
       RO=ROEV(P,S,ID)
       CALL SATUR(P,3,ROSL,ROSS,ID)
       RA=ROSL/ROSS
       CALL SATUR(P,7,TSAT,PIPPO,ID)
       CALL SATUR(P,1,SWAT,SVAP,ID)
       YS=(S-SWAT)/(SVAP-SWAT)
       TTEST=T-TSAT
       IF(YS.GE.0..AND.YS.LE.YC)RISULTATO2=1.
       IF(YS.GT.YC.AND.YS.LE.1.)RISULTATO2=2.
       IF(YS.GT.1.)RISULTATO2=3.
       XK=ALEV(P,T,RO,RA,Y,YC,ID)
       RISULTATO=XK
       write(6,*)'YS=',YS,'TTEST=',TTEST
       GO TO 100
C
C--------------------------------------------
C
  100 CONTINUE
C
       OPEN(UNIT=52,FILE='tables.out')
       WRITE(52,*) RISULTATO
       WRITE(52,*) RISULTATO2
C
       IF(ICOUNT.GT.0) THEN
        IOUT=1
        ICOUNT=0
       ELSE
        IOUT=0
       ENDIF
C
       END
