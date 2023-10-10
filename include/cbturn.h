#ifndef Corburt_Turn_h_Include_Guard
#define Corburt_Turn_h_Include_Guard
#include "cbbase.h"
void timepass(int tick);
void tickfunc(struct et_room *etr);
void turnfunc();
void showtime();
static void clockpulse();
#ifdef CB_REALTIME
static void checkfps();
#endif

#include "cbplayer.h"
#include "dbbuff.h"
#include "dbentity.h"

void timepass(int tick){
    if(cbp.playerdead){
        cbp.playerdead=false;
    }
    if(tick<=0)return;
    struct et_room *etr=et_findroomwithid(player.roomid);
    for(int i=0; i<tick; i++){
        if(player.roomid!=etr->id)etr=et_findroomwithid(player.roomid);
        tickfunc(etr);
///----------------------------------------------------
        global.curtick++;
        if(global.curtick>=30){
            int ct=global.curtick%30;
            global.curround+=(global.curtick-ct)/30;
            global.curtick=ct;
///----------------------------------------------------
            turnfunc();
        }
    }
}
void tickfunc(struct et_room *etr){
    {/// process enemies
        for(int j=0; j<DBE_ENEMYCAP; j++){
            if(etr->etenemy[j]==0)continue;
            struct et_enemy *ete=&et_enemies[etr->etenemy[j]-1];
//            const struct enemydb *edb=et_getenemydb(etr->etenemy[j]);
            if(ete->attackcd==0){
                etenemy_attack(etr->etenemy[j], etr);
                if(player.roomid!=etr->id)break; // player is dead
            }
        }
        for(int i=0; i<enemiesmax; i++){
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
#ifdef CB_REALTIME
    checkfps();
#endif
    if(global.curround%30==0){
        pregen();
        for(int i=0, j=0; i<enemiesmax && j<enemiescount; i++){
            if(!et_enemies[i].available)continue;
            j++;
            enemydb *edb=et_getenemydb(i+1);
            if(et_enemies[i].hp==edb->stats.hpmax)continue;
            et_enemies[i].hp+=edb->stats.vit;
            if(et_enemies[i].hp>edb->stats.hpmax)et_enemies[i].hp=edb->stats.hpmax;
        }
    }
    if(global.curround%120==0){
        et_spawnenemies();
    }
    if(global.curround>36000-player.lvl*player.lvl){
        if(player.loi>10000-player.lvl*50){
            clockpulse();
        }
    }
}
void showtime(){
#ifndef CB_REALTIME
    printr(palette.inform, msg->global_curtime, global.curround, global.curtick);
#else
    bat h=global.curround/3600;
    int s=global.curround%60;
    int m=(global.curround%3600-s)/60;
    printr(palette.inform, msg->global_curtimert, h, m, s, global.curtick);
#endif
}
#ifdef CB_REALTIME
static void checkfps(){
#ifdef Corburt_ShowFPS
    char cbtitlewithfps[128];
    memset(cbtitlewithfps, 0, 128);
//    sprintf(cbtitlewithfps, "Corburt    FPS: %.0f", cbtime_fps);
    sprintf(cbtitlewithfps, "Corburt    FPS: %.2f", cbtime_fps);
    cbc_setwindowtitle(cbtitlewithfps);
#endif
    static int badthingshappen=0;
    static int fpswarncooldown=0;
    static int fpswarncooldownlong=0;
    if(cbtime_fps<27){
        badthingshappen+=5;
    }else{
        badthingshappen*=0.5f;
        badthingshappen-=2;
    }
    if(fpswarncooldown==0 && badthingshappen>=10){
        printr(palette.load, msg->global_lag);
        fpswarncooldownlong+=5;
        fpswarncooldown=fpswarncooldownlong;
        fpswarncooldownlong+=5;
        if(fpswarncooldownlong>10)fpswarncooldownlong=10;
    }else{
        if(fpswarncooldown>1){
            fpswarncooldown--;
        }else{
            if(cbtime_fps>29){
                fpswarncooldown=0;
            }
        }
    }
}
#endif
static void clockpulse(){ // tbd
    //tbd: happens for each 10k lines of input and 10 game hours
//    printr(Default, msg->global_clock);
    global.curround=0;
    global.curtick=0;
    player.loi=0;
    // things should happen during pulses
}

#endif
