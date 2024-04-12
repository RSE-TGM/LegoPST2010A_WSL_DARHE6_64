#!/bin/sh
# The next line is executed by /bin/sh, but not tcl \
exec wish "$0" ${1+"$@"}

proc quit_scada {} {
  puts $::channel "q"
  ::exit
}

proc run_scada {} {
  set ::channel [open |scada w]
  .b configure -text "   quit   " -bg green
  .b configure -command ::quit_scada
}

label .l -text "                Scada                 "
button .b -text "   run   " -bg red -command ::run_scada
pack .l .b
