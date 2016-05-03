% This script defines a project shortcut. 
%
% To get a handle to the current project use the following function:
%
% project = simulinkproject();
%
% You can use the fields of project to get information about the currently 
% loaded project. 
%
% See: help simulinkproject

%% Check if the compiler has been registered

if exist('AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win32.xml') == 0 || ...
        exist('AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win64.xml') == 0
    disp('No third party compiler has been registered for the AR Drone, running install script')
   run('AR_Drone_Target/install_script.m') 
end


%% Compile the video library if needed

if exist('AR_Drone_Target/blocks/videolib/ARdrone_video_lib.slx') == 0
    disp('No video library has been found, starting compilation of the video library using the Legacy Code Tool')
   run('AR_Drone_Target/blocks/videolib/ARdrone_legacy.m')
end

%% update paths of folders that are generated

addpath([pwd '\registry']);

sl_refresh_customizations;

%% Initialise the config

run('AR_Drone_Models\Flight_Models\AR_DRONE_SCRIPT.m')