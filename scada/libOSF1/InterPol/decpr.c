/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/

/*
        la function decpr risolve l'istruzione print
        esamino il tipo di argomento
*/
PRINT :

switch (*s->pc)
{
case p_pag:             /* caso di salto pagina  */  
	ta.strprint[0]=0x0c;
	ta.strprint[1]=0x00;
	ta.hea.lung=sizeof(HEA_STA)+lstr_pag;
	invia(tpr_tabulato,&ta);
        s->pc++ ;
        goto PRINT ;

case p_ret:             /* caso LF + CR */
	ta.strprint[0]=0x0d;
	ta.strprint[1]=0x0a;
	ta.hea.lung=sizeof(HEA_STA)+lstr_ret;
	invia(tpr_tabulato,&ta);
        s->pc++ ;
        goto PRINT ;

case p_stringa:         /* caso stringa */
	s->pc++;
        lunprint=*s->pc;	  	// dopo l'incremento s->pc punta al numero
				   	// di caratteri componenti la stringa
	s->pc++;
	ta.hea.lung=sizeof(HEA_STA)+lunprint;
	memcpy(ta.strprint,s->pc,lunprint);
	invia(tpr_tabulato,&ta);
        s->pc=s->pc+(lunprint+1)/2 ;    // incremento della lunghezza della
					// della stringa
        goto PRINT ;
case p_tim1:            /* richiesta anno mese giorno */
	decnum(ta.strprint,2,-1,(short)dbadv[db_giorno],0.);
	strcpy(&ta.strprint[2]," - ");
	decnum(&ta.strprint[5],2,-1,(short)dbadv[db_mese],0.);
	strcpy(&ta.strprint[7]," - ");
	decnum(&ta.strprint[10],2,-1,(short)dbadv[db_anno],0.);
  	ta.hea.lung=sizeof(HEA_STA)+lstr_tempo;
	invia(tpr_tabulato,&ta);
        s->pc++ ;
        goto PRINT ;

case p_tim2:            /* richiesta ora minuti seco. */
	decnum(ta.strprint,2,-1,(short)dbadv[db_ora],0.);
	strcpy(&ta.strprint[2]," - ");
	decnum(&ta.strprint[5],2,-1,(short)dbadv[db_minuti],0.);
	strcpy(&ta.strprint[7]," - ");
	decnum(&ta.strprint[10],2,-1,(short)dbadv[db_secondi],0.);
	ta.hea.lung=sizeof(HEA_STA)+lstr_tempo;
	invia(tpr_tabulato,&ta);
        s->pc++ ;
        goto PRINT ;

case p_spaces :		/* caso di spazi blank   */
	s->pc++;
        lunprint=*s->pc;	  	// dopo l'incremento s->pc punta al numero
					// di caratteri blank da stampare.
	memset(ta.strprint,0x20,lunprint);
	ta.hea.lung=sizeof(HEA_STA)+lunprint;
	invia(tpr_tabulato,&ta);
        s->pc++ ;
        goto PRINT ;

case p_format :
	s->pc++;
	pform=(struct formato *)s->pc;		// punta alla descrizione del formato
	s->pc++;
        i.s  =*s->pc ;      /* indirizzo variabile */
        if(i.re.indi) i.s= *(fp-(i.di.byad>>1)) ;
        u.s[0]=*(s->dbs+(i.re.byad>>1)) ;
        u.s[1]=*(s->dbs+(i.re.byad>>1)+1)  ;

	if(pform->tipo==treale || pform->tipo==tanalogico)
	{
		decnum(ta.strprint,pform->f.re.tot+1,pform->f.re.fraz,0,u.f);
		ta.hea.lung=sizeof(HEA_STA)+(pform->f.re.tot+1);
		invia(tpr_tabulato,&ta);
	}
	else if(pform->tipo==tstringa)		  // caso di tipo stringa
	{ 
		lunprint=pform->f.in;
		memset(ta.strprint,0x20,lunprint);

		if(diff=( pform->f.in - strlen(s->dbs+(i.re.byad>>1))) <=0 )
			memcpy(ta.strprint,s->dbs+(i.re.byad>>1),lunprint);
		else
            		strcpy(ta.strprint,s->dbc+(i.re.byad)) ;

		ta.hea.lung=sizeof(HEA_STA)+lunprint;
		invia(tpr_tabulato,&ta);
	}
	else 	// caso di tipo intero e organo
	{
		decnum(ta.strprint,pform->f.in,-1,u.s[0],0.);
		ta.hea.lung=sizeof(HEA_STA)+pform->f.in;
		invia(tpr_tabulato,&ta);
	}

	s->pc++;
        goto PRINT ;
case p_dl:       /* stampa stato digitale o valore logico */
	s->pc++;
        i.s  =*s->pc ;      /* indirizzo variabile */
        if(i.re.indi) i.s= *(fp+(i.di.byad>>1)) ;
        u.c[0]=*(s->dbc+i.re.byad) ;
        if(u.c[0]&0x01) ta.strprint[0]='1' ;		// esamina il bit di stato
        else  ta.strprint[0]='0' ;
	ta.hea.lung=sizeof(HEA_STA)+1;
	invia(tpr_tabulato,&ta);
        s->pc++ ;
        goto PRINT ;

case p_cod:
        lung=SCD_SIGLA;   /* lunghezza ed offset  */
        off =po_nome;
        goto EXEC ;
case p_desc:
        lung=SCD_DESCRIZIONE ; off=po_desc ;
        goto EXEC ;
case p_umis:
        lung=pl_umis ;  off=po_umis ;
EXEC :
	s->pc++;
        i.s=*s->pc ;
        tipo=(short)*(s->dbs+(i.re.byad>>1)) ;
        punt=(short)*(s->dbs+(i.re.byad>>1)+1) ;
	dist=(long)nbyte[tipo]*punt+off_f[tipo]+off; 	
        if(rbyte(fileno(fpp[fdde]),(short*)ta.strprint,dist,lung)!=lung) 
		perror("Errore lettura descrittori") ;
	ta.hea.lung=sizeof(HEA_STA)+lung;
	invia(tpr_tabulato,&ta);
	s->pc++;
        goto PRINT ;
case p_org:                     /* stampo stato organo  */
	s->pc++;
        i.s=*s->pc ;        /* indirizzo organo     */
        if(i.re.indi) i.s=*(fp+(i.di.byad>>1)) ;
/*
        lettura dalla tabella stat_diz
*/
        memcpy(ta.strprint,&stat_diz[lun_stato*(*(s->dbc+i.re.byad))],
                lun_stato) ;
	ta.hea.lung=sizeof(HEA_STA)+lun_stato;
	invia(tpr_tabulato,&ta);
	s->pc++;
        goto PRINT ;
case -1 :           /* tappo finale */
        s->pc++ ;
        break ;
case p_sgraf:           /* recupero coefficienti */
	s->pc++;
        u.s[0]=*s->pc ; 	// limite basso
	s->pc++;
	u.s[1]=*s->pc ;	// limite alto
	coeff_mol=100./(u.s[1]-u.s[0]);   // coefficiente moltiplicativo
	coeff_add=-u.s[0]*coeff_mol;	  // coefficiente additivo
        s->pc++ ;
        goto PRINT ;
case p_graf :
	s->pc++;
        numgrafv=*s->pc;	  // ricava il numero di variabili presenti
				  // nel grafico.
        off=coeff_add;
        memset(ta.strprint,' ',100) ;      /* riempio di blank */
        ta.strprint[0]=ta.strprint[99]=':';   /* limiti grafico */
        if(off >= 0) ta.strprint[off]='I'; /* zero del grafico */
//		  printf("\n numero di variabili grafiche = %d",numgrafv);
        for (j=0;j<numgrafv;j++)
	{
        	s->pc++;
        	i.s=*s->pc ;
        	u.s[0]=*(s->dbs+(i.re.byad>>1)) ;
        	u.s[1]=*(s->dbs+(i.re.byad>>1)+1) ;
        	off=u.f*coeff_mol+coeff_add ;   /* valore grafico */
        	if(off<0) off=0 ;
        	if(off>100) off=100 ;        	/* limiti massimi */
        	ta.strprint[off]=j+1+0x30 ;       	/* n. mis.in ascii*/
        }
        s->pc++ ;
	ta.hea.lung=sizeof(HEA_STA)+100;
	invia(tpr_tabulato,&ta);
        goto PRINT ;
default :
        printf(" decpr.c istruzione non nota %d ",*(s->pc)) ;
	pscserr(ERR_TASK,TASK_TABUL,ROU_CPRINT,*s->pc,SYS_CONT);
        s->pc++ ;
}

