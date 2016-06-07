function onAfterCodeGen(hCS, buildInfo)
%ONAFTERCODEGEN Hook point for after code generation

%   Copyright 2013-2104 The MathWorks, Inc.

if ~isequal(get_param(hCS, 'PositivePriorityOrder'), 'on')
	error('You have probably recently updated your AR Drone 2.0 Coder Target with the new UDP blocks. A new change has been made in which your model must have High Priority Value Indicates High Priority Task enabled in the solver configuration. Turn this setting on and rebuild again');
    error(message('arm_cortex_a:utils:WrongPriorityOrder'));
	
end

data = codertarget.data.getData(hCS);
%% Replace host-specific UDP block files with target-specific ones
fileToFind = fullfile('$(MATLAB_ROOT)','toolbox','shared','dspblks','extern','src','HostLib_Network.c');
found = loc_findInBuildInfoSrc(buildInfo, fileToFind);
if ~isempty(found)
    rootDir = find_folder();
    filePathToAdd = fullfile(rootDir,'src');
    fileNameToAdd = 'linuxUDP.c';
    buildInfo.addSourceFiles(fileNameToAdd, filePathToAdd);
    buildInfo.addDefines('_USE_TARGET_UDP_');
    buildInfo.addLinkFlags('-ldl');
end

%% Check for Target-Hardware Build action and start QEMU
if isequal(data.TargetHardware, 'ARM Cortex-A9 (QEMU)')
    if isfield(data.Runtime, 'BuildAction') && ...
            isequal(data.Runtime.BuildAction, 'Build, load, and run')
        codertarget.arm_cortex_a.runQemu();
    end
end
end

%--------------------------------------------------------------------------
function found = loc_findInBuildInfoSrc(buildInfo, filename)
filename = strrep(filename, '$(MATLAB_ROOT)', matlabroot);
found = [];
for j=1:length(buildInfo.Src.Files)
    iFile = fullfile(buildInfo.Src.Files(j).Path, buildInfo.Src.Files(j).FileName);
    iFile = strrep(iFile, '$(MATLAB_ROOT)', matlabroot);
    if ~isempty(strfind(iFile, filename))
        found = iFile;
        break;
    end
end
end
function str = find_folder()

% s = path;
% [~,endIn] = regexp(s,'AR_Drone');
% index = endIn(1);
% while(s(index)~=';'&&index>0)
%     if(index == endIn(1))
%         str = s(index);
%     else
%      str = strcat(str,s(index));
%     end
%     index = index-1;
% end
% 
% str = fliplr(str);
AR_Drone_CustomTarget_path = which('AR_Drone_2_Library');

str = AR_Drone_CustomTarget_path(1:(end-29));
%this is a complete hack but it had to be done..issue is that with
%this new UDP block check, it needs to find the AR_Drone\Src folder
%relative to where the library block is, it will always be here

end
