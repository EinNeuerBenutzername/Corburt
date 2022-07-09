#ifndef Corburt_Base_h_Include_Guard
#define Corburt_Base_h_Include_Guard
#define DISPLAY_WIDTH 68
#define CB_VERSIONNUM 310
#define CB_VERSIONCHECK 0
#define CB_VERSIONTEXT L"v0.3.1"
//#define CB_MAXPOINTERS 32767
#define CB_MAXPOINTERS 4096 // used: 500~600
//#define CB_MAXROOMDESC 2048
#ifndef Corburt_Pointer_Trace_Level
    #define Corburt_Pointer_Trace_Level 0 // off
#endif
#if __STDC_VERSION__<199901L
    #error Please use a C99 compiler.
#endif
#include "msg.h"
#include "mtwister.h"
#include "cbcurses.h"
#include "cbsys.h"
#include <limits.h>
#include <time.h>
#include <wchar.h>
#include <stdarg.h>
#include <stdlib.h> //malloc() realloc() free() exit()
#include <stdbool.h>
#include <inttypes.h>
#include <math.h>

typedef bool foo;
typedef int_fast32_t nat;//32-bit number
typedef int_fast64_t bat;//64-bit integer
//typedef unsigned __int64 bat;
typedef double real;
MTRand mtrand;
foo quit_game=false;
foo isle=true; //platform endianess. this is not a flag.
struct input{
    nat deletable;
    wchar_t *line;
}input;
struct player{
    wchar_t name[32];
    nat spawn;
    nat rnk;
    nat lvl;
    bat exp;
    bat maxhp;
    bat hp;
    struct basestats{
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat wis;
        nat act;
        nat con;
        nat pts;
    } stats;
    struct booststats{
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat wis;
        nat act;
        nat con;
        nat pts;
    } bstats;
    nat roomid;
} player={L"",1,1,1,0,10,10,{0,0,0,0,0,0,0,14},{0,0,0,0,0,0,0,0},1};
struct inventory{
    nat unlocked;
    nat items[64];
    nat accessories[5];
    nat weapon;
    nat armor;
    bat money;
} inventory={16,{0},{0},0,0,0};
struct save{
    nat valid;
    struct player plr;
    struct inventory inv;
};
const nat savescount=5;
struct save saves[5]={0};
int_fast32_t cursaveid=0;
wchar_t *inputbuf;
struct globaldata{
    void **pointerpool;
    nat pointerinuse;
    nat dbpointer;
    nat pointerreserve;
    nat curtick;
    bat curround;
    nat curcolor;
}global={NULL,0,0,100,0,0,Default};
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
void freepointer(void *pointer);
void freeall();
void scanline(wchar_t *scan_str,int scans);
void wcslower(wchar_t **target_str_pos);
void printc(int color,const wchar_t *format,...){
    if(color!=global.curcolor)cbc_setcolor(color);
    global.curcolor=color;
//    fflush(stdout);
    va_list args;
    va_start(args,format);
    vwprintf(format,args);
    va_end(args);
//    if(color!=Default)cbc_setcolor(Default);
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
    if(color!=global.curcolor)
        cbc_setcolor(color);
    global.curcolor=color;
    wmemset(printr_dest,0,4096);
    wmemset(printr_token,0,DISPLAY_WIDTH);
    va_list args;
    va_start(args,format);
    vsnwprintf(printr_dest,4096,format,args);
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
//    if(color!=Default)cbc_setcolor(Default);
    fflush(stdout);
}
void printrp(int color,const wchar_t *linepref,const wchar_t *format,...){
    if(color!=global.curcolor)
        cbc_setcolor(color);
    global.curcolor=color;
    fflush(stdout);
    wmemset(printr_dest,0,4096);
    wmemset(printr_token,0,DISPLAY_WIDTH);
    va_list args;
    va_start(args,format);
    vsnwprintf(printr_dest,4096,format,args);
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

//    if(color!=Default)cbc_setcolor(Default);
    fflush(stdout);
}
void tracelog(int color,const wchar_t *format,...){
#ifdef Corburt_Debug
    if(color!=global.curcolor)cbc_setcolor(color);
    global.curcolor=color;
    va_list args;
    va_start(args,format);
    vwprintf(format,args);
    va_end(args);
    fflush(stdout);
#else
    return;
#endif
}
void fatalerror(enum errorenum error_id){
    const wchar_t *m;
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
    printr(Red,m);
    FILE *errorlog=fopen("err.log","a");
    fprintf(errorlog,"%ls",m);
    fclose(errorlog);
    exit(-1);
}
void *mallocpointer_(size_t bytes){
    if(global.pointerinuse>CB_MAXPOINTERS||global.pointerinuse>global.dbpointer+global.pointerreserve){
        fatalerror(error_bufferpooloverflow);
    }
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    global.pointerinuse++;
    if(Corburt_Pointer_Trace_Level>0){
        tracelog(Green,msg->trace_malloced,bytes);
        tracelog(Green,msg->trace_pointerinuse,global.pointerinuse);
    }
    for(nat i=0;i<CB_MAXPOINTERS;i++){
        if(global.pointerpool[i]==NULL){
            global.pointerpool[i]=pointer;
            break;
        }
    }
    return pointer;
}
void *mallocpointer(size_t bytes){
    if(global.pointerinuse>CB_MAXPOINTERS||global.pointerinuse>global.dbpointer+global.pointerreserve){
        fatalerror(error_bufferpooloverflow);
    }
    void *pointer=NULL;
    pointer=malloc(bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    global.pointerinuse++;
    if(Corburt_Pointer_Trace_Level>1){
        tracelog(Green,msg->trace_malloced,bytes);
        tracelog(Green,msg->trace_pointerinuse,global.pointerinuse);
    }
    for(nat i=0;i<CB_MAXPOINTERS;i++){
        if(global.pointerpool[i]==NULL){
            global.pointerpool[i]=pointer;
            break;
        }
    }
    return pointer;
}
void *reallocpointer(void *pointer,size_t bytes){
    for(nat i=0,found=0;i<CB_MAXPOINTERS;i++){
        if(global.pointerpool[i]==pointer){
            found=1;
            break;
        }
        if(i==CB_MAXPOINTERS-1&&found==0){
            printc(Red,msg->trace_illegalrealloc);
            return NULL;
        }
    }
    pointer=realloc(pointer,bytes);
    if(pointer==NULL)fatalerror(error_cannotmalloc);
    if(Corburt_Pointer_Trace_Level>0){
        tracelog(Green,msg->trace_realloced,bytes);
    }
    return pointer;
}
void freepointer(void *pointer){
    if(pointer==NULL)return;
    for(nat i=0;i<CB_MAXPOINTERS;i++){
        if(global.pointerpool[i]==pointer){
            global.pointerpool[i]=NULL;
            break;
        }
        if(i==CB_MAXPOINTERS-1){
            printc(Red,msg->trace_illegalfree);
            return;
        }
    }
    free(pointer);
    global.pointerinuse--;
    if(Corburt_Pointer_Trace_Level>1){
        tracelog(Green,msg->trace_freed);
        tracelog(Green,msg->trace_pointerinuse,global.pointerinuse);
    }
    pointer=NULL;
}
void freeall(){
    tracelog(Green,msg->trace_pointerinuse,global.pointerinuse);
    for(nat i=0;i<CB_MAXPOINTERS&&global.pointerinuse>0;i++){
        if(global.pointerpool[i]!=NULL){
            free(global.pointerpool[i]);
            global.pointerinuse--;
        }
    }
    tracelog(Green,msg->trace_freealled);
}
#ifndef CB_REALTIME
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
#else
void fscanline(wchar_t *scan_str,int scans);
#endif
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
void initrng(){
    bat seed;
    tracelog(Green,msg->trace_rnginit);
    tracelog(Green,msg->trace_rngseed,seed=time(NULL));
    mtrand=seedRand(seed);
    tracelog(Green,msg->trace_rngtest,genRandLong(&mtrand));
}
//misc2
nat dmgreduc(nat dmg,nat def);
bool accreduc(nat acc,nat dod);
nat critdmg(nat critchance,nat strike,nat basemax,nat *color);
nat dmgreduc(nat dmg,nat def){
    if(dmg<1&&dmg+def<1)return 0;
    nat dmg2=dmg;
    {
        real calcdef=def;
        real bdmg=dmg;
        dmg2-=calcdef*calcdef/(calcdef+bdmg);
    }
    if(dmg2<0){
        real hitrate=genRand(&mtrand);
        nat delta=def-dmg2-50;
        real sigmoid=1.0f/(1.0f+pow(2.71828f,delta/20.0f));
        if(hitrate>sigmoid)dmg2=0;
        else dmg2=1;
    }
    return dmg2;
}
bool accreduc(nat acc,nat dod){
    real hitrate=genRand(&mtrand);
    nat delta=dod-acc;
    real sigmoid=1.0f/(1.0f+pow(1.783f,delta/20.0f));
    if(hitrate>sigmoid)return true;
    else return false;
}
nat critdmg(nat critchance,nat strike,nat basemax,nat *color){
    int critdmg=0,crittier=0;
    for(;critchance>=10000;critchance-=10000)crittier++;
    if(genRandLong(&mtrand)%10000<critchance)crittier++;
    for(int i=0;i<crittier;i++){
        critdmg+=pow(1.4,i)*(float)basemax;
    }
    critdmg+=(pow(1.3,crittier-1)-1.0f)*(float)(crittier*strike*1.0f);
    if(crittier==0)*color=Default;
    else if(crittier==1)*color=Yellow|Bright;
    else *color=Red|Bright;
    return critdmg;
}
// cbm
enum direction{
    dir_East,dir_West,dir_North,dir_South,dir_Up,dir_Down
};
// db
#define ENEMY_MAXDROPS 16
enum db_enemytype {
    db_enemytype_plain,
    db_enemytype_sentinel,
    db_enemytype_assassin,
    db_enemytype_boss
};
typedef struct enemydb{
    nat id;
    nat type;
    wchar_t *name;
//    wchar_t *desc;
    bat exp;
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
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat wis;
        nat act;
        nat con;
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
};
typedef struct itemdb{
    nat id;
    nat type;
    nat price;
    nat prep;
    nat cd;
    nat crit;
    wchar_t *name;
    wchar_t *desc;
    struct {
        nat min_;
        nat max_;
        nat regen;
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat wis;
        nat act;
        nat con;
        nat pts;
    } stats;
} itemdb;
itemdb *db_ifindwithid(nat itemid);
void getitemname(nat id,wchar_t *itemname);
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
    wchar_t *name;
#ifdef CB_MAXROOMDESC
    wchar_t desc[CB_MAXROOMDESC];
#else
    wchar_t *desc;
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
            wchar_t *hint;
            wchar_t *keyword;
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
    wchar_t *name;
    nat initgold;
    nat inititems[16];
};
struct intdat_trap {};
struct intdat_tp {
    nat dest;
};
struct intdat_npc {
    wchar_t *name;
    nat dialogcount;
    struct intdat_npc_dialog {
        wchar_t *keyword;
        wchar_t *response;
    } *dialog;
};
struct intdat_hazard {
    wchar_t *name;
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
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat wis;
        nat act;
        nat con;
        nat pts;
        nat regen;
        nat min_;
        nat max_;
        nat prep;
        nat cd;
        nat crit;
    } calcstats;
    foo playerdead;
    foo editstats;
    bool readying;
    bool isready;
    nat readyframe;
    nat attackcd;
} cbp={0};
void paddexp(nat add);
void phpchange(nat num);
void pdie();
void pcalcstats();
void pshowstats();
void pshowabl();
void pshowinv();
void pshowexp();
void pmove(enum direction dir);
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
