@echo off
powershell -ExecutionPolicy Bypass -File "%~dp0run_atomic_experiments.ps1" %*
exit /b %ERRORLEVEL%
