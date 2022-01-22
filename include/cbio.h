#ifndef Corburt_IO_h_Include_Guard
#define Corburt_IO_h_Include_Guard
#include "cbbase.h"
#include "cbplayer.h"
wchar_t *inputbufl=NULL;
foo fullmatch(wchar_t *wcs1,const wchar_t *wcs2);
foo matchcommands(wchar_t *cmd);
void processinput();

foo fullmatch(wchar_t *wcs1,const wchar_t *wcs2){
    if(wcs1==NULL&&wcs2==NULL)return true;
    if(wcs1==NULL||wcs2==NULL)return false;
    if(wcslen(wcs1)<wcslen(wcs2))return false;
    if(wcslen(wcs1)>wcslen(wcs2)){
        if(wcs1[wcslen(wcs2)]!=L' ')return false;
        for(nat i=wcslen(wcs2);i<wcslen(wcs1)&&i<INT_MAX;i++)
            wcs1[i]=0;
    }
    if(wcscmp(wcs1,wcs2)==0)return true;
    else return false;
}
foo matchcommands(wchar_t *cmd){
    if(fullmatch(cmd,L"st")||
       fullmatch(cmd,L"stats")||
       fullmatch(cmd,L"statistics")){
        pshowstats();
        return true;
    }
    if(fullmatch(cmd,L"quit")||
       fullmatch(cmd,L"exitgame")||
       fullmatch(cmd,L"quitgame")){
        quit_game=true;
        return true;
    }
    if(fullmatch(cmd,L"cls")||
       fullmatch(cmd,L"clear")){
        cbc_clearscreen();
        return true;
    }
    if(fullmatch(cmd,L"east")||
       fullmatch(cmd,L"e")){
        pmove(dir_East);
        return true;
    }
    if(fullmatch(cmd,L"west")||
       fullmatch(cmd,L"w")){
        pmove(dir_West);
        return true;
    }
    if(fullmatch(cmd,L"north")||
       fullmatch(cmd,L"n")){
        pmove(dir_North);
        return true;
    }
    if(fullmatch(cmd,L"south")||
       fullmatch(cmd,L"s")){
        pmove(dir_South);
        return true;
    }
    if(fullmatch(cmd,L"up")){
        pmove(dir_Up);
        return true;
    }
    if(fullmatch(cmd,L"down")){
        pmove(dir_Down);
        return true;
    }
    if(fullmatch(cmd,L"inventory")||
       fullmatch(cmd,L"inv")){
        pshowinventory();
        return true;
    }
    if(fullmatch(cmd,L"expierence")||
       fullmatch(cmd,L"exp")||
       fullmatch(cmd,L"xp")){
        pshowexp();
        return true;
    }
    if(fullmatch(cmd,L"look")||
       fullmatch(cmd,L"l")){
        //showroomdescription(player.roomid);
        return true;
    }
    if(fullmatch(cmd,L"train")||
       fullmatch(cmd,L"tr")){
        ptrain();
    }
    if(fullmatch(cmd,L"editstats")||
       fullmatch(cmd,L"editst")){
        peditstats();
    }
    return false;
}
void processinput(){
    static foo processinput_internal_tmps=false;
    if(wcslen(inputbuf)==0){
        size_t row,col;
        cbc_getcursor(&row,&col);
        cbc_setcursor(row>0?row-1:0,0);
        if(!processinput_internal_tmps){
            printc(Default,L"Time Passes.\n");
            processinput_internal_tmps=true;
        }
        return;
    }
    processinput_internal_tmps=false;
//    wchar_t *inputbufl=mallocpointer_(128*sizeof(wchar_t));
    wmemset(inputbufl,0,128);
    wcscpy(inputbufl,inputbuf);
    wcslower(&inputbufl);
    if(matchcommands(inputbufl)){
//        freepointer_(inputbufl);
        return;
    }
    printc(Cyan|Bright,msg_player_say,player.name);
    printc(Default,L"%ls\n",inputbuf);
//    freepointer_(inputbufl);
    return;
}

#endif
