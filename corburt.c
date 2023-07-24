//#define Corburt_Debug
#define Corburt_Pointer_Trace_Level 1 // partially on
#define Corburt_ShowFPS
#include <stdio.h>
#include <stdlib.h>
#define CB_REALTIME
#include "include/cbcurses.h"
#include "include/cbbase.h"
#include "include/cbplayer.h"
#include "include/cbio.h"
#include "include/cbfio.h"
#include "include/dbfio_.h"
#include "include/dbentity.h"
int main(){
    launchcb();
#ifdef CB_REALTIME
    scanline(inputbuf,127);
    memset(inputbuf,0,128);
    cbc_hidecursor();
#endif
    printr(palette.splash.welcome,"%s",msg->global_welcome);
    printr(palette.splash.logoup,msg->global_splash);
    printr(palette.splash.logodown,msg->global_splash2);
    printr(palette.splash.version,"%50s\n",msg->global_corburtversion);
    readsaves();
    db_rshowdesc(player.roomid);
#ifdef CB_REALTIME
    cbtime_init();
#endif
	while(!quit_game){
        memset(inputbuf,0,128);
#ifdef CB_REALTIME
        fscanline(inputbuf,127);
#else
        scanline(inputbuf,127);
#endif
        processinput();
#ifdef CB_REALTIME
        timepass(1);
        cbtime_wait(30);
        cbtime_end();
#endif
	}
	savesaves();
	endcb();
    return 0;
}
void launchcb(){
    atexit(endcb);
    global.pointerpool=malloc(CB_MAXPOINTERS*sizeof(void *));
    for(nat i=0;i<CB_MAXPOINTERS;i++)global.pointerpool[i]=NULL;
    printr_dest=mallocpointer(4096);
    printr_token=mallocpointer(TOKEN_MAXLEN);
    assertcheck();
    cbc_init();
    cbc_setwindowtitle("Corburt");
    cbc_setcolor(Default);
    cbc_clearscreen();

    initpalette();
    initrng();
    isle=checkendianess();
    if(isle){
        tracelog(msg->trace_endianess_le);
    }else{
        tracelog(msg->trace_endianess_be);
    }
    loadalldb();
    setupentitydata();
    inputbuf=mallocpointer(128*sizeof(char));
    inputbufl=mallocpointer(128*sizeof(char));
    memset(inputbuf,0,128);
    memset(inputbufl,0,128);
    setvbuf(stdout,NULL,_IOFBF,0);
#ifdef CB_REALTIME
    fpinput=fopen("data.dmp","r");
    if(!fpinput){
        printr(palette.inform,msg->global_waitingforinput);
    }
#endif
}
void endcb(){
#ifdef CB_REALTIME
    fclose(fpinput);
    remove("data.dmp");
#endif
    cbc_setcolor(Default);
    fflush(stdout);
    freeall();
}
