#!/bin/ksh
#
# mkill
# utility di pulizia di una simulazione andata male
# massimopentolini  19-03-02  01.01  effettua il kill che prima stampava
#                                    soltanto: effettua killsim e kclean
# massimopentolini  ??-??-01  01.00  creazione
ps -ef | grep $USER | grep "\[ksh\]" \
| awk '  { \
           if ($3=="1") { \
            stringa1=sprintf("kill -9 %s\n", $2); \
            printf(stringa1) \
            system(stringa1) \
            } \
}'
echo killsim
killsim
echo kclean
kclean

