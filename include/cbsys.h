#ifndef Corburt_System_h_Include_Guard
#define Corburt_System_h_Include_Guard
#include "cbbase.h"
#include <time.h>
#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__linux__) || defined(__FreeBSD__)
    #include <sys/time.h>
#elif defined(__APPLE__)
    #include <unistd.h>
#else
    #include <sys/time.h>
#endif
double cbtime_inittime=0;
double cbtime_previoustime=0;

void cbtime_init();
double cbtime_get();
void cbtime_sleep(float ms);
void cbtime_wait(float targetFPS);
void cbtime_end();

void cbtime_init(){
    cbtime_inittime=cbtime_get();
    cbtime_previoustime=cbtime_get();
}
double cbtime_get(){
    return (double)clock()/CLOCKS_PER_SEC-cbtime_inittime;
}
void cbtime_sleep(float ms){
    if(ms<=0)return;
    #if defined(_WIN32)
        Sleep((unsigned int)ms);
    #elif defined(__linux__) || defined(__FreeBSD__) || defined(__EMSCRIPTEN__)
        struct timespec req = { 0 };
        time_t sec = (int)(ms/1000.0f);
        ms -= (sec*1000);
        req.tv_sec = sec;
        req.tv_nsec = ms*1000000L;
        // NOTE: Use nanosleep() on Unix platforms... usleep() it's deprecated.
        while (nanosleep(&req, &req) == -1) continue;
    #elif defined(__APPLE__)
        usleep(ms*1000.0f);
    #else
        struct timespec req = { 0 };
        time_t sec = (int)(ms/1000.0f);
        ms -= (sec*1000);
        req.tv_sec = sec;
        req.tv_nsec = ms*1000000L;
        // NOTE: Use nanosleep() on Unix platforms... usleep() it's deprecated.
        while (nanosleep(&req, &req) == -1) continue;
    #endif
}
void cbtime_wait(float targetFPS){
    if(targetFPS<=0)return;
    if(targetFPS>32767)return;
    static double extratime=0;
    double targetwaittime=1.0f/targetFPS;
    double waittime=targetwaittime-cbtime_get()+cbtime_previoustime;
    if(extratime<0-targetwaittime*5.0f&&extratime<-0.1f)extratime=0;
    if(extratime>targetwaittime*5.0f&&extratime>0.1f)extratime=0;
    double wait=(waittime+extratime)*1000.0f;
    cbtime_sleep(wait);
    double currenttime=cbtime_get();
    extratime=cbtime_previoustime+targetwaittime+extratime-currenttime;
}
void cbtime_end(){
    cbtime_previoustime=cbtime_get();
}

#endif
