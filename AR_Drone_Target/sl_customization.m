% Copyright 2014 The MathWorks, Inc.
function sl_customization(cm)
%SL_CUSTOMIZATION Register individual targets with Coder Target
 
% Copyright 2013 The MathWorks, Inc.
 
cm.registerTargetRegistry(@loc_registerThisTarget);
cm.registerTargetBoardRegistry(@loc_registerBoardsForThisTarget);
cm.registerTargetInfo(@loc_createPILConfig);
end
 
% -------------------------------------------------------------------------
function ret = loc_registerThisTarget()
ret.Name = 'ARM Cortex-A AR Drone';
[targetFilePath, ~, ~] = fileparts(mfilename('fullpath'));
ret.TargetFolder = targetFilePath;
end
 
% -------------------------------------------------------------------------
function boardInfo = loc_registerBoardsForThisTarget()
target = 'ARM Cortex-A';
[targetFolder, ~, ~] = fileparts(mfilename('fullpath'));
boardFolder = codertarget.target.getTargetHardwareRegistryFolder(targetFolder);
boardInfo = codertarget.target.getTargetHardwareInfo(targetFolder, boardFolder, target);
end

%% ------------------------------------------------------------------------
function config = loc_createPILConfig
config(1) = rtw.connectivity.ConfigRegistry;
config(1).ConfigName = 'AR Drone 2 - Thread Timer Scheduler';
config(1).ConfigClass = 'codertarget.arm_cortex_a_drone.pil.ConnectivityConfig';
config(1).isConfigSetCompatibleFcn = @i_isConfigSetCompatible;
end
 
%% ------------------------------------------------------------------------
function isConfigSetCompatible = i_isConfigSetCompatible(configSet)
isConfigSetCompatible = false;
if configSet.isValidParam('CoderTargetData')
    data = configSet.getParam('CoderTargetData');
    isConfigSetCompatible = isequal(data.TargetHardware, ...
        'AR Drone 2 - Thread Timer Scheduler');
end
end