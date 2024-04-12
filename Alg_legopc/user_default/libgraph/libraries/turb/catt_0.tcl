# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image catt_0$GIForient]
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
n {set myportId [$c create image [expr $x + -36.0] [expr $y + -30.0] -image comm_s -anchor s]}
e {set myportId [$c create image [expr $x + 30.0] [expr $y + -36.0] -image comm_w -anchor w]}
s {set myportId [$c create image [expr $x + 36.0] [expr $y + 30.0] -image comm_n -anchor n]}
w {set myportId [$c create image [expr $x + -30.0] [expr $y + 36.0] -image comm_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port9 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port9.$mymodId
set port9.$mymodId { RPMC }

switch $GIForient {
n {set myportId [$c create image [expr $x + -12.0] [expr $y + -30.0] -image comm_s -anchor s]}
e {set myportId [$c create image [expr $x + 30.0] [expr $y + -12.0] -image comm_w -anchor w]}
s {set myportId [$c create image [expr $x + 12.0] [expr $y + 30.0] -image comm_n -anchor n]}
w {set myportId [$c create image [expr $x + -30.0] [expr $y + 12.0] -image comm_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port10 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port10.$mymodId
set port10.$mymodId { AIGV }

switch $GIForient {
n {set myportId [$c create image [expr $x + 12.0] [expr $y + -30.0] -image comm_s -anchor s]}
e {set myportId [$c create image [expr $x + 30.0] [expr $y + 12.0] -image comm_w -anchor w]}
s {set myportId [$c create image [expr $x + -12.0] [expr $y + 30.0] -image comm_n -anchor n]}
w {set myportId [$c create image [expr $x + -30.0] [expr $y + -12.0] -image comm_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port11 withtag $myportId
$c addtag port withtag $myportId
$c addtag comm_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port11.$mymodId
set port11.$mymodId { ZSPO }

switch $GIForient {
n {set myportId [$c create image [expr $x + -54.0] [expr $y + 0.0] -image flue_e -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -54.0] -image flue_s -anchor s]}
s {set myportId [$c create image [expr $x + 54.0] [expr $y + 0.0] -image flue_w -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 54.0] -image flue_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { WASP PASP TASP ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -48.0] [expr $y + 30.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + -48.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + 48.0] [expr $y + -30.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 48.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { WSP1 PCA1 TCA1 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -32.0] [expr $y + 30.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + -32.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + 32.0] [expr $y + -30.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 32.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { WSP2 PCA1 TCA1 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -16.0] [expr $y + 30.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + -16.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + 16.0] [expr $y + -30.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 16.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { WSP3 PCA2 TCA2 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + 30.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + 0.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + -30.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 0.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { WSP4 PCA3 TCA3 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 16.0] [expr $y + 30.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + 16.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + -16.0] [expr $y + -30.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + -16.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port6 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port6.$mymodId
set port6.$mymodId { WSP5 PCA1 TCA1 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 32.0] [expr $y + 30.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + 32.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + -32.0] [expr $y + -30.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + -32.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port7 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port7.$mymodId
set port7.$mymodId { WSP6 PCA2 TCA2 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 48.0] [expr $y + 30.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + 48.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + -48.0] [expr $y + -30.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + -48.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port8 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port8.$mymodId
set port8.$mymodId { WSP7 PCA3 TCA3 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 54.0] [expr $y + 0.0] -image flue_e -anchor w]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + 54.0] -image flue_s -anchor n]}
s {set myportId [$c create image [expr $x + -54.0] [expr $y + 0.0] -image flue_w -anchor e]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + -54.0] -image flue_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { WMAN PMAN TMAN ____ ____ ____ ____ ____ }
