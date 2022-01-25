#ifndef Corburt_Database_Item_h_Include_Guard
#define Corburt_Database_Item_h_Include_Guard
#include "cbbase.h"
void getitemname(nat id,wchar_t *itemname);
void getitemname(nat id,wchar_t *itemname){
    wchar_t *p;
    switch(id){
    case 0:
        p=L"(none)";
        break;
    default:
        p=L"undefined";
        break;
    }
    wcscpy(itemname,p);
}

enum db_itemtype{
    db_itemtype_weapon,
    db_itemtype_armor,
    db_itemtype_consume,
    db_itemtype_collect,
    db_itemtype_key,
    db_itemtype_misc
};
struct itemdb{
    nat id;
    enum db_itemtype type;
    nat price;
    nat cd; // ticks
    const wchar_t *name;
    const wchar_t *desc;
    struct {
        nat min_;
        nat max_;
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat stl;
        nat act;
        nat con;
        nat pts;
    } stats;
};
struct itemdb itemdbs[]={
    {
        .id=1,
        .type=db_itemtype_weapon,
        .price=5,
        .cd=5,
        .name=L"Wooden Stick",
        .desc=L"\"Now let's do it with a wooden stick!\"",
        .stats={.min_=2,.max_=3,.acc=10}
    },
    {
        .id=0
    }
};

struct itemdb *db_ifindwithid(nat itemid);
struct itemdb *db_ifindwithid(nat itemid){
    for(nat i=0;;i++){
        if(itemdbs[i].id==itemid){
            return &itemdbs[i];
            break;
        }
        if(itemdbs[i].id==0)break;
    }
    return NULL;
}
#endif
