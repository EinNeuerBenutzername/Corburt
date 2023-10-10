#ifndef Corburt_Base_h_Include_Guard
#define Corburt_Base_h_Include_Guard
#define DISPLAY_WIDTH 64 // don't change plz
#define TOKEN_MAXLEN 256
#define CB_VERSIONNUM 330
#define CB_VERSIONCHECK 0
#define CB_VERSIONTEXT "v0.3.4"
//#define CB_MAXPOINTERS 32767
#define CB_MAXPOINTERS 4096 // used: about 500 as of 0.3.2
//#define CB_MAXROOMDESC 2048
#ifndef Corburt_Pointer_Trace_Level
    #define Corburt_Pointer_Trace_Level 0 // off
#endif
#ifdef __STDC_VERSION__
    #if __STDC_VERSION__<199901L
        #error Please use a C99 compiler.
    #endif
#endif
#include "msg.h"
#include "mtwister.h"
#include "cbcurses.h"
#include "cbsys.h"
#include <limits.h>
#include <time.h>
#include <stdarg.h>
#include <stdlib.h> //malloc() realloc() free() exit()
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>

// Typedefs
typedef int_fast32_t nat; // 32-bit number
typedef int_fast64_t bat; // 64-bit integer
//typedef int nat;
//typedef long long bat;
//typedef __int64 bat;
typedef double real;

MTRand mtrand;
bool quit_game=false;
bool isle=true; // platform endianess, this is not a flag.

enum ranks {
    rank_golem,
    rank_kin,
    rank_regular,
    rank_lunfading,
    rank_unfading,
    rank_knight,
    rank_highkin,
    rank_demigod,
    rank_king,
    rank_sage,
    rank_god,
    rank_truesage,
    rank_carnageking,
    rank_supreme
};
struct input{
    nat deletable;
    char *line;
}input;
struct player{
    char name[32];
    nat spawn;
    nat rnk;
    nat lvl;
    bat exp;
    bat maxhp;
    bat hp;
    bat maxfp;
    bat fp;
    bat maxst;
    bat st;
    bat maxmp;
    bat mp;
    bat maxpp;
    bat pp;
    struct basestats{
        nat agi; // agility
        nat con; // constitution
        nat res; // responsiveness
        nat str; // strength
        nat wil; // willpower
        nat wis; // wisdom
        nat luck; //luck
        nat pts; // available points
    } stats;
    struct booststats{
        nat agi;
            nat acc;
            nat dod;
        nat con;
            nat def;
            nat vit;
        nat res;
            nat rfl;
            nat foc;
        nat str;
            nat atk;
            nat stm;
        nat wil;
            nat san;
            nat sat;
        nat wis;
            nat mag;
            nat mat;
        nat luck;
    } bstats;
    struct {
        bool hasMP;
        bool hasPP;
    } info;
    nat roomid;
    nat loi; // lines of input
} player={"", 1, rank_regular, 1, 0, 10, 10,
    10, 10, 10, 10, 0, 0, 0, 0,
    {0, 0, 0, 0, 0, 0, 0, 14}, {0},
    {false, false},
    1, 0
};
struct inventory{
    nat unlocked;
    nat items[64];
    nat accessories[5];
    nat weapon;
    nat armor;
    bat money;
} inventory={16, {0}, {0}, 0, 0, 0};
struct save{
    nat valid;
    struct player plr;
    struct inventory inv;
};
struct { // palette
    int input; // $G<
    int msg; // $Gm regular message
    int load; // %Gl
    int inform; // $Gi
    int prompt; // $Gp
    int promptfail; // $Gf
    int success; // $Gs
    int debug; // $d, $Gd
    int warning; // $w, $Gw
    int command; // $c, $Wc
    struct { // Splash
        int welcome;
        int logoup;
        int logodown;
        int version;
    } splash;
    struct { // Room
        int hint;
        int desc;
        int exit;
        int change;
    } room;
    struct { // Item
        int hint;
        int interact;
        int gone;
    } item;
    struct { // Enemy
        int hint;
        int strike;
        int die;
        int miss;
        int blocked;
        int reward;
        int spawn;
    } enemy;
    struct { // Value
        // used in: attack damage
        int plain;
        int crit;
        int supercrit;
        // used in: resources
        int high;
        int mid;
        int low;
    } value;
    struct { // Chat
        int player;
        int text;
    } chat;
    struct { // res Points
        int hp;
        int fp;
        int st;
        int mp;
        int pp;
    } res;
    struct { // player @
        int ready; // $@r
        int miss; // $@m
        int strike; // $@a
        int blocked; // $@b
        int stats; // $@s
    } player;
    int threat[5]; // Threat $T0~$T4
    // when editing palette, please also edit initpalette()
} palette;
const nat savescount=3;
struct save saves[3]={0};
int_fast32_t cursaveid=0;
char *inputbuf;
struct globaldata{
    void **pointerpool;
    nat pointerinuse;
    nat dbpointer;
    nat pointerreserve;
    nat curtick;
    bat curround;
}global={NULL, 0, 0, 100, 0, 0};
//basic
enum errorenum{
    error_cannotmalloc,
    error_cannotrealloc,
    error_badcharbit,
    error_bufferpooloverflow,
    error_cannotsave,
};
void printc(int color, const char *format, ...); // obsolete, please use printr()
size_t wcwidth(const int wc); // no more wchar, so obsolete
void charstate(char ch, int *state, int *arg, int color, int *tint, size_t *width);
size_t strwidth(const char *str);
int strcounthighlights(const char *str);
void printword(const char *word);
void printwordpref(int color, size_t prefw, int prefh, const char *pref, const char *word);
void printr_1(int color, const char *format, ...); // for backup reasons. please use printr()
void printr(int color, const char *format, ...);
void printrp_1(int color, const char *linepref, const char *format, ...); // for backup reasons.. please use printrp()
void printrp(int color, const char *linepref, const char *format, ...);
void tracelog(const char *format, ...);
void warn(const char *format, ...);
void fatalerror(enum errorenum error_id);
void *mallocpointer(size_t bytes);
void *reallocpointer(void *pointer, size_t bytes);
void freepointer(void *pointer);
void freeall();
void scanline(char *scan_str, int scans);
void strlower(char **target_str_pos);
void printc(int color, const char *format, ...){
    cbc_setcolor(color);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}
size_t wcwidth(const int wc){ // no more wchar, so obsolete
    if((wc>=11904 && wc<=55215) || (wc>=63744 && wc<=64255) || (wc>=65281 && wc<=65374)){ // ambiguous E.Asian wide characters
        return 2;
    }
    return 1;
}
void charstate(char ch, int *state, int *arg, int color, int *tint, size_t *width){
    // states
    // 0  - regular character
    // 1  - valid indicator '$'
    // 2  - color indicator
    // 3  - complex color indicator
    // 4  - long color indicator (not yet implemented)
    if(*state==2)*state=0;
    if(ch=='\n'){
        *state=0;
        return;
    }
    *width=*width+1;
    if(ch==' '){
        *state=0;
        return;
    }
    if(ch=='$' && *state==0){
        *state=1;
    }
    else if(*state==1){
        if((ch<='Z' && ch>='A') || (ch<='z' && ch>='a') || ch=='@'){
            *state=2;
            switch(ch){
            case 'o': // $o original color
                *tint=color;
                break;
            case 'd': // $d, $Gd debug
                *tint=palette.debug;
                break;
            case 'w': // $w, $Gw warning
                *tint=palette.warning;
                break;
            case 'c': // $c, $Gc command
                *tint=palette.command;
                break;
            default:
                *state=3;*arg=ch;return;
            }
            *width=*width-2;
        }else{
            *state=0;
        }
    }
    else if(*state==3){
        if(1){
            *state=4;
            switch(*arg){
                case 'G':
                    switch(ch){
                    case '<': // $G< input
                        *tint=palette.input;
                        break;
                    case 'm': // $Gm msg
                        *tint=palette.msg;
                        break;
                    case 'l': // $Gl load
                        *tint=palette.load;
                        break;
                    case 'i': // $Gi inform
                        *tint=palette.inform;
                        break;
                    case 'p': // $Gp prompt
                        *tint=palette.prompt;
                        break;
                    case 'f': // $Gf promptfail
                        *tint=palette.promptfail;
                        break;
                    case 's': // $Gs success
                        *tint=palette.success;
                        break;
                    case 'd': // $d, $Gd debug
                        *tint=palette.debug;
                        break;
                    case 'w': // $w, $Gw warning
                        *tint=palette.warning;
                        break;
                    case 'c': // $c, $Gc command
                        *tint=palette.command;
                        break;
                    default:*state=0;return;
                    }
                    break;
                case 'T':
                    switch(ch){
                    case '0': // $T0
                        *tint=palette.threat[0];
                        break;
                    case '1': // $T1
                        *tint=palette.threat[1];
                        break;
                    case '2': // $T2
                        *tint=palette.threat[2];
                        break;
                    case '3': // $T3
                        *tint=palette.threat[3];
                        break;
                    case '4': // $T4
                        *tint=palette.threat[4];
                        break;
                    default:*state=0;return;
                    }
                    break;
                case 'P':
                    switch(ch){
                    case 'h': // $Ph
                        *tint=palette.res.hp;
                        break;
                    case 'f': // $Pf
                        *tint=palette.res.fp;
                        break;
                    case 's': // $Ps
                        *tint=palette.res.st;
                        break;
                    case 'm': // $Pm
                        *tint=palette.res.mp;
                        break;
                    case 'p': // $Pp
                        *tint=palette.res.pp;
                        break;
                    }
                    break;
                case '@':
                    switch(ch){
                    case 'r':
                        *tint=palette.player.ready;
                        break;
                    case 'm':
                        *tint=palette.player.miss;
                        break;
                    case 'a':
                        *tint=palette.player.strike;
                        break;
                    case 'b':
                        *tint=palette.player.blocked;
                        break;
                    case 's':
                        *tint=palette.player.stats;
                        break;
                    }
                    break;
                default:*state=0;return;
                }
            *width=*width-3;
        }else{
            *state=0;
        }
    }else{
        *state=0;
    }
}
size_t strwidth(const char *str){
    size_t len=0;
    int state=0, tint=0, arg=0;
    for(size_t i=0; i<strlen(str); i++){
        charstate(str[i], &state, &arg, 0, &tint, &len);
    }
    return len;
}
int strcounthighlights(const char *str){
    int hil=0;
    size_t len=0;
    int state=0, tint=0, arg=0;
    for(size_t i=0; i<strlen(str); i++){
        charstate(str[i], &state, &arg, 0, &tint, &len);
        if(state==2)hil++;
    }
    return hil;
}
    char *printr_dest=NULL;
    char *printr_token=NULL;
    size_t pos=0;
void printword(const char *word){
    size_t wordlen=strlen(word);
    if(wordlen==0)return;
    size_t strw=strwidth(word);
    if(strw+pos<DISPLAY_WIDTH){
        printf("%s", word);
        pos+=strw;
        if(word[wordlen-1]=='\n')pos=0;
    }else if(strw<DISPLAY_WIDTH){
        printf("\n%s", word);
        pos=strw;
        if(word[wordlen-1]=='\n')pos=0;
    }else{
        char printword_token[TOKEN_MAXLEN];
        memset(printword_token, 0, TOKEN_MAXLEN);
        int len=0;
        for(size_t i=0; i<strlen(word); i++){
            printword_token[len]=word[i];
            len++;
            if(len+pos>=DISPLAY_WIDTH){
                printf("%s\n", printword_token);
                memset(printword_token, 0, TOKEN_MAXLEN);
                len=0;
            }
        }
        printf("%s", printword_token);
        pos=len;
        if(word[wordlen-1]=='\n')pos=0;
    }
}
void printwordpref(int color, size_t prefw, int prefh, const char *pref, const char *word){
    size_t wordlen=strlen(word);
    if(wordlen==0)return;
//    printf("[%d]", strwidth(word));
    size_t strw=strwidth(word);
    int wordcolor;
    wordcolor=cbc_getcolor();
    if(strw+pos<DISPLAY_WIDTH){
        printf("%s", word);
        pos+=strw;
        if(word[wordlen-1]=='\n')pos=0;
    }else if(strw+prefw<DISPLAY_WIDTH){
//        if(prefh==0){
            cbc_setcolor(color);
            printf("\n%s", pref);
//        }
        cbc_setcolor(wordcolor);
        printf("%s", word);
        pos=strw+prefw;
        if(word[wordlen-1]=='\n')pos=0;
    }else{
        char printword_token[TOKEN_MAXLEN];
        memset(printword_token, 0, TOKEN_MAXLEN);
        int len=0;
        for(size_t i=0; i<strlen(word); i++){
            printword_token[len]=word[i];
            len++;
            if(len+pos+prefw>=DISPLAY_WIDTH){
                {
                    printf("%s\n", printword_token);
//                    if(prefh==0){
                        cbc_setcolor(color);
                        printf("\n%s", pref);
//                    }
                    cbc_setcolor(wordcolor);
                }
                memset(printword_token, 0, TOKEN_MAXLEN);
                len=0;
            }
        }
        cbc_setcolor(wordcolor);
        printf("%s", printword_token);
        pos=len+prefw;
        if(word[wordlen-1]=='\n')pos=0;
    }
}
void printr_1(int color, const char *format, ...){
    cbc_setcolor(color);
    memset(printr_dest, 0, 4096);
    memset(printr_token, 0, DISPLAY_WIDTH);
    va_list args;
    va_start(args, format);
    vsnprintf(printr_dest, 4096, format, args);
    va_end(args);

    size_t strl=0, strw=0, strld=strlen(printr_dest);
    for(size_t i=0; i<strld; i++){
        if(printr_dest[i]=='\n'){
            if(strl>0)printf("%s\n", printr_token);
            else putc('\n', stdout);
            pos=0;memset(printr_token, 0, strl);
            strl=0;strw=0;
        }
        else if(printr_dest[i]==' '){
            if(strl>0)printf("%s ", printr_token);
            else putc(' ', stdout);
            pos+=strl+1;memset(printr_token, 0, strl);
            strl=0;strw=0;
        }
        else{
            if(strw+pos>=DISPLAY_WIDTH-1){
                size_t j;
                for(j=i; j<strlen(printr_dest); j++){
                    if(printr_dest[j]=='\n' || printr_dest[j]==' ')break;
                }
                if(j-i+1<DISPLAY_WIDTH){
                    printf("\n%s", printr_token);
                    pos=strw;memset(printr_token, 0, strl);
                    strl=0;strw=0;
                }else{
                    printf("%s\n", printr_token);
                    pos=0;memset(printr_token, 0, strl);
                    strl=0;strw=0;
                }
            }
            printr_token[strl]=printr_dest[i];
            strl++;
            strw++;
            if(i+1==strld){
                printf("%s", printr_token);
                pos+=strw;memset(printr_token, 0, strl);
                strl=0;strw=0;
            }
        }
    }
    fflush(stdout);
}
void printr(int color, const char *format, ...){
    cbc_setcolor(color);
    memset(printr_dest, 0, 4096);
    memset(printr_token, 0, TOKEN_MAXLEN);
    va_list args;
    va_start(args, format);
    vsnprintf(printr_dest, 4096, format, args);
    va_end(args);

    size_t strl=0, strw=0, strld=strlen(printr_dest);
    int state=0, tint=cbc_getcolor(), arg=0;
    for(size_t i=0; i<strld; i++){
        char ch=printr_dest[i];
        charstate(ch, &state, &arg, color, &tint, &strw);
        printr_token[strl]=ch;
        strl++;
        if(state==0){
            if(ch==' ' || ch=='\n'){
                if(printr_dest[0]!=ch){
                    printword(printr_token);
                    memset(printr_token, 0, TOKEN_MAXLEN);
                    strl=0;
                }else if(i<strld-1){
                    char ch_1=printr_dest[i+1];
//                    if(ch_1!=ch || printr_dest[0]!=ch){
                    if(ch_1!=ch){
                        printword(printr_token);
                        memset(printr_token, 0, TOKEN_MAXLEN);
                        strl=0;
                    }
                }
            }
        }
        else if(state==2){
            if(strl>2){
                printr_token[strl-1]=0;
                printr_token[strl-2]=0;
                printword(printr_token);
            }
            memset(printr_token, 0, TOKEN_MAXLEN);
            strl=0;
            cbc_setcolor(tint);
        }
        else if(state==4){
            if(strl>3){
                printr_token[strl-1]=0;
                printr_token[strl-2]=0;
                printr_token[strl-3]=0;
                printword(printr_token);
            }
            memset(printr_token, 0, TOKEN_MAXLEN);
            strl=0;
            cbc_setcolor(tint);
        }
    }
    printword(printr_token);
    memset(printr_token, 0, TOKEN_MAXLEN);
    fflush(stdout);
}
void printrp_1(int color, const char *linepref, const char *format, ...){
    // print with a starting prefix "linepref" before EVERY line FOLLOWING the first
    if(color!=cbc_getcolor())cbc_setcolor(color);
    fflush(stdout);
    memset(printr_dest, 0, 4096);
    memset(printr_token, 0, TOKEN_MAXLEN);
    va_list args;
    va_start(args, format);
    vsnprintf(printr_dest, 4096, format, args);
    va_end(args);

    size_t strl=0, strw=0, strld=strlen(printr_dest), strwp=strwidth(linepref);
    for(size_t i=0; i<strld; i++){
        if(printr_dest[i]=='\n'){
            if(strl>0)printf("%s\n", printr_token);
            else putc('\n', stdout);
            if(i<strld-1){
                printf("%s", linepref);
                pos=strwp;
            }else pos=0;
            memset(printr_token, 0, strl);
            strl=0;strw=0;
        }
        else if(printr_dest[i]==' '){
            if(strl>0)printf("%s ", printr_token);
            else putc(' ', stdout);
            pos+=strl+1;memset(printr_token, 0, strl);
            strl=0;strw=0;
        }
        else{
            if(strw+pos>=DISPLAY_WIDTH-1){
                size_t j;
                for(j=i; j<strlen(printr_dest); j++){
                    if(printr_dest[j]=='\n' || printr_dest[j]==' ')break;
                }
                if(j-i+1<DISPLAY_WIDTH-strwp){
                    printf("\n%s%s", linepref, printr_token);
                    pos=strw+strwp;memset(printr_token, 0, strl);
                    strl=0;strw=0;
                }else{
                    printf("%s\n%s", printr_token, linepref);
                    pos=strwp;memset(printr_token, 0, strl);
                    strl=0;strw=0;
                }
            }
            printr_token[strl]=printr_dest[i];
            strl++;
            strw++;
            if(i+1==strld){
                pos=0;
                if(strl<strld){
                    printf("%s", linepref);
                    pos+=strwp;
                }
                printf("%s", printr_token);
                pos+=strw;memset(printr_token, 0, strl);
                strl=0;strw=0;
            }
        }
    }
    fflush(stdout);
}
void printrp(int color, const char *linepref, const char *format, ...){
    // print with a starting prefix "linepref" before EVERY line FOLLOWING the first
    // note that line prefixes CANNOT have color indicators in them. I tried, and the program aborts with fatal error afterwards.
    cbc_setcolor(color);
    memset(printr_dest, 0, 4096);
    memset(printr_token, 0, TOKEN_MAXLEN);
    va_list args;
    va_start(args, format);
    vsnprintf(printr_dest, 4096, format, args);
    va_end(args);

    size_t strl=0, strw=0, strld=strlen(printr_dest), prefw=strlen(linepref);
    int state=0, tint=cbc_getcolor(), arg=0, prefh=strcounthighlights(linepref);
    for(size_t i=0; i<strld; i++){
        char ch=printr_dest[i];
        charstate(ch, &state, &arg, color, &tint, &strw);
        printr_token[strl]=ch;
        strl++;
        if(state==0){
            if(ch==' ' || ch=='\n'){
                if(i<strld-1){
                    char ch_1=printr_dest[i+1];
                    if(ch_1!=ch){
                    printwordpref(color, prefw, prefh, linepref, printr_token);
                        memset(printr_token, 0, TOKEN_MAXLEN);
                        strl=0;
                    }
                }
            }
        }
        else if(state==2){
            if(strl>2){
                printr_token[strl-1]=0;
                printr_token[strl-2]=0;
                printwordpref(color, prefw, prefh, linepref, printr_token);
            }
            memset(printr_token, 0, TOKEN_MAXLEN);
            strl=0;
            cbc_setcolor(tint);
        }
        else if(state==4){
            if(strl>3){
                printr_token[strl-1]=0;
                printr_token[strl-2]=0;
                printr_token[strl-3]=0;
                printwordpref(color, prefw, prefh, linepref, printr_token);
            }
            memset(printr_token, 0, TOKEN_MAXLEN);
            strl=0;
            cbc_setcolor(tint);
        }
    }
    printwordpref(color, prefw, prefh, linepref, printr_token);
    memset(printr_token, 0, TOKEN_MAXLEN);
    fflush(stdout);
}
void tracelog(const char *format, ...){
#ifdef Corburt_Debug
    cbc_setcolor(palette.debug);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
#else
    return;
#endif
}
void warn(const char *format, ...){
    cbc_setcolor(palette.warning);
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    fflush(stdout);
}
void fatalerror(enum errorenum error_id){
    const char *m;
    switch(error_id){
    case error_cannotmalloc:
        m=msg->error_cannotmalloc;break;
    case error_cannotrealloc:
        m=msg->error_cannotrealloc;break;
    case error_badcharbit:
        m=msg->error_badcharbit;break;
    case error_bufferpooloverflow:
        m=msg->error_bufferpooloverflow;break;
    case error_cannotsave:
        m=msg->error_cannotsave;break;
    default:
        m=msg->error_unknown;break;
    }
    printr(palette.warning, m);
    FILE *errorlog=fopen("err.log", "a");
    fprintf(errorlog, "%s", m);
    fclose(errorlog);
    exit(-1);
}
void *mallocpointer(size_t bytes){
    if(global.pointerinuse>CB_MAXPOINTERS || global.pointerinuse>global.dbpointer+global.pointerreserve){
        fatalerror(error_bufferpooloverflow);
    }
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    global.pointerinuse++;
    if(Corburt_Pointer_Trace_Level>1){
        tracelog(msg->trace_malloced, bytes);
        tracelog(msg->trace_pointerinuse, global.pointerinuse);
    }
    for(nat i=0; i<CB_MAXPOINTERS; i++){
        if(global.pointerpool[i]==NULL){
            global.pointerpool[i]=pointer;
            break;
        }
    }
    return pointer;
}
void *reallocpointer(void *pointer, size_t bytes){
    for(nat i=0, found=0; i<CB_MAXPOINTERS; i++){
        if(global.pointerpool[i]==pointer){
            found=1;
            break;
        }
        if(i==CB_MAXPOINTERS-1 && found==0){
            printr(palette.warning, msg->trace_illegalrealloc);
            return NULL;
        }
    }
    pointer=realloc(pointer, bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    if(Corburt_Pointer_Trace_Level>0){
        tracelog(msg->trace_realloced, bytes);
    }
    return pointer;
}
void freepointer(void *pointer){
    if(pointer==NULL)return;
    for(nat i=0; i<CB_MAXPOINTERS; i++){
        if(global.pointerpool[i]==pointer){
            global.pointerpool[i]=NULL;
            break;
        }
        if(i==CB_MAXPOINTERS-1){
            printr(palette.warning, msg->trace_illegalfree);
            return;
        }
    }
    free(pointer);
    global.pointerinuse--;
    if(Corburt_Pointer_Trace_Level>1){
        tracelog(msg->trace_freed);
        tracelog(msg->trace_pointerinuse, global.pointerinuse);
    }
    pointer=NULL;
}
void freeall(){
    tracelog(msg->trace_pointerinuse, global.pointerinuse);
    for(nat i=0; i<CB_MAXPOINTERS && global.pointerinuse>0; i++){
        if(global.pointerpool[i]!=NULL){
            free(global.pointerpool[i]);
            global.pointerinuse--;
        }
    }
    tracelog(msg->trace_freealled);
}
#ifndef CB_REALTIME
void scanline(char *scan_str, int scans){
    cbc_setcolor(palette.input);
    fflush(stdout);
    fgets(scan_str, scans, stdin);
    if(scan_str[strlen(scan_str)-1]=='\n'){
        scan_str[strlen(scan_str)-1]=0;
    }
    fflush(stdin);
    cbc_setcolor(palette.msg);

    fflush(stdout);
}
#else
void fscanline(char *scan_str, int scans);
#endif
void strlower(char **target_str_pos){
    for(size_t i=0; i<strlen(*target_str_pos); i++){
        if((*target_str_pos)[i]<=90 && (*target_str_pos)[i]>=65){
            (*target_str_pos)[i]+=32;
        }
    }
}

void launchcb();
void endcb();
void assertcheck();
nat match(const char *sub_str, const char *main_str);
void initrng();
void initpalette();
void assertcheck(){
    if(CHAR_BIT!=8)fatalerror(error_badcharbit);
}
nat match(const char *sub_str, const char *main_str){
    if(strlen(main_str)==0)return 0;
    char *str1l=mallocpointer(sizeof(char)*(strlen(main_str)+1));
    char *str2l=mallocpointer(sizeof(char)*(strlen(sub_str)+1));
    strcpy(str1l, main_str);
    strcpy(str2l, sub_str);
    strlower(&str1l);
    strlower(&str2l);
    str1l[strlen(str1l)]=0;
    str2l[strlen(str2l)]=0;
    char *matchpos=strstr(str1l, str2l);
    if(matchpos==NULL){
        freepointer(str1l);
        freepointer(str2l);
        return -1;
    }else{
        if(matchpos==str1l || str1l[(matchpos-str1l)-1]==' '){
            freepointer(str1l);
            freepointer(str2l);
            real m=(10000.0f*strlen(sub_str))/(1.0f*strlen(main_str));
            return (nat)m;
        }else{
            freepointer(str1l);
            freepointer(str2l);
            return -1;
        }
    }
}
void initrng(){
    bat seed;
    tracelog(msg->trace_rnginit);
    tracelog(msg->trace_rngseed, seed=time(NULL));
    mtrand=seedRand(seed);
    tracelog(msg->trace_rngtest, genRandLong(&mtrand));
}
void initpalette(){
    palette.input=Yellow;
    palette.msg=Default;
    palette.load=Cyan;
    palette.inform=Cyan|Bright;
    palette.prompt=Default|Bright;
    palette.promptfail=Default;
    palette.success=Green|Bright;
    palette.debug=Cyan;
    palette.warning=Red;
    palette.command=Yellow|Bright;
    palette.splash.welcome=Green|Bright;
    palette.splash.logoup=Default;
    palette.splash.logodown=Yellow;
    palette.splash.version=Default|Bright;
    palette.room.hint=Default|Bright;
    palette.room.desc=Cyan|Bright;
    palette.room.exit=Green|Bright;
    palette.room.change=Green;
    palette.item.hint=Yellow|Bright;
    palette.item.interact=Cyan|Bright;
    palette.item.gone=Default;
    palette.enemy.hint=Red|Bright;
    palette.enemy.strike=Red|Bright;
    palette.enemy.die=Blue|Bright;
    palette.enemy.miss=Default;
    palette.enemy.blocked=Default;
    palette.enemy.reward=Cyan|Bright;
    palette.enemy.spawn=Red|Bright;
    palette.value.plain=Default;
    palette.value.crit=Yellow|Bright;
    palette.value.supercrit=Red|Bright;
    palette.value.high=Green|Bright;
    palette.value.mid=Yellow|Bright;
    palette.value.low=Red|Bright;
    palette.chat.player=Cyan|Bright;
    palette.chat.text=Default;
    palette.player.ready=Default;
    palette.player.miss=Default;
    palette.player.strike=Green|Bright;
    palette.player.blocked=Green|Bright;
    palette.player.stats=Default|Bright;
    palette.res.hp=Red|Bright;
    palette.res.fp=Cyan|Bright;
    palette.res.st=Green|Bright;
    palette.res.mp=Blue|Bright;
    palette.res.pp=Magenta|Bright;
    palette.threat[0]=Default;
    palette.threat[1]=Green|Bright;
    palette.threat[2]=Red|Bright;
    palette.threat[3]=Yellow|Bright;
    palette.threat[4]=Magenta|Bright;
}

nat dmgreduc(nat dmg, nat def);
bool accreduc(nat acc, nat dod);
nat critdmg(nat critchance, nat strike, nat basemax, nat *color);
nat dmgreduc(nat dmg, nat def){
    if(dmg<1 && dmg+def<1)return 0;
    nat dmg2=dmg;
    {
        real calcdef=def;
        real bdmg=dmg;
        dmg2-=calcdef*calcdef/(calcdef+bdmg);
    }
    if(dmg2<0){
        real hitrate=genRand(&mtrand);
        nat delta=def-dmg2-50;
        real sigmoid=1.0f/(1.0f+pow(2.71828f, delta/20.0f));
        if(hitrate>sigmoid)dmg2=0;
        else dmg2=1;
    }
    return dmg2;
}
bool accreduc(nat acc, nat dod){
    real hitrate=genRand(&mtrand);
    nat delta=dod-acc;
    real sigmoid=1.0f/(1.0f+pow(1.783f, delta/20.0f));
    if(hitrate>sigmoid)return true;
    else return false;
}
nat critdmg(nat critchance, nat strike, nat basemax, nat *color){
    nat critdmg=0, crittier=0;
    for(;critchance>=10000;critchance-=10000)crittier++;
    if(genRandLong(&mtrand)%10000<(unsigned int)critchance)crittier++;
    for(int i=0; i<crittier; i++){
        critdmg+=pow(1.4, i)*(float)basemax;
    }
    critdmg+=(pow(1.3, crittier-1)-1.0f)*(float)(crittier*strike*1.0f);
    if(crittier==0)*color=palette.value.plain;
    else if(crittier==1)*color=palette.value.crit;
    else *color=palette.value.supercrit;
    return critdmg;
}
// cbm
enum direction{
    dir_East, dir_West, dir_North, dir_South, dir_Up, dir_Down
};
// db
#define ENEMY_MAXDROPS 16
typedef struct enemydb{
    nat id;
    nat type;
    char *name;
    nat lvl;
    bat exp;
    nat abilities[5];
    struct {
        nat type;
        nat combo[20];
        nat skills[6];
    } ai;
    struct {
        nat moneymin;
        nat moneymax;
        nat weapon;
        nat armor;
        struct drops {
            nat itemid;
            nat rate;
        } drops[ENEMY_MAXDROPS];
    } loot;
    struct {
        nat hpmax;
        nat atkcd;
        nat acc;
        nat dod;
        nat def;
        nat vit;
        nat atk;
        nat stm;
        nat san;
        nat sat;
        nat mag;
        nat mat;
    } stats;
} enemydb;

enum db_itemtype{
    db_itemtype_stackable_mask=16,
    db_itemtype_weapon=0,
    db_itemtype_armor=2,
    db_itemtype_accessory=3,
    db_itemtype_key=4,
    db_itemtype_consume=0|db_itemtype_stackable_mask, // stackable
    db_itemtype_collect=1|db_itemtype_stackable_mask, // stackable
    db_itemtype_misc=2|db_itemtype_stackable_mask, // stackable
    db_itemtype_ammo=3|db_itemtype_stackable_mask, // stackable
};
typedef struct itemdb{
    nat id;
    nat type;
    nat price;
    nat prep;
    nat cd;
    nat crit;
    char *name;
    char *desc;
    struct {
        nat min_;
        nat max_;
        nat regen;
        nat agi;
            nat acc;
            nat dod;
        nat con;
            nat def;
            nat vit;
        nat res;
            nat rfl;
            nat foc;
        nat str;
            nat atk;
            nat stm;
        nat wil;
            nat san;
            nat sat;
        nat wis;
            nat mag;
            nat mat;
        nat luck;
    } stats;
} itemdb;
itemdb *db_ifindwithid(nat itemid);
void getitemname(nat id, char *itemname);
void consumeitem(nat itemid);

enum db_roomtype{
    db_roomtype_plain,
    db_roomtype_birth,
    db_roomtype_store,
    db_roomtype_shop=db_roomtype_store,
    db_roomtype_train,
    db_roomtype_gate
};
enum db_roomregion{
    db_roomregion_nlcity, // nameless city
    db_roomregion_forest, // forests of wrath
};
typedef struct roomdb{
    nat id;
    nat x;
    nat y;
    nat region;
    char *name;
#ifdef CB_MAXROOMDESC
    char desc[CB_MAXROOMDESC];
#else
    char *desc;
#endif
    nat type;
    nat exits[6];
    nat table[32];
    nat buff[4];
} roomdb;

enum db_intertype {
    db_intertype_door,
    db_intertype_switch,
    db_intertype_chest,
    db_intertype_trap,
    db_intertype_tp,
    db_intertype_npc,
    db_intertype_hazard
};
typedef struct interdb {
    nat id;
    nat initroom;
    nat intertype;
    void *interdata;
} interdb;
struct intdat_door {
    struct intdat_door_open_requisites {
        struct keyset {
            nat keyid1;
            nat keyid2;
            nat keyid3;
            nat keyid4;
            nat keyid5;
        } keyset;
        struct password {
            char *hint;
            char *keyword;
        } password;
        nat payamount;
    } open;
    struct intdat_door_open_requisites unlock;
};
struct intdat_switch {
    nat doorid;
};
struct intdat_chest {
    nat capacity;
    char *name;
    nat initgold;
    nat inititems[16];
};
struct intdat_trap {
    nat placeholder;
}; // no idea how to make it work
struct intdat_tp {
    nat dest;
};
struct intdat_npc {
    char *name;
    nat dialogcount;
    struct intdat_npc_dialog {
        char *keyword;
        char *response;
    } *dialog;
};
struct intdat_hazard {
    char *name;
    nat debuff[4];
};

#ifndef DBFIO_DATA_EXPORT
nat itemdbsize=0;
itemdb *itemdbs=NULL;
nat enemydbsize=0;
enemydb *enemydbs=NULL;
nat roomdbsize=0;
roomdb *roomdbs=NULL;
nat interdbsize=0;
interdb *interdbs=NULL;
#endif
// cbp
struct {
    struct calcstats{
        nat agi;
            nat acc;
            nat dod;
        nat con;
            nat def;
            nat vit;
        nat res;
            nat rfl;
            nat foc;
        nat str;
            nat atk;
            nat stm;
        nat wil;
            nat san;
            nat sat;
        nat wis;
            nat mag;
            nat mat;
        nat luck;
        nat regen;
        nat min_;
        nat max_;
        nat prep;
        nat cd;
        nat crit;
    } calcstats;
    bool playerdead;
    bool editstats;
    bool readying;
    bool isready;
    int ynprompt; // 1: switch region
    int promptarg;
    nat swinging;
    nat targetid;
    nat readyframe;
    nat attackcd;
} cbp={0};
void paddexp(nat add);
void phpchange(nat num);
void pdie();
void pcalcstats();
void pshowinfo();
void pshowcharacter();
void pshowstats();
void pshowresources();
void pshowabl();
void pshowinv();
void pshowexp();
void pteleport(nat roomid);
void pmove(enum direction dir);
void pmovedirect(enum direction dir);
void pready();
void preadying();
void pattack(nat entityid);
void ptrain();
void peditstats();
void peditstatsend();
void pregen();
void ptakedmg(nat dmg);
bool pcandodge(enemydb *edb);
#endif
