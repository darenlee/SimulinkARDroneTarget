% Copyright 2014 The MathWorks, Inc.
% these values were obtained by running PlayBack_Data and obtaining a
% running average value in different configurations

%+-1G for the X-axis
up_data = [0.9453];  %parallel (axis facing the same way as gravity)
down_data = [-1.03]; %anti-parallel (axis facing opposite of gravity)
Offset_calc = 0.5*(up_data + down_data);
Gain = 0.5*(down_data - up_data) ;
Accel_X_Offset =Offset_calc;
Accel_X_Gain  =Gain;


%+-1G for the Y-axis
up_data = [1.039];  %parallel (axis facing the same way as gravity)
down_data = [-0.9867]; %anti-parallel (axis facing opposite of gravity)
Offset_calc = 0.5*(up_data + down_data);
Gain = 0.5*(down_data - up_data) ;
Accel_Y_Offset =Offset_calc;
Accel_Y_Gain  =Gain;


%+-1G for the Z-axis
up_data = [-0.9694]; %note that this is reversed (negative) because of the way it attitude determination has been setup
down_data = [1.047];

Offset_calc = 0.5*(up_data + down_data);  %find the center
Gain = 0.5*(down_data - up_data) ;  %Find the gain which normalizes it to 1

Accel_Z_Offset = Offset_calc;
Accel_Z_Gain = Gain;

Accel_Calib_Offset_Vector = [Accel_X_Offset Accel_Y_Offset Accel_Z_Offset];
Accel_Calib_Gain_Vector = [Accel_X_Gain Accel_Y_Gain Accel_Z_Gain];

