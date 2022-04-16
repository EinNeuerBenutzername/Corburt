#ifndef Corburt_Database_Enemy_h_Include_Guard
#define Corburt_Database_Enemy_h_Include_Guard
#include "cbbase.h"
enemydb enemydbs[]={
    {.id=1,.name=L"Vagrant",
        .type=db_enemytype_plain,
        .desc=L"They have no homes. Just like you...",
        .exp=12,
        .loot={.moneymin=0,.moneymax=2,.weapon=2},
        .stats={.hpmax=8,.atk=1,.def=0,.acc=5,.dod=-25,.con=1}
    },
    {.id=2,.name=L"Thug",
        .type=db_enemytype_plain,
        .desc=L"Avocation: killing cute animals.",
        .exp=20,
        .loot={.moneymin=0,.moneymax=4,.weapon=6},
        .stats={.hpmax=13,.atk=3,.def=1,.acc=12,.dod=-15,.con=1}
    },
    {.id=3,.name=L"Gang Member",
        .type=db_enemytype_plain,
        .desc=L"Yo, come on and be a gangster!",
        .exp=40,
        .loot={.moneymin=2,.moneymax=9,.weapon=3,.armor=16},
        .stats={.hpmax=20,.atk=2,.def=2,.acc=27,.dod=-9,.con=2}
    },
    {.id=4,.name=L"Gang Leader",
        .type=db_enemytype_plain,
        .desc=L"Do you wanna be a gang-star?",
        .exp=65,
        .loot={.moneymin=16,.moneymax=35,.weapon=4,.armor=17},
        .stats={.hpmax=32,.atk=4,.def=5,.acc=45,.dod=8,.con=2}
    },
    {.id=5,.name=L"Robber",
        .type=db_enemytype_plain,
        .desc=L"\"Show me what you've got...\"",
        .exp=50,
        .loot={.moneymin=3,.moneymax=18,.weapon=5,.armor=16},
        .stats={.hpmax=22,.atk=3,.def=4,.acc=17,.dod=25,.con=3}
    },
    {.id=6,.name=L"Skeleton",
        .type=db_enemytype_plain,
        .desc=L"Do not disturb the peace of the dead... Well... Too late...",
        .exp=350,
        .loot={.moneymin=53,.moneymax=78,.weapon=38},
        .stats={.hpmax=189,.atk=33,.def=35,.acc=56,.dod=67,.con=9}
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
