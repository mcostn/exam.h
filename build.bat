@echo off
setlocal EnableExtensions

if not defined CFLAGS   set "CFLAGS=/nologo /W4 /std:c11 /I."
if not defined CXXFLAGS set "CXXFLAGS=/nologo /W4 /std:c++14 /EHsc /I."

set "C_EXAMPLES=01_basic 02_cli 03_manual 04_callbacks 05_long_names 07_custom_asserts"
set "OBJ=build\obj"

set "TARGET=%~1"
if "%TARGET%"=="" set "TARGET=all"

if /i "%TARGET%"=="clean" goto clean

where cl >nul 2>nul
if errorlevel 1 (
    echo error: cl.exe not found. Run from a Developer Command Prompt.
    exit /b 1
)

if /i "%TARGET%"=="all"      goto all
if /i "%TARGET%"=="examples" goto examples
if /i "%TARGET%"=="tests"    goto tests

echo usage: %~nx0 [all^|examples^|tests^|clean]
exit /b 1

:all
call :build_examples
if errorlevel 1 exit /b 1
call :build_tests
if errorlevel 1 exit /b 1
exit /b 0

:examples
call :build_examples
exit /b %errorlevel%

:tests
call :build_tests
exit /b %errorlevel%

:clean
del /q examples\*.exe tests\*.exe >nul 2>nul
if exist build rmdir /s /q build
exit /b 0

:build_examples
if not exist %OBJ% mkdir %OBJ%
for %%E in (%C_EXAMPLES%) do (
    call :build_c examples\%%E
    if errorlevel 1 exit /b 1
)
call :build_cpp examples\06_C++
exit /b %errorlevel%

:build_tests
if not exist %OBJ% mkdir %OBJ%
call :build_c tests\exam
exit /b %errorlevel%

:build_c
echo CL  %~1.c
cl %CFLAGS% /Fo%OBJ%\ /Fe%~1.exe %~1.c
exit /b %errorlevel%

:build_cpp
echo CL  %~1.cpp
cl %CXXFLAGS% /Fo%OBJ%\ /Fe%~1.exe %~1.cpp
exit /b %errorlevel%
