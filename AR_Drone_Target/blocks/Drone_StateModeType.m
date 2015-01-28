% Copyright 2014 The MathWorks, Inc.
classdef Drone_StateModeType < Simulink.IntEnumType
    % MATLAB enumeration class definition generated from template
    %   to track the active child state of AR_Drone_Full_Controller/Flight Controller1/Supervisory Flight Controller/Drone_State.
    
    enumeration
        None(0),
        WaitForHost(1),
		Initialize(2),
		Controlled_Flight(3),
		Landing_Sequence(4)
        Landing_Terminate(5)
    end

    methods (Static)

        function defaultValue = getDefaultValue()
            % GETDEFAULTVALUE  Returns the default enumerated value.
            %   If this method is not defined, the first enumeration is used.
            defaultValue = Drone_StateModeType.None;
        end

        function dScope = getDataScope()
            % GETDATASCOPE  Specifies whether the data type definition should be imported from,
            %               or exported to, a header file during code generation.
            dScope = 'Auto';
        end

        function desc = getDescription()
            % GETDESCRIPTION  Returns a description of the enumeration.
            desc = 'enumeration to track active child state of AR_Drone_Full_Controller/Flight Controller1/Supervisory Flight Controller/Drone_State';
        end

        function fileName = getHeaderFile()
            % GETHEADERFILE  Returns path to header file if non-empty.
            fileName = '';
        end

        function flag = addClassNameToEnumNames()
            % ADDCLASSNAMETOENUMNAMES  Indicate whether code generator applies the class name as a prefix
            %                          to the enumeration.
            flag = true;
        end

    end

end
