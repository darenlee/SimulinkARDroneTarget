userInput = questdlg('Are you sure you wish to overwrite the calibration data used by the AR Drone models to the sensor default specifications?','Confirm save', 'Yes', 'No','No');

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

        setValue(accOffEntry,[2048 2048 2048]);
        setValue(accGainEntry,[512 512 512]);
        setValue(gyroEntry,[0 0 0]);
        setValue(magEntry,[0 0 0]);
        saveChanges(dict);
        msgbox('Saved the calibration data to the AR Drone data dictionairy. All models linked to the data dictionairy will use the saved calibration parameters.');
    otherwise
        msgbox('User cancelled save, data dictionairy calibration parameters were not overwritten.');
end