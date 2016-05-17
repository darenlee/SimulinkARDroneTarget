%% Setting library and blocks names
currentDir = pwd;

lib_name = 'AR_Drone_2_Lib';
LED_Block_name = 'AR_Drone_LEDs';
Motor_Block_name = 'AR_Drone_Motors';
IMU_Block_name = 'AR_Drone_Internial_Measurement_Unit';
Actuator_Init_Block_name = 'AR_Drone_Initialize_Actuators';
Battery_Block_name = 'AR_Drone_Battery_Measurement';
Version_Check_Block_name = 'AR_Drone_FirmwareCheck';

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
Actuator_Init_Block_def = legacy_code('initialize');
Actuator_Init_Block_def.SourceFiles = {'act_init.c'};
Actuator_Init_Block_def.HeaderFiles = {'act_init.h'};
Actuator_Init_Block_def.IncPaths = {'.'};
Actuator_Init_Block_def.SFunctionName = Actuator_Init_Block_name;
Actuator_Init_Block_def.Options.language = 'C';
Actuator_Init_Block_def.StartFcnSpec = 'Actuator_Initialization(void)';
Actuator_Init_Block_def.TerminateFcnSpec = 'Actuator_Stop(void)';

%% LED_Block
LED_Block_def = legacy_code('initialize');
LED_Block_def.SourceFiles = {'led.c'};
LED_Block_def.HeaderFiles = {'led.h'};
LED_Block_def.IncPaths = {'.',};
LED_Block_def.SFunctionName = LED_Block_name;
LED_Block_def.Options.language = 'C';
LED_Block_def.OutputFcnSpec = 'LED_set(uint8 u1[4])';


%% Motor_Block
Motor_Block_def = legacy_code('initialize');
Motor_Block_def.SourceFiles = {'motor.c'};
Motor_Block_def.HeaderFiles = {'motor.h'};
Motor_Block_def.IncPaths = {'.',};
Motor_Block_def.SFunctionName = Motor_Block_name;
Motor_Block_def.Options.language = 'C';
Motor_Block_def.OutputFcnSpec = 'uint16 y1 = Motor_Set(uint8 u1[5])';

%% Version_Check
Version_Check_def = legacy_code('initialize');
Version_Check_def.SourceFiles = {'versionCheck.c'};
Version_Check_def.HeaderFiles = {'versionCheck.h'};
Version_Check_def.IncPaths = {'.'};
Version_Check_def.SFunctionName = Version_Check_Block_name;
Version_Check_def.Options.language = 'C';
Version_Check_def.StartFcnSpec = 'versionCheckInit(void)';
Version_Check_def.TerminateFcnSpec = 'versionCheckClose(void)';

%% IMU_Block

IMU_Block_def = legacy_code('initialize');
IMU_Block_def.SFunctionName = IMU_Block_name;
IMU_Block_def.InitializeConditionsFcnSpec  = 'void MDL_IMU_start()';
IMU_Block_def.TerminateFcnSpec = 'void MDL_IMU_term()';
IMU_Block_def.OutputFcnSpec                = 'void MDL_IMU_step(IMU_Packets y1[1], int32 y2[1])';  
IMU_Block_def.SourceFiles                  = {'IMU_Navdata_Wrapper.c'};
IMU_Block_def.IncPaths                     = {''};
IMU_Block_def.Options.useTlcWithAccel      = false;
IMU_Block_def.Options.language =  'C';
IMU_Block_def.SampleTime    = 'parameterized';

%% Generate S-functionsand simulink block
def_sim = [Actuator_Init_Block_def; LED_Block_def; Motor_Block_def; Version_Check_def; IMU_Block_def];
% def_codegen = [dev_video1_def_codegen(:); dev_video2_def_codegen(:); dev_printf_def_codegen(:)];
legacy_code('sfcn_cmex_generate', def_sim)
legacy_code('compile', def_sim)
legacy_code('slblock_generate',def_sim, lib_name);

%% Add code generation sources

LED_Block_def.SourceFiles = {'led.c','Actuators.c','GPIO.c'};
Actuator_Init_Block_def.SourceFiles = {'act_init.c','Actuators.c','GPIO.c'};
Motor_Block_def.SourceFiles = {'motor.c','Actuators.c','GPIO.c'};
def_sim = [Actuator_Init_Block_def; LED_Block_def; Motor_Block_def; Version_Check_def; IMU_Block_def];

%% Generate tlc files and rtwmakecfg file

legacy_code('sfcn_tlc_generate', def_sim)
legacy_code('rtwmakecfg_generate', def_sim)

%% Save exd exit
save_system(lib_name);
set_param(lib_name, 'EnableLBRepository','on');
set_param(lib_name, 'Lock', 'on');
% close_system(lib_name);
% clear
% EOF