/* Copyrights 2013, MathWorks Inc */
#include <unistd.h>
#include <rtwtypes.h>
#include <time.h>
extern uint32_T profileReadTimer(void);

#if (!defined(_POSIX_TIMERS) || (_POSIX_TIMERS == 0))
#error "POSIX timers used for execution profiling are not supported on your system."
#endif

uint32_T profileReadTimer(void)
{
    struct timespec tp;
    uint32_T ret;
    int status;
    
    status = clock_gettime(CLOCK_REALTIME, &tp);
    if (status == 0) {
        ret = (uint32_T) (tp.tv_sec * 1000000000 + tp.tv_nsec);  /* Return time in nanoseconds */
    }
    else {
        ret = 0;
    }
   
    return(ret);
}

/* EOF */
