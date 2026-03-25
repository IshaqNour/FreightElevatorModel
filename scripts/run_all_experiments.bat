@echo off
powershell -ExecutionPolicy Bypass -File "%~dp0run_all_experiments.ps1" %*
exit /b %ERRORLEVEL%
