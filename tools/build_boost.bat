@ECHO OFF

REM Extend search path for this batch file
SET PATH=%PATH%;Z:\bin

SET PATH_TO_BOOST=W:\boost_1_73_0

REM Extend search path for this batch file
SET PATH=%PATH%;Z:\bin

REM libs/filesystem
REM libs/date_time

W:
CD %PATH_TO_BOOST%

:BUILD_B2
TITLE *** build b2
CALL bootstrap gcc
GOTO COPY_HEADER

:COPY_HEADER
TITLE *** copy header files
b2 headers
GOTO BUILD_LIBS

:BUILD_LIBS
TITLE *** build libs
b2 clean
b2 toolset=gcc address-model=64 --with-filesystem --with-date_time --with-test
GOTO FINISHED

:ERROR
ECHO *** ERROR
PAUSE

:FINISHED
ECHO *** FINISHED
PAUSE