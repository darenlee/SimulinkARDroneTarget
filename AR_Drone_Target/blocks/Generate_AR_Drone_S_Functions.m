%% Actuator Initialization

act_init_def = legacy_code('initialize');
act_init_def.SourceFiles = {'act_init.c'};
act_init_def.HeaderFiles = {'act_init.h'};
act_init_def.IncPaths = {''};
act_init_def.SFunctionName = 'Init_Actuator';
act_init_def.Options.language = 'C';
act_init_def.StartFcnSpec = 'Actuator_Initialization(void)';
act_init_def.TerminateFcnSpec = 'Actuator_Stop(void)';

% Generate s function
legacy_code('sfcn_cmex_generate', act_init_def);
legacy_code('compile', act_init_def);
act_init_def.SourceFiles = {'act_init.c','Actuators.c','GPIO.c'};
% Add dependancy for target code generation
act_init_def.SrcPaths = {'.'};
legacy_code('sfcn_tlc_generate', act_init_def);

%% printf

print_def = legacy_code('initialize');
print_def.SourceFiles = {'ARprintf.c'};
print_def.HeaderFiles = {'ARprintf.h'};
print_def.IncPaths = {''};
print_def.SFunctionName = 'print';
print_def.Options.language = 'C';
print_def.StartFcnSpec = 'ARpintf_Init(void)';
print_def.OutputFcnSpec = 'ARpintf_Update(double u1)';
print_def.TerminateFcnSpec = 'ARpintf_Close(void)';

% Generate s function
legacy_code('sfcn_cmex_generate', print_def);
legacy_code('compile', print_def);
% legacy_code('slblock_generate',print_init_def);
% Add dependancy for target code generation
print_def.SrcPaths = {'.'};
legacy_code('sfcn_tlc_generate', print_def);

%% IMU Block

% load the IMU Packet bus
load('IMU_Packets_Bus.mat')

IMU_Block_def = legacy_code('initialize');
IMU_Block_def.SFunctionName = 'IMU_Sfcn_mex';
IMU_Block_def.InitializeConditionsFcnSpec  = 'void MDL_IMU_start()';
IMU_Block_def.TerminateFcnSpec = 'void MDL_IMU_term()';
IMU_Block_def.OutputFcnSpec                = 'void MDL_IMU_step(IMU_Packets y1[1], int32 y2[1])';  
IMU_Block_def.SourceFiles                  = {'IMU_Navdata_Wrapper.c'};
IMU_Block_def.IncPaths                     = {''};
IMU_Block_def.Options.useTlcWithAccel      = false;
IMU_Block_def.Options.language =  'C';
IMU_Block_def.SampleTime    = 'parameterized';

% Generate S-function source file
legacy_code('sfcn_cmex_generate', IMU_Block_def);

% Generate for simulation only - the S-function does nothing in normal mode
legacy_code('generate_for_sim', IMU_Block_def);

% When generating TLC, we want to include additional source files which are
% device driver / HW specific
IMU_Block_def.SourceFiles  = {'IMU_Navdata.c','IMU_Navdata_wrapper.c'};
IMU_Block_def.HeaderFiles  = {'IMU_Navdata.h'};
IMU_Block_def.SrcPaths = {'.'};
legacy_code('sfcn_tlc_generate', IMU_Block_def);

%% LED Block

LED_Block_def = legacy_code('initialize');
LED_Block_def.SourceFiles = {'led.c'};
LED_Block_def.HeaderFiles = {'led.h'};
LED_Block_def.IncPaths = {''};
LED_Block_def.SFunctionName = 'ARDrone_LED';
LED_Block_def.Options.language = 'C';
LED_Block_def.OutputFcnSpec = 'LED_set(uint8 u1[4])';

% Generate s function
legacy_code('sfcn_cmex_generate', LED_Block_def);
legacy_code('compile', LED_Block_def);

% Add dependancy for target code generation
LED_Block_def.SourceFiles = {'led.c','Actuators.c','GPIO.c'};
LED_Block_def.SrcPaths = {'.'};
legacy_code('sfcn_tlc_generate', LED_Block_def);

%% Motor Block

Motor_def = legacy_code('initialize');
Motor_def.SourceFiles = {'motor.c'};
Motor_def.HeaderFiles = {'motor.h'};
Motor_def.IncPaths = {''};
Motor_def.SFunctionName = 'ARDrone_Motor';
Motor_def.Options.language = 'C';
Motor_def.OutputFcnSpec = 'uint16 y1 = Motor_Set(uint8 u1[5])';

% Generate s function
legacy_code('sfcn_cmex_generate', Motor_def);
legacy_code('compile', Motor_def);

% Add dependancy for target code generation
Motor_def.SourceFiles = {'motor.c','Actuators.c','GPIO.c'};
legacy_code('sfcn_tlc_generate', Motor_def);

%% Version Check Block
Version_Check_def = legacy_code('initialize');
Version_Check_def.SourceFiles = {'versionCheck.c'};
Version_Check_def.HeaderFiles = {'versionCheck.h'};
Version_Check_def.IncPaths = {''};
Version_Check_def.SFunctionName = 'Version_Check';
Version_Check_def.Options.language = 'C';
Version_Check_def.StartFcnSpec = 'void versionCheckInit(void)';
Version_Check_def.OutputFcnSpec = 'void versionCheckStep(uint8 y1[1])';
Version_Check_def.TerminateFcnSpec = 'void versionCheckClose(void)';

% Generate s function
legacy_code('sfcn_cmex_generate', Version_Check_def);
legacy_code('compile', Version_Check_def);
Version_Check_def.SrcPaths = {'.'};
legacy_code('sfcn_tlc_generate', Version_Check_def);

%% Battery block
Battery_def = legacy_code('initialize');
Battery_def.SFunctionName = 'Battery_Sfcn_mex';
Battery_def.InitializeConditionsFcnSpec  = 'void BatteryMeasure_start()';
Battery_def.TerminateFcnSpec = 'void BatteryMeasure_term()';
Battery_def.OutputFcnSpec                = 'void BatteryMeasure_step(single y1[1])';  
Battery_def.SourceFiles                  = {'BatteryMeasure_Wrapper.c'};
Battery_def.IncPaths                     = {''};
Battery_def.Options.useTlcWithAccel      = false;
Battery_def.Options.language =  'C';
Battery_def.SampleTime    = 'parameterized';

% Generate S-function source file
legacy_code('sfcn_cmex_generate', Battery_def);

% Generate for simulation only - the S-function does nothing in normal mode
legacy_code('generate_for_sim', Battery_def);

% When generating TLC, we want to include additional source files which are
% device driver / HW specific
Battery_def.HeaderFiles                  = {'i2c-dev.h'};
Battery_def.SourceFiles  = {'BatteryMeasure.c','BatteryMeasure_Wrapper.c'};
Battery_def.SrcPaths = {'.'};
legacy_code('sfcn_tlc_generate', Battery_def);

%% Generate the rtwmakecfg file for all s functions

legacy_code('rtwmakecfg_generate', [print_def; act_init_def;IMU_Block_def;LED_Block_def;Motor_def;Version_Check_def;Battery_def]);

%% clear the loaded bus object

clear('IMU_Packets');

