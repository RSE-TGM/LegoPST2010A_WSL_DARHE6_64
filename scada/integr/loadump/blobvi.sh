#!/bin/sh
# -> blobvi
#
# Scarica un blob lo edita con il vi e a seconda del tipo
# di chiusura aggiorna il blob nel data-base INFORMIX.
# La shell funziona con logica inversa false=1 true=0

ARGOMENTO=""
COMMANDLINE=""
for ARG in $@
do
	ARGOMENTO=$ARGOMENTO" "$ARG
done
echo $ARGOMENTO
COMMANDLINE=$ARGOMENTO" DUMP"
if loadump $COMMANDLINE
then
	cp blobdump.txt blobdump.tmp
	vi blobdump.txt
	if  cmp -s blobdump.txt blobdump.tmp
	then
		echo "WARNING: Blob field changes lost"
	else
		COMMANDLINE=$ARGOMENTO" LOAD"
		loadump $COMMANDLINE
	fi

	rm blobdump.txt
	rm blobdump.tmp
fi
exit 0
