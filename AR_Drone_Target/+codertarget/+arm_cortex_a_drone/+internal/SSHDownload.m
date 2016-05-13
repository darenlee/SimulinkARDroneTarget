function SSHDownload(varargin)
%SSHDOWNLOAD Summary of this function goes here
%   Detailed explanation goes here

disp('Setting up FTP Connection with the AR Drone');
droneFtp = ftp('192.168.1.1:5551','root','root');

fileName = char(varargin(2));
fileName = fileName(4:end); % remove ../
disp(['Uploading ' fileName ' to the AR Drone']);
mput(droneFtp,char(varargin(2)));

disp('Opening TPCIP connection with the AR Drone');
droneTcpip = tcpip('192.168.1.1',23);
fopen(droneTcpip);

disp(['Killing any instances of Program.elf or previously running ' fileName]);
query(droneTcpip,'killall -9 program.elf.respawner.sh');
query(droneTcpip,'killall -9 program.elf');
query(droneTcpip,['killall -9' fileName]);

disp('Starting the program on the AR Drone');
query(droneTcpip,['chmod 777 /update/' fileName]);
query(droneTcpip,['./update/' fileName ' -w']);
end


