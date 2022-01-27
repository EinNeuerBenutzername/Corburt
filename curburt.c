#define Corburt_Debug
#define Corburt_Pointer_Trace_Level 1
#include <stdio.h>
#include "include/cbcurses.h"
#include "include/cbbase.h"
#include "include/cbplayer.h"
#include "include/cbio.h"
#include "include/cbfio.h"
#include "include/dbfio_.h"
int main(){
    cbc_init();
    cbc_setwindowtitle("Corburt");
    cbc_setcolor(Default);
    cbc_clearscreen();
    tracelog(Green,msg_trace_savesize,sizeof(struct save));
    tracelog(Green,L"Size of room database: %zu bytes\n",sizeof(roomdbs));
    tracelog(Green,L"Size of item database: %zu bytes\n",sizeof(itemdbs));
    initrng();
    checkendianess();
    inputbuf=mallocpointer(128*sizeof(wchar_t));
    inputbufl=mallocpointer(128*sizeof(wchar_t));
    wmemset(inputbuf,0,128);
    printc(Green|Bright,L"%ls",msg_global_welcome);
    printc(White,msg_global_splash);
    printc(Yellow,msg_global_splash2);
    printc(White,L"%50ls\n",msg_global_corburtversion);
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
