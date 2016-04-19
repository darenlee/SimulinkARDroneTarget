% Copyright 2014 The MathWorks, Inc.
%-------------------------------
% AR DRONE 2.0 Code Generation Data Dictionary
%-------------------------------
clear all

%load Navigation Bus Data Objects
load Navigation_Gain_Bus.mat

%load Sensor Data Bus
load SensorDataBus.mat

%load Bavigation Bus Data Objects
load Config_Set.mat

%Load offset corrections from Rate Gyro Temperature Drift experiment
% load GyroDrift_OffsetCorrections.mat

%Load IMU Bus Object
LibPath = which('AR_Drone_2_Library');
MagicValue = regexp(LibPath,'AR_Drone_2_Library.slx');
load([LibPath(1:(MagicValue-1)) 'Save_IMU_struct.mat'])
clear MagicValue
clear LibPath


%% All Variant Subsystems
% VariantChoice.SubSystem1=2;
% SubSystem1 = 1;

%% Calibration Parameters
%ideally these should be loaded to a MAT file rather than all defined here.
%values come from calibration procedures

Accel_Calib_Offset_Vector = [-0.0423  0.0261  0.0388];
Accel_Calib_Gain_Vector   = [-0.9877 -1.0129 -1.0082]; %note, that this might need to be multiplied by -1
                                                   %depending on how the
                                                   %calibration. this is
                                                   %becaues -g is up and +g
                                                   %might be down if you
                                                   %look at the raw data     

                                                   
%Values for the magnetomer values come from the magnetometer calibration script
%which returns a struct of gain and offset values. Populate these pairs of
%values into the right entry values here
%Magnetometer calibration structure                                                  
Mag_Calib_Offset_Vector.Gain_X = -23;
Mag_Calib_Offset_Vector.Gain_Y = 4.3;
Mag_Calib_Offset_Vector.Gain_Z = 1.44;

Mag_Calib_Gain_Vector.Gain_X = 187;
Mag_Calib_Gain_Vector.Gain_Y = 163;
Mag_Calib_Gain_Vector.Gain_Z = 139;

% %Parameters for polynomial fit of gyro drift versus temperature
% P1 = quadratic gain, P2 = multiply gain, P3 = offset

Gyro_Correction_Roll.P1 = -0.004462 ;
Gyro_Correction_Roll.P2 = 1.144  ;
Gyro_Correction_Roll.Offset = -67.5100;

Gyro_Correction_Pitch.P1 = 0.009828;
Gyro_Correction_Pitch.P2 = 0.4486  ;
Gyro_Correction_Pitch.Offset = 4.961;

%yaw gains taken from recent experiment, see file
%'GyroDrift_OffsetCorrections_II.mat'
Gyro_Correction_Yaw.P1 = -0.0070;
Gyro_Correction_Yaw.P2 = 0.9867;
Gyro_Correction_Yaw.Offset = -35.2100;


%% Declare Navigation Offset and Gain Data Objects

%Magnetometer
Magnetometer_Calib_Offset = Simulink.Parameter; %should make bus exported global
Magnetometer_Calib_Offset.DataType ='Bus: Navigation_Gain_Bus';
Magnetometer_Calib_Offset.Value  = Mag_Calib_Offset_Vector;
Magnetometer_Calib_Offset.CoderInfo.StorageClass = 'ExportedGlobal';

Magnetometer_Calib_Gain = Simulink.Parameter; %should make bus exported global
Magnetometer_Calib_Gain.DataType ='Bus: Navigation_Gain_Bus';
Magnetometer_Calib_Gain.Value  = Mag_Calib_Gain_Vector;
Magnetometer_Calib_Gain.CoderInfo.StorageClass = 'ExportedGlobal';


% Accelerometer 
Accel_Calib_Offset = Simulink.Parameter; %should make bus exported global
Accel_Calib_Offset.DataType ='Bus: Navigation_Gain_Bus';
Accel_Calib_Offset.Value  = struct('Gain_X',Accel_Calib_Offset_Vector(1),'Gain_Y',Accel_Calib_Offset_Vector(2),'Gain_Z',Accel_Calib_Offset_Vector(3));
Accel_Calib_Offset.CoderInfo.StorageClass = 'ExportedGlobal';

Accel_Calib_Gain = Simulink.Parameter; %should make bus exported global
Accel_Calib_Gain.DataType ='Bus: Navigation_Gain_Bus';
Accel_Calib_Gain.Value  = struct('Gain_X',Accel_Calib_Gain_Vector(1),'Gain_Y',Accel_Calib_Gain_Vector(2),'Gain_Z',Accel_Calib_Gain_Vector(3));
Accel_Calib_Gain.CoderInfo.StorageClass = 'ExportedGlobal';


% RateGyro Temperature
Gyro_Calib_Temp_X = Simulink.Parameter; %should make bus exported global
Gyro_Calib_Temp_X.DataType ='Bus: Gyro_Offset_Bus';
Gyro_Calib_Temp_X.Value  = Gyro_Correction_Roll;
Gyro_Calib_Temp_X.CoderInfo.StorageClass = 'ExportedGlobal';

Gyro_Calib_Temp_Y = Simulink.Parameter; %should make bus exported global
Gyro_Calib_Temp_Y.DataType ='Bus: Gyro_Offset_Bus';
Gyro_Calib_Temp_Y.Value  = Gyro_Correction_Pitch;
Gyro_Calib_Temp_Y.CoderInfo.StorageClass = 'ExportedGlobal';

Gyro_Calib_Temp_Z = Simulink.Parameter; %should make bus exported global
Gyro_Calib_Temp_Z.DataType ='Bus: Gyro_Offset_Bus';
Gyro_Calib_Temp_Z.Value  = Gyro_Correction_Yaw;
Gyro_Calib_Temp_Z.CoderInfo.StorageClass = 'ExportedGlobal';



%% All Control Gains

