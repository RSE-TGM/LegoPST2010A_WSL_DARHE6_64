	FUNCTION PHSAT(HNOW)
C
C funzione che chiama la nuova phsat C come funzione void
C
        REAL phs
        
        call phsat_new(HNOW,phs)
        PHSAT=phs
        RETURN
	END

