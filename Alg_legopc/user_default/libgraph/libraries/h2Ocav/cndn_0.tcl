# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image cndn_0$GIForient]
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
n {set myportId [$c create image [expr $x + -4.0] [expr $y + -26.0] -image hydr_s -anchor s]}
e {set myportId [$c create image [expr $x + 26.0] [expr $y + -4.0] -image hydr_w -anchor w]}
s {set myportId [$c create image [expr $x + 4.0] [expr $y + 26.0] -image hydr_n -anchor n]}
w {set myportId [$c create image [expr $x + -26.0] [expr $y + 4.0] -image hydr_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port5 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port5.$mymodId
set port5.$mymodId { WTUR PCND ____ ____ ____ HTUR ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + -54.0] [expr $y + -12.0] -image hydr_e -anchor e]}
e {set myportId [$c create image [expr $x + 12.0] [expr $y + -54.0] -image hydr_s -anchor s]}
s {set myportId [$c create image [expr $x + 54.0] [expr $y + 12.0] -image hydr_w -anchor w]}
w {set myportId [$c create image [expr $x + -12.0] [expr $y + 54.0] -image hydr_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port0 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port0.$mymodId
set port0.$mymodId { WEXT PCND ____ ____ ____ HEXT ____ HLCN }

switch $GIForient {
n {set myportId [$c create image [expr $x + -54.0] [expr $y + 0.0] -image hydr_e -anchor e]}
e {set myportId [$c create image [expr $x + 0.0] [expr $y + -54.0] -image hydr_s -anchor s]}
s {set myportId [$c create image [expr $x + 54.0] [expr $y + 0.0] -image hydr_w -anchor w]}
w {set myportId [$c create image [expr $x + 0.0] [expr $y + 54.0] -image hydr_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port1 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port1.$mymodId
set port1.$mymodId { WDRE PCND ____ ____ ____ HDRE ____ HLCN }

switch $GIForient {
n {set myportId [$c create image [expr $x + -54.0] [expr $y + 12.0] -image hydr_e -anchor e]}
e {set myportId [$c create image [expr $x + -12.0] [expr $y + -54.0] -image hydr_s -anchor s]}
s {set myportId [$c create image [expr $x + 54.0] [expr $y + -12.0] -image hydr_w -anchor w]}
w {set myportId [$c create image [expr $x + 12.0] [expr $y + 54.0] -image hydr_n -anchor n]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port2 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port2.$mymodId
set port2.$mymodId { WRIC PCND ____ ____ ____ HRIC ____ HLCN }

switch $GIForient {
n {set myportId [$c create image [expr $x + -4.0] [expr $y + 26.0] -image hydr_s -anchor n]}
e {set myportId [$c create image [expr $x + -26.0] [expr $y + -4.0] -image hydr_w -anchor e]}
s {set myportId [$c create image [expr $x + 4.0] [expr $y + -26.0] -image hydr_n -anchor s]}
w {set myportId [$c create image [expr $x + 26.0] [expr $y + 4.0] -image hydr_e -anchor w]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port6 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port6.$mymodId
set port6.$mymodId { WLCP PFCN ____ ____ ____ HLCN ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 50.0] [expr $y + 12.0] -image hydr_e -anchor w]}
e {set myportId [$c create image [expr $x + -12.0] [expr $y + 50.0] -image hydr_s -anchor n]}
s {set myportId [$c create image [expr $x + -50.0] [expr $y + -12.0] -image hydr_w -anchor e]}
w {set myportId [$c create image [expr $x + 12.0] [expr $y + -50.0] -image hydr_n -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port3 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port3.$mymodId
set port3.$mymodId { WRFT ____ ____ ____ ____ HUFT ____ ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 50.0] [expr $y + -8.0] -image hydr_w -anchor w]}
e {set myportId [$c create image [expr $x + 8.0] [expr $y + 50.0] -image hydr_n -anchor n]}
s {set myportId [$c create image [expr $x + -50.0] [expr $y + 8.0] -image hydr_e -anchor e]}
w {set myportId [$c create image [expr $x + -8.0] [expr $y + -50.0] -image hydr_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port4 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port4.$mymodId
set port4.$mymodId { WRFT ____ ____ ____ ____ HIFT ____ ____ }
