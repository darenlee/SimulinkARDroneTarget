% Copyright 2014 The MathWorks, Inc.
def = legacy_code('initialize');
def.SourceFiles = {'motor.c'};
def.HeaderFiles = {'motor.h'};
def.IncPaths = {'.',};




def.SFunctionName = 'ARDrone_Motor';
def.Options.language = 'C';
%def.StartFcnSpec = 'Motor_Initialization()';
def.OutputFcnSpec = 'uint16 y1 = Motor_Set(uint8 u1[5])';


legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def);
legacy_code('slblock_generate', def);
def.SourceFiles = {'motor.c','Actuators.c','GPIO.c'};

legacy_code('sfcn_tlc_generate', def);

