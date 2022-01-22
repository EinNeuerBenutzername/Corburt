#ifndef Corburt_FileIO_h_Include_Guard
#define Corburt_FileIO_h_Include_Guard
#include "cbbase.h"
#ifdef __cplusplus
extern "C"{
#endif
//io
static void makewcsle(wchar_t *wcs);
static void makewcsbe(wchar_t *wcs);
nat readwcs(wchar_t *wcs,size_t len,FILE *fp);
void writewcs(wchar_t *wcs,size_t len,FILE *fp);
static nat makenatle(nat n);
static nat makenatbe(nat n);
nat readnat(nat *n,FILE *fp);
void writenat(nat n,FILE *fp);
static nat makebatle(bat b);
static nat makebatbe(bat b);
nat readbat(bat *b,FILE *fp);
void writebat(bat b,FILE *fp);
static void makewcsle(wchar_t *wcs){
    if(isle)return;
    for(nat i=0;i<wcslen(wcs);i++){
        unsigned char c[sizeof(wchar_t)];
        wchar_t result;
        for(nat j=0;j<sizeof(wchar_t);j++){
            c[j]=(wcs[i]>>(8*i))&255;
            result+=(wchar_t)c[i]<<((sizeof(nat)-i-1)*8);
        }
        wcs[i]=result;
    }
}
static void makewcsbe(wchar_t *wcs){
    if(!isle)return;
    for(nat i=0;i<wcslen(wcs);i++){
        unsigned char c[sizeof(wchar_t)];
        wchar_t result;
        for(nat j=0;j<sizeof(wchar_t);j++){
            c[j]=(wcs[i]>>(8*i))&255;
            result+=(wchar_t)c[i]<<((sizeof(nat)-i-1)*8);
        }
        wcs[i]=result;
    }
}
nat readwcs(wchar_t *wcs,size_t len,FILE *fp){
    if(fread(wcs,len*sizeof(wchar_t),1,fp)!=1)return 0;
    if(!isle)makewcsbe(wcs);
    return 1;
}
void writewcs(wchar_t *wcs,size_t len,FILE *fp){
    makewcsle(wcs);
    fwrite(wcs,len*sizeof(wchar_t),1,fp);
}
static nat makenatle(nat n){
    unsigned char c[sizeof(nat)];
    if(isle)return n;
    nat result;
    for(nat i=0;i<sizeof(nat);i++){
        c[i]=(n>>8*i)&255;
        result+=(nat)c[i]<<((sizeof(nat)-i-1)*8);
    }
    return result;
}
static nat makenatbe(nat n){
    unsigned char c[sizeof(nat)];
    if(!isle)return n;
    nat result;
    for(nat i=0;i<sizeof(nat);i++){
        c[i]=(n>>8*i)&255;
        result+=(nat)c[i]<<((sizeof(nat)-i-1)*8);
    }
    return result;
}
nat readnat(nat *n,FILE *fp){
    nat r;
    if(fread(&r,sizeof(nat),1,fp)!=1)return 0;
    if(!isle)r=makenatbe(r);
    *n=r;
    return 1;
}
void writenat(nat n,FILE *fp){
    n=makenatle(n);
    fwrite(&n,sizeof(nat),1,fp);
}
static nat makebatle(bat b){
    unsigned char c[sizeof(bat)];
    if(isle)return b;
    bat result;
    for(nat i=0;i<sizeof(bat);i++){
        c[i]=(b>>8*i)&255;
        result+=(bat)c[i]<<((sizeof(bat)-i-1)*8);
    }
    return result;
}
static nat makebatbe(bat b){
    unsigned char c[sizeof(bat)];
    if(!isle)return b;
    bat result;
    for(nat i=0;i<sizeof(bat);i++){
        c[i]=(b>>8*i)&255;
        result+=(bat)c[i]<<((sizeof(bat)-i-1)*8);
    }
    return result;
}
nat readbat(bat *b,FILE *fp){
    bat r;
    if(fread(&r,sizeof(bat),1,fp)!=1)return 0;
    if(!isle)r=makebatbe(r);
    *b=r;
    return 1;
}
void writebat(bat b,FILE *fp){
    b=makebatle(b);
    fwrite(&b,sizeof(bat),1,fp);
}

void readsaves();
void savesaves();
nat readplayerstats(struct player *p,FILE *fp);
void saveplayerstats(struct player p,FILE *fp);
void readsaves(){
    FILE *save_file=NULL;
    save_file=fopen("save.txt","r");
    if(save_file==NULL){
        printc(Cyan,msg_global_nosave);
        save_file=fopen("save.txt","w");
        fclose(save_file);
    }else{
        printc(Cyan,msg_global_scansave);
        nat readsaves_foundsaves=0;

        //read
        while(readplayerstats(&saves[readsaves_foundsaves].plr,save_file)){
            readsaves_foundsaves++;
        }
        fclose(save_file);

        if(readsaves_foundsaves==0){
            printc(Cyan|Bright,msg_global_saveempty);
        }else if(readsaves_foundsaves==1){
            printc(Cyan|Bright,msg_global_savecount,readsaves_foundsaves);
            printc(Cyan|Bright,L"%ls\n",saves[0].plr.name);
        }else{
            printc(Cyan|Bright,msg_global_savecounts,readsaves_foundsaves);
            printc(Cyan|Bright,L"%ls",saves[0].plr.name);
            for(nat i=1;i<readsaves_foundsaves;i++)printc(Cyan|Bright,L", %ls",saves[i].plr.name);
            printc(Cyan|Bright,L"\n");
        }
    }
    while(true){
        printc(White|Bright,msg_global_enteryourname);
        wchar_t readsave_newname[32];
        scanline(readsave_newname,32);
        if(wcslen(readsave_newname)<2){
            printc(White|Bright,msg_global_nametooshort,readsave_newname);
            continue;
        }else{
            printc(White|Bright,msg_global_confirmyourname,readsave_newname);
        }
        wchar_t yes[2];
        scanline(yes,2);
        if(yes[0]==L'Y'||yes[0]==L'y'){
            wcscpy(player.name,readsave_newname);
            printc(Green|Bright,msg_global_welcome_,readsave_newname);
            break;
        }
    }
}
void savesaves(){
    FILE *save_file=fopen("save.txt","ab");
    saveplayerstats(player,save_file);
    fclose(save_file);
}
nat readplayerstats(struct player *p,FILE *fp){
    struct player plr;
    if(!readwcs(plr.name,32,fp))return 0;
    if(!readnat(&plr.rnk,fp))return 0;
    if(!readnat(&plr.lvl,fp))return 0;
    if(!readbat(&plr.exp,fp))return 0;
    if(!readnat(&plr.maxhp,fp))return 0;
    if(!readnat(&plr.hp,fp))return 0;
    if(!readnat(&plr.stats.atk,fp))return 0;
    if(!readnat(&plr.stats.def,fp))return 0;
    if(!readnat(&plr.stats.acc,fp))return 0;
    if(!readnat(&plr.stats.dod,fp))return 0;
    if(!readnat(&plr.stats.stl,fp))return 0;
    if(!readnat(&plr.stats.act,fp))return 0;
    if(!readnat(&plr.stats.con,fp))return 0;
    if(!readnat(&plr.stats.pts,fp))return 0;
    if(!readnat(&plr.roomid,fp))return 0;
    *p=plr;
    return 1;
}
void saveplayerstats(struct player p,FILE *fp){
    writewcs(p.name,32,fp);
    writenat(p.rnk,fp);
    writenat(p.lvl,fp);
    writebat(p.exp,fp);
    writenat(p.maxhp,fp);
    writenat(p.hp,fp);
    writenat(p.stats.atk,fp);
    writenat(p.stats.def,fp);
    writenat(p.stats.acc,fp);
    writenat(p.stats.dod,fp);
    writenat(p.stats.stl,fp);
    writenat(p.stats.act,fp);
    writenat(p.stats.con,fp);
    writenat(p.stats.pts,fp);
    writenat(p.roomid,fp);
}
#ifdef __cplusplus
}
#endif
#endif
