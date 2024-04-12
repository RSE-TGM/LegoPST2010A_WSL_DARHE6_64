# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image bhd0_0$GIForient]
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
n {set myportId [$c create image [expr $x + 0.0] [expr $y + 22.0] -image term_n -anchor n]}
e {set myportId [$c create image [expr $x + -22.0] [expr $y + 0.0] -image term_e -anchor e]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + -22.0] -image term_s -anchor s]}
w {set myportId [$c create image [expr $x + 22.0] [expr $y + 0.0] -image term_w -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { TEST TCOL GEST ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 22.0] [expr $y + 0.0] -image dump_w -anchor w]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + 22.0] -image dump_n -anchor n]}
s {set myportId [$c create image [expr $x + -22.0] [expr $y + 0.0] -image dump_e -anchor e]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + -22.0] -image dump_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag dump_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { WE_1 PCOL ____ FE_1 HE_1 FNAC HCOL ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -22.0] [expr $y + 0.0] -image dump_w -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -22.0] -image dump_n -anchor s]}
s {set myportId [$c create image [expr $x + 22.0] [expr $y + 0.0] -image dump_e -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 22.0] -image dump_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag dump_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { WU_1 PCOL ____ FNAC HCOL FU_1 HU_1 ____ ____ ____ }
