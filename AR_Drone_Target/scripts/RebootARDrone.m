%% RebootARDrone.m Reboots the AR Drone connected to this computer using the IP specified in the AR_Drone_ConfigSet Configuration Set

%% Retrieve the IP
dict = Simulink.data.dictionary.open('ArDroneDataDictionary.sldd');
data = getSection(dict,'Configurations');
configEntry = getEntry(data,'AR_Drone_ConfigSet');
config = getValue(configEntry);
coderTargetData = config.get_param('CoderTargetData');
IP = coderTargetData.IP;

%% Set up a telnet connection
droneTcpip = tcpip(IP,23);
fopen(droneTcpip);

%% Reboot the drone
query(droneTcpip,'reboot');

disp('Send reboot command to the AR Drone 2.0.')
disp('Manually reconnect to the AR Drone 2 WIFI when the reboot finishes')