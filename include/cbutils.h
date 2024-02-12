#ifndef __CBUTILS
#define __CBUTILS

// top layer utils

#include <stdio.h>
#include <time.h>
#include "cbsys.h"

void __CBUTILS_ShowFPS(void);
void __CBUTILS_SetupRand(void);
u64 __CBUTILS_Rand(void);

struct {
    Rand64 rand;
} __CBUTILS_data = {0};

const struct {
    void (*showFPS)(void);
    void (*setupRand)(void);
    u64 (*rand)(void);
} Utils = {
    .showFPS=__CBUTILS_ShowFPS,
    .setupRand=__CBUTILS_SetupRand,
    .rand=__CBUTILS_Rand
};

void __CBUTILS_ShowFPS(void){
    char title_str[100]={0};
    sprintf(title_str, "Corburt - FPS: %.1f", Time.getFPS());
    Curses.setTitle(title_str);
}
void __CBUTILS_SetupRand(void){
    u64 timeget=10000.0f*Time.get();
    u64 seed=time(NULL);
    seed=(seed<<12)+timeget;
    Log.debug("Setup random seed: %" SPECu64, seed);
    RNG.srand64(&__CBUTILS_data.rand, seed);
}
u64 __CBUTILS_Rand(void){
    return RNG.get64(&__CBUTILS_data.rand);
}

#endif
