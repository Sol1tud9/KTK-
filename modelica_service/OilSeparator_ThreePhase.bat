@echo off
SET PATH=;C:/Program Files/OpenModelica1.24.4-64bit/bin/;%PATH%;
SET ERRORLEVEL=
CALL "%CD%/OilSeparator_ThreePhase.exe" %*
SET RESULT=%ERRORLEVEL%

EXIT /b %RESULT%
