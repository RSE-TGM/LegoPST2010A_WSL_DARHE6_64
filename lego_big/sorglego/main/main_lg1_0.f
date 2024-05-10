/* Copyright (C) 1991-2022 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */


/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */

/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */



/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */

C*********************************************************************
C       Fortran PreCompile:             main_lg1.pf
C       Subsystem:              2
C       Description:
C       %created_by:    lomgr %
C       %date_created:  Mon Oct 27 15:03:33 2003 %
C
C**********************************************************************


C
C     Procedura contenente la variabile per identificare 
C     la versione
C
      BLOCK DATA BDD_main_lg1_pf
      CHARACTER*80  RepoID
      COMMON /CM_main_lg1_pf / RepoID
      DATA RepoID/'@(#)2,pfsrc,main_lg1.pf,2'/
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

      PROGRAM LG1
C
C               PROGRAMMA   L G 1
C
      INCLUDE 'lg_parameter.fh'
C
C
      PARAMETER (MAXCAR=80)
      DIMENSION NOSL(N001)
      DIMENSION NOSCHE(N001)
      DIMENSION NASL(N002),ISL(N002)
      CHARACTER*(MAXCAR) LIMODU(N001)
      CHARACTER*(MAXCAR) LISCHE(N001)
      INTEGER      IPUNB(N002)
      CHARACTER*80 FIL01(MN005)
      CHARACTER*200 MMI_LISTA_SCHEMI
C
C______ FILES DI LAVORO DI LG1
C
      CHARACTER*32 LMODUL,F01DAT,F02DAT,LTMFOR,CLTMDA,LG1ERR,LSCHEM
C
      COMMON/LG1FLS/LMODUL,F01DAT,F02DAT,LTMFOR,CLTMDA,LG1ERR,LSCHEM
C
      CHARACTER*8 MODEL
      CHARACTER FLAG_MMI
C
      DATA IFO/7/
      DATA IF01/1/
C

      MAXMOD=N001
      MAXBLO=N002
C
C______ DEFINIZIONE DEI FILES DI LAVORO DI LG1
C
C______ ARGOMENTO PER CHIAMATA DA PARTE DI L(R)EGOMMI : "L"
        CALL GETARG(1,FLAG_MMI)
        CALL GETARG(2,MMI_LISTA_SCHEMI)
C
      CALL LG1FIL
C
C     APERTURA DEI FILES DI LAVORO
      OPEN(UNIT=04,FILE=LMODUL,STATUS='OLD')
      IF ( FLAG_MMI.EQ.'L' ) THEN
         OPEN(UNIT=8,FILE=MMI_LISTA_SCHEMI,STATUS='OLD')
      ELSE
         OPEN(UNIT=8,FILE=LSCHEM,STATUS='OLD')
      ENDIF
      OPEN(UNIT=IF01,FILE=F01DAT,STATUS='OLD')
      OPEN(UNIT=2,FILE=F02DAT,STATUS='UNKNOWN',FORM='UNFORMATTED')
      OPEN(UNIT=35,FILE=LTMFOR,STATUS='UNKNOWN')
      OPEN(UNIT=34,FILE=CLTMDA,STATUS='UNKNOWN')
C
C  LETTURA ELENCO DEI MODULI DA FILE LMODUL.DAT
C  LETTURA ELENCO DEGLI SCHEMI DI REGOLAZIONE DA FILE LSCHEM.DAT
C
      CALL LISMOD(LIMODU,NOSL,NST,LISCHE,NOSCHE,NSCHE,
     $            MAXMOD,LG1ERR,FIL01,IER)
      IF (IER.EQ.1) THEN
        WRITE (6,*) 'SI VOGLIONO USARE PIU` DI 300 MODULI'
        CALL LGABRT
      ENDIF
C
      ICON=0
C
C     LETTURA DEI NOMI DEI BLOCCHI DA FILE F01DAT
C
      CALL LETF01(IF01,ICON,ISL,NASL,NST,NOSL,MAXBLO,
     $            IPUNB,FIL01,IER,LG1ERR,MODEL,IPUNIN,
     $            NLF01,NSCHE,NOSCHE,LISCHE)
C
      CLOSE (01)
      CLOSE (04)
      CLOSE (08)
C
      IF (IER.NE.0) THEN
        WRITE (6,*) 'ESECUZIONE INTERROTTA PER ERRORI'
        CALL LGABRT
      ENDIF
      IF (ICON.LE.0) THEN
        WRITE (6,*)
     $     'ESECUZIONE INTERROTTA - FILE TOPOLOGICO SENZA BLOCCHI'
        CALL LGABRT
      ENDIF
C
      ITIMOD=1
C
C____ SE 1 ,VERIFICA SE IL MODELLO E` DI PROCESSO O DI REGOLAZIONE
C
      IF(ISL(1).LT.0) THEN
C_____MODELLO DI REGOLAZIONE
         KK=1
      ELSE
C_____MODELLO DI PROCESSO
         KK=0
      ENDIF
      DO 600 I=1,ICON
       WRITE (6,*) 'valore isl =',ISL(I)
       IF(ISL(I).LT.0.AND.KK.EQ.0)GO TO 650
       IF(ISL(I).GT.0.AND.KK.EQ.1)GO TO 650
 600  CONTINUE
      ITIMOD=KK
      GO TO 670
C
C_____ERRORE :CASO IN CUI UN MODELLO TRATTA SIA MODULI DI PROCESSO CHE
C     DI REGOLAZIONE
C
 650  WRITE(6,7682)
 7682 FORMAT(///10X,'**** ERRORE : IL MODELLO NON PUO` CONTENERE ',
     $'CONTEMPORANEAMENTE '/25X,'MODULI DI PROCESSO E MODULI DI ',
     $'REGOLAZIONE'//)
      CALL LGABRT
C
 670  CONTINUE
C
C_________ SI COSTRUISCE UNA LISTA UNICA DI MODULI
C          AGGIUNGENDO ALLA LISTA DEI MODULI DI PROCESSO
C          LA LISTA DEGLI SCHEMI DI REGOLAZIONE
C          (TUTTI GLI ISL(I)<0 DEVONO ESSERE CAMBIATI
C
      DO 700 I=1,NSCHE
      LIMODU(I+NST)=LISCHE(I)
      NOSL(I+NST)=NOSCHE(I)
  700 CONTINUE
      DO 701 I=1,ICON
      IF(ISL(I).LT.0)ISL(I)=-(ISL(I)-NST)
  701 CONTINUE
C
      NST=NST+NSCHE
C
C___________ CONTROLLI SUI DATI TOPOLOGICI
C
      CALL LEGO1(MODEL,FIL01,ISL,IPUNB,NOSL,LIMODU,
     $           ICON,IPUNIN,NLF01,ITIMOD,IERTOP)
C
      CLOSE (02)
      CLOSE (34)
      CLOSE (35)
C
      IF(IERTOP.NE.0) CALL LGABRT
      CALL LGSTOP
      STOP
      END
C            
C            
