# this file created with PREINST rel. 0.3 

set mymodId [$c create image $x $y -image excy_1$GIForient]
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
$c addtag port14 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag output withtag $myportId; #port direction
global port14.$mymodId
set port14.$mymodId { WUTU PUTU ____ ____ ____ HUTU ____ HVAL }

switch $GIForient {
n {set myportId [$c create image [expr $x + 0.0] [expr $y + -62.0] -image hydr_s -anchor s]}
e {set myportId [$c create image [expr $x + 62.0] [expr $y + 0.0] -image hydr_w -anchor w]}
s {set myportId [$c create image [expr $x + 0.0] [expr $y + 62.0] -image hydr_n -anchor n]}
w {set myportId [$c create image [expr $x + -62.0] [expr $y + 0.0] -image hydr_e -anchor e]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port13 withtag $myportId
$c addtag port withtag $myportId
$c addtag hydr_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port13.$mymodId
set port13.$mymodId { WITU PITU ____ ____ ____ HITU ____ HM_1 }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + -44.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + 44.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + 44.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + -44.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port12 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port12.$mymodId
set port12.$mymodId { TPE1 TF11 GE11 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + -24.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + 24.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + 24.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + -24.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port11 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port11.$mymodId
set port11.$mymodId { TPE2 TF21 GE21 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + -4.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + 4.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + 4.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + -4.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port10 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port10.$mymodId
set port10.$mymodId { TPE3 TF31 GE31 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + 12.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + -12.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + -12.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + 12.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port9 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port9.$mymodId
set port9.$mymodId { TPE4 TF41 GE41 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + 32.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + -32.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + -32.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + 32.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port8 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port8.$mymodId
set port8.$mymodId { TPE5 TF51 GE51 ____ }

switch $GIForient {
n {set myportId [$c create image [expr $x + 18.0] [expr $y + 48.0] -image term_w -anchor w]}
e {set myportId [$c create image [expr $x + -48.0] [expr $y + 18.0] -image term_n -anchor n]}
s {set myportId [$c create image [expr $x + -18.0] [expr $y + -48.0] -image term_e -anchor e]}
w {set myportId [$c create image [expr $x + 48.0] [expr $y + -18.0] -image term_s -anchor s]}
}
$c addtag id$myportId withtag $myportId
$c addtag id$mymodId withtag $myportId
$c addtag port7 withtag $myportId
$c addtag port withtag $myportId
$c addtag term_ptype withtag $myportId; #port type
$c addtag input withtag $myportId; #port direction
global port7.$mymodId
set port7.$mymodId { TPE6 TF61 GE61 ____ }
