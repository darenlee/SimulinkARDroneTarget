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

%% Check if the compiler has been registered
if exist('../registry/thirdpartytools/thirdpartytools_win32.xml','file') == 0 || ...
        exist('../registry/thirdpartytools/thirdpartytools_win64.xml','file') == 0
    disp('No third party compiler has been registered for the AR Drone, running install script')
    showDoc = 1; % guess that since the compiler was not registered yet you will want to see the documentation
   run('install_script.m') 
end

%% Check if TargetRegistry has been set
if exist('../registry/gcc_codesourcery_arm_linux_gnueabihf_gmake_win64_v4_8.mat','file') == 0
    disp('No toolchain info mat file was found for use with rtwTargetInfo.m, generating the gcc_codesourcery_arm_linux_gnueabihf_gmake_win64 mat file')
    run('../registry/generateTargetInfoMatFile.m');  % create the mat file containing the toolchain info
    RTW.TargetRegistry.getInstance('reset');         % reset the TargetRegistry such that rtwTargetInfo.m is called when a model is made for the first time
end    

%% register the compiler
sl_refresh_customizations;

%% Compile the video library if needed
if exist('../blocks/videolib/AR_Drone_Video.slx','file') == 0
    disp('No video library has been found, starting compilation of the video library using the Legacy Code Tool')
   run('../blocks/videolib/Generate_AR_Drone_Video.m')
end

%% Create the s functions for the AR_Drone_Library blocks
if exist('../blocks/rtwmakecfg.m','file') == 0 % the rtwmakecfg.m is created at the very end of Generate_AR_Drone_S_Functions
    disp('No rtwmakecfg found for the blocks, running Generate_AR_Drone_S_Functions')
   run('../blocks/Generate_AR_Drone_S_Functions.m')
end

%% set build folder
if exist(['../../Build'],'dir') == 0
    mkdir('../../Build')
end
set_param(0, 'CacheFolder', ['../../Build']);
set_param(0, 'CodeGenFolder', ['../../Build']);

%% show the documentation
if showDoc == 1
    open('Docs\html\ARDrone2Toolbox.html');
end

%% clean up
clear all;




