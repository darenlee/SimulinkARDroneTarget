% Copyright 2014 The MathWorks, Inc.
def = legacy_code('initialize')
def.SourceFiles = {'act_init.c'};
def.HeaderFiles = {'act_init.h'};
def.IncPaths = {'.'};




def.SFunctionName = 'Init_Actuator';
def.Options.language = 'C';
def.StartFcnSpec = 'Actuator_Initialization(void)';
def.TerminateFcnSpec = 'Actuator_Stop(void)';



legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def);
legacy_code('slblock_generate', def);

def.SourceFiles = {'act_init.c','Actuators.c','GPIO.c'};
legacy_code('sfcn_tlc_generate', def);
%legacy_code('rtwmakecfg_generate', def);
