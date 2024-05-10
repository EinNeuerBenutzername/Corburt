#ifndef __CBIO
#define __CBIO

// GAME LAYER

#include <stdio.h>
#include <string.h>
#include "cbsys.h"
#include "cbcurses.h"
#include "cbrng.h"

#define __CB_DISPLAY_WIDTH 64
#define __CBIO_MAX_WORD_SEGS 64

//===========================================
//  External Functions / APIs
//===========================================

void __CBIO_Init(void);
i32 __CBIO_Match(const char *sub, const char *main); // Returns matching percentage {-1} + [0, 10000]
bool __CBIO_FullMatch(char *str, const char *str2);
void __CBIO_Printf(const char *format, ...);
i32 __CBIO_GetColorMode(void);
void __CBIO_SetColorMode(i32 mode_on);

struct {
    i32 color_off;
    i32 pos;
    i32 prevcolor;
    Rand32 io_rand32;
    struct {
        i32 size;
        i32 len;
        struct {
            const char *word;
            i32 color;
            i32 tint;
            i32 len;
            i32 init;
        } segs[__CBIO_MAX_WORD_SEGS];
    } seg;
} __CBIO_data = {
    .color_off=0,
    .pos=0,
    .prevcolor=Default,
    .io_rand32={0},
    .seg={0},
};

const struct {
    void (*init)(void);
    i32 (*match)(const char *main, const char *sub);
    bool (*fullMatch)(char *str, const char *str2);
    void (*printf)(const char *format, ...);
    i32 (*getColorMode)(void);
    void (*setColorMode)(i32 mode_on);
} IO={
    .init=__CBIO_Init,
    .match=__CBIO_Match,
    .fullMatch=__CBIO_FullMatch,
    .printf=__CBIO_Printf,
    .getColorMode=__CBIO_GetColorMode,
    .setColorMode=__CBIO_SetColorMode,
};

#include "cbpalette.h"

void __CBIO_Init(void){
    RNG.srand32(&__CBIO_data.io_rand32, time(NULL)^445145);
    setvbuf(stdout, NULL, _IOFBF, 0);
}

i32 __CBIO_IsWhitespace(char c);

i32 __CBIO_IsWhitespace(char c){
    return c==' ' || c=='\t' || c=='\v' || c=='\f' || c=='\r';
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
        if(!__CBIO_IsWhitespace(str[strlen(str2)]))return false;
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
i32 __CBIO_GetColorMode(void){
    return 1-__CBIO_data.color_off;
}
void __CBIO_SetColorMode(i32 mode_on){
    __CBIO_data.color_off=(mode_on==0);
}

//===========================================
//  printf()
//===========================================

i32 __CBIO_CheckColorIndEscape(i32 width, char *full_str, char *c);
i32 __CBIO_IsColorIndicator(char *full_str, char *c, int *color); // Returns width of indicator
void __CBIO_PrintWord(const char *word, i32 word_len, i32 init);
void __CBIO_CommitWordSeg(const char *word, i32 seg_len, i32 init);
void __CBIO_PrintAllWordSegs();

void __CBIO_Visualize(const char *word, i32 word_len);
void __CBIO_EntropyDisplay(i32 ent, const char *word, i32 word_len);

i32 __CBIO_IsColorIndicator(char *full_str, char *c, int *color){
    // Returns width of indicator, 0 for no indicator
    // The final width is added by 3
    if(!full_str || !c || !color)return 0;
    if(!*c || *c!='{')return 0;
    if(c!=full_str && *(c-1)=='\\')return 0;
    c++;
    if(!*c || *c!='$')return 0;
    char ind[__CB_PALETTE_MAX_IND_LENGTH+1]={0};
    for(i32 i=0; i<=__CB_PALETTE_MAX_IND_LENGTH; i++){
        c++;
        if(!*c)return 0;
        if(*c=='}')break;
        if(*c!='}'){
            ind[i]=*c;
            if(i==__CB_PALETTE_MAX_IND_LENGTH)return 0;
        }
    }
    for(i32 i=0; i<__CB_PALETTE_MAXCOLORS; i++){
        if(!__CBPALETTE_data.colors[i].ind)break;
        if(strcmp(ind, __CBPALETTE_data.colors[i].ind)==0){
            if(i==0){
                *color=__CBIO_data.prevcolor;
            }else{
                __CBIO_data.prevcolor=*color;
                *color=__CBPALETTE_data.colors[i].color;
            }
            if(__CBPALETTE_data.colors[i].width)return __CBPALETTE_data.colors[i].width+3;
            else return (i32)(strlen(__CBPALETTE_data.colors[i].ind)+3);
        }
    }
    return 0;
}
void __CBIO_PrintWord(const char *word, i32 word_len, i32 init){
    // 1 - WORD (including HYPHENS): PRINT AS USUAL
    // 2 - WHITESPACE: KILL HEADS
    // 4 - INITIAL TOKEN: PRINT AS USUSAL
    if(__CBIO_data.seg.size)__CBIO_PrintAllWordSegs();
    if(!word || !(*word) || !word_len)return;
    if(__CBIO_data.pos+word_len<=__CB_DISPLAY_WIDTH){
//        printf("%.*s", (int)word_len, word);
        __CBIO_Visualize(word, word_len);
        __CBIO_data.pos+=word_len;
    }else if(__CBIO_IsWhitespace(*word) && !init){
        printf("\n");
        __CBIO_data.pos=0;
    }else if(word_len<=__CB_DISPLAY_WIDTH){
//        printf("\n%.*s", (int)word_len, word);
        printf("\n");
        __CBIO_Visualize(word, word_len);
        __CBIO_data.pos=word_len;
    }else{
        if(__CB_DISPLAY_WIDTH>__CBIO_data.pos){
//            printf("%.*s", (int)(__CB_DISPLAY_WIDTH-__CBIO_data.pos), word);
            __CBIO_Visualize(word, __CB_DISPLAY_WIDTH-__CBIO_data.pos);
            word_len-=__CB_DISPLAY_WIDTH-__CBIO_data.pos;
            word+=__CB_DISPLAY_WIDTH-__CBIO_data.pos;
        }
        while(word_len>=__CB_DISPLAY_WIDTH){
//            printf("\n%.*s", (int)__CB_DISPLAY_WIDTH, word);
            printf("\n");
            __CBIO_Visualize(word, __CB_DISPLAY_WIDTH);
            word_len-=__CB_DISPLAY_WIDTH;
            word+=__CB_DISPLAY_WIDTH;
        }
        if(word_len){
//            printf("\n%.*s", word_len, word);
            printf("\n");
            __CBIO_Visualize(word, word_len);
        }
        __CBIO_data.pos=word_len;
    }
}
void __CBIO_PrintWordSeg(const char *word, i32 seg_len, i32 word_len, i32 init){
    // 1 - WORD (including HYPHENS): PRINT AS USUAL
    // 2 - WHITESPACE: KILL HEADS
    // 4 - INITIAL TOKEN: PRINT AS USUSAL
    if(!word || !(*word) || !word_len || !seg_len)return;
    if(__CBIO_data.pos+word_len<=__CB_DISPLAY_WIDTH){
//        printf("%.*s", (int)seg_len, word);
        __CBIO_Visualize(word, seg_len);
        __CBIO_data.pos+=seg_len;
    }else if(__CBIO_IsWhitespace(*word) && !init){
        printf("\n");
        __CBIO_data.pos=0;
    }else if(word_len<=__CB_DISPLAY_WIDTH){
//        printf("\n%.*s", (int)seg_len, word);
        printf("\n");
        __CBIO_Visualize(word, seg_len);
        __CBIO_data.pos=seg_len;
    }else{
        if(__CB_DISPLAY_WIDTH>__CBIO_data.pos){
//            printf("%.*s", (int)(__CB_DISPLAY_WIDTH-__CBIO_data.pos), word);
            __CBIO_Visualize(word, __CB_DISPLAY_WIDTH-__CBIO_data.pos);
            seg_len-=__CB_DISPLAY_WIDTH-__CBIO_data.pos;
            word+=__CB_DISPLAY_WIDTH-__CBIO_data.pos;
        }
        while(seg_len>=__CB_DISPLAY_WIDTH){
//            printf("\n%.*s", (int)__CB_DISPLAY_WIDTH, word);
            printf("\n");
            __CBIO_Visualize(word, __CB_DISPLAY_WIDTH);
            seg_len-=__CB_DISPLAY_WIDTH;
            word+=__CB_DISPLAY_WIDTH;
        }
        if(seg_len){
//            printf("\n%.*s", seg_len, word);
            __CBIO_Visualize(word, seg_len);
        }
        __CBIO_data.pos=seg_len;
    }
}
void __CBIO_CommitWordSeg(const char *word, i32 seg_len, i32 init){
    if(__CBIO_data.seg.size==__CBIO_MAX_WORD_SEGS)return;
    __CBIO_data.seg.segs[__CBIO_data.seg.size].word=word;
    __CBIO_data.seg.segs[__CBIO_data.seg.size].len=seg_len;
    __CBIO_data.seg.segs[__CBIO_data.seg.size].init=init;
    __CBIO_data.seg.segs[__CBIO_data.seg.size].tint=0;
    __CBIO_data.seg.size++;
    __CBIO_data.seg.len+=seg_len;
}
void __CBIO_PrintAllWordSegs(){
    for(int i=0; i<__CBIO_data.seg.size; i++){
        __CBIO_PrintWordSeg(
            __CBIO_data.seg.segs[i].word,
            __CBIO_data.seg.segs[i].len,
            __CBIO_data.seg.len,
            __CBIO_data.seg.segs[i].init
        );
        __CBIO_data.seg.len-=__CBIO_data.seg.segs[i].len;
        if(__CBIO_data.seg.segs[i].tint)Curses.setColor(__CBIO_data.seg.segs[i].color);
    }
    __CBIO_data.seg.size=0;
}

void __CBIO_Printf(const char *format, ...){
    __CBIO_data.prevcolor=Default;
    char *dest=Mem.calloc(4096, sizeof(char));
    va_list args;
    va_start(args, format);
    vsprintf(dest, format, args);
    va_end(args);
    char *dend=dest, *dstart=dest;
    // 1 - WORD (including HYPHENS): PRINT AS USUAL
    // 2 - WHITESPACE: KILL TAILS
    // 4 - INITIAL TOKEN: PRINT AS USUSAL
    i32 init=1, color_digit=0, color=Default;
    for(; *dend; dend++){
        if(color_digit && !__CBIO_data.color_off){
            color_digit--;
            if(!color_digit){
                if(__CBIO_data.seg.size){
                    __CBIO_data.seg.segs[__CBIO_data.seg.size-1].tint=1;
                    __CBIO_data.seg.segs[__CBIO_data.seg.size-1].color=color;
                }else{
                    Curses.setColor(color);
                }
                dstart=dend;
                color_digit=__CBIO_IsColorIndicator(dest, dend, &color);
            }
        }
        if(!color_digit || __CBIO_data.color_off){
            if(*dend=='\n'){
                __CBIO_PrintWord(dstart, dend-dstart, init);
                printf("\n");
                __CBIO_data.pos=0; // A new line has already been started
                dstart=dend+1; // The extra '\n' is the added 1
                init=1;
            }else if(*dend=='\\' && !__CBIO_data.color_off){ // "\{i}": directly print "{i}"
                if(*(dend+1)=='{'){
                    __CBIO_PrintWord(dstart, dend-dstart, init);
                    dstart=dend+1; // The extra '\\' is the added 1
                }
            }else{
                i32 divide=*dend=='-' && *(dend+1)!='-';
                divide|=__CBIO_IsWhitespace(*dend)^__CBIO_IsWhitespace(*dstart);
                if(divide){
                    __CBIO_CommitWordSeg(dstart, dend-dstart, init);
                    __CBIO_PrintAllWordSegs();
//                    __CBIO_PrintWord(dstart, dend-dstart, init);
                    dstart=dend;
                    init=0;
                }
                if(!__CBIO_data.color_off){
                    color_digit=__CBIO_IsColorIndicator(dest, dend, &color);
//                divide|=color_digit;
                    if(!divide && color_digit){
                        __CBIO_CommitWordSeg(dstart, dend-dstart, init);
                        dstart=dend;
                        init=0;
                    }
                }
            }
        }
    }
    if(*dstart){
        if(__CBIO_data.color_off){
            __CBIO_PrintWord(dstart, dend-dstart, init);
        }else{
            color_digit=__CBIO_IsColorIndicator(dest, dstart, &color);
            if(color_digit){
                Curses.setColor(color);
                dstart=dend;
            }else{
                __CBIO_PrintWord(dstart, dend-dstart, init);
            }
        }
    }
    Mem.free(dest);
    fflush(stdout);
}

void __CBIO_Visualize(const char *word, i32 word_len){
    __CBIO_EntropyDisplay(0, word, word_len);
}
void __CBIO_EntropyDisplay(i32 ent, const char *word, i32 word_len){
    if(!ent){
        printf("%.*s", (int)word_len, word);
        return;
    }
    i32 cap=10000, lim=ent, lim2=ent*ent/cap, color=Curses.getColor();
    for(i32 i=0; i<word_len; i++){
        i32 rnum=RNG.get32(&__CBIO_data.io_rand32)%cap;
        if(rnum<lim){
            if(rnum<lim2){
                rnum=RNG.get32(&__CBIO_data.io_rand32)%cap;
                if(rnum<lim2){
                    i32 colors[]={Red|Bright, Blue|Bright, Green|Bright, Yellow|Bright,
                                White|Bright, Cyan|Bright, Magenta|Bright, Default};
                    color=colors[RNG.get32(&__CBIO_data.io_rand32)%8];
                }
                rnum=RNG.get32(&__CBIO_data.io_rand32)%3;
                if(rnum==0)continue;
                else{
                    if(color!=Curses.getColor())Curses.setColor(color);
                    if(rnum==1){
                        rnum=RNG.get32(&__CBIO_data.io_rand32)%52;
                        if(rnum<26)printf("%c", 'A'+rnum);
                        else printf("%c", 'a'-26+rnum);
                        rnum=RNG.get32(&__CBIO_data.io_rand32)%52;
                        if(rnum<26)printf("%c", 'A'+rnum);
                        else printf("%c", 'a'-26+rnum);
                    }else printf("#");
                }
            }else{
                if(color!=Curses.getColor())Curses.setColor(color);
                rnum=RNG.get32(&__CBIO_data.io_rand32)%52;
                if(rnum<26)printf("%c", 'A'+rnum);
                else printf("%c", 'a'-26+rnum);
            }
        }else{
            if(color!=Curses.getColor())Curses.setColor(color);
            printf("%c", word[i]);
        }
    }
}

#endif
