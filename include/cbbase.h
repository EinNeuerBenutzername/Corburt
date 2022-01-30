#ifndef Corburt_Base_h_Include_Guard
#define Corburt_Base_h_Include_Guard
#define DISPLAY_WIDTH 68
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
    bat maxhp;
    bat hp;
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
} player={L"",1,1,0,10,10,{0,0,0,0,0,0,0,14},1};
struct inventory{
    nat unlocked;
    nat items[64];
    nat accessories[5];
    nat weapon;
    nat armor;
    bat money;
} inventory={16,{0},{0},0,0,100000};
struct save{
    nat valid;
    struct player plr;
    struct inventory inv;
};
const nat savescount=5;
struct save saves[5]={0};
int_fast32_t cursaveid=0;
void *pointerpool[128]={NULL};
nat pointerinuse=0;
real tick=0.0f;

//basic
enum errorenum{
    error_cannotmalloc,
    error_cannotrealloc,
    error_badcharbit,
    error_bufferpooloverflow,
    error_cannotsave,
};
void printc(int color,const wchar_t *format,...); // obsolete, please use printr()
size_t wcwidth(const wchar_t wc);
size_t wcswidth(const wchar_t *wcs);
void printr(int color,const wchar_t *format,...);
void printrp(int color,const wchar_t *linepref,const wchar_t *format,...);
void printword(size_t *pos,size_t width,wchar_t *word);
void tracelog(int color,const wchar_t *format,...);
void fatalerror(enum errorenum error_id);
void *mallocpointer_(size_t bytes); // for testing
void *mallocpointer(size_t bytes);
void *reallocpointer(void *pointer,size_t bytes);
void freepointer_(void *pointer); // for testing
void freepointer(void *pointer);
void freeall();
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
size_t wcwidth(const wchar_t wc){
    if((wc>=11904&&wc<=55215)||(wc>=63744&&wc<=64255)||(wc>=65281&&wc<=65374)){ // ambiguous E.Asian wide characters
        return 2;
    }
    return 1;
}
size_t wcswidth(const wchar_t *wcs){
    size_t len=0;
    for(size_t i=0;i<wcslen(wcs);i++){
        len+=wcwidth(wcs[i]);
    }
    return len;
}
    wchar_t *printr_dest=NULL;
    wchar_t *printr_token=NULL;
    size_t pos=0;
void printr(int color,const wchar_t *format,...){
    if(color!=Default)cbc_setcolor(color);
    fflush(stdout);
    wmemset(printr_dest,0,4096);
    wmemset(printr_token,0,DISPLAY_WIDTH);
    va_list args;
    va_start(args,format);
    vswprintf(printr_dest,4096,format,args);
    va_end(args);

    size_t wcsl=0,wcsw=0,wcsld=wcslen(printr_dest);
    for(size_t i=0;i<wcsld;i++){
        if(printr_dest[i]==L'\n'){
            if(wcsl>0)wprintf(L"%ls\n",printr_token);
            else putc('\n',stdout);
            pos=0;wmemset(printr_token,0,wcsl);
            wcsl=0;wcsw=0;
        }
        else if(printr_dest[i]==L' '){
            if(wcsl>0)wprintf(L"%ls ",printr_token);
            else putc(' ',stdout);
            pos+=wcsl+1;wmemset(printr_token,0,wcsl);
            wcsl=0;wcsw=0;
        }
        else{
            if(wcsw+pos>=DISPLAY_WIDTH-1){
                size_t j;
                for(j=i;j<wcslen(printr_dest);j++){
                    if(printr_dest[j]==L'\n'||printr_dest[j]==L' ')break;
                }
                if(j-i+1<DISPLAY_WIDTH){
                    wprintf(L"\n%ls",printr_token);
                    pos=wcsw;wmemset(printr_token,0,wcsl);
                    wcsl=0;wcsw=0;
                }else{
                    wprintf(L"%ls\n",printr_token);
                    pos=0;wmemset(printr_token,0,wcsl);
                    wcsl=0;wcsw=0;
                }
            }
            printr_token[wcsl]=printr_dest[i];
            wcsl++;
            wcsw+=wcwidth(printr_dest[i]);
            if(i+1==wcsld){
                wprintf(L"%ls",printr_token);
                pos+=wcsw;wmemset(printr_token,0,wcsl);
                wcsl=0;wcsw=0;
            }
        }
    }
    if(color!=Default)cbc_setcolor(Default);
    fflush(stdout);
}
void printrp(int color,const wchar_t *linepref,const wchar_t *format,...){
    if(color!=Default)cbc_setcolor(color);
    fflush(stdout);
    wmemset(printr_dest,0,4096);
    wmemset(printr_token,0,DISPLAY_WIDTH);
    va_list args;
    va_start(args,format);
    vswprintf(printr_dest,4096,format,args);
    va_end(args);

    size_t wcsl=0,wcsw=0,wcsld=wcslen(printr_dest),wcswp=wcswidth(linepref);
    for(size_t i=0;i<wcsld;i++){
        if(printr_dest[i]==L'\n'){
            if(wcsl>0)wprintf(L"%ls\n",printr_token);
            else putc('\n',stdout);
            if(i<wcsld-1){
                wprintf(L"%ls",linepref);
                pos=wcswp;
            }else pos=0;
            wmemset(printr_token,0,wcsl);
            wcsl=0;wcsw=0;
        }
        else if(printr_dest[i]==L' '){
            if(wcsl>0)wprintf(L"%ls ",printr_token);
            else putc(' ',stdout);
            pos+=wcsl+1;wmemset(printr_token,0,wcsl);
            wcsl=0;wcsw=0;
        }
        else{
            if(wcsw+pos>=DISPLAY_WIDTH-1){
                size_t j;
                for(j=i;j<wcslen(printr_dest);j++){
                    if(printr_dest[j]==L'\n'||printr_dest[j]==L' ')break;
                }
                if(j-i+1<DISPLAY_WIDTH-wcswp){
                    wprintf(L"\n%ls%ls",linepref,printr_token);
                    pos=wcsw+wcswp;wmemset(printr_token,0,wcsl);
                    wcsl=0;wcsw=0;
                }else{
                    wprintf(L"%ls\n%ls",printr_token,linepref);
                    pos=wcswp;wmemset(printr_token,0,wcsl);
                    wcsl=0;wcsw=0;
                }
            }
            printr_token[wcsl]=printr_dest[i];
            wcsl++;
            wcsw+=wcwidth(printr_dest[i]);
            if(i+1==wcsld){
                pos=0;
                if(wcsl<wcsld){
                    wprintf(L"%ls",linepref);
                    pos+=wcswp;
                }
                wprintf(L"%ls",printr_token);
                pos+=wcsw;wmemset(printr_token,0,wcsl);
                wcsl=0;wcsw=0;
            }
        }
    }

    if(color!=Default)cbc_setcolor(Default);
    fflush(stdout);
}
void tracelog(int color,const wchar_t *format,...){
#ifdef Corburt_Debug
    if(color!=Default)cbc_setcolor(color);
    fflush(stdout);
    va_list args;
    va_start(args,format);
    vwprintf(format,args);
    va_end(args);
    if(color!=Default)cbc_setcolor(Default);
    fflush(stdout);
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
    case error_bufferpooloverflow:
        msg=msg_error_bufferpooloverflow;break;
    case error_cannotsave:
        msg=msg_error_cannotsave;break;
    default:
        msg=msg_error_unknown;break;
    }
    printr(Red,msg);
    FILE *errorlog=fopen("err.log","a");
    fprintf(errorlog,"%ls",msg);
    fclose(errorlog);
    exit(-1);
}
void *mallocpointer_(size_t bytes){
    if(pointerinuse>128){
        fatalerror(error_bufferpooloverflow);
    }
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    pointerinuse++;
    if(Corburt_Pointer_Trace_Level>0){
        tracelog(Green,msg_trace_malloced,bytes);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    for(nat i=0;i<128;i++){
        if(pointerpool[i]==NULL){
            pointerpool[i]=pointer;
            break;
        }
    }
    return pointer;
}
void *mallocpointer(size_t bytes){
    if(pointerinuse>128){
        fatalerror(error_bufferpooloverflow);
    }
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    pointerinuse++;
    if(Corburt_Pointer_Trace_Level>1){
        tracelog(Green,msg_trace_malloced,bytes);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    for(nat i=0;i<128;i++){
        if(pointerpool[i]==NULL){
            pointerpool[i]=pointer;
            break;
        }
    }
    return pointer;
}
void *reallocpointer(void *pointer,size_t bytes){
    for(nat i=0,found=0;i<128;i++){
        if(pointerpool[i]==pointer){
            found=1;
            break;
        }
        if(i==127&&found==0){
            printc(Red,msg_trace_illegalrealloc);
            return NULL;
        }
    }
    pointer=realloc(pointer,bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    if(Corburt_Pointer_Trace_Level>0){
        tracelog(Green,msg_trace_realloced,bytes);
    }
    return pointer;
}
void freepointer_(void *pointer){
    if(pointer==NULL)return;
    for(nat i=0;i<128;i++){
        if(pointerpool[i]==pointer){
            pointerpool[i]=NULL;
            break;
        }
        if(i==127){
            printc(Red,msg_trace_illegalfree);
            return;
        }
    }
    free(pointer);
    pointerinuse--;
    if(Corburt_Pointer_Trace_Level>0){
        tracelog(Green,msg_trace_freed);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    pointer=NULL;
}
void freepointer(void *pointer){
    if(pointer==NULL)return;
    for(nat i=0;i<128;i++){
        if(pointerpool[i]==pointer){
            pointerpool[i]=NULL;
            break;
        }
        if(i==127){
            printc(Red,msg_trace_illegalfree);
            return;
        }
    }
    free(pointer);
    pointerinuse--;
    if(Corburt_Pointer_Trace_Level>1){
        tracelog(Green,msg_trace_freed);
        tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    }
    pointer=NULL;
}
void freeall(){
    tracelog(Green,msg_trace_pointerinuse,pointerinuse);
    for(nat i=0;i<128&&pointerinuse>0;i++){
        if(pointerpool[i]!=NULL){
            free(pointerpool[i]);
            pointerinuse--;
        }
    }
    tracelog(Green,msg_trace_freealled);
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
void endcb();
void assertcheck();
nat match(const wchar_t *sub_str,const wchar_t *main_str);
void checkendianess();
void initrng();
void assertcheck(){
    if(CHAR_BIT!=8)fatalerror(error_badcharbit);
}
nat match(const wchar_t *sub_str,const wchar_t *main_str){
    if(wcslen(main_str)==0)return 0;
    wchar_t *str1l=mallocpointer(sizeof(wchar_t)*(wcslen(main_str)+1));
    wchar_t *str2l=mallocpointer(sizeof(wchar_t)*(wcslen(sub_str)+1));
    wcscpy(str1l,main_str);
    wcscpy(str2l,sub_str);
    wcslower(&str1l);
    wcslower(&str2l);
    str1l[wcslen(str1l)]=0;
    str2l[wcslen(str2l)]=0;
    wchar_t *matchpos=wcsstr(str1l,str2l);
    if(matchpos==NULL){
        freepointer(str1l);
        freepointer(str2l);
        return -1;
    }else{
        if(matchpos==str1l||str1l[(matchpos-str1l)-1]==L' '){
            freepointer(str1l);
            freepointer(str2l);
            real m=(10000.0f*wcslen(sub_str))/(1.0f*wcslen(main_str));
            return (nat)m;
        }else{
            freepointer(str1l);
            freepointer(str2l);
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

// cbm
enum direction{
    dir_East,dir_West,dir_North,dir_South,dir_Up,dir_Down
};
// cbp
static void plvlup();
static void paddgearstats();
void paddexp(nat add);
void phpchange(nat num);
void pdie();
void pcalcstats();
void pshowstats();
void pshowabl();
void pshowinv();
void pshowexp();
void pmove(enum direction dir);
void pattack();
void ptrain();
void peditstats();
#endif
