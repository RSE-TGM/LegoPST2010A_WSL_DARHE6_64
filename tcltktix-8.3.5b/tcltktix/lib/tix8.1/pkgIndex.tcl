# Tcl package index file, version 1.0
#
# $Id: pkgIndex.tcl.in,v 1.1.2.1 2001/11/04 05:00:43 idiscovery Exp $
#

package ifneeded Tix 8.1.8.3 [list load "[file join [file dirname $dir] libtix8.1.8.3.so]" Tix]
package ifneeded Tixsam 8.1.8.3 [list load "[file join [file dirname $dir] libtixsam8.1.8.3.so]" Tixsam]
package ifneeded wm_default 1.0 [list source [file join $dir pref WmDefault.tcl]]
