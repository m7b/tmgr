set add=%1
if %add%$ ==$ set add="about:blank" && goto launch

rem http://
set test=%add:~0, 7%
if %test% == http:// goto launch

rem ftp:// 
set test=%add:~0, 6%
if %test% == ftp:// goto launch

rem https://
set test=%add:~0, 8%
if %test% == https:// goto launch

rem add http
set add=http://%add%

:launch
start microsoft-edge:%add%