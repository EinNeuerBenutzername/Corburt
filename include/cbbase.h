#ifndef Corburt_Base_h_Include_Guard
#define Corburt_Base_h_Include_Guard
#if __STDC_VERSION__<199901L
    #error Please use a C99 compiler.
#endif
#include "msg.h"
#include "mtwister.h"
#include <time.h>
#include <wchar.h>
#include <stdarg.h>
#include <stdlib.h> //malloc() realloc() free() exit()
#include <stdbool.h>
#include <inttypes.h>

typedef bool foo;
typedef int_fast32_t nat;//32-bit number
typedef int_fast64_t bat;//64-bit integer
//typedef unsigned __int64 bat;
typedef double real;
MTRand mtrand;
foo quit_game=false;
foo isle=true; //platform endianess. this is not a flag.
wchar_t *inputbuf;
wchar_t *buffer;
struct input{
    nat deletable;
    wchar_t *line;
}input;
struct player{
    wchar_t name[32];
    nat rnk;
    nat lvl;
    bat exp;
    nat maxhp;
    nat hp;
    nat regen;
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
    nat roomid;
} player={L"",1,1,0,10,10,1,{0,0,0,0,0,0,0,21},1};
struct inventory{
    nat unlocked;
    nat items[64];
    nat accessories[5];
    nat weapon;
    nat armor;
    bat money;
} inventory={16,{0},{0},0,0,1000};
struct save{
    nat valid;
    struct player plr;
    struct inventory inv;
};
const nat savescount=5;
struct save saves[5]={0};
int_fast32_t cursaveid=0;
nat pointerinuse=0;
real tick=0.0f;

//basic
enum errorenum{
    error_cannotmalloc,
    error_cannotrealloc,
    error_badcharbit
};
void printc(int color,const wchar_t *format,...);
void printr(int color,const wchar_t *format,...);
void printword(size_t pos,size_t width,wchar_t *word);
void tracelog(int color,const wchar_t *format,...);
void fatalerror(enum errorenum error_id);
void *mallocpointer(size_t bytes);
void *mallocpointer_(size_t bytes); // visible when Corburt_Pointer_Trace_Level is bigger than 2
void *reallocpointer(void *pointer,size_t bytes);
void freepointer(void *pointer);
void freepointer_(void *pointer);
void scanline(wchar_t *scan_str,int scans);
void wcslower(wchar_t **target_str_pos);
void printc(int color,const wchar_t *format,...){
    if(color!=Default)cbc_setcolor(color);
    fflush(stdout);
    va_list args;
    va_start(args,format);
    vwprintf(format,args);
    va_end(args);
    if(color!=Default)cbc_setcolor(Default);
    fflush(stdout);
}
void printr(int color,const wchar_t *format,...){
    if(color!=Default)cbc_setcolor(color);
    wchar_t *dest=mallocpointer_(1024*sizeof(wchar_t));
    wchar_t *token;
    wmemset(dest,0,1024);
    fflush(stdout);
    va_list args;
    va_start(args,format);
    vswprintf(dest,1024,format,args);
    va_end(args);

    if(dest[0]==L' ')putc(' ',stdout);
    size_t row,col;
    foo endwithspace=false;
    cbc_getcursor(&row,&col);
    if(dest[wcslen(dest)-1]==L' ')endwithspace=true;
    token=wcstok(dest,L" ");
    printword(col,67,token);
    if(token!=NULL)token=wcstok(NULL,L" ");
    while(token!=NULL){
        putc(' ',stdout);
        cbc_getcursor(&row,&col);
        printword(col,68,token);
        token=wcstok(NULL,L" ");
    }
    if(endwithspace)putc(' ',stdout);

    if(color!=Default)cbc_setcolor(Default);
    fflush(stdout);
    freepointer_(dest);
}
void printword(size_t pos,size_t width,wchar_t *word){
    if(wcslen(word)+pos<width){
        wprintf(L"%ls",word);
    }
    else if(wcslen(word)>=width){
        size_t start=0,wcsl=wcslen(word);
        wchar_t *line=mallocpointer_((width+1)*sizeof(wchar_t));
        wmemset(line,0,width+1);
        wmemcpy(line,word,width-pos);
        wprintf(L"%ls\n",line);
        start+=width-pos;
        while(wcsl-start>width+1){
            wmemset(line,0,width+1);
            wmemcpy(line,word+start,width);
            wprintf(L"%ls\n",line);
            start+=width;
        }
        wmemset(line,0,width+1);
        wmemcpy(line,word+start,wcsl-start);
        wprintf(L"%ls",line);
        freepointer_(line);
    }
    else{
        wprintf(L"\n%ls",word);
    }
}
void tracelog(int color,const wchar_t *format,...){
#ifdef Corburt_Debug
    cbc_setcolor(color);
    va_list args;
    va_start(args,format);
    vwprintf(format,args);
    va_end(args);
    cbc_setcolor(Default);
#else
    return;
#endif
}
void fatalerror(enum errorenum error_id){
    const wchar_t *msg;
    switch(error_id){
    case error_cannotmalloc:
        msg=msg_error_cannotmalloc;break;
    case error_cannotrealloc:
        msg=msg_error_cannotrealloc;break;
    case error_badcharbit:
        msg=msg_error_badcharbit;break;
    default:
        msg=msg_error_unknown;break;
    }
    printc(Red,msg);
    exit(-1);
}
void *mallocpointer(size_t bytes){
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    if(Corburt_Pointer_Trace_Level>0){
        pointerinuse++;
        tracelog(Green,msg_trace_malloced,bytes);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    return pointer;
}
void *mallocpointer_(size_t bytes){
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    if(Corburt_Pointer_Trace_Level>1){
        pointerinuse++;
        tracelog(Green,msg_trace_malloced,bytes);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    return pointer;
}
void *reallocpointer(void *pointer,size_t bytes){
    return realloc(pointer,bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    if(Corburt_Pointer_Trace_Level>0){
        tracelog(Green,msg_trace_realloced,bytes);
    }
    return pointer;
}
void freepointer(void *pointer){
    if(pointer==NULL)return;
    free(pointer);
    if(Corburt_Pointer_Trace_Level>0){
        pointerinuse--;
        tracelog(Green,msg_trace_freed);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    pointer=NULL;
}
void freepointer_(void *pointer){
    if(pointer==NULL)return;
    free(pointer);
    if(Corburt_Pointer_Trace_Level>1){
        pointerinuse--;
        tracelog(Green,msg_trace_freed);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    pointer=NULL;
}
void scanline(wchar_t *scan_str,int scans){
    cbc_setcolor(Yellow);
    fflush(stdout);
    fgetws(scan_str,scans,stdin);
    if(scan_str[wcslen(scan_str)-1]==L'\n'){
        scan_str[wcslen(scan_str)-1]=0;
    }
    fflush(stdin);
    cbc_setcolor(Default);

    fflush(stdout);
}
void wcslower(wchar_t **target_str_pos){
    for(size_t i=0;i<wcslen(*target_str_pos);i++){
        if((*target_str_pos)[i]<=90&&(*target_str_pos)[i]>=65){
            (*target_str_pos)[i]+=32;
        }
    }
}
//misc
void launchcb();
void assertcheck();
nat match(const wchar_t *sub_str,const wchar_t *main_str);
void checkendianess();
void initrng();
void assertcheck(){
    if(CHAR_BIT!=8)fatalerror(error_badcharbit);
}
nat match(const wchar_t *sub_str,const wchar_t *main_str){
    if(wcslen(main_str)==0)return 0;
    wchar_t *str1l=mallocpointer_(sizeof(wchar_t)*(wcslen(main_str)+1));
    wchar_t *str2l=mallocpointer_(sizeof(wchar_t)*(wcslen(sub_str)+1));
    wcscpy(str1l,main_str);
    wcscpy(str2l,sub_str);
    wcslower(&str1l);
    wcslower(&str2l);
    str1l[wcslen(str1l)]=0;
    str2l[wcslen(str2l)]=0;
    wchar_t *pos=wcsstr(str1l,str2l);
    if(pos==NULL){
        freepointer_(str1l);
        freepointer_(str2l);
        return -1;
    }else{
        if(pos==str1l||str1l[(pos-str1l)-1]==L' '){
            freepointer_(str1l);
            freepointer_(str2l);
            real m=(10000.0f*wcslen(sub_str))/(1.0f*wcslen(main_str));
            return (nat)m;
        }else{
            freepointer_(str1l);
            freepointer_(str2l);
            return -1;
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
    bat seed;
    tracelog(Green,msg_trace_rnginit);
    tracelog(Green,msg_trace_rngseed,seed=time(NULL));
    mtrand=seedRand(seed);
    tracelog(Green,msg_trace_rngtest,genRandLong(&mtrand));
}

#endif
