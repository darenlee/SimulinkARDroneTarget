//https://github.com/paparazzi/paparazzi/blob/master/sw/airborne/boards/ardrone/navdata.c
//http://stackoverflow.com/questions/13013387/clearing-the-serial-ports-buffer
//http://linux.die.net/man/3/tcflush
#include "IMU_Navdata.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdint.h>
#include <math.h>
//#include <iostream.h>
#include <stdio.h>

//extern isInitialized;

#ifndef ABS
#define ABS(val) ((val) < 0 ? -(val) : (val))
#endif

struct bmp180_baro_calibration
{
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
};
struct bmp180_baro_calibration baro_calibration;



static void baro_update_logic(void)
{
  static int32_t lastpressval = 0;
  static uint16_t lasttempval = 0;
  static int32_t lastpressval_nospike = 0;
  static uint16_t lasttempval_nospike = 0;
  static uint8_t temp_or_press_was_updated_last = 0; // 0 = press, so we now wait for temp, 1 = temp so we now wait for press

  static int sync_errors = 0;
  static int spikes = 0;
  static int spike_detected = 0;

  if (temp_or_press_was_updated_last == 0)  // Last update was press so we are now waiting for temp
  {
    // temp was updated
    temp_or_press_was_updated_last = 1;

    // This means that press must remain constant
    if (lastpressval != 0)
    {
      // If pressure was updated: this is a sync error
      if (lastpressval != navdata.pressure)
      {
        // wait for temp again
        temp_or_press_was_updated_last = 0;
        sync_errors++;
      //  printf("Baro-Logic-Error (expected updated temp, got press)\n");
      }
    }
  }
  else
  {
    // press was updated
    temp_or_press_was_updated_last = 0;

    // This means that temp must remain constant
    if (lasttempval != 0)
    {
      // If temp was updated: this is a sync error
      if (lasttempval != navdata.temperature_pressure)
      {
        // wait for press again
        temp_or_press_was_updated_last = 1;
        sync_errors++;
     //   printf("Baro-Logic-Error (expected updated press, got temp)\n");

      }
      else {
        // We now got valid pressure and temperature
       // navdata_baro_available = 1;
      }
    }
  }

  // Detected a pressure switch
  if(lastpressval != 0 && lasttempval != 0 && ABS(lastpressval - navdata.pressure) > ABS(lasttempval - navdata.pressure)) {
   // navdata_baro_available = 0;
  }

  // Detected a temprature switch
  if(lastpressval != 0 && lasttempval != 0 && ABS(lasttempval - navdata.temperature_pressure) > ABS(lastpressval - navdata.temperature_pressure)) {
    //navdata_baro_available = 0;
  }

  lasttempval = navdata.temperature_pressure;
  lastpressval = navdata.pressure;

  /*
   * It turns out that a lot of navdata boards have a problem (probably interrupt related)
   * in which reading I2C data and writing uart output data is interrupted very long (50% of 200Hz).
   * Afterwards, the 200Hz loop tries to catch up lost time but reads the baro too fast swapping the
   * pressure and temperature values by exceeding the minimal conversion time of the bosh baro. The
   * normal Parrot firmware seems to be perfectly capable to fly with this, either with excessive use of
   * the sonar or with software filtering or spike detection. Paparazzi with its tightly coupled baro-altitude
   * had problems. Since this problems looks not uncommon a detector was made. A lot of evidence is grabbed
   * with a logic analyzer on the navboard I2C and serial output. The UART CRC is still perfect, the baro
   * temp-press-temp-press logic is still perfect, so not easy to detect. Temp and pressure are swapped,
   * and since both can have almost the same value, the size of the spike is not predictable. However at
   * every spike of at least 3 broken boards the press and temp are byte-wise exactly the same due to
   * reading them too quickly (trying to catch up for delay that happened earlier due to still non understood
   * reasons. As pressure is more likely to quickly change, a small (yet unlikely) spike on temperature together with
   * press==temp yields very good results as a detector, although theoretically not perfect.

#samp press temp.
50925 39284 34501
50926 39287 34501
50927 39287 34501
50928 39283 34501     // *press good -> baro
50929 39283 34501
50930 39285 34501     // *press good -> baro
50931 39285 34500
50932 34500 34500     // press read too soon from chip (<4.5ms) -> ADC register still previous temp value
50933 34500 36618     // press not updated, still wrong. Temp is weird: looks like the average of both
50934 39284 36618     // new press read, but temp still outdated
50935 39284 34501
50936 39284 34501     // *press good -> baro
50937 39284 34500
50938 39281 34500
50939 39281 34500
50940 39280 34500
50941 39280 34502
50942 39280 34502
50943 39280 34501

   */

  // if press and temp are same and temp has jump: neglect the next frame
  if (navdata.temperature_pressure == navdata.pressure) // && (abs((int32_t)navdata.temperature_pressure - (int32_t)lasttempval) > 40))
  {
    // dont use next 3 packets
    spike_detected = 3;

    spikes++;
   // printf("Spike! # %d\n",spikes);
  }

  if (spike_detected > 0)
  {
    // disable kalman filter use
   // navdata_baro_available = 0;

    // override both to last good
    navdata.pressure = lastpressval_nospike;
    navdata.temperature_pressure = lasttempval_nospike;

    // Countdown
    spike_detected--;
  }
  else // both are good
  {
    lastpressval_nospike = navdata.pressure;
    lasttempval_nospike = navdata.temperature_pressure;
  }

// printf("%d %d %d\r\n", navdata.temperature_pressure, navdata.pressure, spike_detected);
//  printf(",%d,%d",spike_detected,spikes);
}



int IMU_Navdata_init () {
    
    IMU_fd = open ("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NONBLOCK | O_NDELAY ) ;
	printf("Opening serial connection with IMU board \n"); 
    
	if (IMU_fd < 0) {
        printf("Failed to open serial port \n");
        perror("Failed to open serial port");
        return 0 ;
    }

	printf("Setting IMU Serial Port properties \n"); 
    int flags = fcntl(IMU_fd, F_GETFL) ;
        
	fcntl(IMU_fd, F_SETFL, flags | O_NONBLOCK); //read calls are non blocking
        //fcntl(IMU_fd, F_SETFL, flags); //read calls are non blocking
	    //set port options
	struct termios options;
	//Get the current options for the port
	tcgetattr(IMU_fd, &options);
	//Set the baud rates to 460800
	cfsetispeed(&options, 460800);
	cfsetospeed(&options, 460800);

	options.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
	options.c_iflag = 0; //clear input options
	options.c_lflag = 0; //clear local options
	options.c_oflag &= ~OPOST; //clear output options (raw output)
        
     
    //  tcflush(IMU_fd,TCIOFLUSH);

	//Set the new options for the port
	tcsetattr(IMU_fd, TCSANOW, &options);

    // stop acquisition
    uint8_t cmd = 0x02;
    write (IMU_fd, &cmd, 1);
		
    // read some potential dirt (retry a lot of times)
    char tmp[100];
        
	for(int i = 0; i < 12; i++) {
        uint16_t dirt = read (IMU_fd, tmp, sizeof tmp);
        (void) dirt;

        usleep (1000);
    }
		
        
/******************************************************
 *  inline some stuff related to baro calibration
 *
 *******************************************************/
 /*
    printf("/-----------------------------\n"); 
    printf("Barometer calibration... \n"); 
    printf("/-----------------------------\n"); 
*/   
    uint8_t cmd_1=0x17; // send cmd 23
    write(IMU_fd,&cmd_1, 1);
        
	// wait 20ms to retrieve data
    for (int i=0;i<22;i++)
    {
        usleep(1000);
    }

    uint8_t calibBuffer[22];
 
	size_t baro_byte_count = 0;
 
    while(baro_byte_count < 22)
    {
        ssize_t n = read(IMU_fd, calibBuffer + baro_byte_count, 22 - baro_byte_count);
        if (n < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
                continue;
              return n;
        }
        
		baro_byte_count += n;
    }
    
	baro_calibration.ac1 = calibBuffer[0]  << 8 | calibBuffer[1];
	baro_calibration.ac2 = calibBuffer[2]  << 8 | calibBuffer[3];
    baro_calibration.ac3 = calibBuffer[4]  << 8 | calibBuffer[5];
    baro_calibration.ac4 = calibBuffer[6]  << 8 | calibBuffer[7];
    baro_calibration.ac5 = calibBuffer[8]  << 8 | calibBuffer[9];
    baro_calibration.ac6 = calibBuffer[10] << 8 | calibBuffer[11];
    baro_calibration.b1  = calibBuffer[12] << 8 | calibBuffer[13];
    baro_calibration.b2  = calibBuffer[14] << 8 | calibBuffer[15];
	baro_calibration.mb  = calibBuffer[16] << 8 | calibBuffer[17];
	baro_calibration.mc  = calibBuffer[18] << 8 | calibBuffer[19];
	baro_calibration.md  = calibBuffer[20] << 8 | calibBuffer[21];
/*
	printf("Calibration AC1: %d\n", baro_calibration.ac1);
	printf("Calibration AC2: %d\n", baro_calibration.ac2);
	printf("Calibration AC3: %d\n", baro_calibration.ac3);
	printf("Calibration AC4: %d\n", baro_calibration.ac4);
	printf("Calibration AC5: %d\n", baro_calibration.ac5);
	printf("Calibration AC6: %d\n", baro_calibration.ac6);

	printf("Calibration B1: %d\n", baro_calibration.b1);
	printf("Calibration B2: %d\n", baro_calibration.b2);

	printf("Calibration MB: %d\n", baro_calibration.mb);
	printf("Calibration MC: %d\n", baro_calibration.mc);
	printf("Calibration MD: %d\n", baro_calibration.md);

//         imuAvailable = false ; DAREN: remove for now
//         baroAvailable = false ;
//         previousUltrasoundHeight = 0;

    printf("/-----------------------------\n"); 
    printf("Finished Baro Calibration\n"); 
	printf("/-----------------------------\n"); 
	*/
/******************************************************
 * End of in-lining baro calibration
 *
 *******************************************************/
    // start acquisition
    cmd = 0x01;
    write (IMU_fd, &cmd, 1);
        
        
    port.checksum_errors = 0;
    port.bytesRead = 0;
    port.totalBytesRead = 0;
    port.packetsRead = 0;
    port.isInitialized = 1;

      
    isInitialized = 1 ; //DAREN: remove for now

    return 1 ;
 }

int IMU_Navdata_update(unsigned short *y) {
    uint8_t cmd; //used to re-initialize navigation board if needed
    static int last_checksum_wrong = 0 ;
    int checkSumOk = 1 ;
	static int16_t LastMagValue = 0; //to be used to determine if Magnetometer gets stuck
	static int MagFreezeCounter = 0;
	static int OkToKill = 0;
	int SysRet;
    
    Acquire_Navdata_Bytes(); 
    
    // while there is something interesting to do...
        while (port.bytesRead >= NAVDATA_PACKET_SIZE) {
         
            if (port.buffer[0] == NAVDATA_START_BYTE) {
                tcflush(IMU_fd,TCIOFLUSH); 
                memcpy (&navdata, port.buffer, NAVDATA_PACKET_SIZE);

                // Calculating the checksum
                uint16_t checksum = 0;
                for (int i = 2; i < NAVDATA_PACKET_SIZE - 2; i += 2) {
                    checksum += port.buffer[i] + (port.buffer[i + 1] << 8);
                }

                // When checksum is incorrect
                if (navdata.chksum != checksum) {
                    printf ("Checksum error [calculated: %d] [packet: %d] [diff: %d]\n", checksum, navdata.chksum, checksum - navdata.chksum);
                    port.checksum_errors++;
					checkSumOk = 0 ;
                }

                // When we already dropped a packet or checksum is correct
                if (last_checksum_wrong || navdata.chksum == checksum) {
                    // Invert byte order so that TELEMETRY works better
                    uint8_t tmp;
                    uint8_t* p = (uint8_t*) &(navdata.pressure);
                    tmp = p[0];
                    p[0] = p[1];
                    p[1] = tmp;
                    p = (uint8_t*) &(navdata.temperature_pressure);
                    tmp = p[0];
                    p[0] = p[1];
                    p[1] = tmp;

                    //baroUpdateLogic (); DAREN: removed this for now
					baro_update_logic();	
                    //imuAvailable = 1 ; DAREN: removed this for now
                    last_checksum_wrong = 0 ;
                    port.packetsRead++;
                }
				
				
				
				if (LastMagValue == navdata.mx)
				{
					
					MagFreezeCounter++;
					//printf("MagFreezeCounter count: %d \n", MagFreezeCounter);
					//if (MagFreezeCounter > 800) //re-initialize the serial port here
					//if (MagFreezeCounter > 400) //re-initialize the serial port here  | DAREN: Had to comment this out for now!
					if (0==1) //re-initialize the serial port here  | DAREN: Had to comment this out for now!
					//if (MagFreezeCounter > 400) //re-initialize the serial port here
					{
						 printf("Mag needs resetting, Values are frozen!!! %d , %d \n",LastMagValue,navdata.mx);
						 printf("Setting GPIO 177 to reset PIC Navigation Board \n");
						  
						  SysRet = system("gpio 177 -d lo 0 &"); //GPIO used to reset PIC, turned this back on
				          SysRet = system("gpio 177 -d lo 1 &"); //pretend we turned this back on
													
							// wait 20ms to retrieve data
							for (int i=0;i<22;i++)
							{
								usleep(1000);
							}
													    printf("turning pic back on...\n");

						  /*
						  printf("Resuming data acquisition from PIC Navigation Board \n");
						  cmd = 0x02;
						  write (IMU_fd, &cmd, 1);
						  cmd = 0x01; //restart acquisition
						  write (IMU_fd, &cmd, 1);  //command line way: SysRet = system("echo –e –n “\1” > /dev/ttyO1 &");  
							*/	
						  //printf("Closing serial connection \n"); 		
						  IMU_Navdata_stop();
						 // printf("Attempting to re-init serial connection \n");
						  IMU_Navdata_init();
						 
						  OkToKill = 1;
						  
						  //
					MagFreezeCounter = 0; //reset counter back to zero
					}
				}	
				else //if values are different
				{
					//printf("resetting to zero \n");
					MagFreezeCounter = 0;
					if (OkToKill==1)
					{
					//	SysRet = system("killall -9 program.elf");
					}
				}
				
                // Crop the buffer
                cropbuffer (NAVDATA_PACKET_SIZE);
                tcflush(IMU_fd,TCIOFLUSH); //Daren: Flush buffer to get the most up to date values at the next run
				LastMagValue = navdata.mx;
            }
			
            else {
                // find start byte, copy all data from startbyte to buffer origin, update bytesread
                uint8_t * pint;
                pint = (uint8_t*) memchr (port.buffer, NAVDATA_START_BYTE, port.bytesRead);

                if (pint != NULL) {
                    cropbuffer (pint - port.buffer);
                }
                else {
                    // if the start byte was not found, it means there is junk in the buffer
                    port.bytesRead = 0;
                }
            }
        }
    
   
    
   
*y = navdata.ultrasound;

return checkSumOk ;
}
	

void IMU_Navdata_stop() {
   
        isInitialized = 0 ; //DAREN: removed this
        close (IMU_fd) ;
        
        
	
}



/*----------------------------------------------------------------------------- 
*        Other functions not accessed by generated code directly listed below
*-----------------------------------------------------------------------------*/

void Acquire_Navdata_Bytes () { //original function
        int newbytes = read (IMU_fd, port.buffer + port.bytesRead, NAVDATA_BUFFER_SIZE - port.bytesRead);

        // because non-blocking read returns -1 when no bytes available
        if (newbytes > 0) {
            port.bytesRead += newbytes;
            port.totalBytesRead += newbytes;
        }
          
}


static void cropbuffer (int cropsize) {

        if (port.bytesRead - cropsize < 0) {
            // TODO think about why the amount of bytes read minus the cropsize gets below zero
            printf ("BytesRead(=%d) - Cropsize(=%d) may not be below zero. port->buffer=%p\n", port.bytesRead, cropsize, port.buffer);
            return;
        }

        memmove (port.buffer, port.buffer + cropsize, NAVDATA_BUFFER_SIZE - cropsize);
        port.bytesRead -= cropsize;
      //  tcflush(IMU_fd,TCIOFLUSH);
}



