function varargout = Example3_Calibrating_The_AR_Drone(varargin)
% EXAMPLE3_CALIBRATING_THE_AR_DRONE MATLAB code for Example3_Calibrating_The_AR_Drone.fig
%      EXAMPLE3_CALIBRATING_THE_AR_DRONE, by itself, creates a new EXAMPLE3_CALIBRATING_THE_AR_DRONE or raises the existing
%      singleton*.
%
%      H = EXAMPLE3_CALIBRATING_THE_AR_DRONE returns the handle to a new EXAMPLE3_CALIBRATING_THE_AR_DRONE or the handle to
%      the existing singleton*.
%
%      EXAMPLE3_CALIBRATING_THE_AR_DRONE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in EXAMPLE3_CALIBRATING_THE_AR_DRONE.M with the given input arguments.
%
%      EXAMPLE3_CALIBRATING_THE_AR_DRONE('Property','Value',...) creates a new EXAMPLE3_CALIBRATING_THE_AR_DRONE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before Example3_Calibrating_The_AR_Drone_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to Example3_Calibrating_The_AR_Drone_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help Example3_Calibrating_The_AR_Drone

% Last Modified by GUIDE v2.5 11-May-2016 14:04:05


% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @Example3_Calibrating_The_AR_Drone_OpeningFcn, ...
                   'gui_OutputFcn',  @Example3_Calibrating_The_AR_Drone_OutputFcn, ...
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


% --- Executes just before Example3_Calibrating_The_AR_Drone is made visible.
function Example3_Calibrating_The_AR_Drone_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to Example3_Calibrating_The_AR_Drone (see VARARGIN)
% Choose default command line output for Example3_Calibrating_The_AR_Drone
handles.output = hObject;

% Update handles structure
guidata(hObject, handles);

% UIWAIT makes Example3_Calibrating_The_AR_Drone wait for user response (see UIRESUME)
% uiwait(handles.figure1);


% --- Outputs from this function are returned to the command line.
function varargout = Example3_Calibrating_The_AR_Drone_OutputFcn(hObject, eventdata, handles) 
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

drone = tcpip('192.168.1.1',23);
fopen(drone);
query(drone,'./update/Example3_Calibrating_The_AR_Drone_Model.elf -w');

set_param('Example3_Calibrating_The_AR_Drone_Model','SimulationCommand','connect');
set_param('Example3_Calibrating_The_AR_Drone_Model','SimulationCommand','start');
% hObject    handle to StartCalibrationButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton2.
function pushbutton2_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton2 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in pushbutton3.
function pushbutton3_Callback(hObject, eventdata, handles)
% hObject    handle to pushbutton3 (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)


% --- Executes on button press in BuildButton.
function BuildButton_Callback(hObject, eventdata, handles)
% hObject    handle to BuildButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
if bdIsLoaded('Example3_Calibrating_The_AR_Drone_Model')==0
    open('Example3_Calibrating_The_AR_Drone_Model');
end
rtwbuild('Example3_Calibrating_The_AR_Drone_Model');    % default behaviour is to run the program
set_param('Example3_Calibrating_The_AR_Drone_Model','SimulationCommand','connect');
% set_param('Example3_Calibrating_The_AR_Drone_Model','SimulationCommand','start');
set_param('Example3_Calibrating_The_AR_Drone_Model','SimulationCommand','stop');

% --- Executes on button press in TerminateButton.
function TerminateButton_Callback(hObject, eventdata, handles)
% hObject    handle to TerminateButton (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
set_param('Example3_Calibrating_The_AR_Drone_Model','SimulationCommand','stop')


% --- Executes on selection change in CalibrationSelecter.
function CalibrationSelecter_Callback(hObject, eventdata, handles)
% hObject    handle to CalibrationSelecter (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

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
