#define Corburt_Debug
#define Corburt_Pointer_Trace_Level 1
#include <stdio.h>
#include "include/cbcurses.h"
#include "include/cbbase.h"
#include "include/cbplayer.h"
#include "include/cbio.h"
#include "include/cbfio.h"
#include "include/dbentity.h"
int main(){
    launchcb();
    printr(Green|Bright,L"%ls",msg->global_welcome);
    printr(White,msg->global_splash);
    printr(Yellow,msg->global_splash2);
    printr(White,L"%50ls\n",msg->global_corburtversion);
    readsaves();
    db_rshowdesc(player.roomid);
	while(!quit_game){
        wmemset(inputbuf,0,128);
        scanline(inputbuf,127);
        processinput();
	}
	savesaves();
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
        et_spawnenemies();
    inputbuf=mallocpointer(128*sizeof(wchar_t));
    inputbufl=mallocpointer(128*sizeof(wchar_t));
    wmemset(inputbuf,0,128);
    wmemset(inputbufl,0,128);
}
void endcb(){
    freeall();
}
