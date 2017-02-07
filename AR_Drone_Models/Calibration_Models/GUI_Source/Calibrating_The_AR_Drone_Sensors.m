function varargout = Calibrating_The_AR_Drone_Sensors(varargin)
% calibrating_the_ar_drone_sensors MATLAB code for Calibrating_The_AR_Drone_Sensors.fig
%      calibrating_the_ar_drone_sensors, by itself, creates a new calibrating_the_ar_drone_sensors or raises the existing
%      singleton*.
%
%      H = calibrating_the_ar_drone_sensors returns the handle to a new calibrating_the_ar_drone_sensors or the handle to
%      the existing singleton*.
%
%      calibrating_the_ar_drone_sensors('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in calibrating_the_ar_drone_sensors.M with the given input arguments.
%
%      calibrating_the_ar_drone_sensors('Property','Value',...) creates a new calibrating_the_ar_drone_sensors or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Calibrating_The_AR_Drone_Sensors_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Calibrating_The_AR_Drone_Sensors_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Calibrating_The_AR_Drone_Sensors

% Last Modified by GUIDE v2.5 10-Jun-2016 12:31:09


% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Calibrating_The_AR_Drone_Sensors_OpeningFcn, ...
                   'gui_OutputFcn',  @Calibrating_The_AR_Drone_Sensors_OutputFcn, ...
                   'gui_LayoutFcn',  [] , ...
                   'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT



% --- Executes just before Calibrating_The_AR_Drone_Sensors is made visible.
function Calibrating_The_AR_Drone_Sensors_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Calibrating_The_AR_Drone_Sensors (see VARARGIN)
% Choose default command line output for Calibrating_The_AR_Drone_Sensors
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

%% Add custom data

%intialization value used to see if a parameter has been set allready,
%it is important that this value is not a logical calibration value
initializationValue = 0;
handles.initializationValue = initializationValue;
guidata(hObject, handles);
% calibrationData to save the average accelerometer x+,x-,y+,y-,z+,z-
calibrationData = zeros(6,1) + initializationValue; 
handles.calibrationData = calibrationData;
guidata(hObject, handles);
% calibrationParameters to save 
calibrationParameters = zeros(12,1) + initializationValue; 
handles.calibrationParameters = calibrationParameters;
guidata(hObject, handles);
calibrationMode = 1;
handles.calibrationMode = calibrationMode;
guidata(hObject, handles);

% UIWAIT makes Calibrating_The_AR_Drone_Sensors wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Calibrating_The_AR_Drone_Sensors_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on selection change in listbox2.
function listbox2_Callback(hObject, eventdata, handles)
% hObject    handle to listbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: contents = cellstr(get(hObject,'String')) returns listbox2 contents as cell array
%        contents{get(hObject,'Value')} returns selected item from listbox2


% --- Executes during object creation, after setting all properties.
function listbox2_CreateFcn(hObject, eventdata, handles)
% hObject    handle to listbox2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: listbox controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end


% --- Executes on button press in StartCalibrationButton.
function StartCalibrationButton_Callback(hObject, eventdata, handles)

calibrationMode = get(handles.CalibrationSelecter,'Value');
% verify whether a correct calibration mode was set
if calibrationMode > 1
    % save the mode that is used for calibration
    handles.calibrationMode = calibrationMode;
    guidata(hObject, handles);
    set(handles.UserInstructions,'String','The calibration model is now being executed, when execution is complete press the "Process data" button to use this data to compute the calibration parameters. Note that some parameters require two different calibration measurements in opposite directions');
else
    set(handles.UserInstructions,'String','Please select a sensor to calibrate from the drop down menu before pressing "Start Calibration"');
end

% start the executable on the drone
drone = tcpip('192.168.1.1',23);
fopen(drone);
query(drone,'./update/Calibrating_The_AR_Drone_Sensors_Model.elf -w');

% run the simulink model
stopTime = 5;
if calibrationMode == 9
    stopTime = 60;
end
set_param('Calibrating_The_AR_Drone_Sensors_Model/Has Stop Time Been Reached','stopTime',num2str(stopTime));
set_param('Calibrating_The_AR_Drone_Sensors_Model','SimulationCommand','connect');
set_param('Calibrating_The_AR_Drone_Sensors_Model','SimulationCommand','start');

waitBarHandle = waitbar(0,['Running a calibration on the AR Drone of ' num2str(stopTime) ' seconds.']);
dt = 0.1;
t = 0;
while ~strcmp(get_param('Calibrating_The_AR_Drone_Sensors_Model','SimulationStatus'),'stopped')
    pause(dt);
    t = t + dt;
    waitbar(t/stopTime,waitBarHandle);
end

close(waitBarHandle);

%% load allready saved data
calibrationData = handles.calibrationData;
calibrationParameters = handles.calibrationParameters;
%% load the new data 
AccelCalib = evalin('base','AccelCalib');
GyroCalib = evalin('base','GyroCalib');
MagnetoCalib = evalin('base','MagnetoCalib');
%% save the new data
switch calibrationMode
    case 2 % x+
        calibrationData(1) = mean(double(AccelCalib.signals.values(:,1)));
    case 3 % x-
        calibrationData(2) = mean(double(AccelCalib.signals.values(:,1)));
    case 4 % y+
        calibrationData(3) = mean(double(AccelCalib.signals.values(:,2)));
    case 5 % y-
        calibrationData(4) = mean(double(AccelCalib.signals.values(:,2)));
    case 6 % z+
        calibrationData(5) = mean(double(AccelCalib.signals.values(:,3)));
    case 7 % z-
        calibrationData(6) = mean(double(AccelCalib.signals.values(:,3)));
    case 8 % gyro
        calibrationParameters(7:9) = mean(double(GyroCalib.signals.values));
    case 9 % magneto
        calibrationParameters(10:12) = 0.5 * (max(double(MagnetoCalib.signals.values)) + min(double(MagnetoCalib.signals.values))); % rough version
    otherwise
        set(handles.UserInstructions,'String','No valid calibration has been completed, please select a calibration mode from the drop down menu and press "Start calibration". When the calibration is complete press "Process data"');
end
handles.calibrationData = calibrationData;
handles.calibrationParameters = calibrationParameters;
guidata(hObject, handles);
%% process the calibration data
% verify whether the calibration actually returned any data
if size(AccelCalib,1) == 0 || size(GyroCalib,1) == 0 || size(MagnetoCalib,1) == 0
   msgbox('The model on the drone is no longer operating properly, please rebuild the model using the Build and Upload button') ;
else
    switch calibrationMode
        case {2,3}
            % check if both X positive and negative calibrations have been executed
            if calibrationData(1) ~= handles.initializationValue && calibrationData(2) ~= handles.initializationValue
                calibrationData(1)
                calibrationData(2)
                handles.calibrationParameters(1) = 0.5 + (calibrationData(1) + calibrationData(2))/2;
                set(handles.xAccOffText,'String',num2str(handles.calibrationParameters(1)));
                handles.calibrationParameters(4) = 0.5 + (calibrationData(1) - calibrationData(2))/2;
                set(handles.xAccGainText,'String',num2str(handles.calibrationParameters(4)));
            else
                set(handles.xAccOffText,'String','TBD');
                set(handles.xAccGainText,'String','TBD');
            end

        case {4,5}
            % check if both Y positive and negative calibrations have been executed
            if calibrationData(3) ~= handles.initializationValue && calibrationData(4) ~= handles.initializationValue
                handles.calibrationParameters(2) = 0.5 + (calibrationData(3) + calibrationData(4))/2;
                set(handles.yAccOffText,'String',num2str(handles.calibrationParameters(2)));
                handles.calibrationParameters(5) = 0.5 + (calibrationData(3) - calibrationData(4))/2;
                set(handles.yAccGainText,'String',num2str(handles.calibrationParameters(5)));
                else
                set(handles.yAccOffText,'String','TBD');
                set(handles.yAccGainText,'String','TBD');
            end
        case {6,7}
            % check if both Z positive and negative calibrations have been executed
            if calibrationData(5) ~= handles.initializationValue && calibrationData(6) ~= handles.initializationValue
                handles.calibrationParameters(3) = 0.5 + (calibrationData(5) + calibrationData(6))/2;
                set(handles.zAccOffText,'String',num2str(handles.calibrationParameters(3)));
                handles.calibrationParameters(6) = 0.5 + (calibrationData(5) - calibrationData(6))/2;
                set(handles.zAccGainText,'String',num2str(handles.calibrationParameters(6)));
                else
                set(handles.zAccOffText,'String','TBD');
                set(handles.zAccGainText,'String','TBD');
            end
        case 8
            set(handles.xGyroOffText,'String',num2str(handles.calibrationParameters(7)));
            set(handles.yGyroOffText,'String',num2str(handles.calibrationParameters(8)));
            set(handles.zGyroOffText,'String',num2str(handles.calibrationParameters(9)));
        case 9
            set(handles.xMagOffText,'String',num2str(handles.calibrationParameters(10)));
            set(handles.yMagOffText,'String',num2str(handles.calibrationParameters(11)));
            set(handles.zMagOffText,'String',num2str(handles.calibrationParameters(12)));
        otherwise
    end
    guidata(hObject, handles);
end


% --- Executes on button press in loadParamButton.
function loadParamButton_Callback(hObject, eventdata, handles)
% hObject    handle to loadParamButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

%% Load the data from the dictionary
dict = Simulink.data.dictionary.open('ArDroneDataDictionary.sldd');
Data = getSection(dict,'Design Data');
accOffEntry = getEntry(Data,'accelerometerXyzOffsets');
accGainEntry = getEntry(Data,'accelerometerXyzGains');
gyroEntry = getEntry(Data,'gyroXyzOffsets');
magEntry = getEntry(Data,'magnetoXyzOffsets');

%% Set the data inside the GUI data container

handles.calibrationParameters(1:3) = getValue(accOffEntry);
handles.calibrationParameters(4:6) = getValue(accGainEntry);
handles.calibrationParameters(7:9) = getValue(gyroEntry);
handles.calibrationParameters(10:12) = getValue(magEntry);
guidata(hObject, handles);

%% Update the text boxes
updateAllText(handles);


function updateAllText(handles)
set(handles.xAccOffText,'String',num2str(handles.calibrationParameters(1)));
set(handles.xAccGainText,'String',num2str(handles.calibrationParameters(4)));
set(handles.yAccOffText,'String',num2str(handles.calibrationParameters(2)));
set(handles.yAccGainText,'String',num2str(handles.calibrationParameters(5)));
set(handles.zAccOffText,'String',num2str(handles.calibrationParameters(3)));
set(handles.zAccGainText,'String',num2str(handles.calibrationParameters(6)));
set(handles.xGyroOffText,'String',num2str(handles.calibrationParameters(7)));
set(handles.yGyroOffText,'String',num2str(handles.calibrationParameters(8)));
set(handles.zGyroOffText,'String',num2str(handles.calibrationParameters(9)));
set(handles.xMagOffText,'String',num2str(handles.calibrationParameters(10)));
set(handles.yMagOffText,'String',num2str(handles.calibrationParameters(11)));
set(handles.zMagOffText,'String',num2str(handles.calibrationParameters(12)));


% --- Executes on button press in saveParamButton.
function saveParamButton_Callback(hObject, eventdata, handles)
% hObject    handle to saveParamButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

userInput = questdlg('Are you sure you wish to overwrite the calibration data used by the AR Drone models?','Confirm save', 'Yes', 'No','No');

switch userInput
    case 'Yes'
        %% open the dictionary
        dict = Simulink.data.dictionary.open('ArDroneDataDictionary.sldd');
        Data = getSection(dict,'Design Data');
        accOffEntry = getEntry(Data,'accelerometerXyzOffsets');
        accGainEntry = getEntry(Data,'accelerometerXyzGains');
        gyroEntry = getEntry(Data,'gyroXyzOffsets');
        magEntry = getEntry(Data,'magnetoXyzOffsets');

        %% store values in the dictionairy

        setValue(accOffEntry,handles.calibrationParameters(1:3));
        setValue(accGainEntry,handles.calibrationParameters(4:6));
        setValue(gyroEntry,handles.calibrationParameters(7:9));
        setValue(magEntry,handles.calibrationParameters(10:12));
        saveChanges(dict);
        msgbox('Saved the calibration data to the AR Drone data dictionairy. All models linked to the data dictionairy will use the saved calibration parameters.');
    otherwise
        msgbox('User cancelled save, data dictionairy calibration parameters were not overwritten.');
end



% --- Executes on button press in BuildButton.
function BuildButton_Callback(hObject, eventdata, handles)
% hObject    handle to BuildButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set(handles.UserInstructions,'String','Building and uploading the model to the AR Drone 2.0, please wait untill the process is complete.');
pause(0.1); % without this pause the build process starts before the GUI has time to update the text
if bdIsLoaded('Calibrating_The_AR_Drone_Sensors_Model')==0
    open('Calibrating_The_AR_Drone_Sensors_Model');
end
rtwbuild('Calibrating_The_AR_Drone_Sensors_Model');    % default behaviour is to run the program
set_param('Calibrating_The_AR_Drone_Sensors_Model','SimulationCommand','connect'); % so connect to the drone
set_param('Calibrating_The_AR_Drone_Sensors_Model','SimulationCommand','stop'); % and stop the program
set(handles.UserInstructions,'String','Completed the build and upload process, use the selection box above to select the desired calibration mode and follow the instructions provided.');


% --- Executes on selection change in CalibrationSelecter.
function CalibrationSelecter_Callback(hObject, eventdata, handles)
% hObject    handle to CalibrationSelecter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
switch get(hObject,'Value')
    case 2
        set(handles.UserInstructions,'String','Accelerometer X+:  Place the drone such that the camera is pointing straight up and does not move (an easy way to do this is to let the back of the AR Drone rest on a flat surface while pressing the feet of the AR Drone against a flat vertical wall). If the model has not yet been build and uploaded do this first, else press "Start calibration". For the full X axis accelerometer calibration another calibration measurement needs to be done for the X- direction');
    case 3
        set(handles.UserInstructions,'String','Accelerometer X-:  Place the drone such that the camera is pointing straight down and does not move (an easy way to do this is to let the front of the AR Drone rest on a flat surface while pressing the feet of the AR Drone against a flat vertical wall). If the model has not yet been build and uploaded do this first, else press "Start calibration". For the full X axis accelerometer calibration another calibration measurement needs to be done for the X+ direction');
    case 4
        set(handles.UserInstructions,'String','Accelerometer Y+:  Place the drone on its side with the top facing you and the camera facing right (an easy way to do this is to let the side of the AR Drone rest on a flat surface while pressing the feet of the AR Drone against a flat vertical wall). If the model has not yet been build and uploaded do this first, else press "Start calibration". For the full Y axis accelerometer calibration another calibration measurement needs to be done for the Y- direction');
    case 5
        set(handles.UserInstructions,'String','Accelerometer Y-:  Place the drone on its side with the top facing you and the camera facing left (an easy way to do this is to let the side of the AR Drone rest on a flat surface while pressing the feet of the AR Drone against a flat vertical wall). If the model has not yet been build and uploaded do this first, else press "Start calibration". For the full Y axis accelerometer calibration another calibration measurement needs to be done for the Y+ direction');
    case 6
        set(handles.UserInstructions,'String','Accelerometer Z+:  Place the AR Drone 2.0 on a flat horizontal surface such that it is standing on its feet and does not move. If the model has not yet been build and uploaded do this first, else press "Start calibration". For the full Z axis accelerometer calibration another calibration measurement needs to be done for the Z- direction');
    case 7
        set(handles.UserInstructions,'String','Accelerometer Z-:  Place the AR Drone 2.0 such that it is perfectly level and upside down (its feet should point at the sky) and does not move (an easy way to achieve this is to press the AR Drone against the bottom of a level table). If the model has not yet been build and uploaded do this first, else press "Start calibration". For the full Z axis accelerometer calibration another calibration measurement needs to be done for the Z+ direction');
    case 8
        set(handles.UserInstructions,'String','Gyroscope:  Place the AR Drone on a flat horizontal surface such that it is standing on its feet. If the model has not yet been build and uploaded do this first, else press "Start calibration" and do not move the drone during the calibration run.');
    case 9
        set(handles.UserInstructions,'String','Magnetometer:  Hold the drone in your hand. If the model has not yet been build and uploaded do this first, else press "Start calibration" and then rotate the drone at least 180 degrees in all three cardinal directions (around its roll, pitch and yaw axis) during the calibration.');
    otherwise
        set(handles.UserInstructions,'String','This user interface will allow you to calibrate the AR Drone 2.0 sensors and save the paramters to the AR Drone data dictionairy. First make sure the AR Drone 2.0 is turned on and connected to the PC and then click "Build and upload", you only need to do this once. Once the upload process is complete you can select the desired calibration mode from the drop down menu, it will then give you further instuctions on how to place the drone for that calibration.');
end

% Hints: contents = cellstr(get(hObject,'String')) returns CalibrationSelecter contents as cell array
%        contents{get(hObject,'Value')} returns selected item from CalibrationSelecter


% --- Executes during object creation, after setting all properties.
function CalibrationSelecter_CreateFcn(hObject, eventdata, handles)
% hObject    handle to CalibrationSelecter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: popupmenu controls usually have a white background on Windows.
%       See ISPC and COMPUTER.
if ispc && isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor','white');
end
