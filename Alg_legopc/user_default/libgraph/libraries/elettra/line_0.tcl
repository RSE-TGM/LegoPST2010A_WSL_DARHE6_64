# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image line_0$GIForient]
$c addtag id$mymodId withtag $mymodId
$c addtag module withtag $mymodId
$c addtag $idclass.cls withtag $mymodId
$c addtag $GIForient.ori withtag $mymodId
if {$fromfile == "yes"} {
	$c addtag $mlpath.lpath withtag $mymodId
} else {
	$c addtag $curLibPath.lpath withtag $mymodId
}
# let the user choose a name (Id)
if {$fromfile == "yes"} then {set progName $ff_progNumb} else {inputModName $c $x $y}
$c addtag $progName.name withtag $mymodId
incr progNumb

switch $GIForient {
n {set myportId [$c create image [expr $x + -50.0] [expr $y + -12.0] -image elek_w -anchor e]}
e {set myportId [$c create image [expr $x + 12.0] [expr $y + -50.0] -image elek_n -anchor s]}
s {set myportId [$c create image [expr $x + 50.0] [expr $y + 12.0] -image elek_e -anchor w]}
w {set myportId [$c create image [expr $x + -12.0] [expr $y + 50.0] -image elek_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { UR01 UX01 IR01 IX01 }

switch $GIForient {
n {set myportId [$c create image [expr $x + 50.0] [expr $y + -12.0] -image elek_e -anchor w]}
e {set myportId [$c create image [expr $x + 12.0] [expr $y + 50.0] -image elek_s -anchor n]}
s {set myportId [$c create image [expr $x + -50.0] [expr $y + 12.0] -image elek_w -anchor e]}
w {set myportId [$c create image [expr $x + -12.0] [expr $y + -50.0] -image elek_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { UR02 UX02 IR02 IX02 }

switch $GIForient {
n {set myportId [$c create image [expr $x + 50.0] [expr $y + 8.0] -image comm_w -anchor w]}
e {set myportId [$c create image [expr $x + -8.0] [expr $y + 50.0] -image comm_n -anchor n]}
s {set myportId [$c create image [expr $x + -50.0] [expr $y + -8.0] -image comm_e -anchor e]}
w {set myportId [$c create image [expr $x + 8.0] [expr $y + -50.0] -image comm_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { STL2 }

switch $GIForient {
n {set myportId [$c create image [expr $x + -50.0] [expr $y + 8.0] -image comm_e -anchor e]}
e {set myportId [$c create image [expr $x + -8.0] [expr $y + -50.0] -image comm_s -anchor s]}
s {set myportId [$c create image [expr $x + 50.0] [expr $y + -8.0] -image comm_w -anchor w]}
w {set myportId [$c create image [expr $x + 8.0] [expr $y + 50.0] -image comm_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { STL1 }
