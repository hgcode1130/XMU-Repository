chcp 65001

@ECHO OFF&PUSHD %~DP0 &TITLE 厦门大学正版软件激活
@echo off
%1 mshta vbscript:CreateObject("Shell.Application").ShellExecute("cmd.exe","/c %~s0 ::","","runas",1)(window.close)&&exit
cd /d "%~dp0"

color 2F
echo.
echo.
echo.1.激活 Office 2013
echo.
echo.2.激活 Office 2010
echo.
echo.3.激活 Office 2016
echo.
echo.4.激活 Office 2019/2021
echo.
echo.5.激活 Windows
echo.
echo.
set KMS_Server=210.34.0.137
set KMS_Port=1688
set /p c=请输入数字并回车：
if %c%==1 goto 1
if %c%==2 goto 2
if %c%==3 goto 3
if %c%==4 goto 4
if %c%==5 goto 5
:office
setlocal EnableDelayedExpansion
reg query %strRegKey% >nul 2>nul
if %errorlevel%==0 (set strCurrentKey=%strRegKey%) else (set strCurrentKey=%strRegKey6432%)
for /f "delims=" %%i in ('reg query %strCurrentKey%') do (
set strInstPath=%%i
set strInstPath=!strInstPath:*REG_SZ=!
)
:LTrim
if "%strInstPath:~0,1%"==" " set "strInstPath=%strInstPath:~1%" && goto LTrim
:RTrim
if "%strInstPath:~-1%"==" " set "strInstPath=%strInstPath:~0,-1%" && goto RTrim
if "%strInstPath:~-1%" neq "\" set strInstPath=%strInstPath%\
echo office安装目录为%strInstPath%
cd /d %strInstPath%
cscript ospp.vbs /sethst:%KMS_Server%
cscript ospp.vbs /setprt:%KMS_Port%
cscript ospp.vbs /act
pause
exit

:1
set "strRegKey=HKEY_LOCAL_MACHINE\Software\Microsoft\Office\15.0\Common\InstallRoot /v Path"
set "strRegKey6432=HKEY_LOCAL_MACHINE\Software\Wow6432Node\Microsoft\Office\15.0\Common\InstallRoot /v Path"
goto office

:2
set "strRegKey=HKEY_LOCAL_MACHINE\Software\Microsoft\Office\14.0\Common\InstallRoot /v Path"
set "strRegKey6432=HKEY_LOCAL_MACHINE\Software\Wow6432Node\Microsoft\Office\14.0\Common\InstallRoot /v Path"
goto office

:3
set "strRegKey=HKEY_LOCAL_MACHINE\Software\Microsoft\Office\16.0\Common\InstallRoot /v Path"
set "strRegKey6432=HKEY_LOCAL_MACHINE\Software\Wow6432Node\Microsoft\Office\16.0\Common\InstallRoot /v Path"
goto office

:4
(if exist "%ProgramFiles%\Microsoft Office\Office16\ospp.vbs" cd /d "%ProgramFiles%\Microsoft Office\Office16")&(if exist "%ProgramFiles(x86)%\Microsoft Office\Office16\ospp.vbs" cd /d "%ProgramFiles(x86)%\Microsoft Office\Office16")&(for /f %%x in ('dir /b ..\root\Licenses16\ProPlus2019VL*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul)&(for /f %%x in ('dir /b ..\root\Licenses16\ProPlus2019VL_KMS*.xrm-ms') do cscript ospp.vbs /inslic:"..\root\Licenses16\%%x" >nul)
cscript //nologo ospp.vbs /unpkey:6MWKP >nul&cscript //nologo ospp.vbs /inpkey:NMMKJ-6RK4F-KMJVX-8D9MJ-6MWKP >nul
cscript ospp.vbs /sethst:%KMS_Server%
cscript ospp.vbs /setprt:%KMS_Port%
cscript ospp.vbs /act
pause
exit

:5
cscript "%SystemRoot%\system32\slmgr.vbs" /skms %KMS_Server%
cscript "%SystemRoot%\system32\slmgr.vbs" -ato
pause
exit