% Copyright 2014 The MathWorks, Inc.
function my_function()
    ab = getActiveConfigSet(bdroot); %was gcs but this is not the best method
    IP_String  = codertarget.data.getParameterValue(ab,'IP');
    setenv('AR_DRONE_IP_ADDRESS',IP_String)
end
