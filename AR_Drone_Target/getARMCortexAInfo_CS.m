function info = getARMCortexAInfo_CS()
% GETARMCORTEXAINFO Single Source the ARM Cortex-A supprot package
% information
% The "info" structure holds a lot of information used throughout this
% support package.
% This allows the common-names to be sourced from a single location.

info.ToolChainName = 'Code Sourcery';
info.BoardName = 'AR_Drone_2';
info.BoardParamObj = remotetarget.util.BoardParameters(info.BoardName);

