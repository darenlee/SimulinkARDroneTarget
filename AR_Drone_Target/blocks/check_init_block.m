% Copyright 2014 The MathWorks, Inc.
function check_init_block
persistent x;

if(isempty(x))
msgbox('Both the Actuator and the LED blocks need the Init_Actuator block to work properly. Add this block to the model. It is part of the AR Drone 2 Target library');
x=0;
end
end