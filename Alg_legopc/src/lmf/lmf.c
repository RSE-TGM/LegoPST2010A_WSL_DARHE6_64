#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define INTERACTIVE 1

char buff[21];
char buff1[21];
char serialN[21];

void ethernet(char *);

void shuffle() 
{
	int  i,j;
	char ch;

	for (i=0;i<20;i++) {
		ch=buff[i];
		for (j=0;j<i;j++) {
			if (ch == '9') {
				ch = '0';
			} else if (ch == 'Z') {
				ch = 'A';
			} else if ((ch >= 'A' && ch < 'Z') || 
					   (ch >= '0' && ch < '9'))  {
				++ch;
			} else {
				printf("Codice errato!\n");
			}
		}
		serialN[i]=ch;
	}
	serialN[20] = '\0';

        for (i=0;i<10;i+=2) {
		ch = serialN[i];
		serialN[i] = serialN[19-i];
		serialN[19-i] = ch;
        }

        for (i=0;i<20;i++) {
	    ch=serialN[i];
	    for (j=0;j<i;j++) {
		 if (ch == '9') {
			ch = '0';
		 } else if (ch == 'Z') {
			ch = 'A';
		 } else if ((ch >= 'A' && ch < 'Z') || 
			    (ch >= '0' && ch < '9'))  {
			++ch;
		 } else {
			printf("Codice errato!\n");
		 }
	    }
	    serialN[i]=ch;
       }

       for (i=0;i<20;i+=2) {
	    ch = serialN[i];
	    serialN[i] = serialN[i+1];
	    serialN[i+1] = ch;
       }	

}

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

void gettime(void)
{

//	char tmp_string[100];
	time_t timer;
	struct tm *act_time;

	timer = time(&timer);
	act_time = localtime(&timer);
 
//	sprintf(tmp_string,"%02d/%02d/%04d %02d:%02d:%02d\n", 
//		act_time->tm_mday,
//		(act_time->tm_mon + 1),
//		act_time->tm_year + 1900,
//		act_time->tm_hour,
//		act_time->tm_min,
//		act_time->tm_sec);
//	printf("Time: %s",tmp_string);
	sprintf(buff+12,"%02d%02d%04d",
		    act_time->tm_mday,
			(act_time->tm_mon + 1),
			act_time->tm_year + 1900);
	printf("Actual ethernet+date is: %s\n",buff);


}

void main(void) 
{

    int c,i,buono;
    

    if (INTERACTIVE == 0) {
        ethernet(buff);
	gettime();
   } else {
        buono=0;
        while (!buono) {
   	   printf("Ethernet number (12 uppercase chars): ");
   	   c=getchar();
   	   i = 0;
   	   while (i<12) {
   	      if (c != ' ') {
   	         buff[i++]=c; 
   	         c=getchar();
   	      }
   	   }
   	   if (i == 12) buono=1;
   	}  
   	buff[12]='\0';
   	printf("The Ethernet number is: %s\n",buff);
   	
   	buono=0;
        while (!buono) {
   	   printf("Expiry date (ggmmaaaa): ");
   	   c=getchar();
   	   i = 12;
   	   while (i<20) {
   	      if (c != ' ') {
   	         buff[i++]=c; 
   	         c=getchar();
   	      }
   	   }
   	   if (i == 20) buono=1;
   	}  
   	buff[20]='\0';
   	printf("Actual ethernet+date is: %s\n",buff);
   }
   
   shuffle();
   printf("Serial number is: %s\n",serialN);

   unshuffle();
   printf("Reconstructed ethernet+date number is: %s\n",buff1);

}
