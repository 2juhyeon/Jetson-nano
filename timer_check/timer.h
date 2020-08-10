#ifndef __LJH_TIMER__
#define __LJH_TIMER__

#include <time.h>
#include <signal.h>
#include <iostream>

#define TIMER_HANDLER(VAR) void(*(VAR))(int sig, siginfo_t* si, void* uc)
#define US2MS 1000000 //10^6

namespace TIMER {
	int create_timer(char* name, timer_t* timerID, TIMER_HANDLER(timer_handler));
	int set_timer(timer_t* timerID, int sec, int _100ns);
	int delete_timer(timer_t timerid);
}

#endif // !__LJH_TIMER__


