# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image fumn_5$GIForient]
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
n {set myportId [$c create image [expr $x + 0.0] [expr $y + 66.0] -image flue_s -anchor n]}
e {set myportId [$c create image [expr $x + -66.0] [expr $y + 0.0] -image flue_w -anchor e]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + -66.0] -image flue_n -anchor s]}
w {set myportId [$c create image [expr $x + 66.0] [expr $y + 0.0] -image flue_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag flue_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { WIF_ ____ TUF_ ____ ____ %CO2 %PH2 %H2O }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + -66.0] -image flue_s -anchor s]}
e {set myportId [$c create image [expr $x + 66.0] [expr $y + 0.0] -image flue_w -anchor w]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + 66.0] -image flue_n -anchor n]}
w {set myportId [$c create image [expr $x + -66.0] [expr $y + 0.0] -image flue_e -anchor e]}
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
n {set myportId [$c create image [expr $x + -18.0] [expr $y + -44.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + 44.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + 44.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + -44.0] [expr $y + 18.0] -image term_s -anchor n]}
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
n {set myportId [$c create image [expr $x + -18.0] [expr $y + -24.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + 24.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + 24.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + -24.0] [expr $y + 18.0] -image term_s -anchor n]}
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
n {set myportId [$c create image [expr $x + -18.0] [expr $y + -8.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + 8.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + 8.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + -8.0] [expr $y + 18.0] -image term_s -anchor n]}
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
n {set myportId [$c create image [expr $x + -18.0] [expr $y + 12.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + -12.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + -12.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + 12.0] [expr $y + 18.0] -image term_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { TM14 TF_4 GF_4 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -18.0] [expr $y + 32.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + -32.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + -32.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + 32.0] [expr $y + 18.0] -image term_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port6 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port6.$mymodId
set port6.$mymodId { TM15 TF_5 GF_5 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -18.0] [expr $y + 48.0] -image term_w -anchor e]}
e {set myportId [$c create image [expr $x + -48.0] [expr $y + -18.0] -image term_n -anchor s]}
s {set myportId [$c create image [expr $x + 18.0] [expr $y + -48.0] -image term_e -anchor w]}
w {set myportId [$c create image [expr $x + 48.0] [expr $y + 18.0] -image term_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port7 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port7.$mymodId
set port7.$mymodId { TM16 TF_6 GF_6 ____ }
