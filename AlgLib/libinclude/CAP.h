/*@(#)cap.h	Include per Controllo Accessi Programma	1997-03-21	*/

# ifndef CAP_H
# define CAP_H

/*----------------------------------------------------------------------*/
/*	Define								*/

#define	OK		0
#define	NOK		(-1)
#define	LF		0x0a

# define ENELINFOINI "Stringa di autorizzazione "

# define INPUT_STR      ">>"
# define OUTPUT_STR     "<<"
# define ELAB_STR       "@@"

#define  IND_RETE_CRA   "AC1B76"	/* 172.27.118....... */ 
#define  DEF_CRA_RT     "full-99999"	/* Default per macchine enel e 
                                           applicativi runtime          */ 
#define  DEF_CRA_NORT   "full"		/* Default per macchine enel e 
                                           applicativi non runtime      */ 
#define  CONFIG_LIC     "algcf"	
#define  LEGOCAD_LIC    "alglc"
#define  SCADA_LIC      "algsc"
#define  SCHED_LIC      "algrt"
#define  MMI_LIC        "algmm"


#define		PLAINTEXT_MAX	100


/*----------------------------------------------------------------------*/
/*	Variabili Globali						*/


extern unsigned int Debug ;
extern char * CAPdirname ;
extern char * Demo ;
extern char CAPINFO_FN [ ] ;
extern char CAPCONF_FN [ ] ;

/*----------------------------------------------------------------------*/
/*	Prototypes							*/

extern int	AZencode ( unsigned char * , unsigned char * * ) ;
extern int	AZdecode ( unsigned char * , unsigned char * * ) ;
extern void	decode( unsigned char* , int );
extern void	encode( unsigned char* , int );
extern int	InitEnv ( void ) ;
extern void	PrintVersion ( void ) ;

# include <sys/utsname.h>


# define SYSNAME_LEN	4
# define MACHINE_LEN	12

#if defined (OSF1_40)
# define ADDRESS_LEN	12
#elif defined (LINUX)
# define ADDRESS_LEN	12
#elif defined (NUTC)
# define ADDRESS_LEN	12
#else
# define ADDRESS_LEN    8
#endif

# define PROGRAMID_LEN	5
# define ENELINFO_LEN	10


struct CAPinfo {
  
  char SysName [ SYSNAME_LEN ] ;
  char Machine [ MACHINE_LEN ] ;
  char Address [ ADDRESS_LEN ] ;
  char ProgramID [ PROGRAMID_LEN ] ;
  char EnelInfo [ ENELINFO_LEN ] ;
  char nil ;

} ;

# define CAPSTRC_SZ	sizeof(struct CAPinfo)
# define CAPINFO_SZ	(CAPSTRC_SZ - 1)

/*###############################################################*/
/* Define e strutture per gestire il recupero delle informazioni */
/* contenute in CAP.info per le licenze presenti a Puertollano   */
/* (basate su indirizzo IP).                                     */
/*###############################################################*/

/* Numero di byte costituenti l'indirizzo IP */ 
# define ADDRESS_LEN_IP 8

struct CAPinfo_IP {  
  char SysName [ SYSNAME_LEN ] ;
  char Machine [ MACHINE_LEN ] ;
  char Address [ ADDRESS_LEN_IP ] ;
  char ProgramID [ PROGRAMID_LEN ] ;
  char EnelInfo [ ENELINFO_LEN ] ;
  char nil ;

} ;

/* Dimensione della struttura CAP_info_IP */ 
# define CAPINFO_IP_SZ  (sizeof(struct CAPinfo_IP) - 1) 


/*################################################################*/

extern int cap_info ( struct CAPinfo * ) ;

extern int CAP ( char * , char * ) ;

extern int manageLicense(char *, char *, int *, double *);

extern int manageLicenseNoTime(char *, char *, int *);

extern int getTimeLicense(double *);

extern int setTimeLicense(int, double *);

# endif /* CAP_H */
