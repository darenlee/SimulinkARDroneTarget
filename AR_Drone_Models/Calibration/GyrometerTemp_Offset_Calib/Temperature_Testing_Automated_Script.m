% Copyright 2014 The MathWorks, Inc.
%This script assumes that you have: 
% a) First collected data of gyro drift and temperature
% b) Ran the TempCorrect_OfflineTest to filter the data

%% Correct for Roll Drift First
close all
Ts = 1/400;
StartTime =10;
StartTick = StartTime/Ts;

GyroDrift_Roll = Roll_Gyro_filtered.signals.values(StartTick:end,2);

TempMeasureRefined = FilteredTemp.signals.values(StartTick:end,2);

% [SortedTemp IndexSort] = sort(TempMeasureRefined);
% re_ordered = GyroDrift_Roll(IndexSort);

% figure
% plot(TempMeasureRefined,GyroDrift_Roll,'.')
% figure
PlotName = 'Roll Drift Estimation';
[fitresult, gof] = createFit_Automate(TempMeasureRefined,GyroDrift_Roll,PlotName);
% cftool

 
Gyro_Correction_Roll.P1 = 0;
Gyro_Correction_Roll.P2 = fitresult.p1;
Gyro_Correction_Roll.Offset = fitresult.p2;



%% Correct for Pitch Drift 
Ts = 1/400;
StartTime =10;
StartTick = StartTime/Ts;

GyroDrift_Pitch = Pitch_Gyro_filtered.signals.values(StartTick:end,2);
TempMeasureRefined = FilteredTemp.signals.values(StartTick:end,2);
% figure
% plot(TempMeasureRefined,GyroDrift_Pitch)
PlotName = 'Pitch Drift Estimation';
% figure
[fitresult, gof] = createFit_Automate(TempMeasureRefined,GyroDrift_Pitch,PlotName);
% cftool
Gyro_Correction_Pitch.P1 = 0;
Gyro_Correction_Pitch.P2 = fitresult.p1;
Gyro_Correction_Pitch.Offset = fitresult.p2;


%% Correct Yaw Drift

Ts = 1/400;
StartTime =10;
StartTick = StartTime/Ts;

GyroDrift_Yaw = Yaw_Gyro_filtered.signals.values(StartTick:end,2);
TempMeasureRefined = FilteredTemp.signals.values(StartTick:end,2);
% figure
% plot(TempMeasureRefined,GyroDrift_Yaw)
PlotName = 'Yaw Drift Estimation';
% figure
[fitresult, gof] = createFit_Automate(TempMeasureRefined,GyroDrift_Yaw,PlotName);
Gyro_Correction_Yaw.P1 = 0;
Gyro_Correction_Yaw.P2 = fitresult.p1;
Gyro_Correction_Yaw.Offset = fitresult.p2;
% cftool

save GyroDrift_OffsetCorrections.mat Gyro_Correction_Roll Gyro_Correction_Pitch Gyro_Correction_Yaw
