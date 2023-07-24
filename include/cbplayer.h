#ifndef Corburt_Player_h_Include_Guard
#define Corburt_Player_h_Include_Guard
#define PLAYER_LVL_CAP 20 // for Lite
//#define PLAYER_LVL_CAP 100
#define DMG_RATIO 0.334f
#include "dbmap.h"
const bat exp2next[]={
    [0]=20,
    [1]=80,
    [2]=220,
    [3]=440,
    [4]=760,
    [5]=1200,
    [6]=2100,
    [7]=3470,
    [8]=5470,
    [9]=8330,
    [10]=12400,
    [11]=18100,
    [12]=26000,
    [13]=36780,
    [14]=51250,
    [15]=70590,
    [16]=95860,
    [17]=128700,
    [18]=171800,
    [19]=227100,
    [20]=297200,
    [21]=386400,
    [22]=499350,
    [23]=641490,
    [24]=818700,
    [25]=1039900,
    [26]=1314900,
    [27]=1655400,
    [28]=2075600,
    [29]=2592300,
    [30]=3227700,
    [31]=4004000,
    [32]=4952500,
    [33]=6108100,
    [34]=7515500,
    [35]=9220600,
    [36]=11286000,
    [37]=13786000,
    [38]=16805000,
    [39]=20443000,
    [40]=24815000,
    [41]=30068000,
    [42]=36375000,
    [43]=43931000,
    [44]=52979000,
    [45]=63792100,
    [46]=76706300,
    [47]=92102000,
    [48]=110444000,
    [49]=132282000,
    [50]=158241000,
    [51]=189103000,
    [52]=225737000,
    [53]=269157000,
    [54]=320629000,
    [55]=381558000,
    [56]=453686000,
    [57]=538951000,
    [58]=639681700,
    [59]=758603700,
    [60]=898912100,
    [61]=1064344000,
    [62]=1259276000,
    [63]=1488822000,
    [64]=1758957000,
    [65]=2076661000,
    [66]=2450259000,
    [67]=2889110000,
    [68]=3404530000,
    [69]=4009511000,
    [70]=4719195000,
    [71]=5551539000,
    [72]=6527162000,
    [73]=7670067500,
    [74]=9008182100,
    [75]=10574510000,
    [76]=12406952000,
    [77]=14550220000,
    [78]=17055669000,
    [79]=19982942000,
    [80]=23402255000,
    [81]=27395322000,
    [82]=32055989000,
    [83]=37494504000,
    [84]=43837478000,
    [85]=51233470000,
    [86]=59855072000,
    [87]=69900469300,
    [88]=81601806000,
    [89]=95228521500,
    [90]=111093246000,
    [91]=129554943000,
    [92]=151033204000,
    [93]=176019160000,
    [94]=205072467000,
    [95]=238840394000,
    [96]=278084905000,
    [97]=323682258000,
    [98]=376646975000,
    [99]=438143575000,
    [100]=509539542000,
    [101]=592406958000,
    [102]=688564228000,
    [103]=800114186200,
    [104]=929488041400,
    [105]=1079516418000,
    [106]=1253429191000,
    [107]=1455005028000,
    [108]=1688585526000,
    [109]=1959218331000,
    [110]=2272664721000,
    [111]=2635652458000,
    [112]=3055957042000,
    [113]=3542509101000,
    [114]=4105613698000,
    [115]=4757159535000,
    [116]=5510937917000,
    [117]=6382871949000,
    [118]=7391243090000,
    [119]=8557240942000,
    [120]=10000000000000
};
const char *ranks[]={
//    "Golem","Kin","Regular",
//    "Lesser Unfading","Unfading","Knight","Higher Kin",
//    "Demigod","King","Sage",
//    "God","True Sage","Carnage King",
//    "Supreme"
    "$T0Golem$o","$T0Kin$o","$T0Regular$o",
    "$T1Lesser Unfading$o","$T1Unfading$o","$T1Knight$o","$T1Higher Kin$o",
    "$T2Demigod$o","$T2King$o","$T2Sage$o",
    "$T3God$o","$T3True Sage$o","$T3Carnage King$o",
    "$T4Supreme$o"
};
const nat ranklvlcap[]={
    40,40,40,
    60,75,75,75,
    100,110,100,
    135,120,150, // 120 for the player
    99999
};
static int pswitchregprompt();
static void pmovesuccess();
static void paddgearstats();
static void plvlup();
static void pchangerank(nat targetrank);
static void pbreakready();

#include "dbitem.h"
#include "cbturn.h"

// br: breaks the "ready" state

static void plvlup(){
    if(player.lvl>=ranklvlcap[player.rnk])return;
    if(player.lvl>=120&&player.rnk!=rank_supreme)return;
    if(player.lvl>=PLAYER_LVL_CAP)return;
    player.lvl++;
    player.stats.pts+=4;
    player.stats.pts+=player.lvl/9.429f;
    pcalcstats();
    printr(palette.success,msg->player_trainsuccess,player.lvl);
}
static void pchangerank(nat targetrank){}
static void paddgearstats(){ // prep'ed
    if(inventory.weapon!=0){
        struct et_item *eti=&et_items[inventory.items[inventory.weapon-1]-1];
        itemdb *idb=db_ifindwithid(eti->itemid);
        cbp.calcstats.agi+=idb->stats.agi;
        cbp.calcstats.acc+=idb->stats.acc;
        cbp.calcstats.dod+=idb->stats.dod;
        cbp.calcstats.con+=idb->stats.con;
        cbp.calcstats.def+=idb->stats.def;
        cbp.calcstats.vit+=idb->stats.vit;
        cbp.calcstats.res+=idb->stats.res;
        cbp.calcstats.rfl+=idb->stats.rfl;
        cbp.calcstats.foc+=idb->stats.foc;
        cbp.calcstats.str+=idb->stats.str;
        cbp.calcstats.atk+=idb->stats.atk;
        cbp.calcstats.stm+=idb->stats.stm;
        cbp.calcstats.wil+=idb->stats.wil;
        cbp.calcstats.san+=idb->stats.san;
        cbp.calcstats.sat+=idb->stats.sat;
        cbp.calcstats.wis+=idb->stats.wis;
        cbp.calcstats.mag+=idb->stats.mag;
        cbp.calcstats.mat+=idb->stats.mat;
        cbp.calcstats.luck+=idb->stats.luck;
        cbp.calcstats.regen+=idb->stats.regen;
        cbp.calcstats.min_=idb->stats.min_;
        cbp.calcstats.max_=idb->stats.max_;
        cbp.calcstats.prep=idb->prep;
        cbp.calcstats.cd=idb->cd;
        cbp.calcstats.crit=idb->crit;
    }else{
        cbp.calcstats.min_=1;
        cbp.calcstats.max_=2;
        cbp.calcstats.cd=30;
        cbp.calcstats.prep=5;
        cbp.calcstats.crit=0;
    }
    if(inventory.armor!=0){
        struct et_item *eti=&et_items[inventory.items[inventory.armor-1]-1];
        itemdb *idb=db_ifindwithid(eti->itemid);
        cbp.calcstats.agi+=idb->stats.agi;
        cbp.calcstats.acc+=idb->stats.acc;
        cbp.calcstats.dod+=idb->stats.dod;
        cbp.calcstats.con+=idb->stats.con;
        cbp.calcstats.def+=idb->stats.def;
        cbp.calcstats.vit+=idb->stats.vit;
        cbp.calcstats.res+=idb->stats.res;
        cbp.calcstats.rfl+=idb->stats.rfl;
        cbp.calcstats.foc+=idb->stats.foc;
        cbp.calcstats.str+=idb->stats.str;
        cbp.calcstats.atk+=idb->stats.atk;
        cbp.calcstats.stm+=idb->stats.stm;
        cbp.calcstats.wil+=idb->stats.wil;
        cbp.calcstats.san+=idb->stats.san;
        cbp.calcstats.sat+=idb->stats.sat;
        cbp.calcstats.wis+=idb->stats.wis;
        cbp.calcstats.mag+=idb->stats.mag;
        cbp.calcstats.mat+=idb->stats.mat;
        cbp.calcstats.luck+=idb->stats.luck;
        cbp.calcstats.regen+=idb->stats.regen;
    }
    for(nat i=0;i<5;i++){
        if(inventory.accessories[i]!=0){
            struct et_item *eti=&et_items[inventory.items[inventory.accessories[i]-1]-1];
            itemdb *idb=db_ifindwithid(eti->itemid);
            cbp.calcstats.agi+=idb->stats.agi;
            cbp.calcstats.acc+=idb->stats.acc;
            cbp.calcstats.dod+=idb->stats.dod;
            cbp.calcstats.con+=idb->stats.con;
            cbp.calcstats.def+=idb->stats.def;
            cbp.calcstats.vit+=idb->stats.vit;
            cbp.calcstats.res+=idb->stats.res;
            cbp.calcstats.rfl+=idb->stats.rfl;
            cbp.calcstats.foc+=idb->stats.foc;
            cbp.calcstats.str+=idb->stats.str;
            cbp.calcstats.atk+=idb->stats.atk;
            cbp.calcstats.stm+=idb->stats.stm;
            cbp.calcstats.wil+=idb->stats.wil;
            cbp.calcstats.san+=idb->stats.san;
            cbp.calcstats.sat+=idb->stats.sat;
            cbp.calcstats.wis+=idb->stats.wis;
            cbp.calcstats.mag+=idb->stats.mag;
            cbp.calcstats.mat+=idb->stats.mat;
            cbp.calcstats.luck+=idb->stats.luck;
            cbp.calcstats.regen+=idb->stats.regen;
        }
    }
}
void paddexp(nat add){
    if(add>0)player.exp+=add;
    else if(add<0&&player.exp+add>0)player.exp+=add;
    if(player.exp>exp2next[PLAYER_LVL_CAP-1])player.exp=exp2next[PLAYER_LVL_CAP-1];
}
void phpchange(nat num){
    if(num==0)return;
    if(num>0){
        if(player.hp==player.maxhp)return;
        if(player.hp+num<player.maxhp)player.hp+=num;
        else player.hp=player.maxhp;
        printr(palette.res.hp,"HP");
        printr(palette.msg,": [");
        nat color;
        if(player.hp<player.maxhp*0.3333f)color=palette.value.low;
        else if(player.hp<player.maxhp*0.6667f)color=palette.value.mid;
        else color=palette.value.high;
        printr(color,"%" PRIdFAST64,player.hp);
        printr(palette.msg,"/%" PRIdFAST64 "]\n",player.maxhp);
    }
    else{
        if(player.hp+num>0){
            player.hp+=num;
            printr(palette.res.hp,"HP");
            printr(palette.msg,": [");
            nat color;
            if(player.hp<player.maxhp*0.3333f)color=palette.value.low;
            else if(player.hp<player.maxhp*0.6667f)color=palette.value.mid;
            else color=palette.value.high;
            printr(color,"%" PRIdFAST64,player.hp);
            printr(palette.msg,"/%" PRIdFAST64 "]\n",player.maxhp);
        }
        else pdie();
    }
}
void pdie(){ // br
    pbreakready();
    printr(palette.prompt,msg->player_die);
    // should be teleported back to the spawn point
    printr(palette.prompt,msg->player_die_xplost,(bat)(player.exp-(bat)player.exp*0.9f));
    player.exp*=0.9f;
    player.hp=player.maxhp*0.7f;
    { // drop money and item
        nat dropm=inventory.money*0.1f;
        if(dropm>0&&inventory.money>0){
            inventory.money-=dropm;
            struct et_room *etr=&et_rooms[player.roomid-1];
            if(!etr){
                warn(msg->db_retidnullexceptionerror);
                return;
            }
            etr->money+=dropm;
            printr(palette.prompt,msg->db_retmoneydrop,dropm);
        }
        nat itemsc=0;
        for(nat i=0;i<inventory.unlocked;i++){
            if(inventory.items[i]!=0)itemsc++;
        }
        if(itemsc){
            nat dropid=genRandLong(&mtrand)%itemsc;
            printf("%d/%d\n",dropid,itemsc);
            for(nat i=0,j=0;i<inventory.unlocked;i++){
                if(inventory.items[i]==0)continue;
                if(j==dropid){
                    itemdb *idb=et_getitemdb(inventory.items[i]);
                    if(idb==NULL){
                        warn(msg->db_ietidnullexceptionerror);
                        return;
                    }
                    etitem_rebind(inventory.items[i],player.roomid);
                    printr(palette.prompt,msg->db_retitemdrop,idb->name);
                    break;
                }
                j++;
            }
        }
    }
    cbp.playerdead=true;
    player.roomid=player.spawn;
    db_rshowdesc(player.roomid);
}
void pcalcstats(){
    { // hp
        player.maxhp=10;
        player.maxhp+=player.lvl*(player.lvl/1.942f);
        player.maxhp+=player.stats.con*pow(player.lvl,0.7)/2.85f;
        player.maxhp+=player.stats.con*pow(player.lvl,1.5)/32.52f;
        player.maxhp+=player.stats.con*player.stats.con*pow(player.lvl,0.7)/25972.142f;
        if(player.maxhp<1)player.maxhp=1;
        if(player.hp>player.maxhp)player.hp=player.maxhp;
    }
    { // stats
        int statcap=99999;
        if(player.stats.agi>statcap)player.stats.agi=statcap;
        if(player.stats.con>statcap)player.stats.con=statcap;
        if(player.stats.res>statcap)player.stats.res=statcap;
        if(player.stats.str>statcap)player.stats.str=statcap;
        if(player.stats.wil>statcap)player.stats.wil=statcap;
        if(player.stats.wis>statcap)player.stats.wis=statcap;
        if(player.stats.luck>statcap)player.stats.luck=statcap;
        if(player.stats.pts>statcap)player.stats.pts=statcap;
        if(player.bstats.agi>statcap)player.bstats.agi=statcap;
        if(player.bstats.con>statcap)player.bstats.con=statcap;
        if(player.bstats.res>statcap)player.bstats.res=statcap;
        if(player.bstats.str>statcap)player.bstats.str=statcap;
        if(player.bstats.wil>statcap)player.bstats.wil=statcap;
        if(player.bstats.wis>statcap)player.bstats.wis=statcap;
        if(player.bstats.luck>statcap)player.bstats.luck=statcap;
        cbp.calcstats.agi=player.stats.agi+player.bstats.agi;
        cbp.calcstats.con=player.stats.con+player.bstats.con;
        cbp.calcstats.res=player.stats.res+player.bstats.res;
        cbp.calcstats.str=player.stats.str+player.bstats.str;
        cbp.calcstats.wil=player.stats.wil+player.bstats.wil;
        cbp.calcstats.wis=player.stats.wis+player.bstats.wis;
        cbp.calcstats.luck=player.stats.luck+player.bstats.luck;
        cbp.calcstats.regen=0;
        paddgearstats();
    }
}
void pshowinfo(){

}
void pshowstatsbrief(){
    pcalcstats();
    printr(palette.msg,
        msg->player_stats_brief,
        player.name,
        ranks[player.rnk],
        player.hp,player.maxhp,(player.hp*100.0f/player.maxhp),
        player.lvl,player.exp,exp2next[player.lvl-1],(player.exp*100.0f/exp2next[player.lvl-1]),
        cbp.calcstats.agi,cbp.calcstats.con,
        cbp.calcstats.res,cbp.calcstats.str,
        cbp.calcstats.wil,cbp.calcstats.wis,
        player.stats.pts
    );
}
void pshowstats(){
    pcalcstats();
    printr(palette.msg,
        msg->player_stats,
        player.name,
        ranks[player.rnk],
        player.hp,player.maxhp,(player.hp*100.0f/player.maxhp),
        player.lvl,player.exp,exp2next[player.lvl-1],(player.exp*100.0f/exp2next[player.lvl-1]),
        cbp.calcstats.agi,cbp.calcstats.con,
        cbp.calcstats.res,cbp.calcstats.str,
        cbp.calcstats.wil,cbp.calcstats.wis,
        cbp.calcstats.acc,cbp.calcstats.dod,
        cbp.calcstats.def,cbp.calcstats.vit,
        cbp.calcstats.rfl,cbp.calcstats.foc,
        cbp.calcstats.atk,cbp.calcstats.stm,
        cbp.calcstats.san,cbp.calcstats.sat,
        cbp.calcstats.mag,cbp.calcstats.mat,
        player.stats.pts
    );
}
void pshowabl(){printr(palette.msg,msg->player_abl);}
void pshowinv(){
    nat invitemscount=0;
    for(nat i=0;i<64;i++){
        if(inventory.items[i]!=0)invitemscount++;
    }
    printr(palette.msg,
        msg->player_inv,
        inventory.money,
        invitemscount,inventory.unlocked
    );
    if(invitemscount==0)printr(palette.msg,msg->player_inv_none);
    else{
        for(nat i=0,j=0;i<64;i++){
            if(inventory.items[i]!=0){
                struct et_item *eti=&et_items[inventory.items[i]-1];
                itemdb *idb=db_ifindwithid(eti->itemid);
                if(j>0)printr(palette.msg,"\n               ");
                if(inventory.weapon==i+1){
                    printr(palette.item.interact,msg->player_inv_wielding);
                }
                if(inventory.armor==i+1){
                    printr(palette.item.interact,msg->player_inv_wearing);
                }
                for(nat k=0;k<5;k++)if(inventory.accessories[k]==i+1){
                    printr(palette.item.interact,msg->player_inv_equipping);
                    break;
                }
                printrp(palette.msg,"                ","%s ",idb->name);
                if(idb->type&db_itemtype_stackable_mask&&eti->qnty>1){
                    printrp(palette.msg,"                ","(x%" PRIdFAST32 ")",eti->qnty);
                }
                invitemscount--;
                j++;
                if(invitemscount==0)break;
            }
        }
    }
    printr(palette.msg,"\n%s",msg->line);
}
void pshowexp(){
    printr(palette.msg,msg->player_exp,player.lvl,player.exp,exp2next[player.lvl-1],(player.exp*100.0f/exp2next[player.lvl-1]));
}
void pteleport(nat roomid){
    roomdb *rm=db_rfindwithid(roomid);
    if(rm==NULL){
        warn(msg->db_ridnullexceptionerror);
        return;
    }
    player.roomid=roomid;
    db_rshowdesc(roomid);
}
void pmove(enum direction dir){ // br
    pbreakready();
    roomdb *rm=db_rfindwithid(player.roomid);
    if(rm==NULL){
        warn(msg->db_ridnullexceptionerror);
        return;
    }
    if(!rm->exits[dir]){printr(palette.promptfail,msg->player_walkno);return;}
    roomdb *rmtarget=db_rfindwithid(rm->exits[dir]);
    if(rmtarget==NULL){
        warn(msg->db_ridnullexceptionerror);
        printr(palette.promptfail,msg->player_walkno);
        return;
    }
//    if(rm->region!=rmtarget->region){
//        cbp.promptarg=dir;
//        pswitchregprompt();
//        return;
//    }
#ifndef CB_REALTIME
    timepass(30);
    if(cbp.playerdead){
        cbp.playerdead=false;
        return;
    }
#endif
    pmovedirect(dir);
}
void pmovedirect(enum direction dir){
    roomdb *rm=db_rfindwithid(player.roomid);
    player.roomid=rm->exits[dir];
    switch(dir){
    case dir_East:
        printr(palette.room.change,msg->player_walkeast);
        pmovesuccess();
        return;
    case dir_West:
        printr(palette.room.change,msg->player_walkwest);
        pmovesuccess();
        return;
    case dir_North:
        printr(palette.room.change,msg->player_walknorth);
        pmovesuccess();
        return;
    case dir_South:
        printr(palette.room.change,msg->player_walksouth);
        pmovesuccess();
        return;
    case dir_Up:
        printr(palette.room.change,msg->player_walkup);
        pmovesuccess();
        return;
    case dir_Down:
        printr(palette.room.change,msg->player_walkdown);
        pmovesuccess();
        return;
    default:
        break;
    }
    printr(palette.promptfail,msg->player_walkno);
}
static int pswitchregprompt(){ //br
    pbreakready();
    cbp.ynprompt=true;
    printr(palette.prompt,msg->player_switchregionprompt);
    return 0;
}
static void pmovesuccess(){
    db_rshowdesc(player.roomid);
    roomdb *rm=db_rfindwithid(player.roomid);
    { // enemies are waiting
        struct et_room *etr=et_findroomwithid(player.roomid);
        for(nat i=0;i<DBE_ENEMYCAP;i++){
            struct et_enemy *ete=&et_enemies[etr->etenemy[i]-1];
            if(ete->attackcd<=1)ete->attackcd+=genRandLong(&mtrand)%8+1;
        }
    }
    if(rm->type==db_roomtype_birth&&player.spawn!=player.roomid){
        player.spawn=player.roomid;
        printr(palette.inform,msg->player_spawnupdate,rm->name);
    }
}
void pready(){
    cbp.readying=true;
    if(cbp.readyframe<0)cbp.readyframe=0;
    if(cbp.isready){
        printr(palette.player.ready,msg->player_isalready);
    }
}
void preadying(){
    if(!cbp.readying)return;
    if(cbp.readyframe>=cbp.calcstats.prep&&cbp.isready==false){
        cbp.isready=true;
        printr(palette.player.ready,msg->player_isready);
    }else if(cbp.readyframe<cbp.calcstats.prep){
        cbp.readyframe++;
    }
}
static void pbreakready(){
    cbp.isready=false;
    cbp.readying=false;
    cbp.readyframe=0;
}
void pattack(nat entityid){ // br
//    if(cbp.attackcd>0){
//        printr(palette.promptfail,msg->player_cantattack);
//        return;
//    }
    struct et_enemy *ete=&et_enemies[entityid-1];
    if(!ete->available){
        warn(msg->db_eetidnullexceptionerror);
        return;
    }
    const enemydb *edb=et_getenemydb(entityid);
    bool enemycandodge;
    { // enemycandodge
        nat edod=edb->stats.dod;
        if(edb->loot.weapon)edod+=db_ifindwithid(edb->loot.weapon)->stats.dod;
        if(edb->loot.armor)edod+=db_ifindwithid(edb->loot.armor)->stats.dod;
        enemycandodge=accreduc(cbp.calcstats.acc,edod);
    }
    if(enemycandodge){
        printr(palette.player.miss,msg->db_eetyouattackmiss,edb->name);
    }else{
        nat bdmg=cbp.calcstats.atk*DMG_RATIO,edef=edb->stats.def;
        nat dmgcolor=0;
        { // player base damage
            nat delta=cbp.calcstats.max_-cbp.calcstats.min_;
            bdmg+=cbp.calcstats.min_;
            if(delta!=0){
                if(delta<0)delta=0-delta;
                bdmg+=genRandLong(&mtrand)%(delta)+cbp.calcstats.min_;
            }
            bdmg+=critdmg(cbp.calcstats.crit,cbp.calcstats.atk,cbp.calcstats.max_,&dmgcolor);
            if(bdmg<1)bdmg=1;
        }
        { // enemy defense
            if(edb->loot.weapon){
                edef+=db_ifindwithid(edb->loot.weapon)->stats.def;
            }
            if(edb->loot.armor){
                edef+=db_ifindwithid(edb->loot.armor)->stats.def;
            }
        }
        nat dmg=dmgreduc(bdmg,edef*DMG_RATIO);
        if(dmg){
            printr(palette.player.strike,msg->db_eetyouattack1,edb->name);
            printr(dmgcolor,msg->db_eetyouattack2,dmg);
            printr(palette.player.strike,msg->db_eetyouattack3);
        }
        else printr(palette.player.blocked,msg->db_eetyouattackblocked,edb->name);
        etenemy_takedamage(entityid,dmg);
    }
    pbreakready();
#ifndef CB_REALTIME
    timepass(cbp.calcstats.cd);
#else
    cbp.attackcd=cbp.calcstats.cd;
#endif
}
void ptrain(){ // br
    pbreakready();
    roomdb *rm=db_rfindwithid(player.roomid);
    if(rm==NULL){
        warn(msg->db_ridnullexceptionerror);
        return;
    }
    if(rm->type!=db_roomtype_train){
        printr(palette.promptfail,msg->player_canttrain);
        return;
    }
    if(player.lvl==PLAYER_LVL_CAP){
        printr(palette.promptfail,msg->player_canttrain_maxlvl);
        return;
    }
    if(player.lvl>=ranklvlcap[player.rnk]){
        printr(palette.promptfail,msg->player_canttrain_maxlvl);
        return;
    }
    if(player.lvl>=120&&player.rnk!=rank_supreme){
        printr(palette.promptfail,msg->player_canttrain_maxlvl);
        return;
    }
    if(player.exp<exp2next[player.lvl-1]){
        printr(palette.promptfail,msg->player_canttrain_noexp);
    }else{
        plvlup();
    }
}
void peditstats(){ // br
    pbreakready();
    if(db_rfindwithid(player.roomid)->type!=db_roomtype_train){
        printr(palette.promptfail,msg->player_canteditstats);
        return;
    }
    if(player.stats.pts){
        cbp.editstats=true;
        printr(palette.promptfail,msg->player_editstatshint);
        printr(palette.promptfail,msg->player_points,
            player.stats.agi,player.stats.con,
            player.stats.res,player.stats.str,
            player.stats.wil,player.stats.wis,
            player.stats.pts);
    }else{
        printr(palette.promptfail,msg->player_points,
            player.stats.agi,player.stats.con,
            player.stats.res,player.stats.str,
            player.stats.wil,player.stats.wis,
            player.stats.pts);
        printr(palette.promptfail,msg->player_editstatsnopoints);
    }
}
void peditstatsend(){
    cbp.editstats=false;
    pcalcstats();
    db_rshowdesc(player.roomid);
}
void pregen(){
    nat regennum=player.lvl;
    regennum+=cbp.calcstats.con;
    regennum+=cbp.calcstats.regen;
//    printr(palette.success,"Regen: +%d (extra +%d)\n",regennum,cbp.calcstats.regen);
    phpchange(regennum);
}
void ptakedmg(nat dmg){
    if(dmg<=0)return;
    if(player.hp-dmg>0){
        phpchange(0-dmg);
    }
    else{
        player.hp=0;
        pdie();
    }
}
bool pcandodge(enemydb *edb){
    nat gearacc=0;
    if(edb->loot.weapon)gearacc+=db_ifindwithid(edb->loot.weapon)->stats.acc;
    if(edb->loot.armor)gearacc+=db_ifindwithid(edb->loot.armor)->stats.acc;
    return accreduc(edb->stats.acc+gearacc,cbp.calcstats.dod);
}
#endif
