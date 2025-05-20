


#ifndef _net_compi_h_
#define _net_compi_h_

extern void testata(char *, char *);
void crea_variabili (char**, VARIABILI **, int*, int);
void co_snap();
void check_dt(MODEL [],int ,int *);
void read_f04_write_s04(VARLEGO *,int,MODEL[]);
int leggi_record_ftn( int , int , int , char , int , ...);
void check_input(char *,int ,int *,VARLEGO *,MODEL []);
void check_output(char *,int ,int *,VARLEGO *,MODEL []);
void check_model(char *,int ,int *,MODEL [],int );
void read_n04_write_s04(VARLEGO *,int,MODEL []);
void legge_riga_n04(char*,int*);
//void separa_str( char riga[], int lun, int nstr, STRIN_ST strin[]);
void tabelle_net(int ,int );


#endif