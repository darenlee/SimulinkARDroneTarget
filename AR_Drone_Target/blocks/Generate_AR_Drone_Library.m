%% Setting library and blocks names
currentDir = pwd;

lib_name = 'AR_Drone_2_Lib';
LED_Block_name = 'AR Drone LEDs';
Motor_Block_name = 'AR Drone Motors';
IMU_Block_name = 'AR Drone Internial Measurement Unit';
Actuator_Init_Block_name = 'AR Drone Initialize Actuators';
Battery_Block_name = 'AR Drone Battery Measurement';
Version_Check_Block_name = 'AR Drone FirmwareCheck';

if exist(lib_name, 'file')
	load_system(lib_name);
	set_param(lib_name, 'Lock', 'off')
	try
        delete_block([lib_name, '/', LED_Block_name]);
        delete_block([lib_name, '/', Motor_Block_name]);
        delete_block([lib_name, '/', IMU_Block_name]);
        delete_block([lib_name, '/', Actuator_Init_Block_name]);
        delete_block([lib_name, '/', Battery_Block_name]);
        delete_block([lib_name, '/', Version_Check_Block_name]);
	catch
	end
else
	new_system(lib_name, 'Library');
	load_system(lib_name);
end


%% Actuator_Init_Block
Actuator_Init_Block_def = legacy_code('initialize')
Actuator_Init_Block_def.SourceFiles = {'act_init.c'};
Actuator_Init_Block_def.HeaderFiles = {'act_init.h'};
Actuator_Init_Block_def.IncPaths = {'.'};
Actuator_Init_Block_def.SFunctionName = Actuator_Init_Block_name
Actuator_Init_Block_def.Options.language = 'C';
Actuator_Init_Block_def.StartFcnSpec = 'Actuator_Initialization(void)';
Actuator_Init_Block_def.TerminateFcnSpec = 'Actuator_Stop(void)';
Actuator_Init_Block_def.SourceFiles = {'act_init.c','Actuators.c','GPIO.c'};
Actuator_Init_Block_def = legacy_code('initialize');
Actuator_Init_Block_def.SourceFiles = {'led.c'};
Actuator_Init_Block_def.HeaderFiles = {'led.h'};
Actuator_Init_Block_def.IncPaths = {'.',};


%% LED_Block
LED_Block_def = legacy_code('initialize');
LED_Block_def.SourceFiles = {'led.c'};
LED_Block_def.HeaderFiles = {'led.h'};
LED_Block_def.IncPaths = {'.',};
LED_Block_def.SFunctionName = LED_Block_name;
LED_Block_def.Options.language = 'C';
LED_Block_def.OutputFcnSpec = 'LED_set(uint8 u1[4])';
LED_Block_def.SourceFiles = {'led.c','Actuators.c','GPIO.c'};

%% Motor_Block
Motor_Block_def = legacy_code('initialize');
Motor_Block_def.SourceFiles = {'motor.c'};
Motor_Block_def.HeaderFiles = {'motor.h'};
Motor_Block_def.IncPaths = {'.',};
Motor_Block_def.SFunctionName = Motor_Block_name;
Motor_Block_def.Options.language = 'C';
Motor_Block_def.OutputFcnSpec = 'uint16 y1 = Motor_Set(uint8 u1[5])';
Motor_Block_def.SourceFiles = {'motor.c','Actuators.c','GPIO.c'};

%% Version_Check
Version_Check_def = legacy_code('initialize');
Version_Check_def.SourceFiles = {'versionCheck.c'};
Version_Check_def.HeaderFiles = {'versionCheck.h'};
Version_Check_def.IncPaths = {'.'};
Version_Check_def.SFunctionName = Version_Check_Block_name;
Version_Check_def.Options.language = 'C';
Version_Check_def.StartFcnSpec = 'versionCheckInit(void)';
Version_Check_def.TerminateFcnSpec = 'versionCheckClose(void)';


%% Generate S-funktions, tls files and rtwmakecfg file
def_sim = [dev_video1_def_sim(:); dev_video2_def_sim(:); dev_printf_def_sim(:)];
% def_sim = dev_video1_def_sim(:);
def_codegen = [dev_video1_def_codegen(:); dev_video2_def_codegen(:); dev_printf_def_codegen(:)];
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