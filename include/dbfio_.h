#ifndef Corburt_Database_FileIO_h_Include_Guard
#define Corburt_Database_FileIO_h_Include_Guard
#include "cbfio_base.h"
#include <stdlib.h>
#ifdef DBFIO_DATA_EXPORT
//#include "dbdata.h"
#include "../tools/dxport/dbdata.h"
void savealldb();
void savedb_map(FILE *fp);
void savedb_reg(FILE *fp);
void savedb_item(FILE *fp);
void savedb_enemy(FILE *fp);
void savedb_inter(FILE *fp);
#else
struct dbfio_ {
    int dbsize;
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
    FILE *fp=fopenrelative("cb.dat", "wb");
    savedb_enemy(fp);
    savedb_item(fp);
    savedb_map(fp);
    savedb_inter(fp);
    fclose(fp);
}
void savedb_map(FILE *fp){
    int_fast32_t_write(roomdbsize, fp);
    for(int i=0; i<roomdbsize; i++){
        int_fast32_t_write(roomdbs[i].id, fp);
        int_fast32_t_write(roomdbs[i].x, fp);
        int_fast32_t_write(roomdbs[i].y, fp);
        int_fast32_t_write(roomdbs[i].region, fp);
        int_fast32_t_write(strlen(roomdbs[i].name), fp);
        str_write(roomdbs[i].name, strlen(roomdbs[i].name), fp);
        int_fast32_t_write(strlen(roomdbs[i].desc), fp);
        str_write(roomdbs[i].desc, strlen(roomdbs[i].desc), fp);
        int_fast32_t_write(roomdbs[i].type, fp);
        for(int j=0; j<6; j++)
            int_fast32_t_write(roomdbs[i].exits[j], fp);
        for(int j=0; j<32; j++)
            int_fast32_t_write(roomdbs[i].table[j], fp);
        for(int j=0; j<4; j++)
            int_fast32_t_write(roomdbs[i].buff[j], fp);
    }
}
void savedb_item(FILE *fp){
    int_fast32_t_write(itemdbsize, fp);
    for(int i=0; i<itemdbsize; i++){
        int_fast32_t_write(itemdbs[i].id, fp);
        int_fast32_t_write(itemdbs[i].type, fp);
        int_fast32_t_write(itemdbs[i].price, fp);
        int_fast32_t_write(itemdbs[i].prep, fp);
        int_fast32_t_write(itemdbs[i].cd, fp);
        int_fast32_t_write(itemdbs[i].crit, fp);
        int_fast32_t_write(strlen(itemdbs[i].name), fp);
        str_write(itemdbs[i].name, strlen(itemdbs[i].name), fp);
        int_fast32_t_write(strlen(itemdbs[i].desc), fp);
        str_write(itemdbs[i].desc, strlen(itemdbs[i].desc), fp);
        int_fast32_t_write(itemdbs[i].stats.min_, fp);
        int_fast32_t_write(itemdbs[i].stats.max_, fp);
        int_fast32_t_write(itemdbs[i].stats.regen, fp);
        int_fast32_t_write(itemdbs[i].stats.agi, fp);
        int_fast32_t_write(itemdbs[i].stats.acc, fp);
        int_fast32_t_write(itemdbs[i].stats.dod, fp);
        int_fast32_t_write(itemdbs[i].stats.con, fp);
        int_fast32_t_write(itemdbs[i].stats.def, fp);
        int_fast32_t_write(itemdbs[i].stats.vit, fp);
        int_fast32_t_write(itemdbs[i].stats.res, fp);
        int_fast32_t_write(itemdbs[i].stats.rfl, fp);
        int_fast32_t_write(itemdbs[i].stats.foc, fp);
        int_fast32_t_write(itemdbs[i].stats.str, fp);
        int_fast32_t_write(itemdbs[i].stats.atk, fp);
        int_fast32_t_write(itemdbs[i].stats.stm, fp);
        int_fast32_t_write(itemdbs[i].stats.wil, fp);
        int_fast32_t_write(itemdbs[i].stats.san, fp);
        int_fast32_t_write(itemdbs[i].stats.sat, fp);
        int_fast32_t_write(itemdbs[i].stats.wis, fp);
        int_fast32_t_write(itemdbs[i].stats.mag, fp);
        int_fast32_t_write(itemdbs[i].stats.mat, fp);
        int_fast32_t_write(itemdbs[i].stats.luck, fp);
    }
}
void savedb_enemy(FILE *fp){
    int_fast32_t_write(enemydbsize, fp);
    for(int i=0; i<enemydbsize; i++){
        int_fast32_t_write(enemydbs[i].id, fp);
        int_fast32_t_write(enemydbs[i].type, fp);
        int_fast32_t_write(strlen(enemydbs[i].name), fp);
        str_write(enemydbs[i].name, strlen(enemydbs[i].name), fp);
//        int_fast32_t_write(strlen(enemydbs[i].desc), fp);
//        str_write(enemydbs[i].desc, strlen(enemydbs[i].desc), fp);
        int_fast64_t_write(enemydbs[i].exp, fp);
        int_fast32_t_write(enemydbs[i].loot.moneymin, fp);
        int_fast32_t_write(enemydbs[i].loot.moneymax, fp);
        int_fast32_t_write(enemydbs[i].loot.weapon, fp);
        int_fast32_t_write(enemydbs[i].loot.armor, fp);
        for(int j=0; j<ENEMY_MAXDROPS; j++){
            int_fast32_t_write(enemydbs[i].loot.drops[j].itemid, fp);
            int_fast32_t_write(enemydbs[i].loot.drops[j].rate, fp);
        }
        int_fast32_t_write(enemydbs[i].stats.hpmax, fp);
        int_fast32_t_write(enemydbs[i].stats.atkcd, fp);
        int_fast32_t_write(enemydbs[i].stats.acc, fp);
        int_fast32_t_write(enemydbs[i].stats.dod, fp);
        int_fast32_t_write(enemydbs[i].stats.vit, fp);
        int_fast32_t_write(enemydbs[i].stats.atk, fp);
        int_fast32_t_write(enemydbs[i].stats.stm, fp);
        int_fast32_t_write(enemydbs[i].stats.san, fp);
        int_fast32_t_write(enemydbs[i].stats.sat, fp);
        int_fast32_t_write(enemydbs[i].stats.mag, fp);
        int_fast32_t_write(enemydbs[i].stats.mat, fp);
    }
}
void savedb_inter(FILE *fp){}
#else
void loadalldb(){
    fio_getfilesize("cb.dat");
    if(fio.fail){
        printr(palette.warning, "Error: Cannot open data file.\n");
        printr(palette.msg, "Press any key to quit.\n");
        cbc_getch();
        exit(-1);
    }
    FILE *fp=fopenrelative("cb.dat", "rb");
    if(!fp)exit(-1);
    loaddb_enemy(fp);
    loaddb_item(fp);
    loaddb_map(fp);
    loaddb_inter(fp);
    fclose(fp);
    tracelog(msg->global_dbsize, dbfio_.dbsize/1048576.0f);
    tracelog(msg->trace_pointerinuse, global.pointerinuse);
    printr(palette.inform, msg->global_dataloaded);
}
void loaddb_map(FILE *fp){
    int_fast32_t_read(&roomdbsize, fp);
    roomdbs=mallocpointer(roomdbsize*sizeof(roomdb));
    for(int i=0; i<roomdbsize; i++){
        int_fast32_t_read(&roomdbs[i].id, fp);
        int_fast32_t_read(&roomdbs[i].x, fp);
        int_fast32_t_read(&roomdbs[i].y, fp);
        int_fast32_t_read(&roomdbs[i].region, fp);
        int len;
        int_fast32_t_read(&len, fp);
        roomdbs[i].name=mallocpointer((len+1)*sizeof(char));
        global.dbpointer++;
#ifndef CB_MAXROOMDESC
        dbfio_.dbsize+=(len+1)*sizeof(char);
#endif
        str_read(roomdbs[i].name, len, fp);
        roomdbs[i].name[len]=0;
        int_fast32_t_read(&len, fp);
#ifndef CB_MAXROOMDESC
        roomdbs[i].desc=mallocpointer((len+1)*sizeof(char));
        global.dbpointer++;
        dbfio_.dbsize+=(len+1)*sizeof(char);
#endif
        str_read(roomdbs[i].desc, len, fp);
        roomdbs[i].desc[len]=0;
        int_fast32_t_read(&roomdbs[i].type, fp);
        for(int j=0; j<6; j++)
            int_fast32_t_read(&roomdbs[i].exits[j], fp);
        for(int j=0; j<32; j++)
            int_fast32_t_read(&roomdbs[i].table[j], fp);
        for(int j=0; j<4; j++)
            int_fast32_t_read(&roomdbs[i].buff[j], fp);
        dbfio_.dbsize+=sizeof(roomdb);
    }
}
void loaddb_item(FILE *fp){
    int_fast32_t_read(&itemdbsize, fp);
    itemdbs=mallocpointer(itemdbsize*sizeof(itemdb));
    for(int i=0; i<itemdbsize; i++){
        int_fast32_t_read(&itemdbs[i].id, fp);
        int_fast32_t_read(&itemdbs[i].type, fp);
        int_fast32_t_read(&itemdbs[i].price, fp);
        int_fast32_t_read(&itemdbs[i].prep, fp);
        int_fast32_t_read(&itemdbs[i].cd, fp);
        int_fast32_t_read(&itemdbs[i].crit, fp);
        int len;
        int_fast32_t_read(&len, fp);
        dbfio_.dbsize+=(len+1)*sizeof(char);
        itemdbs[i].name=mallocpointer((len+1)*sizeof(char));
        global.dbpointer++;
        str_read(itemdbs[i].name, len, fp);
        itemdbs[i].name[len]=0;
        int_fast32_t_read(&len, fp);
        dbfio_.dbsize+=(len+1)*sizeof(char);
        itemdbs[i].desc=mallocpointer((len+1)*sizeof(char));
        global.dbpointer++;
        str_read(itemdbs[i].desc, len, fp);
        itemdbs[i].desc[len]=0;
        int_fast32_t_read(&itemdbs[i].stats.min_, fp);
        int_fast32_t_read(&itemdbs[i].stats.max_, fp);
        int_fast32_t_read(&itemdbs[i].stats.regen, fp);
        int_fast32_t_read(&itemdbs[i].stats.agi, fp);
        int_fast32_t_read(&itemdbs[i].stats.con, fp);
        int_fast32_t_read(&itemdbs[i].stats.res, fp);
        int_fast32_t_read(&itemdbs[i].stats.str, fp);
        int_fast32_t_read(&itemdbs[i].stats.wil, fp);
        int_fast32_t_read(&itemdbs[i].stats.wis, fp);
        int_fast32_t_read(&itemdbs[i].stats.acc, fp);
        int_fast32_t_read(&itemdbs[i].stats.dod, fp);
        int_fast32_t_read(&itemdbs[i].stats.def, fp);
        int_fast32_t_read(&itemdbs[i].stats.vit, fp);
        int_fast32_t_read(&itemdbs[i].stats.rfl, fp);
        int_fast32_t_read(&itemdbs[i].stats.foc, fp);
        int_fast32_t_read(&itemdbs[i].stats.atk, fp);
        int_fast32_t_read(&itemdbs[i].stats.stm, fp);
        int_fast32_t_read(&itemdbs[i].stats.san, fp);
        int_fast32_t_read(&itemdbs[i].stats.sat, fp);
        int_fast32_t_read(&itemdbs[i].stats.mag, fp);
        int_fast32_t_read(&itemdbs[i].stats.mat, fp);
        int_fast32_t_read(&itemdbs[i].stats.luck, fp);
        dbfio_.dbsize+=sizeof(itemdb);
    }
}
void loaddb_enemy(FILE *fp){
    int_fast32_t_read(&enemydbsize, fp);
    enemydbs=mallocpointer(enemydbsize*sizeof(enemydb));
    for(int i=0; i<enemydbsize; i++){
        int_fast32_t_read(&enemydbs[i].id, fp);
        int_fast32_t_read(&enemydbs[i].type, fp);
        int len;
        int_fast32_t_read(&len, fp);
        dbfio_.dbsize+=(len+1)*sizeof(char);
        enemydbs[i].name=mallocpointer((len+1)*sizeof(char));
        global.dbpointer++;
        str_read(enemydbs[i].name, len, fp);
        enemydbs[i].name[len]=0;
//        int_fast32_t_read(&len, fp);
//        enemydbs[i].desc=mallocpointer((len+1)*sizeof(char));
//        str_read(enemydbs[i].desc, len, fp);
        int_fast64_t_read(&enemydbs[i].exp, fp);
        int_fast32_t_read(&enemydbs[i].loot.moneymin, fp);
        int_fast32_t_read(&enemydbs[i].loot.moneymax, fp);
        int_fast32_t_read(&enemydbs[i].loot.weapon, fp);
        int_fast32_t_read(&enemydbs[i].loot.armor, fp);
        for(int j=0; j<ENEMY_MAXDROPS; j++){
            int_fast32_t_read(&enemydbs[i].loot.drops[j].itemid, fp);
            int_fast32_t_read(&enemydbs[i].loot.drops[j].rate, fp);
        }
        int_fast32_t_read(&enemydbs[i].stats.hpmax, fp);
        int_fast32_t_read(&enemydbs[i].stats.atkcd, fp);
        int_fast32_t_read(&enemydbs[i].stats.acc, fp);
        int_fast32_t_read(&enemydbs[i].stats.dod, fp);
        int_fast32_t_read(&enemydbs[i].stats.vit, fp);
        int_fast32_t_read(&enemydbs[i].stats.atk, fp);
        int_fast32_t_read(&enemydbs[i].stats.stm, fp);
        int_fast32_t_read(&enemydbs[i].stats.san, fp);
        int_fast32_t_read(&enemydbs[i].stats.sat, fp);
        int_fast32_t_read(&enemydbs[i].stats.mag, fp);
        int_fast32_t_read(&enemydbs[i].stats.mat, fp);
        dbfio_.dbsize+=sizeof(enemydb);
    }
}
void loaddb_inter(FILE *fp){}
#endif
#endif
