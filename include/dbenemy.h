#ifndef Corburt_Database_Enemy_h_Include_Guard
#define Corburt_Database_Enemy_h_Include_Guard
#include "cbbase.h"

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
