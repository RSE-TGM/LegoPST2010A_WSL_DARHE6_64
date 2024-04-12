#include <stdio.h>
#include <string.h>
#include <math.h>
#include <dconf.inc>
#define _PUBLIC 0
#include <g2comdb.inc>
#include <g2ptrdb.inc>
#include <fileop.inc>
#include <simmsg.inc>

DB_HEADER header;
char *dballoc,*notenmem;

PrintAA(int);
PrintAS(int);
PrintAC(int);
PrintAD(int);
PrintAO(int);
PrintDA(int);
PrintDS(int);
PrintDC(int);
PrintDD(int);
PrintDO(int);
PrintOR(int);
PrintST(int);
PrintINVAO(int);
PrintCOMAN(int);
PrintFSTATO();

main(int argc, char **argv)
{
FILE *fp;
char zero = 0;
int i;



fp=fopen("fdbdp.rtf","r");
// scrittura header
fread(&header,sizeof(DB_HEADER),1,fp);
if((ldb_header - sizeof(DB_HEADER)) > 0)
	{
	for(i=0;i<ldb_header - sizeof(DB_HEADER);i++)
		fread(&zero,1,1,fp);
	}
// allocazione database
dballoc = (char*)malloc(100);
notenmem = (char*)malloc(100);
strcpy(dballoc,"Allocati");
strcpy(notenmem,"Impossibile allocare il database");
allocdb(0,&header);
ClearDB();
// lettura database
if(header.dimaa)
{
   fread((char *)dbaav,sizeof(S_DBAAV),header.dimaa,fp);
   fread((char *)dbaaf,sizeof(S_DBAAF),header.dimaa,fp);
   fread((char *)dbaau,sizeof(S_DBAAU),header.dimaa,fp);
   fread((char *)dbaaal,sizeof(S_DBALL),header.dimaa,fp);
   fread((char *)dbaafa,sizeof(S_DBAAFA),header.dimaa,fp);
}
if(header.dimas)
{
   fread((char *)dbasv,sizeof(S_DBASV),header.dimas,fp);
   fread((char *)dbasf,sizeof(S_DBASF),header.dimas,fp);
   fread((char *)dbasu,sizeof(S_DBASU),header.dimas,fp);
   fread((char *)dbasal,sizeof(S_DBALL),header.dimas,fp);
   fread((char *)dbasde,sizeof(DES),header.dimas,fp);
}
if(header.dimac)
{
   fread((char *)dbacv,sizeof(S_DBACV),header.dimac,fp);
   fread((char *)dbacf,sizeof(S_DBACF),header.dimac,fp);
   fread((char *)dbacu,sizeof(S_DBACU),header.dimac,fp);
   fread((char *)dbacal,sizeof(S_DBALL),header.dimac,fp);
}
if(header.dimad)
{
   fread((char *)dbadv,sizeof(S_DBADV),header.dimad,fp);
   fread((char *)dbadf,sizeof(S_DBADF),header.dimad,fp);
   fread((char *)dbadu,sizeof(S_DBADU),header.dimad,fp);
   fread((char *)dbadal,sizeof(S_DBALL),header.dimad,fp);
}
if(header.dimao)
{
   fread((char *)dbaof,sizeof(S_DBAOF),header.dimao,fp);
   fread((char *)dbaou,sizeof(S_DBAOU),header.dimao,fp);
   fread((char *)dbaom,sizeof(S_DBAOM),header.dimao,fp);
}
if(header.dimda)
{
        fread((char *)dbda,sizeof(S_DBDA),header.dimda,fp);
        fread((char *)dbdatr,sizeof(S_DBDATR),header.dimda,fp);
   fread((char *)dbdau,sizeof(S_DBDAU),header.dimda,fp);
        fread((char *)dbdaco,sizeof(S_CALIN),header.dimda,fp);
}
if(header.dimds)
{
        fread((char *)dbds,sizeof(S_DBDS),header.dimds,fp);
        fread((char *)dbdstr,sizeof(S_DBDSTR),header.dimds,fp);
        fread((char *)dbdsu,sizeof(S_DBDSU),header.dimds,fp);
        fread((char *)dbdsco,sizeof(S_CALIN),header.dimds,fp);
   fread((char *)dbdsde,sizeof(S_DCALC),header.dimds,fp);
}
if(header.dimdc)
{
        fread((char *)dbdc,sizeof(S_DBDC),header.dimdc,fp);
        fread((char *)dbdctr,sizeof(S_DBDCTR),header.dimdc,fp);
        fread((char *)dbdcu,sizeof(S_DBDCU),header.dimdc,fp);
        fread((char *)dbdcco,sizeof(S_CALIN),header.dimdc,fp);
}
if(header.dimdd)
{
        fread((char *)dbdd,sizeof(S_DBDD),header.dimdd,fp);
        fread((char *)dbddtr,sizeof(S_DBDDTR),header.dimdd,fp);
        fread((char *)dbddu,sizeof(S_DBDDU),header.dimdd,fp);
        fread((char *)dbddco,sizeof(S_CALIN),header.dimdd,fp);
}
if(header.dimdo)
{
        fread((char *)dbdo,sizeof(S_DBDO),header.dimdo,fp);
        fread((char *)dbdou,sizeof(S_DBDOU),header.dimdo,fp);
        fread((char *)dbdom,sizeof(S_DBDOM),header.dimdo,fp);
}
if(header.dimor)
{
        fread((char *)dbosc,sizeof(S_DBOSC),header.dimor,fp);
        fread((char *)dbosa,sizeof(S_DBOSA),header.dimor,fp);
        fread((char *)dbosp,sizeof(S_DBOSP),header.dimor,fp);
        fread((char *)dbto,sizeof(S_DBTO),header.dimor,fp);
        fread((char *)dbou,sizeof(S_DBOU),header.dimor,fp);
        fread((char *)dboft,sizeof(S_DBOFT),header.dimor,fp);
        fread((char *)dbode,sizeof(S_DESORG),header.dimor,fp);
}
if(header.dimst)
{
        fread((char *)dbsttr,sizeof(S_DBSTTR),header.dimst,fp);
        fread((char *)dbstu,sizeof(S_DBSTU),header.dimst,fp);
        fread((char *)dbstv,sizeof(S_DBSTV),(header.dimst*g0lunst),fp);
}
fclose(fp);

if(argc >=2)
   if(strcmp(argv[1],"AA")==0)
	PrintAA(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"AS")==0)
	PrintAS(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"AD")==0)
	PrintAD(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"AC")==0)
	PrintAC(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"AO")==0)
	PrintAO(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"DA")==0)
	PrintDA(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"DS")==0)
	PrintDS(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"DC")==0)
	PrintDC(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"DD")==0)
	PrintDD(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"DO")==0)
	PrintDO(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"OR")==0)
	PrintOR(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"ST")==0)
	PrintST(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"COMAN")==0)
	PrintCOMAN(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"INVAO")==0)
	PrintINVAO(atoi(argv[2]));
if(argc >=2)
   if(strcmp(argv[1],"FSTATO")==0)
	PrintFSTATO();

return(1);
}





static int ClearDB()
{
if(header.dimaa)
{
   memset((char *)dbaav,0,sizeof(S_DBAAV)*header.dimaa);
   memset((char *)dbaaf,0,sizeof(S_DBAAF)*header.dimaa);
   memset((char *)dbaau,0,sizeof(S_DBAAU)*header.dimaa);
   memset((char *)dbaaal,0,sizeof(S_DBALL)*header.dimaa);
   memset((char *)dbaafa,0,sizeof(S_DBAAFA)*header.dimaa);
}
if(header.dimas)
{
   memset((char *)dbasv,0,sizeof(S_DBASV)*header.dimas);
   memset((char *)dbasf,0,sizeof(S_DBASF)*header.dimas);
   memset((char *)dbasu,0,sizeof(S_DBASU)*header.dimas);
   memset((char *)dbasal,0,sizeof(S_DBALL)*header.dimas);
   memset((char *)dbasde,0,sizeof(DES)*header.dimas);
}
if(header.dimac)
{
   memset((char *)dbacv,0,sizeof(S_DBACV)*header.dimac);
   memset((char *)dbacf,0,sizeof(S_DBACF)*header.dimac);
   memset((char *)dbacu,0,sizeof(S_DBACU)*header.dimac);
   memset((char *)dbacal,0,sizeof(S_DBALL)*header.dimac);
}
if(header.dimad)
{
   memset((char *)dbadv,0,sizeof(S_DBADV)*header.dimad);
   memset((char *)dbadf,0,sizeof(S_DBADF)*header.dimad);
   memset((char *)dbadu,0,sizeof(S_DBADU)*header.dimad);
   memset((char *)dbadal,0,sizeof(S_DBALL)*header.dimad);
}
if(header.dimao)
{
   memset((char *)dbaof,0,sizeof(S_DBAOF)*header.dimao);
   memset((char *)dbaou,0,sizeof(S_DBAOU)*header.dimao);
   memset((char *)dbaom,0,sizeof(S_DBAOM)*header.dimao);
}
if(header.dimda)
{
        memset((char *)dbda,0,sizeof(S_DBDA)*header.dimda);
        memset((char *)dbdatr,0,sizeof(S_DBDATR)*header.dimda);
   memset((char *)dbdau,0,sizeof(S_DBDAU)*header.dimda);
        memset((char *)dbdaco,0,sizeof(S_CALIN)*header.dimda);
}
if(header.dimds)
{
        memset((char *)dbds,0,sizeof(S_DBDS)*header.dimds);
        memset((char *)dbdstr,0,sizeof(S_DBDSTR)*header.dimds);
        memset((char *)dbdsu,0,sizeof(S_DBDSU)*header.dimds);
        memset((char *)dbdsco,0,sizeof(S_CALIN)*header.dimds);
   memset((char *)dbdsde,0,sizeof(S_DCALC)*header.dimds);
}
if(header.dimdc)
{
        memset((char *)dbdc,0,sizeof(S_DBDC)*header.dimdc);
        memset((char *)dbdctr,0,sizeof(S_DBDCTR)*header.dimdc);
        memset((char *)dbdcu,0,sizeof(S_DBDCU)*header.dimdc);
        memset((char *)dbdcco,0,sizeof(S_CALIN)*header.dimdc);
}
if(header.dimdd)
{
        memset((char *)dbdd,0,sizeof(S_DBDD)*header.dimdd);
        memset((char *)dbddtr,0,sizeof(S_DBDDTR)*header.dimdd);
        memset((char *)dbddu,0,sizeof(S_DBDDU)*header.dimdd);
        memset((char *)dbddco,0,sizeof(S_CALIN)*header.dimdd);
}
if(header.dimdo)
{
        memset((char *)dbdo,0,sizeof(S_DBDO)*header.dimdo);
        memset((char *)dbdou,0,sizeof(S_DBDOU)*header.dimdo);
        memset((char *)dbdom,0,sizeof(S_DBDOM)*header.dimdo);
}
if(header.dimor)
{
        memset((char *)dbosc,0,sizeof(S_DBOSC)*header.dimor);
        memset((char *)dbosa,0,sizeof(S_DBOSA)*header.dimor);
        memset((char *)dbosp,0,sizeof(S_DBOSP)*header.dimor);
        memset((char *)dbto,0,sizeof(S_DBTO)*header.dimor);
        memset((char *)dbou,0,sizeof(S_DBOU)*header.dimor);
        memset((char *)dboft,0,sizeof(S_DBOFT)*header.dimor);
        memset((char *)dbode,0,sizeof(S_DESORG)*header.dimor);
}
if(header.dimst)
{
        memset((char *)dbsttr,0,sizeof(S_DBSTTR)*header.dimst);
        memset((char *)dbstu,0,sizeof(S_DBSTU)*header.dimst);
        memset((char *)dbstv,0,sizeof(S_DBSTV),(header.dimst*g0lunst));
}
}

PrintAS(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimas;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbasu[i]>=0)
	{
	printf(
	  "AS - %d - val=%f - f=%x - zona=%d tr=%x \n",i,
		dbasv[i],dbasf[i],dbasu[i],dbasal[i].tr_bdm);
	printf("   soglie(%x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x)\n",i,
		dbasal[i].alto_sic.cval[0],
		dbasal[i].alto_sic.cval[1],
		dbasal[i].alto_sic.cval[2],
		dbasal[i].alto_sic.cval[3],
		dbasal[i].alto_con.cval[0],
		dbasal[i].alto_con.cval[1],
		dbasal[i].alto_con.cval[2],
		dbasal[i].alto_con.cval[3],
		dbasal[i].bass_con.cval[0],
		dbasal[i].bass_con.cval[1],
		dbasal[i].bass_con.cval[2],
		dbasal[i].bass_con.cval[3],
		dbasal[i].bass_sic.cval[0],
		dbasal[i].bass_sic.cval[1],
		dbasal[i].bass_sic.cval[2],
		dbasal[i].bass_sic.cval[3]
		);
	printf("periodo = %x tipoc = %d  link = %d\n",
		dbasde[i].a.periodo,dbasde[i].a.tipoc,dbasde[i].a.link);
	switch(dbasde[i].a.tipoc)
		{
		case 1:  // media
		case 2:  // massimo
		case 3:  // minimo
			printf("ammm: punt=%d ext=%d freq=%d\n",
			dbasde[i].a.indice.punt,
			dbasde[i].a.indice.ext,
			dbasde[i].a.freq);
			break;
		case 4:   // integrale
		case 5:   // accumulo
			printf("integrale: punt=%d ext=%d freq=%d time=%d\n",
			dbasde[i].i.indice.punt,
			dbasde[i].i.indice.ext,
			dbasde[i].i.freq,dbasde[i].i.time);
			break;
		case 6:   // portata AGA
		case 7:   // portata UNI
			printf("portata: punt=%d %d %d ext=%d %d %d c1=%f c2=%f\n",
			dbasde[i].p.Dp.punt,
			dbasde[i].p.press.punt,
			dbasde[i].p.temper.punt,
			dbasde[i].p.Dp.ext,
			dbasde[i].p.press.ext,
			dbasde[i].p.temper.ext,
			dbasde[i].p.cost1,dbasde[i].p.cost2);
			break;
		case  8:  // filtro
		       printf("filtro: punt = %d ext = %d cost = %d\n",
				dbasde[i].f.misura.punt,
				dbasde[i].f.misura.ext,
				dbasde[i].f.cost1);
			break;
		case  9:  // media
			printf("media: %d %d - %d %d - %d %d\n",
			dbasde[i].m.misura[0].punt,dbasde[i].m.misura[0].ext,
			dbasde[i].m.misura[1].punt,dbasde[i].m.misura[1].ext,
			dbasde[i].m.misura[2].punt,dbasde[i].m.misura[2].ext);
			printf("       %d %d - %d %d - %d %d\n",
			dbasde[i].m.misura[3].punt,dbasde[i].m.misura[3].ext,
			dbasde[i].m.misura[4].punt,dbasde[i].m.misura[4].ext,
			dbasde[i].m.misura[5].punt,dbasde[i].m.misura[5].ext);
			break;
		case 10:
			{
			char q[4];
			memcpy(q,&dbasde[i].o.c_m,4);
			printf(
			  "operazioni: punt=%d ext=%d oper=%d cost=%x%x%x%x\n",
				dbasde[i].o.misura.punt,
                        	dbasde[i].o.misura.ext,
                        	dbasde[i].o.oper,
				q[0],q[1],q[2],q[3]);
			break;
			}
		case  11:  // somma
			printf("somma: %d %d - %d %d - %d %d - %d %d\n",
			dbasde[i].s.ind_misure[0],dbasde[i].s.tip_misure[0],
			dbasde[i].s.ind_misure[1],dbasde[i].s.tip_misure[1],
			dbasde[i].s.ind_misure[2],dbasde[i].s.tip_misure[2],
			dbasde[i].s.ind_misure[3],dbasde[i].s.tip_misure[3]);
			printf("       %d %d - %d %d - %d %d - %d %d\n",
			dbasde[i].s.ind_misure[3],dbasde[i].s.tip_misure[4],
			dbasde[i].s.ind_misure[4],dbasde[i].s.tip_misure[5],
			dbasde[i].s.ind_misure[6],dbasde[i].s.tip_misure[6],
			dbasde[i].s.ind_misure[7],dbasde[i].s.tip_misure[7]);
			break;
		case 12:   // scarto Q
			printf("scarto: punt=%d ext=%d freq=%d\n",
			dbasde[i].q.misura.punt,
			dbasde[i].q.misura.ext,
			dbasde[i].q.freq);
			break;
		case 13:   // organi
			printf("organi: punt=%d ext=%d stato=%d\n",
			dbasde[i].r.organo.punt,
			dbasde[i].r.organo.ext,
			dbasde[i].r.stato);
			break;
		case 14:   // ore misura
			{
			char q[4];
			memcpy(q,&dbasde[i].h.v_s,4);
			printf(
			  "ore misura: punt=%d ext=%d cost=%x%x%x%x\n",
				dbasde[i].h.misura.punt,
                        	dbasde[i].h.misura.ext,
				q[0],q[1],q[2],q[3]);
			break;
			}
		}
		
        }
/*	
   memset((char *)dbasv,0,sizeof(S_DBASV)*header.dimas);
   memset((char *)dbasf,0,sizeof(S_DBASF)*header.dimas);
   memset((char *)dbasu,0,sizeof(S_DBASU)*header.dimas);
   memset((char *)dbasal,0,sizeof(S_DBALL)*header.dimas);
   memset((char *)dbasde,0,sizeof(DES)*header.dimas);
*/
}

PrintAA(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimaa;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbaau[i]>=0)
	{
	printf(
	  "AA - %d - val=%f - f=%x - zona=%d tr=%x \n",i,
		dbaav[i],dbaaf[i],dbaau[i],dbaaal[i].tr_bdm);
	printf("   soglie(%x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x)\n",i,
		dbaaal[i].alto_sic.cval[0],
		dbaaal[i].alto_sic.cval[1],
		dbaaal[i].alto_sic.cval[2],
		dbaaal[i].alto_sic.cval[3],
		dbaaal[i].alto_con.cval[0],
		dbaaal[i].alto_con.cval[1],
		dbaaal[i].alto_con.cval[2],
		dbaaal[i].alto_con.cval[3],
		dbaaal[i].bass_con.cval[0],
		dbaaal[i].bass_con.cval[1],
		dbaaal[i].bass_con.cval[2],
		dbaaal[i].bass_con.cval[3],
		dbaaal[i].bass_sic.cval[0],
		dbaaal[i].bass_sic.cval[1],
		dbaaal[i].bass_sic.cval[2],
		dbaaal[i].bass_sic.cval[3]
		);
        }
}

PrintAD(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimad;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbadu[i]>=0)
	{
	printf(
	  "AD - %d - val=%f - f=%x - zona=%d tr=%d \n",i,
		dbadv[i],dbadf[i],dbadu[i],dbadal[i].tr_bdm);
	printf("   soglie(%x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x)\n",i,
		dbadal[i].alto_sic.cval[0],
		dbadal[i].alto_sic.cval[1],
		dbadal[i].alto_sic.cval[2],
		dbadal[i].alto_sic.cval[3],
		dbadal[i].alto_con.cval[0],
		dbadal[i].alto_con.cval[1],
		dbadal[i].alto_con.cval[2],
		dbadal[i].alto_con.cval[3],
		dbadal[i].bass_con.cval[0],
		dbadal[i].bass_con.cval[1],
		dbadal[i].bass_con.cval[2],
		dbadal[i].bass_con.cval[3],
		dbadal[i].bass_sic.cval[0],
		dbadal[i].bass_sic.cval[1],
		dbadal[i].bass_sic.cval[2],
		dbadal[i].bass_sic.cval[3]
		);
        }
}

PrintAC(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimac;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbacu[i]>=0)
	{
	printf(
	  "AC - %d - val=%f - f=%x - zona=%d tr=%x \n",i,
		dbacv[i],dbacf[i],dbacu[i],dbacal[i].tr_bdm);
	printf("   soglie(%x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x %x|%x|%x|%x)\n",i,
		dbacal[i].alto_sic.cval[0],
		dbacal[i].alto_sic.cval[1],
		dbacal[i].alto_sic.cval[2],
		dbacal[i].alto_sic.cval[3],
		dbacal[i].alto_con.cval[0],
		dbacal[i].alto_con.cval[1],
		dbacal[i].alto_con.cval[2],
		dbacal[i].alto_con.cval[3],
		dbacal[i].bass_con.cval[0],
		dbacal[i].bass_con.cval[1],
		dbacal[i].bass_con.cval[2],
		dbacal[i].bass_con.cval[3],
		dbacal[i].bass_sic.cval[0],
		dbacal[i].bass_sic.cval[1],
		dbacal[i].bass_sic.cval[2],
		dbacal[i].bass_sic.cval[3]
		);
        }
}

PrintAO(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimao;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbaou[i]>=0)
	{
	printf(
	  "AO - %d - f=%x - zona=%d star=%d \n",i,
		dbaof[i],dbaou[i],dbaom[i]);
	}
}

PrintDA(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimda;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbdau[i]>=0)
	{
	printf(
	  "DA - %d - f=%x - zona=%d trat=%x \n",i,
		dbda[i],dbdau[i],dbdatr[i]);
	printf(
	  "     cont - %d %d - %d %d - %d %d - %d %d\n",
		dbdaco[i].tipo_cont[0],dbdaco[i].cont[0],
		dbdaco[i].tipo_cont[1],dbdaco[i].cont[1],
		dbdaco[i].tipo_cont[2],dbdaco[i].cont[2],
		dbdaco[i].tipo_cont[3],dbdaco[i].cont[3]);
	printf(
	  "     inib: tipo %d - %d %d - %d %d\n",
		dbdaco[i].tin_an,dbdaco[i].inib[0],dbdaco[i].tipo_inib[0],
			dbdaco[i].inib[1],dbdaco[i].tipo_inib[1]);
	}
}

PrintDS(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimds;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbdsu[i]>=0)
	{
	printf(
	  "DS - %d - f=%x - zona=%d trat=%x \n",i,
		dbds[i],dbdsu[i],dbdstr[i]);
	printf(
	  "     cont - %d %d - %d %d - %d %d - %d %d\n",
		dbdsco[i].tipo_cont[0],dbdsco[i].cont[0],
		dbdsco[i].tipo_cont[1],dbdsco[i].cont[1],
		dbdsco[i].tipo_cont[2],dbdsco[i].cont[2],
		dbdsco[i].tipo_cont[3],dbdsco[i].cont[3]);
	printf(
	  "     inib: tipo %d - %d %d\n",
		dbdsco[i].tin_an,dbdsco[i].inib[0],dbdsco[i].inib[1]);
	printf(
	  "     calc: tipo %d - %d %d - %d %d - %d %d - %d %d\n",
		dbdsde[i].tipc,
		dbdsde[i].punt[0],dbdsde[i].ext[0],
		dbdsde[i].punt[1],dbdsde[i].ext[1],
		dbdsde[i].punt[2],dbdsde[i].ext[2],
		dbdsde[i].punt[3],dbdsde[i].ext[3]);
		
	}
}

PrintDC(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimdc;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbdcu[i]>=0)
	{
	printf(
	  "DC - %d - f=%x - zona=%d trat=%x \n",i,
		dbdc[i],dbdcu[i],dbdctr[i]);
	printf(
	  "     cont - %d %d - %d %d - %d %d - %d %d\n",
		dbdcco[i].tipo_cont[0],dbdcco[i].cont[0],
		dbdcco[i].tipo_cont[1],dbdcco[i].cont[1],
		dbdcco[i].tipo_cont[2],dbdcco[i].cont[2],
		dbdcco[i].tipo_cont[3],dbdcco[i].cont[3]);
	printf(
	  "     inib: tipo %d - %d %d\n",
		dbdcco[i].tin_an,dbdcco[i].inib[0],dbdcco[i].inib[1]);
	}
}

PrintDD(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimdd;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbddu[i]>=0)
	{
	printf(
	  "DD - %d - f=%x - zona=%d trat=%x \n",i,
		dbdd[i],dbddu[i],dbddtr[i]);
	printf(
	  "     cont - %d %d - %d %d - %d %d - %d %d\n",
		dbddco[i].tipo_cont[0],dbddco[i].cont[0],
		dbddco[i].tipo_cont[1],dbddco[i].cont[1],
		dbddco[i].tipo_cont[2],dbddco[i].cont[2],
		dbddco[i].tipo_cont[3],dbddco[i].cont[3]);
	printf(
	  "     inib: tipo %d - %d %d\n",
		dbddco[i].tin_an,dbddco[i].inib[0],dbddco[i].inib[1]);
	}
}

PrintDO(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimdo;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbdou[i]>=0)
	{
	printf(
	  "DO - %d - f=%x - zona=%d star=%x \n",i,
		dbdo[i],dbdou[i],dbdom[i]);
	}
}

PrintOR(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimor;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbou[i]>=0)
	{
	printf(
	  "OR - %d - f=%x - zona=%d att=%d prec=%d t-out=%d ft-out=%d\n",i,
		dbosc[i],dbou[i],dbosa[i],dbosp[i],dbto[i],dboft[i]);
	printf(
	  "   trat=%d tipo = %d contr=%d %d - %d %d - %d %d - %d %d - %d %d\n",
		dbode[i].trat,dbode[i].tipo,
		dbode[i].punt[0],dbode[i].ext[0],
		dbode[i].punt[1],dbode[i].ext[1],
		dbode[i].punt[2],dbode[i].ext[2],
		dbode[i].punt[3],dbode[i].ext[3],
		dbode[i].punt[4],dbode[i].ext[4]);
	printf(
	  "   stprot = %d time_out = %d funz = %d stinib = %d\n",
	dbode[i].stprot,dbode[i].time_out,dbode[i].funz,dbode[i].stinib);
	printf(
	  "   inib: %d %d %d - %d %d %d\n",
	dbode[i].pinib[0].tipin,dbode[i].pinib[0].punt,dbode[i].pinib[0].ext,
	dbode[i].pinib[1].tipin,dbode[i].pinib[1].punt,dbode[i].pinib[1].ext);
	}
/*
        fread((char *)dbosc,sizeof(S_DBOSC),header.dimor,fp);
        fread((char *)dbosa,sizeof(S_DBOSA),header.dimor,fp);
        fread((char *)dbosp,sizeof(S_DBOSP),header.dimor,fp);
        fread((char *)dbto,sizeof(S_DBTO),header.dimor,fp);
        fread((char *)dbou,sizeof(S_DBOU),header.dimor,fp);
        fread((char *)dboft,sizeof(S_DBOFT),header.dimor,fp);
        fread((char *)dbode,sizeof(S_DESORG),header.dimor,fp);
*/
}

PrintST(int num)
{
int da, a,i;
if(num<0)
	{
	da = 0;
	a = header.dimst;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	if(dbstu[i]>=0)
	{
	printf(
	  "ST - %d - valore = [%s] tr=%x - zona=%d\n",i,
		&dbstv[i],dbsttr[i],dbstu[i]);
	
        }
}

PrintCOMAN(int num)
{
int da, a,i;
FILE *fp;
S_FDCOM_SIM *punt;
int tot=0;

for(i=0;i<header.dimdo;i++)
	if(dbdou[i]>=0)
		++tot;

punt = malloc(sizeof(S_FDCOM_SIM)*tot);
fp=fopen("fdcom.rtf","r");
fread(punt,sizeof(S_FDCOM_SIM),tot,fp);
fclose(fp);

if(num<0)
	{
	da = 0;
	a = tot;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	{
	printf(
	  "COMAN - comando %d - tipo=%d - organo=%d time=%d \n",
		punt[i].comando,
		punt[i].tipo,
		punt[i].organo,
		punt[i].time);
	printf(
	  "      - abili %d - onoff=%d - puntda=%d \n",
		punt[i].abili,
		punt[i].onoff,
		punt[i].puntda);
	printf(
	  "      - STATI: %d/%d %d/%d %d/%d %d/%d \n",
		punt[i].stat[0].st_att,punt[i].stat[0].st_fut,
		punt[i].stat[1].st_att,punt[i].stat[1].st_fut,
		punt[i].stat[2].st_att,punt[i].stat[2].st_fut,
		punt[i].stat[3].st_att,punt[i].stat[3].st_fut);
	}
free(punt);
}

PrintINVAO(int num)
{
int da, a,i;
FILE *fp;
S_FDEAO_SIM *punt;
int tot=0;

for(i=0;i<header.dimao;i++)
	if(dbaou[i]>=0)
		++tot;

punt = malloc(sizeof(S_FDEAO_SIM)*tot);
fp=fopen("fdeao.rtf","r");
fread(punt,sizeof(S_FDEAO_SIM),tot,fp);
fclose(fp);

if(num<0)
	{
	da = 0;
	a = tot;
	}
else
	{
        da = num;
        a = num+1;
        }
for(i=da;i<a;i++)
	{
	printf(
	  "INVAO - puntdb %hd - flabst=%hd - puntaa=%hd\n",
		punt[i].puntdb,
		punt[i].flabst,
		punt[i].puntaa);
	}
free(punt);
}

PrintFSTATO()
{
FILE *fp;
S_FSTATO rec;
int i=0;

printf("fstato\n");
fp=fopen("fstato.rtf","r");
while(fread(&rec,sizeof(S_FSTATO),1,fp)==1)
	{
	printf("record [%d]  ncontr = %d\n",i,rec.ncontr);
	printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		rec.vet_stati[0],
		rec.vet_stati[1],
		rec.vet_stati[2],
		rec.vet_stati[3],
		rec.vet_stati[4],
		rec.vet_stati[5],
		rec.vet_stati[6],
		rec.vet_stati[7],
		rec.vet_stati[8],
		rec.vet_stati[9],
		rec.vet_stati[10],
		rec.vet_stati[11],
		rec.vet_stati[12],
		rec.vet_stati[13],
		rec.vet_stati[14],
		rec.vet_stati[15]);
	printf("%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n",
		rec.vet_stati[16],
		rec.vet_stati[17],
		rec.vet_stati[18],
		rec.vet_stati[19],
		rec.vet_stati[20],
		rec.vet_stati[21],
		rec.vet_stati[22],
		rec.vet_stati[23],
		rec.vet_stati[24],
		rec.vet_stati[25],
		rec.vet_stati[26],
		rec.vet_stati[27],
		rec.vet_stati[28],
		rec.vet_stati[29],
		rec.vet_stati[30],
		rec.vet_stati[31]);
	i++;
	}
}
