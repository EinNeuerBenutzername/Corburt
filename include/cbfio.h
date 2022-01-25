#ifndef Corburt_FIO_h_Include_Guard
#define Corburt_FIO_h_Include_Guard
#include "cbfio_base.h"
#include "cbbase.h"
static void readsave(nat saveid,FILE *fp);
static void savesave(nat saveid,FILE *fp);
static void readplayerstats(struct player *p,FILE *fp);
static void saveplayerstats(struct player plr,FILE *fp);
void readsaves();
void savesaves();

static void readsave(nat saveid,FILE *fp){
    int_fast32_t_read(&saves[saveid].valid,fp);
    //tracelog(Green,L"Valid: %" PRIuFAST32 "\n",saves[saveid].valid);
    if(!saves[saveid].valid)return;
    readplayerstats(&saves[saveid].plr,fp);
}
static void savesave(nat saveid,FILE *fp){
    int_fast32_t_write(saves[saveid].valid,fp);
    if(!saves[saveid].valid)return;
    saveplayerstats(saves[saveid].plr,fp);
}
static void readplayerstats(struct player *p,FILE *fp){
    struct player plr={0};
    wcs_read(plr.name,32,fp);
    int_fast32_t_read(&plr.rnk,fp);
    int_fast32_t_read(&plr.lvl,fp);
    int_fast64_t_read(&plr.exp,fp);
    int_fast32_t_read(&plr.maxhp,fp);
    int_fast32_t_read(&plr.hp,fp);
    int_fast32_t_read(&plr.stats.atk,fp);
    int_fast32_t_read(&plr.stats.def,fp);
    int_fast32_t_read(&plr.stats.acc,fp);
    int_fast32_t_read(&plr.stats.dod,fp);
    int_fast32_t_read(&plr.stats.stl,fp);
    int_fast32_t_read(&plr.stats.act,fp);
    int_fast32_t_read(&plr.stats.con,fp);
    int_fast32_t_read(&plr.stats.pts,fp);
    int_fast32_t_read(&plr.roomid,fp);
    *p=plr;
}
static void saveplayerstats(struct player plr,FILE *fp){
    wcs_write(plr.name,32,fp);
    int_fast32_t_write(plr.rnk,fp);
    int_fast32_t_write(plr.lvl,fp);
    int_fast64_t_write(plr.exp,fp);
    int_fast32_t_write(plr.maxhp,fp);
    int_fast32_t_write(plr.hp,fp);
    int_fast32_t_write(plr.stats.atk,fp);
    int_fast32_t_write(plr.stats.def,fp);
    int_fast32_t_write(plr.stats.acc,fp);
    int_fast32_t_write(plr.stats.dod,fp);
    int_fast32_t_write(plr.stats.stl,fp);
    int_fast32_t_write(plr.stats.act,fp);
    int_fast32_t_write(plr.stats.con,fp);
    int_fast32_t_write(plr.stats.pts,fp);
    int_fast32_t_write(plr.roomid,fp);
}
void readsaves(){
    fio.fail=0;
    FILE *fp_save=NULL;
    nat foundsaves=0;
    fp_save=fopen("save.txt","rb");
    if(fp_save==NULL){
        printc(Cyan,msg_global_nosave);
        fp_save=fopen("save.txt","w");
        fclose(fp_save);
    }else{
        printc(Cyan,msg_global_scansave);
        for(int i=0;i<savescount&&!fio.fail;i++){
            readsave(foundsaves,fp_save);
            if(saves[foundsaves].valid)foundsaves++;
        }
        if(foundsaves==0)printc(Cyan|Bright,msg_global_saveempty);
        else if(foundsaves==1){
            printc(Cyan|Bright,msg_global_savecount,foundsaves);
            printc(Cyan|Bright,L"%ls\n",saves[0].plr.name);
        }
        else{
            printc(Cyan|Bright,msg_global_savecounts,foundsaves);
            printc(Cyan|Bright,L"%ls",saves[0].plr.name);
            for(nat i=1;i<foundsaves;i++)printc(Cyan|Bright,L", %ls",saves[i].plr.name);
            printc(Cyan|Bright,L"\n");
        }
    }
    fclose(fp_save);
    while(true){
        printc(White|Bright,msg_global_enteryourname);
        wchar_t readsave_newname[32];
        scanline(readsave_newname,32);
        if(wcslen(readsave_newname)<2){
            printc(White|Bright,msg_global_nametooshort,readsave_newname);
            continue;
        }else{
            nat saveid=-1;
            for(nat i=0;i<savescount;i++){
                if(wcscmp(saves[i].plr.name,readsave_newname)==0){
                    saveid=i;
                    break;
                }
            }
            if(saveid==-1){
                if(foundsaves==savescount){
                    printc(White|Bright,msg_global_savetoomany);
                    continue;
                }
                printc(White|Bright,msg_global_confirmyourname,readsave_newname);
                wchar_t yes[2];
                scanline(yes,2);
                if(yes[0]==L'Y'||yes[0]==L'y'){
                    cursaveid=foundsaves;
                    saves[foundsaves].valid=1;
                    wcscpy(player.name,readsave_newname);
                    printc(Green|Bright,msg_global_welcomeplayer,readsave_newname);
                    break;
                }
            }else{
                printc(White|Bright,msg_global_confirmchoice,saves[saveid].plr.name);
                wchar_t yes[2];
                scanline(yes,2);
                if(yes[0]==L'Y'||yes[0]==L'y'){
                    cursaveid=saveid;
                    //wcscpy(player.name,readsave_newname);
                    player=saves[saveid].plr;
                    printc(Green|Bright,msg_global_welcomeplayer2,readsave_newname);
                    break;
                }

            }
        }
    }
}
void savesaves(){
    FILE *fp_save=NULL;
    fp_save=fopen("save.txt","wb");
    for(nat i=0;i<savescount;i++){
        if(i==cursaveid){
            saves[i].plr=player;
        }
        savesave(i,fp_save);
    }
    fclose(fp_save);
}
#endif
