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

if exist('AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win32.xml','file') == 0 || ...
        exist('AR_Drone_Target/registry/thirdpartytools/thirdpartytools_win64.xml','file') == 0
    disp('No third party compiler has been registered for the AR Drone, running install script')
   run('AR_Drone_Target/install_script.m') 
end

%% Check if TargetRegistry has been set
if exist('AR_Drone_Target/registry/gcc_codesourcery_arm_linux_gnueabihf_gmake_win64_v4_8.mat','file') == 0
    disp('No toolchain info mat file was found for use with rtwTargetInfo.m, generating the gcc_codesourcery_arm_linux_gnueabihf_gmake_win64 mat file')
    run('AR_Drone_Target\registry\generateTargetInfoMatFile.m');  % create the mat file containing the toolchain info
    RTW.TargetRegistry.getInstance('reset');         % reset the TargetRegistry such that rtwTargetInfo.m is called when a model is made for the first time
end    

%% register the compiler
sl_refresh_customizations;

%% Compile the video library if needed

if exist('AR_Drone_Target/blocks/videolib/AR_Drone_Video.slx','file') == 0
    disp('No video library has been found, starting compilation of the video library using the Legacy Code Tool')
   run('AR_Drone_Target/blocks/videolib/Generate_AR_Drone_Video.m')
end

%% Create the s functions for the AR_Drone_Library blocks

if exist('AR_Drone_Target/blocks/rtwmakecfg.m','file') == 0 % the rtwmakecfg.m is created at the very end of Generate_AR_Drone_S_Functions
    disp('No rtwmakecfg found for the blocks, running Generate_AR_Drone_S_Functions')
   run('AR_Drone_Target/blocks/Generate_AR_Drone_S_Functions.m')
end

%% update paths 

addpath([pwd '\Docs']); % include the documentation

%% set build folder
if exist(fullfile(pwd,'Build'),'dir') == 0
    mkdir('Build')
end
set_param(0, 'CacheFolder', fullfile(pwd,'Build'));
set_param(0, 'CodeGenFolder', fullfile(pwd,'Build'));




