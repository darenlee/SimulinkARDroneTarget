#ifndef _GPIO_H
#define _GPIO_H

#include <stdint.h>


  /*  enum Motor {

                    Motor1 = 171,
                    Motor2 = 172,
                    Motor3 = 173,
                    Motor4 = 174,
                    FlipFlop = 175, 
			        Input  = 176 
                }; */
struct Motor {

                     uint16_t Motor1;
                     uint16_t Motor2;
                     uint16_t Motor3;
                     uint16_t Motor4;
			         uint16_t Input;
                     uint16_t FlipFlop;
};       
	int init_GPIO () ;

    void stop_GPIO () ;

    void setupInput (uint16_t pin) ;
	void setupOutput (uint16_t pin) ;

    void set_GPIO (uint16_t pin) ;

    uint16_t get_GPIO (uint16_t pin) ;

    void clear_GPIO (uint16_t pin) ;



#endif