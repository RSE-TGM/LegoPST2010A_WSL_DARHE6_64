/**********************************************************************
*
*       C Header:               aing_def.h
*       Subsystem:              1
*       Description:
*       %created_by:    mauric %
*       %date_created:  Thu Dec 19 17:43:13 1996 %
*
**********************************************************************/
/***
      aing_def.h

      definizioni per finestra Aing

***/

typedef struct menu_aing_st {
                        char *descrizione;
                        Boolean _campo_1;
                        char *descr_1;
                        Boolean _campo_2;
                        char *descr_2;
                        Boolean _campo_3;
                        char *descr_3;
                        Boolean _campo_4;
                        char *descr_4;
                        Boolean _campo_5;
                        char *descr_5;
                        Boolean _campo_6;
                        char *descr_6;
                        Boolean _campo_7;
                        char *descr_7;
                        Boolean _Start;
                        Boolean _Stop;
                        } S_MENU_AING;

static S_MENU_AING menu_aing[]={
{"Not: ",False,"",False,"",False,"",False,"",False,"",False,"",
        False,"",True,False},
{"Step: ",True,"Target: ",False,"",False,"",False,"",False,"",False,"",
        False,"",True,False},
{"Pulse: ",True,"Target: ",True,"Wide: ",False,"",False,"",
        False,"",False,"",False,"",True,True},
{"Ramp/Grad: ",True,"Target: ",True,"Grad.: ",False,"",False,"",
                False,"",False,"",False,"",True,True},
{"Ramp/Delta: ",True,"Target: ",True,"Delta: ",False,"",False,"",
        False,"",False,"",False,"",True,True},
{"Ramp/At: ",True,"Target: ",True,"At: ",False,"",False,"",False,"",False,"",
        False,"",True,True},
{"Sinusoidal: ",True,"Period: ",True,"Mean Value: ",True,"Wide: ",
        True,"Phase: ",False,"",False,"",False,"",True,True},
{"Periodic: ",True,"Period: ",True,"Mean Value: ",True,"Wide: ",True,"Phase: ",
        True,"T1: ",True,"T2: ",True,"T3: ",True,True},
{"White Noise: ",True,"Variance : ",True,"Mean Value: ",False,"",False,"",
        False,"",False,"",False,"",True,True},
{"Malfunction: ",True,"Target : ",True,"Type: ",False,"",False,"",
        False,"",False,"",False,"",True,True}
                };

#define NUM_MENU_AING   10

