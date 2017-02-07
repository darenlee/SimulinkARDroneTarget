function [ IP varOut2 port ] = iptest( varargin )
%IPTEST Summary of this function goes here
%   Detailed explanation goes here

%% make sure that the correct (parent) model is used for getting the configset


hCs = [];
try hCs = getActiveConfigSet(gcs);
    
catch
        parent = get_param(gcs,'parent');
    while ~isequal(parent,'')
        current = parent;
        parent = get_param(current,'parent');
        if isequal(parent,'')
            hCs = getActiveConfigSet(current);
        end
    end
end
  
data = hCs.get_param('CoderTargetData');
IP = data.IP;
varOut2 = 1;
port = 17725;
end

