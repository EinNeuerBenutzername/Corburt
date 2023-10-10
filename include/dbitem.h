#ifndef Corburt_Database_Item_h_Include_Guard
#define Corburt_Database_Item_h_Include_Guard
#define ITEM_MAXSTACK 16
#define ITEM_SELLRATE 0.5f
#include "cbbase.h"
#include "cbplayer.h"

itemdb *db_ifindwithid(int itemid){
    if(itemdbs[itemid-1].id==itemid)return &itemdbs[itemid-1];
    for(int i=0;; i++){
        if(itemdbs[i].id==itemid){
            return &itemdbs[i];
            break;
        }
        if(itemdbs[i].id==0)break;
    }
    return NULL;
}
void getitemname(int id, char *itemname){
    const char *p;
    switch(id){
    case 0:
        p="(none)";
        break;
    default:;
        itemdb *idb=db_ifindwithid(id);
        if(idb==NULL){
            printf("\n");
            warn(msg->db_iidnullexceptionerror);
            p="undefined";
            break;
        }
        p=idb->name;
        break;
    }
    strcpy(itemname, p);
}
void consumeitem(int itemid){
    itemdb *idb=db_ifindwithid(itemid);
    int range=idb->stats.max_-idb->stats.min_;
    int regennum=idb->stats.min_;
    if(range<0){
        range=1-range;
        regennum=genRandLong(&mtrand)%range+idb->stats.max_;
    }else{
        range++;
        regennum=genRandLong(&mtrand)%range+idb->stats.min_;
    }
    phpchange(regennum);
    pcalcstats();
}
#endif
