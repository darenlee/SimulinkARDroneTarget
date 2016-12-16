Two simulation models have been provided

1) SL_3D_SIM
This model uses the aerospace blockset to model six degrees of freedom of the quad-copter.
Experiments were conducted to measure the moment of inertia and thrust produced by the
propellers. This information are the main parameters used in describing the drone's
dynamics. A Simulink 3D Animation blockset is used to show the drone's attitude / orientation

To use:
Open the Simulink model, FullDroneSimulation_flightTunedController.slx
The model should already be configured to simulate by hitting the play button

2) SimMech
This folder contains all the files used to import the CAD model of the AR Drone created by 
Omar Osorio on GrabCad. SimMechanics is used to import these files into Simulink.
Simscape/Sim-Electronics are used to model the motor system. A full control system
modeled and simulated in this.

To use:
Run the script Start_SimMechanics_Demo.m which adds the folder to the MATLAB path.
This folder contains all the CAD information of the drone such as the STL visualizations.
Next, open up the model ARDRONE_SIM.slx and start the simulation



