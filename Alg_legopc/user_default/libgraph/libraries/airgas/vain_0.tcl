# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image vain_0$GIForient]
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
n {set myportId [$c create image [expr $x + 0.0] [expr $y + -26.0] -image comm_s -anchor s]}
e {set myportId [$c create image [expr $x + 26.0] [expr $y + 0.0] -image comm_w -anchor w]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + 26.0] -image comm_n -anchor n]}
w {set myportId [$c create image [expr $x + -26.0] [expr $y + 0.0] -image comm_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { ALZV }

switch $GIForient {
n {set myportId [$c create image [expr $x + -26.0] [expr $y + 0.0] -image flue_e -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -26.0] -image flue_s -anchor s]}
s {set myportId [$c create image [expr $x + 26.0] [expr $y + 0.0] -image flue_w -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 26.0] -image flue_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { WVAL PMON TMON TMI_ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 26.0] [expr $y + 0.0] -image flue_e -anchor w]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + 26.0] -image flue_s -anchor n]}
s {set myportId [$c create image [expr $x + -26.0] [expr $y + 0.0] -image flue_w -anchor e]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + -26.0] -image flue_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { WVAL PVAL TVAL TVI_ ____ ____ ____ ____ }
