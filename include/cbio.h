#ifndef Corburt_IO_h_Include_Guard
#define Corburt_IO_h_Include_Guard
#include "cbbase.h"
#include "cbfio.h"
#include "cbplayer.h"
#include "dbmap.h"
#include "dbitem.h"
char *inputbufl=NULL;
foo fullmatch(char *str,const char *str2);
foo matchcommands(char *cmd);
foo match__commands(char *cmd); // template
foo matchregularcommands(char *cmd);
foo matcheditstatscommands(char *cmd);
foo matchyesnocommands(char *cmd);
void processinput();
#ifdef CB_REALTIME
#include "cbsys.h"
int cbio_matchid=0,cbio_matchidold=1,cbio_len=0;
FILE *fpinput=NULL;
#endif

foo fullmatch(char *str,const char *str2){
    if(str==NULL&&str2==NULL)return true;
    if(str==NULL||str2==NULL)return false;
    if(strlen(str)<strlen(str2))return false;
    if(str[0]!=str2[0])return false;
    if(strlen(str)>strlen(str2)){
        if(str[strlen(str2)]!=' ')return false;
        for(size_t i=0;i<strlen(str2);i++){
            if(str[i]!=str2[i])return false;
        }
        return true;
    }
    else{
        if(strcmp(str,str2)==0)return true;
        return false;
    }
}
foo matchcommands(char *cmd){
    if(cbp.editstats){
        return matcheditstatscommands(cmd);
    }
    if(cbp.ynprompt){
        return matchyesnocommands(cmd);
    }
    return matchregularcommands(cmd);
}
foo match__commands(char *cmd){
    if(fullmatch(cmd,"quit")||
       fullmatch(cmd,"exitgame")||
       fullmatch(cmd,"quitgame")){
        quit_game=true;
        return true;
    }
    return false;
}
foo matchregularcommands(char *cmd){
    if(fullmatch(cmd,"st")){
        pshowstatsbrief();
        return true;
    }
    if(fullmatch(cmd,"stats")||
       fullmatch(cmd,"statistics")){
        pshowstats();
        return true;
    }
    if(fullmatch(cmd,"information")||
       fullmatch(cmd,"info")||
       fullmatch(cmd,"character")||
       fullmatch(cmd,"char")||
       fullmatch(cmd,"ch")
       ){
        pshowinfo();
        return true;
    }
    if(fullmatch(cmd,"quit")||
       fullmatch(cmd,"exitgame")||
       fullmatch(cmd,"quitgame")){
        quit_game=true;
        return true;
    }
    if(fullmatch(cmd,"cls")||
       fullmatch(cmd,"clear")){
        cbc_clearscreen();
        return true;
    }
    if(fullmatch(cmd,"east")||
       fullmatch(cmd,"e")){
        pmove(dir_East);
        return true;
    }
    if(fullmatch(cmd,"west")||
       fullmatch(cmd,"w")){
        pmove(dir_West);
        return true;
    }
    if(fullmatch(cmd,"north")||
       fullmatch(cmd,"n")){
        pmove(dir_North);
        return true;
    }
    if(fullmatch(cmd,"south")||
       fullmatch(cmd,"s")){
        pmove(dir_South);
        return true;
    }
    if(fullmatch(cmd,"up")){
        pmove(dir_Up);
        return true;
    }
    if(fullmatch(cmd,"down")){
        pmove(dir_Down);
        return true;
    }
    if(fullmatch(cmd,"inventory")||
       fullmatch(cmd,"inv")){
        pshowinv();
        return true;
    }
    if(fullmatch(cmd,"experience")||
       fullmatch(cmd,"exp")||
       fullmatch(cmd,"xp")){
        pshowexp();
        return true;
    }
    if(fullmatch(cmd,"look")||
       fullmatch(cmd,"l")){
        db_rshowdesc(player.roomid);
        return true;
    }
    if(fullmatch(cmd,"train")||
       fullmatch(cmd,"tr")){
        ptrain();
        return true;
    }
    if(fullmatch(cmd,"time")||
       fullmatch(cmd,"tm")){
        showtime();
        return true;
    }
    if(fullmatch(cmd,"editstats")||
       fullmatch(cmd,"editst")){
        peditstats();
        return true;
    }
    if(fullmatch(cmd,"help")){
        printr(palette.msg,msg->global_help);
        return true;
    }
    if(fullmatch(cmd,"abilities")||
       fullmatch(cmd,"ability")||
       fullmatch(cmd,"abi")||
       fullmatch(cmd,"abl")||
       fullmatch(cmd,"ab")){
        pshowabl();
        return true;
    }
    if(fullmatch(cmd,"save")){
        savesaves();
        printr(palette.inform,msg->global_progresssaved);
        return true;
    }
    if(fullmatch(cmd,"list")){
        db_rshowtable(player.roomid);
        return true;
    }
    if(fullmatch(cmd,"buy")){
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            warn(msg->db_ridnullexceptionerror);
            return true;
        }
        if(rm->type!=db_roomtype_shop){
            printr(palette.promptfail,msg->db_notinstore);
            return true;
        }
        char *buytarget=NULL;
        buytarget=mallocpointer(128*sizeof(char));
        memset(buytarget,0,128);
        nat j=0,sth=0;
        for(size_t i=3;i<strlen(cmd);i++){
            if(cmd[i]!=' '&&((cmd[i]>'9'||cmd[i]<'0')||sth==3))sth=2;
            else{
                if(cmd[i]==' '&&sth==1)sth=3;
                else if(cmd[i]!=' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                buytarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&strlen(buytarget)>0){
                j=0;
                memset(buytarget,0,128);
            }
        }
        nat qnty=0;
        for(size_t i=3;i<128;i++){
            if((cmd[i]<'0'||cmd[i]>'9')&&!(cmd[i]==' '&&qnty==0))break;
            if(qnty){
                qnty*=10;
                qnty+=cmd[i]-'0';
                if(qnty>=ITEM_MAXSTACK){
                    qnty=ITEM_MAXSTACK;
                    break;
                }
            }
            if(cmd[i]>='1'&&cmd[i]<='9'&&qnty==0)qnty=cmd[i]-'0';
        }
        if(qnty==0)qnty=1;
        nat maxmatch=-1;
        nat maxmatchid=0;
        for(nat i=0;rm->table[i]!=0;i++){
            itemdb *idb=db_ifindwithid(rm->table[i]);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
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
                warn(msg->db_iidnullexceptionerror);
                return true;
            }
            if(idb->type&db_itemtype_stackable_mask){
                if(inventory.money>=idb->price*qnty){
                    etitem_push(idb->id,qnty,0,1);
                    return true;
                }else{
                    if(qnty==1)printr(palette.promptfail,msg->db_icantafford,idb->price*qnty-inventory.money);
                    else printr(palette.promptfail,msg->db_icantaffordmult,idb->price*qnty-inventory.money);
                }
            }
            else{
                if(inventory.money>=idb->price){
                    etitem_push(idb->id,1,0,1);
                    return true;
                }else{
                    printr(palette.promptfail,msg->db_icantafford,idb->price-inventory.money);
                }
            }
        }else{
            printr(palette.promptfail,msg->db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,"use")){
        char *usetarget=NULL;
        usetarget=mallocpointer(128*sizeof(char));
        memset(usetarget,0,128);
        foo sth=false;
        nat j=0;
        for(size_t i=3;i<strlen(cmd);i++){
            if(cmd[i]!=' ')sth=true;
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
                warn(msg->db_iidnullexceptionerror);
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
                warn(msg->db_iidnullexceptionerror);
                return true;
            }
            if(idb->type==db_itemtype_weapon){
                inventory.weapon=ininvindex+1;
                pcalcstats();
                printr(palette.inform,msg->player_inv_wield,idb->name);
            }
            if(idb->type==db_itemtype_armor){
                inventory.armor=ininvindex+1;
                pcalcstats();
                printr(palette.inform,msg->player_inv_wear,idb->name);
            }
            if(idb->type==db_itemtype_accessory){
                foo canequip=true;
                for(nat k=0;k<5;k++){
                    if(inventory.accessories[k]==ininvindex+1){
                        printr(palette.promptfail,msg->player_inv_alreadyequipped,idb->name);
                        canequip=false;
                        break;
                    }
                }
                if(canequip){
                    for(nat k=0;k<5;k++){
                        if(inventory.accessories[k]==0){
                            inventory.accessories[k]=ininvindex+1;
                            printr(palette.inform,msg->player_inv_equip,idb->name);
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
            printr(palette.promptfail,msg->db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,"take")||
       fullmatch(cmd,"get")||
       fullmatch(cmd,"g")){
        size_t startp=4;
        if(fullmatch(cmd,"get"))startp=3;
        else if(fullmatch(cmd,"g"))startp=1;
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            warn(msg->db_ridnullexceptionerror);
            return true;
        }
        char *taketarget=NULL;
        taketarget=mallocpointer(128*sizeof(char));
        memset(taketarget,0,128);
        nat j=0,sth=0;
        for(size_t i=startp;i<strlen(cmd);i++){
            if(cmd[i]!=' '&&((cmd[i]>'9'||cmd[i]<'0')||sth==3))sth=2;
            else{
                if(cmd[i]==' '&&sth==1)sth=3;
                else if(cmd[i]!=' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                taketarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&strlen(taketarget)>0){
                j=0;
                memset(taketarget,0,128);
            }
        }
        nat qnty=0,qnty2=0;
        for(size_t i=startp;i<128;i++){
            if((cmd[i]<'0'||cmd[i]>'9')&&!(cmd[i]==' '&&qnty==0))break;
            if(qnty){
                qnty*=10;
                qnty+=cmd[i]-'0';
                if(qnty>=ITEM_MAXSTACK){
                    qnty=ITEM_MAXSTACK;
                    break;
                }
            }
            if(cmd[i]>='1'&&cmd[i]<='9'&&qnty==0)qnty=cmd[i]-'0';
        }
        if(qnty==0)qnty=1;
        qnty2=qnty;
        nat maxmatch=-1;
        nat maxmatchid=0;
        struct et_room *etr=et_findroomwithid(rm->id);
        if(etr==NULL){
            warn(msg->db_retidnullexceptionerror);
            return true;
        }
        for(nat i=0;i<DBE_ITEMCAP;i++){
            if(etr->etitem[i]==0)continue;
            struct et_item *eti=&et_items[etr->etitem[i]-1];
            if(eti==NULL){
                warn(msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
                return true;
            }
            nat curmatch=match(taketarget,idb->name);
            if(curmatch>maxmatch){
                maxmatch=curmatch;
                maxmatchid=etr->etitem[i];
            }
        }
        if(maxmatch<0){
            if(taketarget[0]=='$'){
                struct et_room *etrp=et_findroomwithid(player.roomid);
                if(etrp==NULL){
                    warn(msg->db_retidnullexceptionerror);
                    return true;
                }

                nat moni=0;
                for(size_t i=1;i<strlen(taketarget);i++){
                    if((taketarget[i]<'0'||taketarget[i]>'9'))break;
                    moni*=10;
                    moni+=taketarget[i]-'0';
                }
                if(moni>etrp->money){
                    printr(palette.promptfail,msg->db_retnotthatmuchmoney);
                }else if(moni){
                    etrp->money-=moni;
                    inventory.money+=moni;
                    printr(palette.item.interact,msg->db_retplayermoneypickup,moni);
                    freepointer(taketarget);
                }
                return true;
            }
        }
        freepointer(taketarget);
        if(maxmatch>=0){
            struct et_item *eti=&et_items[maxmatchid-1];
            if(!eti->available){
                warn(msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
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
                                warn(msg->db_ietidnullexceptionerror);
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
                if(qnty2-qnty>1)printr(palette.item.interact,msg->db_ietmulttake,idb->name,qnty2-qnty);
                else if(qnty2-qnty==1)printr(palette.item.interact,msg->db_iettake,idb->name);
                else printr(palette.promptfail,msg->db_inosuchitem);
            }
            else{
                etitem_rebind(maxmatchid,0);
                printr(palette.item.interact,msg->db_iettake,idb->name);
            }
        }
        else{
            printr(palette.promptfail,msg->db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,"drop")){
        struct et_room *etr=et_findroomwithid(player.roomid);
        if(etr==NULL){
            warn(msg->db_retidnullexceptionerror);
            return true;
        }
        char *droptarget=NULL;
        droptarget=mallocpointer(128*sizeof(char));
        memset(droptarget,0,128);
        nat j=0,sth=0;
        for(size_t i=4;i<strlen(cmd);i++){
            if(cmd[i]!=' '&&((cmd[i]>'9'||cmd[i]<'0')||sth==3))sth=2;
            else{
                if(cmd[i]==' '&&sth==1)sth=3;
                else if(cmd[i]!=' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                droptarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&strlen(droptarget)>0){
                j=0;
                memset(droptarget,0,128);
            }
        }
        nat qnty=0,qnty2=0;
        for(size_t i=4;i<128;i++){
            if((cmd[i]<'0'||cmd[i]>'9')&&!(cmd[i]==' '&&qnty==0))break;
            if(qnty){
                qnty*=10;
                qnty+=cmd[i]-'0';
                if(qnty>=ITEM_MAXSTACK){
                    qnty=ITEM_MAXSTACK;
                    break;
                }
            }
            if(cmd[i]>='1'&&cmd[i]<='9'&&qnty==0)qnty=cmd[i]-'0';
        }
        if(qnty==0)qnty=1;
        qnty2=qnty;
        nat maxmatch=-1;
        nat maxmatchid=0;
        for(nat i=0;i<inventory.unlocked;i++){
            if(inventory.items[i]==0)continue;
            struct et_item *eti=&et_items[inventory.items[i]-1];
            if(eti==NULL){
                warn(msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
                return true;
            }
            nat curmatch=match(droptarget,idb->name);
            if(curmatch>maxmatch){
                maxmatch=curmatch;
                maxmatchid=inventory.items[i];
            }
        }
        if(maxmatch<0){
            if(droptarget[0]=='$'){
                nat moni=0;
                for(size_t i=1;i<strlen(droptarget);i++){
                    if((droptarget[i]<'0'||droptarget[i]>'9'))break;
                    moni*=10;
                    moni+=droptarget[i]-'0';
                }
                if(moni>inventory.money){
                    printr(palette.promptfail,msg->db_retplayernotthatmuchmoney);
                    return true;
                }else if(moni){
                    inventory.money-=moni;
                    struct et_room *etrp=et_findroomwithid(player.roomid);
                    if(etrp==NULL){
                        warn(msg->db_retidnullexceptionerror);
                        return true;
                    }
                    etrp->money+=moni;
                    printr(palette.item.interact,msg->db_retplayermoneydrop,moni);
                    freepointer(droptarget);
                    return true;
                }
            }
        }
        freepointer(droptarget);
        if(maxmatch>=0){
            struct et_item *eti=&et_items[maxmatchid-1];
            if(!eti->available){
                warn(msg->db_ietidnullexceptionerror);
                return true;
            }
            itemdb *idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
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
                                warn(msg->db_ietidnullexceptionerror);
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
                if(qnty2-qnty>1)printr(palette.item.interact,msg->db_ietmultdrop,idb->name,qnty2-qnty);
                else printr(palette.item.interact,msg->db_ietdrop,idb->name);
            }
            else{
                etitem_rebind(maxmatchid,player.roomid);
                printr(palette.item.interact,msg->db_ietdrop,idb->name);
            }
            pcalcstats();
        }else{
            printr(palette.promptfail,msg->db_inosuchitem);
        }
        return true;
    }
    if(fullmatch(cmd,"sell")){
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            warn(msg->db_ridnullexceptionerror);
            return true;
        }
        if(rm->type!=db_roomtype_shop){
            printr(palette.promptfail,msg->db_notinstore);
            return true;
        }
        char *selltarget=NULL;
        selltarget=mallocpointer(128*sizeof(char));
        memset(selltarget,0,128);
        nat j=0,sth=0;
        for(size_t i=4;i<strlen(cmd);i++){
            if(cmd[i]!=' '&&((cmd[i]>'9'||cmd[i]<'0')||sth==3))sth=2;
            else{
                if(cmd[i]==' '&&sth==1)sth=3;
                else if(cmd[i]!=' '&&sth==0)sth=1;
            }
            if(sth==1||sth==2){
                selltarget[j]=cmd[i];
                j++;
            }
            if(sth==3&&strlen(selltarget)>0){
                j=0;
                memset(selltarget,0,128);
            }
        }
        nat qnty=0,qnty2=0;
        for(size_t i=4;i<128;i++){
            if((cmd[i]<'0'||cmd[i]>'9')&&!(cmd[i]==' '&&qnty==0))break;
            if(qnty){
                qnty*=10;
                qnty+=cmd[i]-'0';
                if(qnty>=ITEM_MAXSTACK){
                    qnty=ITEM_MAXSTACK;
                    break;
                }
            }
            if(cmd[i]>='1'&&cmd[i]<='9'&&qnty==0)qnty=cmd[i]-'0';
        }
        if(qnty==0)qnty=1;
        qnty2=qnty;
        nat maxmatch=-1;
        nat maxmatchitemid=0;
        for(nat i=0;rm->table[i]!=0;i++){
            itemdb *idb=db_ifindwithid(rm->table[i]);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
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
                warn(msg->db_iidnullexceptionerror);
                return true;
            }
        }else{
            printr(palette.promptfail,msg->db_inosuchitem);
            return true;
        }
        itemdb *idb=NULL;
        for(nat i=0;i<inventory.unlocked;i++){
            if(inventory.items[i]==0)continue;
            struct et_item *eti=&et_items[inventory.items[i]-1];
            if(eti==NULL){
                warn(msg->db_ietidnullexceptionerror);
                return true;
            }
            idb=db_ifindwithid(eti->itemid);
            if(idb==NULL){
                warn(msg->db_iidnullexceptionerror);
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
        if(qnty2==qnty)printr(palette.promptfail,msg->db_inosuchitem);
        else if(qnty2-qnty==1)printr(palette.item.interact,msg->db_isellitemhint,idb->name);
        else printr(palette.item.interact,msg->db_isellmultitemhint,idb->name,qnty2-qnty);
        return true;
    }
    if(fullmatch(cmd,"attack")||
       fullmatch(cmd,"a")){
        size_t startp=6;
        if(fullmatch(cmd,"a"))startp=1;
        roomdb *rm=db_rfindwithid(player.roomid);
        if(rm==NULL){
            warn(msg->db_ridnullexceptionerror);
            return true;
        }
        char *attacktarget=NULL;
        attacktarget=mallocpointer(128*sizeof(char));
        memset(attacktarget,0,128);
        foo sth=false;
        nat j=0;
        for(size_t i=startp;i<strlen(cmd);i++){
            if(cmd[i]!=' ')sth=true;
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
                warn(msg->db_eidnullexceptionerror);
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
            printr(palette.promptfail,msg->db_enosuchenemy);
        }else if(maxmatch>=0){
            if(cbp.attackcd>0){
                printr(palette.promptfail,msg->player_cantattack);
                pbreakready();
                cbp.attackcd=cbp.calcstats.cd;
                return true;
            }
            cbp.swinging=cbp.calcstats.prep-cbp.readyframe;
            if(cbp.swinging==0)cbp.swinging=1;
            cbp.targetid=maxmatchenemyentityid;
        }else{
            printr(palette.promptfail,msg->db_enosuchenemy);
        }
        pbreakready();
        return true;
    }
    if(fullmatch(cmd,"ready")||
       fullmatch(cmd,"r")){
        pready();
        return true;
    }
    return false;
}
foo matcheditstatscommands(char *cmd){
    if(fullmatch(cmd,"quit")||
       fullmatch(cmd,"exitgame")||
       fullmatch(cmd,"quitgame")){
        peditstatsend();
        quit_game=true;
        return true;
    }
    if(fullmatch(cmd,"exit")){
        peditstatsend();
        return true;
    }
    if(fullmatch(cmd,"1")||
       fullmatch(cmd,"2")||
       fullmatch(cmd,"3")||
       fullmatch(cmd,"4")||
       fullmatch(cmd,"5")||
       fullmatch(cmd,"6")){
        if(player.stats.pts){
            if(fullmatch(cmd,"1")){
                player.stats.pts--;
                player.stats.agi++;
            }else if(fullmatch(cmd,"2")){
                player.stats.pts--;
                player.stats.con++;
            }else if(fullmatch(cmd,"3")){
                player.stats.pts--;
                player.stats.res++;
            }else if(fullmatch(cmd,"4")){
                player.stats.pts--;
                player.stats.str++;
            }else if(fullmatch(cmd,"5")){
                player.stats.pts--;
                player.stats.wil++;
            }else if(fullmatch(cmd,"6")){
                player.stats.pts--;
                player.stats.wis++;
            }
        }else{
            printr(palette.promptfail,msg->player_editstatsnopoints);
            peditstatsend();
        }
        printr(palette.msg,msg->player_points,
            player.stats.agi,player.stats.con,
            player.stats.res,player.stats.str,
            player.stats.wil,player.stats.wis,
            player.stats.pts);
        if(player.stats.pts){}else{
            printr(palette.inform,msg->player_editstatsend);
            peditstatsend();
        }
        return true;
    }
    printr(palette.promptfail,msg->player_editstatsunknown);
    return true;
}
foo matchyesnocommands(char *cmd){
    int yesnostate=0; // don't forget to cbp.ynprompt=0;!
    if(fullmatch(cmd,"quit")||
       fullmatch(cmd,"exitgame")||
       fullmatch(cmd,"quitgame")){
        cbp.ynprompt=0;
        quit_game=true;
        return true;
    }
    if(fullmatch(cmd,"yes")||
       fullmatch(cmd,"ye")||
       fullmatch(cmd,"yeah")||
       fullmatch(cmd,"ja")||
       fullmatch(cmd,"y")){
        yesnostate=1;
    }
    if(fullmatch(cmd,"no")||
       fullmatch(cmd,"nope")||
       fullmatch(cmd,"n")){
        yesnostate=-1;
    }
    switch(cbp.ynprompt){
    case 1:
        switch(yesnostate){
        case 1:
            pmovedirect(cbp.promptarg);
            break;
        default:
            printr(palette.item.gone,msg->player_switchregionpromptno);
            break;
        }
        cbp.ynprompt=0;
        break;
    default:break;
    }
    return true;
}
void processinput(){
#ifndef CB_REALTIME
    if(strlen(inputbuf)==0){
        size_t row,col;
        cbc_getcursor(&row,&col);
        if(row>0)cbc_setcursor(row-1,0);
        if(strlen(inputbufl)==0)return;
        printr(palette.input,"%s\n",inputbufl);
        matchcommands(inputbufl);
        return;
    }
#else
    if(strlen(inputbuf)==0){
        return;
    }
#endif
    memset(inputbufl,0,128);
    strcpy(inputbufl,inputbuf);
    strlower(&inputbufl);
    if(matchcommands(inputbufl)){
        player.loi++;
        return;
    }else{
        memset(inputbufl,0,128);
    }
    printr(palette.chat.player,msg->player_say,player.name);
    printr(palette.chat.text,"%s\n",inputbuf);
    return;
}

#ifdef CB_REALTIME
void fscanline(char *scan_str,int scans){
    memset(scan_str,0,scans);
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
    fgets(scan_str,cbio_len+1,fpinput);
    cbio_matchidold=cbio_matchid;
    rewind(fpinput);
    fflush(fpinput);
}
void scanline(char *scan_str,int scans){
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
        memset(scan_str,0,scans);
        fgets(scan_str,cbio_len+1,fpinput);
        cbio_matchidold=cbio_matchid;
        rewind(fpinput);
        fflush(fpinput);
        break;
    }
}
#endif
#endif
