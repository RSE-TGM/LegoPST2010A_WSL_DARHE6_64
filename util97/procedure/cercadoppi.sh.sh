#############################################################################
#
# Cerca le tag doppie in una task per i segnali blu 
#
#############################################################################
#
export tag
if [ -f variabili.edf ]
then
  grep '@#K@' variabili.edf | grep 'slsc' | \
  cut -f7 -d' ' | sort | uniq -d > cercadoppi.tmp
  cat cercadoppi.tmp | while read tag
  do
    echo ${tag}
    grep ${tag} ????.pag | cut -c 1-4
  done
else
  echo File variabili.edf non presente !!
fi
rm -f cercadoppi.tmp
