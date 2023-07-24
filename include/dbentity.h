#ifndef Corburt_Database_Entity_h_Include_Guard
#define Corburt_Database_Entity_h_Include_Guard
#include "cbbase.h"
#include "dbitem.h"
#include "dbmap.h"
#include "dbenemy.h"
#define DBE_ENEMYCAP 64
#define DBE_ITEMCAP 32
#define DBE_INTERCAP 16
#define DBE_EXPANDSTEP 64
#define DBE_TRACELOG 1
struct et_room{
    nat id;
    nat money;
    nat etenemy[DBE_ENEMYCAP];
    nat etitem[DBE_ITEMCAP];
    nat etinteract[DBE_INTERCAP];
};
struct et_room *et_rooms=NULL;
struct et_enemy{
    foo available;
    nat roomid;
    nat enemyid;
    nat hp;
    nat attackcd;
    nat breach;
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
void etenemy_attack(nat etid,struct et_room *etr);
void etenemy_takedamage(nat entityid,nat dmg);
void etenemy_die(nat entityid);
void etenemy_deathdrops(enemydb *edb,nat roomid);
void etenemy_list();
enemydb *et_getenemydb(nat enemyentityid);
void etitem_expand();
void etitem_delete(nat entityid);
void etitem_rebind(nat entityid,nat newroomid);
void etitem_push(nat itemid,nat qnty,nat roomid,nat purchase);
itemdb *et_getitemdb(nat itementityid);
void et_initenemies();
void et_spawnenemies();

void setupentitydata(){
    if(DBE_TRACELOG)tracelog("Setting up entity data...\n");
    if(DBE_TRACELOG)tracelog("Rooms count: %" PRIdFAST32 "\n",roomdbsize);
    et_rooms=mallocpointer(roomdbsize*sizeof(struct et_room));
    struct et_room etr={0};
    for(nat i=0;i<roomdbsize;i++){
        et_rooms[i]=etr;
        et_rooms[i].id=roomdbs[i].id;
    }
    enemiesmax+=DBE_EXPANDSTEP;
    et_enemies=mallocpointer(enemiesmax*sizeof(struct et_enemy));
    struct et_enemy ete={0};
    for(nat i=0;i<enemiesmax;i++){
        et_enemies[i]=ete;
        et_enemies[i].available=false;
    }
    itemsmax+=DBE_EXPANDSTEP;
    et_items=mallocpointer(itemsmax*sizeof(struct et_item));
    struct et_item eti={0};
    for(nat i=0;i<itemsmax;i++){
        et_items[i]=eti;
        et_items[i].available=false;
    }

}
struct et_room *et_findroomwithid(nat roomid){
    for(nat i=0;i<roomdbsize;i++){
        if(et_rooms[i].id==roomid)return &et_rooms[i];
    }
    return NULL;
}
void etenemy_expand(){
    if(DBE_TRACELOG)tracelog("Expanding enemy entity list... (%" PRIdFAST32 "->%" PRIdFAST32 ")\n",enemiesmax,enemiesmax+DBE_EXPANDSTEP);
    enemiesmax+=DBE_EXPANDSTEP;
    et_enemies=reallocpointer(et_enemies,enemiesmax*sizeof(struct et_enemy));
    struct et_enemy ete={0};
    for(nat i=enemiesmax-DBE_EXPANDSTEP;i<enemiesmax;i++){
        et_enemies[i]=ete;
    }
}
void etenemy_push(nat enemyid,nat roomid){
    struct et_room *etr=NULL;
    enemydb *edb=NULL;
    nat enemyreferenceindex=-1, // spawn in etr->etenemy[index]
        enemyentityindex=-1; // spawn in et_enemies[index]
    for(nat i=0;i<roomdbsize;i++){
        if(et_rooms[i].id==roomid){
            etr=&et_rooms[i];
            break;
        }
    }
    if(etr==NULL){ // no such room
        warn(msg->db_ridnullexceptionerror);
        return;
    }
    for(nat i=0;enemydbs[i].id!=0;i++){
        if(enemydbs[i].id==enemyid){
            edb=&enemydbs[i];
            break;
        }
    }
    if(edb==NULL){ // no such enemy
        warn(msg->db_eidnullexceptionerror);
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
        enemypointer=enemiesmax;
        etenemy_expand();
    }

    struct et_enemy ete={
        .available=true,
        .roomid=roomid,
        .enemyid=enemyid,
        .hp=edb->stats.hpmax,
        .attackcd=genRandLong(&mtrand)%8+1,
    };
    et_enemies[enemyentityindex]=ete;
    etr->etenemy[enemyreferenceindex]=enemyentityindex+1;
    enemiescount++;
    if(DBE_TRACELOG)tracelog("Create enemy entity: entityid=%d (enemyid=%d, roomid=%d)\n",(int)enemyentityindex+1,(int)enemyid,(int)roomid);
}
void etenemy_attack(nat etid,struct et_room *etr){
    struct et_enemy *ete=&et_enemies[etid-1];
    if(ete->available==false){
        warn(msg->db_eetidnullexceptionerror);
        return;
    }
    if(ete->attackcd>0)return;
    enemydb *edb=et_getenemydb(etid);
    if(edb==NULL){
        warn(msg->db_eetidnullexceptionerror);
        return;
    }
    if(edb->loot.weapon){
        itemdb *idb=db_ifindwithid(edb->loot.weapon);
        if(idb==NULL){
            warn(msg->db_ietidnullexceptionerror);
            return;
        }
        ete->attackcd=idb->cd;
    }else ete->attackcd=30;
    if(pcandodge(edb)){
        printr(palette.enemy.miss,msg->db_eetattackmiss,edb->name);
    }
    else{
        nat atk=edb->stats.atk;
        nat dmgcolor=palette.value.plain;
        if(edb->loot.armor)atk+=db_ifindwithid(edb->loot.armor)->stats.atk;
        if(edb->loot.weapon){
            itemdb *idb=db_ifindwithid(edb->loot.weapon);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
                return;
            }
            atk+=idb->stats.atk;
            nat atk2=atk;
            atk*=DMG_RATIO;
            atk+=idb->stats.min_;
            nat delta=idb->stats.max_-idb->stats.min_;
            if(delta<0)delta=0-delta;
            if(delta)atk+=genRandLong(&mtrand)%delta;
            atk+=critdmg(idb->crit,atk2,idb->stats.max_,&dmgcolor);
        }
        nat dmg=dmgreduc(atk,cbp.calcstats.def*DMG_RATIO);
        if(dmg){
            printr(palette.enemy.strike,msg->db_eetattack1,edb->name);
            printr(dmgcolor,msg->db_eetattack2,dmg);
            printr(palette.enemy.strike,msg->db_eetattack3);
        }
        else printr(palette.enemy.blocked,msg->db_eetattackblocked,edb->name);
        ptakedmg(dmg);
    }
}
void etenemy_takedamage(nat entityid,nat dmg){
    struct et_enemy *ete=&et_enemies[entityid-1];
    if(ete==NULL){
        warn(msg->db_eetidnullexceptionerror);
        return;
    }
    if(dmg>=ete->hp){
        ete->hp=0;
        etenemy_die(entityid);
    }else{
        ete->hp-=dmg;
    }
}
void etenemy_die(nat entityid){
    struct et_enemy *ete=&et_enemies[entityid-1];
    enemydb *edb=db_efindwithid(ete->enemyid);
    if(!ete->available){
        warn(msg->db_eetidnullexceptionerror);
        return;
    }
    struct et_room *etr=et_findroomwithid(ete->roomid);
    if(etr==NULL){
        warn(msg->db_retidnullexceptionerror);
        return;
    }
    for(nat i=0;i<DBE_ENEMYCAP;i++){
        if(etr->etenemy[i]==entityid){
            etr->etenemy[i]=0;
            break;
        }
    }
    etenemy_deathdrops(edb,ete->roomid);
    {
        ete->available=false;
        ete->attackcd=0;
        ete->enemyid=0;
        ete->roomid=0;
        ete->hp=0;
        enemiescount--;
        if(enemypointer>=entityid)enemypointer=entityid-1;
        if(DBE_TRACELOG)tracelog("Enemy entity #%" PRIdFAST32 " deleted.\n",entityid);
    }
}
void etenemy_deathdrops(enemydb *edb,nat roomid){
    printr(palette.enemy.die,msg->db_eetdie,edb->name);
    player.exp+=edb->exp;
    printr(palette.enemy.reward,msg->db_eetdieexp,edb->exp);
    { // money drops
        nat money=edb->loot.moneymin;
        nat delta=edb->loot.moneymax-edb->loot.moneymin;
        if(delta<0)delta=0-delta;
        if(delta>0){
            money+=genRandLong(&mtrand)%delta;
        }
        if(money>0){
            struct et_room *etr=et_findroomwithid(roomid);
            if(!etr){
                warn(msg->db_retidnullexceptionerror);
                return;
            }
            etr->money+=money;
            printr(palette.enemy.reward,msg->db_retmoneydrop,money);
        }
    }
    { // gear drops
//        if(edb->loot.weapon){
//            if(genRandLong(&mtrand)%10000<300){
//                etitem_push(edb->loot.weapon,1,roomid,0);
//                printr(palette.enemy.reward,msg->db_retitemdrop,db_ifindwithid(edb->loot.weapon)->name);
//            }
//        }
//        if(edb->loot.armor){
//            if(genRandLong(&mtrand)%10000<300){
//                etitem_push(edb->loot.armor,1,roomid,0);
//                printr(palette.enemy.reward,msg->db_retitemdrop,db_ifindwithid(edb->loot.armor)->name);
//            }
//        }
    }
    if(edb->loot.drops[0].itemid){ // item drops
        for(nat i=0;i<ENEMY_MAXDROPS;i++){
            if(edb->loot.drops[i].itemid==0)break;
            if(genRandLong(&mtrand)%10000<edb->loot.drops[i].rate){
                etitem_push(edb->loot.drops[i].itemid,1,roomid,0);
                printr(palette.enemy.reward,msg->db_retitemdrop,db_ifindwithid(edb->loot.drops[i].itemid)->name);
            }
        }
    }
}
enemydb *et_getenemydb(nat enemyentityid){
    if(et_enemies[enemyentityid-1].available==false){
        warn(msg->db_eetidnullexceptionerror);
        return NULL;
    }
    enemydb *edb=db_efindwithid(et_enemies[enemyentityid-1].enemyid);
    return edb;
}
void etitem_expand(){
    if(DBE_TRACELOG)tracelog("Expanding item entity list... (%" PRIdFAST32 "->%" PRIdFAST32 ")\n",itemsmax,itemsmax+DBE_EXPANDSTEP);
    itemsmax+=DBE_EXPANDSTEP;
    et_items=reallocpointer(et_items,itemsmax*sizeof(struct et_item));
    struct et_item eti={0};
    for(nat i=itemsmax-DBE_EXPANDSTEP;i<itemsmax;i++){
        et_items[i]=eti;
    }
}
void etitem_delete(nat entityid){
    struct et_item *eti=&et_items[entityid-1];
    if(!eti->available){
        warn(msg->db_ietidnullexceptionerror);
        return;
    }
    if(eti->roomid!=0){
        struct et_room *etr=et_findroomwithid(eti->roomid);
        if(etr==NULL){
            warn(msg->db_retidnullexceptionerror);
            return;
        }
        for(nat i=0;i<DBE_ITEMCAP;i++){
            if(etr->etitem[i]==entityid){
                etr->etitem[i]=0;
                break;
            }
        }
    }
    else{
        nat invindex=-1;
        for(nat i=0;i<inventory.unlocked;i++){
            if(inventory.items[i]==entityid){
                inventory.items[i]=0;
                invindex=i;
                break;
            }
        }
        if(inventory.weapon==invindex+1){
            inventory.weapon=0;
        }
        if(inventory.armor==invindex+1){
            inventory.armor=0;
        }
        for(nat i=0;i<5;i++){
            if(inventory.accessories[i]==invindex+1){
                inventory.accessories[i]=0;
                break;
            }
        }
    }
    eti->available=false;
    eti->roomid=0;
    eti->itemid=0;
    eti->qnty=0;
    if(itempointer>=entityid)itempointer=entityid-1;
    if(DBE_TRACELOG)tracelog("Item entity #%" PRIdFAST32 " deleted.\n",entityid);
}
void etitem_rebind(nat entityid,nat newroomid){
    struct et_item *eti=&et_items[entityid-1];
    struct et_item etio=et_items[entityid-1];
    if(!eti->available){
        warn(msg->db_ietidnullexceptionerror);
        return;
    }
    etitem_delete(entityid);
    etitem_push(etio.itemid,etio.qnty,newroomid,0);
}
void etitem_push(nat itemid,nat qnty,nat roomid,nat purchase){
    if(qnty<=0)return; //
    foo success=false;
    struct et_room *etr=NULL;
    itemdb *idb=NULL;
    nat itemreferenceindex=-1, // spawn in etr->etitem[index]
        itementityindex=-1; // spawn in et_items[index]
    if(roomid!=0){
        for(nat i=0;i<roomdbsize;i++){
            if(et_rooms[i].id==roomid){
                etr=&et_rooms[i];
                break;
            }
        }
        if(etr==NULL){ // no such room
            warn(msg->db_ridnullexceptionerror);
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
        warn(msg->db_iidnullexceptionerror);
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
        if(!(idb->type&db_itemtype_stackable_mask))itempointer=itemsmax;
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
                printr(palette.item.gone,msg->db_ietfull,db_ifindwithid(itemid)->name);
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
            success=true;
        }
        else{
            foo hasslot=false;
            if(qnty>ITEM_MAXSTACK)qnty=ITEM_MAXSTACK;
            for(nat i=0;i<DBE_ITEMCAP;i++){
                if(etr->etitem[i]==0){hasslot=true;continue;}
                struct et_item *eti=&et_items[etr->etitem[i]-1];
                if(eti->itemid!=itemid)continue;
                if(eti->qnty==ITEM_MAXSTACK)continue;
                if(eti->qnty>ITEM_MAXSTACK){eti->qnty=ITEM_MAXSTACK;continue;}
                if(eti->qnty+qnty<=ITEM_MAXSTACK){
                    eti->qnty+=qnty;
                    qnty=0;
                    itementityindex--;
                    itempointer--;
                    success=true;
                    break;
                }
                else{
                    qnty-=ITEM_MAXSTACK-eti->qnty;
                    eti->qnty=ITEM_MAXSTACK;
                }
            }
            if((!success)&&hasslot){
                for(nat i=0;i<DBE_ITEMCAP;i++){
                    if(etr->etitem[i]==0){
                        struct et_item eti={
                            .available=true,
                            .roomid=roomid,
                            .itemid=itemid,
                            .qnty=qnty
                        };
                        et_items[itementityindex]=eti;
                        etr->etitem[i]=itementityindex+1;
                        itemscount++;
                        success=true;
                        break;
                    }
                }
            }
            else if((!success)&&(!hasslot)){
                printr(palette.item.gone,msg->db_ietfull,idb->name);
            }
            else if(success){
                itempointer--;
            }
        }
    }
    else{ // add item into inventory
        if(!stackable){
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
                        printr(palette.msg,msg->db_ipurchaseitemhint,idb->name);
                    }
                    success=true;
                    break;
                }
            }
            if(!success){ // drops to the ground
                printr(palette.promptfail,msg->db_icantcarry);
                if(!purchase)etitem_push(itemid,qnty,player.roomid,0);
            }
            else if(success){
                itempointer--;
            }
        }
        else{
            nat qnty2=qnty;
            foo hasslot=false;
            if(qnty>ITEM_MAXSTACK)qnty=ITEM_MAXSTACK;
            for(nat i=0;i<inventory.unlocked&&qnty>0;i++){
                if(inventory.items[i]==0){hasslot=true;continue;}
                struct et_item *eti=&et_items[inventory.items[i]-1];
                if(eti->itemid!=itemid)continue;
                if(eti->qnty==ITEM_MAXSTACK)continue;
                if(eti->qnty>ITEM_MAXSTACK){eti->qnty=ITEM_MAXSTACK;continue;}
                if(eti->qnty+qnty<=ITEM_MAXSTACK){
                    eti->qnty+=qnty;
                    qnty=0;
                    itempointer--;
                    itementityindex--;
                    success=true;
                    break;
                }
                else{
                    qnty-=ITEM_MAXSTACK-eti->qnty;
                    eti->qnty=ITEM_MAXSTACK;
                }
            }
            if((!success)&&hasslot){
                for(nat i=0;i<inventory.unlocked;i++){
                    if(inventory.items[i]==0){
                        struct et_item eti={
                            .available=true,
                            .roomid=0,
                            .itemid=itemid,
                            .qnty=qnty
                        };
                        et_items[itementityindex]=eti;
                        inventory.items[i]=itementityindex+1;
                        itemscount++;
                        success=true;
                        qnty=0;
                        break;
                    }
                }
            }
            else if((!success)&&(!hasslot)){ // drops to the ground
                printr(palette.promptfail,msg->db_icantcarry);
                if(!purchase)etitem_push(itemid,qnty,player.roomid,0);
            }
            if(purchase&&qnty2>qnty){
                inventory.money-=idb->price*(qnty2-qnty);
                printr(palette.promptfail,msg->db_ipurchasemultitemhint,idb->name,(qnty2-qnty));
            }
            qnty=qnty2;
        }
    }
    if(!success)itempointer--;
    if(DBE_TRACELOG)tracelog("Create item entity: entityid=%d (qnty=%d, itemid=%d, roomid=%d) %s\n",(int)itementityindex+1,(int)qnty,(int)itemid,(int)roomid,success?"":"fail");
}
itemdb *et_getitemdb(nat itementityid){
    if(et_items[itementityid-1].available==false){
        warn(msg->db_ietidnullexceptionerror);
        return NULL;
    }
    itemdb *idb=db_ifindwithid(et_items[itementityid-1].itemid);
    return idb;
}
void et_initenemies(){
    for(nat i=0;i<roomdbsize;i++){
        if(roomdbs[i].type!=db_roomtype_plain)continue;
        if(roomdbs[i].table[0]==0)continue;
        struct et_room *etr=et_findroomwithid(roomdbs[i].id);
        nat roomenemytablesize=0;
        for(nat j=0;roomdbs[i].table[j]!=0;j++)roomenemytablesize++;
        for(nat j=0,c=0;j<DBE_ENEMYCAP;j++){
            if(etr->etenemy[j]!=0)c++;
            if(j==DBE_ENEMYCAP-1&&c>=roomenemytablesize)return;
        }
        for(nat j=0;j<roomenemytablesize;j++){
            etenemy_push(roomdbs[i].table[j],roomdbs[i].id);
        }
    }
}
void et_spawnenemies(){
    for(nat i=0;i<roomdbsize;i++){
        if(roomdbs[i].type!=db_roomtype_plain)continue;
        if(roomdbs[i].table[0]==0)continue;
        struct et_room *etr=et_findroomwithid(roomdbs[i].id);
        nat roomenemytablesize=0;
        for(nat j=0;roomdbs[i].table[j]!=0;j++)roomenemytablesize++;
        for(nat j=0,c=0;j<DBE_ENEMYCAP;j++){
            if(etr->etenemy[j]!=0)c++;
            if(j==DBE_ENEMYCAP-1&&c>=roomenemytablesize)continue; // no need to spawn enemies
        }
        nat enemytable[DBE_ENEMYCAP]={0};
        for(nat j=0;j<roomenemytablesize;j++){
            enemytable[j]=roomdbs[i].table[j];
        }
        for(nat j=0;j<DBE_ENEMYCAP;j++){
            if(etr->etenemy[j]==0)continue;
            for(nat k=0;k<roomenemytablesize;k++){
                if(enemytable[k]==et_enemies[etr->etenemy[j]-1].enemyid){
                    enemytable[k]=0;
                    break;
                }
            }
        }
        for(nat j=0;j<roomenemytablesize;j++){
            if(enemytable[j]==0)continue;
            if(roomdbs[i].id==player.roomid){
                enemydb *dbe=db_efindwithid(enemytable[j]);
                printr(palette.enemy.spawn,msg->db_eetenterroom,dbe->name);
            }
            etenemy_push(enemytable[j],roomdbs[i].id);
            break;
        }
    }
}
#endif
