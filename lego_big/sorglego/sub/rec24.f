C*********************************************************************
C       Fortran Source:             rec24.f
C       Subsystem:              1
C       Description:
C       %created_by:    lopez %
C       %date_created:  Mon Oct 28 10:56:57 2002 %
C
C**********************************************************************


C
C Procedura contenete la variabile per l'identificazione della versione
C
      BLOCK DATA BDD_rec24_f
      CHARACTER*80  RepoID
      COMMON /CM_rec24_f / RepoID
      DATA RepoID/'@(#)1,fsrc,rec24.f,2'/
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

      SUBROUTINE REC24(NEQSIS,XY,NU,UU)
      DIMENSION A(20),XY(*),UU(*)
C$$$      DATA EOF/'EOF'/,XLG/'*LG*'/,ISSO/'SI'/
C
C
C_________ SALVATAGGIO DEI RISULTATI SU FILE 24.
C

C GUAG 0/09/2007 Modificata per ovviare ad un baco del compilatore linux g77 del 
C descriyyore G10.5 che causa un errore sulla stmap del f24 per numeri come 0.999999
C oppur -0.99  che vengono stampati  ******. Per ovirae nel caso di errore si utilizza
C il decrittore del format F10.5. A tale scopo è stata creata la subroutine REC24_STAM
C
C GUAG 6/10/2010 Altra modifica per ovviare ad analogo problema sui numeri grandi
C 

      REWIND 14
      REWIND 24
 1000 FORMAT(20A4)
      DO 1 I=1,4
      READ(14,1000)A
      WRITE(24,1000)A
    1 CONTINUE
      
      DO 10 I=1,NEQSIS
      READ(14,1000)(A(J),J=1,20)
      CALL REC24_STAM(A,XY(I))      
   10 CONTINUE
      
      READ(14,1000)A
      WRITE(24,1000)A      
      
      DO 20 I=1,NU
      READ(14,1000)(A(J),J=1,20)
      CALL REC24_STAM(A,UU(I))            
   20 CONTINUE
   
   
   30 READ(14,1000,END=100)(A(I),I=1,20)
      WRITE(24,1000)(A(I),I=1,20)
      GO TO 30  
  100 RETURN
             
      END
C            
      SUBROUTINE REC24_STAM(A,XU)

      DIMENSION A(*)
      CHARACTER*10 SSTRIN
        
      WRITE(SSTRIN,3001) XU
      IF(SSTRIN(1:2).EQ.'**') THEN
        WRITE(SSTRIN,3002) XU
	IF(SSTRIN(1:2).EQ.'**') THEN
C          PRINT*,'ERRORE. provo G10.3'	  
C	   WRITE(6,1003)(A(J),J=1,4),XU,(A(J),J=7,20)
	     WRITE(24,1003)(A(J),J=1,4),XU,(A(J),J=7,20)
	ELSE
C          PRINT*,'FORMAT G10.4'
C	   WRITE(6,1002)(A(J),J=1,4),XU,(A(J),J=7,20)
	     WRITE(24,1002)(A(J),J=1,4),XU,(A(J),J=7,20)
        ENDIF
      ELSE
C        PRINT*,'FORMAT G10.5'
C        WRITE(6,1001)(A(J),J=1,4),XU,(A(J),J=7,20)
        WRITE(24,1001)(A(J),J=1,4),XU,(A(J),J=7,20)
      ENDIF	     

 
 1001 FORMAT(3A4,A2,G10.5,14A4)
 1002 FORMAT(3A4,A2,G10.4,14A4)
 1003 FORMAT(3A4,A2,G10.3,14A4)
 
C 1013 FORMAT(3A4,A2,F10.5,14A4)
C 1014 FORMAT(3A4,A2,F10.4,14A4)

 3001 FORMAT(G10.5) 
 3002 FORMAT(G10.4) 
             
      RETURN
      END	
