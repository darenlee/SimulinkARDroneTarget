% Copyright 2014 The MathWorks, Inc.

disp('===================================================================')
disp('          Please browse to location of Code Sourcery Directory     ')
disp('===================================================================')
disp(char(10));
FolderIsLegit = 0;

% check the default folder before asking the user
if exist('C:\Program Files (x86)\CodeSourcery\Sourcery G++ Lite\bin','dir') ~= 0
    folder_name = 'C:\Program Files (x86)\CodeSourcery\Sourcery G++ Lite\bin';
    ListOfFiles =ls(folder_name);
    if size(ListOfFiles,2)>=22
    FirstFile = ListOfFiles(3,1:22);
    end
    if  strcmp('arm-none-linux-gnueabi',FirstFile)==1
        FolderIsLegit = 1;
    end
end

% If the default folder was not legit, prompt the user
while(FolderIsLegit==0)
folder_name = uigetdir('c:\', 'Please select the Code Sourcery bin directory, the following default location was not found: C:\Program Files (x86)\CodeSourcery\Sourcery G++ Lite\bin');
ListOfFiles =ls(folder_name);

if size(ListOfFiles,2)>=22
FirstFile = ListOfFiles(3,1:22);
end
if  strcmp('arm-none-linux-gnueabi',FirstFile)==1
    FolderIsLegit = 1;
end

end


disp(char(10));
disp('===============================================================================')
disp('                 Generating XML File for Third Party Tools in                  ')
disp('                  \AR_Drone_Target\registry\thirdpartytools                           ')
disp('===============================================================================')
disp(char(10));

% change folder since the P code file places the xml files in the current
% directory
cd ..
PassFail = RegisterThirdPartyCompilerXML(folder_name);
cd ..

if PassFail==1
    disp('Compiler Succesfully Registered');
end

disp(char(10));
disp('===============================================================================')
disp('                              Updating Path Settings')
disp('===============================================================================')
disp(char(10));

savepath

