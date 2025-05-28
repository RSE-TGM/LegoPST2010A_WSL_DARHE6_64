CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE LGDYNINI(RESTAR)
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
      PARAMETER (N000=160, N001=N000*10, N002=N000*25, N003=N000*50,
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
C*********MEMORIA PER LA SOLUZIONE DEL SISTEMA
C
      DIMENSION TN(N003),PX(N003),ICONV(N003)
      DIMENSION RN(N003),CNXY(N003),CNUU(N004),
     $          UUP(N004),XYOUT(M010),IVECT(M006),JVECT(M006)
      COMMON/DDDDD/TN,RN !subroutine dres
C
      EQUIVALENCE (IVECT(1),IRN(1)),(JVECT(1),IRN(M006+1)),
     $            (RIGA(1),ICONV(1))
C     
      COMMON/SERBIDO/NX2,NX3,NX4,NX8,MX7,MX10,IGRAD,IVAI,CNXY,CNUU,
     $               XYOUT,SYOUT,ICDTR,CDTN,PX,IQNMX
C     
C********* PARAMETRI PER STAMPE
C stampa1 =1 STAMPA TEMPI E INFORMAZIONI OGNI PASSO (file stampa), =0 NON STAMPA
C stampa2 =1 STAMPA TEMPI FINALI (file stampa), = 0 NON STAMPA       
C stampa3 =1 STAMPA TEMPO OGNI PASSO (file tempo), = 0 NON STAMPA       
C      
      PARAMETER(stampa1=0,stampa2=0,stampa3=0)     
C
      CHARACTER*100 GIASEL(N005+N002)
      CHARACTER*8 NMMODU,SIGLA,SYOUT(M010),LINEA
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
      COMMON/FILE22/NOF22
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
      COMMON/METHOD/CHABS
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
!      PRINT*,'LGDYNINI: ecco NSTPLT=',NSTPLT
!      PAUSE 'premi...'
      IVAI=1
      IF(NOF22.NE.1) THEN
      CALL RECOUT(IVAI,NVPLT,IPLOT,NSTPLT,TSTEP,TFIN,IGRAD,TEMPO,
     $                  SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,CNXY,CNUU,
     $  XYOUT,SYOUT,MX10,ITITOL,KPLT,NPER,NSEL,GIASEL,NMMODU)
      ENDIF
C-stampe su terminale ...
!      CALL LEGPRI(IVAI,NSTSTP,TSTEP,TFIN,ITITOL,IGRAD,NVSTP,
!     $                  ISTMP,SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,
!     $                  CNXY,CNUU,XYOUT,SYOUT,MX10,TEMPO,KSTP)

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

      IF(NOF22.NE.1) THEN
      CALL RECOUT(IVAI,NVPLT,IPLOT,NSTPLT,TSTEP,TFIN,IGRAD,TEMPO,
     $                  SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,CNXY,CNUU,
     $  XYOUT,SYOUT,MX10,ITITOL,KPLT,NPER,NSEL,GIASEL,NMMODU)
      ENDIF
C-stampe su terminale 
!      CALL LEGPRI(IVAI,NSTSTP,TSTEP,TFIN,ITITOL,IGRAD,NVSTP,
!     $                  ISTMP,SIVAR,NX3,VARI,NX4,NEQSIS,NU,XY,UU,
!     $                  CNXY,CNUU,XYOUT,SYOUT,MX10,TEMPO,KSTP)
C
C     SELEZIONE METODO DI RISOLUZIONE
C
      REWIND(25)
 1    READ(25,'(A)') LINEA
      IF (LINEA(1:8).NE.'* METHOD'.AND.LINEA(1:5).NE.'* END') GOTO 1
      IF(LINEA(1:5).EQ.'* END') THEN
      	 PRINT *,'NEL FILE simul.dat MANCA IL CAMPO "METHOD"'
      	 CHABS='N'
      	 GOTO 20
      ENDIF

      READ(25,'(A1)') CHABS
C      WRITE(6,'(A1)') CHABS
20    IF (CHABS.EQ.'M'.OR.CHABS.EQ.'m') THEN
	  WRITE(6,*) 'LGDYNINI: *********** RISOLUZIONE CON MA28'
      ELSEIF (CHABS.EQ.'N'.OR.CHABS.EQ.'n') THEN
	  WRITE(6,*) '*********** RISOLUZIONE CON QUASI-NEWTON (MA28)' 
      ELSE
          WRITE(6,*) '******** METODO ILLEGALE: USO QUASI-NEWTON' 
          CHABS='N'
      ENDIF

      CLOSE(25)

      IF (CHABS.EQ.'N'.OR.CHABS.EQ.'n') THEN
         IQNMX=(NQSISV*2)/3  !numero massimo di passi per il metodo quasi-newton
         IF((N00Q/NQSISV).LT.IQNMX)THEN
            WRITE(6,*)'memoria insufficiente per il metodo quasi-newton'
            CALL LGABRT
         ENDIF
      ENDIF
C
C      write(6,*) 'LGDYNINI: fine ' 
      RETURN
      END
      

