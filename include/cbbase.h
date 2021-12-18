#ifndef Corburt_Base_h_Include_Guard
#define Corburt_Base_h_Include_Guard
#include "cr.h"
#include "msg.h"
#include "mtwister.h"
#include <time.h>
#include <wchar.h>
#include <stdarg.h>
#include <stdlib.h> //malloc() realloc() free() exit()
#include <limits.h>

typedef enum foo{false,true} foo;//enum bool
typedef unsigned int nat;//natural number, 32-bit
typedef unsigned long long bat;//64-bit integer
//typedef unsigned __int64 bat;
typedef float real;
MTRand mtrand;
foo isle=true; //platform endianess. this is not a flag.
wchar_t *buffer;
struct player{
    wchar_t name[32];
    nat rnk;
    nat lvl;
    bat exp;
    nat maxhp;
    nat hp;
    struct stats{
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat stl;
        nat act;
        nat con;
        nat pts;
    } stats;
} player={L"",1,1,0,10,10,{0,0,0,0,0,0,0,21}};
struct inventory{
    nat unlocked;
    nat items[64];
    nat weapon;
    nat armor;
    bat money;
};
struct save{
    struct player plr;
};
struct save saves[10];
#ifdef Corburt_Explicit_Pointer_Trace
    nat pointerinuse=0;
#endif

//basic
void printc(int color,const wchar_t *format,...){
    crossline_color_set(color);
    fflush(stdout);
    va_list args;
    va_start(args,format);
    vwprintf(format,args);
    va_end(args);
    crossline_color_set(Default);
    fflush(stdout);
}
const wchar_t *wsprintfc(const wchar_t *text,...){ //obsolete function
    wmemset(buffer,0,1024);
    va_list args;
    va_start(args,text);
    vswprintf_s(buffer,1024,text,args);
    va_end(args);
    return buffer;
}
void tracelog(int color,const wchar_t *format,...){
#ifdef Corburt_Debug
    crossline_color_set(color);
    va_list args;
    va_start(args,format);
    vwprintf(format,args);
    va_end(args);
    crossline_color_set(Default);
#else
    return;
#endif
}
enum errorenum{
    error_cannotmalloc,
    error_cannotrealloc
};
void fatalerror(enum errorenum error_id){
    switch(error_id){
    case error_cannotmalloc:
        printc(Red,msg_error_cannotmalloc);
        exit(-1);
    case error_cannotrealloc:
        printc(Red,msg_error_cannotrealloc);
        exit(-1);
    }
}
void *mallocpointer(size_t bytes){
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
#ifdef Corburt_Explicit_Pointer_Trace
    pointerinuse++;
    tracelog(Green,msg_trace_malloced,bytes);
    tracelog(Green,msg_trace_pointerinuse,pointerinuse);
#endif
    return pointer;
}
void *reallocpointer(void *pointer,size_t bytes){
    return realloc(pointer,bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
#ifdef Corburt_Explicit_Pointer_Trace
    tracelog(Green,msg_trace_realloced,bytes);
#endif
    return pointer;
}
void freepointer(void *pointer){
    if(pointer==NULL)return;
    free(pointer);
#ifdef Corburt_Explicit_Pointer_Trace
    pointerinuse--;
    tracelog(Green,msg_trace_freed);
    tracelog(Green,msg_trace_pointerinuse,pointerinuse);
#endif
    pointer=NULL;
}
void scanline(wchar_t *scan_str,int scans){
    crossline_color_set(Yellow);
    fflush(stdout);
    fgetws(scan_str,scans,stdin);
    if(scan_str[wcslen(scan_str)-1]==L'\n'){
        scan_str[wcslen(scan_str)-1]=0;
    }
    fflush(stdin);
    crossline_color_set(Default);
    fflush(stdout);
}
void wcslower(wchar_t **target_str_pos){
    wchar_t *target_str=*target_str_pos;
    for(unsigned int i=0;i<wcslen(target_str);i++){
        if(target_str[i]<=L'Z'&&target_str[i]>=L'A'){
            target_str[i]+=(L'a'-L'A');
        }
    }
    target_str_pos=&target_str;
}
//misc
real match(wchar_t *str1,wchar_t *str2);
void checkendianess();
void initrng();
real match(wchar_t *str1,wchar_t *str2){
    if(wcslen(str1)==0)return 0.0f;
    wchar_t *str1l=mallocpointer(sizeof(wchar_t)*(wcslen(str1)+1));
    wchar_t *str2l=mallocpointer(sizeof(wchar_t)*(wcslen(str2)+1));
    wcscpy(str1l,str1);
    wcscpy(str2l,str2);
    wcslower(&str1l);
    wcslower(&str2l);
    str1l[wcslen(str1l)-1]=0;
    str2l[wcslen(str2l)-1]=0;
    wchar_t *pos=wcsstr(str2l,str1l);
    if(pos==NULL){
        freepointer(str1l);
        freepointer(str2l);
        return -1.0f;
    }else{
        if(pos==str2l||str2l[(pos-str2l)-1]==L' '){
            freepointer(str1l);
            freepointer(str2l);
            return (1.0f*wcslen(str1))/(1.0f*wcslen(str2));
        }else{
            freepointer(str1l);
            freepointer(str2l);
            return -1.0f;
        }
    }
}
void checkendianess(){
    const int i=1;
    char c=*(char*)&i;
    if(c==1){
        tracelog(Green,msg_trace_endianess_le);
        isle=true;
    }else{
        tracelog(Green,msg_trace_endianess_be);
        isle=false;
    }
}
void initrng(){
    time_t seed;
    tracelog(Green,msg_trace_rnginit);
    tracelog(Green,msg_trace_rngseed,seed=time(NULL));
    mtrand=seedRand(seed);
    tracelog(Green,msg_trace_rngtest,genRandLong(&mtrand));
}

#endif
