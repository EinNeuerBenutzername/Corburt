#ifndef __CBIO
#define __CBIO

// GAME LAYER

#include <stdio.h>
#include <string.h>
#include "cbsys.h"
#include "cbcurses.h"

#define __CB_DISPLAY_WIDTH 20

void __CBIO_Init(void);
bool __CBIO_IsWhitespace(char c);
i32 __CBIO_Match(const char *sub, const char *main); // returns matching percentage
bool __CBIO_FullMatch(char *str, const char *str2);
void __CBIO_Printf(const char *format, ...);

struct {
    i32 pos;
} __CBIO_data = {
    .pos=0
};

const struct {
    void (*init)(void);
    i32 (*match)(const char *main, const char *sub);
    bool (*fullMatch)(char *str, const char *str2);
    void (*printf)(const char *format, ...);
} IO={
    .init=__CBIO_Init,
    .match=__CBIO_Match,
    .fullMatch=__CBIO_FullMatch,
    .printf=__CBIO_Printf
};

void __CBIO_Init(void){
    setvbuf(stdout, NULL, _IOFBF, 0);
}
bool __CBIO_IsWhitespace(char c){
    return c==' ' || c=='\n' || c=='\t' || c=='\v' || c=='\f' || c=='\r';
}
i32 __CBIO_Match(const char *main, const char *sub){
    if(!main || !sub)return -1;
    if(*main=='0' || *sub=='0')return 0;
    char *matchpos=strstr(main, sub);
    if(matchpos==NULL){
        return -1;
    }else{
        if(matchpos==main || __CBIO_IsWhitespace(*(matchpos-1))){
            real m=(10000.0f*strlen(sub))/(1.0f*strlen(main));
            return (int)m;
        }
        else return -1;
    }
}
bool __CBIO_FullMatch(char *str, const char *str2){
    if(str==NULL && str2==NULL)return true;
    if(*str=='0' && *str2=='0')return true;
    if(str==NULL || str2==NULL)return false;
    if(*str=='0' || *str2=='0')return false;
    if(strlen(str)<strlen(str2))return false;
    if(str[0]!=str2[0])return false;
    if(strlen(str)>strlen(str2)){
        if(str[strlen(str2)]!=' ')return false;
        for(size_t i=0; i<strlen(str2); i++){
            if(str[i]!=str2[i])return false;
        }
        return true;
    }
    else{
        if(strcmp(str, str2)==0)return true;
        return false;
    }
}

void __CBIO_PrintWord(const char *word, i32 word_len, i32 state){
    int iword_len=word_len;
    if(__CBIO_data.pos+word_len<=__CB_DISPLAY_WIDTH){
        printf("%.*s", iword_len, word);
        __CBIO_data.pos+=word_len;
    }else{
        if(word_len<__CBIO_data.pos){
            printf("\n%.*s", iword_len, word);
            __CBIO_data.pos=word_len;
        }else{

        }
    }
}

void __CBIO_Printf(const char *format, ...){
    char *dest=Mem.malloc(4096);
    va_list args;
    va_start(args, format);
    vsprintf(dest, format, args);
    va_end(args);
    char *dend=dest, *dstart=dest;
    // 1 - WORD (including HYPHENS)
    // 2 - COLOR INDICATOR
    // 4 - WHITESPACE
    // 8 - INITIAL TOKEN
    i32 state=8;
    for(; *dend; dend++){
        if(__CBIO_IsWhitespace(*dend)){
            dend++;
            __CBIO_PrintWord(dstart, dend-dstart, state);
            state=0;
            dstart=dend;
        }else{

        }
    }
    __CBIO_PrintWord(dstart, dend-dstart, state);
    Mem.free(dest);
    fflush(stdout);
}

#endif
