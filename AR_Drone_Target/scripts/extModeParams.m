function [ IP varOut2 port ] = iptest( varargin )
%IPTEST Summary of this function goes here
%   Detailed explanation goes here

%% make sure that the correct (parent) model is used for getting the configset

parent = get_param(gcs,'parent');
if isequal(parent,'');
    hCs = getActiveConfigSet(gcs);
else
    hCs = getActiveConfigSet(parent);
end
  
data = hCs.get_param('CoderTargetData');
IP = data.IP;
varOut2 = 1;
port = 17725;
end

