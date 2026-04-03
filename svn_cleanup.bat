@echo off
setlocal

rem this batch file is used to svn cleanup new build version info to subverison
if "%OS%"=="Windows_NT" goto nt
echo This script only works with NT-based versions of Windows.
goto :eof

:nt
rem go to D: drive as Jenkins workspace on D:
D:
rem %~dp0 is location of current script under NT
rem echo %~dp0
cd %~dp0
"C:\Program Files\TortoiseSVN\bin\svn" update
"C:\Program Files\TortoiseSVN\bin\svn" cleanup

goto :eof