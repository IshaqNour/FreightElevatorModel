@echo off
setlocal

set "MAKE_EXE="

if exist "C:\msys64\ucrt64\bin\mingw32-make.exe" set "MAKE_EXE=C:\msys64\ucrt64\bin\mingw32-make.exe"
if not defined MAKE_EXE if exist "C:\msys64\mingw64\bin\mingw32-make.exe" set "MAKE_EXE=C:\msys64\mingw64\bin\mingw32-make.exe"
if not defined MAKE_EXE if exist "C:\msys64\clang64\bin\mingw32-make.exe" set "MAKE_EXE=C:\msys64\clang64\bin\mingw32-make.exe"
if not defined MAKE_EXE if exist "C:\msys64\ucrt64\bin\make.exe" set "MAKE_EXE=C:\msys64\ucrt64\bin\make.exe"
if not defined MAKE_EXE if exist "C:\msys64\mingw64\bin\make.exe" set "MAKE_EXE=C:\msys64\mingw64\bin\make.exe"
if not defined MAKE_EXE if exist "C:\msys64\clang64\bin\make.exe" set "MAKE_EXE=C:\msys64\clang64\bin\make.exe"

if not defined MAKE_EXE (
    echo Could not find an MSYS2 make executable under C:\msys64.
    echo Install MSYS2 with a gcc/make toolchain, then try again.
    exit /b 1
)

"%MAKE_EXE%" %*
exit /b %ERRORLEVEL%
