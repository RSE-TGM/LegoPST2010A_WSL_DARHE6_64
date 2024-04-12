# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image drel_0$GIForient]
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
n {set myportId [$c create image [expr $x + -26.0] [expr $y + -4.0] -image dump_e -anchor e]}
e {set myportId [$c create image [expr $x + 4.0] [expr $y + -26.0] -image dump_s -anchor s]}
s {set myportId [$c create image [expr $x + 26.0] [expr $y + 4.0] -image dump_w -anchor w]}
w {set myportId [$c create image [expr $x + -4.0] [expr $y + 26.0] -image dump_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag dump_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { UMOD FASE QATT QREA IFIL ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -4.0] [expr $y + 26.0] -image dump_s -anchor n]}
e {set myportId [$c create image [expr $x + -26.0] [expr $y + -4.0] -image dump_w -anchor e]}
s {set myportId [$c create image [expr $x + 4.0] [expr $y + -26.0] -image dump_n -anchor s]}
w {set myportId [$c create image [expr $x + 26.0] [expr $y + 4.0] -image dump_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag dump_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { UMD1 FAS1 QAT1 QRE1 IFI1 ____ ____ ____ ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 26.0] [expr $y + -4.0] -image dump_e -anchor w]}
e {set myportId [$c create image [expr $x + 4.0] [expr $y + 26.0] -image dump_s -anchor n]}
s {set myportId [$c create image [expr $x + -26.0] [expr $y + 4.0] -image dump_w -anchor e]}
w {set myportId [$c create image [expr $x + -4.0] [expr $y + -26.0] -image dump_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag dump_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { VMD2 FAS2 QAT2 QRE2 IFI2 ____ ____ ____ ____ ____ }
