Simulink AR Drone Target
========================

Deploy MATLAB Simulink model automatically to Parrot AR Drone with Embedded Coder C code generation. These set of files contain a Simulink model for navigation and control which will allow the AR Drone 2.0 to hover. WiFi communication between a Simulink model running on a PC can receive telemetry and send commands to the drone for take-off and hover mode.

Tested in MATLAB R2014a and R2014b in Windows 7 64-bit

To get started:

1. install CodeSourcery toolchain
	Register here: http://www.mentor.com/
	Download Sourcery CodeBench Lite for ARM GNU/Linux here: 
	https://sourcery.mentor.com/sgpp/lite/arm/portal/subscription?@template=lite

2. cd in MATLAB into AR_Drone_Target folder and run install_script.m

3. Pick ~\MentorGraphics\Sourcery_CodeBench_Lite_for_ARM_GNU_Linux\bin folder


We would also like to thank:

- Egoitz Martinez, Aimar Cordero Garcia and Asier Urcelay for providing us with the 3D VRML model of the AR Drone. Please contact this group on any questions related to the 3D model of the drone (Contact: egoitzml@gmail.com)

- The Paparazzi community for developing and providing source code for drivers of the AR Drone 2.0.

- Omar Osorio for providing us a CAD model for the AR Drone 2.0 for Sim-Mechanics Import
http://grabcad.com/library/drone-2-0/

NOTE:
If you have issues downloading the compiler, try this link 
https://sourcery.mentor.com/sgpp/lite/arm/portal/package8738/public/arm-none-linux-gnueabi/arm-2011.03-41-arm-none-linux-gnueabi.exe

