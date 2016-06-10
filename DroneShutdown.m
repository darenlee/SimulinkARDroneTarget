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

%% remove the paths that are outside of the Simulink Project Path
rmpath([pwd '\Docs']); 
rmpath([pwd '\\AR_Drone_Models\Calibration_Models']);
rmpath([pwd '\\AR_Drone_Models\Calibration_Models\GUI_Source']);

%% reset build folder
set_param(0, 'CacheFolder', '');
set_param(0, 'CodeGenFolder', '');

bdclose all;
close all;
clear all;
clc;