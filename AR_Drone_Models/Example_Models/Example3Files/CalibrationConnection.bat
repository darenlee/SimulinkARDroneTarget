@ ECHO OFF

REM Passing the "&" option together with extra inputs can give issues, so load the matlab path from an external file instead of having it passed
SET /p MATLABROOT=<AR_Drone_Models\Example_Models\Example3Files\matlabroot.txt

REM Create the full path to plink
SET PLINK_EXE=%MATLABROOT%\toolbox\idelink\foundation\hostapps\plink.exe

REM Write the required commands to execute on the drone to a different file
echo cd update > AR_Drone_Models\Example_Models\Example3Files\sshCommands.txt
echo ./Example3_Calibrating_The_AR_Drone_Model.elf -w >> AR_Drone_Models\Example_Models\Example3Files\sshCommands.txt

REM execute the commands on the drone
"%PLINK_EXE%" -telnet -P 23 192.168.1.1 < AR_Drone_Models\Example_Models\Example3Files\sshCommands.txt