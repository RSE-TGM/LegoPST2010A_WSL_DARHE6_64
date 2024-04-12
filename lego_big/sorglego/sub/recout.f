C*********************************************************************
C       Fortran Source:             recout.f
C       Subsystem:              1
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Tue Aug 21 10:29:44 2001 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_recout_f
      CHARACTER*80  RepoID
      COMMON /CM_recout_f / RepoID
      DATA RepoID/'@(#)1,fsrc,recout.f,2'/
      END
C**********************************************************************
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
      DIMENSION IPLOT(*),XY(*),UU(*),CNXY(*),
     $          CNUU(*),XYOUT(*),ITITOL(*)
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
      RETURN
    5 IER=0
      CALL FILPOS(22,TREST,NN,IER)
      IF (IER.NE.0) CALL LGABRT
      RETURN
C
  100 CALL PASSOT(NSTPLT,TSTEP,TEMPO,IGRAD,KOUT)
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
C
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
