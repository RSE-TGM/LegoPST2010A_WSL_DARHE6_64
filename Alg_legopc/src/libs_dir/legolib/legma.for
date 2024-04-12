CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGMA(NEQSIS,IPCJ,ICJ,NBL,ISLB,NUSTA,NUSCI,
     $   IPDATI,DATI,IP,TN,CDT,XYU,RN,ICONV,SIVAR,MX1,IPVRS,TOLL,
     $   RNO,XYO,JACYES,IPS,IPVRT,XY,UU,NU,IPI,IPVRI,ICBJ,
     $   FJ,PX,NEQAL,TEMPO,AJAC,MX5,NOBLC,MX3,RNI,
     $   IGRAD,ICN,IRN,IKEEP,IW,W,RHS,MXTER,tresi,tjaco,tma28a,
     $   tccc,nresi,njaco,naaa,nccc,npas,stampa1,
C___________ NUOVI PARAMETRI E TAVOLE
     $   IPVVSS,IPSSVV,IPVRSV,RNV,NQSISV,XYV,NQMODU,NQALV,NOSUB)
C
      CHARACTER*8 SIVAR(MX1)
      DIMENSION IPCJ(*),ICJ(*),ISLB(*),NUSTA(*),NUSCI(*),IPDATI(*),
     $   DATI(*),IP(*),TN(*),XYU(*),RN(*),ICONV(*),IPVRS(*),TOLL(*),
     $   RNO(*),XYO(*),IPS(*),IPVRT(*),XY(*),UU(*),IPI(*),IPVRI(*),
     $   ICBJ(*),FJ(*),PX(*),AJAC(MX5,MX5),NOBLC(MX3,2),RNI(*),
     $   ICN(*),IRN(*),IKEEP(*),IW(*),W(*),RHS(*),
C___________ NUOVI PARAMETRI E TAVOLE
     $   IPVVSS(*),IPSSVV(*),IPVRSV(*),RNV(*),XYV(*),NQMODU(*),NOSUB(*)
 
      real*4 etime,tmp(2),tt,tresi,tjaco,tma28a,tccc  
C     external etime                                       

      REAL TEMP,FITERT,FJAC,TTOT,TTRES,TTSOL,TTJAC
      DIMENSION ITITOL(20)
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
      COMMON/PARINT/ITITOL,TFIN,TSTEP,FATOLL,INTERR,TINTER
      COMMON/RSTRT1/TREST,IREGIM
      COMMON/SOLV00/JACSI

      CHARACTER*80 DESC(10), PSEUDO*8
      CHARACTER*4  IBL,SYITER,SYJACO,SYTCDT,SYTCRE,SYTCSO,SYTCJA
      DATA IALG /0/ IPHTIM /1/ IBL /'    '/
      DATA SYITER /'NITE'/ SYJACO /'NJAC'/ SYTCDT /'KTDT'/
      DATA SYTCRE /'KTRE'/ SYTCSO /'KTSO'/ SYTCJA /'KTJA'/

C     DESCRIZIONE DELLE VARIABILI

      DATA (DESC(I),I=1,6) /
     $'NITE      NUMERO DI ITERAZIONI PER OGNI PASSO DI INTEGRAZIONE',
     $'NJAC      NUMERO DI JACOBIANI  PER OGNI PASSO DI INTEGRAZIONE',
     $'KTDT      TEMPO DI CALCOLO (SEC) PER OGNI PASSO DI INTEGRAZIONE',
     $'KTRE      TEMPO DI CALCOLO (SEC) DEI RESIDUI PER OGNI PASSO
     $ DI INTEGRAZIONE',
     $'KTSO      TEMPO DI CALCOLO (SEC) DELLE SOLUZIONI PER OGNI
     $ PASSO DI INTEGRAZIONE',
     $'KTJA      TEMPO DI CALCOLO (SEC) DELLO JACOBIANO PER OGNI
     $ PASSO DI INTEGRAZIONE' /

C      RISOLVE IL SISTEMA ALG.-DIFF. COL METODO DI NEWTON-RAPHSON SMORZ.
C
C     DESCRIZIONE  DEI VETTORI
C       - MATRICE JACOBIANA -  IPCJ,ICJ,ICBJ,FJ
C       - RESIDUI-SOLUZIONI -   RN ,RNO, XY ,XYO
C       - INGRESSI  -          UU
C       - COEFF.PER EQU.DIFF. -   TN , CDT
C       - TOLLERANZE -           TOLL
C       - MATRICE COLLEG. DIRETTA -  IPVRS
C       - MATRICI COLLEG. INVERSE -  IPS,IPVRT , IPI,IPVRI
C       - DERIVATE  -  PX
C       - VETTORI IN INGRESSO TIPICI- ISLB,NUSTA,NUSCI,IP,XYU,
C                                      IPDATI,DATI,SIVAR
C       - VETTORI PER FATTORIZZAZIONE -  FJ,ICN,IRN,IKEEP,IW,W,RHS
C       - VETTORI DI COMODO  -  ICONV,AJAC(MX5,MX5)

      DATA NITERJ/7/NJACMX/10/ 
      DATA BETA/0.5/KBEMX/5/
      DATA UPIV/0.1/MTYPE/1/   !parametri ma28

      ITERT=0
      ITER=0
      JAC=0
      JOK=0
      VARR=0.
      TRES=0.
      TJAC=0.
      TSOL=0.
      IF(IGRAD.EQ.1)JACYES=1
      IF(IALG.EQ.1)JACYES=1
      
      if((npas.eq.1).and.(stampa1.eq.1))
     *write(55,*)'  metodo ma28' 

      CALL SSVV(NEQSIS,IPSSVV,XY,XYV) ! carica xy in xyv
      ICONVE=0
      DO WHILE(ICONVE.EQ.0)

        ICONVE=1           !calcolo residui
        CALL CLOC (CPUT1)
C       tt=etime(tmp)                                      
        CALL LEGRES(NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,IP,TN,CDT,XYU,RN,
     $       ICONV,SIVAR,MX1,NEQSIS,IPVRS,TOLL,ICONVE,NOBLC,MX3,RNI,
     $       IPVVSS,IPSSVV,RNV,XY,IPS,IPVRT,NOSUB) 
C       tt=etime(tmp)-tt                                   
        tresi=tresi+tt                                     
        nresi=nresi+1                                      
        CALL CLOC (CPUT2)
        TRES = (CPUT2-CPUT1)

        IF(NQSISV.GT.0)THEN !se non ci sono eq. da risolvere, fine del calcolo
        
        IF((ICONVE.EQ.0).OR.(ITERT.EQ.0))THEN
          VAR=SNRM2(NQSISV,RNV,1)/NQSISV  ! norma residui
          if(stampa1.eq.1)write(55,555)tt,var,iter,itert,iconve 
          IF(JACSI.EQ.1)JACYES=1

          IF((JACYES.EQ.0).AND.(ITERT.GT.0))THEN
            IF((VAR.LE.VARR).AND.(ITER.GE.NITERJ))THEN 
              JACYES=1 !superato numero max iterazioni, calcolare lo jacobiano 
            ELSEIF(VAR.GT.VARR)THEN !difficoltà di convergenza
              CALL SSWTCH(4,LL)
              IF(LL.EQ.1)WRITE(6,1000)VAR,VARR 
              IF(JOK.EQ.0)THEN
                CALL SCOPY(NEQSIS,RNO,1,RN,1)   ! copia rno in rn
                CALL SCOPY(NEQSIS,XYO,1,XY,1)   ! copia xyo in xy
                CALL SSVV(NEQSIS,IPSSVV,XY,XYV) ! carica xy in xyv
                CALL SSVV(NEQSIS,IPSSVV,RN,RNV) ! carica rn in rnv
                JACYES=1    ! calcolare lo jacobiano
              ELSEIF(KBETA.LT.KBEMX)THEN  !correzioni delle soluzioni con beta
                KBETA=KBETA+1  
                CALL SAXPY(NEQSIS,1.,XYO,1,XY,1)  !  xy=xy+xyo
                CALL SSCAL(NEQSIS,BETA,XY,1)       !  xy=(1/2)xy 
                CALL SSVV(NEQSIS,IPSSVV,XY,XYV)   !  carica xy in xyv
                CALL LEGBL1(NEQSIS,IPS,IPVRT,XY,XYU)
                CALL LEGBL1(NU,IPI,IPVRI,UU,XYU)
              ELSE
                ICONVE=-1  ! soluzione non trovata             
              ENDIF
            ENDIF
          ENDIF

          IF(JACYES.EQ.1)THEN
            JACYES=0
            IF(JAC.LT.NJACMX)THEN
              ITER=0
              JOK=1
              JAC=JAC+1
              IALG=0
              IF(IGRAD.EQ.1)IALG=1
              CALL CLOC (CPUT1)
C             tt=etime(tmp)                               
              CALL LEGBL1(NEQSIS,IPS,IPVRT,XY,XYU)    
              CALL LEGBL1(NU    ,IPI,IPVRI,UU,XYU)
              CALL LEGJAC1(NBL,ISLB,IPDATI,IP,XYU,DATI,IPVRSV,NQMODU,
     $        NUSTA,IPCJ,ICBJ,FJ,CDT,NQSISV,ICJ,AJAC,MX5,NOBLC,MX3,
     $        RNI,ICN,IRN,IGRAD,NQALV,NTER,NOSUB) !calcolo jacobiano
C             tt=etime(tmp)-tt                             
              tjaco=tjaco+tt                               
              njaco=njaco+1                                
              if(stampa1.eq.1)write(55,550)tt,nter,ipcj(nqsisv+1)-1
C             tt=etime(tmp)                                
              CALL MA28A(NQSISV,NTER,FJ,MXTER,IRN,MXTER,ICN,UPIV,
     $                   IKEEP,IW,W,IFLAG)  ! fattorizzazione
C             tt=etime(tmp)-tt                
              tma28a=tma28a+tt                
              naaa=naaa+1                     
              if(stampa1.eq.1)write(55,*)'tempo ma28a    ',tt   
              IF(IFLAG.NE.0)THEN
                CALL ER28A(IFLAG)
                IF(IFLAG.LE.2)THEN
                  CALL SING(NQSISV,IPVVSS,SIVAR,IKEEP,stampa1) !stampa singolarità
                ELSE
                  CALL LGABRT
                ENDIF
              ENDIF
              CALL CLOC (CPUT2)
              TJAC = (CPUT2-CPUT1)
            ELSE  !superamento numero massimo jacobiani
              ICONVE=-1
              WRITE(6,1005)TEMPO
            ENDIF  
          ENDIF
              
          IF((ITER.EQ.0).OR.((VAR.LE.VARR).AND.(ITER.LT.NITERJ)))THEN 
            IF((ITERT.EQ.0).OR.(VAR.LE.VARR))THEN
              CALL SCOPY(NEQSIS,XY,1,XYO,1)  ! copia xy in xyo
              CALL SCOPY(NEQSIS,RN,1,RNO,1)  ! copia rn in rno
              VARR=VAR                                
            ENDIF
            IF(ITER.EQ.1)JOK=0
            KBETA=0              
            ITER=ITER+1
            ITERT=ITERT+1
            CALL CLOC (CPUT1)
            CALL SCOPY(NQSISV,RNV,1,RHS,1)  ! copia rnv in rhs
C           tt=etime(tmp)                             
            CALL MA28C(NQSISV,FJ,MXTER,ICN,IKEEP,RHS,W,MTYPE)! risoluzione
C           tt=etime(tmp)-tt                        
            tccc=tccc+tt                              
            nccc=nccc+1                              
            if(stampa1.eq.1)write(55,*)'tempo ma28c    ',tt 
            CALL SAXPY(NQSISV,1.,RHS,1,XYV,1) ! xyv=xyv+rhs aggiornamento
            CALL VVSS(NQSISV,IPVVSS,XYV,XY)   ! carica xyv in xy 
            CALL LEGBL1(NEQSIS,IPS,IPVRT,XY,XYU)
            CALL LEGBL1(NU,IPI,IPVRI,UU,XYU)
            CALL CLOC (CPUT2)
            TSOL = (CPUT2-CPUT1)
            ICONVE=0
          ENDIF
        ENDIF
        ENDIF
      ENDDO
      
      IF(NQSISV.GT.0)THEN
        IF(ICONVE.EQ.-1)THEN      !soluzione non trovata
          WRITE(6,1003)TEMPO
          WRITE(6,7656)VAR
          WRITE(6,3060)
          KE=0
          DO I=1,NEQSIS
            IF(ICONV(I).NE.0)THEN
              KE=KE+1
              WRITE(6,3061)KE,SIVAR(I),RN(I)
            ENDIF
          ENDDO
        ENDIF
        
        if(stampa1.eq.1)then
          if(iconve.eq.1)then                              
          var=snrm2(nqsisv,rnv,1)/nqsisv                    
          write(55,555)tt,var,iter,itert,iconve  
          endif                                             
        endif 
          
C     calcolo delle derivate ricordando che -XN+CDT*F(XN)+TN =RN
C                                         F(XN)=(RN-TN +XN)*1/CDT
        NEQD= NEQSIS-NEQAL
        CDDT=CDT
        IF(IGRAD.EQ.1)THEN  !la perturbazione è un gradino
          CDDT=1.           !calcolo le derivate a T=tempo+
          JACYES=1
C         tt=etime(tmp)                   
          CALL LEGRES(NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,IP,TN,
     $                CDDT,XYU,RN,ICONV,SIVAR,MX1,NEQSIS,IPVRS,
     $                TOLL,ICONVE,NOBLC,MX3,RNI,
     $                IPVVSS,IPSSVV,RNV,XY,IPS,IPVRT,NOSUB) 
C         tt=etime(tmp)-tt                
          tresi=tresi+tt                  
          nresi=nresi+1                   
          if(stampa1.eq.1)write(55,*)'tempo residui  ',tt  
        ENDIF
        DO I=1,NEQD
          K=NEQAL+I
          PX(I)=(RN(K)-TN(I)+XY(K))/CDDT
        ENDDO
        CALL LEGBL1(NEQSIS,IPS,IPVRT,XY,XYU)
        CALL LEGBL1(NU,IPI,IPVRI,UU,XYU)
      ENDIF

C            apertura file 21 per registrazione tempi di calcolo
      NWO=6
      IF(IPHTIM.NE.0)THEN
        IPHTIM=0
        IF(IREGIM.EQ.2)THEN
          IER=0
          CALL FILPOS(21,TREST,NWO,IER)
          IF (IER.NE.0) CALL LGABRT
        ELSE
          TREST=0.
          REWIND 21
          WRITE(21)(ITITOL(I),I=1,20)
          WRITE(21)NWO,SYITER,IBL,SYJACO,IBL,SYTCDT,IBL,SYTCRE,IBL,
     $           SYTCSO,IBL,SYTCJA,IBL,PSEUDO,NWO,(DESC(I),I=1,NWO)
        ENDIF
      ENDIF
C                      registrazione file 21 tempi di calcolo
      FITERT=ITERT
      FJAC=JAC
      TTOT=(TRES+TSOL)*ITERT+TRES+TJAC*JAC
      TTRES=TRES*(ITERT+1)
      TTSOL=TSOL*ITERT
      TTJAC=TJAC*JAC
      TEMP=TEMPO+TREST
      WRITE(21)TEMP,FITERT,FJAC,TTOT,TTRES,TTSOL,TTJAC
      CALL SSWTCH(3,LL)
      IF(LL.EQ.1)THEN
        WRITE(6,3152)TEMPO,ITERT,JAC,CDT
        WRITE(6,3163)TRES,TSOL,TJAC
      ENDIF
      RETURN

  555 FORMAT(1x,'tempo residui var iter itert iconve',
     $       2(2x,1pe13.7),3x,3i3)
  550 FORMAT(1x,'tempo jacobiano',1pe,'   nonzeri veri finti',2i7)    
 1000 FORMAT(///10X,'DIFFICOLTA DI CONVERGENZA N(I)= ',E15.8,1X,
     $   '  N(I-1) =',E15.8)          
 1005 FORMAT(///10X,'SUPERATO IL NUMERO MASSIMO DI JACOBIANI DURANTE ',
     $   'LA SOLUZIONE '/10X,'DEL SISTEMA ALG-DIFF AL TEMPO ', F8.3 //)
 1003 FORMAT(//10X,'NON RIESCO A RISOLVERE IL SISTEMA ALG-DIFF AL TEMPO'
     $      ,F8.3)
 7656 FORMAT(10X,'NORMA RESIDUI= ',E15.8//)
 3060 FORMAT(//10X,'EQUAZIONI NON SODDISFATTE'//)
 3061 FORMAT(I6,2X,A8,2X,E12.5)
 3152 FORMAT(//10X,'SOL.SIS.ALG.-DIFF. AL TEMPO  ',F8.2/10X,
     $   'ITER.SOL.-RES.',I6/10X,'JACOBIANI',I6/,10X,'CDT=',F8.2//)
 3163 FORMAT(10X,'TEMPO CALC. RESIDUI=',F10.5,'(SEC)',/10X,
     $   'TEMPO CALC. SOLUZIONI A/I =',F10.5,'(SEC)'/10X,
     $   'TEMPO CALC. E FATT. JACOBIANO=',F10.5,'(SEC)'//)
      END


