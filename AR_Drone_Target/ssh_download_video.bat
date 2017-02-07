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

SET NLM=^

SET NL=^^^%NLM%%NLM%^%NLM%%NLM%

ECHO Removing old binaries
echo killall -9 program.elf.respawner.sh; killall -9 program.elf; killall -9 gst-launch-0.10; killall -9 %EXE_NAME%;  killall -9 gst-launch-0.10; exit > generated_cmds_del.txt
"%PLINK_EXE%" -telnet -P 23 %HOSTNAME% < generated_cmds_del.txt

ECHO WinSCP FTP Uploading Drone ELF File to port %AR_DRONE_IP_ADDRESS%:5551

echo open ftp://anonymous@%AR_DRONE_IP_ADDRESS%:5551/ -passive=on > %EXE_PATH%upload_script.txt
echo put "%EXE_PATH%%EXE_NAME%" ./ >> %EXE_PATH%upload_script.txt
echo put "%EXE_PATH%video_script.sh" ./ >> %EXE_PATH%upload_script.txt
echo exit >> %EXE_PATH%upload_script.txt
rem "C:\Program Files (x86)\WinSCP\WinSCP.com" /log="%EXE_PATH%ftp.log" /script="%EXE_PATH%upload_script.txt"
"C:\Program Files (x86)\WinSCP\WinSCP.com" /script="%EXE_PATH%upload_script.txt"

ECHO Telneting into AR Drone 2.0 and running executable

rem this functions but its annoying, this was the old way, it piped stuff to the diagonstic window
rem echo cd update;chmod 777 %EXE_NAME%;./%EXE_NAME% | "%PLINK_EXE%" -telnet -P 23 %HOSTNAME% 

ECHO Creating temporary txt file for running commands remotely
rem echo cd update;chmod 777 %EXE_NAME%; > generated_cmds.txt

echo cd /bin ; ./basescript.sh ; cd /update; chmod 777 video_script.sh; ./video_script.sh; chmod 777 %EXE_NAME%; ./%EXE_NAME% -w > generated_cmds.txt

ECHO Creating temporary batch script for PLINK commands
echo "%PLINK_EXE%" -telnet -P 23 %HOSTNAME% ^< generated_cmds.txt > generated_batch.bat

ECHO Running model %EXE_NAME% on AR Drone 2.0
start "AR Drone 2.0 Console Window"  generated_batch.bat



ECHO Deleting Generated Batch Files
rem del generated_batch.bat
rem del generated_cmds.txt

REM [END OF FILE]

