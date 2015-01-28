% Copyright 2014 The MathWorks, Inc.
%This script assumes that you have: 
% a) First collected data of gyro drift and temperature
% b) Ran the TempCorrect_OfflineTest to filter the data

%% Correct for Roll Drift First
Ts = 1/400;
StartTime =10;
StartTick = StartTime/Ts;

GyroDrift_Roll = Roll_Gyro_filtered.signals.values(StartTick:end,2);

TempMeasureRefined = FilteredTemp.signals.values(StartTick:end,2);

[SortedTemp IndexSort] = sort(TempMeasureRefined);
plot(SortedTemp,GyroDrift_Roll(IndexSort))
re_ordered = GyroDrift_Roll(IndexSort);

plot(TempMeasureRefined,GyroDrift_Roll,'.')
cftool




%% Correct for Pitch Drift 

Ts = 1/400;
StartTime =10;
StartTick = StartTime/Ts;

GyroDrift_Pitch = Pitch_Gyro_filtered.signals.values(StartTick:end,2);
TempMeasureRefined = FilteredTemp.signals.values(StartTick:end,2);

plot(TempMeasureRefined,GyroDrift_Pitch)

cftool



%% Correct Yaw Drift

Ts = 1/400;
StartTime =10;
StartTick = StartTime/Ts;

GyroDrift_Yaw = Yaw_Gyro_filtered.signals.values(StartTick:end,2);
TempMeasureRefined = FilteredTemp.signals.values(StartTick:end,2);

plot(TempMeasureRefined,GyroDrift_Yaw)
cftool

