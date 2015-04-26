@echo off
cls

set DRIVE_LETTER=%1:
set PATH=%DRIVE_LETTER%\MinGW\bin;%DRIVE_LETTER%\MinGW\msys\1.0\bin;%DRIVE_LETTER%\MinGW\gtkmm3\bin;%DRIVE_LETTER%\MinGW\gtk\bin;c:\Windows;c:\Windows\system32
set PROJECT_PATH=.

make DRIVE_LETTER="%DRIVE_LETTER%" PROJECT_DIR="%PROJECT_PATH%"
