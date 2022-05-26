@echo off
set /p sdk= <PATH.txt
%sdk%\bin\make.exe %*
