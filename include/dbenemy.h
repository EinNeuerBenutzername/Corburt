#ifndef Corburt_Database_Enemy_h_Include_Guard
#define Corburt_Database_Enemy_h_Include_Guard
#include "cbbase.h"
enum db_enemytype {
    db_enemytype_plain,
    db_enemytype_sentinel,
    db_enemytype_assassin,
    db_enemytype_boss
};
typedef const struct {
    nat id;
    enum db_enemytype type;
    wchar_t *name;
    wchar_t *desc;
    nat exp;
    struct {
        nat moneymin;
        nat moneymax;
    } loot;
    struct {
        nat hpmax;
        nat atkcd;
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat stl;
        nat act;
        nat con;
    } stats;
} enemydb;
enemydb enemydbs[]={
    {.id=1,.name=L"Vagrant",
        .type=db_enemytype_plain,
        .desc=L"They have no homes. Just like you...",
        .exp=12,
        .loot={.moneymin=0,.moneymax=2},
        .stats={.hpmax=8,.atkcd=30,.atk=2,.def=1,.acc=5,.dod=-25,.con=1}
    },
    {.id=2,.name=L"Thug",
        .type=db_enemytype_plain,
        .desc=L"Avocation: killing cute animals.",
        .exp=20,
        .loot={.moneymin=0,.moneymax=4},
        .stats={.hpmax=13,.atkcd=25,.atk=3,.def=3,.acc=12,.dod=-15,.con=1}
    },
    {.id=3,.name=L"Gang Member",
        .type=db_enemytype_plain,
        .desc=L"Yo, come on and be a gangster!",
        .exp=40,
        .loot={.moneymin=2,.moneymax=7},
        .stats={.hpmax=20,.atkcd=20,.atk=4,.def=6,.acc=27,.dod=-9,.con=2}
    },
    {.id=4,.name=L"Gang Leader",
        .type=db_enemytype_plain,
        .desc=L"Do you wanna be a gangstar?",
        .exp=65,
        .loot={.moneymin=16,.moneymax=30},
        .stats={.hpmax=32,.atkcd=32,.atk=6,.def=8,.acc=45,.dod=8,.con=2}
    },
    {.id=5,.name=L"Robber",
        .type=db_enemytype_plain,
        .desc=L"\"Show me what you've got...\"",
        .exp=50,
        .loot={.moneymin=3,.moneymax=15},
        .stats={.hpmax=22,.atkcd=26,.atk=6,.def=5,.acc=17,.dod=25,.con=3}
    },
    {.id=6,.name=L"Skeleton",
        .type=db_enemytype_plain,
        .desc=L"Do not disturb the peace of the dead... Well... Too late...",
        .exp=350,
        .loot={.moneymin=53,.moneymax=78},
        .stats={.hpmax=189,.atkcd=44,.atk=23,.def=35,.acc=95,.dod=67,.con=9}
    },
//              -------------------------------------------------------------------\n"
    {.id=0}
};

enemydb *db_efindwithid(nat enemyid);
enemydb *db_efindwithid(nat enemyid){
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
