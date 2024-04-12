# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image tra3_0$GIForient]
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
n {set myportId [$c create image [expr $x + -26.0] [expr $y + 0.0] -image elek_w -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -26.0] -image elek_n -anchor s]}
s {set myportId [$c create image [expr $x + 26.0] [expr $y + 0.0] -image elek_e -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 26.0] -image elek_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { VFR1 VFX1 IR1_ IX1_ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -26.0] [expr $y + 12.0] -image comm_e -anchor e]}
e {set myportId [$c create image [expr $x + -12.0] [expr $y + -26.0] -image comm_s -anchor s]}
s {set myportId [$c create image [expr $x + 26.0] [expr $y + -12.0] -image comm_w -anchor w]}
w {set myportId [$c create image [expr $x + 12.0] [expr $y + 26.0] -image comm_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { SW1_ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 8.0] [expr $y + -26.0] -image elek_n -anchor s]}
e {set myportId [$c create image [expr $x + 26.0] [expr $y + 8.0] -image elek_e -anchor w]}
s {set myportId [$c create image [expr $x + -8.0] [expr $y + 26.0] -image elek_s -anchor n]}
w {set myportId [$c create image [expr $x + -26.0] [expr $y + -8.0] -image elek_w -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { VFR2 VFX2 IR2_ IX2_ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 20.0] [expr $y + -26.0] -image comm_s -anchor s]}
e {set myportId [$c create image [expr $x + 26.0] [expr $y + 20.0] -image comm_w -anchor w]}
s {set myportId [$c create image [expr $x + -20.0] [expr $y + 26.0] -image comm_n -anchor n]}
w {set myportId [$c create image [expr $x + -26.0] [expr $y + -20.0] -image comm_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port6 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port6.$mymodId
set port6.$mymodId { SW2_ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 8.0] [expr $y + 26.0] -image elek_s -anchor n]}
e {set myportId [$c create image [expr $x + -26.0] [expr $y + 8.0] -image elek_w -anchor e]}
s {set myportId [$c create image [expr $x + -8.0] [expr $y + -26.0] -image elek_n -anchor s]}
w {set myportId [$c create image [expr $x + 26.0] [expr $y + -8.0] -image elek_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { VFR3 VFX3 IR3_ IX3_ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 20.0] [expr $y + 26.0] -image comm_n -anchor n]}
e {set myportId [$c create image [expr $x + -26.0] [expr $y + 20.0] -image comm_e -anchor e]}
s {set myportId [$c create image [expr $x + -20.0] [expr $y + -26.0] -image comm_s -anchor s]}
w {set myportId [$c create image [expr $x + 26.0] [expr $y + -20.0] -image comm_w -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { SW3_ }
