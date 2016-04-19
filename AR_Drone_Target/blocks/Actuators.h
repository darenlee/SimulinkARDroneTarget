#ifndef _ACTUATORS_H
#define _ACTUATORS_H

#include <stdint.h>

    int init () ;
    
    uint16_t setPWM (uint8_t cmd[]) ;
    
    void set (uint8_t led[]) ;
	int sendCmd (uint8_t cmd, uint8_t *reply, int replyLen);
	
    void stop ();
    void terminate_interrupt(int sig);
    enum LEDs{
		        OFF,
                RED,
				GREEN,
				ORANGE
             };

#endif