#ifndef Corburt_Database_Entity_h_Include_Guard
#define Corburt_Database_Entity_h_Include_Guard
#include "cbbase.h"
#include "dbmap.h"
#include "dbenemy.h"
#define DBE_ENEMYCAP 64
#define DBE_ITEMCAP 32
#define DBE_INTCAP 16
struct et_room{
    nat id;
    nat etenemy[DBE_ENEMYCAP];
    nat etitem[DBE_ITEMCAP];
    nat etinteract[DBE_INTCAP];
};
struct et_room *et_rooms=NULL;
const nat roomsmax=sizeof(roomdbs)/sizeof(struct roomdb)-1;
struct et_enemy{
    foo available;
    nat roomid;
    nat enemyid;
    nat hp;
    real attackcd;
};
nat enemiescount=0;
nat enemiesmax=0;
nat enemypointer=0;
struct et_enemy *et_enemies=NULL;
struct et_item{
    foo available;
    nat roomid;
    nat itemid;
    nat qnty;
};
nat itemscount=0;
nat itemsmax=0;
nat itempointer=0;
struct et_item *et_items=NULL;

void setupentitydata();
struct et_room *et_findroomwithid(nat roomid);
void etenemy_expand();
void etenemy_push(nat enemyid,nat roomid);
const struct enemydb *et_getenemydb(nat enemyentityid);
void etitem_expand();
void etitem_push(nat itemid,nat qnty,nat roomid,nat purchase);
const struct itemdb *et_getitemdb(nat itementityid);
void et_spawnenemies();
void setupentitydata(){
    tracelog(Green,L"Setting up entity data...\n");
    tracelog(Green,L"Rooms count: %" PRIdFAST32 "\n",roomsmax);
    et_rooms=mallocpointer(roomsmax*sizeof(struct et_room));
    struct et_room etr={0};
    for(nat i=0;i<roomsmax;i++){
        et_rooms[i]=etr;
        et_rooms[i].id=roomdbs[i].id;
    }
    enemiesmax+=1024;
    et_enemies=mallocpointer(enemiesmax*sizeof(struct et_enemy));
    struct et_enemy ete={0};
    for(nat i=0;i<enemiesmax;i++){
        et_enemies[i]=ete;
        et_enemies[i].available=false;
    }
    itemsmax+=1024;
    et_items=mallocpointer(itemsmax*sizeof(struct et_item));
    struct et_item eti={0};
    for(nat i=0;i<itemsmax;i++){
        et_items[i]=eti;
        et_items[i].available=false;
    }

}
struct et_room *et_findroomwithid(nat roomid){
    for(nat i=0;i<roomsmax;i++){
        if(et_rooms[i].id==roomid)return &et_rooms[i];
    }
    return NULL;
}
void etenemy_expand(){
    tracelog(Green,L"Expanding enemy entity list...\n");
    enemiescount+=1024;
    et_enemies=reallocpointer(et_enemies,enemiescount*sizeof(struct et_enemy));
    struct et_enemy ete={0};
    for(nat i=enemiesmax-1024;i<enemiesmax;i++){
        et_enemies[i]=ete;
    }
}
void etenemy_push(nat enemyid,nat roomid){
    struct et_room *etr=NULL;
    const struct enemydb *edb=NULL;
    nat enemyreferenceindex=-1, // spawn in etr->etenemy[index]
        enemyentityindex=-1; // spawn in et_enemies[index]
    for(nat i=0;i<roomsmax;i++){
        if(et_rooms[i].id==roomid){
            etr=&et_rooms[i];
            break;
        }
    }
    if(etr==NULL){ // no such room
        printc(Red,msg_db_ridnullexceptionerror);
        return;
    }
    for(nat i=0;enemydbs[i].id!=0;i++){
        if(enemydbs[i].id==enemyid){
            edb=&enemydbs[i];
            break;
        }
    }
    if(edb==NULL){ // no such enemy
        printc(Red,msg_db_eidnullexceptionerror);
        return;
    }
    for(nat i=0;i<DBE_ENEMYCAP;i++){
        if(etr->etenemy[i]==0){
            enemyreferenceindex=i;
            break;
        }
    }
    if(enemyreferenceindex==-1){ // etr->etenemy[] is full
        return;
    }
    for(nat i=enemypointer;i<enemiesmax;i++){
        if(et_enemies[i].available==false){
            enemyentityindex=i;
            enemypointer=i+1;
            break;
        }
    }
    if(enemyentityindex==-1){ // et_enemies[] is full
        enemyentityindex=enemiesmax;
        etenemy_expand();
    }

    struct et_enemy ete={
        .available=true,
        .roomid=roomid,
        .enemyid=enemyid,
        .hp=edb->stats.hpmax,
        .attackcd=0.0f
    };
    et_enemies[enemyentityindex]=ete;
    etr->etenemy[enemyreferenceindex]=enemyentityindex+1;
    enemiescount++;
    tracelog(Cyan,L"Pushing enemy entity: entityid=%d (enemyid=%d, roomid=%d)\n",(int)enemyentityindex+1,(int)enemyid,(int)roomid);
}
const struct enemydb *et_getenemydb(nat enemyentityid){
    if(et_enemies[enemyentityid-1].available==false){
        printc(Red,msg_db_eetidnullexceptionerror);
        return NULL;
    }
    const struct enemydb *edb=db_efindwithid(et_enemies[enemyentityid-1].enemyid);
    return edb;
}
void etitem_expand(){
    tracelog(Green,L"Expanding item entity list...\n");
    itemscount+=1024;
    et_items=reallocpointer(et_items,itemscount*sizeof(struct et_item));
    struct et_item eti={0};
    for(nat i=itemsmax-1024;i<itemsmax;i++){
        et_items[i]=eti;
    }
}
void etitem_push(nat itemid,nat qnty,nat roomid,nat purchase){
    struct et_room *etr=NULL;
    const struct itemdb *idb=NULL;
    nat itemreferenceindex=-1, // spawn in etr->etitem[index]
        itementityindex=-1; // spawn in et_items[index]
    if(roomid!=0){
        for(nat i=0;i<roomsmax;i++){
            if(et_rooms[i].id==roomid){
                etr=&et_rooms[i];
                break;
            }
        }
        if(etr==NULL){ // no such room
            printc(Red,msg_db_ridnullexceptionerror);
            return;
        }
    }
    for(nat i=0;itemdbs[i].id!=0;i++){
        if(itemdbs[i].id==itemid){
            idb=&itemdbs[i];
            break;
        }
    }
    if(idb==NULL){
        printc(Red,msg_db_iidnullexceptionerror);
        return;
    }
    nat stackable=idb->type&db_itemtype_stackable_mask;
    for(nat i=itempointer;i<itemsmax;i++){
        if(et_items[i].available==false){
            itementityindex=i;
            itempointer=i+1;
            break;
        }
    }
    if(itementityindex==-1){
        itementityindex=itemsmax;
        etitem_expand();
    }
    if(roomid!=0){ // add into room
        if(!stackable){
            for(nat i=0;i<DBE_ITEMCAP;i++){
                if(etr->etitem[i]==0){
                    itemreferenceindex=i;
                    break;
                }
            }
            if(itemreferenceindex==-1){ // etr->etitem[] is full
                return;
            }
            struct et_item eti={
                .available=true,
                .roomid=roomid,
                .itemid=itemid,
                .qnty=1
            };
            et_items[itementityindex]=eti;
            if(roomid!=0)etr->etitem[itemreferenceindex]=itementityindex+1;
            itemscount++;
        }
        else{}
    }
    else{ // add item into inventory
        if(!stackable){
            foo success=false;
            for(nat i=0;i<inventory.unlocked;i++){
                if(inventory.items[i]==0){
                    struct et_item eti={
                        .available=true,
                        .roomid=0,
                        .itemid=itemid,
                        .qnty=1
                    };
                    et_items[itementityindex]=eti;
                    inventory.items[i]=itementityindex+1;
                    itemscount++;
                    if(purchase){
                        inventory.money-=idb->price;
                        printc(Default,msg_db_iobtainitemhint,idb->name);
                    }
                    success=true;
                    break;
                }
            }
            if(!success)printc(Default,msg_db_icantcarry);
        }
        else{}
    }
    tracelog(Cyan,L"Pushing item entity: entityid=%d (itemid=%d, roomid=%d)\n",(int)itementityindex+1,(int)itemid,(int)roomid);
}
const struct itemdb *et_getitemdb(nat itementityid){
    if(et_items[itementityid-1].available==false){
        printc(Red,msg_db_ietidnullexceptionerror);
        return NULL;
    }
    const struct itemdb *idb=db_ifindwithid(et_items[itementityid-1].itemid);
    return idb;
}
void et_spawnenemies(){
    for(nat i=0;roomdbs[i].id!=0;i++){
        if(roomdbs[i].type!=db_roomtype_plain)continue;
        if(roomdbs[i].table[0]==0)continue;
        for(nat j=0;roomdbs[i].table[j]!=0;j++){
            etenemy_push(roomdbs[i].table[j],roomdbs[i].id);
        }
    }
}
#endif
