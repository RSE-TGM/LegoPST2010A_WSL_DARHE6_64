# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image bev0_0$GIForient]
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
n {set myportId [$c create image [expr $x + -40.0] [expr $y + -34.0] -image term_n -anchor s]}
e {set myportId [$c create image [expr $x + 34.0] [expr $y + -40.0] -image term_e -anchor w]}
s {set myportId [$c create image [expr $x + 40.0] [expr $y + 34.0] -image term_s -anchor n]}
w {set myportId [$c create image [expr $x + -34.0] [expr $y + 40.0] -image term_w -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { TEMP TMI1 GATU ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + -34.0] -image term_n -anchor s]}
e {set myportId [$c create image [expr $x + 34.0] [expr $y + 0.0] -image term_e -anchor w]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + 34.0] -image term_s -anchor n]}
w {set myportId [$c create image [expr $x + -34.0] [expr $y + 0.0] -image term_w -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { TEMP TMI2 GATU ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 40.0] [expr $y + -34.0] -image term_n -anchor s]}
e {set myportId [$c create image [expr $x + 34.0] [expr $y + 40.0] -image term_e -anchor w]}
s {set myportId [$c create image [expr $x + -40.0] [expr $y + 34.0] -image term_s -anchor n]}
w {set myportId [$c create image [expr $x + -34.0] [expr $y + -40.0] -image term_w -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { TEMP TMI3 GATU ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 50.0] [expr $y + -4.0] -image hydr_e -anchor w]}
e {set myportId [$c create image [expr $x + 4.0] [expr $y + 50.0] -image hydr_s -anchor n]}
s {set myportId [$c create image [expr $x + -50.0] [expr $y + 4.0] -image hydr_w -anchor e]}
w {set myportId [$c create image [expr $x + -4.0] [expr $y + -50.0] -image hydr_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { WSTP PRES ____ ____ ____ HSTE ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -8.0] [expr $y + 30.0] -image hydr_n -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + -8.0] -image hydr_e -anchor e]}
s {set myportId [$c create image [expr $x + 8.0] [expr $y + -30.0] -image hydr_s -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 8.0] -image hydr_w -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { WDSI PRES PFDS LEVD ____ HDSI ____ HDIS }

switch $GIForient {
n {set myportId [$c create image [expr $x + 16.0] [expr $y + 30.0] -image hydr_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + 16.0] -image hydr_w -anchor e]}
s {set myportId [$c create image [expr $x + -16.0] [expr $y + -30.0] -image hydr_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + -16.0] -image hydr_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { WDSO PRES PFDS LEVD ____ HDIS ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -36.0] [expr $y + 30.0] -image dump_n -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + -36.0] -image dump_e -anchor e]}
s {set myportId [$c create image [expr $x + 36.0] [expr $y + -30.0] -image dump_s -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + 36.0] -image dump_w -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port6 withtag $myportId
$c addtag port withtag $myportId
$c addtag dump_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port6.$mymodId
set port6.$mymodId { WBRI PRES PFBR FNAI HBRI FNAC HBRN LEVB ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 44.0] [expr $y + 30.0] -image dump_s -anchor n]}
e {set myportId [$c create image [expr $x + -30.0] [expr $y + 44.0] -image dump_w -anchor e]}
s {set myportId [$c create image [expr $x + -44.0] [expr $y + -30.0] -image dump_n -anchor s]}
w {set myportId [$c create image [expr $x + 30.0] [expr $y + -44.0] -image dump_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port7 withtag $myportId
$c addtag port withtag $myportId
$c addtag dump_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port7.$mymodId
set port7.$mymodId { WBRO PRES PFBR FNAC HBRN ____ ____ LEVB ____ ____ }
