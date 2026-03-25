@echo off
powershell -ExecutionPolicy Bypass -File "%~dp0run_top_experiments.ps1" %*
exit /b %ERRORLEVEL%
