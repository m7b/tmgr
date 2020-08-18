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