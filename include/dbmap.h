#ifndef Corburt_Database_Map_h_Include_Guard
#define Corburt_Database_Map_h_Include_Guard
#include "cbbase.h"
enum db_regionthreat{
    db_regionthreat_none,
    db_regionthreat_low,
    db_regionthreat_moderate,
    db_regionthreat_substantial,
    db_regionthreat_severe,
    db_regionthreat_critical,
    db_regionthreat_extirpative
};
typedef struct {
    nat region;
    wchar_t *name;
    nat threat;
    nat sentinel[32];
} regiondb;
regiondb regiondbs[]={
    {.region=db_roomregion_nlcity,
        .name=L"Nameless City",
        .threat=db_regionthreat_low,
    },
    {.region=db_roomregion_forest,
        .name=L"Forest of Wrath",
        .threat=db_regionthreat_moderate,
    },
};

#include "dbentity.h"

roomdb *db_rfindwithid(nat roomid);
void db_rshowdesc(nat roomid);
void db_rshowtable(nat roomid);
regiondb *db_rgfindwithregion(nat region);
void db_rgshowdesc(nat region);
roomdb *db_rfindwithid(nat roomid){
    for(nat i=0;i<roomdbsize;i++){
        if(roomdbs[i].id==roomid){
            return &roomdbs[i];
            break;
        }
        if(roomdbs[i].id==0)break;
    }
    return NULL;
}
void db_rshowdesc(nat roomid){
    roomdb *rm=db_rfindwithid(roomid);
    if(rm==NULL){
        printr(Red,msg->db_ridnullexceptionerror);
        return;
    }
    printr(White|Bright,L"\n%ls\n",rm->name);
    printr(Cyan|Bright,L"%ls\n",rm->desc);
    printr(Green|Bright,L"exits: ");
    if(rm->exits[dir_North])printr(Green|Bright,L"NORTH  ");
    if(rm->exits[dir_East])printr(Green|Bright,L"EAST  ");
    if(rm->exits[dir_South])printr(Green|Bright,L"SOUTH  ");
    if(rm->exits[dir_West])printr(Green|Bright,L"WEST  ");
    struct et_room *etr=et_findroomwithid(roomid);
    if(etr==NULL){
        printr(Red,msg->db_retidnullexceptionerror);
    }
    else{
        for(nat i=0,first=1;i<DBE_ENEMYCAP;i++){ // enemies:
            if(etr->etenemy[i]!=0){
                enemydb *edb=et_getenemydb(etr->etenemy[i]);
                if(first){
                    printr(Red|Bright,L"\nenemies: %ls",edb->name);
                }else{
                    printr(Red|Bright,L", %ls",edb->name);
                }
                first=0;
            }
        }
        for(nat i=0,first=1;i<DBE_ITEMCAP;i++){ // items:
            if(etr->etitem[i]!=0){
                struct et_item *eti=&et_items[etr->etitem[i]-1];
                if(eti->available==false){
                    printr(Red,msg->db_ietidnullexceptionerror);
                    continue;
                }
                itemdb *idb=db_ifindwithid(eti->itemid);
                if(idb==NULL){
                    printr(Red,msg->db_iidnullexceptionerror);
                    continue;
                }
                if(first){
                    if(!(idb->type&db_itemtype_stackable_mask))printr(Yellow|Bright,L"\nitems: %ls",idb->name,etr->etitem[i]);
                    else{
                        if(eti->qnty==1)printr(Yellow|Bright,L"\nitems: %ls",idb->name);
                        else printr(Yellow|Bright,L"\nitems: %ls (x%" PRIdFAST32 ")",idb->name,eti->qnty);
                    }
                }else{
                    if(!(idb->type&db_itemtype_stackable_mask))printr(Yellow|Bright,L", %ls",idb->name,etr->etitem[i]);
                    else{
                        if(eti->qnty==1)printr(Yellow|Bright,L", %ls",idb->name);
                        else printr(Yellow|Bright,L", %ls (x%" PRIdFAST32 ")",idb->name,eti->qnty);
                    }
                }
                first=0;
            }
//            if(i==DBE_ITEMCAP-1&&first==0)printf("\n");
        }
        if(etr->money){ // money:
            printc(Yellow|Bright,L"\nmoney: $%" PRIdFAST32,etr->money);
        }
    }
    printr(Default,L"\n\n");
}
void db_rshowtable(nat roomid){
    roomdb *rm=db_rfindwithid(roomid);
    if(rm==NULL){
        printr(Red,msg->db_ridnullexceptionerror);
        return;
    }
    if(rm->type!=db_roomtype_shop){
        printr(Default,msg->db_notinstore);
        return;
    }
    printr(Default,msg->line);
    for(nat i=0;i<32;i++){
        if(rm->table[i]!=0){
            itemdb *idb=db_ifindwithid(rm->table[i]);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return;
            }
            printrp(Default,L"            | ",msg->db_listitem,idb->price,idb->name);
        }else break;
    }
    printr(Default,msg->line);
}
regiondb *db_rgfindwithregion(nat region){
    for(nat i=0;i<2;i++){
        if(regiondbs[i].region==region){
            return &regiondbs[i];
            break;
        }
    }
    return NULL;
}
#endif
