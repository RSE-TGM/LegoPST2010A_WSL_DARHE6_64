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
        l'include read.c provvede ad inserire un
        dato del data base di sistema in un variabile locale
*/
/*
        puntatore data base locale
*/
i.s=*(s->pc+2) ;
if(i.re.indi) i.s=*(fp-(i.di.byad>>1));
pcha=s->dbc+i.re.byad ;                 /* punt. in dbl a bytes */

/*
        puntatore data base di sistema
*/
tipo=( *(s->pc+3)  & 0xF000) >> 12 ;
punt=*(s->pc+3) & 0x0FFF ;

switch(tipo)
{
case g1tipaa :          /* analogici acquisiti  */
        u.f   =g2an.dbaav[punt] ;
        p1=&g2an.dbaaf[punt] ;
        swab(p1,&u.c[4],2) ;
        off=6 ;
        break ;
case g1tipas :          /* analogici calcolati standard */
        u.f   =g2an.dbasv[punt] ;
        p1=&g2an.dbasf[punt] ;
        swab(p1,&u.c[4],2) ;
        off=6 ;
        break ;
case g1tipac :          /* analogici calcolati non stand.*/
        u.f   =g2an.dbacv[punt] ;
        p1=&g2an.dbacf[punt] ;
        swab(p1,&u.c[4],2) ;
        off=6 ;
        break ;
case g1tipad :          /* analogici di diagnostica     */
        u.f   =g2an.dbadv[punt] ;
        p1=&g2an.dbadf[punt] ;
        swab(p1,&u.c[4],2) ;
        off=6 ;
        break ;
case g1tipda :          /* digitali acquisiti           */
        u.c[0]=g2di.dbda[punt] >> 8 ;
        off=1 ;
        break ;
case g1tipds :          /* digitali calcolati standard  */
        u.c[0]=g2di.dbds[punt] >> 8 ;
        off=1 ;
        break ;
case g1tipdc :          /* digitali calcolati non stand*/
        u.c[0]=g2di.dbdc[punt] >> 8 ;
        off=1 ;
        break ;
case g1tipdd :          /* digitali di diagnostica      */
        u.c[0]=g2di.dbdd[punt] >> 8 ;
        off=1 ;
        break ;
case g1tipor :          /*      organi                  */
        p1=&g2or.dbosc[punt] ;
        swab(p1,u.c,2) ;
        off=2 ;
        break ;
}
memcpy(pcha,&u.c[0],off) ;

