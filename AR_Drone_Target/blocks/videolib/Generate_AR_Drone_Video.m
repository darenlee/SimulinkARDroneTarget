%% Setting library and blocks names
clc

currentDir = pwd;

lib_name = 'AR_Drone_Video';
frontCamBlockName = 'AR_Drone_Front_Camera';
botCamBlockName = 'AR_Drone_Bottom_Camera';
if exist(lib_name, 'file')
	load_system(lib_name);
	set_param(lib_name, 'Lock', 'off')
	try
	delete_block([lib_name, '/', frontCamBlockName]);
	delete_block([lib_name, '/', botCamBlockName]);
	catch
	end
else
	new_system(lib_name, 'Library');
	load_system(lib_name);
end

%% ARdrone_video1_dev_block
frontCamSimDef = legacy_code('initialize');
frontCamSimDef.SFunctionName = frontCamBlockName;
frontCamSimDef.StartFcnSpec =		'void videoInit1(void)';
frontCamSimDef.OutputFcnSpec =		'videoGrabImage1(uint8 y1[1843200])';

frontCamSimDef.TerminateFcnSpec =	'void videoClose1(void)';
frontCamSimDef.SampleTime = 'parameterized';
frontCamSimDef.SourceFiles =  {'video.c'};
frontCamSimDef.HeaderFiles = {'video.h'};

% Add necesarry specification to definition for code generation purpose
frontCamCodeDef = frontCamSimDef;
frontCamCodeDef.IncPaths = ...
	{currentDir,...
     '.'};
frontCamCodeDef.SrcPaths = ...
	{currentDir,...
	 '.'};
frontCamCodeDef.SourceFiles = ...
	{'video.c'};

%% ARdrone_video2_dev_block
botCamSimDef = legacy_code('initialize');
botCamSimDef.SFunctionName = botCamBlockName;
botCamSimDef.StartFcnSpec =		'void videoInit2(void)';
botCamSimDef.OutputFcnSpec =		'videoGrabImage2(uint8 y1[153600])';

botCamSimDef.TerminateFcnSpec =	'void videoClose2(void)';
botCamSimDef.SampleTime = 'parameterized';
botCamSimDef.SourceFiles =  {'video.c'};
botCamSimDef.HeaderFiles = {'video.h'};

% Add necesarry specification to definition for code generation purpose
botCamCodeDef = botCamSimDef;
botCamCodeDef.IncPaths = ...
	{currentDir,...
     '.'};
botCamCodeDef.SrcPaths = ...
	{currentDir,...
	 '.'};
botCamCodeDef.SourceFiles = ...
	{'video.c'};

%% Generate S-funktions, tls files and rtwmakecfg file
def_sim = [frontCamSimDef(:); botCamSimDef(:)];
def_codegen = [frontCamCodeDef(:); botCamCodeDef(:)];
legacy_code('sfcn_cmex_generate', def_sim)
legacy_code('compile', def_sim)
legacy_code('slblock_generate',def_codegen, lib_name);
legacy_code('sfcn_tlc_generate', def_codegen)
legacy_code('rtwmakecfg_generate', def_codegen)


%% Save and exit

set_param([lib_name '/' frontCamBlockName],'ShowSpec','off')
set_param([lib_name '/' botCamBlockName],'ShowSpec','off')
set_param([lib_name '/' frontCamBlockName],'SampleTime','0.1')
set_param([lib_name '/' botCamBlockName],'SampleTime','0.1')
set_param(lib_name, 'EnableLBRepository','on');
set_param(lib_name, 'Lock', 'on');

save_system(lib_name);

% EOF