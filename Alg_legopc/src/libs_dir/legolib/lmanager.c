#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

/* ethernet - routine di recupero ethernet address                 */

static char buff[21],buff1[21],serialN[21],snpass[21]="01091995010919950109\0";
static char buffone[300];

extern void ethernet(char *);

/* routine gettime - legge tempo corrente */

void gettime(void)
{

	time_t timer;
	struct tm *act_time;

	timer = time(&timer);
	act_time = localtime(&timer);
 
	sprintf(buff+12,"%02d%02d%04d",
		    act_time->tm_mday,
			(act_time->tm_mon + 1),
			act_time->tm_year + 1900);

}

/* unshuffle - routine di decriptazione SN                 */

void unshuffle()
{
	int  i,j;
	char ch;

	for (i=0;i<20;i+=2) {
		buff1[i] = serialN[i+1];
		buff1[i+1] = serialN[i];
	}
	buff1[20]='\0';

	for (i=0;i<20;i++) {
		ch=buff1[i];
   		if (islower(ch)) ch=toupper(ch);
		for (j=0;j<i;j++) {
			if (ch == '0') {
				ch = '9';
			} else if (ch == 'A') {
				ch = 'Z';
			} else if ((ch > 'A' && ch <= 'Z') || 
					   (ch > '0' && ch <= '9'))  {
				--ch;
			} else {
				printf("Codice errato!\n");
			}
		}
		buff1[i]=ch;
	}

        for (i=0;i<10;i+=2) {
		ch = buff1[i];
		buff1[i] = buff1[19-i];
		buff1[19-i] = ch;
	}

	for (i=0;i<20;i++) {
		ch=buff1[i];
		for (j=0;j<i;j++) {
			if (ch == '0') {
				ch = '9';
			} else if (ch == 'A') {
				ch = 'Z';
			} else if ((ch > 'A' && ch <= 'Z') || 
					   (ch > '0' && ch <= '9'))  {
				--ch;
			} else {
				printf("Codice errato!\n");
			}
		}
		buff1[i]=ch;
	}

}

/* DateManage - routine di gestione exiry date                  */

int DateManage(char *date,char *expiry) 

{

   int goed=0;
   int d,m,y;
   int d_exp,m_exp,y_exp;
   sscanf(date,"%2d%2d%4d",&d,&m,&y);
   sscanf(expiry,"%2d%2d%4d",&d_exp,&m_exp,&y_exp);
//   printf("%s %d %d %d\n",date, d,m,y);
//   printf("%s %d %d %d\n",expiry, d_exp,m_exp,y_exp);
   if (y_exp > y) {
	   goed = 1;
   } else if (y_exp == y) {
       if (m_exp > m) {
		   goed = 1;
	   } else if (m_exp == m) {
		   if (d_exp >= d) goed = 1;
	   }
   }

   return ( goed );

}


/* lmfManage - routine di gestione delle licenze                 */

int LMFMANAGE(void)

{

  int c, i,goed,goed2,gopass;
  FILE *fp;
  char tmp_str[100];
  
  
  serialN[20]='\0';
  buff[20]='\0';
  buff1[20]='\0';

  strcpy(tmp_str,getenv("LG_LEGO"));
  strcat(tmp_str,"\\lmf.dat");
  
  if ( (fp=fopen(tmp_str,"r")) == NULL) {
     MessageBox( NULL, "Impossible to find license file", "Error", MB_OK|MB_ICONINFORMATION );
     return(1);
  }
  
  i=0;
  while ( (c=fgetc(fp)) != EOF && i<20 )
        serialN[i++]=(char)c;

  if ( c==EOF && i<20) {
     MessageBox( NULL, "Wrong license S/N", "Error", MB_OK|MB_ICONINFORMATION );
     return(1);
  }
  
  gopass=1;
  for(i=0;i<12;i++)
	  if (serialN[i] != snpass[i]) gopass=0; 
  if(gopass == 1) {
    	sprintf(buffone,"serialN=%s -- snpass=%s",serialN,snpass);
//  	MessageBox( NULL, buffone, "Error", MB_OK|MB_ICONINFORMATION );
     	return (0);
     	}
  
  ethernet(buff);
  unshuffle();
  gettime();
  
  goed=1;  
  for(i=0;i<12;i++)
	  if (buff[i] != buff1[i]) goed=0;

  if ( goed ) {
	 goed2=DateManage(buff+12,buff1+12);
	 if ( goed2	) {
	    return(0);
	 } else {
        MessageBox( NULL, "Expired license", "Error", MB_OK|MB_ICONINFORMATION );
		return(1);
     }
  }  else  {
     MessageBox( NULL, "Wrong license S/N", "Error", MB_OK|MB_ICONINFORMATION );
     return(1);
  }
  
}
