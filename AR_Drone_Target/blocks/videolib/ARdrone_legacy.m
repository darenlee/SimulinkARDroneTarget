%% Setting library and blocks names
clc

currentDir = pwd;

lib_name = 'ARdrone_video_lib';
dev_video1_block_name = 'dev_video1_sfcn';
dev_video2_block_name = 'dev_video2_sfcn';
dev_printf_block_name = 'dev_printf_sfcn';
dev_send1_block_name 		= 'dev_send1_sfcn';
dev_receive1_block_name 	= 'dev_receive1_sfcn';
dev_send2_block_name 		= 'dev_send2_sfcn';
dev_receive2_block_name 	= 'dev_receive2_sfcn';
dev_video1_send_block_name 			= 'dev_video1_send_sfcn';
dev_video2_send_block_name 			= 'dev_video2_send_sfcn';
dev_video1_send_thread_block_name 	= 'dev_video1_send_thread_sfcn';
dev_video2_send_thread_block_name 	= 'dev_video2_send_thread_sfcn';

if exist(lib_name, 'file')
	load_system(lib_name);
	set_param(lib_name, 'Lock', 'off')
	try
	delete_block([lib_name, '/', dev_video1_block_name]);
	delete_block([lib_name, '/', dev_video2_block_name]);
	delete_block([lib_name, '/', dev_printf_block_name]);
    delete_block([lib_name, '/', dev_send1_block_name]);
	delete_block([lib_name, '/', dev_receive1_block_name]);
	delete_block([lib_name, '/', dev_send2_block_name]);
	delete_block([lib_name, '/', dev_receive2_block_name]);
	delete_block([lib_name, '/', dev_video1_send_block_name]);
	delete_block([lib_name, '/', dev_video2_send_block_name]);	
	delete_block([lib_name, '/', dev_video1_send_thread_block_name]);
	delete_block([lib_name, '/', dev_video2_send_thread_block_name]);
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
dev_video1_def_sim.OutputFcnSpec =		'videorabImage1(uint8 y1[1843200])';

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
dev_video2_def_sim.OutputFcnSpec =		'videorabImage2(uint8 y1[153600])';

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

%% ARprintf block
dev_printf_def_sim = legacy_code('initialize');
dev_printf_def_sim.SFunctionName = dev_printf_block_name;
% dev_printf_def_sim.StartFcnSpec =		'void ARpintf_Init(void)';
dev_printf_def_sim.OutputFcnSpec =		'ARpintf_Update(double u1)';

% dev_printf_def_sim.TerminateFcnSpec =	'void ARpintf_Close(void)';
dev_printf_def_sim.SampleTime = 'parameterized';
dev_printf_def_sim.SourceFiles =  {'ARprintf.c'};
dev_printf_def_sim.HeaderFiles = {'ARprintf.h'};
% dev_video1_def_sim.Options.language =  'C++';


%% Add necesarry specification to definition for code generation purpose
dev_printf_def_codegen = dev_printf_def_sim;
dev_printf_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_printf_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_printf_def_codegen.SourceFiles = ...
	{'ARprintf.c'};


	
%% ------------------------------------------------------------------------------%
%% 								ARdrone_send1_dev_block							 %
%% ------------------------------------------------------------------------------%
dev_send1_def_sim = legacy_code('initialize');
dev_send1_def_sim.SFunctionName = dev_send1_block_name;
dev_send1_def_sim.StartFcnSpec =		'void imageInitConnection1(int32 work1[1], int32 p1)';
dev_send1_def_sim.OutputFcnSpec =		'double y1 = imageSend1(uint8 u1[1843200], int32 work1[1])';

%%dev_send_def_sim.TerminateFcnSpec =	'void videoClose1(void)';
dev_send1_def_sim.SampleTime = 'parameterized';
dev_send1_def_sim.SourceFiles =  {'tcpLinuxClient.c'};
dev_send1_def_sim.HeaderFiles = {'tcpLinuxClient.h'};

% Add necesarry specification to definition for code generation purpose
dev_send1_def_codegen = dev_send1_def_sim;
dev_send1_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_send1_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_send1_def_codegen.SourceFiles = ...
	{'tcpLinuxClient.c'};
	
	
%% ------------------------------------------------------------------------------%
%% 								ARdrone_send2_dev_block							 %
%% ------------------------------------------------------------------------------%
dev_send2_def_sim = legacy_code('initialize');
dev_send2_def_sim.SFunctionName = dev_send2_block_name;
dev_send2_def_sim.StartFcnSpec =		'void imageInitConnection2(int32 work1[1], int32 p1)';
dev_send2_def_sim.OutputFcnSpec =		'double y1 = imageSend2(uint8 u1[153600], int32 work1[1])';

%%dev_send_def_sim.TerminateFcnSpec =	'void videoClose1(void)';
dev_send2_def_sim.SampleTime = 'parameterized';
dev_send2_def_sim.SourceFiles =  {'tcpLinuxClient.c'};
dev_send2_def_sim.HeaderFiles = {'tcpLinuxClient.h'};

% Add necesarry specification to definition for code generation purpose
dev_send2_def_codegen = dev_send2_def_sim;
dev_send2_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_send2_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_send2_def_codegen.SourceFiles = ...
	{'tcpLinuxClient.c'};
	
	
	
	
	
	
	
	
	
	
%% ------------------------------------------------------------------------------%
%% 								ARdrone_receive1_dev_block							 %
%% ------------------------------------------------------------------------------%
dev_receive1_def_sim = legacy_code('initialize');
dev_receive1_def_sim.SFunctionName = dev_receive1_block_name;
dev_receive1_def_sim.StartFcnSpec =  'void initConnection1(int32 work1[1], int32 p1)';
dev_receive1_def_sim.OutputFcnSpec ='double y2 = imageReceive1(uint8 y1[1843200], int32 work1[1])';

dev_receive1_def_sim.TerminateFcnSpec =	'void closeConnection1(int32 work1[1])';
dev_receive1_def_sim.SampleTime = 'parameterized';
dev_receive1_def_sim.SourceFiles =  {'tcpWindowsServer.c'};
dev_receive1_def_sim.HeaderFiles = {'tcpWindowsServer.h'};

% Add necesarry specification to definition for code generation purpose
dev_receive1_def_codegen = dev_receive1_def_sim;
dev_receive1_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_receive1_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_receive1_def_codegen.SourceFiles = ...
	{'tcpWindowsServer.c'};
	
	
%% ------------------------------------------------------------------------------%
%% 								ARdrone_receive2_dev_block							 %
%% ------------------------------------------------------------------------------%
dev_receive2_def_sim = legacy_code('initialize');
dev_receive2_def_sim.SFunctionName = dev_receive2_block_name;
dev_receive2_def_sim.StartFcnSpec =  'void initConnection2(int32 work1[1], int32 p1)';
dev_receive2_def_sim.OutputFcnSpec ='double y2 = imageReceive2(uint8 y1[153600], int32 work1[1])';

dev_receive2_def_sim.TerminateFcnSpec =	'void closeConnection2(int32 work1[1])';
dev_receive2_def_sim.SampleTime = 'parameterized';
dev_receive2_def_sim.SourceFiles =  {'tcpWindowsServer.c'};
dev_receive2_def_sim.HeaderFiles = {'tcpWindowsServer.h'};

% Add necesarry specification to definition for code generation purpose
dev_receive2_def_codegen = dev_receive2_def_sim;
dev_receive2_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_receive2_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_receive2_def_codegen.SourceFiles = ...
	{'tcpWindowsServer.c'};
	
	
	
	
	
%% ------------------------------------------------------------------------------%
%% 						ARdrone_video1_send_dev_block					 %
%% ------------------------------------------------------------------------------%
dev_video1_send_def_sim = legacy_code('initialize');
dev_video1_send_def_sim.SFunctionName = dev_video1_send_block_name;
dev_video1_send_def_sim.StartFcnSpec =		'void video1InitGrabSend(int32 work1[1], int32 p1, int32 p2, int32 p3)';
dev_video1_send_def_sim.OutputFcnSpec =		'double y1 = video1GrabSend(int32 work1[1])';
dev_video1_send_def_sim.TerminateFcnSpec =	'void video1CloseGrabSend(void)';
dev_video1_send_def_sim.SampleTime = 'parameterized';
dev_video1_send_def_sim.SourceFiles =  {'tcpVideoLinuxClient.c'};
dev_video1_send_def_sim.HeaderFiles = {'tcpVideoLinuxClient.h'};

% Add necesarry specification to definition for code generation purpose
dev_video1_send_def_codegen = dev_video1_send_def_sim;
dev_video1_send_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_video1_send_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_video1_send_def_codegen.SourceFiles = ...
	{'tcpVideoLinuxClient.c'};

	
%% ------------------------------------------------------------------------------%
%% 						ARdrone_video2_send_lock					 %
%% ------------------------------------------------------------------------------%
dev_video2_send_def_sim = legacy_code('initialize');
dev_video2_send_def_sim.SFunctionName = dev_video2_send_block_name;
dev_video2_send_def_sim.StartFcnSpec =		'void video2InitGrabSend(int32 work1[1], int32 p1, int32 p2, int32 p3)';
dev_video2_send_def_sim.OutputFcnSpec =		'double y1 = video2GrabSend(int32 work1[1])';
dev_video2_send_def_sim.TerminateFcnSpec =	'void video2CloseGrabSend(void)';
dev_video2_send_def_sim.SampleTime = 'parameterized';
dev_video2_send_def_sim.SourceFiles =  {'tcpVideoLinuxClient.c'};
dev_video2_send_def_sim.HeaderFiles = {'tcpVideoLinuxClient.h'};

% Add necesarry specification to definition for code generation purpose
dev_video2_send_def_codegen = dev_video2_send_def_sim;
dev_video2_send_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_video2_send_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_video2_send_def_codegen.SourceFiles = ...
	{'tcpVideoLinuxClient.c'};
	
	
		
	
	
	
		
		
		
	
%% ------------------------------------------------------------------------------%
%% 						ARdrone_video1_send_thread_dev_block					 %
%% ------------------------------------------------------------------------------%
dev_video1_send_thread_def_sim = legacy_code('initialize');
dev_video1_send_thread_def_sim.SFunctionName = dev_video1_send_thread_block_name;
dev_video1_send_thread_def_sim.StartFcnSpec =		'void video1InitGrabSendMultiThread(int32 work1[1], int32 p1, int32 p2, int32 p3)';
dev_video1_send_thread_def_sim.OutputFcnSpec =		'double y1 = video1GrabSendMultiThread(int32 work1[1])';
dev_video1_send_thread_def_sim.TerminateFcnSpec =	'void video1CloseGrabSendMultiThread(void)';
dev_video1_send_thread_def_sim.SampleTime = 'parameterized';
dev_video1_send_thread_def_sim.SourceFiles =  {'tcpVideoLinuxClientMultiThread.c'};
dev_video1_send_thread_def_sim.HeaderFiles = {'tcpVideoLinuxClientMultiThread.h'};

% Add necesarry specification to definition for code generation purpose
dev_video1_send_thread_def_codegen = dev_video1_send_thread_def_sim;
dev_video1_send_thread_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_video1_send_thread_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_video1_send_thread_def_codegen.SourceFiles = ...
	{'tcpVideoLinuxClientMultiThread.c'};

	
%% ------------------------------------------------------------------------------%
%% 						ARdrone_video2_send_thread_dev_block					 %
%% ------------------------------------------------------------------------------%
dev_video2_send_thread_def_sim = legacy_code('initialize');
dev_video2_send_thread_def_sim.SFunctionName = dev_video2_send_thread_block_name;
dev_video2_send_thread_def_sim.StartFcnSpec =		'void video2InitGrabSendMultiThread(int32 work1[1], int32 p1, int32 p2, int32 p3)';
dev_video2_send_thread_def_sim.OutputFcnSpec =		'double y1 = video2GrabSendMultiThread(int32 work1[1])';
dev_video2_send_thread_def_sim.TerminateFcnSpec =	'void video2CloseGrabSendMultiThread(void)';
dev_video2_send_thread_def_sim.SampleTime = 'parameterized';
dev_video2_send_thread_def_sim.SourceFiles =  {'tcpVideoLinuxClientMultiThread.c'};
dev_video2_send_thread_def_sim.HeaderFiles = {'tcpVideoLinuxClientMultiThread.h'};

% Add necesarry specification to definition for code generation purpose
dev_video2_send_thread_def_codegen = dev_video2_send_thread_def_sim;
dev_video2_send_thread_def_codegen.IncPaths = ...
	{currentDir,...
     '.'};
dev_video2_send_thread_def_codegen.SrcPaths = ...
	{currentDir,...
	 '.'};
dev_video2_send_thread_def_codegen.SourceFiles = ...
	{'tcpVideoLinuxClientMultiThread.c'};




%% Generate S-funktions, tls files and rtwmakecfg file
def_sim = [dev_video1_def_sim(:); dev_video2_def_sim(:); dev_printf_def_sim(:); dev_send1_def_sim(:) ; dev_receive1_def_sim(:) ; dev_send2_def_sim(:) ; dev_receive2_def_sim(:) ; dev_video1_send_def_sim(:) ; dev_video2_send_def_sim(:) ; dev_video1_send_thread_def_sim(:) ; dev_video2_send_thread_def_sim(:) ];
% def_sim = dev_video1_def_sim(:);
def_codegen = [dev_video1_def_codegen(:); dev_video2_def_codegen(:); dev_printf_def_codegen(:) ; dev_send1_def_codegen(:) ; dev_receive1_def_codegen(:) ; dev_send2_def_codegen(:) ; dev_receive2_def_codegen(:) ; dev_video1_send_def_codegen(:) ; dev_video2_send_def_codegen(:) ; dev_video1_send_thread_def_codegen(:) ; dev_video2_send_thread_def_codegen(:) ];
legacy_code('sfcn_cmex_generate', def_sim)
legacy_code('compile', def_sim)
legacy_code('slblock_generate',def_codegen, lib_name);
legacy_code('sfcn_tlc_generate', def_codegen)
legacy_code('rtwmakecfg_generate', def_codegen)

%% Save exd exit
save_system(lib_name);
set_param(lib_name, 'EnableLBRepository','on');
set_param(lib_name, 'Lock', 'on');
% close_system(lib_name);
% clear
% EOF