      SUBROUTINE SNDB(N,S,D)
      REAL*4 S(*)
      REAL*8 D(*)
      DO I=1,N
      D(I)=DBLE(S(I))
      ENDDO
      RETURN
      END

      SUBROUTINE DBSN(N,D,S)
      REAL*4 S(*)
      REAL*8 D(*)
      DO I=1,N
      S(I)=SNGL(D(I))
      ENDDO
      RETURN
      END

      SUBROUTINE PUNT(N,NT,IR,IPN)
      DIMENSION IR(*),IPN(*)
      NRIGA=0
      DO I=1,NT
         IF (IR(I).GT.NRIGA) THEN
            DO L=NRIGA+1,IR(I)
              IPN(L)=I
            ENDDO
            NRIGA=IR(I)
         ENDIF
      ENDDO
      DO L=NRIGA+1,N+1
        IPN(L)=NT+1
      ENDDO 
      RETURN
      END
      
      
       
      SUBROUTINE SMORZ(NUMS,PCEN,N,X,S)
      DIMENSION X(*),S(*)      
      IF (NUMS.EQ.1) THEN !smorzamento sulle sole eccedenze
	 DO I=1,N
	   IF(X(I).NE.0.)THEN
	     C=ABS(PCEN*X(I))
	     IF (ABS(S(I)).GT.C) THEN
	       IF (S(I).GT.0) THEN
		   S(I)=C
	       ELSE
		  S(I)=-C
	       ENDIF
	     ENDIF
	   ENDIF	   
	 ENDDO 
      ELSE IF (NUMS.EQ.2) THEN !smorzamento su tutte le variabili
	 CM=0.
	 IM=0
	 DO I=1,N
	   IF(X(I).NE.0.)THEN
	     C=ABS(S(I))-ABS(PCEN*X(I))
	     IF(C.GT.0.)THEN
	       IF(C.GT.CM)THEN
	         CM=C
	         IM=I
	       ENDIF
	     ENDIF
	   ENDIF
	 ENDDO
	 IF (IM.GT.0) THEN
           C=ABS(PCEN*X(IM))/ABS(S(IM))
	   CALL SSCAL(N,C,S,1)    
	 ENDIF	 
      ENDIF
      RETURN
      END

  
  
      SUBROUTINE PESIWD(NNOTO,PESI,PESO0,WD)
      DIMENSION PESI(*)
      REAL*8 WD(*)
      DPESO0=DBLE(PESO0)
      I=0                             
      DO WHILE(I.LT.NNOTO)
	I=I+1
	IF(PESI(I).NE.0.)I=NNOTO+1
      ENDDO
      IF(I.GT.NNOTO)THEN !almeno un peso e' stato assegnato
	 DO I=1,NNOTO !scrittura vettore reciproci dei pesi
	   IF(PESI(I).LE.0.)THEN
	     WD(I)=1.D+00/DPESO0
	   ELSE
	     WD(I)=1.D+00/DBLE(PESI(I))
	   ENDIF
	 ENDDO
      ELSE !caso di nessun peso assegnato (li metto tutti unitari)
	 DO I=1,NNOTO
	 WD(I)=1.D+00
	 ENDDO
      ENDIF 
      RETURN
      END   
      


      
      SUBROUTINE SSVV(N,IPSSVV,XY,XYV)
      DIMENSION IPSSVV(*),XY(*),XYV(*)      
      DO I=1,N 
      JJ=IPSSVV(I)
      IF(JJ.GT.0) XYV(JJ)=XY(I)
      ENDDO
      RETURN
      END
      
      SUBROUTINE VVSS(N,IPVVSS,XYV,XY)
      DIMENSION IPVVSS(*),XYV(*),XY(*)
      DO I=1,N
      JJ=IPVVSS(I)
      XY(JJ)=XYV(I)
      ENDDO
      RETURN
      END
      
      
      
      SUBROUTINE SING(N,IPVVSS,SIVAR,IKEEP,stampa1)    
      DIMENSION IPVVSS(*),IKEEP(N,*)
      CHARACTER*8 SIVAR(*)
      DO I=1,N
        IF(IKEEP(I,3).LT.0)THEN
          JR=IABS(IKEEP(I,2))
          JJR=IPVVSS(JR)
          JC=-IKEEP(I,3)
          JJC=IPVVSS(JC)
          WRITE(6,66)JR,JJR,SIVAR(JJR)
C         WRITE(6,66)JR,JJR,SIVAR(JJR),IEQBL(JJR)
C         WRITE(6,67)JC,JJC,SIVAR(JJC)          
          if(stampa1.eq.1)WRITE(55,66)JR,JJR,SIVAR(JJR)
C         WRITE(55,66)JR,JJR,SIVAR(JJR),IEQBL(JJR)
C         WRITE(55,67)JC,JJC,SIVAR(JJC)
        ENDIF
      ENDDO
      RETURN
   66 FORMAT(1x,'singolarità nella riga',i4,'  (equazione',i4,1x,a8,')')
C  66 FORMAT(1x,'singolarità nella riga',i4,'  (equazione',i4,1x,a8,')',
C    *   2x,'blocco',i4,')')
C  67 FORMAT(1x,'colonna',i4,'  (',i4,1x,a8,')',3x,'eliminata')      
      END 


 
      SUBROUTINE EQBL(NBL,NUSTA,NUSCI,IEQBL)
      DIMENSION NUSTA(*),NUSCI(*),IEQBL(*)
      L=0
      DO I=1,NBL
      DO J=1,NUSCI(I)
      L=L+1
      IEQBL(L)=I
      ENDDO
      ENDDO
      DO I=1,NBL
      DO J=1,NUSTA(I)
      L=L+1
      IEQBL(L)=I
      ENDDO
      ENDDO
      RETURN
      END


      SUBROUTINE BLO(NEQSIS,ICONV,IEQBL,NBL,IBLO,JP)
      DIMENSION ICONV(*),IEQBL(*),IBLO(*)
      IF(JP.EQ.0)THEN
        DO I=1,NBL
        IBLO(I)=1
        ENDDO
      ELSEIF(ABS(JP).EQ.1)THEN
        DO I=1,NEQSIS
          IF(ICONV(I).EQ.1)THEN
          II=IEQBL(I)
          IBLO(II)=1
          ENDIF
        ENDDO
      ELSE
        DO I=1,NEQSIS
          IF(ICONV(I).EQ.0)THEN
          II=IEQBL(I)
          IBLO(II)=1
          ENDIF
        ENDDO
      ENDIF
      RETURN
      END

     
      subroutine stampab(nbl,iblo,nusta,nqmodu,neqsis,iconv)
      dimension iblo(*),nusta(*),nqmodu(*),iconv(*)
      ne=0
      nb=0
      neb=0
      do i=1,nbl
      if(iblo(i).eq.1)then
      write(55,*)'iblo nusta nqmodu',i,nusta(i),nqmodu(i)
      nb=nb+1
      neb=neb+nusta(i)+nqmodu(i)
      endif
      enddo
      do i=1,neqsis
      ne=ne+iconv(i)
      enddo
      write(55,111) nb,neb,ne
      return
  111 format(1x,'num.blocchi  num.equaz.blocchi  num.equaz.',3i5)  
      end
