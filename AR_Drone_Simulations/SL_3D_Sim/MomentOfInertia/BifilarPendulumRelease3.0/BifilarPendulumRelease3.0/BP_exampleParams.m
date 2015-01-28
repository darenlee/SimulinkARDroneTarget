function [D,SigD,h,Sigh] = BP_exampleParams
% BP_exampleParams.m -- returns experimental apparatus dimensions and
% estimated standard deviations on the errors in those measurements.
%
% OUTPUTS:
% D -- Distance between the two vertical pendulum wires
% SigD -- Estimated error standard deviation for D
% h -- Vertical length (height) of pendulum wires
% Sigh -- Estimated error standard deviation for h
%
%NOTES:
% CONFIGURATION: test mass clean (no damping paddles)
%
%
% Copyright 2009, The MathWorks, Inc.
configstr = 'Test Mass Clean (no damping paddles)'; %#ok<NASGU>
starttime = '14:40'; %#ok<NASGU>
% [Du;Duerr;Dl;Dlerr;hb;hberr;ha;haerr]
moiexpdata = [0.452437;0.001600;0.454025;0.001600;2.749550;0.003000;2.749550;0.003000];
%% Add Mass manually
mass = 1.54122; %#ok<NASGU> % kilograms

D = mean([moiexpdata(1) moiexpdata(3)]);
SigD = mean([moiexpdata(2) moiexpdata(4)]);
h = mean([moiexpdata(5) moiexpdata(7)]);
Sigh = mean([moiexpdata(6) moiexpdata(8)]);