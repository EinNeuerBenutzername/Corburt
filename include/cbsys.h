#ifndef __CBSYS
#define __CBSYS

// BOTTOM LAYER
// ALL code outside of this header file and cbcurses.h should be fully portable.

#include <limits.h>

#if CHAR_BIT!=8
    #error Compile Error: Macro CHAR_BIT is not 8.
#endif

#include <stdbool.h>

#include <inttypes.h>
// Hope it supports fixed-size integers...
typedef int32_t i32;
typedef uint32_t u32;
typedef int64_t i64;
typedef uint64_t u64;
typedef double real;

#define SPECi32 PRId32
#define SPECu32 PRIu32
#define SPECi64 PRId64
#define SPECu64 PRIu64

// Corburt would not read or write any float point numbers in
// disk I/O, for consistency. Still, endianness is something
// we need to take into considerations.

// System-level defines and APIs

//===========================================
//  Global Platform Detection
//===========================================

#if !defined(__CB_WINDOWS) && !defined(__CB_POSIX)
    #if defined(_WIN32)
        #define __CB_WINDOWS
    #elif defined(__POSIX__) || defined(__APPLE__) || defined(__linux__)  ||  defined(__FreeBSD__)  ||  defined(__EMSCRIPTEN__)
        #define __CB_POSIX
        #if (_BSD_SOURCE || (_XOPEN_SOURCE >= 500 || _XOPEN_SOURCE && _XOPEN_SOURCE_EXTENDED) && !(_POSIX_C_SOURCE >= 200809L || _XOPEN_SOURCE >= 700))
            #define __CB_POSIX_USE_USLEEP
        #endif
    #else
        #error Compile Error: Unsupported platform.
    #endif
#endif

//===========================================
//  Logging Module
//===========================================

void __CBLOG_Debug(const char *format, ...);
void __CBLOG_Error(const char *format, ...);
void __CBLOG_Fatal(const char *format, ...);

const struct {
    void (*debug)(const char *format, ...);
    void (*error)(const char *format, ...);
    void (*fatal)(const char *format, ...);
} Log={
    .debug=__CBLOG_Debug,
    .error=__CBLOG_Error,
    .fatal=__CBLOG_Fatal
};

#include "cbcurses.h"
#include <stdarg.h>
#include <stdlib.h>

void __CBLOG_Debug(const char *format, ...){
#ifdef __CB_DEBUG
    int color=Curses.getColor();
    Curses.setColor(Cyan);
    printf("[DEBUG] ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
    fflush(stdout);
    Curses.setColor(color);
#else
    (void)format;
#endif
}
void __CBLOG_Error(const char *format, ...){
    int color=Curses.getColor();
    Curses.setColor(Red|Bright);
    printf("[ERROR] ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
    fflush(stdout);
    Curses.setColor(color);
}
void __CBLOG_Fatal(const char *format, ...){
    int color=Curses.getColor();
    Curses.setColor(Red);
    printf("[FATAL] ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
    fflush(stdout);
    Curses.setColor(color);
    exit(-1);
}

//===========================================
//  Time Module
//===========================================

real GetTime(void);
void SleepMs(real ms);
void EndLoop(void);
void Wait(real targetFPS);
real GetFPS(void);

#include <time.h>
#if defined(__CB_WINDOWS)
    #include <Windows.h>
#elif defined(__CB_POSIX)
    #include <unistd.h>
    #include <sys/time.h>
#else

#endif

struct {
    u32 frame_counter;
    real previous;
    real current;
    real frame;
    real fps;
    real extratime;
    i32 hist_i;
    real history[30];
    real average;
    real target_fps;
} __CBSYS_time = {0};
// stole this from Ascede

real __CBSYS_TimeDiff(void);
real __CBSYS_GetTime(void);
void __CBSYS_SleepMs(real ms);
void __CBSYS_EndLoop(void);
void __CBSYS_Wait(real target_fps);
real __CBSYS_GetFPS(void);

const struct {
    real (*get)(void);
    real (*getFPS)(void);
    void (*wait)(real target_fps);
    void (*endLoop)(void);
} Time = {
    .get=__CBSYS_GetTime,
    .getFPS=__CBSYS_GetFPS,
    .wait=__CBSYS_Wait,
    .endLoop=__CBSYS_EndLoop
};

real __CBSYS_TimeDiff(void){
    real diff=__CBSYS_GetTime()-__CBSYS_time.previous;
    if(diff<0)diff+=60.0f;
    return diff;
}
real __CBSYS_GetTime(void){
#if defined(__CB_WINDOWS)
// Broken implementation: piece of shit with a
//   ridiculous granularity of ~50 ms...
//    LARGE_INTEGER qpctime, qpcfreq;
//    QueryPerformanceCounter(&qpctime);
//    QueryPerformanceFrequency(&qpcfreq);
//    real tmreal=qpctime.QuadPart*1.0f/qpcfreq.QuadPart;
    SYSTEMTIME systime;
    GetSystemTime(&systime);
    real tmreal=0.001f*systime.wMilliseconds+1.0f*systime.wSecond;
    return tmreal;
#else
    struct timespec tmspec;
//    timespec_get(&tmspec, TIME_UTC);
    clock_gettime(CLOCK_MONOTONIC, &tmspec);
    real tmreal=tmspec.tv_nsec/1000000000.0f+tmspec.tv_sec*1.0f;
    return tmreal;
#endif
}
void __CBSYS_SleepMs(real ms){
    if(ms<=0)return;
#if defined(__CB_WINDOWS)
    // Sleep() is a piece of fucking shit, totally screws up the precision (~5-10ms)
    // But it works, and I just can't figure out why
    Sleep((u32)ms);
#elif defined(__CB_POSIX)
    #if defined(__CB_POSIX_USE_USLEEP)
        // Special: usleep() is deprecated on later POSIX standards
        usleep(ms*1000.0f);
    #else
        struct timespec req = { 0 };
        time_t sec = (i32)(ms/1000.0f);
        ms -= (sec*1000);
        req.tv_sec = sec;
        req.tv_nsec = ms*1000000L;
        while (nanosleep(&req, &req) == -1) continue;
    #endif
#endif
}
void __CBSYS_EndLoop(void){
    __CBSYS_time.frame_counter++;
    __CBSYS_time.current=__CBSYS_GetTime();
    __CBSYS_time.frame=__CBSYS_time.current-__CBSYS_time.previous;
    __CBSYS_time.previous=__CBSYS_time.current;
    if(__CBSYS_time.frame>=0){
        __CBSYS_time.hist_i=(__CBSYS_time.hist_i+1)%30;
        __CBSYS_time.average-=__CBSYS_time.history[__CBSYS_time.hist_i];
        __CBSYS_time.history[__CBSYS_time.hist_i]=__CBSYS_time.frame/30.0f;
        __CBSYS_time.average+=__CBSYS_time.history[__CBSYS_time.hist_i];
        __CBSYS_time.fps=1.0f/__CBSYS_time.average;
    }else{
        __CBSYS_time.fps=0;
    }
}
void __CBSYS_Wait(real target_fps){
    if(target_fps<=0.5f)return;
    if(target_fps>32767.0f)return;
    __CBSYS_time.target_fps=target_fps;
    real extra=__CBSYS_time.extratime;
    real target=1.0f/target_fps;
    real wait=target-__CBSYS_TimeDiff();
    // Prevent losing too many frames.
    real absextra=extra>0?extra:-1.0f*extra;
    if(absextra>target*5.0f && absextra>0.1f){
        extra=0;
    }
    if(wait+extra>0){
        real ms=wait+extra;
        ms*=1000.0f;
        __CBSYS_SleepMs(ms);
    }
    extra+=target-__CBSYS_TimeDiff();
    __CBSYS_time.extratime=extra;
}
real __CBSYS_GetFPS(void){
    return __CBSYS_time.fps;
}

//===========================================
//  Linked List Data Structure
//===========================================

typedef struct Node Node;
typedef struct LList LList;
struct Node {
    void *data;
    Node *prev;
    Node *next;
    LList *mother;
};

struct LList {
    u32 len;
    Node *head;
    Node *tail;
};

LList __CBLL_NewList(void); // REMEMBER TO kill() THE LISTS!!
Node *__CBLL_Locate(LList *llist, void *data);
void __CBLL_Push(LList *llist, void *data);
void __CBLL_Delete(Node *node);
void __CBLL_Kill(LList *llist);
void __CBLL_MoveNode(Node *node, LList *dest);

const struct {
    LList (*newList)(void);
    Node *(*locate)(LList *llist, void *data);
    void (*push)(LList *llist, void *data);
    void (*delete)(Node *node);
    void (*kill)(LList *llist);
    void (*moveNode)(Node *node, LList *dest);
} LL = {
    .newList=__CBLL_NewList,
    .locate=__CBLL_Locate,
    .push=__CBLL_Push,
    .delete=__CBLL_Delete,
    .kill=__CBLL_Kill,
    .moveNode=__CBLL_MoveNode
};

LList __CBLL_NewList(void){
    return (LList){.len=0, .head=NULL, .tail=NULL};
}
Node *__CBLL_Locate(LList *llist, void *data){
    for(Node *node=llist->tail; node; node=node->prev){
        if(node->data==data)return node;
    }
    return NULL;
}
void __CBLL_Push(LList *llist, void *data){
    if(!llist || !data)return;
    Node *node=calloc(1, sizeof(Node));
    if(!node){
        Log.fatal("Cannot allocate memory.");
    }
    node->prev=NULL;
    node->next=NULL;
    node->data=data;
    node->mother=llist;
    if(llist->head){
        llist->tail->next=node;
        node->prev=llist->tail;
    }else{
        llist->head=node;
    }
    llist->tail=node;
    llist->len++;
}
void __CBLL_Delete(Node *node){
    if(!node)return;
    if(node->mother->head==node)node->mother->head=node->next;
    if(node->mother->tail==node)node->mother->tail=node->prev;
    if(node->prev)node->prev->next=node->next;
    if(node->next)node->next->prev=node->prev;
    node->mother->len--;
    free(node);
}
void __CBLL_Kill(LList *llist){
    if(!llist)return;
    Node *node=llist->tail;
    while(node){
        Node *prev=node->prev;
        free(node);
        node=prev;
    }
    llist->tail=NULL;
    llist->head=NULL;
    llist->len=0;
}
void __CBLL_MoveNode(Node *node, LList *dest){
    if(!node || !dest)return;
    if(node->mother->head==node)node->mother->head=node->next;
    if(node->mother->tail==node)node->mother->tail=node->prev;
    if(node->prev)node->prev->next=node->next;
    if(node->next)node->next->prev=node->prev;
    node->mother->len--;
    if(dest->head){
        dest->tail->next=node;
        node->prev=dest->tail;
    }else{
        dest->head=node;
        dest->tail=node;
        node->prev=NULL;
    }
    node->next=NULL;
    dest->tail=node;
    dest->len++;
    node->mother=dest;
}

void __CBLL_PrintLList(LList *llist, void (*printFunc)(void *NodeData)){
    if(!llist)return;
    Log.debug("Printing Linked List of length %" SPECu32, llist->len);
    fflush(stdout);
    Node *node=llist->head;
    printf("{");
    while(node){
        if(printFunc){
            printFunc(node->data);
        }else{
            i32 value=*(i32 *)node->data;
            printf("%" SPECi32, value);
        }
        if(node->next)printf(", ");
        node=node->next;
    }
    printf("}\n");
}

//===========================================
//  Memory Module
//===========================================
// (Requires linked list data structure)

void *__CBMEM_Calloc(size_t nitems, size_t size);
void __CBMEM_Free(void *ptr);
void __CBMEM_FreeAll(void);

LList __CBMEM_mem_list={.len=0, .head=NULL, .tail=NULL};

const struct {
    void *(*calloc)(size_t nitems, size_t size);
    void (*free)(void *ptr);
    void (*freeAll)(void);
} Mem = {
    .calloc=__CBMEM_Calloc,
    .free=__CBMEM_Free,
    .freeAll=__CBMEM_FreeAll
};

void *__CBMEM_Calloc(size_t nitems, size_t size){
    void *ptr=calloc(nitems, size);
    if(!ptr){
        Log.fatal("Cannot allocate memory.");
        return NULL;
    }
    LL.push(&__CBMEM_mem_list, ptr);
    return ptr;
}
void __CBMEM_Free(void *ptr){
    if(!ptr)return;
    LL.delete(LL.locate(&__CBMEM_mem_list, ptr));
    free(ptr);
}
void __CBMEM_FreeAll(void){
    Node *node=__CBMEM_mem_list.head;
    while(node){
        Node *next=node->next;
        free(node->data);
        node=next;
    }
    Log.debug("%" SPECu32 " allocation%s freed.", __CBMEM_mem_list.len, __CBMEM_mem_list.len>1?"s":"");
    LL.kill(&__CBMEM_mem_list);
}

#endif
