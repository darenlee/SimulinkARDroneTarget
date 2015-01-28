% Copyright 2014 The MathWorks, Inc.
function rtwTargetInfo(tr)
%RTWTARGETINFO Register toolchain
 
% Copyright 2013 The MathWorks, Inc.
tr.registerTargetInfo(@loc_createToolchain);
end

%--------------------------------------------------------------------------
function config = loc_createToolchain
rootDir = fileparts(mfilename('fullpath'));
config = coder.make.ToolchainInfoRegistry; % initialize
info = getARMCortexAInfo_CS();

if strcmpi(computer('arch'), 'win64')
    config(end).Name           = info.ToolChainName;
    config(end).Alias          = 'CODE_SOURCERY_GNU_ARM_LINUX_WIN64'; % internal use only
    config(end).FileName       = fullfile(rootDir, 'gcc_codesourcery_arm_linux_gnueabihf_gmake_win64_v4.8.mat');
    config(end).TargetHWDeviceType = {'*'};
    config(end).Platform           = {'win64'};
elseif strcmpi(computer('arch'), 'win32')
    config(end).Name           = info.ToolChainName;
    config(end).Alias          = 'CODE_SOURCERY_GNU_ARM_LINUX_WIN64'; % internal use only
    config(end).FileName       = fullfile(rootDir, 'gcc_codesourcery_arm_linux_gnueabihf_gmake_win32_v4.8.mat');
    config(end).TargetHWDeviceType = {'*'};
    config(end).Platform           = {'win32'};
end

end
% [EOF]
