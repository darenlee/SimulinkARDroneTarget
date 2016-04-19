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
disp('                  \AR_Drone\registry\thirdpartytools                           ')
disp('===============================================================================')
disp(char(10));

PassFail = RegisterThirdPartyCompilerXML(folder_name);


if PassFail==1
    disp('Compiler Succesfully Registered');
end

disp(char(10));
disp('===============================================================================')
disp('                              Updating Path Settings')
disp('===============================================================================')
disp(char(10));

addpath([pwd]);
addpath([pwd '\blocks']);
addpath([pwd '\registry']);
savepath
% save_path
% 
% addpath([pwd]);
% addpath([pwd '\blocks']);
% addpath([pwd '\registry']);
% savepath

