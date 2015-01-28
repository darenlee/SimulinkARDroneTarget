% Copyright 2014 The MathWorks, Inc.
% your_relative_path = 'C:\Pi_builds_2013_july\practice_build\'; %change this to whatever path


def = legacy_code('initialize');
def.SFunctionName = 'IMU_Sfcn_mex';
def.InitializeConditionsFcnSpec  = 'void MDL_IMU_start()';
def.TerminateFcnSpec = 'void MDL_IMU_term()';
def.OutputFcnSpec                = 'void MDL_IMU_step(IMU_Packets y1[1], int32 y2[1])';  
def.SourceFiles                  = {'IMU_Navdata_Wrapper.c'};
% def.HeaderFiles                  = {'IMU_Navdata.h'};
def.IncPaths                     = {''};
def.Options.useTlcWithAccel      = false;
def.Options.language =  'C';
def.SampleTime    = 'parameterized';

%generate S-function source file
legacy_code('sfcn_cmex_generate', def);

%Generate for simulation only - the S-function does nothing in normal mode
legacy_code('generate_for_sim', def);
 
% spawns instance of the s-function in a model, drag n drop it into a model
legacy_code('slblock_generate', def, 'IMU_Start')

%When generating TLC, we want to include additional source files which are
%device driver / HW specific
def.SourceFiles  = {'IMU_Navdata.c','IMU_Navdata_wrapper.c'};
def.HeaderFiles  = {'IMU_Navdata.h'};
legacy_code('sfcn_tlc_generate', def);

% 
% legacy_code('rtwmakecfg_generate', def);






