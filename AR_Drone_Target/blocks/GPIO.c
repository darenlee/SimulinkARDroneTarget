#include "GPIO.h"

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define GPIO_MAGIC 'p'
#define GPIO_DIRECTION _IOW(GPIO_MAGIC, 0, struct Direction)
#define GPIO_READ _IOWR(GPIO_MAGIC, 1, struct Data)
#define GPIO_WRITE _IOW(GPIO_MAGIC, 2, struct Data)

enum Mode {
			GPIO_INPUT = 0,             //!< Pin configured for input
			GPIO_OUTPUT_LOW,            //!< Pin configured for output with low level
			GPIO_OUTPUT_HIGH,           //!< Pin configured for output with high level
  		  };

struct Data {
			int pin ;
  			int value ;
	    	}data;

struct Direction {
			int pin ;
			int mode ;
       		}direction;

	

 const uint32_t GPIO_PORT = 0x32524 ;

 //   struct Data data ;
 //   struct Direction direction ;

    int fd = -1 ;

    int init_GPIO () {
        if (fd != -1) {
            return 1 ;
        }
        return (fd = open ("/dev/gpio", O_RDWR)) != -1 ;
    }

    void stop_GPIO () {
        close (fd) ;
        fd = -1 ;
    }

    void setup (uint16_t pin, uint8_t mode) {
        direction.pin = pin ;
        direction.mode = mode ;
        ioctl (fd, GPIO_DIRECTION, &direction) ;
    }

	void setupInput (uint16_t pin) {
		direction.pin = pin ;
		direction.mode = GPIO_INPUT ;
		ioctl (fd, GPIO_DIRECTION, &direction) ;
	}

	void setupOutput (uint16_t pin) {
		/*
		direction.pin = pin ;
		direction.mode = GPIO_OUTPUT_LOW ;
		ioctl (fd, GPIO_DIRECTION, &direction) ;
		*/
	}

    void set_GPIO (uint16_t pin) {
        data.pin = pin ;
        data.value = 1 ;
        ioctl (fd, GPIO_WRITE, &data) ;
    }

    uint16_t get_GPIO (uint16_t pin) {
        data.pin = pin ;
        ioctl (fd, GPIO_READ, &data) ;
        return data.value ;
    }

    void clear_GPIO (uint16_t pin) {
        data.pin = pin ;
        data.value = 0 ;
        ioctl (fd, GPIO_WRITE, &data) ;
    }

