# AR Drone 2.0 MATLAB/Simulink Target

The AR Drone 2.0 Target provides automatic code generation support for Simulink models for the Parrot AR Drone 2.0. 
The provided Simulink blocks allow you to read all the sensors and both cameras on the AR Drone 2.0. You can also control the motors to make the AR Drone 2.0 hover.

## Before you can use the AR Drone 2.0 Target
1. Download and install MATLAB R2016a or higher for Windows.
2. Install a C compiler. You can evaluate `mex -setup c` in MATLAB to see if you have a compiler installed. The free MinGW64 compiler can be installed from the MATLAB Add-Ons Explorer
3. Download and install the Code Sourcery ARM compiler. This is a free compiler which you can download using [this direct link.](https://sourcery.mentor.com/sgpp/lite/arm/portal/package8738/public/arm-none-linux-gnueabi/arm-2011.03-41-arm-none-linux-gnueabi.exe). If you are using Windows 8 or newer you will need to run the installer in the Windows 7 compatibility mode

## How to open the AR Drone 2.0 Target
1. Use the _Download Zip_ button on this page
2. Extract the zip to a destination of your choice
3. Navigate to the folder where you extracted the AR Drone 2.0 Target in MATLAB and open AR_Drone.prj

## How to use the Simulink project
1. Opening AR_Drone.prj will cause a startup script to set up MATLAB for the AR Drone 2.0 Target. Closing the project disables the AR Drone 2.0 Target functionality
2. The Simulink project provides you with shortcuts on the MATLAB toolstrip. Things such as the documentation or calibration models can be easily accessed from there
3. The folder structure for the files is such that
  1. Pre made Simulink models are inside the AR_Drone_Models folder
  2. Library blocks, C source code and custom scripts are in the AR_Drone_Target folder 