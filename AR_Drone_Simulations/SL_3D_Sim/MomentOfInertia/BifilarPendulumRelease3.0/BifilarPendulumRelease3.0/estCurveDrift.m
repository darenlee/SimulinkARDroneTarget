function [newparams,resnorm,exitflag] = estCurveDrift(x,t,init)

% Run zeroCrossing.m to get an idea of the period of oscillation. This
% value can be used in the initial value condition to estimate the curve.
% Make sure to remove inital data points since they are disturbances.
% Remove data points till the curve resembles a dampled sine wave and then
% pass it as input arguments to this function.
 
%     FILE NAME                    AXIS         DATA POINTS TO CONSIDER      INIT VECTOR
% 1.  Gyro_reading1 (2 deg)        YAW                 4001:end             [4,0,0.02,1.4]  
% 2.  Gyro_reading2 (10 deg)       YAW                2501:43000            [4,0,0.02,1.4] 
% 3.  Gyro_reading3 (2 deg)        ROLL                2484:end
% 4.  Gyro_reading4 (10 deg)       ROLL
% 5.  Gyro_reading7 (2 deg)        PITCH
% 6.  Gyro_reading8 (10 deg)       PITCH

x = x - mean(x);
%t = t - t(1);

% Define curve model functions
expsin = @(a,b,c,wn,m,off,t) a*sin(wn* t + b) .* exp(-c * t)+m.*t+off;
lsqexpsin = @(p, t)expsin(p(1), p(2), p(3),p(4),p(5),p(6),t);


% Fit model to data. Choose the init values according to the data. For
% validating data sets of the same axis, just change the first value in the
% init vector. 
% init = [4,0,0.02,1.4,-0.15,5];
[newparams, resnorm,~,exitflag] = lsqcurvefit(lsqexpsin, init, t, x);

plot(t,x,'-r',t, lsqexpsin(newparams, t),'.b');