namespace TIMER;
Link with -lrt

change your make file!
1. make timer_handler
   ex) void timer_handler(ing sig, siginfo_t* si, void* uc)

2. write distinguish code
   ex) timer_t* tidp;
    tidp = (void**)(si->si_value).sival_ptr;
    //compare your timer id
    if (*tidp == <your timerId>) {
       /* do */
    }
    
    
        
wating update!
