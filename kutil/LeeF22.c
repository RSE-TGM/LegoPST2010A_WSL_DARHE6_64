#include <stdio.h>
#include <sys/fcntl.h>
#define	VERDAD 1;
struct fecha {
	int	hh;
	int	mm;
	int	ss;
	int	dd;
	int	mes;
	int	yy;
};
int	fd;
FILE	*fd2;
FILE	*fd3;

int	nb;
int	hora,minuto;
float	segundo;
char	kks[80];
char	kks_aux[80];
char	linea[132];
short	test[10000];
float	multiplicador[10000], sumador[10000];
int	muestra;
int cont;
int var_no;

main()
{
	struct fecha fecha;
float tiempo;
float pp2;
int	donde;
int i=0;
char	buf_aux2[04154];
char	buffer[6004];
char	fl_aux[4];
int	start_reg,reg_no,max_size;
int	i0;
int	pp;

	/* Abro fichero de output */
	if((fd2 = fopen("LeeF22.out","w")) == NULL ) {
                printf("Incapaz de abrir fichero de salida LeeF22.out\n");
                exit(0); 
	} else { 
		printf(" Abierto fichero de salida LeeF22.out \n");
	}

	/* Lectura del tiempo de muestreo */
	/* Apertura del fichero que contiene el nombre de
	   las variables que seran monitorizadas */
	if((fd3 = fopen("LeeF22.in", "r")) == NULL) {
               	printf("Incapaz de abrir fichero de input LeeF22.in\n");
		exit();
	}


	/* Lectura de la primera linea, donde se incluye la
	   frecuencia de muestreo. Pasa de los comentarios */
	while(fgets(linea, 131, fd3) != NULL) {
		if(linea[0] != '#') {       /* si no es comentario */
			sscanf(linea,"%d%*[^\n]\n",&muestra);
			break;
		}
	}

	fclose(fd3);

	if(muestra == 0) {

/************************************************************/
/* Si se quiere atacar al fichero de datos de la simulacion */
/* cambiar la apertura del fichero, incluyendo el path      */
/* completo. Es decir,                                      */
/* if((fd = open("/usr/users/igccr1/sked/igcc_1/f22circ.dat */
/************************************************************/
	/* Abro fichero de input */
	if((fd = open("f22circ.dat", O_RDONLY|O_SYNC)) < 0) {
		printf("Incapaz de abrir fichero de graficacion f22circ.dat\n");
		exit();
        }

	/* MORRALLA DEL COMIENZO */
	if((nb = read(fd, buf_aux2 , sizeof(buf_aux2))) != sizeof(buf_aux2)) {
		printf("001 Leidos  %d de %d bytes\n", nb, sizeof(buf_aux2));
                        exit();
        }

	/* DATOS DE TAMANO DE LECTURA */
	if((nb = read(fd, buffer , 16)) != 16) {
		printf("Problemas en la lectura de datos iniciales\n");
                        exit();
        }

	memcpy(&start_reg,buffer,4);
	memcpy(&reg_no,buffer+4,4);
	memcpy(&max_size,buffer+8,4); 
	memcpy(&var_no,buffer+12,4); 

	/* Comentarios relacionados con el fichero de input */
/****************************************************************/
/*	printf("\n\tComienza en el registro %d \n",start_reg);	*/
/*	printf("\tGrabados %d \n",reg_no);			*/
/*	printf("\tNumero maximo de registros %d \n",max_size);	*/
/*	printf("\tNumero de variables %d \n",var_no);		*/
/****************************************************************/

	/* Lectura de la fecha de grabacion */
	if((nb = read(fd, (char *)&fecha , sizeof(fecha))) != sizeof(fecha)) { 
		printf("Problemas en la lectura de la fecha de grabacion\n");
                exit();
        }
	/* Comentarios relacionados con la fecha de grabacion  */
/****************************************************************/
/*	printf(" %d/%d/%d %d:%d:%d\n",fecha.dd,fecha.mes,	*/
/*		fecha.yy,fecha.hh,fecha.mm,fecha.ss);		*/
/****************************************************************/

		 
	/* Escritura de los nombres de las variables */
	Escribe_nombre();

	/* Vamos a por los valores */
		/* Leo el tiempo de simulacion */
		for(i=0;i<max_size;i++) {
			if((nb = read(fd, fl_aux , sizeof(fl_aux))) != sizeof(fl_aux)) {
				printf("004 %d Leidos  %d de %d bytes\n", i,nb, sizeof(fl_aux));
				max_size=i;
				break;
       	         	}

			memcpy(&tiempo,fl_aux,4);
			hora = (int)tiempo/3600;
			minuto = (int)((tiempo-hora*3600)/60);
			segundo = tiempo - ((hora*3600) + (minuto*60));

			/* Escribo el tiempo de simulacion */
			if(segundo<10)
				fprintf(fd2,"%2.2d:%2.2d:%.1f  ",hora,minuto,segundo);
			else
				fprintf(fd2,"%2.2d:%2.2d:%.1f ",hora,minuto,segundo);
	
			/* Leo los valores de las variables */
			for(pp=0;pp<var_no;pp++) {
				if((nb = read(fd, fl_aux , sizeof(fl_aux))) != sizeof(fl_aux)) {
					printf("Problemas en la lectura de los valores de las variables \n");
       			            	exit();
       			       	}

				memcpy(&pp2,fl_aux,4);

				/* Las escribo aplicando mult y sum */
				if(test[pp]) {
					fprintf(fd2,"%22.3f ",(pp2*multiplicador[pp])+sumador[pp]);
				}
			}

		fprintf(fd2,"\n");
		}

		close(fd);
	} else {	/* Escritura del ultimo valor */
	for(;;){
/************************************************************/
/* Si se quiere atacar al fichero de datos de la simulacion */
/* cambiar la apertura del fichero, incluyendo el path      */
/* completo. Es decir,                                      */
/* if((fd = open("/usr/users/igccr1/sked/igcc_1/f22circ.dat */
/************************************************************/
	/* Abro fichero de input */
	if((fd = open("f22circ.dat", O_RDONLY|O_SYNC)) < 0) {
		printf("Incapaz de abrir fichero de graficacion f22circ.dat\n");
		exit();
        }

	/* MORRALLA DEL COMIENZO */
	if((nb = read(fd, buf_aux2 , sizeof(buf_aux2))) != sizeof(buf_aux2)) {
		printf("001 Leidos  %d de %d bytes\n", nb, sizeof(buf_aux2));
                        exit();
        }

	/* DATOS DE TAMANO DE LECTURA */
	if((nb = read(fd, buffer , 16)) != 16) {
		printf("Problemas en la lectura de datos iniciales\n");
                        exit();
        }

	memcpy(&start_reg,buffer,4);
	memcpy(&reg_no,buffer+4,4);
	memcpy(&max_size,buffer+8,4); 
	memcpy(&var_no,buffer+12,4); 

	/* Comentarios relacionados con el fichero de input */
/****************************************************************/
/*	printf("\n\tComienza en el registro %d \n",start_reg);	*/
/*	printf("\tGrabados %d \n",reg_no);			*/
/*	printf("\tNumero maximo de registros %d \n",max_size);	*/
/*	printf("\tNumero de variables %d \n",var_no);		*/
/****************************************************************/

	/* Lectura de la fecha de grabacion */
	if((nb = read(fd, (char *)&fecha , sizeof(fecha))) != sizeof(fecha)) { 
		printf("Problemas en la lectura de la fecha de grabacion\n");
                exit();
        }
	/* Comentarios relacionados con la fecha de grabacion  */
/****************************************************************/
/*	printf(" %d/%d/%d %d:%d:%d\n",fecha.dd,fecha.mes,	*/
/*		fecha.yy,fecha.hh,fecha.mm,fecha.ss);		*/
/****************************************************************/

		 
	/* Escritura de los nombres de las variables */
	Escribe_nombre();

		/* Salto del tiempo anterior */
		lseek(fd,(sizeof(float)*(var_no+1)*reg_no),SEEK_CUR);

		/* Leo el tiempo de simulacion */
		if((nb = read(fd, fl_aux , sizeof(fl_aux))) != sizeof(fl_aux)) {
			printf("004 %d Leidos  %d de %d bytes\n", i,nb, sizeof(fl_aux));
			max_size=i;
                }

		memcpy(&tiempo,fl_aux,4);
		hora = (int)tiempo/3600;
		minuto = (int)((tiempo-hora*3600)/60);
		segundo = tiempo - ((hora*3600) + (minuto*60));
		
		printf(" LeeF22  %2.2d:%2.2d:%.1f\n",hora,minuto,segundo);

		/* Escribo el tiempo de simulacion */
		if(segundo<10)
			fprintf(fd2,"%2.2d:%2.2d:%.1f  ",hora,minuto,segundo);
		else
			fprintf(fd2,"%2.2d:%2.2d:%.1f ",hora,minuto,segundo);

		for(pp=0;pp<var_no;pp++) {
			if((nb = read(fd, fl_aux , sizeof(fl_aux))) != sizeof(fl_aux)) {
				printf("006 Leidos  %d de %d bytes\n", nb, sizeof(fl_aux));
       	               	  exit();
       	       		}
			memcpy(&pp2,fl_aux,4);
			if(test[pp]) {
				fprintf(fd2,"%22.3f ",(pp2*multiplicador[pp])+sumador[pp]);
			}
		}
	rewind(fd2);
	close(fd);
	sleep(muestra);
	}
	}

	fclose(fd2);


}

/************************************************************/
/* Rutina para la escritura de los nombres de las variables */
/************************************************************/
Escribe_nombre()
{
	/* Escribo los nombres de las variables */

	fprintf(fd2,"TIEMPOS     ");

	for(cont=0;cont<var_no;cont++){

		/* Leo el nombre de la variable */
		if((nb = read(fd, kks , sizeof(kks))) != sizeof(kks)) {
			printf("Problemas en la lectura del nombre de la variable %d\n",cont);
                       	 exit();
        	}

		/* Apertura del fichero que contiene el nombre de
		   las variables que seran monitorizadas */
		if((fd3 = fopen("LeeF22.in", "r")) == NULL) {
                	printf("Incapaz de abrir fichero de input LeeF22.in\n");
			exit();
		}


		/* Lectura de la primera linea, donde se incluye la
		   frecuencia de muestreo. Pasa de los comentarios */
		while(fgets(linea, 131, fd3) != NULL) {
			if(linea[0] != '#') {       /* si no es comentario */
				sscanf(linea,"%d%*[^\n]\n",&muestra);
				break;
			}
		}

		
		/* Esta presente la variable en el input ? */
		while(fgets(linea, 131, fd3) != NULL) {
			if(linea[0] != '#') {       /* si no es comentario */
				sscanf(linea, "%s %f %f%*[^\n]\n", kks_aux, &multiplicador[cont], &sumador[cont]);
               			if (!strncmp(kks_aux,kks+30,strlen(kks_aux))) {
					/* Esta presente */
					test[cont] = VERDAD;
					/*fprintf(fd2,"%21.21s  ",kks+30);*/
					if(!strncmp(kks_aux,"@#K@",4))
						fprintf(fd2,"%21.21s  ",kks_aux+4);
					else
						fprintf(fd2,"%21.21s  ",kks_aux);
					break;
               		 	}
			}
		}

		fclose(fd3);

	}
		fprintf(fd2,"\n");
}
