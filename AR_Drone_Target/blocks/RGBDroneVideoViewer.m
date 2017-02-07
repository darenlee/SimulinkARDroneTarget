function RGBDroneVideoViewer(block)
% Level-2 MATLAB file S-Function for unit delay demo.
%   Copyright 1990-2009 The MathWorks, Inc.

  setup(block);
  
%endfunction

function setup(block)
   
  %% Register number of input and output ports
  block.NumInputPorts  = 3;
  block.NumOutputPorts = 0;
  block.NumDialogPrms  = 0;

  %% Setup functional port properties to dynamically
  %% inherited.
  block.SetPreCompInpPortInfoToDynamic;
  
  %% Set block sample time to inhereted
  block.SampleTimes = [-1 0];
  
  %% Set the block simStateCompliance to default (i.e., same as a built-in block)
  block.SimStateCompliance = 'DefaultSimState';

  %% Register methods
  block.RegBlockMethod('InitializeConditions',    @InitConditions);  
  block.RegBlockMethod('Update',                  @Update);  
  
  %% Set block as a viewer
  block.SetSimViewingDevice(true);
  
%endfunction

function InitConditions(block)

  
%endfunction

function Update(block)


%% Get data
R = block.InputPort(1).Data;
G = block.InputPort(2).Data;
B = block.InputPort(3).Data;

% create RBG 3D matrix
height =size(R,1);
width = size(R,2);
RGB = uint8(zeros(width,height,3));
% transpose because of how image defines X and Y
RGB(:,:,1) = uint8(R');
RGB(:,:,2) = uint8(G');
RGB(:,:,3) = uint8(B');

% show image 
image(RGB);

%endfunction

