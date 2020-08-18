CALL __environment.bat

REM Eventuell verbundenes Netzlaufwerk trennen
NET USE %TOOLS_DRIVE% /delete /yes
NET USE %EXT_LIBS_DRIVE% /delete /yes
NET USE %PROJ_DRIVE% /delete /yes
NET USE %COMPILLER_DRIVE% /delete /yes

REM Eventuell substituiertes Laufwerk trennen
SUBST %TOOLS_DRIVE% /d
SUBST %EXT_LIBS_DRIVE% /d
SUBST %PROJ_DRIVE% /d
SUBST %COMPILLER_DRIVE% /d

REM %EXT_LIBS_DRIVE% als Laufwerk von %PATH_TO_EXT_LIBS% substituieren
SUBST %TOOLS_DRIVE% %PATH_TO_TOOLS%
SUBST %EXT_LIBS_DRIVE% %PATH_TO_EXT_LIBS%
SUBST %PROJ_DRIVE% ..\..
SUBST %COMPILLER_DRIVE% %PATH_TO_COMPILLER%