#ifndef Corburt_IO_h_Include_Guard
#define Corburt_IO_h_Include_Guard
#include "cbbase.h"
#include "cbfio.h"
#include "cbplayer.h"
#include "dbmap.h"
wchar_t *inputbufl=NULL;
foo fullmatch(wchar_t *wcs,const wchar_t *wcs2);
foo matchcommands(wchar_t *cmd);
void processinput();

foo fullmatch(wchar_t *wcs,const wchar_t *wcs2){
    if(wcs==NULL&&wcs2==NULL)return true;
    if(wcs==NULL||wcs2==NULL)return false;
    if(wcslen(wcs)<wcslen(wcs2))return false;
    if(wcs[0]!=wcs2[0])return false;
    if(wcslen(wcs)>wcslen(wcs2)){
        if(wcs[wcslen(wcs2)]!=L' ')return false;
        for(size_t i=0;i<wcslen(wcs2);i++){
            if(wcs[i]!=wcs2[i])return false;
        }
        return true;
    }
    else{
        if(wcscmp(wcs,wcs2)==0)return true;
        return false;
    }
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
        pshowinv();
        return true;
    }
    if(fullmatch(cmd,L"experience")||
       fullmatch(cmd,L"exp")||
       fullmatch(cmd,L"xp")){
        pshowexp();
        return true;
    }
    if(fullmatch(cmd,L"look")||
       fullmatch(cmd,L"l")){
        db_rshowdesc(player.roomid);
        return true;
    }
    if(fullmatch(cmd,L"train")||
       fullmatch(cmd,L"tr")){
        ptrain();
        return true;
    }
    if(fullmatch(cmd,L"editstats")||
       fullmatch(cmd,L"editst")){
        peditstats();
        return true;
    }
    if(fullmatch(cmd,L"help")){
        printc(Default,msg_global_help);
        return true;
    }
    if(fullmatch(cmd,L"abilities")||
       fullmatch(cmd,L"abl")){
        pshowabl();
        return true;
    }
    if(fullmatch(cmd,L"save")){
        savesaves();
        printr(Cyan|Bright,msg_global_progresssaved);
        return true;
    }
    if(fullmatch(cmd,L"list")){
        db_rshowtable(player.roomid);
        return true;
    }
    if(fullmatch(cmd,L"buy")){
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            printr(Red,msg_db_ridnullexceptionerror);
            return true;
        }
        if(rm->type!=db_roomtype_shop){
            printr(Default,msg_db_notinstore);
            return true;
        }
        wchar_t *buytarget=NULL;
        buytarget=mallocpointer(128*sizeof(wchar_t));
        wmemset(buytarget,0,128);
        nat j=0,sth=0;
        for(size_t i=3;i<wcslen(cmd);i++){
            if(cmd[i]!=L' '&&((cmd[i]>L'9'||cmd[i]<L'0')||sth==3))sth=2;
            else{
                if(cmd[i]==L' '&&sth==1)sth=3;
                else if(cmd[i]!=L' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                buytarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&wcslen(buytarget)>0){
                j=0;
                wmemset(buytarget,0,128);
            }
        }
        nat qnty=0;
        for(size_t i=3;i<128;i++){
            if((cmd[i]<L'0'||cmd[i]>L'9')&&!(cmd[i]==' '&&qnty==0))break;
            if(qnty){
                qnty*=10;
                qnty+=cmd[i]-L'0';
                if(qnty>=ITEM_MAXSTACK){
                    qnty=ITEM_MAXSTACK;
                    break;
                }
            }
            if(cmd[i]>=L'1'&&cmd[i]<=L'9'&&qnty==0)qnty=cmd[i]-L'0';
        }
        if(qnty==0)qnty=1;
        nat maxmatch=-1;
        nat maxmatchid=0;
        for(nat i=0;rm->table[i]!=0;i++){
            itemdb *idb=db_ifindwithid(rm->table[i]);
            if(idb==NULL){
                printr(Red,msg_db_iidnullexceptionerror);
                return true;
            }
            nat curmatch=match(buytarget,idb->name);
            if(curmatch>maxmatch){
                maxmatch=curmatch;
                maxmatchid=idb->id;
            }
        }
        freepointer(buytarget);
        if(maxmatch>=0){
            itemdb *idb=db_ifindwithid(maxmatchid);
            if(idb==NULL){
                printr(Red,msg_db_iidnullexceptionerror);
                return true;
            }
            if(idb->type&db_itemtype_stackable_mask){
                if(inventory.money>=idb->price*qnty){
                    etitem_push(idb->id,qnty,0,1);
                    return true;
                }else{
                    if(qnty==1)printr(Default,msg_db_icantafford,idb->price*qnty-inventory.money);
                    else printr(Default,msg_db_icantaffordmult,idb->price*qnty-inventory.money);
                }
            }
            else{
                if(inventory.money>=idb->price){
                    etitem_push(idb->id,1,0,1);
                    return true;
                }else{
                    printr(Default,msg_db_icantafford,idb->price-inventory.money);
                }
            }
        }else{
            printr(Default,msg_db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,L"use")){
        wchar_t *usetarget=NULL;
        usetarget=mallocpointer(128*sizeof(wchar_t));
        wmemset(usetarget,0,128);
        foo sth=false;
        nat j=0;
        for(size_t i=3;i<wcslen(cmd);i++){
            if(cmd[i]!=L' ')sth=true;
            if(sth){
                usetarget[j]=cmd[i];
                j++;
            }
        }
        nat maxmatch=-1;
        nat maxmatchid=0;
        nat ininvindex=0;
        foo noprev=true;
        for(nat i=0;inventory.items[i]!=0;i++){
            itemdb *idb=db_ifindwithid(et_items[inventory.items[i]-1].itemid);
            if(idb==NULL){
                printr(Red,msg_db_iidnullexceptionerror);
                return true;
            }
            nat curmatch=match(usetarget,idb->name);
            if(curmatch>maxmatch){
                noprev=false;
                for(nat k=0;k<5;k++)if(inventory.accessories[k]==i+1){
                    noprev=true;break;
                }
                maxmatch=curmatch;
                maxmatchid=idb->id;
                ininvindex=i;
            }else if(curmatch==maxmatch&&noprev){
                foo equipped=false;
                for(nat k=0;k<5;k++){
                    if(inventory.accessories[k]==i+1){
                        equipped=true;
                        break;
                    }
                }
                if(!equipped){
                    maxmatchid=idb->id;
                    ininvindex=i;
                    noprev=false;
                }
            }
        }
        freepointer(usetarget);
        if(maxmatch>=0){
            itemdb *idb=db_ifindwithid(maxmatchid);
            if(idb==NULL){
                printr(Red,msg_db_iidnullexceptionerror);
                return true;
            }
            if(idb->type==db_itemtype_weapon){
                inventory.weapon=ininvindex+1;
                printr(Default,msg_player_inv_wield,idb->name);
            }
            if(idb->type==db_itemtype_armor){
                inventory.armor=ininvindex+1;
                printr(Default,msg_player_inv_wear,idb->name);
            }
            if(idb->type==db_itemtype_accessory){
                foo canequip=true;
                for(nat k=0;k<5;k++){
                    if(inventory.accessories[k]==ininvindex+1){
                        printr(Default,msg_player_inv_alreadyequipped,idb->name);
                        canequip=false;
                        break;
                    }
                }
                if(canequip){
                    for(nat k=0;k<5;k++){
                        if(inventory.accessories[k]==0){
                            inventory.accessories[k]=ininvindex+1;
                            printr(Default,msg_player_inv_equip,idb->name);
                            break;
                        }
                    }
                }
            }
            // consume
        }else{
            printr(Default,msg_db_inosuchitem);
        }
        return true;
    }
    return false;
}
void processinput(){
    if(wcslen(inputbuf)==0){
        size_t row,col;
        cbc_getcursor(&row,&col);
        if(row>0)cbc_setcursor(row-1,0);
        if(wcslen(inputbufl)==0)return;
        printr(Yellow,L"%ls\n",inputbufl);
        matchcommands(inputbufl);
        return;
    }
    wmemset(inputbufl,0,128);
    wcscpy(inputbufl,inputbuf);
    wcslower(&inputbufl);
    if(matchcommands(inputbufl)){
        return;
    }else{
        memset(inputbufl,0,128);
    }
    printr(Cyan|Bright,msg_player_say,player.name);
    printr(Default,L"%ls\n",inputbuf);
    return;
}

#endif
