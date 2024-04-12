#
#  Script:                      tsimula.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         zanna %
#  %date_created:       Wed Jan 22 12:30:10 1997 %
clear
if [ $# -eq 0 ]
then
echo "Si puo' attivare killsim passando un qualsiasi parametro "
sleep 1
fi
if [ $# -eq 1 ]
then
echo Attivazione iniziale di killsim 
killsim 
fi
echo 
echo "Attivazioni: - dispatcher - net_sked 1 - net_tast 7"
sleep 1
dispatcher &
net_sked 1 & 
net_tast 7&
sleep 1
net_tast &
