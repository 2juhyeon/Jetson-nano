namespace TIMER;
Link with -lrt

change your make file!
1. make timer_handler
   ex) void timer_handler(ing sig, siginfo_t* si, void* uc)

2. write distinguish code
   ex) timer_t* tidp;
    tidp = Get_Timer_ID;
    //compare your timer id
    if (*tidp == <your timerId>) {
       /* do */
    }