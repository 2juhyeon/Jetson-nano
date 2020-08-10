#include "timer.h"
#include<iostream>



//keyboard interrupt code
int end_this_program;
void signalHandler(int sig) {
    //signal comare
    if(sig == SIGINT) end_this_program = true;
}



//make timer id
timer_t firstTimerID;


//if you change name of handler in that case change the name of create_timer's parameter;;
MY_HANDLER_(timer_handler)
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
    TIMER::create_timer(&firstTimerID, timer_handler);

    //set_timer consist of timerid, sec, us but Do not set less of 200us
    TIMER::set_timer(&firstTimerID, 1, 0);

    while (!end_this_program) {
        // write your code!!        




    }

    std::cout << "program end!" << std::endl;
    return 0;
}

