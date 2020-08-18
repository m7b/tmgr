@ECHO OFF

REM Extend search path for this batch file
SET PATH=%PATH%;Z:\bin

SET PATH_TO_WXWIDGETS=W:\wxWidgets-3.0.5.1

W:
CD %PATH_TO_WXWIDGETS%\build\msw

GOTO BUILD_DEBUG

:BUILD_DEBUG
TITLE *** build wxwidgets debug
mingw32-make -j1 -f makefile.gcc BUILD=debug   SHARED=0 UNICODE=1 CXXFLAGS="-g -static -mthreads -pipe -Wall -O0 -DwxDEBUG_LEVEL=1" setup_h
mingw32-make -j9 -f makefile.gcc BUILD=debug   SHARED=0 UNICODE=1 CXXFLAGS="-g -static -mthreads -pipe -Wall -O0 -DwxDEBUG_LEVEL=1"

:BUILD_RELEASE
TITLE *** build wxwidgets release
mingw32-make -j1 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 CXXFLAGS="-static -mthreads -pipe -Wall -Ofast -mfpmath=sse -funroll-loops -s -DwxDEBUG_LEVEL=0" clean
mingw32-make -j1 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 CXXFLAGS="-static -mthreads -pipe -Wall -Ofast -mfpmath=sse -funroll-loops -s -DwxDEBUG_LEVEL=0" setup_h
mingw32-make -j9 -f makefile.gcc BUILD=release SHARED=0 UNICODE=1 CXXFLAGS="-static -mthreads -pipe -Wall -Ofast -mfpmath=sse -funroll-loops -s -DwxDEBUG_LEVEL=0"

::TITLE *** build wxwidgets samples
::CD %PATH_TO_WXWIDGETS%\samples
::mingw32-make -j1 -f makefile.gcc

GOTO FINISHED

:ERROR
ECHO *** ERROR
PAUSE

:FINISHED
ECHO *** FINISHED
PAUSE