@echo off
setlocal
pushd "%~dp0" || exit /b 1

wsl ./linux-x86-64-debug.sh

set "EXIT_CODE=%ERRORLEVEL%"
popd
exit /b %EXIT_CODE%
