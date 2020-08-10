#include "timer.h"


namespace TIMER {
    int create_timer(timer_t* timerID, MY_HANDLER_(VAR))
    {
        struct sigevent         te;
        struct sigaction        sa;
        int                     sigNo = SIGRTMIN;

        /* Set up signal handler. */
        sa.sa_flags = SA_SIGINFO;


        sa.sa_sigaction = VAR;
        sigemptyset(&sa.sa_mask);

        if (sigaction(sigNo, &sa, NULL) == -1)
        {
            std::cout << "sigaction error\n";
            return -1;
        }

        /* Set and enable alarm */
        te.sigev_notify = SIGEV_SIGNAL;

        te.sigev_signo = sigNo;
        te.sigev_value.sival_ptr = timerID;
        timer_create(CLOCK_REALTIME, &te, timerID);
        return 0;
    }


    int set_timer(timer_t* timerID, int Sec_Value, int _100ns) {
        struct itimerspec       its;

        its.it_interval.tv_sec = Sec_Value;
        its.it_interval.tv_nsec = _100ns * US2100NS;

        its.it_value.tv_sec = Sec_Value;
        its.it_value.tv_nsec = _100ns * US2100NS;

        timer_settime(*timerID, 0, &its, NULL);
    }

    int delete_timer(timer_t timerid) {
        timer_delete(timerid);
        return 0;
    }
}