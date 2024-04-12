# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image sble_0$GIForient]
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
n {set myportId [$c create image [expr $x + -14.0] [expr $y + 0.0] -image elek_e -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -14.0] -image elek_s -anchor s]}
s {set myportId [$c create image [expr $x + 14.0] [expr $y + 0.0] -image elek_w -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 14.0] -image elek_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { V1RE V1IM I1RE I1IM }

switch $GIForient {
n {set myportId [$c create image [expr $x + 14.0] [expr $y + 0.0] -image elek_w -anchor w]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + 14.0] -image elek_n -anchor n]}
s {set myportId [$c create image [expr $x + -14.0] [expr $y + 0.0] -image elek_e -anchor e]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + -14.0] -image elek_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { V1RE V1IM I2RE I2IM }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + 34.0] -image elek_s -anchor n]}
e {set myportId [$c create image [expr $x + -34.0] [expr $y + 0.0] -image elek_w -anchor e]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + -34.0] -image elek_n -anchor s]}
w {set myportId [$c create image [expr $x + 34.0] [expr $y + 0.0] -image elek_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag elek_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { V1RE V1IM ICRE ICIM }
