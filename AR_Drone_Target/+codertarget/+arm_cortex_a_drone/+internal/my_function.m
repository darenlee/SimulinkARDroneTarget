% Copyright 2014 The MathWorks, Inc.
function my_function()
    ab = getActiveConfigSet(gcs);
    IP_String  = codertarget.data.getParameterValue(ab,'IP');
    setenv('AR_DRONE_IP_ADDRESS',IP_String)
end