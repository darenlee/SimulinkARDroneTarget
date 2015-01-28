% Copyright 2014 The MathWorks, Inc.
clear all
load SYS_ID_DATA_II.mat
% load SYS_ID_DATA_III.MAT

%Euler Angles
Y_sysid_out_1 = EulerAngles.signals(2).values;

%Thruster Action after motor mixing
All_Thrust = [Control_Input.signals(1).values Control_Input.signals(2).values Control_Input.signals(3).values Control_Input.signals(4).values];

%Output torque from controller
Toqrue_Input_1 = Toqrue_Input.signals.values(:,2);     

% %Gyro
q_out_1 = Gyro.signals.values(:,2);
gyro_bias = mean(Gyro.signals.values(1:1200,2));

ind = Off_Switch.signals(1).values(:,1)>10;

%Off_Switch.signals(2).values
% Off_Switch.signals(2).values > 3.5

Y_sysid_out = Y_sysid_out_1(ind);
All_Thrust_out = All_Thrust( ind,:);
Toqrue_Input_extract = Toqrue_Input_1(ind,:);
q_out = (q_out_1(ind) - gyro_bias);  %forgot to add this conversion factor here, kind of important
% q_out = GyroFiltered.signals.values(ind,:);
close all
% h= plot(Gyro.time(ind),Y_sysid_out)
% hold on 
plot(Gyro.time(ind),Toqrue_Input_extract)
title('Control Effort');
ylabel('U (N*M)');
xlabel('Time (s)');

figure
plot(Gyro.time(ind),q_out)
title('Angular Velocity');
ylabel('Rate (deg/s)');
xlabel('Time (s)');

time_out_1 = EulerAngles.time(ind);
time_out = time_out_1-time_out_1(1);


%%%%%%%%%%%%%%%%
%%% Approx Fit
%%% Time Extraction   : 1.1475 to 5.515
%%% Filter Extraction : 0.024449588
%%% Numerator : 30
%%% Damping (last) term : 0.27
%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%
%%% Transfer function
%%%  Numerator : 30.05, zeta : 0.2543, , make others 0.1, 0.1 and then hit
%%%  then tune it
%%%%%%%%%%%%%%%%
%%%%
