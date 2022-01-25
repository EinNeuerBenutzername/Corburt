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
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat stl;
        nat act;
        nat con;
    } stats;
};
#endif
