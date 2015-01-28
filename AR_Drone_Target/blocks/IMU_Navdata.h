#ifndef IMU_DEFINE
#define IMU_DEFINE

#ifndef MATLAB_MEX_FILE

	#include <stdint.h>


	/*------The functions below will either be called by above wrapper code directly or called other internal functions-------*/

	int IMU_Navdata_init (void) ;
	int IMU_Navdata_update(unsigned short *y);
	void IMU_Navdata_stop (void) ;

	static void cropbuffer (int cropsize);
	void Acquire_Navdata_Bytes (void);


	int16_t height () ;       

	int16_t getRawX () ;
	int16_t getRawY () ;
	int16_t getRawZ () ;

	 

		  
	#define NAVDATA_PACKET_SIZE 60
	#define NAVDATA_START_BYTE 0x3a 
	#define NAVDATA_BUFFER_SIZE 60 

		struct NavdataPort {
			uint8_t isInitialized;
			uint16_t bytesRead;
			uint32_t totalBytesRead;
			uint32_t packetsRead;
			uint32_t checksum_errors;
			uint8_t buffer[NAVDATA_BUFFER_SIZE];
		} ;

		struct BaroCalibration {
			int16_t ac1;
			int16_t ac2;
			int16_t ac3;
			uint16_t ac4;
			uint16_t ac5;
			uint16_t ac6;
			int16_t b1;
			int16_t b2;
			int16_t mb;
			int16_t mc;
			int16_t md;

			// These values are calculated
			int32_t b5;
		} ;
		
	  typedef struct  __attribute__ ((packed)){
			uint16_t taille;
			uint16_t nu_trame;

			uint16_t ax;
			uint16_t ay;
			uint16_t az;

			int16_t vx;
			int16_t vy;
			int16_t vz;
			uint16_t temperature_acc;
			uint16_t temperature_gyro;

			uint16_t ultrasound;

			uint16_t us_debut_echo;
			uint16_t us_fin_echo;
			uint16_t us_association_echo;
			uint16_t us_distance_echo;

			uint16_t us_curve_time;
			uint16_t us_curve_value;
			uint16_t us_curve_ref;

			uint16_t nb_echo;

			uint32_t sum_echo; //unsigned long
			int16_t gradient;

			uint16_t flag_echo_ini;

			int32_t pressure;
			uint16_t temperature_pressure;

			int16_t my;
			int16_t mx;
			int16_t mz;

			uint16_t chksum;

		}IMU_Packets;
	// #ifndef MATLAB_MEX_FILE 
	// 	 __attribute__ ((packed));
	// 	#else
	//      ;
	// #endif
	//     
	   
		
		struct NavdataPort port ;
		//struct IMU_Packets navdata ;
		IMU_Packets navdata ;
		
		int IMU_fd ; // file descriptor for opening serial port
		int isInitialized; // flag to indicate IMU initialization
		
		
		
	/*------LCT Wrapper Functions for Simulink to use-------*/

	void MDL_IMU_start(void); //will call IMU_Navdata_init()
	void MDL_IMU_term(void); //will call IMU_Navdata_stop()
	//void MDL_IMU_step(IMU_Packets *y1); //will call IMU_Navdata_update()

	void MDL_IMU_step(IMU_Packets *y1, int *y2); //will call IMU_Navdata_update()



#else //else you're doing a MEX build



	#include <stdint.h>


	typedef struct {
			uint16_t taille;
			uint16_t nu_trame;

			uint16_t ax;
			uint16_t ay;
			uint16_t az;

			int16_t vx;
			int16_t vy;
			int16_t vz;
			uint16_t temperature_acc;
			uint16_t temperature_gyro;

			uint16_t ultrasound;

			uint16_t us_debut_echo;
			uint16_t us_fin_echo;
			uint16_t us_association_echo;
			uint16_t us_distance_echo;

			uint16_t us_curve_time;
			uint16_t us_curve_value;
			uint16_t us_curve_ref;

			uint16_t nb_echo;

			uint32_t sum_echo; //unsigned long
			int16_t gradient;

			uint16_t flag_echo_ini;

			int32_t pressure;
			uint16_t temperature_pressure;

			int16_t my;
			int16_t mx;
			int16_t mz;

			uint16_t chksum;

		}IMU_Packets;
		
	void MDL_IMU_step(IMU_Packets *y1, int *y2); //will call IMU_Navdata_update()


#endif


#endif