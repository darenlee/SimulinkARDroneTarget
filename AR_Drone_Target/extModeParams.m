function [ IP varOut2 port ] = iptest( varargin )
%IPTEST Summary of this function goes here
%   Detailed explanation goes here


hCs = getActiveConfigSet(gcs);
data = hCs.get_param('CoderTargetData');
IP = data.IP
varOut2 = 1;
port = 17725;
end

