@ECHO OFF

SET PLINK_EXE=%~f1\plink.exe
ECHO "%PLINK_EXE%"

SET PSCP_EXE=%~f1\pscp.exe
ECHO "%PSCP_EXE%"

SET PASSWORD=%2
ECHO "%PASSWORD%"

SET USERNAME=%3
ECHO "%USERNAME%"

SET HOSTNAME=%4
ECHO "%HOSTNAME%"

SET REMOTE_DIR=%5
ECHO "%REMOTE_DIR%"

SET EXE_NAME=%~nx6
ECHO "%EXE_NAME%"

SET EXE_PATH=%~dp6
ECHO "%EXE_PATH%"

ECHO Removing old binaries
echo killall -9 program.elf.respawner.sh;killall -9 program.elf;killall -9 %EXE_NAME%;cd update;rm %EXE_NAME%;exit > generated_cmds_del.txt
"%PLINK_EXE%" -telnet -P 23 %HOSTNAME% < generated_cmds_del.txt

rem generated_cmds_del.txt

REM [END OF FILE]

