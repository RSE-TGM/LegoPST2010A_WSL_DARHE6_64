# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image colt_1$GIForient]
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
n {set myportId [$c create image [expr $x + -26.0] [expr $y + -24.0] -image hydr_e -anchor e]}
e {set myportId [$c create image [expr $x + 24.0] [expr $y + -26.0] -image hydr_s -anchor s]}
s {set myportId [$c create image [expr $x + 26.0] [expr $y + 24.0] -image hydr_w -anchor w]}
w {set myportId [$c create image [expr $x + -24.0] [expr $y + 26.0] -image hydr_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { WE_1 PCOL ____ ____ ____ HE_1 ____ HCOL }

switch $GIForient {
n {set myportId [$c create image [expr $x + -26.0] [expr $y + 0.0] -image hydr_e -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -26.0] -image hydr_s -anchor s]}
s {set myportId [$c create image [expr $x + 26.0] [expr $y + 0.0] -image hydr_w -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 26.0] -image hydr_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { WE_2 PCOL ____ ____ ____ HE_2 ____ HCOL }

switch $GIForient {
n {set myportId [$c create image [expr $x + -26.0] [expr $y + 24.0] -image hydr_e -anchor e]}
e {set myportId [$c create image [expr $x + -24.0] [expr $y + -26.0] -image hydr_s -anchor s]}
s {set myportId [$c create image [expr $x + 26.0] [expr $y + -24.0] -image hydr_w -anchor w]}
w {set myportId [$c create image [expr $x + 24.0] [expr $y + 26.0] -image hydr_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { WE_3 PCOL ____ ____ ____ HE_3 ____ HCOL }

switch $GIForient {
n {set myportId [$c create image [expr $x + 26.0] [expr $y + -24.0] -image hydr_e -anchor w]}
e {set myportId [$c create image [expr $x + 24.0] [expr $y + 26.0] -image hydr_s -anchor n]}
s {set myportId [$c create image [expr $x + -26.0] [expr $y + 24.0] -image hydr_w -anchor e]}
w {set myportId [$c create image [expr $x + -24.0] [expr $y + -26.0] -image hydr_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { WU_1 PCOL ____ ____ ____ HCOL ____ HU_1 }

switch $GIForient {
n {set myportId [$c create image [expr $x + 26.0] [expr $y + 0.0] -image hydr_e -anchor w]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + 26.0] -image hydr_s -anchor n]}
s {set myportId [$c create image [expr $x + -26.0] [expr $y + 0.0] -image hydr_w -anchor e]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + -26.0] -image hydr_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { WU_2 PCOL ____ ____ ____ HCOL ____ HU_3 }

switch $GIForient {
n {set myportId [$c create image [expr $x + 26.0] [expr $y + 24.0] -image hydr_e -anchor w]}
e {set myportId [$c create image [expr $x + -24.0] [expr $y + 26.0] -image hydr_s -anchor n]}
s {set myportId [$c create image [expr $x + -26.0] [expr $y + -24.0] -image hydr_w -anchor e]}
w {set myportId [$c create image [expr $x + 24.0] [expr $y + -26.0] -image hydr_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { WU_3 PCOL ____ ____ ____ HCOL ____ HU_3 }
