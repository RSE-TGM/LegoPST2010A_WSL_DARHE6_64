/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
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
C Fortran PreCompile: main_lg3.pf
C Subsystem: 1
C Description:
C %created_by: lomgr %
C %date_created: Thu Mar 24 17:57:57 2005 %
C
C**********************************************************************
C
C Procedura contenete la variabile per identificare la versione
C
      BLOCK DATA BDD_main_lg3_pf
      CHARACTER*80 RepoID
      COMMON /CM_main_lg3_pf / RepoID
      DATA RepoID/'@(#)1,pfsrc,main_lg3.pf,2'/
      END
C**********************************************************************
C******************************************************************************
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C C
C LEGO unificato per singola / doppia precisione C
C e per diverse piattaforme operative C
C C
C Attivata versione singola precisione per sistema operativo Unix C
C C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C***********************************************************************
       PROGRAM LG3
C
C PROGRAMMA DI ACQUISIZIONE DATI GEOMETRICI E FISICI
C E CALCOLO DEL REGIME STAZIONARIO INIZIALE
C
C***********************************************************************
C
C______ FILES DI LAVORO DI LG3
C
      CHARACTER*32 F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR,N04DAT
C
      COMMON/LG3FLS/F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR,N04DAT
      COMMON/LGTV01/LGTEMPO,ILEGO,ICOUNT,ICOUNTMX
      COMMON/LGTV02/LGMODULO,LGBLOCCO
C
C Permette la visualizzazione di molti errori sulle tavole
C perche' la prima fase e' quella di lettura parametri
C
      ILEGO=1
      ICOUNTMX=1000
      CALL LG3FIL
C
C APERTURA FILE TAVOLE VAPORE
C
      CALL INITSM
C Inizio parte modificata da Furlani
      OPEN(UNIT=3,FILE=F03DAT,STATUS='OLD',FORM='UNFORMATTED')
      OPEN(UNIT=14,FILE=F14DAT,STATUS='OLD',FORM='FORMATTED')
      OPEN(UNIT=4,FILE=F04DAT,STATUS='UNKNOWN',FORM='UNFORMATTED')
      OPEN(UNIT=44,FILE=N04DAT,STATUS='UNKNOWN',FORM='FORMATTED')
C OPEN(UNIT=24,FILE=F24DAT,STATUS='UNKNOWN')
      IER=0
C
C_________ LETTURA DEI DATI TOPOLOGIGICI,GEOMETRICI E FISICI DEL MODELLO
C
      CALL LEGO3(IER)
      IF (IER.EQ.1) CALL LGABRT
C
C_________ CALCOLO DEL REGIME STAZIONARIO
C
      CALL LEGO34
C
      CALL LGSTOP
      STOP
      END
C
C
C
      BLOCK DATA MA2801
      LOGICAL ABORT1,ABORT2,ABORT3
      COMMON /MA30E/ LP,ABORT1,ABORT2,ABORT3
      COMMON /MA30G/ EPS,RMIN
      DATA EPS/1.0E-4/
      DATA LP/6/
      DATA ABORT1/.FALSE./,ABORT2/.FALSE./,ABORT3/.FALSE./
      END
C
C
C
      BLOCK DATA MA2802
      COMMON/MC19B /LP,IFAIL
      DATA LP/6/
      END
C
C
C
      BLOCK DATA MA2803
      LOGICAL LBLOCK,GROW,ABORT1,ABORT2
      COMMON /MA28E/ LP,MP,LBLOCK,GROW
      COMMON /MA28F/ EPS,RMIN,RESID,IRNCP,ICNCP,MINIRN,MINICN,
     $ IRANK,ABORT1,ABORT2
      DATA EPS/1.0E-4/
      DATA LP/6/,MP/6/
      DATA LBLOCK/.TRUE./,GROW/.TRUE./
      DATA ABORT1/.FALSE./,ABORT2/.FALSE./
      END
C
C
C
      BLOCK DATA MA2804
      LOGICAL ABORT
      COMMON /MC23B/ LP,NUMNZ,NUM,LARGE,ABORT
      DATA LP/6/,ABORT/.FALSE./
      END
C
