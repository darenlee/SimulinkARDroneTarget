% Copyright 2014 The MathWorks, Inc.

disp('===================================================================')
disp('          Please browse to location of Code Sourcery Directory     ')
disp('===================================================================')
disp(char(10));
FolderIsLegit = 0;
while(FolderIsLegit==0)
folder_name = uigetdir('c:\', 'Select Code Sourcery Directory Location, Look for CodeSourcery\Sourcery_CodeBench_Lite_for_ARM_GNU_Linux\bin');
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
cd AR_Drone_Target
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

