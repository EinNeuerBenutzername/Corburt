#ifndef Corburt_Database_Enemy_h_Include_Guard
#define Corburt_Database_Enemy_h_Include_Guard
#define ENEMY_MAXDROPS 16
#include "cbbase.h"
typedef const struct enemydb{
    nat id;
    enum db_enemytype type;
    wchar_t *name;
    wchar_t *desc;
    bat exp;
    struct {
        nat moneymin;
        nat moneymax;
        nat weapon;
        nat armor;
        struct drops {
            nat itemid;
            nat rate;
        } drops[ENEMY_MAXDROPS];
    } loot;
    struct {
        nat hpmax;
        nat atkcd;
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat wis;
        nat act;
        nat con;
    } stats;
} enemydb;
enemydb enemydbs[]={
    {.id=1,.name=L"Vagrant",
        .type=db_enemytype_plain,
        .desc=L"They have no homes. Just like you...",
        .exp=12,
        .loot={.moneymin=0,.moneymax=2,.weapon=2},
        .stats={.hpmax=8,.atk=1,.def=0,.acc=15,.dod=-25,.con=1}
    },
    {.id=2,.name=L"Thug",
        .type=db_enemytype_plain,
        .desc=L"Avocation: killing cute animals.",
        .exp=20,
        .loot={.moneymin=0,.moneymax=4,.weapon=6},
        .stats={.hpmax=15,.atk=3,.def=1,.acc=12,.dod=-15,.con=1}
    },
    {.id=3,.name=L"Gang Member",
        .type=db_enemytype_plain,
        .desc=L"Yo, come on and be a gangster!",
        .exp=80,
        .loot={.moneymin=2,.moneymax=9,.weapon=3,.armor=16},
        .stats={.hpmax=40,.atk=12,.def=12,.acc=27,.dod=-9,.con=3}
    },
    {.id=4,.name=L"Gang Leader",
        .type=db_enemytype_plain,
        .desc=L"Do you wanna be a gang-star?",
        .exp=135,
        .loot={.moneymin=16,.moneymax=35,.weapon=4,.armor=17},
        .stats={.hpmax=62,.atk=17,.def=25,.acc=45,.dod=8,.con=5}
    },
    {.id=5,.name=L"Robber",
        .type=db_enemytype_plain,
        .desc=L"\"Show me what you've got...\"",
        .exp=110,
        .loot={.moneymin=3,.moneymax=18,.weapon=5,.armor=16},
        .stats={.hpmax=50,.atk=17,.def=8,.acc=47,.dod=65,.con=4}
    },
    {.id=6,.name=L"Skeleton",
        .type=db_enemytype_plain,
        .desc=L"Do not disturb the peace of the dead... Well... Too late...",
        .exp=3580,
        .loot={.moneymin=53,.moneymax=78,.weapon=38},
        .stats={.hpmax=489,.atk=63,.def=45,.acc=156,.dod=97,.con=39}
    },
//              -------------------------------------------------------------------\n"
    {.id=0}
};

enemydb *db_efindwithid(nat enemyid);
enemydb *db_efindwithid(nat enemyid){
    if(enemydbs[enemyid-1].id==enemyid)return &enemydbs[enemyid-1];
    for(nat i=0;;i++){
        if(enemydbs[i].id==enemyid){
            return &enemydbs[i];
            break;
        }
        if(enemydbs[i].id==0)break;
    }
    return NULL;
}
#endif
