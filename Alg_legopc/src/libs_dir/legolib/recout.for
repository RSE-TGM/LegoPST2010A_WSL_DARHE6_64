C******************************************************************************
C modulo recout.f
C tipo 
C release 2.1
C data 7/10/95
C reserver @(#)recout.f	2.1
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo Unix    C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE RECOUT(IVAI,NVPLT,IPLOT,NSTPLT,TSTEP,TFIN,IGRAD,TEMPO,
     $                  SIVAR,MX1,VARI,MX3,NEQSIS,NU,XY,UU,CNXY,CNUU,
     $  XYOUT,SYOUT,MX2,ITITOL,KPLT,NPER,NSEL,GIASEL,NMMODU)
C
C--GUAG lug2002 
      PARAMETER (N000=160, N001=N000*10, N002=N000*25, N003=N000*50,
     $           N004=N000*25, N005=N000*100, N006=100,
     $           N007=N000*500, N008=40, NR00=12, NR01=70, NR02=50,
cc     $           N007=N000*500, N008=40, NR00=12, NR01=70, NR02=18,
     $           NP00=10)
C
      PARAMETER (M003 = N002+1, M004 = N003+1, M005 = N004+1,
     $           M001 = N005-N003, M002 = M001-N004)


      DIMENSION IPLOT(*),XY(*),UU(*),CNXY(*),
     $          CNUU(*),XYOUT(*),ITITOL(*)
C--     
      CHARACTER*8 SIVAR(MX1),VARI(MX3),SYOUT(MX2)
      COMMON/RSTRT1/TREST,IREGIM

             
      CHARACTER*(*) GIASEL(*),NMMODU
      CHARACTER*30 FILE11
      REAL TEMP
      
      DATA IVOLT/1/
C
      MMX1=MX1
      MMX3=MX3
      MMX2=MX2
      GO TO (1,100),IVAI
C
C     APERTURA FILE 22
C
    1 CALL PLPROT(NVPLT,IPLOT,SIVAR,MMX1,VARI,MMX3,NEQSIS,NU,
     $           XY,UU,CNXY,CNUU,NN,XYOUT,SYOUT,MMX2)
C
      IF(NVPLT.EQ.0)RETURN
      NPUNTI=TFIN/(NSTPLT*TSTEP)+100
      CALL PREPO(NPUNTI,NN)
C
      K=20
      IF(IREGIM.EQ.2)GO TO 5
      TREST=0.
      REWIND 22
C
      WRITE(22)(ITITOL(I),I=1,K)
      WRITE(22)NN,(SYOUT(I),I=1,NN),
     $         NMMODU,NSEL,(GIASEL(I)(1:80),I=1,NSEL)
      NREC=4
C--GUAG lug2002
      	IVAI2=1
	CALL PREP_F22(IVAI2,NN,NSEL,TEMPO,LOC(XYOUT),SYOUT,GIASEL)      
      PRINT*,'----NN=',NN,' NSEL=',NSEL,' NSTPLT=',NSTPLT
C--
        
      
      RETURN
    5 IER=0
      CALL FILPOS(22,TREST,NN,IER)
      IF (IER.NE.0) CALL LGABRT
      RETURN
C
  100  CONTINUE
C        PAUSE 'recout:  premi..'
  	CALL PASSOT(NSTPLT,TSTEP,TEMPO,IGRAD,KOUT)
C

      KPLT=KOUT
      IF(KOUT.EQ.0)RETURN
C
      IF(NVPLT.EQ.0)RETURN
      NREC=NREC+1
C
      CALL PLPROT(NVPLT,IPLOT,SIVAR,MMX1,VARI,MMX3,NEQSIS,NU,
     $            XY,UU,CNXY,CNUU,NN,XYOUT,SYOUT,MMX2)
C
      TEMP=TEMPO+TREST
      WRITE(22)TEMP,(XYOUT(I),I=1,NN)
C--GUAG lug2002
      	IVAI2=2
	CALL PREP_F22(IVAI2,NN,NSEL,TEMP,LOC(XYOUT),SYOUT,GIASEL)       
C     	PRINT*,'----scritto al tempo=',TEMP
C--
C       SCRITTURA DI UN FILE_MESSAGGIO PER LEGOCAD
C       CHE LO AVVERTE DELL'AVVENUTA REGISTRAZIONE
C       DEL PRIMO PUNTO DEL TRANSITORIO
C
        IF (IVOLT.NE.1) RETURN
        FILE11 = 'proc/via_graf.dat'
        OPEN(UNIT=11,FILE=FILE11,STATUS='UNKNOWN',FORM='FORMATTED')
        WRITE(11,*)'VIA_GRAF'
        IVOLT=0
        CLOSE (UNIT=11)
C
      RETURN
      END
C            
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_recout
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)recout.f	2.1\t7/10/95'/
      END
