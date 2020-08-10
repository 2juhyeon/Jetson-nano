#include "timer.h"
#include<iostream>


//keyboard interrupt code
int end_this_program;
void signalHandler(int s) {
    //signal comare
    if(s == SIGINT) end_this_program = true;
}

//make timer id
timer_t firstTimerID;

static void timer_handler(int sig, siginfo_t* si, void* uc)
{
    timer_t* tidp;
    tidp = (void**)(si->si_value).sival_ptr;

    //compare timerId
    if (*tidp == firstTimerID) {
        /* write your code!*/

        std::cout << "1s" << std::endl;

    }

}

int main() {
    //make keyboard interrupt signal in linux -> crtl + c
    //ctrl + z is stop the program!
    signal(SIGINT, signalHandler);


    // timer_handler is just one!
    TIMER::create_timer("First Timer", &firstTimerID, timer_handler);

    //set_timer consist of timerid, sec, us but Do not set less of 200us
    TIMER::set_timer(&firstTimerID, 1, 0);

    while (!end_this_program) {
        // write your code!!        
    }

    std::cout << "program end!" << std::endl;
    return 0;
}