% Copyright 2014 The MathWorks, Inc.
function blkStruct = slblocks
blkStruct.Name = 'AR Drone 2 Library Blocks'; %Display name
blkStruct.OpenFcn = 'AR_Drone_2_Library'; %Library name
blkStruct.MaskDisplay = '';
Browser(1).Library = 'AR_Drone_2_Library'; %Library name

%   Copyright 2010 The MathWorks, Inc.

Browser(1).Name='AR Drone 2 Target';%Display name
blkStruct.Browser = Browser;
