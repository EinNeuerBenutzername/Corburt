#ifndef Corburt_Database_Enemy_h_Include_Guard
#define Corburt_Database_Enemy_h_Include_Guard
#include "cbbase.h"
enum db_enemytype {
    db_enemytype_plain,
    db_enemytype_regular=db_enemytype_plain,
    db_enemytype_sentinel,
    db_enemytype_sentry=db_enemytype_sentinel,
    db_enemytype_assassin,
    db_enemytype_boss
};
struct enemydb {
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
        real atkcd;
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat stl;
        nat act;
        nat con;
    } stats;
};
const struct enemydb enemydbs[]={
    {.id=1,.name="Vagrant",
        .type=db_enemytype_plain,
        .desc=L"",
        .exp=12,
        .loot={.moneymin=0,.moneymax=2},
        .stats={.hpmax=8,.atkcd=1.5f,.atk=2,.def=1,.acc=5,.dod=-25,.con=1}
    },
    {.id=2,.name="Thug",
        .type=db_enemytype_plain,
        .desc=L"",
        .exp=20,
        .loot={.moneymin=0,.moneymax=4},
        .stats={.hpmax=13,.atkcd=1.5f,.atk=3,.def=1,.acc=12,.dod=-15,.con=1}
    },
    {.id=3,.name="Gang Member",
        .type=db_enemytype_plain,
        .desc=L"",
        .exp=40,
        .loot={.moneymin=2,.moneymax=7},
        .stats={.hpmax=20,.atkcd=1.0f,.atk=4,.def=2,.acc=27,.dod=-9,.con=2}
    },
    {.id=4,.name="Gang Leader",
        .type=db_enemytype_plain,
        .desc=L"",
        .exp=65,
        .loot={.moneymin=16,.moneymax=30},
        .stats={.hpmax=32,.atkcd=1.3f,.atk=6,.def=3,.acc=45,.dod=8,.con=2}
    },
    {.id=5,.name="Robber",
        .type=db_enemytype_plain,
        .desc=L"",
        .exp=50,
        .loot={.moneymin=3,.moneymax=15},
        .stats={.hpmax=22,.atkcd=2.0f,.atk=6,.def=2,.acc=17,.dod=25,.con=3}
    },
    {.id=6,.name="Skeleton",
        .type=db_enemytype_plain,
        .desc=L"",
        .exp=250,
        .loot={.moneymin=43,.moneymax=78},
        .stats={.hpmax=89,.atkcd=4.5f,.atk=23,.def=9,.acc=95,.dod=67,.con=9}
    },
    {.id=0}
};

struct enemydb *db_efindwithid(nat enemyid);
struct enemydb *db_efindwithid(nat enemyid){
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
