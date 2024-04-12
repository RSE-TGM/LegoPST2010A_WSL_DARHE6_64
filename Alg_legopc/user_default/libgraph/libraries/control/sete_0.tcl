# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image sete_0$GIForient]
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
n {set myportId [$c create image [expr $x + -22.0] [expr $y + -12.0] -image hydr_e -anchor e]}
e {set myportId [$c create image [expr $x + 12.0] [expr $y + -22.0] -image hydr_s -anchor s]}
s {set myportId [$c create image [expr $x + 22.0] [expr $y + 12.0] -image hydr_w -anchor w]}
w {set myportId [$c create image [expr $x + -12.0] [expr $y + 22.0] -image hydr_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { ____ PRES ____ ____ ____ HENT ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -22.0] [expr $y + 8.0] -image hydr_w -anchor e]}
e {set myportId [$c create image [expr $x + -8.0] [expr $y + -22.0] -image hydr_n -anchor s]}
s {set myportId [$c create image [expr $x + 22.0] [expr $y + -8.0] -image hydr_e -anchor w]}
w {set myportId [$c create image [expr $x + 8.0] [expr $y + 22.0] -image hydr_s -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { ____ PRES ____ ____ ____ ____ ____ HENT }
