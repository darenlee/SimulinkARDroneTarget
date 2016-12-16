%% Calculate Drone Moment of Inertia
% September 4, 2014

%% Method
% To calcuate the moment of inertia about each axis of the drone, a bifilar
% pendulum method was used.  The method is described in detail in the
% article,
% <http://www.mathworks.com/company/newsletters/articles/improving-mass-moment-of-inertia-measurements.html
% Improving Mass Moment of Inertia Measurements>
% 
% The mass momemnt of inertia can be calculated using a linearized formula
% as described, or the full non-linear dynamic equation can be represented
% in Simulink and parameter estimation can be used to find all unknown
% parameters including the moment of inertia.
%
% Only the linearized formula will be used to calculate the moment of
% ineratia here.

%% Load Raw Data
% The drone was attached to the bifilar pendulum to measure the motion
% about the Z-axis (yaw).  Gyroscope readings were collected for all three
% axis.
close all
load Gyro_reading2

figure
plot(GyroIntegration.signals.values)
legend('Roll','Pitch','Yaw')
title('Gyroscope Data')
xlabel('Points')
ylabel('Angle (seconds)')
grid on

%%
% By inpection, the indeces of the yaw data that we will use is 2501:43000.

ind = 2501:43000;

time = GyroIntegration.time(ind);
time = time - time(1); % start the new time vector at 0
yaw  = GyroIntegration.signals.values(ind,3);

figure
plot(time,yaw)
title('Yaw Data of Interest')
ylabel('Angle (degrees)')
xlabel('Time (seconds)')
grid on

%% Find Natural Frequency
% The equation to calculate the moment of inertia from the linearized
% equation of motion requires several physical constants and one unknown,
% the natural frequency.  We can find the natural frequency from the
% oscillations of the gyroscope data.  We will use a curve fitting function
% to find the equation of the decaying sine wave for the oscillations. The
% form of the equation is:
%
% $$y(t) = A \cdot e^{-\lambda t}\cdot \sin\left(\omega_n t + \phi\right) + m \cdot t + b$$
%
% The additional terms are a line to correct for any drift in the sensors
% over time (refer to the roll reading in the first figure).

init = [0,0,0,2,0,0];
[params,resnorm,exitflag] = estCurveDrift(yaw,time,init);
title('Yaw Data with Curve Fit')
xlabel('Time (seconds)')
ylabel('Angle (Degrees)')
legend('Data','Curve Fit')
wn = params(4)

%% Calculate Inertia
% The equation for calculating the inertia about the vertical axis of the
% bifilar pendulum is:
% 
% $$ I = \frac{mgD^2}{4h\omega_n^2} $$
%
% Where $m$ is the mass of the drone, $g$ is the gravitational
% acceleration, $D$ is the distance between the two stings of the pendulum,
% $h$ is the length of the pendulum strings, and $\omega_n$ is the
% natural frequency of the oscillations.
%
% We found the natural frequency from the curve fitting and the other
% parameters can be measured.

load droneMasses

m = m_indoorHull; %kg
D = 34.3/100;     % m
h = 187.3/100;    % m
g = 9.81;         % m/s^2

I = (m*g*D^2)/(4*h*wn^2)



