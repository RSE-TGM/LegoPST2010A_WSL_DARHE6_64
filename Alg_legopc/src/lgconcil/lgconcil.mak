# Microsoft Developer Studio Generated NMAKE File, Based on LgConcil.dsp
!IF "$(CFG)" == ""
CFG=LgConcil - Win32 Debug
!MESSAGE No configuration specified. Defaulting to LgConcil - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "LgConcil - Win32 Release" && "$(CFG)" !=\
 "LgConcil - Win32 Debug"
!MESSAGE Invalid configuration "$(CFG)" specified.
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "LgConcil.mak" CFG="LgConcil - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "LgConcil - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "LgConcil - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "LgConcil - Win32 Release"

OUTDIR=.\Release
INTDIR=.\Release
# Begin Custom Macros
OutDir=.\Release
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\LgConcil.exe" "$(OUTDIR)\LgConcil.bsc"

!ELSE 

ALL : "$(OUTDIR)\LgConcil.exe" "$(OUTDIR)\LgConcil.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AlarmDlg.obj"
	-@erase "$(INTDIR)\AlarmDlg.sbr"
	-@erase "$(INTDIR)\LgConcil.obj"
	-@erase "$(INTDIR)\LgConcil.pch"
	-@erase "$(INTDIR)\LgConcil.res"
	-@erase "$(INTDIR)\LgConcil.sbr"
	-@erase "$(INTDIR)\LgConcilDlg.obj"
	-@erase "$(INTDIR)\LgConcilDlg.sbr"
	-@erase "$(INTDIR)\ParamDlg.obj"
	-@erase "$(INTDIR)\ParamDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\WNDlg.obj"
	-@erase "$(INTDIR)\WNDlg.sbr"
	-@erase "$(OUTDIR)\LgConcil.bsc"
	-@erase "$(OUTDIR)\LgConcil.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LgConcil.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Release/
CPP_SBRS=.\Release/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "NDEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\LgConcil.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LgConcil.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AlarmDlg.sbr" \
	"$(INTDIR)\LgConcil.sbr" \
	"$(INTDIR)\LgConcilDlg.sbr" \
	"$(INTDIR)\ParamDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\WNDlg.sbr"

"$(OUTDIR)\LgConcil.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:no\
 /pdb:"$(OUTDIR)\LgConcil.pdb" /machine:I386 /out:"$(OUTDIR)\LgConcil.exe" 
LINK32_OBJS= \
	"$(INTDIR)\AlarmDlg.obj" \
	"$(INTDIR)\LgConcil.obj" \
	"$(INTDIR)\LgConcil.res" \
	"$(INTDIR)\LgConcilDlg.obj" \
	"$(INTDIR)\ParamDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WNDlg.obj"

"$(OUTDIR)\LgConcil.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "LgConcil - Win32 Debug"

OUTDIR=.\Debug
INTDIR=.\Debug
# Begin Custom Macros
OutDir=.\Debug
# End Custom Macros

!IF "$(RECURSE)" == "0" 

ALL : "$(OUTDIR)\LgConcil.exe" "$(OUTDIR)\LgConcil.bsc"

!ELSE 

ALL : "$(OUTDIR)\LgConcil.exe" "$(OUTDIR)\LgConcil.bsc"

!ENDIF 

CLEAN :
	-@erase "$(INTDIR)\AlarmDlg.obj"
	-@erase "$(INTDIR)\AlarmDlg.sbr"
	-@erase "$(INTDIR)\LgConcil.obj"
	-@erase "$(INTDIR)\LgConcil.pch"
	-@erase "$(INTDIR)\LgConcil.res"
	-@erase "$(INTDIR)\LgConcil.sbr"
	-@erase "$(INTDIR)\LgConcilDlg.obj"
	-@erase "$(INTDIR)\LgConcilDlg.sbr"
	-@erase "$(INTDIR)\ParamDlg.obj"
	-@erase "$(INTDIR)\ParamDlg.sbr"
	-@erase "$(INTDIR)\StdAfx.obj"
	-@erase "$(INTDIR)\StdAfx.sbr"
	-@erase "$(INTDIR)\vc50.idb"
	-@erase "$(INTDIR)\vc50.pdb"
	-@erase "$(INTDIR)\WNDlg.obj"
	-@erase "$(INTDIR)\WNDlg.sbr"
	-@erase "$(OUTDIR)\LgConcil.bsc"
	-@erase "$(OUTDIR)\LgConcil.exe"
	-@erase "$(OUTDIR)\LgConcil.ilk"
	-@erase "$(OUTDIR)\LgConcil.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS"\
 /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LgConcil.pch" /Yu"stdafx.h"\
 /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 
CPP_OBJS=.\Debug/
CPP_SBRS=.\Debug/

.c{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_OBJS)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(CPP_SBRS)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/nologo /D "_DEBUG" /mktyplib203 /o NUL /win32 
RSC=rc.exe
RSC_PROJ=/l 0x410 /fo"$(INTDIR)\LgConcil.res" /d "_DEBUG" /d "_AFXDLL" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\LgConcil.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\AlarmDlg.sbr" \
	"$(INTDIR)\LgConcil.sbr" \
	"$(INTDIR)\LgConcilDlg.sbr" \
	"$(INTDIR)\ParamDlg.sbr" \
	"$(INTDIR)\StdAfx.sbr" \
	"$(INTDIR)\WNDlg.sbr"

"$(OUTDIR)\LgConcil.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=/nologo /subsystem:windows /incremental:yes\
 /pdb:"$(OUTDIR)\LgConcil.pdb" /debug /machine:I386\
 /out:"$(OUTDIR)\LgConcil.exe" /pdbtype:sept 
LINK32_OBJS= \
	"$(INTDIR)\AlarmDlg.obj" \
	"$(INTDIR)\LgConcil.obj" \
	"$(INTDIR)\LgConcil.res" \
	"$(INTDIR)\LgConcilDlg.obj" \
	"$(INTDIR)\ParamDlg.obj" \
	"$(INTDIR)\StdAfx.obj" \
	"$(INTDIR)\WNDlg.obj"

"$(OUTDIR)\LgConcil.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(CFG)" == "LgConcil - Win32 Release" || "$(CFG)" ==\
 "LgConcil - Win32 Debug"
SOURCE=.\AlarmDlg.cpp

!IF  "$(CFG)" == "LgConcil - Win32 Release"

DEP_CPP_ALARM=\
	".\AlarmDlg.h"\
	".\LgConcil.h"\
	".\LgConcilDlg.h"\
	

"$(INTDIR)\AlarmDlg.obj"	"$(INTDIR)\AlarmDlg.sbr" : $(SOURCE) $(DEP_CPP_ALARM)\
 "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


!ELSEIF  "$(CFG)" == "LgConcil - Win32 Debug"

DEP_CPP_ALARM=\
	".\AlarmDlg.h"\
	".\LgConcil.h"\
	".\LgConcilDlg.h"\
	

"$(INTDIR)\AlarmDlg.obj"	"$(INTDIR)\AlarmDlg.sbr" : $(SOURCE) $(DEP_CPP_ALARM)\
 "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


!ENDIF 

SOURCE=.\LgConcil.cpp
DEP_CPP_LGCON=\
	".\LgConcil.h"\
	".\LgConcilDlg.h"\
	

"$(INTDIR)\LgConcil.obj"	"$(INTDIR)\LgConcil.sbr" : $(SOURCE) $(DEP_CPP_LGCON)\
 "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


SOURCE=.\LgConcil.rc
DEP_RSC_LGCONC=\
	".\res\alarm.ico"\
	".\res\freeze.ico"\
	".\res\graph.ico"\
	".\res\ico00001.ico"\
	".\res\icon1.ico"\
	".\res\init.ico"\
	".\res\LgConcil.ico"\
	".\res\LgConcil.rc2"\
	".\res\pert.ico"\
	".\res\run.ico"\
	".\res\stop.ico"\
	

"$(INTDIR)\LgConcil.res" : $(SOURCE) $(DEP_RSC_LGCONC) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\LgConcilDlg.cpp

!IF  "$(CFG)" == "LgConcil - Win32 Release"

DEP_CPP_LGCONCI=\
	".\AlarmDlg.h"\
	".\application.h"\
	".\LgConcil.h"\
	".\LgConcilDlg.h"\
	".\ParamDlg.h"\
	".\WNDlg.h"\
	

"$(INTDIR)\LgConcilDlg.obj"	"$(INTDIR)\LgConcilDlg.sbr" : $(SOURCE)\
 $(DEP_CPP_LGCONCI) "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


!ELSEIF  "$(CFG)" == "LgConcil - Win32 Debug"

DEP_CPP_LGCONCI=\
	".\AlarmDlg.h"\
	".\application.h"\
	".\LgConcil.h"\
	".\LgConcilDlg.h"\
	".\ParamDlg.h"\
	".\WNDlg.h"\
	

"$(INTDIR)\LgConcilDlg.obj"	"$(INTDIR)\LgConcilDlg.sbr" : $(SOURCE)\
 $(DEP_CPP_LGCONCI) "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


!ENDIF 

SOURCE=.\ParamDlg.cpp
DEP_CPP_PARAM=\
	".\LgConcil.h"\
	".\ParamDlg.h"\
	

"$(INTDIR)\ParamDlg.obj"	"$(INTDIR)\ParamDlg.sbr" : $(SOURCE) $(DEP_CPP_PARAM)\
 "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


SOURCE=.\StdAfx.cpp
DEP_CPP_STDAF=\
	".\StdAfx.h"\
	

!IF  "$(CFG)" == "LgConcil - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS"\
 /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LgConcil.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\"\
 /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LgConcil.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "LgConcil - Win32 Debug"

CPP_SWITCHES=/nologo /MDd /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D\
 "_WINDOWS" /D "_AFXDLL" /FR"$(INTDIR)\\" /Fp"$(INTDIR)\LgConcil.pch"\
 /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\StdAfx.obj"	"$(INTDIR)\StdAfx.sbr"	"$(INTDIR)\LgConcil.pch" : \
$(SOURCE) $(DEP_CPP_STDAF) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\WNDlg.cpp

!IF  "$(CFG)" == "LgConcil - Win32 Release"

DEP_CPP_WNDLG=\
	".\LgConcil.h"\
	".\LgConcilDlg.h"\
	".\wn_externals.h"\
	".\WNDlg.h"\
	

"$(INTDIR)\WNDlg.obj"	"$(INTDIR)\WNDlg.sbr" : $(SOURCE) $(DEP_CPP_WNDLG)\
 "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


!ELSEIF  "$(CFG)" == "LgConcil - Win32 Debug"

DEP_CPP_WNDLG=\
	".\LgConcil.h"\
	".\LgConcilDlg.h"\
	".\wn_externals.h"\
	".\WNDlg.h"\
	

"$(INTDIR)\WNDlg.obj"	"$(INTDIR)\WNDlg.sbr" : $(SOURCE) $(DEP_CPP_WNDLG)\
 "$(INTDIR)" "$(INTDIR)\LgConcil.pch"


!ENDIF 


!ENDIF 

