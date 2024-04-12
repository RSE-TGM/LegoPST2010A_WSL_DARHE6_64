#!/bin/ksh
#
#  Script:                      testforaus.sh
#  Subsystem:           1
#  %version:            2 %
#  Description:
#  %created_by:         lomgr %
#  %date_created:       Wed Feb 19 17:00:52 1997 %

#
# make per test compilazione fortran ausiliario
#

# compilo il file temporaneo contenente il fortran ausiliario
ftmp: foraustmp.f
	$(FC) -c foraustmp.f
	@echo Done

fpartial: forpart.f
	$(FC) -c forpart.f

rtmp: foraustmp.f
	rm foraustmp.f
