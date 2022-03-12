#ifndef Corburt_Turn_h_Include_Guard
#define Corburt_Turn_h_Include_Guard
#include "cbbase.h"
//generally, 1 turn=30 tick.
void timepass(nat tick);
void showtime();

#include "cbplayer.h"
#include "dbentity.h"

void timepass(nat tick){
    if(tick<=0)return;
    for(nat i=0;i<tick;i++){


///----------------------------------------------------
        global.curtick++;
        if(global.curtick>=30){
            nat ct=global.curtick%30;
            global.curround+=(global.curtick-ct)/30;
            global.curtick=ct;
        }
    }
}
void showtime(){
    printc(Cyan|Bright,msg->global_curtime,global.curround,global.curtick);
}

#endif
