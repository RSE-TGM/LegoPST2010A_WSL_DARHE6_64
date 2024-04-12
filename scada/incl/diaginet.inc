/**********************************************************************
*
*       C Header:               %name%
*       Subsystem:              %subsystem%
*       Description:
*       %created_by:    %
*       %date_created:  %
*
**********************************************************************/
/*
        file punti di diagnostica in caso di comunicazione rete
        inet
*/
#include "defpub.h"

#define  lanswap        73

#define  pdig_arm       6    // n. digitali diagnostica per armadio

#define  congrete      110   // utilizzato per commutazione
			     // in caso di tutti i nodi off line

#define  stastopa      111
#define  stbstopa      112
#define  modstopa      113
#define  stastopb      114
#define  stbstopb      115
#define  modstopb      116
#define  staper0a      117
#define  stbper0a      118
#define  modper0a      119
#define  staper0b      120
#define  stbper0b      121
#define  modper0b      122
#define  staper1a      123
#define  stbper1a      124
#define  modper1a      125
#define  staper1b      126
#define  stbper1b      127
#define  modper1b      128
#define  staper2a      129
#define  stbper2a      130
#define  modper2a      131
#define  staper2b      132
#define  stbper2b      133
#define  modper2b      134
#define  staper3a      135
#define  stbper3a      136
#define  modper3a      137
#define  staper3b      138
#define  stbper3b      139
#define  modper3b      140
#define  staper4a      141
#define  stbper4a      142
#define  modper4a      143
#define  staper4b      144
#define  stbper4b      145
#define  modper4b      146
#define  staper5a      147
#define  stbper5a      148
#define  modper5a      149
#define  staper5b      150
#define  stbper5b      151
#define  modper5b      152
#define  staper6a      153
#define  stbper6a      154
#define  modper6a      155
#define  staper6b      156
#define  stbper6b      157
#define  modper6b      158
#define  staper7a      159
#define  stbper7a      160
#define  modper7a      161
#define  staper7b      162
#define  stbper7b      163
#define  modper7b      164
#define  staper8a      165
#define  stbper8a      166
#define  modper8a      167
#define  staper8b      168
#define  stbper8b      169
#define  modper8b      170
#define  staper9a      171
#define  stbper9a      172
#define  modper9a      173 
#define  staper9b      174
#define  stbper9b      175
#define  modper9b      176
/*
        definizione analogici di diagnostica contatori
        n. punti trattati per nodo
*/
#define max_cn		10		// n. massimo contatori

#define cnta01       90
#define cnta02       91
#define cnta03       92
#define cnta04       93
#define cnta05       94
#define cnta06       95
#define cnta07       96
#define cnta08       97
#define cnta09       98
#define cnta10       99

#define cntb01      100
#define cntb02      101
#define cntb03      102
#define cntb04      103
#define cntb05      104
#define cntb06      105
#define cntb07      106
#define cntb08      107
#define cntb09      108
#define cntb10      109


