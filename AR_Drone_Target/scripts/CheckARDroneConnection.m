%% CheckARDroneConnection.m Verifies whether the AR Drone is connected to this computer using the IP specified in the AR_Drone_ConfigSet Configuration Set

%% Retrieve the IP
dict = Simulink.data.dictionary.open('ArDroneDataDictionary.sldd');
data = getSection(dict,'Configurations');
configEntry = getEntry(data,'AR_Drone_ConfigSet');
config = getValue(configEntry);
coderTargetData = config.get_param('CoderTargetData');
IP = coderTargetData.IP;

%% Set up a telnet connection
droneTcpip = tcpip(IP,23);

success = 1;
try
    fopen(droneTcpip);
catch
    h = msgbox(['Unable to establish a tcpip connection with the AR Drone at ' IP ':23']);
    success = 0;
end
%% Connection OK

if success == 1
    h = msgbox(['Successfully established a tcpip connection with the AR Drone at ' IP ':23']);
end

%% clean up variables
clear dict data configEntry config coderTargetData IP droneTcpip success fopen h;