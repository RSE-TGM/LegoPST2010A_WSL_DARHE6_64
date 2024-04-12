/**********************************************************************
*
*       C Header:               unita.h
*       Subsystem:              1
*       Description:
*       %created_by:    famgr %
*       %date_created:  Wed Apr 10 12:07:28 1996 %
*
**********************************************************************/
/* file unita.h */

/* strutture utilizzate per le unita' di misura */
#ifndef UNITA_H
#define UNITA_H
#define FILE_UNITA_MISURA	"unimis_doc.dat"

typedef struct {
                    char codice[7];
                    float moltip, sommat;
               }  DimensioneUnita;

typedef struct {
                    char nome_tipo[9], tipo;
                    short ind_selez;
                    DimensioneUnita dim[5];
               } UnitaMisura;

typedef struct {
                  char nome_tipo[9];
                  short ind_selez;
               } RecordUmis;

#endif
/* fine unita.h */
