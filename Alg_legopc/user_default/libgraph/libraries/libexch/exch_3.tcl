# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image exch_3$GIForient]
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
n {set myportId [$c create image [expr $x + 0.0] [expr $y + 62.0] -image hydr_s -anchor n]}
e {set myportId [$c create image [expr $x + -62.0] [expr $y + 0.0] -image hydr_w -anchor e]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + -62.0] -image hydr_n -anchor s]}
w {set myportId [$c create image [expr $x + 62.0] [expr $y + 0.0] -image hydr_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { WUTU PUTU ____ ____ ____ HUTU ____ HVAL }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + -40.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + 40.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + 40.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + -40.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { TPE1 TF11 GE11 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + -16.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + 16.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + 16.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + -16.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { TPE2 TF21 GE21 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + 16.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + -16.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + -16.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + 16.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { TPE3 TF31 GE31 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + 40.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + -40.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + -40.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + 40.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { TPE4 TF41 GE41 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + -62.0] -image hydr_s -anchor s]}
e {set myportId [$c create image [expr $x + 62.0] [expr $y + 0.0] -image hydr_w -anchor w]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + 62.0] -image hydr_n -anchor n]}
w {set myportId [$c create image [expr $x + -62.0] [expr $y + 0.0] -image hydr_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { WITU PITU ____ ____ ____ HITU ____ HM_1 }
