#ifndef Corburt_Turn_h_Include_Guard
#define Corburt_Turn_h_Include_Guard
#include "cbbase.h"
void timepass(nat tick);
void tickfunc(struct et_room *etr);
void turnfunc();
void showtime();
static void clockpulse();

#include "cbplayer.h"
#include "dbentity.h"

void timepass(nat tick){
    if(cbp.playerdead){
        cbp.playerdead=false;
    }
    if(tick<=0)return;
    struct et_room *etr=et_findroomwithid(player.roomid);
    for(nat i=0;i<tick;i++){
        if(player.roomid!=etr->id)etr=et_findroomwithid(player.roomid);
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
            if(etr->etenemy[j]==0)continue;
            struct et_enemy *ete=&et_enemies[etr->etenemy[j]-1];
//            const struct enemydb *edb=et_getenemydb(etr->etenemy[j]);
            if(ete->attackcd==0){
                etenemy_attack(etr->etenemy[j],etr);
                if(player.roomid!=etr->id)break; // player is dead
            }
        }
        for(nat i=0;i<enemiesmax;i++){
            if(!et_enemies[i].available)continue;
            if(et_enemies[i].attackcd>0)et_enemies[i].attackcd--;
            if(et_enemies[i].attackcd<0)et_enemies[i].attackcd=0;
        }
    }
    {/// process player
        if(cbp.attackcd>0)cbp.attackcd--;
        if(cbp.swinging>0){
            cbp.swinging--;
            if(cbp.swinging==0){
                pattack(cbp.targetid);
            }
        }
        preadying();
    }
}
void turnfunc(){ // tbd
    if(global.curround%30==0){
        pregen();
        for(nat i=0,j=0;i<enemiesmax&&j<enemiescount;i++){
            if(!et_enemies[i].available)continue;
            j++;
            enemydb *edb=et_getenemydb(i+1);
            if(et_enemies[i].hp==edb->stats.hpmax)continue;
            et_enemies[i].hp+=edb->stats.con;
            if(et_enemies[i].hp>edb->stats.hpmax)et_enemies[i].hp=edb->stats.hpmax;
        }
    }
    if(global.curround%120==0){
        et_spawnenemies();
    }
    if(global.curround>36000){
        if(1){ // tbd: measure lines of input
            clockpulse();
        }
    }
}
void showtime(){
#ifndef CB_REALTIME
    printc(Cyan|Bright,msg->global_curtime,global.curround,global.curtick);
#else
    bat h=global.curround/3600;
    nat s=global.curround%60;
    nat m=(global.curround%3600-s)/60;
    printc(Cyan|Bright,msg->global_curtimert,h,m,s,global.curtick);
#endif
}
static void clockpulse(){ // tbd
    //tbd: happens for each 10k lines of input and 10 game hours
    printc(Default,msg->global_clock);
    global.curround=0;
    global.curtick=0;
    // things should happen during pulses
}

#endif
