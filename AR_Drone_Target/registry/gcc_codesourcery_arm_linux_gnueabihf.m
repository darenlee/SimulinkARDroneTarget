% Copyright 2014 The MathWorks, Inc.
function [tc, results] = gcc_codesourcery_arm_linux_gnueabihf()
%gcc_codesourcery_arm_linux_gnueabihf

% Copyright 2013 The MathWorks, Inc.

toolchain.Platforms  = {'win64', 'win32'};
toolchain.Versions   = {'4.8'};
toolchain.Artifacts  = {'gmake'};
toolchain.FuncHandle = str2func('getToolchainInfoFor');
toolchain.ExtraFuncArgs = {};

[tc, results] = coder.make.internal.generateToolchainInfoObjects(mfilename, toolchain);
end

function tc = getToolchainInfoFor(platform, version, artifact, varargin)
% Toolchain Information

tc = coder.make.ToolchainInfo('BuildArtifact', 'gmake makefile', 'SupportedLanguages', {'Asm/C/C++'});
info = getARMCortexAInfo_CS();
tc.Name = coder.make.internal.formToolchainName(info.ToolChainName, ...
    platform, version, artifact);
tc.Platform = platform;
tc.setBuilderApplication(platform);

% Toolchain's attribute
tc.addAttribute('TransformPathsWithSpaces');
tc.addAttribute('SupportsUNCPaths',     false);
tc.addAttribute('SupportsDoubleQuotes', false);


% ------------------------------
% Make
% ------------------------------

make = tc.BuilderApplication();
make.IncludeFiles = {'codertarget_assembly_flags.mk', '../codertarget_assembly_flags.mk'};

% Add macros
tc.addIntrinsicMacros({'TARGET_LOAD_CMD_ARGS'});
tc.addIntrinsicMacros({'TARGET_PKG_INSTALLDIR'}); %Daren: important for pointing out where the batch file for download is (your target directory)
tc.addMacro('CCOUTPUTFLAG',     '--output_file=');
tc.addMacro('LDOUTPUTFLAG',     '--output_file=');
% tc.addMacro('CPFLAGS', '-O binary');

tc.addIntrinsicMacros({'CODE_SOURCERY'}); %Daren: Added this here, according to the doc
tc.addMacro('COMPILER_PATH','$(CODE_SOURCERY)');

% Assembler
assembler = tc.getBuildTool('Assembler');
assembler.setName([info.ToolChainName, ' Assembler']);
assembler.setCommand('arm-none-linux-gnueabi-as');
assembler.setDirective('IncludeSearchPath', '-I');
assembler.setDirective('PreprocessorDefine', '-D');
assembler.setDirective('OutputFlag', '-o');
assembler.setDirective('Debug', '-g');
assembler.DerivedFileExtensions = {'Object'};
assembler.setFileExtension('Source','.s');
assembler.setFileExtension('Object', '.o');
assembler.setPath('$(CODE_SOURCERY)');

% Compiler
cCompiler = tc.getBuildTool('C Compiler');
cCompiler.setName([info.ToolChainName, ' C Compiler']);
cCompiler.setCommand('arm-none-linux-gnueabi-gcc');
cCompiler.setDirective('IncludeSearchPath', '-I');
cCompiler.setDirective('PreprocessorDefine', '-D');
cCompiler.setDirective('OutputFlag', '-o');
cCompiler.setDirective('Debug', '-g');
cCompiler.setFileExtension('Source', '.c');
cCompiler.setFileExtension('Header', '.h');
cCompiler.setFileExtension('Object', '.o');
cCompiler.setPath('$(COMPILER_PATH)');

% C++ compiler
cppCompiler = tc.getBuildTool('C++ Compiler');
cppCompiler.setName([info.ToolChainName, ' C Compiler']);
cppCompiler.setCommand('arm-none-linux-gnueabi-g++');
cppCompiler.setDirective('IncludeSearchPath', '-I');
cppCompiler.setDirective('PreprocessorDefine', '-D');
cppCompiler.setDirective('OutputFlag', '-o');
cppCompiler.setDirective('Debug', '-g');
cppCompiler.setFileExtension('Source', '.cpp');
cppCompiler.setFileExtension('Header', '.hpp');
cppCompiler.setFileExtension('Object', '.o');
% cppcompiler.setPath('$(CODE_SOURCERY)');

% Linker
linker = tc.getBuildTool('Linker');
linker.setName([info.ToolChainName, ' Linker']);
linker.setCommand('arm-none-linux-gnueabi-gcc');
linker.setDirective('Library', '-l');
linker.setDirective('LibrarySearchPath', '-L');
linker.setDirective('OutputFlag', '-o');
linker.setDirective('Debug', '-g');
linker.setFileExtension('Executable', '.elf');
linker.setFileExtension('Shared Library', '.so');
linker.Libraries = {'-lm'};
linker.setPath('$(CODE_SOURCERY)');

% C++ Linker
cppLinker = tc.getBuildTool('C++ Linker');
cppLinker.setName([info.ToolChainName, ' C++ Linker']);
cppLinker.setCommand('arm-none-linux-gnueabi-gcc');
cppLinker.setDirective('Library', '-l');
cppLinker.setDirective('LibrarySearchPath', '-L');
cppLinker.setDirective('OutputFlag', '-o');
cppLinker.setDirective('Debug', '-g');
cppLinker.setFileExtension('Executable', '');
cppLinker.setFileExtension('Shared Library', '.so');
cppLinker.Libraries = {'-lm'};
% cpplinker.setPath('$(CODE_SOURCERY)');

% Archiver
archiver = tc.getBuildTool('Archiver');
archiver.setName([info.ToolChainName, ' Archiver']);
archiver.setCommand('arm-none-linux-gnueabi-ar');
archiver.setDirective('OutputFlag', '');
archiver.setFileExtension('Static Library', '.lib');
archiver.setPath('$(CODE_SOURCERY)');


% --------------------------------------------
% BUILD CONFIGURATIONS
% --------------------------------------------
optimsOffOpts = {'-O0'};
optimsOnOpts = {'-O2'};
cCompilerOpts    = {''};
archiverOpts     = {'-r'};

compilerOpts = {...
    '-c'};

assemblerOpts = compilerOpts;

linkerOpts = { ...
    '-lm    -lrt  -lpthread'};

% Get the debug flag per build tool
debugFlag.CCompiler   = '-g -D"_DEBUG"';  
debugFlag.Linker      = ''; 
debugFlag.Archiver    = ''; 

cfg = tc.getBuildConfiguration('Faster Builds');
cfg.setOption('Assembler',  horzcat(cCompilerOpts, assemblerOpts, '$(ASFLAGS_ADDITIONAL)', '$(INCLUDES)'));
cfg.setOption('C Compiler', horzcat(cCompilerOpts, compilerOpts, optimsOffOpts));
cfg.setOption('Linker',     linkerOpts);
cfg.setOption('Archiver',   archiverOpts);

cfg = tc.getBuildConfiguration('Faster Runs');
cfg.setOption('Assembler',  horzcat(cCompilerOpts, assemblerOpts, '$(ASFLAGS_ADDITIONAL)', '$(INCLUDES)'));
cfg.setOption('C Compiler', horzcat(cCompilerOpts, compilerOpts, optimsOnOpts));
cfg.setOption('Linker',     linkerOpts);
cfg.setOption('Archiver',   archiverOpts);

cfg = tc.getBuildConfiguration('Debug');
cfg.setOption('Assembler',  horzcat(cCompilerOpts, assemblerOpts, '$(ASFLAGS_ADDITIONAL)', '$(INCLUDES)', debugFlag.CCompiler));
cfg.setOption('C Compiler', horzcat(cCompilerOpts, compilerOpts, optimsOffOpts, debugFlag.CCompiler));
cfg.setOption('Linker',     horzcat(linkerOpts, debugFlag.Linker));
cfg.setOption('Archiver',   horzcat(archiverOpts, debugFlag.Archiver));

tc.setBuildConfigurationOption('all', 'Make Tool', '-f $(MAKEFILE)');

end
