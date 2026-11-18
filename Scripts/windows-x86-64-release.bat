@echo off
setlocal
pushd "%~dp0..\Source" || exit /b 1

cmake --workflow --preset windows-x86-64-release

set "EXIT_CODE=%ERRORLEVEL%"
popd
pause
exit /b %EXIT_CODE%
