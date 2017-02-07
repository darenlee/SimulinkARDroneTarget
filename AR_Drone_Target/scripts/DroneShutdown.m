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

%% reset build folder
set_param(0, 'CacheFolder', '');
set_param(0, 'CodeGenFolder', '');

bdclose all;
close all;
clear all;
clc;