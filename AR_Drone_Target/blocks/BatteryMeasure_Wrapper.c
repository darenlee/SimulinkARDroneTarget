#ifndef MATLAB_MEX_FILE

// #include "i2c-dev.h"

#else

//#include "IMU_Navdata.h"

#endif


void BatteryMeasure_start()
{
    #ifndef MATLAB_MEX_FILE
	
		BatteryMeasure_init();
   
    #endif

}


void BatteryMeasure_term()
{ 
    #ifndef MATLAB_MEX_FILE
	
		//BatteryMeasure_stop(); //may not do anything for now
    
	#endif
}


 
void BatteryMeasure_step(float *y1)
{ 
float VoltageMeasure;

    
    #ifndef MATLAB_MEX_FILE
       
		BatteryMeasure_update(&VoltageMeasure); //send voltage/current via y1 
		*y1 = VoltageMeasure;
// 		*y2 = CurrentMeasure;
        
        //printf("Voltage measurement is : %f \n",VoltageMeasure);
		   
    #endif
}
