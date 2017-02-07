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

%% If you do not want to see the documentation at startup, set this value to 0
showDoc = 1;

%% Find the base folder since different MATLAB versions execute and find files differently
% some versions will run this script from the simulink project folder,
% others from the folder it is in
currentFolder = pwd;
if isequal(currentFolder(end-6:end),'scripts') 
   cd ../.. 
end

%% Check if the compiler has been registered
if exist(['AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win32.xml'],'file') == 0 || ...
        exist(['AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win64.xml'],'file') == 0
    disp('No third party compiler has been registered for the AR Drone, running install script')
    cd AR_Drone_Target/scripts/
    run('install_script.m') 
    % install script resets cd to baseFolder
end

%% Check if TargetRegistry has been set
if exist(['AR_Drone_Target/registry/gcc_codesourcery_arm_linux_gnueabihf_gmake_win64_v4_8.mat'],'file') == 0
    disp('No toolchain info mat file was found for use with rtwTargetInfo.m, generating the gcc_codesourcery_arm_linux_gnueabihf_gmake_win64 mat file')
    % cd to the folder where the mat file should be put
    cd AR_Drone_Target/registry
    run('../registry/generateTargetInfoMatFile.m');  % create the mat file containing the toolchain info
    cd ../..
    RTW.TargetRegistry.getInstance('reset');         % reset the TargetRegistry such that rtwTargetInfo.m is called when a model is made for the first time
end    

%% register the compiler
sl_refresh_customizations;

%% Compile the video library if needed
if exist(['AR_Drone_Target/blocks/videolib/AR_Drone_Front_Camera.tlc'],'file') == 0 ||...
        exist(['AR_Drone_Target/blocks/videolib/AR_Drone_Bottom_Camera.tlc'],'file') == 0
    disp('No video source files were found, starting compilation of the video library using the Legacy Code Tool')
    cd AR_Drone_Target/blocks/videolib
    run('Generate_AR_Drone_Video.m')
    bdclose; % close the video lib it opens
    cd ../../..
end

%% Create the s functions for the AR_Drone_Library blocks
if exist(['AR_Drone_Target/blocks/rtwmakecfg.m'],'file') == 0 % the rtwmakecfg.m is created at the very end of Generate_AR_Drone_S_Functions
    disp('No rtwmakecfg found for the blocks, running Generate_AR_Drone_S_Functions')
    cd AR_Drone_Target/blocks
   run('Generate_AR_Drone_S_Functions.m')
   cd ../..
end

%% set build folder

if exist([pwd '/Build'],'dir') == 0
    disp('Creating build folder')
    mkdir(['Build'])
end
set_param(0, 'CacheFolder', ['Build']);
set_param(0, 'CodeGenFolder', ['Build']);

%% show the documentation

if showDoc == 1
    pause(0.1); % Give MATLAB some time to recognize updated path
    open('Docs/html/ARDrone2Target.html');
    open('AR_Drone_2_Library')
end

%% clean up
clear all;




