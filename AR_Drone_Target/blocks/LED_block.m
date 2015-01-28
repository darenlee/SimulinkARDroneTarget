% Copyright 2014 The MathWorks, Inc.
def = legacy_code('initialize');
def.SourceFiles = {'led.c'};
def.HeaderFiles = {'led.h'};
def.IncPaths = {'.',};




def.SFunctionName = 'ARDrone_LED';
def.Options.language = 'C';
%def.StartFcnSpec = 'LED_Initialization()';
def.OutputFcnSpec = 'LED_set(uint8 u1[4])';
%def.TerminateFcnSpec='LED_stop()';

legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def);

legacy_code('slblock_generate', def);

def.SourceFiles = {'led.c','Actuators.c','GPIO.c'};

legacy_code('sfcn_tlc_generate', def);
legacy_code('rtwmakecfg_generate', def);
