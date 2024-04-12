C*********************************************************************
C       Fortran Source:             calcola.f
C       Subsystem:              1
C       Description:
C       %created_by:    famgr %
C       %date_created:  Tue Apr 30 10:06:20 1996 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_calcola_f
      CHARACTER*80  RepoID
      COMMON /CM_calcola_f / RepoID
      DATA RepoID/'@(#)1,fsrc,calcola.f,3'/
      END

C
C*************
C   Calcoli relativi alle tavole del vapore
C*************
C
C       ILEGO = INDICATORE DEL PROGRAMMA CHIAMANTE LE TAVOLE
C             =1 LEGO E` IL PROGRAMMA CHIAMANTE
C             =0 NON E` IL LEGO IL PROGRAMMA CHIAMANTE
C
C       ICOUNTMX = CONTATORE STABILITO DAL PROGRAMMA CHIAMANTE LE TAVOLE
C                  SUPERATO IL QUALE VIENE DECRETATO LO STOP .
C
	subroutine CALCOLA(NUM_FUNZ, ARG1, ARG2, ARG3, IOUT, 
     &	RISULTATO, RISULTATO2)
        REAL*4 ARG1, ARG2, ARG3, RISULTATO, RISULTATO2
C
C     common per diagnostica calcoli sulle tavole
C
      COMMON/LGTV01/LGTEMPO,ILEGO,ICOUNT,ICOUNTMX
      COMMON/LGTV02/LGMODULO,LGBLOCCO
      CHARACTER*8 LGMODULO,LGBLOCCO
      REAL LGTEMPO
C
	DATA IPRI/1/
        WRITE(*,*)NUM_FUNZ, ARG1, ARG2, ARG3, ID
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
	GO TO (1,2,3,4,5,6,7,8,9,10,11,12,13,14) NUM_FUNZ

C-------------Calcolo temperatura
1	continue
	P=ARG1
	S=ARG2
	P=P*1.E5
	S=S*1.E3
	T=TEV(P,S,ID)
	T=T-273.15
	RISULTATO=T
	GOTO100
C----
2	continue
	P=ARG1
	H=ARG2
	P=P*1.E5
	H=H*1.E3
	S1=SHEV(P,H,ID)
	T=TEV(P,S1,ID)
	T=T-273.15
	RISULTATO=T
	GOTO100
C----
3	continue
	P=ARG1
	P=P*1.E5
	CALL SATUR(P,7,T,PIPPO,ID)
	T=T-273.15
	RISULTATO=T
	GOTO100
C-------------Calcolo entropia
4	continue
	P=ARG1
	H=ARG2
	P=P*1.E5
	H=H*1.E3
	S=SHEV(P,H,ID)
	S=S*1.E-3
	RISULTATO=S
	GOTO100
C----
5	continue
	P=ARG1
	T=ARG2
	Y=ARG3
	P=P*1.E5
	T=T+273.15
	S=STEV(P,T,Y,ID)
	S=S*1.E-3
	RISULTATO= S
	GOTO100
C------------Calcolo entalpia
6	continue
	P=ARG1
	S=ARG2
	P=P*1.E5
	S=S*1.E3
	H=HEV(P,S,ID)
	H=H*1.E-3
	RISULTATO= H
	GOTO100
C----
7	continue
	P=ARG1
	T=ARG2
	Y=ARG3
	P=P*1.E5
	T=T+273.15
	S=STEV(P,T,Y,ID)
	H=HEV(P,S,ID)
	H=H*1.E-3
	RISULTATO=H
	GOTO100
C-----------Densita`
8	continue
	P=ARG1
	H=ARG2
	P=P*1.E5
	H=H*1.E3
	S=SHEV(P,H,ID)
	RO=ROEV(P,S,ID)
	RISULTATO=RO
	GOTO100
C-----
9	continue
	P=ARG1
	T=ARG2
	Y=ARG3
	P=P*1.E5
	T=T+273.15
	S=STEV(P,T,Y,ID)
	RO=ROEV(P,S,ID)
	RISULTATO=RO
	GOTO100
C----------Calcolo calore specifico
10	continue
	P=ARG1
	T=ARG2
	Y=ARG3
	P=P*1.E5
	T=T+273.15
	S=STEV(P,T,Y,ID)
	data YC/.57/
	CP=CPEV(P,S,Y,YC,ID)
	RISULTATO=CP
	GOTO100
C--------Calcolo entalpia acqua e del vapore saturo
11	continue
	P=ARG1
	P=P*1.E5
	CALL SATUR(P,2,HWAT,HVAP,ID)
	HWAT=HWAT*1.E-3
	HVAP=HVAP*1.E-3
	RISULTATO=HWAT
	RISULTATO2=HVAP
	GOTO100
C--------Calcolo entropia acqua e del vapore saturo
12	continue
	P=ARG1
	P=P*1.E5
	CALL SATUR(P,1,SWAT,SVAP,ID)
	SWAT=SWAT*1.E-3
	SVAP=SVAP*1.E-3
	RISULTATO=SWAT
	RISULTATO2=SVAP
	GOTO100
C--------Calcolo densita` acqua e del vapore saturo
13	continue
	P=ARG1
	P=P*1.E5
	CALL SATUR(P,3,ROWAT,ROVAP,ID)
	RISULTATO=ROWAT
	RISULTATO2=ROVAP
	GOTO100
C--------Calcolo titolo in vapore
14	continue
	P=ARG1
	H=ARG2
	P=P*1.E5
	H=H*1.E3
	S1=SHEV(P,H,ID)
	Y=YEV(P,S1,ID)
	RISULTATO=Y
	GOTO 100
C----------------------------------------------------------
100	WRITE(*,*)'RISULTATI:'
        WRITE(*,*) RISULTATO, RISULTATO2
	IF(ICOUNT.GT.0) THEN
        IOUT=1
	ICOUNT=0
	ELSE
	IOUT=0
	ENDIF
        CONTINUE

	return 
	end
C
C
C Procedura contenete la variabile per l'identificazione della versione
C        
      SUBROUTINE SCCS_calcola
      CHARACTER*80 SccsID
      DATA SccsId/'@(#)calcola.f	1.4\t3/29/95'/
      END
