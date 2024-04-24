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
C Fortran PreCompile: main_cf04.pf
C Subsystem: 1
C Description:
C %created_by: lomgr %
C %date_created: Thu Mar 24 18:20:18 2005 %
C
C**********************************************************************
C
C Procedura contenente la variabile per identificare la versione
C
      BLOCK DATA BDD_main_cf04_pf
      CHARACTER*80 RepoID
      COMMON /CM_main_cf04_pf / RepoID
      DATA RepoID/'@(#)1,pfsrc,main_cf04.pf,2'/
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
       PROGRAM CF04
C
C PROGRAMMA DI ACQUISIZIONE DATI GEOMETRICI E FISICI
C E SCRITTURA CORRISPONDENTE FILE F04
C
C***********************************************************************
C
C______ FILES DI LAVORO DI LG3
C
      CHARACTER*32 F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR,N04DAT
C
      COMMON/LG3FLS/F14DAT,F03DAT,F04DAT,F24DAT,LG3ERR,N04DAT
C
      F14DAT = 'f14.s'
      F03DAT = 'proc/f03.dat'
      F04DAT = 'proc/f04.dat'
      F24DAT = 'proc/f24.dat'
      LG3ERR = 'proc/lg3.err'
C
      OPEN(UNIT=3,FILE=F03DAT,STATUS='OLD',FORM='UNFORMATTED')
      OPEN(UNIT=14,FILE=F14DAT,STATUS='OLD',FORM='FORMATTED')
      OPEN(UNIT=4,FILE=F04DAT,STATUS='UNKNOWN',FORM='UNFORMATTED')
      IER=0
C
C_________ LETTURA DEI DATI TOPOLOGIGICI,GEOMETRICI E FISICI DEL MODELLO
C
      WRITE(*,*)'prima di lego3'
      CALL LEGO3(IER)
      WRITE(*,*)'dopo lego3'
      IF (IER.EQ.1) CALL LGABRT
C
      CLOSE(UNIT=3)
      CLOSE(UNIT=14)
      CLOSE(UNIT=4)
C
      WRITE(*,*)'finita la scrittura'
      CALL LGSTOP
      STOP
      END
C
