@echo off
set /p option="[1] Release [2] Debug ~$ "
if %option% == 1 (gcc main.c -o azr)
if %option% == 2 (gcc -Wall -Wextra main.c -o azr)
if %option% GTR 2 (echo Error)
if %option% LSS 1 (echo Error)
@echo on
