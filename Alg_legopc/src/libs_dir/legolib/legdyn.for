CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LEGDYN(RESTAR)
C
C     DEL PROGRAMMA  LG5
C
C      INCLUDE 'LG5_PARAMETER.F'
C**   Descrizione delle parameter di LG5
C**
C**   N000= MOLTIPLICATORE
C**
C**   N001= N. MODULI
C**   N002= N. BLOCCHI
C**   N003= N.STATI+ALG. = ORDINE MASSIMO SISTEMA ALGEBRICO
C**   N004= N. INGRESSI
C**   N005= N. VARIABILI
C**   N006= N. VAR. DI 1 BLOCCO
C**   N007= N. DI DATI
C**   N008= N. DI EQUAZIONI DI UN BLOCCO
C**   NR00= N. DI TERMINI #0 PER OGNI EQUAZIONE
C**   NP00= N. DI PERTURBAZIONI
C
      PARAMETER (N000=70, N001=N000*10, N002=N000*25, N003=N000*50,
     $           N004=N000*25, N005=N000*100, N006=100,
     $           N007=N000*500, N008=40, NR00=12, NR01=70, NR02=50,
cc     $           N007=N000*500, N008=40, NR00=12, NR01=70, NR02=18,
     $           NP00=10)
C
      PARAMETER (M003 = N002+1, M004 = N003+1, M005 = N004+1,
     $           M001 = N005-N003, M002 = M001-N004)
C
C**      M006 = N. TERMINI # 0 DELLO JACOBIANO
C**      M007 = N. TERMINI # 0 DELLO JACOBIANO FATTORIZZATO
C**      M010 = N.VARIABILI IN OUTPUT
C
      PARAMETER (M006 = N003*NR00, M007 = 2*M006, M008 = 5*N003,
     $           M009 = 8*N003, M010 = N004+N003, MP01 = NP00+1,
     $           MP02 = NP00*200)
      PARAMETER (NZP00=N003*NR01,NZG0=N003*NR02,N00Q=N003*100)      
C
C**************DATI GENERALI
C
      DIMENSION NOSL(N001),NOSUB(N002),NOBLC(N002,2),NUSTA(N002),
     $          NUSCI(N002),NINGR(N002),ISLB(N002),IP(M003),IPVRS(N005),
     $          IPS(M004),IPVRT(N005),IPI(M005),IPVRI(M001),
     $          XY(N003),UU(N004),XYU(N005),DATI(N007),IPDATI(M003),
     $          CNXYU(N005),IPLOT(N003),ISTMP(N003),TOLL(N003),
     $          IVPER(NP00),ITPER(NP00),IPPER(MP01),DATPER(MP02)
      COMMON/C0LG5A/XY,UU,XYU,DATI,CNXYU,TOLL,DATPER,NOSL,NOSUB,NOBLC,
     $              NUSTA,NUSCI,NINGR,ISLB,IP,IPVRS,IPS,IPVRT,IPI,
     $              IPVRI,IPDATI,IPLOT,ISTMP,IVPER,ITPER,IPPER
C
C*********MEMORIA PER LA MATRICE JACOBIANA
C
      DIMENSION IPCJ(M004),ICJ(M006),ICBJ(M006),FJ(M007),ICN(M007),
     $          IRN(M007),IKEEP(M008),IW(M009),W(N003),RHS(N003),
     $          AJAC(N008,N006),RNI(N003),RIGA(N003)
      COMMON/C0LG5B/FJ,W,RHS,AJAC,RNI,RIGA,
     $              IPCJ,ICJ,ICBJ,ICN,IRN,IKEEP,IW
C
C*********MEMORIA PER RIDEFINIZIONE DELLE REALI DIMENSIONI DEL SISTEMA
C
      DIMENSION NQMODU(N002),IPVRSV(N005),
     $          IPVVSS(N003),IPSSVV(N003),RNV(N003),XYV(N003)
      COMMON/C0LG5C/RNV,XYV,NQMODU,IPVRSV,IPVVSS,IPSSVV
C
C*********VARIABILI DI TIPO CARATTERE
C
      CHARACTER*8 VAR(N005),SIVAR(N003),VARI(N004),VARSYS(N003)
      COMMON/C0LG5D/VAR,SIVAR,VARI,VARSYS
C
C*********MEMORIA PER IL METODO QUASI-NEWTON
C
      DIMENSION QN1(N00Q),QN2(N00Q),QN3(N003),QN4(N003)
C
C*********MEMORIA PER LA SOLUZIONE DEL SISTEMA
C
      DIMENSION TN(N003),PX(N003),ICONV(N003)
      DIMENSION RN(N003),RNO(N003),XYO(N003),CNXY(N003),CNUU(N004),
     $          UUP(N004),XYOUT(M010),IVECT(M006),JVECT(M006)
      COMMON/DDDDD/TN,RN !subroutine dres
C
      EQUIVALENCE (IVECT(1),IRN(1)),(JVECT(1),IRN(M006+1)),
     $            (RIGA(1),ICONV(1))
C     
C********* PARAMETRI PER STAMPE
C stampa1 =1 STAMPA TEMPI E INFORMAZIONI OGNI PASSO (file stampa), =0 NON STAMPA
C stampa2 =1 STAMPA TEMPI FINALI (file stampa), = 0 NON STAMPA       
C stampa3 =1 STAMPA TEMPO OGNI PASSO (file tempo), = 0 NON STAMPA       
C      
      PARAMETER(stampa1=0,stampa2=0,stampa3=0)     
C
      CHARACTER*100 GIASEL(N005+N002)
      CHARACTER*8 NMMODU,SIGLA,SYOUT(M010)
      COMMON/VARDE1/NSEL
      COMMON/VARDE2/GIASEL,NMMODU
C
      DIMENSION ITITOL(20)
      COMMON/NORM/P0,H0,T0,Q0,R0,AL0,V0,DP0
      COMMON/DIMAJA/NRXJC,NCXJC
      COMMON/PARINT/ITITOL,TFIN,TSTEP,FATOLL,INTERR,TINTER
      COMMON/INTEGR/TSTOP,TEMPO,DTINT,NPAS,CDT,ALFADT
      COMMON/INPAR1/NBL,NEQAL,NEQSIS,NU,NST,NVART,NPVRT,NVRI,NDATI
      COMMON/INPARV/NQALV,NQSISV
      COMMON/PARPAR/NPER,NVPLT,NVSTP,NSTPLT,NSTSTP,KPLT,KSTP,ITERT
C%%% TOLLERANZA ASSEGNATA RUN_TIME DAI MODULI
      COMMON/TOLEG00/TOLIN(N008)
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 15 FEB 87 <<<<<<<<<<<<<<<<<<<<<<<<<
      COMMON/FIXPAS/PASFIX
      LOGICAL PASFIX
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 15 FEB 87 <<<<<<<<<<<<<<<<<<<<<<<<<
      LOGICAL RESTAR
C********************** TAVOLE ******************************
C       ILEGO = INDICATORE DEL PROGRAMMA CHIAMANTE LE TAVOLE
C             =1 LEGO E` IL PROGRAMMA CHIAMANTE
C             =0 NON E` IL LEGO IL PROGRAMMA CHIAMANTE
C
C       ICNTMX = CONTATORE STABILITO DAL PROGRAMMA CHIAMANTE LE TAVOLE
C                  SUPERATO IL QUALE VIENE DECRETATO LO STOP .
C
c.......................................................................
      CHARACTER*1 CHABS
      real*4 etime,tmp(2),tt,tpas
C     external etime
c....................................................................... 
      COMMON/LGTV01/LGTEMP,ILEGO,ICOUNT,ICNTMX
      COMMON/LGTV02/LGMODU,LGBLOC
      CHARACTER*8 LGMODU,LGBLOC
      REAL LGTEMP
      ILEGO = 1
C********************** TAVOLE ******************************
      NX2=N002
      NX3=N003
      NX4=N004
      NX8=N008
      MX7=M007
      MX10=M010
      NZPMX=NZP00
      NZGMX=NZG0

      ALFADT=0.63
      
      if((stampa1.eq.1).or.(stampa2.eq.1))
     *open(unit=55,file='stampa',status='unknown',form='formatted')
      if(stampa3.eq.1)
     *open(unit=66,file='tempo',status='unknown',form='formatted')
      tresi=0.
      tjaco=0.
      tjacop=0.
      taaa=0.
      tbbb=0.
      tccc=0.
      nresi=0
      njaco=0
      njacop=0
      naaa=0
      nbbb=0
      nccc=0
C     tt=etime(tmp)

C     BLOCCO DEL PASSO DI INTEGRAZIONE SE RICHIESTO DALL'UTENTE

C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 15 FEB 87 <<<<<<<<<<<<<<<<<<<<<<<<<
      PASFIX=.FALSE.
      IF(FATOLL.LT.0)PASFIX=.TRUE.
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 15 FEB 87 <<<<<<<<<<<<<<<<<<<<<<<<<
      
      CALL EQBL(NBL,NUSTA,NUSCI,IEQBL)
      CALL BLLEG1(IPVRS,NVART,CNXYU,CNXY,CNUU)

C       INIZIALIZZAZIONE FILE DI OUTPUT

      IVAI=1
      CALL RECOUT(IVAI,NVPLT,IPLOT,NSTPLT,TSTEP,TFIN,IGRAD,TEMPO,
     $                  SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,CNXY,CNUU,
     $  XYOUT,SYOUT,MX10,ITITOL,KPLT,NPER,NSEL,GIASEL,NMMODU)
      CALL LEGPRI(IVAI,NSTSTP,TSTEP,TFIN,ITITOL,IGRAD,NVSTP,
     $                  ISTMP,SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,
     $                  CNXY,CNUU,XYOUT,SYOUT,MX10,TEMPO,KSTP)

C      CALCOLO DELLE DERIVATE PX(0)

      NEQDIF=NEQSIS-NEQAL
      CDT=1.
      IF(NEQDIF.GT.0) THEN
	  DO 5 I=1,NEQDIF
	  K=NEQAL+I
	  TN(I)=XY(K)
    5 CONTINUE
      ENDIF
      ICONVE=1
C
      CALL LEGRES(NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,IP,TN,CDT,XYU,
     $             RN,ICONV,SIVAR,NX3,NEQSIS,IPVRS,TOLL,ICONVE,
     $             NOBLC,NX2,RNI,
C_________ NUOVI PARAMETRI
     $                  IPVVSS,IPSSVV,RNV,XY,IPS,IPVRT,
C********************** TAVOLE ******************************
     $                  NOSUB)
C
      IF(NEQDIF.GT.0) THEN
	 DO 10 I=1,NEQDIF
	 K=NEQAL+I
	 PX(I)=RN(K)
   10 CONTINUE
      ENDIF
C
C      INIZIALIZZAZIONE
C
      NPAS=0
      TEMPO=0.
C********************** TAVOLE ******************************
      LGTEMP=TEMPO
C********************** TAVOLE ******************************

      CDT=0.
      CDTN=0.
      WRITE(6,*)' Metodo implicito con alfa = ',ALFADT

      IVAI=2
      JACYES=1
      IGO=1
      ICDTR=0
      KSTEP=0

C      LETTURA DATI ED INIZIALIZZAZIONE REGOLAZIONE

C      STAMPA E REGISTRAZIONE 0-

      CALL RECOUT(IVAI,NVPLT,IPLOT,NSTPLT,TSTEP,TFIN,IGRAD,TEMPO,
     $                  SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,CNXY,CNUU,
     $  XYOUT,SYOUT,MX10,ITITOL,KPLT,NPER,NSEL,GIASEL,NMMODU)
      CALL LEGPRI(IVAI,NSTSTP,TSTEP,TFIN,ITITOL,IGRAD,NVSTP,
     $                  ISTMP,SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,
     $                  CNXY,CNUU,XYOUT,SYOUT,MX10,TEMPO,KSTP)
  11  WRITE(6,302) 
  302 FORMAT(//10X,'RISOLVERE CON'
     $       /10X,'M = MA28',  
     $       /10X,'N = QUASI-NEWTON (MA28)')
      READ(5,'(A1)') CHABS
      IF (CHABS.EQ.'M'.OR.CHABS.EQ.'m') THEN
	  WRITE(6,*) '*********** RISOLUZIONE CON MA28'
      ELSEIF (CHABS.EQ.'N'.OR.CHABS.EQ.'n') THEN
	  WRITE(6,*) '*********** RISOLUZIONE CON QUASI-NEWTON (MA28)' 
      ELSE
          WRITE(6,*) '******** SCELTE POSSIBILI M OPPURE N !!' 
          GOTO 11
      ENDIF
      WRITE(6,*)

      IF (CHABS.EQ.'N'.OR.CHABS.EQ.'n') THEN
         IQNMX=(NQSISV*2)/3  !numero massimo di passi per il metodo quasi-newton
         IF((N00Q/NQSISV).LT.IQNMX)THEN
            WRITE(6,*)'memoria insufficiente per il metodo quasi-newton'
            CALL LGABRT
         ENDIF
      ENDIF
      
C      LOOP DI INTEGRAZIONE

  999 CONTINUE
C
      DO 15 I=1,NU
      UUP(I)=UU(I)
   15 CONTINUE

C      ESECUZIONE PERTURBAZIONI AL TEMPO = TEMPO+DTINT
C
      CALL PERTUR(NPER,ITPER,IPPER,IVPER,DATPER,UU,NU,
     $         VARI,NX4,TEMPO,TSTEP,DTINT,IGRAD)
C
      IF(TEMPO.EQ.0.)GO TO 18
      IF(IGRAD.EQ.0)GO TO 18
C
C      LA PERTURBAZIONE E' UN GRADINO
C
C      STAMPA E REGISTRAZIONE T-
C
      IF(KPLT.EQ.1)GO TO 16
      CALL RECOUT(IVAI,NVPLT,IPLOT,NSTPLT,TSTEP,TFIN,IGRAD,TEMPO,
     $                  SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UUP,CNXY,CNUU,
     $  XYOUT,SYOUT,MX10,ITITOL,KPLT,NPER,NSEL,GIASEL,NMMODU)
   16 IF(KSTP.EQ.1)GO TO 18
      CALL LEGPRI(IVAI,NSTSTP,TSTEP,TFIN,ITITOL,IGRAD,NVSTP,
     $                  ISTMP,SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UUP,
     $                  CNXY,CNUU,XYOUT,SYOUT,MX10,TEMPO,KSTP)
C
C      ESECUZIONE DI UN PASSO DI INTEGRAZIONE
C
   18 CONTINUE
C
      ICDTU=1
      DO 20 I=1,NU
      AAB=ABS(UUP(I)-UU(I))
      IF(AAB.GT.1.E-8)ICDTU=0
   20 CONTINUE
      ICDT=ICDTR*ICDTU
C
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 15 FEB 87 <<<<<<<<<<<<<<<<<<<<<<<<<
      IF(PASFIX)ICDT=0
C>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> 15 FEB 87 <<<<<<<<<<<<<<<<<<<<<<<<<
      NPAS=NPAS+1
      TEMPO= TEMPO+ DTINT
C********************** TAVOLE ******************************
      LGTEMP=TEMPO
C********************** TAVOLE ******************************
      CDT =DTINT*ALFADT + CDT*ICDT
      CDTN=DTINT*(1.-ALFADT) + CDTN*ICDT
      IF(ICDT.EQ.0)GO TO 27
      IF(NSTEP.NE.0)GO TO 28
      NSTEP=999
      IF(NEQDIF.GT.0) THEN
	 DO 25  I=1,NEQDIF
	 NSTP=999
	 APX=ABS(PX(I))*DTINT
	 IF(APX.LT.1.E-8)GO TO 25
	 NSTP=TOLL(NEQAL+I)/APX-1
	 IF(NSTEP.GT.NSTP)NSTEP=NSTP
   25 CONTINUE
      ENDIF
C
      KSTEP=0
      GO TO 28
   27 NSTEP=0
   28 KSTEP=KSTEP+1
      IF (KSTEP.LE.NSTEP) GO TO 31
      IF (NEQDIF.GT.0) THEN
	 DO 30 I=1,NEQDIF
	 M=NEQAL+I
	 TN(I)= XY(M) + CDTN*PX(I)
   30 CONTINUE
      ENDIF
C
C     RISOLUZIONE DEL SISTEMA ALGEBRICO-DIFFERENZIALE
C
      CALL LEGBL1(NEQSIS,IPS,IPVRT,XY,XYU)
      CALL LEGBL1(NU,IPI,IPVRI,UU,XYU)

      if(stampa1.eq.1)write(55,550)npas,tempo
  550 format(/'passo ',i5,'    tempo',f)
C     tpas=etime(tmp)
      IF (CHABS.EQ.'M'.OR.CHABS.EQ.'m') THEN
         CALL LEGMA(NEQSIS,IPCJ,ICJ,NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,
     $         IP,TN,CDT,XYU,RN,ICONV,SIVAR,NX3,IPVRS,TOLL,RNO,XYO,
     $         JACYES,IPS,IPVRT,XY,UU,NU,IPI,IPVRI,
     $         ICBJ,FJ,PX,NEQAL,TEMPO,AJAC,NX8,NOBLC,NX2,RNI,
     $         IGRAD,ICN,IRN,IKEEP,IW,W,RHS,MX7,
     $         tresi,tjaco,taaa,tccc,nresi,njaco,naaa,
     $         nccc,npas,stampa1,
     $         IPVVSS,IPSSVV,IPVRSV,RNV,NQSISV,XYV,NQMODU,NQALV,
     $         NOSUB)    
      ELSEIF (CHABS.EQ.'N'.OR.CHABS.EQ.'n') THEN
         CALL LEGMAQN(NEQSIS,IPCJ,ICJ,NBL,ISLB,NUSTA,NUSCI,IPDATI,DATI,
     $         IP,TN,CDT,XYU,RN,ICONV,SIVAR,NX3,IPVRS,TOLL,RNO,XYO,
     $         JACYES,IPS,IPVRT,XY,UU,NU,IPI,IPVRI,
     $         ICBJ,FJ,PX,NEQAL,TEMPO,AJAC,NX8,NOBLC,NX2,RNI,
     $         IGRAD,ICN,IRN,IKEEP,IW,W,RHS,MX7,
     $         IQNMX,QN1,QN2,QN3,QN4,
     $         tresi,tjaco,taaa,tccc,
     $         nresi,njaco,naaa,nccc,npas,stampa1,
     $         IPVVSS,IPSSVV,IPVRSV,RNV,NQSISV,XYV,NQMODU,NQALV,
     $         NOSUB)                      
      ELSE
         WRITE(6,*) 'METODO INESISTENTE'
         STOP   
      ENDIF
C     tpas=etime(tmp)-tpas 
      if(stampa3.eq.1)write(66,*)tempo,tpas  
C********************** TAVOLE ******************************

C      CALCOLO MATRICE JACOBIANA RETTANGOLARE DEL MODELLO LINEAR.

   31 CONTINUE

C     STAMPE PASSO PASSO

      CALL RECOUT (IVAI,NVPLT,IPLOT,NSTPLT,TSTEP,TFIN,IGRAD,TEMPO,
     $            SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,CNXY,CNUU,XYOUT,
     $            SYOUT,MX10,ITITOL,KPLT,NPER,NSEL,GIASEL,NMMODU)
      CALL LEGPRI (IVAI,NSTSTP,TSTEP,TFIN,ITITOL,IGRAD,NVSTP,
     $            ISTMP,SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,
     $            CNXY,CNUU,XYOUT,SYOUT,MX10,TEMPO,KSTP)

C      TEST  FINE TRANSITORIO

      IGO=0
      IF (TEMPO.LT.TFIN) GO TO 999
      WRITE(6,96)
   96 FORMAT(///10X,'FINE DEL CALCOLO PASSO-PASSO DEL TRANSITORIO')
   
C     tt=etime(tmp)-tt
      if(stampa2.eq.1)then
      write(55,*)
      if(chabs.eq.'M'.or.chabs.eq.'m')then
      write(55,*)' metodo ma28'
      elseif(chabs.eq.'S'.or.chabs.eq.'s')then
      write(55,*)' metodo gram schmidt'      
      elseif(chabs.eq.'P'.or.chabs.eq.'p')then
      write(55,*)' metodo jacobiano parziale  ma28'                     
      elseif(chabs.eq.'J'.or.chabs.eq.'j')then
      write(55,*)' metodo jacobiano parziale  gram schmidt'      
      elseif(chabs.eq.'N'.or.chabs.eq.'n')then
      write(55,*)' metodo quasi-newton - ma28'      
      elseif(chabs.eq.'Q'.or.chabs.eq.'q')then
      write(55,*)' metodo quasi-newton   gram schmidt'      
      elseif(chabs.eq.'U'.or.chabs.eq.'u')then
      write(55,*)' metodo quasi-newton (jacobiano parziale) ma28'          
      else
      write(55,*)' metodo quasi-newton tempo variabile'
      endif
      write(55,*)
      write(55,*)'tempo residui   ',tresi,tresi/nresi,nresi
      write(55,*)'tempo jacobiano ',tjaco,tjaco/njaco,njaco
      if(chabs.eq.'M'.or.chabs.eq.'m')then
      write(55,*)'tempo ma28a     ',taaa,taaa/naaa,naaa
      if(nbbb.ne.0)then
      write(55,*)'tempo ma28b     ',tbbb,tbbb/nbbb,nbbb
      write(55,*)'tempo ma28a+b   ',taaa+tbbb,(taaa+tbbb)/(naaa+nbbb),
     *                              naaa+nbbb
      endif
      write(55,*)'tempo ma28c     ',tccc,tccc/nccc,nccc
      write(55,*)'tempo r+j+ma+b+c',tresi+tjaco+taaa+tbbb+tccc
      write(55,*)'tempo totale    ',tt
      elseif(chabs.eq.'S'.or.chabs.eq.'s')then
      write(55,*)'tempo gsa       ',taaa,taaa/naaa,naaa
      write(55,*)'tempo gsb       ',tbbb,tbbb/nbbb,nbbb
      write(55,*)'tempo r+j+a+b   ',tresi+tjaco+taaa+tbbb
      write(55,*)'tempo totale    ',tt 
	   
      elseif(chabs.eq.'P'.or.chabs.eq.'p')then
      if(njacop.ne.0)then
      write(55,*)'tempo jac.parz. ',tjacop,tjacop/njacop,njacop
      write(55,*)'tempo jac+jac.p.',tjaco+tjacop,
     *            (tjaco+tjacop)/(njaco+njacop),njaco+njacop
      endif
      write(55,*)'tempo ma28a     ',taaa,taaa/naaa,naaa
      if(nbbb.ne.0)then
      write(55,*)'tempo ma28b     ',tbbb,tbbb/nbbb,nbbb
      write(55,*)'tempo ma28a+b   ',taaa+tbbb,(taaa+tbbb)/(naaa+nbbb),
     *                              naaa+nbbb
      endif
      write(55,*)'tempo ma28c     ',tccc,tccc/nccc,nccc
      write(55,*)'tempo r+j+ma+b+c',tresi+tjaco+tjacop+taaa+tbbb+tccc
      write(55,*)'tempo totale    ',tt 
			       
      elseif(chabs.eq.'J'.or.chabs.eq.'j')then
      if(njacop.ne.0)then
      write(55,*)'tempo jac.parz. ',tjacop,tjacop/njacop,njacop
      write(55,*)'tempo jac+jac.p.',tjaco+tjacop,
     *            (tjaco+tjacop)/(njaco+njacop),njaco+njacop
      endif
      write(55,*)'tempo fat.      ',taaa,taaa/naaa,naaa
      if(nccc.ne.0)then
      write(55,*)'tempo fat.mod.  ',tccc,tccc/nccc,nccc
      write(55,*)'tempo fat+f.mod.',taaa+tccc,
     *            (taaa+tccc)/(naaa+nccc),naaa+nccc
      endif
      write(55,*)'tempo x         ',tbbb,tbbb/nbbb,nbbb
      write(55,*)'tempo r+j+fat+x ',tresi+tjaco+tjacop+taaa+tccc
      write(55,*)'tempo totale    ',tt
      
      elseif(chabs.eq.'N'.or.chabs.eq.'n')then
      write(55,*)'tempo ma28a     ',taaa,taaa/naaa,naaa
      write(55,*)'tempo qn        ',tccc,tccc/nccc,nccc
      write(55,*)'tempo r+j+a+qn  ',tresi+tjaco+taaa+tccc
      write(55,*)'tempo totale    ',tt 
	    
      elseif(chabs.eq.'U'.or.chabs.eq.'u')then
      if(njacop.ne.0)then
      write(55,*)'tempo jac.parz. ',tjacop,tjacop/njacop,njacop
      write(55,*)'tempo jac+jac.p.',tjaco+tjacop,
     *            (tjaco+tjacop)/(njaco+njacop),njaco+njacop
      endif
      write(55,*)'tempo ma28a     ',taaa,taaa/naaa,naaa
      if(nbbb.ne.0)then
      write(55,*)'tempo ma28b     ',tbbb,tbbb/nbbb,nbbb
      write(55,*)'tempo ma28a+b   ',taaa+tbbb,(taaa+tbbb)/(naaa+nbbb),
     *                              naaa+nbbb
      endif
      write(55,*)'tempo qn        ',tccc,tccc/nccc,nccc
      write(55,*)'tempo r+j+a+b+qn',tresi+tjaco+tjacop+taaa+tbbb+tccc
      write(55,*)'tempo totale    ',tt      
	   
      else
      write(55,*)'tempo gsa       ',taaa,taaa/naaa,naaa
      write(55,*)'tempo qn        ',tccc,tccc/nccc,nccc
      write(55,*)'tempo r+j+a+qn  ',tresi+tjaco+taaa+tccc
      write(55,*)'tempo totale    ',tt       
      endif
      endif      
      if((stampa1.eq.1).or.(stampa2.eq.1))close(55)
      if(stampa3.eq.1)close(66)      
      RETURN
      END
