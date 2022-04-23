#define Corburt_Debug
#define Corburt_Pointer_Trace_Level 1 // off
#define CB_REALTIME
#include <stdio.h>
#include "include/cbcurses.h"
#include "include/cbbase.h"
#include "include/cbplayer.h"
#include "include/cbio.h"
#include "include/cbfio.h"
#include "include/dbentity.h"
#ifdef CB_REALTIME
    #include "include/cbsys.h"
#endif
int main(){
    launchcb();
    printr(Green|Bright,L"%ls",msg->global_welcome);
    printr(White,msg->global_splash);
    printr(Yellow,msg->global_splash2);
    printr(White,L"%50ls\n",msg->global_corburtversion);
#ifdef CB_REALTIME
    scanline(inputbuf,127);
    wmemset(inputbuf,0,128);
#endif
    readsaves();
    db_rshowdesc(player.roomid);
#ifdef CB_REALTIME
    cbtime_init();
#endif
	while(!quit_game){
        wmemset(inputbuf,0,128);
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
    printr_dest=mallocpointer(4096*sizeof(wchar_t));
    printr_token=mallocpointer(DISPLAY_WIDTH*sizeof(wchar_t));
    assertcheck();
    cbc_init();
    cbc_setwindowtitle("Corburt");
    cbc_setcolor(Default);
    cbc_clearscreen();
    initrng();
    checkendianess();
    setupentitydata();
        et_initenemies();
    inputbuf=mallocpointer(128*sizeof(wchar_t));
    inputbufl=mallocpointer(128*sizeof(wchar_t));
    wmemset(inputbuf,0,128);
    wmemset(inputbufl,0,128);
#ifdef CB_REALTIME
    fpinput=fopen("data.dmp","r");
    if(!fpinput){
        printc(Cyan|Bright,msg->global_waitingforinput);
    }
#endif
}
void endcb(){
#ifdef CB_REALTIME
    fclose(fpinput);
    remove("data.dmp");
#endif
    freeall();
}
