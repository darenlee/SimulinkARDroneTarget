#include "Actuators.h"

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <stdint.h>
#include <signal.h>
#include "GPIO.h"

int fd_act;
int isInitialized = 0;


int init () {
        
	    enum LEDs led1,led2,led3,led4;
        
        led1 = GREEN;
        led2 = GREEN;
        led3 = GREEN;
        led4 = GREEN;
	    uint8_t led[4] = {led1,led2,led3,led4};
       /* uint16_t motor1 = Motor1;
        uint16_t motor2 = Motor2;
        uint16_t motor3 = Motor3;
        uint16_t motor4 = Motor4;
        uint16_t flipflop = FlipFlop;
        uint16_t input = Input;*/
       struct Motor motor; 
        motor.Motor1=171;
        motor.Motor2=172;
        motor.Motor3=173;
        motor.Motor4=174;
        motor.FlipFlop=175;
        motor.Input=176;
        
        if (isInitialized) {
			return 1 ;
		}

        if (!init_GPIO ()) {
			return 0 ;
		}

        fd_act = open ("/dev/ttyO0", O_RDWR | O_NOCTTY | O_NDELAY) ;

        if (fd_act < 0) {
            return 0 ;
        }

        int flags = fcntl(fd_act, F_GETFL, 0) ;
	    fcntl(fd_act, F_SETFL, flags | O_NONBLOCK); //read calls are non blocking

        //set port options
        struct termios options;
        //Get the current options for the port
        tcgetattr (fd_act, &options);
        //Set the baud rates to 115200
        cfsetispeed (&options, B115200);
        cfsetospeed (&options, B115200);

        options.c_cflag |= (CLOCAL | CREAD); //Enable the receiver and set local mode
        options.c_iflag = 0; //clear input options
        options.c_lflag = 0; //clear local options
        options.c_oflag &= ~OPOST; //clear output options (raw output)

        //Set the new options for the port
        tcsetattr (fd_act, TCSANOW, &options);

        setupInput (motor.Input) ;

		setupOutput (motor.FlipFlop) ;
		clear_GPIO (motor.FlipFlop) ;
		usleep (1000) ;
		set_GPIO (motor.FlipFlop) ;
		
        setupOutput (motor.Motor1);
        setupOutput (motor.Motor2);
        setupOutput (motor.Motor3);
        setupOutput (motor.Motor4);
        set_GPIO (motor.Motor1) ;
        set_GPIO (motor.Motor2) ;
        set_GPIO (motor.Motor3) ;
        set_GPIO (motor.Motor4) ;

        //configure motors
        uint8_t reply[256];
        int m;
        for (m = 0; m < 4; m++) {
            clear_GPIO (motor.Motor1 + m);
            sendCmd (0xe0, reply, 2);
            if (reply[0] != 0xe0 || reply[1] != 0x00) {
                printf ("motor%d cmd=0x%02x reply=0x%02x\n", m + 1, (int) reply[0], (int) reply[1]);
            }
            usleep(1000);
            sendCmd (m + 1, reply, 1);
            set_GPIO (motor.Motor1 + m);
        }

        //all select lines active
        clear_GPIO (motor.Motor1) ;
        clear_GPIO (motor.Motor2) ;
        clear_GPIO (motor.Motor3) ;
        clear_GPIO (motor.Motor4) ;

        //start multicast
		
        sendCmd (0xa0, reply, 1);
        sendCmd (0xa0, reply, 1);
        sendCmd (0xa0, reply, 1);
        sendCmd (0xa0, reply, 1);
        sendCmd (0xa0, reply, 1); 

        //reset IRQ flipflop - on error 176 reads 1, this code resets 176 to 0
         clear_GPIO (motor.FlipFlop) ;
        set_GPIO (motor.FlipFlop);

		set(led) ;
        signal(SIGINT,terminate_interrupt); //Interrupts for Ctrl+C.

		isInitialized = 1 ;
        return 1 ;
        
        
    }

void stop () {
        uint8_t led_close[4] = {1,1,1,1};
        set(led_close);    
 		isInitialized = 0 ;
        close (fd_act) ;
        
    }
void terminate_interrupt(int sig) // Terminates the program if the user presses Ctrl+C
{
    stop();
    printf("%d\n",sig);
    exit(sig);
}    


int sendCmd (uint8_t cmd, uint8_t *reply, int replyLen) {
        write (fd_act, &cmd, 1) ;
        return read (fd_act, reply, replyLen) ;
    }
void set (uint8_t led[]) {
            uint8_t cmd[2];
            
            

            led[0] &= 0x03;
            led[1] &= 0x03;
            led[2] &= 0x03;
            led[3] &= 0x03;

            cmd[0] = 0x60 | ((led[0] & 1) << 4) | ((led[1] & 1) << 3) | ((led[2] & 1) << 2) | ((led[3] & 1) << 1);
            cmd[1] = ((led[0] & 2) << 3) | ((led[1] & 2) << 2) | ((led[2] & 2) << 1) | ((led[3] & 2) << 0);

            write(fd_act, cmd, 2);
        }
 
 uint16_t setPWM (uint8_t cmd[]) 
 {
        
         uint16_t data,R;
         
         write (fd_act, cmd, 5);
         
        // R=get_GPIO (175);
         data=get_GPIO (176);
     
         return data;
}      


       
    

