#include <stdio.h>
#include <string.h>

main(int argc,char *argv[])
{

int i;
char *s=argv[1];
i=strlen(s);
for(;i>=0;)
        {
        if(s[--i]==' ')
                s[i]='\0';
        else
                break;
        }
printf("[%s]\n",s);
}


