#ifndef Corburt_IO_h_Include_Guard
#define Corburt_IO_h_Include_Guard
#include "cbbase.h"
#include "cbfio.h"
#include "cbplayer.h"
#include "dbmap.h"
#include "dbitem.h"
wchar_t *inputbufl=NULL;
foo fullmatch(wchar_t *wcs,const wchar_t *wcs2);
foo matchcommands(wchar_t *cmd);
foo match__commands(wchar_t *cmd); // template
foo matchregularcommands(wchar_t *cmd);
foo matcheditstatscommands(wchar_t *cmd);
void processinput();
#ifdef CB_REALTIME
#include "cbsys.h"
int cbio_matchid=0,cbio_matchidold=1,cbio_len=0;
FILE *fpinput=NULL;
#endif

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
    if(cbp.editstats){
        return matcheditstatscommands(cmd);
    }
    return matchregularcommands(cmd);
}
foo match__commands(wchar_t *cmd){
    if(fullmatch(cmd,L"quit")||
       fullmatch(cmd,L"exitgame")||
       fullmatch(cmd,L"quitgame")){
        quit_game=true;
        return true;
    }
    return false;
}
foo matchregularcommands(wchar_t *cmd){
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
    if(fullmatch(cmd,L"time")||
       fullmatch(cmd,L"tm")){
        showtime();
        return true;
    }
    if(fullmatch(cmd,L"editstats")||
       fullmatch(cmd,L"editst")){
        peditstats();
        return true;
    }
    if(fullmatch(cmd,L"help")){
        printc(Default,msg->global_help);
        return true;
    }
    if(fullmatch(cmd,L"abilities")||
       fullmatch(cmd,L"abl")){
        pshowabl();
        return true;
    }
    if(fullmatch(cmd,L"save")){
        savesaves();
        printr(Cyan|Bright,msg->global_progresssaved);
        return true;
    }
    if(fullmatch(cmd,L"list")){
        db_rshowtable(player.roomid);
        return true;
    }
    if(fullmatch(cmd,L"buy")){
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            printr(Red,msg->db_ridnullexceptionerror);
            return true;
        }
        if(rm->type!=db_roomtype_shop){
            printr(Default,msg->db_notinstore);
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
                printr(Red,msg->db_iidnullexceptionerror);
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
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            if(idb->type&db_itemtype_stackable_mask){
                if(inventory.money>=idb->price*qnty){
                    etitem_push(idb->id,qnty,0,1);
                    return true;
                }else{
                    if(qnty==1)printr(Default,msg->db_icantafford,idb->price*qnty-inventory.money);
                    else printr(Default,msg->db_icantaffordmult,idb->price*qnty-inventory.money);
                }
            }
            else{
                if(inventory.money>=idb->price){
                    etitem_push(idb->id,1,0,1);
                    return true;
                }else{
                    printr(Default,msg->db_icantafford,idb->price-inventory.money);
                }
            }
        }else{
            printr(Default,msg->db_inosuchitem);
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
        for(nat i=0;i<inventory.unlocked;i++){
            if(inventory.items[i]==0)continue;
            itemdb *idb=db_ifindwithid(et_items[inventory.items[i]-1].itemid);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
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
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            if(idb->type==db_itemtype_weapon){
                inventory.weapon=ininvindex+1;
                pcalcstats();
                printr(Default,msg->player_inv_wield,idb->name);
            }
            if(idb->type==db_itemtype_armor){
                inventory.armor=ininvindex+1;
                pcalcstats();
                printr(Default,msg->player_inv_wear,idb->name);
            }
            if(idb->type==db_itemtype_accessory){
                foo canequip=true;
                for(nat k=0;k<5;k++){
                    if(inventory.accessories[k]==ininvindex+1){
                        printr(Default,msg->player_inv_alreadyequipped,idb->name);
                        canequip=false;
                        break;
                    }
                }
                if(canequip){
                    for(nat k=0;k<5;k++){
                        if(inventory.accessories[k]==0){
                            inventory.accessories[k]=ininvindex+1;
                            printr(Default,msg->player_inv_equip,idb->name);
                            pcalcstats();
                            break;
                        }
                    }
                }
            }
            if(idb->type==db_itemtype_consume){
                struct et_item *eti=&et_items[inventory.items[ininvindex]-1];
                consumeitem(eti->itemid);
                if(eti->qnty>1)eti->qnty--;
                else{
                    etitem_delete(inventory.items[ininvindex]);
                }
            }
        }else{
            printr(Default,msg->db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,L"take")||
       fullmatch(cmd,L"get")||
       fullmatch(cmd,L"g")){
        size_t startp=4;
        if(fullmatch(cmd,L"get"))startp=3;
        else if(fullmatch(cmd,L"g"))startp=1;
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            printr(Red,msg->db_ridnullexceptionerror);
            return true;
        }
        wchar_t *taketarget=NULL;
        taketarget=mallocpointer(128*sizeof(wchar_t));
        wmemset(taketarget,0,128);
        nat j=0,sth=0;
        for(size_t i=startp;i<wcslen(cmd);i++){
            if(cmd[i]!=L' '&&((cmd[i]>L'9'||cmd[i]<L'0')||sth==3))sth=2;
            else{
                if(cmd[i]==L' '&&sth==1)sth=3;
                else if(cmd[i]!=L' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                taketarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&wcslen(taketarget)>0){
                j=0;
                wmemset(taketarget,0,128);
            }
        }
        nat qnty=0,qnty2=0;
        for(size_t i=startp;i<128;i++){
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
        qnty2=qnty;
        nat maxmatch=-1;
        nat maxmatchid=0;
        struct et_room *etr=et_findroomwithid(rm->id);
        if(etr==NULL){
            printr(Red,msg->db_retidnullexceptionerror);
            return true;
        }
        for(nat i=0;i<DBE_ITEMCAP;i++){
            if(etr->etitem[i]==0)continue;
            struct et_item *eti=&et_items[etr->etitem[i]-1];
            if(eti==NULL){
                printr(Red,msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            nat curmatch=match(taketarget,idb->name);
            if(curmatch>maxmatch){
                maxmatch=curmatch;
                maxmatchid=etr->etitem[i];
            }
        }
        if(maxmatch<0){
            if(taketarget[0]==L'$'){
                struct et_room *etrp=et_findroomwithid(player.roomid);
                if(etrp==NULL){
                    printc(Red,msg->db_retidnullexceptionerror);
                    return true;
                }

                nat moni=0;
                for(size_t i=1;i<wcslen(taketarget);i++){
                    if((taketarget[i]<L'0'||taketarget[i]>L'9'))break;
                    moni*=10;
                    moni+=taketarget[i]-L'0';
                }
                if(moni>etrp->money){
                    printc(Default,msg->db_retnotthatmuchmoney);
                }else if(moni){
                    etrp->money-=moni;
                    inventory.money+=moni;
                    printc(Cyan|Bright,msg->db_retplayermoneypickup,moni);
                    freepointer(taketarget);
                }
                return true;
            }
        }
        freepointer(taketarget);
        if(maxmatch>=0){
            struct et_item *eti=&et_items[maxmatchid-1];
            if(!eti->available){
                printr(Red,msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            if(idb->type&db_itemtype_stackable_mask){
                if(eti->qnty<=qnty){
                    qnty-=eti->qnty;
                    nat itemid=eti->itemid;
                    etitem_rebind(maxmatchid,0);
                    if(qnty>0){
                        for(nat i=0;i<DBE_ITEMCAP;i++){
                            if(etr->etitem[i]==0)continue;
                            struct et_item *etii=&et_items[etr->etitem[i]-1];
                            if(etii->available==false){
                                printr(Red,msg->db_ietidnullexceptionerror);
                                return true;
                            }
                            if(etii->itemid==itemid){
                                if(etii->qnty<=qnty){
                                    qnty-=etii->qnty;
                                    etitem_rebind(etr->etitem[i],0);
                                    if(qnty==0)break;
                                }else{
                                    etii->qnty-=qnty;
                                    etitem_push(etii->itemid,qnty,0,0);
                                    qnty=0;
                                    break;
                                }
                            }
                        }
                    }
                }
                else{
                    eti->qnty-=qnty;
                    etitem_push(eti->itemid,qnty,0,0);
                    qnty=0;
                }
                if(qnty2-qnty>1)printr(Cyan|Bright,msg->db_ietmulttake,idb->name,qnty2-qnty);
                else if(qnty2-qnty==1)printr(Cyan|Bright,msg->db_iettake,idb->name);
                else printr(Default,msg->db_inosuchitem);
            }
            else{
                etitem_rebind(maxmatchid,0);
                printr(Cyan|Bright,msg->db_iettake,idb->name);
            }
        }
        else{
            printr(Default,msg->db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,L"drop")){
        struct et_room *etr=et_findroomwithid(player.roomid);
        if(etr==NULL){
            printr(Red,msg->db_retidnullexceptionerror);
            return true;
        }
        wchar_t *droptarget=NULL;
        droptarget=mallocpointer(128*sizeof(wchar_t));
        wmemset(droptarget,0,128);
        nat j=0,sth=0;
        for(size_t i=4;i<wcslen(cmd);i++){
            if(cmd[i]!=L' '&&((cmd[i]>L'9'||cmd[i]<L'0')||sth==3))sth=2;
            else{
                if(cmd[i]==L' '&&sth==1)sth=3;
                else if(cmd[i]!=L' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                droptarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&wcslen(droptarget)>0){
                j=0;
                wmemset(droptarget,0,128);
            }
        }
        nat qnty=0,qnty2=0;
        for(size_t i=4;i<128;i++){
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
        qnty2=qnty;
        nat maxmatch=-1;
        nat maxmatchid=0;
        for(nat i=0;i<inventory.unlocked;i++){
            if(inventory.items[i]==0)continue;
            struct et_item *eti=&et_items[inventory.items[i]-1];
            if(eti==NULL){
                printr(Red,msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            nat curmatch=match(droptarget,idb->name);
            if(curmatch>maxmatch){
                maxmatch=curmatch;
                maxmatchid=inventory.items[i];
            }
        }
        if(maxmatch<0){
            if(droptarget[0]==L'$'){
                nat moni=0;
                for(size_t i=1;i<wcslen(droptarget);i++){
                    if((droptarget[i]<L'0'||droptarget[i]>L'9'))break;
                    moni*=10;
                    moni+=droptarget[i]-L'0';
                }
                if(moni>inventory.money){
                    printc(Default,msg->db_retplayernotthatmuchmoney);
                    return true;
                }else if(moni){
                    inventory.money-=moni;
                    struct et_room *etrp=et_findroomwithid(player.roomid);
                    if(etrp==NULL){
                        printc(Red,msg->db_retidnullexceptionerror);
                        return true;
                    }
                    etrp->money+=moni;
                    printc(Cyan|Bright,msg->db_retplayermoneydrop,moni);
                    freepointer(droptarget);
                    return true;
                }
            }
        }
        freepointer(droptarget);
        if(maxmatch>=0){
            struct et_item *eti=&et_items[maxmatchid-1];
            if(!eti->available){
                printr(Red,msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            if(idb->type&db_itemtype_stackable_mask){
                if(eti->qnty<=qnty){
                    qnty-=eti->qnty;
                    nat itemid=eti->itemid;
                    etitem_rebind(maxmatchid,player.roomid);
                    if(qnty>0){
                        for(nat i=0;i<inventory.unlocked;i++){
                            if(inventory.items[i]==0)continue;
                            struct et_item *etii=&et_items[inventory.items[i]-1];
                            if(etii->available==false){
                                printr(Red,msg->db_ietidnullexceptionerror);
                                return true;
                            }
                            if(etii->itemid==itemid){
                                if(etii->qnty<=qnty){
                                    qnty-=etii->qnty;
                                    etitem_rebind(inventory.items[i],player.roomid);
                                    if(qnty==0)break;
                                }else{
                                    etii->qnty-=qnty;
                                    etitem_push(etii->itemid,qnty,player.roomid,0);
                                    qnty=0;
                                    break;
                                }
                            }
                        }
                    }
                }else{
                    eti->qnty-=qnty;
                    etitem_push(eti->itemid,qnty,player.roomid,0);
                    qnty=0;
                }
                if(qnty2-qnty>1)printr(Cyan|Bright,msg->db_ietmultdrop,idb->name,qnty2-qnty);
                else printr(Cyan|Bright,msg->db_ietdrop,idb->name);
            }
            else{
                etitem_rebind(maxmatchid,player.roomid);
                printr(Cyan|Bright,msg->db_ietdrop,idb->name);
            }
            pcalcstats();
        }else{
            printr(Default,msg->db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,L"sell")){
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            printr(Red,msg->db_ridnullexceptionerror);
            return true;
        }
        if(rm->type!=db_roomtype_shop){
            printr(Default,msg->db_notinstore);
            return true;
        }
        wchar_t *selltarget=NULL;
        selltarget=mallocpointer(128*sizeof(wchar_t));
        wmemset(selltarget,0,128);
        nat j=0,sth=0;
        for(size_t i=4;i<wcslen(cmd);i++){
            if(cmd[i]!=L' '&&((cmd[i]>L'9'||cmd[i]<L'0')||sth==3))sth=2;
            else{
                if(cmd[i]==L' '&&sth==1)sth=3;
                else if(cmd[i]!=L' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                selltarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&wcslen(selltarget)>0){
                j=0;
                wmemset(selltarget,0,128);
            }
        }
        nat qnty=0,qnty2=0;
        for(size_t i=4;i<128;i++){
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
        qnty2=qnty;
        nat maxmatch=-1;
        nat maxmatchitemid=0;
        for(nat i=0;rm->table[i]!=0;i++){
            itemdb *idb=db_ifindwithid(rm->table[i]);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            nat curmatch=match(selltarget,idb->name);
            if(curmatch>maxmatch){
                maxmatch=curmatch;
                maxmatchitemid=idb->id;
            }else if(curmatch==maxmatch){
                for(nat k=0;k<inventory.unlocked;k++){
                    if(et_items[inventory.items[k]-1].itemid==idb->id){
                        maxmatchitemid=idb->id;
                        break;
                    }
                }
            }
        }
        freepointer(selltarget);
        if(maxmatch>=0){
            itemdb *idb=db_ifindwithid(maxmatchitemid);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
        }else{
            printr(Default,msg->db_inosuchitem);
            return true;
        }
        itemdb *idb=NULL;
        for(nat i=0;i<inventory.unlocked;i++){
            if(inventory.items[i]==0)continue;
            struct et_item *eti=&et_items[inventory.items[i]-1];
            if(eti==NULL){
                printr(Red,msg->db_ietidnullexceptionerror);
                return true;
            }
            idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return true;
            }
            if(idb->id==maxmatchitemid){
                if(idb->type&db_itemtype_stackable_mask){
                    if(eti->qnty>qnty){
                        eti->qnty-=qnty;
                        inventory.money+=(qnty*ITEM_SELLRATE*idb->price);
                        qnty=0;
                        break;
                    }else{
                        qnty-=eti->qnty;
                        inventory.money+=(eti->qnty*ITEM_SELLRATE*idb->price);
                        etitem_delete(inventory.items[i]);
                        if(qnty==0)break;
                    }
                }else{
                    etitem_delete(inventory.items[i]);
                    inventory.money+=(ITEM_SELLRATE*idb->price);
                    qnty=0;qnty2=1;
                    break;
                }
            }
        }
        pcalcstats();
        idb=db_ifindwithid(maxmatchitemid);
        if(qnty2==qnty)printr(Default,msg->db_inosuchitem);
        else if(qnty2-qnty==1)printr(Cyan|Bright,msg->db_isellitemhint,idb->name);
        else printr(Cyan|Bright,msg->db_isellmultitemhint,idb->name,qnty2-qnty);
        return true;
    }
    if(fullmatch(cmd,L"attack")||
       fullmatch(cmd,L"a")){
        size_t startp=6;
        if(fullmatch(cmd,L"a"))startp=1;
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            printr(Red,msg->db_ridnullexceptionerror);
            return true;
        }
        wchar_t *attacktarget=NULL;
        attacktarget=mallocpointer(128*sizeof(wchar_t));
        wmemset(attacktarget,0,128);
        foo sth=false;
        nat j=0;
        for(size_t i=startp;i<wcslen(cmd);i++){
            if(cmd[i]!=L' ')sth=true;
            if(sth){
                attacktarget[j]=cmd[i];
                j++;
            }
        }
        struct et_room *etr=et_findroomwithid(rm->id);
        nat maxmatch=-1;
//        nat maxmatchenemyid=0;
        nat maxmatchenemyentityid=0;
        for(nat i=0;i<DBE_ENEMYCAP;i++){
            if(etr->etenemy[i]==0)continue;
            enemydb *edb=et_getenemydb(etr->etenemy[i]);
            if(edb==NULL){
                printr(Red,msg->db_eidnullexceptionerror);
                return true;
            }
            nat curmatch=match(attacktarget,edb->name);
            if(curmatch>maxmatch){
                maxmatch=curmatch;
//                maxmatchenemyid=edb->id;
                maxmatchenemyentityid=etr->etenemy[i];
            }
        }
        freepointer(attacktarget);
        if(maxmatchenemyentityid==0){
            printr(Default,msg->db_enosuchenemy);
        }else if(maxmatch>=0){
            pattack(maxmatchenemyentityid);
        }else{
            printr(Default,msg->db_enosuchenemy);
        }
        return true;
    }
    if(fullmatch(cmd,L"ready")||
       fullmatch(cmd,L"r")){
        pready();
    }
    return false;
}
foo matcheditstatscommands(wchar_t *cmd){
    if(fullmatch(cmd,L"quit")||
       fullmatch(cmd,L"exitgame")||
       fullmatch(cmd,L"quitgame")){
        peditstatsend();
        quit_game=true;
        return true;
    }
    if(fullmatch(cmd,L"exit")){
        peditstatsend();
        return true;
    }
    if(fullmatch(cmd,L"1")){
        if(player.stats.pts){
            player.stats.pts--;
            player.stats.atk++;
        }else if(player.bstats.pts){
            player.bstats.pts--;
            player.bstats.atk++;
        }
        // the rest is the same
        else{
            printc(Default,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        if(player.stats.pts||player.bstats.pts){
        }else{
            printc(Default,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    if(fullmatch(cmd,L"2")){
        if(player.stats.pts){
            player.stats.pts--;
            player.stats.def++;
        }else if(player.bstats.pts){
            player.bstats.pts--;
            player.bstats.def++;
        }
        // the rest is the same
        else{
            printc(Default,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        if(player.stats.pts||player.bstats.pts){
        }else{
            printc(Default,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    if(fullmatch(cmd,L"3")){
        if(player.stats.pts){
            player.stats.pts--;
            player.stats.acc++;
        }else if(player.bstats.pts){
            player.bstats.pts--;
            player.bstats.acc++;
        }
        // the rest is the same
        else{
            printc(Default,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        if(player.stats.pts||player.bstats.pts){
        }else{
            printc(Default,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    if(fullmatch(cmd,L"4")){
        if(player.stats.pts){
            player.stats.pts--;
            player.stats.dod++;
        }else if(player.bstats.pts){
            player.bstats.pts--;
            player.bstats.dod++;
        }
        // the rest is the same
        else{
            printc(Default,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        if(player.stats.pts||player.bstats.pts){
        }else{
            printc(Default,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    if(fullmatch(cmd,L"5")){
        if(player.stats.pts){
            player.stats.pts--;
            player.stats.wis++;
        }else if(player.bstats.pts){
            player.bstats.pts--;
            player.bstats.wis++;
        }
        // the rest is the same
        else{
            printc(Default,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        if(player.stats.pts||player.bstats.pts){
        }else{
            printc(Default,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    if(fullmatch(cmd,L"6")){
        if(player.stats.pts){
            player.stats.pts--;
            player.stats.act++;
        }else if(player.bstats.pts){
            player.bstats.pts--;
            player.bstats.act++;
        }
        // the rest is the same
        else{
            printc(Default,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        if(player.stats.pts||player.bstats.pts){
        }else{
            printc(Default,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    if(fullmatch(cmd,L"7")){
        if(player.stats.pts){
            player.stats.pts--;
            player.stats.con++;
        }else if(player.bstats.pts){
            player.bstats.pts--;
            player.bstats.con++;
        }
        // the rest is the same
        else{
            printc(Default,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        if(player.stats.pts||player.bstats.pts){
        }else{
            printc(Default,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    printc(Default,msg->player_editstatsunknown);
    return true;
}
void processinput(){
#ifndef CB_REALTIME
    if(wcslen(inputbuf)==0){
        size_t row,col;
        cbc_getcursor(&row,&col);
        if(row>0)cbc_setcursor(row-1,0);
        if(wcslen(inputbufl)==0)return;
        printr(Yellow,L"%ls\n",inputbufl);
        matchcommands(inputbufl);
        return;
    }
#else
    if(wcslen(inputbuf)==0){
        return;
    }
#endif
    wmemset(inputbufl,0,128);
    wcscpy(inputbufl,inputbuf);
    wcslower(&inputbufl);
    if(matchcommands(inputbufl)){
        return;
    }else{
        memset(inputbufl,0,128);
    }
    printr(Cyan|Bright,msg->player_say,player.name);
    printr(Default,L"%ls\n",inputbuf);
    return;
}

#ifdef CB_REALTIME
void fscanline(wchar_t *scan_str,int scans){
    wmemset(scan_str,0,scans);
    if(!fpinput){
        fpinput=fopen("data.dmp","r");
        return;
    }
    fscanf(fpinput,"%d.%d.",&cbio_matchid,&cbio_len);
    if(cbio_matchid==cbio_matchidold){
        rewind(fpinput);
        fflush(fpinput);
        return;
    }
    if(cbio_len>=scans)cbio_len=scans-1;
    fgetws(scan_str,cbio_len+1,fpinput);
    cbio_matchidold=cbio_matchid;
    rewind(fpinput);
    fflush(fpinput);
}
void scanline(wchar_t *scan_str,int scans){
    while(1){
        cbtime_sleep(30);
        if(!fpinput){
            fpinput=fopen("data.dmp","r");
            continue;
        }
        fscanf(fpinput,"%d.%d.",&cbio_matchid,&cbio_len);
        if(cbio_matchid==cbio_matchidold){
            rewind(fpinput);
            fflush(fpinput);
            continue;
        }
        if(cbio_len>scans)cbio_len=scans-1;
        wmemset(scan_str,0,scans);
        fgetws(scan_str,cbio_len+1,fpinput);
        cbio_matchidold=cbio_matchid;
        rewind(fpinput);
        fflush(fpinput);
        break;
    }
}
#endif
#endif
