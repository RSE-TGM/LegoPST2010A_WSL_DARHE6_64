CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC
C                                                                      C
C           LEGO unificato per singola / doppia precisione             C
C                 e per diverse piattaforme operative                  C
C                                                                      C
C   Attivata versione singola precisione per sistema operativo VMS     C
C                                                                      C
CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC

      SUBROUTINE JACTO(IRJ,ICJ,NZTER,NEQSIS,NNOTO,IA)
      DIMENSION IRJ(*),ICJ(*),IA(*)
C
C     CONTROLLO SE CI SONO RIGHE O COLONNE NULLE
C
      DO I=1,NEQSIS
      IA(I)=0
      ENDDO
      DO I=1,NZTER
      IA(IRJ(I))=1
      ENDDO
      DO I=1,NEQSIS
      IF(IA(I).EQ.0)WRITE(6,1000)I
      ENDDO
      
      DO I=1,NNOTO
      IA(I)=0
      ENDDO
      DO I=1,NZTER
      IA(ICJ(I))=1
      ENDDO
      DO I=1,NNOTO
      IF(IA(I).EQ.0)WRITE(6,1001)I
      ENDDO
      
      RETURN
 1000 FORMAT(///10X,'****LA RIGA DELLO JACOBIANO***',I4,
     &'  NON HA TERMINI')
 1001 FORMAT(///10X,'****LA COLONNA DELLO JACOBIANO***',I4,
     &'  NON HA TERMINI')
      END
