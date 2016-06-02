function ARDroneVideoViewer(block)
% Level-2 MATLAB file S-Function for unit delay demo.
%   Copyright 1990-2009 The MathWorks, Inc.

  setup(block);
  
%endfunction

function setup(block)
   
  %% Register number of input and output ports
  block.NumInputPorts  = 1;
  block.NumOutputPorts = 0;
  block.NumDialogPrms  = 2;

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

%% constants for color conversion
c1 =     298.082/256;
Rc1 =    408.583/256;
Rc2 =   -222.921;
Gc1 =   -100.291/256;
Gc2 =   -208.120/256;
Gc3 =    135.576;
Bc1=     516.412/256;
Bc2=    -276.836;

%% find the video resolution from the input length
YCbCr422In = block.InputPort(1).Data;
inputLength = length(YCbCr422In);

horizontalFactor = block.DialogPrm(1).Data;
verticalFactor = block.DialogPrm(2).Data;

n = sqrt((inputLength / 2) / horizontalFactor / verticalFactor);
if (floor(n) ~= n)
    n = 0;
end
width = n * horizontalFactor;
height = n * verticalFactor;

R = uint8(zeros(height,width));
G = uint8(zeros(height,width));
B = uint8(zeros(height,width));

%% Convert to RGB

for verticalIndex = 1 : 1 : height;             
    for horizontalIndex = 1 : 1 : (width/2);  
        index = 4 * ((verticalIndex - 1) * (width / 2) + horizontalIndex) - 3;  % translate the horizontal and vertical indexes into the index into the video input
        pixel = [single(YCbCr422In(index)) single(YCbCr422In(index+1)) single(YCbCr422In(index+2)) single(YCbCr422In(index+3))];
        R(verticalIndex, 2 * horizontalIndex - 1) = c1 * pixel(2) + Rc1 * pixel(3) + Rc2;
        G(verticalIndex, 2 * horizontalIndex - 1) = c1 * pixel(2) + Gc1 * pixel(1) + Gc2 * pixel(3) + Gc3;
        B(verticalIndex, 2 * horizontalIndex - 1) = c1 * pixel(2) + Bc1 * pixel(1) + Bc2;
        R(verticalIndex, 2 * horizontalIndex) = c1 * pixel(4) + Rc1 * pixel(3) + Rc2;
        G(verticalIndex, 2 * horizontalIndex) = c1 * pixel(4) + Gc1 * pixel(1) + Gc2 * pixel(3) + Gc3;
        B(verticalIndex, 2 * horizontalIndex) = c1 * pixel(4) + Bc1 * pixel(1) + Bc2;
    end
end


RGB = uint8(zeros(height,width,3));
RGB(:,:,1) = uint8(R);
RGB(:,:,2) = uint8(G);
RGB(:,:,3) = uint8(B);
image(RGB);

%endfunction

