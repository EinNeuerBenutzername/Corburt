#ifndef Corburt_Database_FileIO_h_Include_Guard
#define Corburt_Database_FileIO_h_Include_Guard
#include "cbbase.h"
#include "cbfio_base.h"
void savealldb();
void savedb_map(FILE *fp);
void savedb_item(FILE *fp);
void savedb_enemy(FILE *fp);
void loadalldb();

void savealldb(){
    FILE *fp_db=NULL;
    fp_db=fopen("cb.dat","wb");
    if(fp_db==NULL)return;
    savedb_map(fp_db);
    savedb_item(fp_db);
    savedb_enemy(fp_db);
    fclose(fp_db);
}
void savedb_map(FILE *fp){
    nat rmcount=0;
    for(nat i=0;roomdbs[i].id!=0;i++)rmcount++;
    int_fast32_t_write(rmcount,fp);
    for(nat i=0;roomdbs[i].id!=0;i++){
        int_fast32_t_write(roomdbs[i].id,fp);
        int_fast32_t_write((nat)roomdbs[i].region,fp);
        int_fast32_t_write((nat)wcslen(roomdbs[i].name),fp);
        wcs_write(roomdbs[i].name,wcslen(roomdbs[i].name),fp);
        int_fast32_t_write((nat)wcslen(roomdbs[i].desc),fp);
        wcs_write(roomdbs[i].desc,wcslen(roomdbs[i].desc),fp);
        int_fast32_t_write((nat)roomdbs[i].type,fp);
        for(nat j=0;j<6;j++)
            int_fast32_t_write(roomdbs[i].exits[j],fp);
        for(nat j=0;j<6;j++)
            int_fast32_t_write(roomdbs[i].exitsid[j],fp);
        for(nat j=0;j<32;j++)
            int_fast32_t_write(roomdbs[i].table[j],fp);
        for(nat j=0;j<4;j++)
            int_fast32_t_write(roomdbs[i].buff[j],fp);
    }
}
void savedb_item(FILE *fp){
    for(nat i=0;itemdbs[i].id!=0;i++){

    }
}
void savedb_enemy(FILE *fp){}

#endif
