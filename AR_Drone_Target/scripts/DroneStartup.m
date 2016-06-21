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

%% Guess whether the user would want to see the documentation at startup
showDoc = 0;

%% Find the base folder since different MATLAB versions execute and find files differently
baseFolder = which('AR_Drone.prj');
if isequal(baseFolder,'')
   h = errormsg('Cannot locate AR_Drone.prj which is used as a reference to find the base project folder') ;
end
baseFolder = baseFolder(1:end-13); % remove /README.md

%% Running a script in a sub folder changes the cd in some MATLAB versions but not all, so we allways go back to baseFolder
while size(pwd,1) > size(baseFolder,1)
    cd ..
end

%% Check if the compiler has been registered
if exist([baseFolder '/AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win32.xml'],'file') == 0 || ...
        exist([baseFolder '/AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win64.xml'],'file') == 0
    disp('No third party compiler has been registered for the AR Drone, running install script')
    showDoc = 1; % guess that since the compiler was not registered yet you will want to see the documentation
    cd AR_Drone_Target/scripts/
    run('install_script.m') 
    % install script resets cd to baseFolder
end

%% Check if TargetRegistry has been set
if exist([baseFolder '/AR_Drone_Target/registry/gcc_codesourcery_arm_linux_gnueabihf_gmake_win64_v4_8.mat'],'file') == 0
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
if exist([baseFolder '/AR_Drone_Target/blocks/videolib/AR_Drone_Video.slx'],'file') == 0
    disp('No video library has been found, starting compilation of the video library using the Legacy Code Tool')
    cd AR_Drone_Target/blocks/videolib
    run('Generate_AR_Drone_Video.m')
    cd ../../..
end

%% Create the s functions for the AR_Drone_Library blocks
if exist([baseFolder '/AR_Drone_Target/blocks/rtwmakecfg.m'],'file') == 0 % the rtwmakecfg.m is created at the very end of Generate_AR_Drone_S_Functions
    disp('No rtwmakecfg found for the blocks, running Generate_AR_Drone_S_Functions')
    cd AR_Drone_Target/blocks
   run('Generate_AR_Drone_S_Functions.m')
   cd ../..
end

%% set build folder
if exist([baseFolder '/Build'],'dir') == 0
    disp('Creating build folder')
    mkdir([baseFolder '/Build'])
end
set_param(0, 'CacheFolder', [baseFolder '/Build']);
set_param(0, 'CodeGenFolder', [baseFolder '/Build']);

%% show the documentation
if showDoc == 1
    open([baseFolder '/Docs/html/ARDrone2Toolbox.html']);
end

%% clean up
clear all;




