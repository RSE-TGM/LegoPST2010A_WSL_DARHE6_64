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
   InvioGdc
      routine che invia la stringa ricevuta al
      gestore di chiamate
      Attende il messaggio di risposta e verifica eventuali malfunziona-
      menti.

   Parametri

      char* messaggio da inviare gia' nel formato del
            protocollo

   Ritorno

      =0 se tutto ok
      =1 problemi di comunicazione impossibile inviare messaggio
         ( richiedere un reset dell'apparecchio)

*/
#include "repgdc.h"
//
//   structtura scambio dati fra routine risposta ad interrupt
//   e routine interpretazione messaggio
//
extern struct dati_507
      {
        short StPort;    //   Indirizzo Status Register del canale
        short DtPort;    //   Indirizzo Data   Register del canale
        long nTx;      //   Counter byte da trasmettere
        char * TxBuff;  //   Indirizzo del buffer da trasmettere
        long nRx;      //   N. byte da ricevere
        long nMaxRx;    //   n: massimo caratteri da ricevere
        char *RxBuff;   //   Indirizzo del buffer in ricezione
      } struct_507D;

GDC_RPL  BRx;           //   buffer utilizzato per ricezione messaggi da GDC

#include "g1tipdb.inc"
#include "g2comdb.inc"

short InvioGdc(char* mess)
{
   short retry;
   short status;

   retry=retry_Gdc;

   do
   {
      struct_507D.nRx=0;
      RepSend(linea_Gdc,strlen(mess),mess);
      _disable();
      if(!struct_507D.nRx || (*(struct_507D.RxBuff+struct_507D.nRx-1)!=0x0A))
      {
        if(suw(trisp_Gdc))
        {
            _enable();
            return 1;              // time out ricezione risposta
         }
      }
      else _enable();            
//
//    arrivato Risposta Status: verifico che il comando sia stato
//    accettato, in caso contrario ritento per 3 volte
//    
      status=CodStatGdc(&BRx.hea.statA1[0])*16+CodStatGdc(&BRx.hea.statA1[1]);
      GdcDia(status);
      if(!(status & gdc_mCMD))
      {
         retry=0;
         return 0;
      }
      else
      {
         dbadv[gdc_aERCMD]= (status & gdc_mER) >>6;
         retry --;
      }
   }
   while (retry);
   return 1;
}
/*
   IniGdc
      inizializza le aree di comunicazione per routine di risposta
      ad interrupt
*/
IniGdc()
{
   struct_507D.RxBuff=(char*) &BRx;
   struct_507D.nMaxRx=max_BRx;
   dbadv[gdc_aERCMD]= -1;              // ultimo errore =0
}
/*
   InterpGdc
      Dato il messaggio estrae i campi

   Parametri
      char** pcampi vettore di indirizzi ai vari campi che compongono il
             messaggio

   Ritorno
      int o short contenente la codifica dello stato
*/
InterpGdc(char ** pcampi)
{
   char* pbyte, *ptoken;
   short i;
   short iCar;

   pbyte=&BRx.statL;     // stato della linea
   ptoken=pbyte;
   iCar=struct_507D.nRx-sizeof(GDC_RPL_HEA);     // n. caratteri che compongono il messaggio
   
   for(i=0;i<n_campi;i++) pcampi[i]=0;           // default campo non esistente
   for(i=0;i<n_campi && iCar && ((*pbyte)!= eom2_Gdc);i++)
   {
      while(((*pbyte) != eom1_Gdc) && ((*pbyte) != sep_Gdc) && iCar)
      {
         pbyte++;
         iCar--;
      }
      if(pbyte-ptoken)
      {
         pcampi[i]=ptoken;    // individuato un token
         *pbyte=0;
         iCar--;
      }
      pbyte++;
      ptoken=pbyte;
   }
   if(pcampi[0])
   {
         return(CodStatGdc(pcampi[0])*16 + CodStatGdc(pcampi[0]+1));
   }
   return (-1);
}
/*
   CodStatGdc
      La routine dato un byte in ASCII lo trasforma in intero

   Parametri
      char * dato da tradurre

   Ritorno
      valore intero tradotto

*/
CodStatGdc(char * dato)
{
   if(*dato > 0x40)
      return((*dato)-0x37);     // lettera A, B...F
   else return((*dato)=(*dato)-0x30); // numero 0, 1, ....9
}
