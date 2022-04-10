#ifndef Corburt_Turn_h_Include_Guard
#define Corburt_Turn_h_Include_Guard
#include "cbbase.h"
//generally, 1 turn=30 tick.
void timepass(nat tick);
void tickfunc(struct et_room *etr);
void turnfunc();
void showtime();

#include "cbplayer.h"
#include "dbentity.h"

void timepass(nat tick){
    if(tick<=0)return;
    struct et_room *etr=et_findroomwithid(player.roomid);
    for(nat i=0;i<tick;i++){
        tickfunc(etr);
///----------------------------------------------------
        global.curtick++;
        if(global.curtick>=30){
            nat ct=global.curtick%30;
            global.curround+=(global.curtick-ct)/30;
            global.curtick=ct;
///----------------------------------------------------
            turnfunc();
        }
    }
}
void tickfunc(struct et_room *etr){
    {/// process enemies
        for(nat j=0;j<DBE_ENEMYCAP;j++){
            if(etr->etenemy[j]==0)break;
            struct et_enemy *ete=&et_enemies[etr->etenemy[j]-1];
//            const struct enemydb *edb=et_getenemydb(etr->etenemy[j]);
            if(ete->attackcd>0)ete->attackcd--;
            if(ete->attackcd==0){
                etenemy_attack(etr->etenemy[j],etr);
                if(player.roomid!=etr->id)break; // player is dead
            }
        }
    }
}
void turnfunc(){
    if(global.curround%50==0){
        pregen();
    }
}
void showtime(){
    printc(Cyan|Bright,msg->global_curtime,global.curround,global.curtick);
}

#endif
