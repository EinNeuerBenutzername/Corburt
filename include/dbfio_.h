#ifndef Corburt_Database_FileIO_h_Include_Guard
#define Corburt_Database_FileIO_h_Include_Guard
#include "cbfio_base.h"
#include <stdlib.h>
#ifdef DBFIO_DATA_EXPORT
#include "dbdata.h"
void savealldb();
void savedb_map(FILE *fp);
void savedb_reg(FILE *fp);
void savedb_item(FILE *fp);
void savedb_enemy(FILE *fp);
void savedb_inter(FILE *fp);
#else
struct dbfio_ {
    nat dbsize;
} dbfio_={0};
#include "cbbase.h"
void loadalldb();
void loaddb_map(FILE *fp);
void loaddb_item(FILE *fp);
void loaddb_enemy(FILE *fp);
void loaddb_inter(FILE *fp);
#endif

#ifdef DBFIO_DATA_EXPORT
void savealldb(){
    FILE *fp=fopen("cb.dat","wb");
    savedb_enemy(fp);
    savedb_item(fp);
    savedb_map(fp);
    savedb_inter(fp);
    fclose(fp);
}
void savedb_map(FILE *fp){
    int_fast32_t_write(roomdbsize,fp);
    for(nat i=0;i<roomdbsize;i++){
        int_fast32_t_write(roomdbs[i].id,fp);
        int_fast32_t_write(roomdbs[i].x,fp);
        int_fast32_t_write(roomdbs[i].y,fp);
        int_fast32_t_write(roomdbs[i].region,fp);
        int_fast32_t_write(wcslen(roomdbs[i].name),fp);
        wcs_write(roomdbs[i].name,wcslen(roomdbs[i].name),fp);
        int_fast32_t_write(wcslen(roomdbs[i].desc),fp);
        wcs_write(roomdbs[i].desc,wcslen(roomdbs[i].desc),fp);
        int_fast32_t_write(roomdbs[i].type,fp);
        for(nat j=0;j<6;j++)
            int_fast32_t_write(roomdbs[i].exits[j],fp);
        for(nat j=0;j<32;j++)
            int_fast32_t_write(roomdbs[i].table[j],fp);
        for(nat j=0;j<4;j++)
            int_fast32_t_write(roomdbs[i].buff[j],fp);
    }
}
void savedb_item(FILE *fp){
    int_fast32_t_write(itemdbsize,fp);
    for(nat i=0;i<itemdbsize;i++){
        int_fast32_t_write(itemdbs[i].id,fp);
        int_fast32_t_write(itemdbs[i].type,fp);
        int_fast32_t_write(itemdbs[i].price,fp);
        int_fast32_t_write(itemdbs[i].prep,fp);
        int_fast32_t_write(itemdbs[i].cd,fp);
        int_fast32_t_write(itemdbs[i].crit,fp);
        int_fast32_t_write(wcslen(itemdbs[i].name),fp);
        wcs_write(itemdbs[i].name,wcslen(itemdbs[i].name),fp);
        int_fast32_t_write(wcslen(itemdbs[i].desc),fp);
        wcs_write(itemdbs[i].desc,wcslen(itemdbs[i].desc),fp);
        int_fast32_t_write(itemdbs[i].stats.min_,fp);
        int_fast32_t_write(itemdbs[i].stats.max_,fp);
        int_fast32_t_write(itemdbs[i].stats.regen,fp);
        int_fast32_t_write(itemdbs[i].stats.atk,fp);
        int_fast32_t_write(itemdbs[i].stats.def,fp);
        int_fast32_t_write(itemdbs[i].stats.acc,fp);
        int_fast32_t_write(itemdbs[i].stats.dod,fp);
        int_fast32_t_write(itemdbs[i].stats.wis,fp);
        int_fast32_t_write(itemdbs[i].stats.act,fp);
        int_fast32_t_write(itemdbs[i].stats.con,fp);
        int_fast32_t_write(itemdbs[i].stats.pts,fp);
    }
}
void savedb_enemy(FILE *fp){
    int_fast32_t_write(enemydbsize,fp);
    for(nat i=0;i<enemydbsize;i++){
        int_fast32_t_write(enemydbs[i].id,fp);
        int_fast32_t_write(enemydbs[i].type,fp);
        int_fast32_t_write(wcslen(enemydbs[i].name),fp);
        wcs_write(enemydbs[i].name,wcslen(enemydbs[i].name),fp);
//        int_fast32_t_write(wcslen(enemydbs[i].desc),fp);
//        wcs_write(enemydbs[i].desc,wcslen(enemydbs[i].desc),fp);
        int_fast64_t_write(enemydbs[i].exp,fp);
        int_fast32_t_write(enemydbs[i].loot.moneymin,fp);
        int_fast32_t_write(enemydbs[i].loot.moneymax,fp);
        int_fast32_t_write(enemydbs[i].loot.weapon,fp);
        int_fast32_t_write(enemydbs[i].loot.armor,fp);
        for(nat j=0;j<ENEMY_MAXDROPS;j++){
            int_fast32_t_write(enemydbs[i].loot.drops[j].itemid,fp);
            int_fast32_t_write(enemydbs[i].loot.drops[j].rate,fp);
        }
        int_fast32_t_write(enemydbs[i].stats.hpmax,fp);
        int_fast32_t_write(enemydbs[i].stats.atkcd,fp);
        int_fast32_t_write(enemydbs[i].stats.atk,fp);
        int_fast32_t_write(enemydbs[i].stats.def,fp);
        int_fast32_t_write(enemydbs[i].stats.acc,fp);
        int_fast32_t_write(enemydbs[i].stats.dod,fp);
        int_fast32_t_write(enemydbs[i].stats.wis,fp);
        int_fast32_t_write(enemydbs[i].stats.act,fp);
        int_fast32_t_write(enemydbs[i].stats.con,fp);
    }
}
void savedb_inter(FILE *fp){}
#else
void loadalldb(){
    fio_getfilesize("cb.dat");
    if(fio.fail)exit(-1);
    FILE *fp=fopen("cb.dat","rb");
    if(!fp)exit(-1);
    loaddb_enemy(fp);
    loaddb_item(fp);
    loaddb_map(fp);
    loaddb_inter(fp);
    fclose(fp);
    tracelog(Green,msg->global_dbsize,dbfio_.dbsize/1048576.0f);
    tracelog(Green,msg->trace_pointerinuse,global.pointerinuse);
    printc(Cyan|Bright,msg->global_dataloaded);
}
void loaddb_map(FILE *fp){
    int_fast32_t_read(&roomdbsize,fp);
    roomdbs=mallocpointer(roomdbsize*sizeof(roomdb));
    for(nat i=0;i<roomdbsize;i++){
        int_fast32_t_read(&roomdbs[i].id,fp);
        int_fast32_t_read(&roomdbs[i].x,fp);
        int_fast32_t_read(&roomdbs[i].y,fp);
        int_fast32_t_read(&roomdbs[i].region,fp);
        nat len;
        int_fast32_t_read(&len,fp);
        roomdbs[i].name=mallocpointer((len+1)*sizeof(wchar_t));
        global.dbpointer++;
#ifndef CB_MAXROOMDESC
        dbfio_.dbsize+=(len+1)*sizeof(wchar_t);
#endif
        wcs_read(roomdbs[i].name,len,fp);
        roomdbs[i].name[len]=0;
        int_fast32_t_read(&len,fp);
#ifndef CB_MAXROOMDESC
        roomdbs[i].desc=mallocpointer((len+1)*sizeof(wchar_t));
        global.dbpointer++;
        dbfio_.dbsize+=(len+1)*sizeof(wchar_t);
#endif
        wcs_read(roomdbs[i].desc,len,fp);
        roomdbs[i].desc[len]=0;
        int_fast32_t_read(&roomdbs[i].type,fp);
        for(nat j=0;j<6;j++)
            int_fast32_t_read(&roomdbs[i].exits[j],fp);
        for(nat j=0;j<32;j++)
            int_fast32_t_read(&roomdbs[i].table[j],fp);
        for(nat j=0;j<4;j++)
            int_fast32_t_read(&roomdbs[i].buff[j],fp);
        dbfio_.dbsize+=sizeof(roomdb);
    }
}
void loaddb_item(FILE *fp){
    int_fast32_t_read(&itemdbsize,fp);
    itemdbs=mallocpointer(itemdbsize*sizeof(itemdb));
    for(nat i=0;i<itemdbsize;i++){
        int_fast32_t_read(&itemdbs[i].id,fp);
        int_fast32_t_read(&itemdbs[i].type,fp);
        int_fast32_t_read(&itemdbs[i].price,fp);
        int_fast32_t_read(&itemdbs[i].prep,fp);
        int_fast32_t_read(&itemdbs[i].cd,fp);
        int_fast32_t_read(&itemdbs[i].crit,fp);
        nat len;
        int_fast32_t_read(&len,fp);
        dbfio_.dbsize+=(len+1)*sizeof(wchar_t);
        itemdbs[i].name=mallocpointer((len+1)*sizeof(wchar_t));
        global.dbpointer++;
        wcs_read(itemdbs[i].name,len,fp);
        itemdbs[i].name[len]=0;
        int_fast32_t_read(&len,fp);
        dbfio_.dbsize+=(len+1)*sizeof(wchar_t);
        itemdbs[i].desc=mallocpointer((len+1)*sizeof(wchar_t));
        global.dbpointer++;
        wcs_read(itemdbs[i].desc,len,fp);
        itemdbs[i].desc[len]=0;
        int_fast32_t_read(&itemdbs[i].stats.min_,fp);
        int_fast32_t_read(&itemdbs[i].stats.max_,fp);
        int_fast32_t_read(&itemdbs[i].stats.regen,fp);
        int_fast32_t_read(&itemdbs[i].stats.atk,fp);
        int_fast32_t_read(&itemdbs[i].stats.def,fp);
        int_fast32_t_read(&itemdbs[i].stats.acc,fp);
        int_fast32_t_read(&itemdbs[i].stats.dod,fp);
        int_fast32_t_read(&itemdbs[i].stats.wis,fp);
        int_fast32_t_read(&itemdbs[i].stats.act,fp);
        int_fast32_t_read(&itemdbs[i].stats.con,fp);
        int_fast32_t_read(&itemdbs[i].stats.pts,fp);
        dbfio_.dbsize+=sizeof(itemdb);
    }
}
void loaddb_enemy(FILE *fp){
    int_fast32_t_read(&enemydbsize,fp);
    enemydbs=mallocpointer(enemydbsize*sizeof(enemydb));
    for(nat i=0;i<enemydbsize;i++){
        int_fast32_t_read(&enemydbs[i].id,fp);
        int_fast32_t_read(&enemydbs[i].type,fp);
        nat len;
        int_fast32_t_read(&len,fp);
        dbfio_.dbsize+=(len+1)*sizeof(wchar_t);
        enemydbs[i].name=mallocpointer((len+1)*sizeof(wchar_t));
        global.dbpointer++;
        wcs_read(enemydbs[i].name,len,fp);
        enemydbs[i].name[len]=0;
//        int_fast32_t_read(&len,fp);
//        enemydbs[i].desc=mallocpointer((len+1)*sizeof(wchar_t));
//        wcs_read(enemydbs[i].desc,len,fp);
        int_fast64_t_read(&enemydbs[i].exp,fp);
        int_fast32_t_read(&enemydbs[i].loot.moneymin,fp);
        int_fast32_t_read(&enemydbs[i].loot.moneymax,fp);
        int_fast32_t_read(&enemydbs[i].loot.weapon,fp);
        int_fast32_t_read(&enemydbs[i].loot.armor,fp);
        for(nat j=0;j<ENEMY_MAXDROPS;j++){
            int_fast32_t_read(&enemydbs[i].loot.drops[j].itemid,fp);
            int_fast32_t_read(&enemydbs[i].loot.drops[j].rate,fp);
        }
        int_fast32_t_read(&enemydbs[i].stats.hpmax,fp);
        int_fast32_t_read(&enemydbs[i].stats.atkcd,fp);
        int_fast32_t_read(&enemydbs[i].stats.atk,fp);
        int_fast32_t_read(&enemydbs[i].stats.def,fp);
        int_fast32_t_read(&enemydbs[i].stats.acc,fp);
        int_fast32_t_read(&enemydbs[i].stats.dod,fp);
        int_fast32_t_read(&enemydbs[i].stats.wis,fp);
        int_fast32_t_read(&enemydbs[i].stats.act,fp);
        int_fast32_t_read(&enemydbs[i].stats.con,fp);
        dbfio_.dbsize+=sizeof(enemydb);
    }
}
void loaddb_inter(FILE *fp){}
#endif
#endif
