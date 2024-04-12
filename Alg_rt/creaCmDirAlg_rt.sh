#!/bin/sh
#
#  Script:                      %name%
#  Subsystem:           %subsystem%
#  %version:            %
#  Description:
#  %created_by:         %
#  %date_created:       %

#shell per la creazione delle directory  nel progetto
#per Alg_rt
ccm create -t dir bin
ccm create -t dir uid
ccm create -t dir net_simula
cd ./net_simula
ccm create -t dir net_monit
cd ..


