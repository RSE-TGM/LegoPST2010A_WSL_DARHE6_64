# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image tatt_0$GIForient]
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
n {set myportId [$c create image [expr $x + -20.0] [expr $y + 30.0] -image flue_n -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + -20.0] -image flue_e -anchor e]}
s {set myportId [$c create image [expr $x + 20.0] [expr $y + -30.0] -image flue_s -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 20.0] -image flue_w -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { WIN1 PCA1 TIN1 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -4.0] [expr $y + 30.0] -image flue_n -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + -4.0] -image flue_e -anchor e]}
s {set myportId [$c create image [expr $x + 4.0] [expr $y + -30.0] -image flue_s -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 4.0] -image flue_w -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { WIN2 PCA2 TIN2 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 12.0] [expr $y + 30.0] -image flue_n -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + 12.0] -image flue_e -anchor e]}
s {set myportId [$c create image [expr $x + -12.0] [expr $y + -30.0] -image flue_s -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + -12.0] -image flue_w -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { WIN3 PCA3 TIN3 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -30.0] [expr $y + 0.0] -image flue_e -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -30.0] -image flue_s -anchor s]}
s {set myportId [$c create image [expr $x + 30.0] [expr $y + 0.0] -image flue_w -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 30.0] -image flue_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { WAMM PAMM TAMM ____ XCOM XXCH XH2O ZMN2 }

switch $GIForient {
n {set myportId [$c create image [expr $x + -20.0] [expr $y + -34.0] -image comm_s -anchor s]}
e {set myportId [$c create image [expr $x + 34.0] [expr $y + -20.0] -image comm_w -anchor w]}
s {set myportId [$c create image [expr $x + 20.0] [expr $y + 34.0] -image comm_n -anchor n]}
w {set myportId [$c create image [expr $x + -34.0] [expr $y + 20.0] -image comm_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { RPMC }

switch $GIForient {
n {set myportId [$c create image [expr $x + 30.0] [expr $y + 0.0] -image flue_e -anchor w]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + 30.0] -image flue_s -anchor n]}
s {set myportId [$c create image [expr $x + -30.0] [expr $y + 0.0] -image flue_w -anchor e]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + -30.0] -image flue_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { WSCA PSCA TSCA ____ ____ ____ XH2O ____ }
