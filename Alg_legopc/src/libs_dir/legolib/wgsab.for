      SUBROUTINE WGSA(M,N,A,IND,IPN,IPNA,IPNB,W,Z,EPS,P,INDP,IPNP,
     *                NZPMX,G,INDG,IPNG,IPNR,NZGMX,F,S,Q,IRK,IEQ,
     *                IWR,IER)
      
* WGSA decomposes a sparse mxn (m<=n) matrix A with associated weights
* into the factors P (rectangular) and G (lower triangular) using 
* the weighted Gram Schmidt method.
* M    integer, number of rows of A, unchanged on exit.
* N    integer, number of columns of A, unchanged on exit.
* A    real*8 array of lenght nz (nz is the number of nonzeros in A), 
*      the nonzero entries of A, stored by rows, unchanged on exit.
* IND  integer array of lenght nz, column indices of the entries of A, 
*      unchanged on exit. 
* IPN  integer array dimension M+1, pointers to the locations in A, 
*      IPN(i), for i=1 to M, points to the first element of the row i, 
*      IPN(M+1)=nz+1, if row i is empty IPN(i)=IPN(i+1),  
*      unchanged on exit.
* IPNA integer array dimension M, workspace. 
* IPNB integer array dimension dim(IPNA)-1, workspace.
* W    real*8 array dimension N, inverse weights, unchanged on exit.  
* Z    real*8, tolerance to regard elements of P and G as zero, 
*      unchanged on exit.  
* EPS  real*8, tolerance to test linearly dependence, unchanged on exit.
* P    real*8 array dimension NZPMX, on exit P holds the nonzero  
*      elements of the rectangular factor of A stored by columns.
* INDP integer array dimension NZPMX, on exit the row indices of the 
*      elements in P. 
* IPNP integer array dimension M+1, on exit the pointers to the 
*      locations in P.
* NZPMX integer, on entry the dimension of P and INDP, unchanged on exit. 
* G    real*8 array of dimension NZGMX, on exit G holds the nonzero 
*      elements of the lower triangular factor stored by columns.
* INDG integer array dimension NZGMX, on exit the row indices of the 
*      elements in G. 
* IPNG integer array dimension M+1, on exit the pointers to the 
*      locations in G.
* IPNR integer array dimension M+1, workspace.
* NZGMX integer, on entry the dimension of G and INDG, unchanged on exit. 
* F    real*8 array dimension M, workspace.  
* S    real*8 array dimension N, workspace.  
* Q    real*8 array dimension N, workspace.  
* IRK  integer, on exit the rank of A determined by the tolerance EPS.
* IEQ  integer array dimension M+1, on exit the first M-IRK elements 
*      contain the indices of linearly dependent rows of A.
* IWR  integer, on entry the unit number for diagnostic messages, 
*      IWR<=0 suppresses the output, unchanged on exit. 
* IER  integer, on exit, ier=0 successful return,
*      ier=k>0 the k-th argument has an illegal value :
*         ier=1  M<=0
*         ier=2  N<M
*         ier=8  Z<0
*         ier=9  EPS<0
*         ier=13 insufficient storage for P
*         ier=18 insufficient storage for G
* required Sparse BLAS routines: DCSCMM, DCSRMM.

      REAL*8 A(*),W(*),P(*),G(*),F(*),S(*),Q(*)
      REAL*8 EPS,DD,Z
      INTEGER IND(*),IPN(*),IPNA(*),IPNB(*),INDP(*),IPNP(*),INDG(*)
      INTEGER IPNG(*),IPNR(*),IEQ(*),IDES(9)
      DATA IDES/0,0,0,1,1,0,0,0,0/      
* test the input parameters      
      IER=0
      IF(M.LE.0)THEN
        IER=1
        ELSEIF(N.LT.M)THEN
        IER=2
        ELSEIF(Z.LT.0.D+0)THEN
        IER=8
        ELSEIF(EPS.LT.0.D+0)THEN
        IER=9
      ENDIF
      IF(IER.NE.0)RETURN
* initialization
      IRK=0
      NZP=0
      NZG=0
      IP1=1
      IPNP(1)=1
      IPNG(1)=1
* loop on the iteration
      DO 10 K=1,M
* compute a vector of the matrix P
      DO I=1,N
      S(I)=0.D+00
      ENDDO
      DO I=1,IRK   
        J=IPNR(I)
        IF(INDG(J).EQ.K)THEN
          DD=G(J)/G(IPNG(I))
          IPNR(I)=J+1
          II=IPNP(I)          
          IP2=IPNP(I+1)-IPNP(I)+1   
          CALL dcscmm_(0,N,1,1,-1.D+0,IDES,P(II),INDP(II),IP1,IP2,
     *              DD,1,1.D+0,S,N,Q,N) !compute S=-p*(g(i,k)/g(k,k))+S
        ENDIF
      ENDDO
      DO J=IPN(K),IPN(K+1)-1   !compute S=W*(row k of A)+S
        I=IND(J)
        S(I)=S(I)+W(I)*A(J)
      ENDDO
      DD=0.D+0   !compute the weighted norm of S
      DO J=IPN(K),IPN(K+1)-1
        I=IND(J)
        DD=DD+A(J)*S(I)
      ENDDO
* test linear dependence       
      IF(DSQRT(DABS(DD)).GT.EPS)THEN   
* row k of A is linearly independent
        IRK=IRK+1         
        NZG=NZG+1
        IF(NZG.GT.NZGMX)THEN
          IER=18
          RETURN
        ENDIF
        G(NZG)=DD   !diagonal element of G
        INDG(NZG)=IRK
        IPNR(IRK)=NZG+1   !pointer to row k+1 of G
        DO I=1,N   !store S in P in compressed form   
          IF(DABS(S(I)).GT.Z)THEN
            NZP=NZP+1
            IF(NZP.GT.NZPMX)THEN
              IER=13
              RETURN
            ENDIF
            P(NZP)=S(I)
            INDP(NZP)=I
          ENDIF
        ENDDO
        IPNP(IRK+1)=NZP+1
        IF(K.LT.M)THEN   !reset the pointers of A
          IA=IPN(K+1)
          LIPN=IPN(K+1)-IPN(1)
          DO I=1,M-K+1
             IPNA(I)=IPN(K+I)-LIPN
             IF (I.GT.1) IPNB(I-1)=IPNA(I)
          ENDDO  
          CALL dcsrmm_(0,M-K,1,N,1.D+0,IDES,A(IA),IND(IA),IPNA,IPNB,S,
     *      N,0.D+0,F(K+1),M-K,Q,N) !compute F=A*S the irk-th column of G'
          DO I=K+1,M   !store F in G in compressed form
            IF(DABS(F(I)).GT.Z)THEN
              NZG=NZG+1
              IF(NZG.GE.NZGMX)THEN
                IER=18
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
* row k of A is linearly dependent
        IEQ(K-IRK)=K
        IF(IWR.GT.0) WRITE(IWR,22) K,DSQRT(DABS(DD)),EPS
c   22 FORMAT(/1X,'ROW',I5,4X,'WEIGHTED NORM  ',D12.6,3X,
c     *       'TOLERANCE  ',D7.1)
   22 FORMAT(/1X,'la riga',I5,'  della matrice jacobiana è linearmente',
     * ' dipendente'/1X,'norma pesata  ',D12.6,3X,'tolleranza  ',D7.1)
      ENDIF
   10 CONTINUE
* end of the loop
      IEQ(M-IRK+1)=M+1
* compress the matrix G eliminating the linearly dependent rows      
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
      


      SUBROUTINE WGSB(M,N,A,IND,IPN,B,P,INDP,IPNP,G,INDG,IPNG,Y,
     *                Q,IRK,IEQ,IWR)

* WGSB determines the minimal weighted norm solution of a set of sparse 
* mxn (m<=n) linear equations Ax=b where A has been factored using WGSA.
* M    integer, number of rows of A, unchanged on exit.
* N    integer, number of columns of A, unchanged on exit.
* A    real*8 array of lenght nz (nz is the number of nonzeros in A), 
*      the nonzero entries of A, stored by rows, unchanged on exit.
* IND  integer array of lenght nz, column indices of the entries of A, 
*      unchanged on exit. 
* IPN  integer array dimension M+1, pointers to the locations in A,  
*      IPN(i), for i=1 to M, points to the first element of the row i, 
*      IPN(M+1)=nz+1, if row i is empty IPN(i)=IPN(i+1),  
*      unchanged on exit.
* B    real*8 array dimension N, on entry the right-hand side, 
*      on exit the solution.
* P,G  real*8 array, on entry the values produced by WGSA,  
*      unchanged on exit.  
* INDP,IPNP,INDG,IPNG,IEQ  integer array, on entry the values produced  
*      by WGSA, unchanged on exit.
* Y    real*8 array dimension N, workspace.  
* Q    real*8 array dimension N, workspace.  
* IRK  integer, on entry the rank of A determined by WGSA, 
*      unchanged on exit.
* IWR  integer, on entry the unit number for diagnostic messages, 
*      IWR<=0 suppresses the output, unchanged on exit. 
* required Sparse BLAS routines: DCSCSM, DCSCMM.

      REAL*8 A(*),B(*),P(*),G(*),Y(*),Q(*),R
      INTEGER IND(*),IPN(*),INDP(*),IPNP(*),INDG(*),IPNG(*),IEQ(*)
      INTEGER IDES(9),IDES1(9)
      DATA  IDES/0,0,0,1,1,0,0,0,0/
      DATA IDES1/3,1,0,1,1,0,0,0,0/
* gather the elements of B corresponding to the linearly 
* independent  rows of A 
      DO I=1,M-IRK
        Y(M-I+1)=B(IEQ(I))
        DO J=IEQ(I)+1,IEQ(I+1)-1
          B(J-I)=B(J)
        ENDDO
      ENDDO      
* solve G*Y=B     
      CALL dcscsm_(0,IRK,1,1,1.D+0,1.D+0,IDES1,G,INDG,IPNG,IPNG(2),
     *            B,IRK,0.D+00,Y,IRK,Q,IRK) 
* compute B=P*Y 
      CALL dcscmm_(0,N,1,IRK,1.D+0,IDES,P,INDP,IPNP,IPNP(2),
     *            Y,IRK,0.D+00,B,N,Q,N) 
* compute the residual error of the equations removed because of dependency  
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
c   33 FORMAT(/1X,'EQUATION',I5,2X,'  RESIDUAL ERROR  ',D12.6)
   33 FORMAT(/1X,'errore residuo della equazione',I5,2X,
     *       'del sistema lineare  ',D12.6)
      END



      SUBROUTINE WGSERR(IER)
      IF(IER.EQ.1)THEN
      WRITE(6,1)
      ELSEIF(IER.EQ.2)THEN
      WRITE(6,2)
      ELSEIF(IER.EQ.8)THEN
      WRITE(6,8)
      ELSEIF(IER.EQ.9)THEN
      WRITE(6,9)
      ELSEIF(IER.EQ.13)THEN
      WRITE(6,13)
      ELSEIF(IER.EQ.18)THEN
      WRITE(6,18)
      ENDIF
      RETURN
    1 FORMAT(/' numero di equazioni minore o uguale a zero')
    2 FORMAT(/' numero di colonne minore del numero di righe')
    8 FORMAT(/' tolleranza Z minore di zero')
    9 FORMAT(/' tolleranza EPS minore di zero') 
   13 FORMAT(/' superato dimensionamento matrice P')
   18 FORMAT(/' superato dimensionamento matrice G')
      END
