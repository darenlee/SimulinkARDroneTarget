% Copyright 2014 The MathWorks, Inc.
def = legacy_code('initialize');
def.SourceFiles = {'versionCheck.c'};
def.HeaderFiles = {'versionCheck.h'};
def.IncPaths = {'.'};

def.SFunctionName = 'droneVersionCheck';
def.Options.language = 'C';
def.StartFcnSpec = 'versionCheckInit(void)';
def.TerminateFcnSpec = 'versionCheckClose(void)';

legacy_code('sfcn_cmex_generate', def);
legacy_code('compile', def);
legacy_code('slblock_generate', def);
legacy_code('sfcn_tlc_generate', def);
