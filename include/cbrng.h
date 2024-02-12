#ifndef __CBRNG
#define __CBRNG

// BOTTOM LAYER - RNG

// Remove this #include to make CBRNG standalone
#include "cbsys.h"

#ifndef __CBSYS // For standalone use
#include <inttypes.h>
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
#endif

// BOTTOM LAYER

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    i32 index;
    u32 state[624];
} Rand32;

typedef struct {
    i64 index;
    u64 state[312];
} Rand64;

void __CBRNG_SRand32(Rand32 *rng, u32 seed);
void __CBRNG_Gen32(Rand32 *rng);
u32 __CBRNG_Get32(Rand32 *rng);

void __CBRNG_SRand64(Rand64 *rng, u64 seed);
void __CBRNG_Gen64(Rand64 *rng);
u64 __CBRNG_Get64(Rand64 *rng);

const struct {
    void (*srand32)(Rand32 *rand, u32 seed);
    u32 (*get32)(Rand32 *rand);
    void (*srand64)(Rand64 *rand, u64 seed);
    u64 (*get64)(Rand64 *rand);
} RNG = {
    .srand32=__CBRNG_SRand32,
    .get32=__CBRNG_Get32,
    .srand64=__CBRNG_SRand64,
    .get64=__CBRNG_Get64
};

void __CBRNG_SRand32(Rand32 *rand, u32 seed){
    rand->index=0;
    rand->state[0]=seed&0xffffffff;
    for(i32 i=1; i<624; i++){
        u32 t=1812433253*(rand->state[i-1]^(rand->state[i-1]>>30))+i;
        rand->state[i]=t&0xffffffff;
    }
}
void __CBRNG_Gen32(Rand32 *rand){
    for(i32 i=0; i<624; i++){
        // 2^31=0x80000000
        u32 y=(rand->state[i]&0x80000000)+((rand->state[(i+1)%624])&0x7fffffff);
        rand->state[i]=(rand->state[(i+397)%624])^(y>>1);
        if(y&1)rand->state[i]^=0x9908b0df;
    }
}
u32 __CBRNG_Get32(Rand32 *rand){
    if(rand->index==0)__CBRNG_Gen32(rand);
    u32 y=rand->state[rand->index];
    y^=(y>>11);
    y^=((y<<7)&0x9d2c5680);
    y^=((y<<15)&0xefc60000);
    y^=(y>>18);
    rand->index=(rand->index+1)%624;
    return y;
}

void __CBRNG_SRand64(Rand64 *rand, u64 seed){
    rand->index=0;
    rand->state[0]=seed;
    for(i32 i=1; i<312; i++){
        u64 t=6364136223846793005ULL*(rand->state[i-1]^(rand->state[i-1]>>30))+i;
        rand->state[i]=t&0x5555555555555555ULL;
    }
}
void __CBRNG_Gen64(Rand64 *rand){
    for(i32 i=0; i<312; i++){
        u64 y=(rand->state[i]&0x80000000ULL)+((rand->state[(i+1)%312])&0x7fffffffULL);
        rand->state[i]=(rand->state[(i+156)%312])^(y>>1);
        if(y&1)rand->state[i]^=0xb5026f5aa96619e9ULL;
    }
}
u64 __CBRNG_Get64(Rand64 *rand){
    if(rand->index==0)__CBRNG_Gen64(rand);
    u64 y=rand->state[rand->index];
    y^=(y>>29);
    y^=((y<<17)&0x71d67fffeda60000ULL);
    y^=((y<<37)&0xfff7eee000000000ULL);
    y^=(y>>43);
    rand->index=(rand->index+1)%312;
    return y;
}

#ifdef __cplusplus
}
#endif

#endif
