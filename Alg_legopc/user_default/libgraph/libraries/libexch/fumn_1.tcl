# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image fumn_1$GIForient]
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
n {set myportId [$c create image [expr $x + -18.0] [expr $y + -20.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + 20.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + 20.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + -20.0] [expr $y + 18.0] -image term_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { TM11 TF_1 GF_1 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -18.0] [expr $y + 0.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + 0.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 18.0] -image term_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { TM12 TF_2 GF_2 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -18.0] [expr $y + 20.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + -20.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + -20.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + 20.0] [expr $y + 18.0] -image term_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { TM13 TF_3 GF_3 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + -38.0] -image flue_s -anchor s]}
e {set myportId [$c create image [expr $x + 38.0] [expr $y + 0.0] -image flue_w -anchor w]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + 38.0] -image flue_n -anchor n]}
w {set myportId [$c create image [expr $x + -38.0] [expr $y + 0.0] -image flue_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { WIF_ ____ TIF_ ____ ____ %CO2 %PH2 %H2O }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + 38.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -38.0] [expr $y + 0.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + -38.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 38.0] [expr $y + 0.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { WIF_ ____ TUF_ ____ ____ %CO2 %PH2 %H2O }
