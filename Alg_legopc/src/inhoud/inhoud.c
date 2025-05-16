/**************************************************************

 inhoud.c   v. 1.0


 description:
 The goal of this utility is to insert a .tom in the current one.
 The program receives two arguments: a modelname and a letter 
 identifying a direction (N/S/W/E).
 It produces a new .tom in the current model including the specified
 one.
 Convention: I=inserting model; i=inserted model
 
 **************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


#define MARG 100
#define MAX_DIM_MODELS 800

struct oldnew {
	char oldname[5];
	int index;
};

int  exists(char line[], char block[][5],int nitems,int *ind);
char *calculate_new_name(char c[],char block[][5],
						 struct oldnew newnames[],int nnames);

int main (int argc, char **argv)

{

int   DIM_X_I, DIM_Y_I, DIM_X_i, DIM_Y_i;
int   DNEW_X, DNEW_Y;
int   iblock=0;
int   inewnames=0;
int   index, i;
int   counter=1;

char  Imodel[100], imodel[100];
char  direction;
char  line[81];
char  block[2*MAX_DIM_MODELS][5];
char  a[5], b[6], c[5];

float XMAX_i, YMAX_i, XMAX_I, YMAX_I;
float DX_I, DY_I, DX_i, DY_i;
float x,y;

FILE *ifile, *Ifile, *newfile, *outfile;

struct oldnew newnames[MAX_DIM_MODELS];

/* decoding arguments imodel and direction */

  if (argc != 4) {
  	printf("Usage: inhoud Imodel imodel direction");
  	return(1);
  }

  strcpy(Imodel,argv[1]);
  strcat(Imodel,".tom");
  
  sprintf(imodel,"..\/%s\/%s.tom",argv[2],argv[2]);

  direction=toupper(argv[3][0]);
  if (direction != 'N' && direction != 'S' &&
	  direction != 'E' && direction != 'W') {
  		printf("Direction can be only N/S/W/E");
  		return(1);
  }

/* reading max insertion coordinates from the two files
              XMAX_I YMAX_I XMAX_i YMAX_i
   and drawing dimensions
              DIM_X_I DIM_Y_I DIM_X_i DIM_Y_i */

  if ((Ifile = fopen(Imodel, "r")) == NULL) {
    printf("%s doesn't exist",Imodel);
    return(1);
  } else {

    XMAX_I=0.0;
    YMAX_I=0.0;

    fgets(line,80,Ifile);

    fgets(line,80,Ifile);
    sscanf(line,"%d %d",&DIM_X_I,&DIM_Y_I);

    fgets(line,80,Ifile);
    while (strncmp(line,"****",4)) {
       fgets(line,80,Ifile);
       fgets(line,80,Ifile);

       fgets(line,80,Ifile);
       sscanf(line,"%f %f",&x,&y);
       if (x > XMAX_I) XMAX_I=x;
       if (y > YMAX_I) YMAX_I=y;

       fgets(line,80,Ifile);
       fgets(line,80,Ifile);
    }
  }

  if ((ifile = fopen(imodel, "r")) == NULL) {
    printf("%s doesn't exist",imodel);
    return(1);
  } else {
  
    XMAX_i=0.0;
    YMAX_i=0.0;
    
    fgets(line,80,ifile);
    
    fgets(line,80,ifile);
    sscanf(line,"%d %d",&DIM_X_i,&DIM_Y_i);
        
    fgets(line,80,ifile);
    while (strncmp(line,"****",4)) {
       fgets(line,80,ifile);    
       fgets(line,80,ifile);
       
       fgets(line,80,ifile);
       sscanf(line,"%f %f",&x,&y);
       if (x > XMAX_i) XMAX_i=x;
       if (y > YMAX_i) YMAX_i=y;
 
       fgets(line,80,ifile);    
       fgets(line,80,ifile); 
    }
  }
              
/* calculating new drawing dimensions DNEW_X DNEW_Y and
   insertion points displacements DX_I DY_I DX_i DY_i */
    
   switch (direction) {
      case 'N':
         DNEW_X=(int)fmax((double)DIM_X_i,(double)DIM_X_I);
         DNEW_Y=(int)(YMAX_I+0.5)+(int)(YMAX_i+0.5)+2*MARG;
         DX_I=0;
         DY_I=YMAX_i+MARG;
         DX_i=0;
         DY_i=0;
         break;
      case 'S':
         DNEW_X=(int)fmax((double)DIM_X_i,(double)DIM_X_I);
         DNEW_Y=(int)(YMAX_I+0.5)+(int)(YMAX_i+0.5)+2*MARG;
         DX_I=0;
         DY_I=0;
         DX_i=0;
         DY_i=YMAX_I+MARG;
         break;
      case 'W':
         DNEW_X=(int)(XMAX_I+0.5)+(int)(XMAX_i+0.5)+2*MARG;
         DNEW_Y=(int)fmax((double)DIM_Y_i,(double)DIM_Y_I);
         DX_I=XMAX_i+MARG;
         DY_I=0;
         DX_i=0;
         DY_i=0;
         break;
      case 'E':
         DNEW_X=(int)(XMAX_I+0.5)+(int)(XMAX_i+0.5)+2*MARG;
         DNEW_Y=(int)fmax((double)DIM_Y_i,(double)DIM_Y_I);
         DX_I=0;
         DY_I=0;
         DX_i=XMAX_I+MARG;
         DY_i=0;         
         break;
   }
   
/* reading the two files .tom and creating new one */

   if ((newfile = fopen("inhoud.tom", "w")) == NULL) {
      printf("Can't open new file for writing");
      return(1);
   } else {
      rewind(Ifile);
     
      fgets(line,80,Ifile);
      fputs(line,newfile);
     
      fgets(line,80,Ifile);
      sprintf(line,"%d %d\n",DNEW_X,DNEW_Y);
      fputs(line,newfile);
     
      fgets(line,80,Ifile);
      while (strncmp(line,"****",4)) {
        fputs(line,newfile);
        fgets(line,80,Ifile);
           
        fputs(line,newfile);
        fgets(line,80,Ifile);
       
        sscanf(line,"%s",block[iblock++]);
        fputs(line,newfile);
        fgets(line,80,Ifile);

        sscanf(line,"%f %f",&x,&y);
        sprintf(line,"%f %f\n",x+DX_I,y+DY_I);
        fputs(line,newfile);
        fgets(line,80,Ifile);
 
        fputs(line,newfile);    
        fgets(line,80,Ifile); 
      } 
  
      rewind(ifile);
      fgets(line,80,ifile);
      fgets(line,80,ifile);
      
      fgets(line,80,ifile);
      while (strncmp(line,"****",4)) {
        fputs(line,newfile);
        fgets(line,80,ifile);
          
        fputs(line,newfile);
        fgets(line,80,ifile);
 
		strcpy(newnames[inewnames].oldname,line);
        while (exists(line,block,iblock,&index)) {
           switch (line[3]) {
              case '0':
                 line[3]='1';
                 break;
              case '1':
                 line[3]='2';
                 break;
              case '2':
                 line[3]='3';
                 break;
              case '3':
                 line[3]='4';
                 break;
              case '4':
                 line[3]='5';
                 break;
              case '5':
                 line[3]='6';
                 break;
              case '6':
                 line[3]='7';
                 break;
              case '7':
                 line[3]='8';
                 break;
              case '8':
                 line[3]='9';
                 break;
              case '9':
                 line[3]='$';
				 break;
              case '$':
                 line[3]='?';
                 break;
              case '?':
                 line[3]='!';
				 break;
              case '!':
                 printf("Sorry, no symbols more left");
				 return(2);
				 break;
			  default:
				 line[3]='0';
				 break;
           }
        }
		newnames[inewnames++].index=iblock;
        sscanf(line,"%s",block[iblock++]);
        fputs(line,newfile);
        fgets(line,80,ifile);
      
        sscanf(line,"%f %f",&x,&y);
        sprintf(line,"%f %f\n",x+DX_i,y+DY_i);
        fputs(line,newfile);
        fgets(line,80,ifile);
        fputs(line,newfile);    
        fgets(line,80,ifile);
       }
       
       fputs("****\n",newfile);

       fgets(line,80,Ifile);
       while(! feof(Ifile) && strncmp(line,"****",4)) {
          fputs(line,newfile);
		  fgets(line,80,Ifile);
       }   
       fclose(Ifile);
 
	   fgets(line,80,ifile);
       while(! feof(ifile) && strncmp(line,"****",4)) {
		  if (!strncmp(line,"busy",4)) {
			  sscanf(line,"%s %s %s",&a,&b,&c);
			  strcpy(c,calculate_new_name(c,block,newnames,inewnames));
			  sprintf(line,"%s %s %s\n",a,b,c);
		  } else if (counter == 2) {
			  sscanf(line,"%s",&c);
			  strcpy(c,calculate_new_name(c,block,newnames,inewnames));
			  sprintf(line,"%s\n",c);
		  }
		  fputs(line,newfile);
		  fgets(line,80,ifile);
		  if (!strncmp(line,"++++",4)) {
			  counter=0;
		  } else {
			  counter++;
		  }
       }   
       fclose(ifile);
       
	   fputs("****\n",newfile);
       fclose(newfile);

   }

/* writing on file changed.out the modified blocknames */    

  if ((outfile = fopen("changed.out", "w")) == NULL) {
     printf("Can't open file changed.out");
	 return(1);
  } else {
	 fprintf(outfile,"OLDNAME NEWNAME\n======= =======\n");
	 for (i=0;i<inewnames;i++) {
	    if (strncmp(newnames[i].oldname,block[newnames[i].index],4)) {
		 fprintf(outfile,"%s        %s\n",newnames[i].oldname,
                                          block[newnames[i].index]);
		}
     }
	 fclose(outfile);
  }
 

   return(0);

}

/*********************************************************/

int exists(char line[], char block[][5],int nitems,int *ind) {

   int i;
   int found=0;

   for(i=0;i<nitems;i++) {
      if (strncmp(line,block[i],4) == 0) {
         found=1;
         break;
      }      
   }
   *ind=i;
   return(found);
}

/*********************************************************/

char *calculate_new_name(char c[],char block[][5],
						 struct oldnew newnames[],int nnames)  {

	int i;
	int found=0;

    for(i=0;i<nnames;i++) {
       if (strncmp(c,newnames[i].oldname,4) == 0) {
		   found=1;
		   break;
	   }
	}
	if (!found) {
		printf("Inserted model contains ties to nonexisting blocks");
		exit(1);
	} else {
		return(block[newnames[i].index]);
	}
}
