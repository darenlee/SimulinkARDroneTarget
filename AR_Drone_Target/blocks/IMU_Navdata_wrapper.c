#ifndef MATLAB_MEX_FILE

#include "IMU_Navdata.h"

#else

#include "IMU_Navdata.h"

#endif



void MDL_IMU_start()
{
    #ifndef MATLAB_MEX_FILE
    if (IMU_Navdata_init() == 0)
    {
      perror("Failed to initialize AR Drone Inertial Measurement Unit System!");
      printf("Failed to initialize AR Drone Inertial Measurement Unit System! \n");
    }  
    else
    {
     printf("IMU Initialization and Connection succesful! \n");     
     
    }
     
    #endif

}


void MDL_IMU_term()
{ 
    #ifndef MATLAB_MEX_FILE
    IMU_Navdata_stop();
    #endif
}


 
void MDL_IMU_step(IMU_Packets *y1, int *y2)
{ int ChkSumFlag;
  unsigned short GrabUltraSound; //was used to grab ultra sound readings, testing purposes only
    #ifndef MATLAB_MEX_FILE
    
    
    ChkSumFlag = IMU_Navdata_update(&GrabUltraSound);
    
    *y1 = navdata;    //pointer to the navdata global structure which gets updated from IMU_Navdata_update
    *y2 = ChkSumFlag; //output checksum value
    
    #endif
}