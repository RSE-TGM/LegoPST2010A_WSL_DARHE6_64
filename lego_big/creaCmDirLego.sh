#!/bin/sh
#
#  Script:                      %name%
#  Subsystem:           %subsystem%
#  %version:            %
#  Description:
#  %created_by:         %
#  %date_created:       %

#shell per la creazione delle directory  nel progetto
#per i prodotti lego
ccm create -t dir bin
ccm create -t dir lib
ccm create -t dir procedure
ccm create -t dir sorglego
ccm create -t dir tavole
cd ./sorglego
ccm create -t dir main
ccm create -t dir sub
cd ..

