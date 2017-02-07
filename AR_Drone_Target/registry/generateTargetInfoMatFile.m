% Copyright 2014 The MathWorks, Inc.
% Runs the gcc_codesourcery_arm_linux_gnueabihf m file to retrieve the
% target info and saves it to a .mat file which is called by rtwTargetInfo

[tc ~] =  gcc_codesourcery_arm_linux_gnueabihf();
tc = tc(1);
save gcc_codesourcery_arm_linux_gnueabihf_gmake_win64_v4_8.mat tc 