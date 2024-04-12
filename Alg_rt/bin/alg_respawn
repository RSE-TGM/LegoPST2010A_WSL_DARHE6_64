#
# Procedura di uso generale per l'attivazione ripetuta di un particolare
# processo
#
#
#
echo comando $*
#
set -m
#
trap "alg_respawn $* &" 20
#
$* &
wait
