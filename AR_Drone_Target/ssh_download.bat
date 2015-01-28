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

ECHO Windows FTP Uploading Drone ELF File to port %AR_DRONE_IP_ADDRESS%:5551

echo open %AR_DRONE_IP_ADDRESS% 5551>> ftpcmd.dat
echo user>> ftpcmd.dat
echo put "%EXE_PATH%%EXE_NAME%">> ftpcmd.dat
echo disconnect >>ftpcmd.dat
echo quit>> ftpcmd.dat
echo Connecting to FTP and uploading binary
ftp -s:ftpcmd.dat 
echo Done Uploading
del ftpcmd.dat


ECHO Telneting into AR Drone 2.0 and running executable

rem this functions but its annoying, this was the old way, it piped stuff to the diagonstic window
rem echo cd update;chmod 777 %EXE_NAME%;./%EXE_NAME% | "%PLINK_EXE%" -telnet -P 23 %HOSTNAME% 



ECHO Creating temporary txt file for running commands remotely
rem echo cd update;chmod 777 %EXE_NAME%; > generated_cmds.txt
echo cd update;chmod 777 %EXE_NAME%;./%EXE_NAME% -w> generated_cmds.txt

ECHO Creating temporary batch script for PLINK commands
echo "%PLINK_EXE%" -telnet -P 23 %HOSTNAME% ^< generated_cmds.txt > generated_batch.bat

ECHO Running model %EXE_NAME% on AR Drone 2.0
start "AR Drone 2.0 Console Window"  generated_batch.bat

ECHO Deleting Generated Batch Files
rem del generated_batch.bat
rem del generated_cmds.txt

REM [END OF FILE]

