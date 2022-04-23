#ifndef Corburt_Database_Item_h_Include_Guard
#define Corburt_Database_Item_h_Include_Guard
#define ITEM_MAXSTACK 64
#define ITEM_SELLRATE 0.9f
#include "cbbase.h"
#include "cbplayer.h"

enum db_itemtype{
    db_itemtype_stackable_mask=16,
    db_itemtype_weapon=0,
    db_itemtype_armor=2,
    db_itemtype_accessory=3,
    db_itemtype_key=4,
    db_itemtype_consume=0|db_itemtype_stackable_mask, // stackable
    db_itemtype_collect=1|db_itemtype_stackable_mask, // stackable
    db_itemtype_misc=2|db_itemtype_stackable_mask, // stackable
};
typedef const struct{
    nat id;
    enum db_itemtype type;
    nat price;
    nat cd;
    nat crit;
    wchar_t *name;
    wchar_t *desc;
    struct {
        nat min_;
        nat max_;
        nat regen;
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat wis;
        nat act;
        nat con;
        nat pts;
    } stats;
} itemdb;
itemdb itemdbs[]={
    {.id=1,.name=L"Wooden Stick",
        .type=db_itemtype_weapon,
        .price=5,
        .cd=45,
        .desc=L"\"Now let's do it with a wooden stick!\"",
        .stats={.min_=1,.max_=3,.acc=-5}
    },
    {.id=2,.name=L"Rusty Knife",
        .type=db_itemtype_weapon,
        .price=5,
        .cd=30,
        .desc=L"A simple rusty knife. What do you expect?",
        .stats={.min_=1,.max_=3,.acc=3}
    },
    {.id=3,.name=L"Stiletto",
        .type=db_itemtype_weapon,
        .price=15,
        .cd=42,
        .desc=L"Born for stabbing.",
        .stats={.min_=1,.max_=5,.acc=5}
    },
    {.id=4,.name=L"Iron Shortsword",
        .type=db_itemtype_weapon,
        .price=30,
        .cd=72,
        .desc=L"Classic newbie weapon.",
        .stats={.min_=4,.max_=6,.acc=3}
    },
    {.id=5,.name=L"Vicious Stiletto",
        .type=db_itemtype_weapon,
        .price=50,
        .cd=24,
        .crit=500,
        .desc=L"Specially enhanced for your stabbing pleasure...",
        .stats={.min_=1,.max_=7,.acc=13}
    },
    {.id=6,.name=L"Knife",
        .type=db_itemtype_weapon,
        .price=18,
        .cd=42,
        .desc=L"Designed to cut things, not people.",
        .stats={.min_=2,.max_=5,.acc=4}
    },
    {.id=7,.name=L"Rusty Sword",
        .type=db_itemtype_weapon,
        .price=40,
        .cd=32,
        .crit=500,
        .desc=L"Occasionally reveals its power.",
        .stats={.min_=1,.max_=7}
    },
    {.id=8,.name=L"Tiny Green Leaf",
        .type=db_itemtype_consume,
        .price=1,
        .desc=L"Sprout of some exotic plant.",
        .stats={.min_=1,.max_=2}
    },
    {.id=9,.name=L"Small Green Leaf",
        .type=db_itemtype_consume,
        .price=3,
        .desc=L"Young leaves of some exotic plant.",
        .stats={.min_=2,.max_=4}
    },
    {.id=10,.name=L"Immature Green Leaf",
        .type=db_itemtype_consume,
        .price=8,
        .desc=L"Immature leaves of some exotic plant.",
        .stats={.min_=5,.max_=12}
    },
    {.id=11,.name=L"Green Leaf",
        .type=db_itemtype_consume,
        .price=13,
        .desc=L"Leaves of some exotic plant.",
        .stats={.min_=13,.max_=20}
    },
    {.id=12,.name=L"Large Green Leaf",
        .type=db_itemtype_consume,
        .price=21,
        .desc=L"Larger leaves of some exotic plant.",
        .stats={.min_=15,.max_=35}
    },
    {.id=13,.name=L"Huge Green Leaf",
        .type=db_itemtype_consume,
        .price=53,
        .desc=L"Huge leaves of some exotic plant.",
        .stats={.min_=30,.max_=55}
    },
    {.id=14,.name=L"Enormous Green Leaf",
        .type=db_itemtype_consume,
        .price=96,
        .desc=L"Enormous leaves of some exotic plant.",
        .stats={.min_=65,.max_=115}
    },
    {.id=15,.name=L"Tremendous Green Leaf",
        .type=db_itemtype_consume,
        .price=134,
        .desc=L"Tremendous leaves of some exotic plant.",
        .stats={.min_=175,.max_=255}
    },
    {.id=16,.name=L"Thin Cloth Armor",
        .type=db_itemtype_armor,
        .price=20,
        .desc=L"Basically, it's plain clothes.",
        .stats={.dod=8,.acc=5}
    },
    {.id=17,.name=L"Leather Armor",
        .type=db_itemtype_armor,
        .price=40,
        .desc=L"Pig skin, stronger than most people's.",
        .stats={.def=2,.dod=4,.acc=5}
    },
    {.id=18,.name=L"Chain Shirt",
        .type=db_itemtype_armor,
        .price=75,
        .desc=L"Do you feel chained?",
        .stats={.def=5,.dod=2,.acc=9}
    },
    {.id=19,.name=L"Hide",
        .type=db_itemtype_armor,
        .price=35,
        .desc=L"Pig skin, stronger than most pigs'.",
        .stats={.def=4,.dod=-2,.acc=2}
    },
    {.id=20,.name=L"Scalemail Armor",
        .type=db_itemtype_armor,
        .price=85,
        .desc=L"They're like flappy wings!",
        .stats={.def=7,.dod=-3,.act=-3,.acc=5}
    },
    {.id=21,.name=L"Chainmail Armor",
        .type=db_itemtype_armor,
        .price=185,
        .desc=L"\"The more you tank\"",
        .stats={.def=9,.dod=-5,.acc=4}
    },
    {.id=22,.name=L"Breastplate Armor",
        .type=db_itemtype_armor,
        .price=290,
        .desc=L"\"The less you dodge\"",
        .stats={.def=12,.dod=-8,.acc=1}
    },
    {.id=23,.name=L"Platemail Armor",
        .type=db_itemtype_armor,
        .price=400,
        .desc=L"Only the weak dodges.",
        .stats={.def=15,.dod=-13,.acc=-1}
    },
    {.id=24,.name=L"Full Platemail Armor",
        .type=db_itemtype_armor,
        .price=650,
        .desc=L"Dodging? What's that?",
        .stats={.def=20,.dod=-16,.acc=-3}
    },
    {.id=25,.name=L"Necklace of Slight Regeneration",
        .type=db_itemtype_accessory,
        .price=75,
        .desc=L"It's... Blue?",
        .stats={.regen=1}
    },
    {.id=26,.name=L"Minor Healing Potion",
        .type=db_itemtype_consume,
        .price=15,
        .desc=L"The unique precision of chemical reagents.",
        .stats={.min_=20,.max_=20}
    },
    {.id=27,.name=L"Small Healing Potion",
        .type=db_itemtype_consume,
        .price=35,
        .desc=L"The unique precision of chemical reagents.",
        .stats={.min_=40,.max_=40}
    },
    {.id=28,.name=L"Necklace of Mild Regeneration",
        .type=db_itemtype_accessory,
        .price=405,
        .desc=L"Why aren't necklaces of regeneration red?",
        .stats={.regen=3,.def=1,.dod=3}
    },
    {.id=29,.name=L"Paper",
        .type=db_itemtype_weapon,
        .price=2,
        .cd=8,
        .desc=L"For the long-forgotten glory...",
        .stats={.min_=0,.max_=1,.def=-1,.acc=1}
    },
    {.id=30,.name=L"Fan",
        .type=db_itemtype_weapon,
        .price=5,
        .cd=90,
        .desc=L"Impractical.",
        .stats={.min_=-1,.max_=0}
    },
    {.id=31,.name=L"Toilet Paper",
        .type=db_itemtype_misc,
        .price=1,
        .desc=L"Might be brand new. Might not...",
    },
    {.id=32,.name=L"Scissors",
        .type=db_itemtype_weapon,
        .price=7,
        .cd=24,
        .desc=L"Two pieces of blade, but half the damage.",
        .stats={.min_=1,.max_=2}
    },
    {.id=33,.name=L"Wooden Block",
        .type=db_itemtype_misc,
        .price=4,
        .desc=L"Why would you keep it?"
    },
    {.id=34,.name=L"Apple",
        .type=db_itemtype_consume,
        .price=2,
        .desc=L"\"Apfel, Nuss und Mandelkern,\"",
        .stats={.min_=2,.max_=2}
    },
    {.id=35,.name=L"Banana",
        .type=db_itemtype_consume,
        .price=2,
        .desc=L"Have a bana-na.",
        .stats={.min_=2,.max_=2}
    },
    {.id=36,.name=L"Cooked Meat",
        .type=db_itemtype_consume,
        .price=10,
        .desc=L"It's impossible to figure out what kind of meat this is.",
        .stats={.min_=10,.max_=12}
    },
    {.id=37,.name=L"Fried Salmon",
        .type=db_itemtype_consume,
        .price=25,
        .desc=L"\"Why wouldn't you like to have a fish?\"\n"
                "    -- fishstore",
        .stats={.min_=3,.max_=9}
    },
    {.id=38,.name=L"Broken Bone Longsword",
        .type=db_itemtype_weapon,
        .price=1650,
        .cd=153,
        .crit=343,
        .desc=L"Are they getting the material from themselves? Well...",
        .stats={.min_=22,.max_=35,.acc=20,.dod=4,.con=4}
    },
    {
        .id=0
//              -------------------------------------------------------------------\n"
    }
};

itemdb *db_ifindwithid(nat itemid);
void getitemname(nat id,wchar_t *itemname);
void consumeitem(nat itemid);


itemdb *db_ifindwithid(nat itemid){
    if(itemdbs[itemid-1].id==itemid)return &itemdbs[itemid-1];
    for(nat i=0;;i++){
        if(itemdbs[i].id==itemid){
            return &itemdbs[i];
            break;
        }
        if(itemdbs[i].id==0)break;
    }
    return NULL;
}
void getitemname(nat id,wchar_t *itemname){
    const wchar_t *p;
    switch(id){
    case 0:
        p=L"(none)";
        break;
    default:;
        itemdb *idb=db_ifindwithid(id);
        if(idb==NULL){
            printf("\n");
            printr(Red,msg->db_iidnullexceptionerror);
            p=L"undefined";
            break;
        }
        p=idb->name;
        break;
    }
    wcscpy(itemname,p);
}
void consumeitem(nat itemid){
    itemdb *idb=db_ifindwithid(itemid);
    nat range=idb->stats.max_-idb->stats.min_;
    nat regennum=idb->stats.min_;
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
