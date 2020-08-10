#ifndef __LJH_TIMER__
#define __LJH_TIMER__

#include <time.h>
#include <signal.h>
#include <iostream>

#define MY_HANDLER_(VAR) void((VAR))(int sig, siginfo_t* sig_info, void* uc)
#define Get_Timer_ID ((void**)(sig_info->si_value).sival_ptr)
#define US2100NS 100000 //10^5
 
namespace TIMER {
	int create_timer(timer_t* timerID, MY_HANDLER_(VAR));
	int set_timer(timer_t* timerID, int sec, int _100ns);
	int delete_timer(timer_t timerid);
}

#endif // !__LJH_TIMER__


