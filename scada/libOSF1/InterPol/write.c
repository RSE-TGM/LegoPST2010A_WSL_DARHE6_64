/**********************************************************************
*
*       C Source:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
#ifndef lint
static char *_csrc = "@(#) %filespec: %  (%full_filespec: %)";
#endif
/*
        Variabile per identificazione della versione
*/
/*
        Fine sezione per SCCS
*/
/*
        l'include    write.c provvede ad inserire un
        dato del data base di sistema in un variabile locale
*/
/*
        puntatore data base locale
*/
i.s=*(s->pc+2) ;
if(i.re.indi) i.s=*(fp-(i.di.byad>>1));
pcha=s->dbc+i.re.byad ;                 /* punt. in dbl a bytes */

memcpy(u.c,pcha,6) ;            /* al massimo 6 bytes di dati */

/*
        puntatore data base di sistema
*/
tipo=(*(s->pc+3)  & 0xF000) >> 12 ;
punt=*(s->pc+3) & 0x0FFF ;

switch(tipo)
{
case g1tipaa :          /* analogici acquisiti  */
        g2an.dbaav[punt]=u.f ;
        p1=&g2an.dbaaf[punt] ;
        swab(&u.c[4],p1,2) ;
        break ;
case g1tipas :          /* analogici calcolati standard */
        g2an.dbasv[punt]=u.f ;
        p1=&g2an.dbasf[punt] ;
        swab(&u.c[4],p1,2) ;
        break ;
case g1tipac :          /* analogici calcolati non stand.*/
        g2an.dbacv[punt]=u.f ;
        p1=&g2an.dbacf[punt] ;
        swab(&u.c[4],p1,2) ;
        break ;
case g1tipad :          /* analogici di diagnostica     */
        g2an.dbadv[punt]=u.f ;
        p1=&g2an.dbadf[punt] ;
        swab(&u.c[4],p1,2) ;
        break ;
case g1tipda :          /* digitali acquisiti           */
        g2di.dbda[punt] =u.c[0]<<8 + (g2di.dbda[punt] & 0x00FF) ;
        break ;
case g1tipds :          /* digitali calcolati standard  */
        g2di.dbds[punt] = u.c[0]<<8 + (g2di.dbds[punt] & 0x00FF) ;
        break ;
case g1tipdc :          /* digitali calcolati non stand*/
        g2di.dbdc[punt] = u.c[0] <<8 + (g2di.dbdc[punt] & 0x00FF) ;
        break ;
case g1tipdd :          /* digitali di diagnostica      */
        g2di.dbdd[punt] = u.c[0]<<8 +(g2di.dbdd[punt] & 0x00FF) ;
        break ;
case g1tipdo :          /* comandi                      */
        mesco.indice=punt ;     
        gsend(s->globale,s->locale,&mesco.mess,sizeof(S_MUTCA)) ;
        break ;
case g1tipor :          /*      organi                  */
        p1=&g2or.dbosc[punt] ;
        swab(u.c,p1,2) ;
        break ;
}

*) 
