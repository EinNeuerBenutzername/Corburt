#ifndef Corburt_System_h_Include_Guard
#define Corburt_System_h_Include_Guard
//#include "cbbase.h"
#ifdef CB_REALTIME
#include <time.h>
#if defined(_WIN32)
    #include <Windows.h>
#elif defined(__APPLE__)
    #include <unistd.h>
#else
    #include <unistd.h>
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
#ifdef WIN32
    SYSTEMTIME systime;
    GetSystemTime(&systime);
    double tmdouble=systime.wMilliseconds/1000.0f+systime.wSecond*1.0f;
    return tmdouble;
#else
    struct timespec tmspec;
    clock_gettime(CLOCK_MONOTONIC,&tmspec);
    double tmdouble=tmsp    ec.tv_nsec/1000000000.0f+tmspec.tv_sec*1.0f;
    return tmdouble;
#endif
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

int checkendianess();

int checkendianess(){
//    const int i=1;
//    char c=*(char*)&i;
//    if(c==1){
//        return 1; // is le
//    }else{
//        return 0;
//    }
    uint8_t buffer[4];
    buffer[0]=0x00;
    buffer[0]=0x01;
    buffer[0]=0x02;
    buffer[0]=0x03;
    switch((*(uint32_t*)buffer)){
    case 0x00010203: return 0;
    case 0x03020100: return 1;
    case 0x02030001: break; // BIG WORD
    case 0x01000302: break; // LITTLE WORD
    default: break; // UNKNOWN
    }
    return 2; // shit.
}

#endif
