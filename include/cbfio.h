#ifndef Corburt_FIO_h_Include_Guard
#define Corburt_FIO_h_Include_Guard
#include "cbfio_base.h"
#include "cbbase.h"
#include <stdlib.h>
static void readsave(nat saveid,FILE *fp);
static void savesave(nat saveid,FILE *fp);
static void save_overwrite(nat saveid);
static void save_overwritten(nat saveid);
static void readplayerstats(struct player *p,FILE *fp);
static void saveplayerstats(struct player plr,FILE *fp);
static void readinventory(struct inventory *inv,FILE *fp);
static void saveinventory(struct inventory inv,FILE *fp);
static void readet_items(FILE *fp);
static void saveet_items(FILE *fp);
static void readet_enemies(FILE *fp);
static void saveet_enemies(FILE *fp);
static void readet_rooms(FILE *fp);
static void saveet_rooms(FILE *fp);
static void readsavesglobaldata(FILE *fp);
static void savesavesglobaldata(FILE *fp);
void readsaves();
void savesaves();

static void readsave(nat saveid,FILE *fp){
    int_fast32_t_read(&saves[saveid].valid,fp);
    //tracelog(Green,L"Valid: %" PRIuFAST32 "\n",saves[saveid].valid);
    if(!saves[saveid].valid)return;
    readplayerstats(&saves[saveid].plr,fp);
    readinventory(&saves[saveid].inv,fp);
}
static void savesave(nat saveid,FILE *fp){
    int_fast32_t_write(saves[saveid].valid,fp);
    if(!saves[saveid].valid)return;
    saveplayerstats(saves[saveid].plr,fp);
    saveinventory(saves[saveid].inv,fp);
}
static void save_overwrite(nat saveid){
    saves[saveid].valid=true;
    player=saves[saveid].plr;
    inventory=saves[saveid].inv;
}
static void save_overwritten(nat saveid){
    saves[saveid].plr=player;
    saves[saveid].inv=inventory;
}
static void readplayerstats(struct player *p,FILE *fp){
    struct player plr={0};
    wcs_read(plr.name,32,fp);
    int_fast32_t_read(&plr.spawn,fp);
    int_fast32_t_read(&plr.rnk,fp);
    int_fast32_t_read(&plr.lvl,fp);
    int_fast64_t_read(&plr.exp,fp);
    int_fast64_t_read(&plr.maxhp,fp);
    int_fast64_t_read(&plr.hp,fp);
    int_fast32_t_read(&plr.stats.atk,fp);
    int_fast32_t_read(&plr.stats.def,fp);
    int_fast32_t_read(&plr.stats.acc,fp);
    int_fast32_t_read(&plr.stats.dod,fp);
    int_fast32_t_read(&plr.stats.wis,fp);
    int_fast32_t_read(&plr.stats.act,fp);
    int_fast32_t_read(&plr.stats.con,fp);
    int_fast32_t_read(&plr.stats.pts,fp);
    int_fast32_t_read(&plr.bstats.atk,fp);
    int_fast32_t_read(&plr.bstats.def,fp);
    int_fast32_t_read(&plr.bstats.acc,fp);
    int_fast32_t_read(&plr.bstats.dod,fp);
    int_fast32_t_read(&plr.bstats.wis,fp);
    int_fast32_t_read(&plr.bstats.act,fp);
    int_fast32_t_read(&plr.bstats.con,fp);
    int_fast32_t_read(&plr.bstats.pts,fp);
    int_fast32_t_read(&plr.roomid,fp);
    *p=plr;
}
static void saveplayerstats(struct player plr,FILE *fp){
    wcs_write(plr.name,32,fp);
    int_fast32_t_write(plr.spawn,fp);
    int_fast32_t_write(plr.rnk,fp);
    int_fast32_t_write(plr.lvl,fp);
    int_fast64_t_write(plr.exp,fp);
    int_fast64_t_write(plr.maxhp,fp);
    int_fast64_t_write(plr.hp,fp);
    int_fast32_t_write(plr.stats.atk,fp);
    int_fast32_t_write(plr.stats.def,fp);
    int_fast32_t_write(plr.stats.acc,fp);
    int_fast32_t_write(plr.stats.dod,fp);
    int_fast32_t_write(plr.stats.wis,fp);
    int_fast32_t_write(plr.stats.act,fp);
    int_fast32_t_write(plr.stats.con,fp);
    int_fast32_t_write(plr.stats.pts,fp);
    int_fast32_t_write(plr.bstats.atk,fp);
    int_fast32_t_write(plr.bstats.def,fp);
    int_fast32_t_write(plr.bstats.acc,fp);
    int_fast32_t_write(plr.bstats.dod,fp);
    int_fast32_t_write(plr.bstats.wis,fp);
    int_fast32_t_write(plr.bstats.act,fp);
    int_fast32_t_write(plr.bstats.con,fp);
    int_fast32_t_write(plr.bstats.pts,fp);
    int_fast32_t_write(plr.roomid,fp);
}
static void readinventory(struct inventory *inv,FILE *fp){
    struct inventory v;
    int_fast32_t_read(&v.unlocked,fp);
    for(nat i=0;i<64;i++)
        int_fast32_t_read(&v.items[i],fp);
    for(nat i=0;i<5;i++)
        int_fast32_t_read(&v.accessories[i],fp);
    int_fast32_t_read(&v.weapon,fp);
    int_fast32_t_read(&v.armor,fp);
    int_fast64_t_read(&v.money,fp);
    *inv=v;
}
static void saveinventory(struct inventory inv,FILE *fp){
    int_fast32_t_write(inv.unlocked,fp);
    for(nat i=0;i<64;i++)
        int_fast32_t_write(inv.items[i],fp);
    for(nat i=0;i<5;i++)
        int_fast32_t_write(inv.accessories[i],fp);
    int_fast32_t_write(inv.weapon,fp);
    int_fast32_t_write(inv.armor,fp);
    int_fast64_t_write(inv.money,fp);
}
static void readet_items(FILE *fp){
    nat itemsmax_tmp;
    int_fast32_t_read(&itemsmax_tmp,fp);
//    tracelog(Cyan,L"max items: %" PRIdFAST32 ".\n",itemsmax_tmp);
    while(itemsmax_tmp>itemsmax){
        etitem_expand();
    }
    itemscount=0;
    for(nat i=0;i<itemsmax_tmp;i++){
        nat avail;
        int_fast32_t_read(&avail,fp);
        et_items[i].available=(avail==1);
        if(avail){
            int_fast32_t_read(&et_items[i].roomid,fp);
            int_fast32_t_read(&et_items[i].itemid,fp);
            int_fast32_t_read(&et_items[i].qnty,fp);
            itemscount++;
        }
    }
    if(itemscount)
        tracelog(Cyan,msg->trace_loadeti,itemscount);
}
static void saveet_items(FILE *fp){
    int_fast32_t_write(itemsmax,fp);
    for(nat i=0;i<itemsmax;i++){
        nat avail=et_items[i].available?1:0;
        int_fast32_t_write(avail,fp);
        if(et_items[i].available){
            int_fast32_t_write(et_items[i].roomid,fp);
            int_fast32_t_write(et_items[i].itemid,fp);
            int_fast32_t_write(et_items[i].qnty,fp);
        }
    }
}
static void readet_enemies(FILE *fp){
    nat enemiesmax_tmp;
    int_fast32_t_read(&enemiesmax_tmp,fp);
//    tracelog(Cyan,L"max enemies: %" PRIdFAST32 ".\n",enemiesmax_tmp);
    enemiescount=0;
    while(enemiesmax_tmp>enemiesmax){
        etenemy_expand();
    }
    for(nat i=0;i<enemiesmax_tmp;i++){
        nat avail;
        int_fast32_t_read(&avail,fp);
        et_enemies[i].available=(avail==1);
        if(avail){
            int_fast32_t_read(&et_enemies[i].roomid,fp);
            int_fast32_t_read(&et_enemies[i].enemyid,fp);
            int_fast32_t_read(&et_enemies[i].hp,fp);
            int_fast32_t_read(&et_enemies[i].attackcd,fp);
            enemiescount++;
        }
    }
    if(enemiescount)
        tracelog(Cyan,msg->trace_loadete,enemiescount);
}
static void saveet_enemies(FILE *fp){
    int_fast32_t_write(enemiesmax,fp);
    for(nat i=0;i<enemiesmax;i++){
        nat avail=et_enemies[i].available?1:0;
        int_fast32_t_write(avail,fp);
        if(et_enemies[i].available){
            int_fast32_t_write(et_enemies[i].roomid,fp);
            int_fast32_t_write(et_enemies[i].enemyid,fp);
            int_fast32_t_write(et_enemies[i].hp,fp);
            int_fast32_t_write(et_enemies[i].attackcd,fp);
        }
    }
}
static void readet_rooms(FILE *fp){
    nat roomsmax_tmp;
    int_fast32_t_read(&roomsmax_tmp,fp);
    if(roomdbsize<roomsmax_tmp){
        printc(Red,msg->global_invalidroomcount);
        exit(-1);
    }else if(roomdbsize>roomsmax_tmp){
        printc(Cyan,msg->global_roomcountfewer);
    }
    for(nat i=0;i<roomsmax_tmp;i++){
        int_fast32_t_read(&et_rooms[i].id,fp);
        int_fast32_t_read(&et_rooms[i].money,fp);
        for(nat j=0;j<DBE_ENEMYCAP;j++)
            int_fast32_t_read(&et_rooms[i].etenemy[j],fp);
        for(nat j=0;j<DBE_ITEMCAP;j++)
            int_fast32_t_read(&et_rooms[i].etitem[j],fp);
        for(nat j=0;j<DBE_INTERCAP;j++)
            int_fast32_t_read(&et_rooms[i].etinteract[j],fp);
    }
}
static void saveet_rooms(FILE *fp){
    int_fast32_t_write(roomdbsize,fp);
    for(nat i=0;i<roomdbsize;i++){
        int_fast32_t_write(et_rooms[i].id,fp);
        int_fast32_t_write(et_rooms[i].money,fp);
        for(nat j=0;j<DBE_ENEMYCAP;j++)
            int_fast32_t_write(et_rooms[i].etenemy[j],fp);
        for(nat j=0;j<DBE_ITEMCAP;j++)
            int_fast32_t_write(et_rooms[i].etitem[j],fp);
        for(nat j=0;j<DBE_INTERCAP;j++)
            int_fast32_t_write(et_rooms[i].etinteract[j],fp);
    }
}
static void readsavesglobaldata(FILE *fp){
    nat version=0;
    int_fast32_t_read(&version,fp);
    if(version!=CB_VERSIONNUM&&CB_VERSIONCHECK){
        printr(Red,msg->global_save_incompat,msg->global_corburtversion);
        fio.fail=1;
    }
    int_fast32_t_read(&global.curtick,fp);
    int_fast64_t_read(&global.curround,fp);
    readet_items(fp);
    readet_enemies(fp);
    readet_rooms(fp);
    if(version!=CB_VERSIONNUM){
        printc(Cyan,msg->global_resetenemydata);
        struct et_enemy ete={0};
        for(nat i=0;i<enemiesmax;i++){
            et_enemies[i]=ete;
            et_enemies[i].available=false;
        }
        enemiescount=0;
        for(nat i=0;i<roomdbsize;i++){
            for(nat j=0;j<DBE_ENEMYCAP;j++){
                et_rooms[i].etenemy[j]=0;
            }
        }
        et_initenemies();
    }
}
static void savesavesglobaldata(FILE *fp){
    int_fast32_t_write(CB_VERSIONNUM,fp);
    int_fast32_t_write(global.curtick,fp);
    int_fast64_t_write(global.curround,fp);
    saveet_items(fp);
    saveet_enemies(fp);
    saveet_rooms(fp);
}
void readsaves(){
    fio.fail=0;
    FILE *fp_save=NULL;
    nat foundsaves=0;
    fio_getfilesize("save.txt");
    fp_save=fopen("save.txt","rb");
    if(fp_save==NULL){
        et_initenemies();
        printr(Cyan,msg->global_nosave);
    }else{
        printr(Cyan,msg->global_scansave);
        readsavesglobaldata(fp_save);
        for(int i=0;i<savescount;i++){
            readsave(foundsaves,fp_save);
            if(saves[foundsaves].valid)foundsaves++;
        }
        fclose(fp_save);
        if(foundsaves==0)printr(Cyan|Bright,msg->global_saveempty);
        else if(foundsaves==1){
            printr(Cyan|Bright,msg->global_savecount,foundsaves);
            printr(Cyan|Bright,L"%ls\n",saves[0].plr.name);
        }
        else{
            printr(Cyan|Bright,msg->global_savecounts,foundsaves);
            printr(Cyan|Bright,L"%ls",saves[0].plr.name);
            for(nat i=1;i<foundsaves;i++)printr(Cyan|Bright,L", %ls",saves[i].plr.name);
            printr(Cyan|Bright,L"\n");
        }
    }
    while(true){
        printr(White|Bright,msg->global_enteryourname);
        wchar_t readsave_newname[32];
        scanline(readsave_newname,32);
        if(wcslen(readsave_newname)<2){
            printr(White|Bright,msg->global_nametooshort,readsave_newname);
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
                    printr(White|Bright,msg->global_savetoomany);
                    continue;
                }
                printr(White|Bright,msg->global_confirmyourname,readsave_newname);
                wchar_t yes[2];
                scanline(yes,2);
                if(yes[0]==L'Y'||yes[0]==L'y'){
                    cursaveid=foundsaves;
                    saves[foundsaves].valid=1;
                    wcscpy(player.name,readsave_newname);
                    printr(Green|Bright,msg->global_welcomeplayer,readsave_newname);
                    break;
                }
            }
            else{
                printr(White|Bright,msg->global_confirmchoice,saves[saveid].plr.name);
                wchar_t yes[2];
                scanline(yes,2);
                if(yes[0]==L'Y'||yes[0]==L'y'){
                    cursaveid=saveid;
                    save_overwrite(saveid);
                    printr(Green|Bright,msg->global_welcomeplayer2,readsave_newname);
                    break;
                }

            }
        }
    }
    pcalcstats();
}
void savesaves(){
    FILE *fp_save=NULL;
    fp_save=fopen("save.txt","wb");
    if(fp_save==NULL){
        fatalerror(error_cannotsave);
        return;
    }
    savesavesglobaldata(fp_save);
    save_overwritten(cursaveid);
    for(nat i=0;i<savescount;i++){
        savesave(i,fp_save);
    }
    fclose(fp_save);
}
#endif
