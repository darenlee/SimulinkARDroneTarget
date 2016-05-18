%% Setting library and blocks names
clc

currentDir = pwd;

lib_name = 'AR_Drone_Video';
dev_video1_block_name = 'AR_Drone_Front_Camera';
dev_video2_block_name = 'AR_Drone_Bottom_Camera';
if exist(lib_name, 'file')
	load_system(lib_name);
	set_param(lib_name, 'Lock', 'off')
	try
	delete_block([lib_name, '/', dev_video1_block_name]);
	delete_block([lib_name, '/', dev_video2_block_name]);
	catch
	end
else
	new_system(lib_name, 'Library');
	load_system(lib_name);
end

%% ARdrone_video1_dev_block
dev_video1_def_sim = legacy_code('initialize');
dev_video1_def_sim.SFunctionName = dev_video1_block_name;
dev_video1_def_sim.StartFcnSpec =		'void videoInit1(void)';
dev_video1_def_sim.OutputFcnSpec =		'videoGrabImage1(uint8 y1[1843200])';

dev_video1_def_sim.TerminateFcnSpec =	'void videoClose1(void)';
dev_video1_def_sim.SampleTime = 'parameterized';
dev_video1_def_sim.SourceFiles =  {'video.c'};
dev_video1_def_sim.HeaderFiles = {'video.h'};

% Add necesarry specification to definition for code generation purpose
dev_video1_def_codegen = dev_video1_def_sim;
dev_video1_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_video1_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_video1_def_codegen.SourceFiles = ...
	{'video.c'};

%% ARdrone_video2_dev_block
dev_video2_def_sim = legacy_code('initialize');
dev_video2_def_sim.SFunctionName = dev_video2_block_name;
dev_video2_def_sim.StartFcnSpec =		'void videoInit2(void)';
dev_video2_def_sim.OutputFcnSpec =		'videoGrabImage2(uint8 y1[153600])';

dev_video2_def_sim.TerminateFcnSpec =	'void videoClose2(void)';
dev_video2_def_sim.SampleTime = 'parameterized';
dev_video2_def_sim.SourceFiles =  {'video.c'};
dev_video2_def_sim.HeaderFiles = {'video.h'};

% Add necesarry specification to definition for code generation purpose
dev_video2_def_codegen = dev_video2_def_sim;
dev_video2_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_video2_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_video2_def_codegen.SourceFiles = ...
	{'video.c'};

%% Generate S-funktions, tls files and rtwmakecfg file
def_sim = [dev_video1_def_sim(:); dev_video2_def_sim(:)];
def_codegen = [dev_video1_def_codegen(:); dev_video2_def_codegen(:)];
legacy_code('sfcn_cmex_generate', def_sim)
legacy_code('compile', def_sim)
legacy_code('slblock_generate',def_codegen, lib_name);
legacy_code('sfcn_tlc_generate', def_codegen)
legacy_code('rtwmakecfg_generate', def_codegen)

%% Save exd exit
save_system(lib_name);
set_param(lib_name, 'EnableLBRepository','on');
set_param(lib_name, 'Lock', 'on');

% EOF