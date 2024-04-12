
      SUBROUTINE GSA(M,N,A,IND,IPN,IPNA,Z,EPS,P,INDP,IPNP,NZPMX,G,
     *               INDG,IPNG,IPNR,NZGMX,F,S,Q,IRK,IEQ,IWR,IER)
      
* FATTORIZZAZIONE DELLA MATRICE SPARSA A (A=G*P) CON IL METODO DI      
* GRAM-SCHMIDT
      
      REAL*8 A(*),P(*),G(*),F(*),S(*),Q(*)
      REAL*8 EPS,DD,Z,ZZ
      INTEGER IND(*),IPN(*),IPNA(*),INDP(*),IPNP(*),INDG(*),IPNG(*)
      INTEGER IPNR(*),IEQ(*),DESCRA(9)
      DATA ZZ/0.D+0/
      DATA DESCRA/0,0,0,1,1,0,0,0,0/      
      IER=0
      IF(M.LE.0)THEN
        IER=1
      ELSEIF(N.LT.M)THEN
        IER=2
      ELSEIF(EPS.LT.ZZ)THEN
        EPS=ZZ
      ELSEIF(Z.LT.ZZ)THEN
        Z=ZZ
      ENDIF
      IF(IER.NE.0)RETURN
      IRK=0
      NZP=0
      NZG=0
      IPNP1=1
      IPNP(1)=1
      IPNG(1)=1
      DO 10 K=1,M
      CALL DCOPY(N,ZZ,0,S,1)
      DO I=1,IRK
        J=IPNR(I)
        IF(INDG(J).EQ.K)THEN
          DD=-G(J)
          IPNR(I)=J+1
          II=IPNP(I)
          IPNP2=IPNP(I+1)-IPNP(I)+1
          CALL DCSCMM(0,N,1,1,1.D+00,DESCRA,P(II),INDP(II),IPNP1,
     *                IPNP2,DD,1,1.D+00,S,N,Q,N)
        ENDIF
      ENDDO
      DO J=IPN(K),IPN(K+1)-1
        I=IND(J)
        S(I)=S(I)+A(J)
      ENDDO
      DD=ZZ
      DO J=IPN(K),IPN(K+1)-1
        I=IND(J)
        DD=DD+A(J)*S(I)
      ENDDO
      DD=DSQRT(DABS(DD))
      IF(DD.GT.EPS) THEN
        IRK=IRK+1      
        NZG=NZG+1
        IF(NZG.GT.NZGMX)THEN
          IER=17
          RETURN
        ENDIF
        G(NZG)=DD
        INDG(NZG)=IRK
        IPNR(IRK)=NZG+1
        DO I=1,N
          IF(DABS(S(I)).GT.Z)THEN
            NZP=NZP+1
            IF(NZP.GE.NZPMX)THEN
              IER=12
              RETURN
            ENDIF
            S(I)=S(I)/DD
            P(NZP)=S(I)
            INDP(NZP)=I
          ENDIF
        ENDDO
        IPNP(IRK+1)=NZP+1
        IF(K.LT.M)THEN
          IA=IPN(K+1)
          LIPN=IPN(K+1)-IPN(1)
          DO I=1,M-K+1
            IPNA(I)=IPN(K+I)-LIPN
          ENDDO      
          CALL DCSRMM(0,M-K,1,N,1.D+00,DESCRA,A(IA),IND(IA),IPNA,
     *                IPNA(2),S,N,ZZ,F(K+1),M-K,Q,N)
          DO I=K+1,M
            IF(DABS(F(I)).GT.Z)THEN
              NZG=NZG+1
              IF(NZG.GE.NZGMX)THEN
                IER=17
                RETURN
              ENDIF
              G(NZG)=F(I)
              INDG(NZG)=I
            ENDIF
          ENDDO
          INDG(NZG+1)=0
        ENDIF
        IPNG(IRK+1)=NZG+1
      ELSE
        IEQ(K-IRK)=K
        IF(IWR.GT.0) WRITE(IWR,22) K,DABS(DD),EPS
        WRITE(55,22) K,DABS(DD),EPS
   22   FORMAT(1X,'RIGA',I5,2X,' NORMA',D13.6,'  TOLLERANZA',D8.1)
      ENDIF
   10 CONTINUE
      IEQ(M-IRK+1)=M+1
      IF(IRK.LT.M)THEN
        L=0
        DO K=1,IRK
          II=1
          L=L+1
          L0=L
          J=IPNG(K)
          G(L)=G(J)
          INDG(L)=INDG(J)
          DO I=IPNG(K)+1,IPNG(K+1)-1
            J=INDG(I)
            DO WHILE(J.GT.IEQ(II))
              II=II+1
            ENDDO
            IF(J.EQ.IEQ(II))THEN
              II=II+1
            ELSE
              L=L+1
              G(L)=G(I)
              INDG(L)=INDG(I)-II+1
            ENDIF
          ENDDO
          IPNG(K)=L0
        ENDDO
        IPNG(IRK+1)=L+1
      ENDIF
      RETURN
      END



      SUBROUTINE GSB(M,N,A,IND,IPN,B,P,INDP,IPNP,G,INDG,IPNG,Y,
     *               Q,IRK,IEQ,IWR)

* SOLUZIONE DEL SISTEMA Ax=b PER SOSTITUZIONE Gy=b, x=Py

      REAL*8 A(*),B(*),P(*),G(*),Y(*),Q(*),R
      INTEGER IND(*),IPN(*),INDP(*),IPNP(*),INDG(*),IPNG(*),IEQ(*)
      INTEGER DESCRA(9),DESCRA1(9)
      DATA  DESCRA/0,0,0,1,1,0,0,0,0/
      DATA DESCRA1/3,1,0,1,1,0,0,0,0/
      DO I=1,M-IRK
        Y(M-I+1)=B(IEQ(I))
        DO J=IEQ(I)+1,IEQ(I+1)-1
          B(J-I)=B(J)
        ENDDO
      ENDDO      
      CALL DCSCSM(0,IRK,1,1,1.D+00,1.D+00,DESCRA1,G,INDG,IPNG,IPNG(2),
     *            B,IRK,0.D+00,Y,IRK,Q,IRK) 
      CALL DCSCMM(0,N,1,IRK,1.D+00,DESCRA,P,INDP,IPNP,IPNP(2),
     *            Y,IRK,0.D+00,B,N,Q,N) 
      IF(IWR.GT.0)THEN
        DO KK=1,M-IRK
          K=IEQ(KK)
          R=-Y(M-KK+1)
          DO J=IPN(K),IPN(K+1)-1
            I=IND(J)
            R=R+A(J)*B(I)
          ENDDO
        WRITE(IWR,33)K,DABS(R)
        ENDDO
      ENDIF
      RETURN      
   33 FORMAT(1X,'EQUAZIONE',I5,2X,' ERRORE RESIDUO ',D13.6)
      END



      SUBROUTINE GSAERR(IER)
      IF(IER.EQ.1)THEN
      WRITE(6,1)
      ELSEIF(IER.EQ.2)THEN
      WRITE(6,2)
      ELSEIF(IER.EQ.12)THEN
      WRITE(6,12)
      ELSEIF(IER.EQ.17)THEN
      WRITE(6,17)
      ENDIF
      RETURN
    1 FORMAT(/' NUMERO DI EQUAZIONI MINORE O UGUALE A ZERO')
    2 FORMAT(/' NUMERO DI COLONNE MINORE DEL NUMERO DI RIGHE')
   12 FORMAT(/' SUPERATO DIMENSIONAMENTO MATRICE P')
   17 FORMAT(/' SUPERATO DIMENSIONAMENTO MATRICE G')
      END

