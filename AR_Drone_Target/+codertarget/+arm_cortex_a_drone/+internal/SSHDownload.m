function SSHDownload(varargin)
%SSHDOWNLOAD is used to upload the model compiled for the ARM AR Drone target to the AR Drone 2.0 and execute it 

%% Retrieve the IP
fileName = char(varargin(2));
fileName = fileName(4:end); % remove ../
modelName = fileName(1: end - 4); %remove .elf

hCs = getActiveConfigSet(modelName);
data = hCs.get_param('CoderTargetData');
IP = data.IP;

disp(['Setting up FTP Connection with the AR Drone at IP adress: ' IP ':5551']);
droneFtp = ftp([IP ':5551'],'root','root');

disp(['Uploading ' fileName ' to the AR Drone']);
%Delete any older versions of the program on the drone because mput does
%not overwrite files
try
    delete(droneFtp,fileName);
catch
end

% copy the executable to the drone
mput(droneFtp,which(fileName));

disp('Opening TPCIP connection with the AR Drone');
droneTcpip = tcpip(IP,23);
fopen(droneTcpip);


disp(['Killing any instances of Program.elf or previously running ' fileName]);
query(droneTcpip,'killall -9 program.elf.respawner.sh');
query(droneTcpip,'killall -9 program.elf');
query(droneTcpip,['killall -9 ' fileName]);

disp('Starting the program on the AR Drone');
query(droneTcpip,['chmod 777 /update/' fileName]);

outputFileName = [fileName(1:end-4) '.txt']; %create a file to save the terminal output to
query(droneTcpip,['./update/' fileName ' -w > /update/' outputFileName]);
end


