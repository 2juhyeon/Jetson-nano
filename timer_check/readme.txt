namespace TIMER;
Link with -lrt
touch your make file!

1. make timer_handler
   ex) MY_HANDLER_(VAR)
       TIMER::create_timer(&firstTimerID, VAR);

2. write distinguish code
   ex) timer_t* tidp;
    tidp = Get_Timer_ID;
    //compare your timer id
    if (*tidp == <your timerId>) {
       /* do */
    }
