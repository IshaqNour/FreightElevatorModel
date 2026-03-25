@echo off
powershell -ExecutionPolicy Bypass -File "%~dp0run_coupled_experiments.ps1" %*
exit /b %ERRORLEVEL%
