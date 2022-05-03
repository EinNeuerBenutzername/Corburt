#ifndef Corburt_Player_h_Include_Guard
#define Corburt_Player_h_Include_Guard
//#define LVL_CAP 120
#define LVL_CAP 20
#define DMG_RATIO 0.333f
#include "dbmap.h"
const bat exp2next[]={
    [0]=20,
    [1]=50,
    [2]=100,
    [3]=180,
    [4]=320,
    [5]=550,
    [6]=930,
    [7]=1560,
    [8]=2580,
    [9]=4210,
    [10]=6790,
    [11]=10820,
    [12]=17060,
    [13]=26610,
    [14]=41110,
    [15]=62940,
    [16]=95560,
    [17]=143960,
    [18]=215300,
    [19]=319840,
    [20]=472170,
    [21]=693000,
    [22]=1011580,
    [23]=1469100,
    [24]=2123370,
    [25]=3055260,
    [26]=4377580,
    [27]=6247230,
    [28]=8881850,
    [29]=12582570,
    [30]=17765020,
    [31]=25001520,
    [32]=35078390,
    [33]=49073650,
    [34]=68462230,
    [35]=95258090,
    [36]=132206010,
    [37]=183040000,
    [38]=252830860,
    [39]=348453140,
    [40]=479211520,
    [41]=657680010,
    [42]=900824820,
    [43]=1231504830,
    [44]=1680474360,
    [45]=2289053170,
    [46]=3112681870,
    [47]=4225651290,
    [48]=5727386440,
    [49]=7750787530,
    [50]=10473290040,
    [51]=14131515660,
    [52]=19040661260,
    [53]=25620133860,
    [54]=34427412730,
    [55]=46202738750,
    [56]=61928041610,
    [57]=82904574550,
    [58]=110855110580,
    [59]=148058361250,
    [60]=197525637170,
    [61]=263232844450,
    [62]=350424918630,
    [63]=466015016510,
    [64]=619107579400,
    [65]=821683217910,
    [66]=1089494856100,
    [67]=1443239499750,
    [68]=1910089376800,
    [69]=2525691355680,
    [70]=3336776180940,
    [71]=4404561375000,
    [72]=5809186479970,
    [73]=7655490320460,
    [74]=10080531886780,
    [75]=13263375368040,
    [76]=17437813668880,
    [77]=22908903553730,
    [78]=30074442426800,
    [79]=39452848474640,
    [80]=51719334088760,
    [81]=67752814959510,
    [82]=88696709747780,
    [83]=116037703762530,
    [84]=151707733656440,
    [85]=198215974649950,
    [86]=258819574590240,
    [87]=337744405230360,
    [88]=440470350823080,
    [89]=574099833108710,
    [90]=747833643678330,
    [91]=973585057394660,
    [92]=1266772066924590,
    [93]=1647338962864590,
    [94]=2141073096189500,
    [95]=2781301408224130,
    [96]=3611075360267130,
    [97]=4685983726923080,
    [98]=6077772234838240,
    [99]=7878999661420960,
    [100]=10209024860775340,
    [101]=13221702222301660,
    [102]=17115269355757360,
    [103]=22145046800764630,
    [104]=28639743530967650,
    [105]=37022384492415310,
    [106]=47837160812769560,
    [107]=61783866769111510,
    [108]=79762051940935950,
    [109]=102927610027851320,
    [110]=132765283033245310,
    [111]=171181526067665320,
    [112]=220623411420454270,
    [113]=284230824004160180,
    [114]=366031206985228980,
    [115]=471188674958973280,
    [116]=606322573259283920,
    [117]=779914717769851030,
    [118]=1002829843867296280,
    [119]=1288980535973807190,
};
const wchar_t *ranks[]={
    L"The Condemned",
    L"Regular",
    L"King",
    L"God",
    L"Void",
    L"Dev"
};
static void pmovesuccess();

#include "dbitem.h"
#include "cbturn.h"

static void plvlup(){
    if(player.lvl>=LVL_CAP)return;
    player.lvl++;
    player.stats.pts+=4;
    player.stats.pts+=player.lvl/9.429f;
    pcalcstats();
    printr(Green|Bright,msg->player_trainsuccess,player.lvl);
}
static void paddgearstats(){
    if(inventory.weapon!=0){
        struct et_item *eti=&et_items[inventory.items[inventory.weapon-1]-1];
        itemdb *idb=db_ifindwithid(eti->itemid);
        cbp.calcstats.atk+=idb->stats.atk;
        cbp.calcstats.def+=idb->stats.def;
        cbp.calcstats.acc+=idb->stats.acc;
        cbp.calcstats.dod+=idb->stats.dod;
        cbp.calcstats.wis+=idb->stats.wis;
        cbp.calcstats.act+=idb->stats.act;
        cbp.calcstats.con+=idb->stats.con;
        cbp.calcstats.regen+=idb->stats.regen;
        cbp.calcstats.min_=idb->stats.min_;
        cbp.calcstats.max_=idb->stats.max_;
        cbp.calcstats.cd=idb->cd;
        cbp.calcstats.crit=idb->crit;
    }else{
        cbp.calcstats.min_=1;
        cbp.calcstats.max_=2;
        cbp.calcstats.cd=30;
        cbp.calcstats.crit=0;
    }
    if(inventory.armor!=0){
        struct et_item *eti=&et_items[inventory.items[inventory.armor-1]-1];
        itemdb *idb=db_ifindwithid(eti->itemid);
        cbp.calcstats.atk+=idb->stats.atk;
        cbp.calcstats.def+=idb->stats.def;
        cbp.calcstats.acc+=idb->stats.acc;
        cbp.calcstats.dod+=idb->stats.dod;
        cbp.calcstats.wis+=idb->stats.wis;
        cbp.calcstats.act+=idb->stats.act;
        cbp.calcstats.con+=idb->stats.con;
            cbp.calcstats.regen+=idb->stats.regen;
    }
    for(nat i=0;i<5;i++){
        if(inventory.accessories[i]!=0){
            struct et_item *eti=&et_items[inventory.items[inventory.accessories[i]-1]-1];
            itemdb *idb=db_ifindwithid(eti->itemid);
            cbp.calcstats.atk+=idb->stats.atk;
            cbp.calcstats.def+=idb->stats.def;
            cbp.calcstats.acc+=idb->stats.acc;
            cbp.calcstats.dod+=idb->stats.dod;
            cbp.calcstats.wis+=idb->stats.wis;
            cbp.calcstats.act+=idb->stats.act;
            cbp.calcstats.con+=idb->stats.con;
            cbp.calcstats.regen+=idb->stats.regen;
        }
    }
}
void paddexp(nat add){
    if(add>0)player.exp+=add;
    else if(add<0&&player.exp+add>0)player.exp+=add;
    if(player.exp>exp2next[LVL_CAP-1])player.exp=exp2next[LVL_CAP-1];
}
void phpchange(nat num){
    if(num==0)return;
    if(num>0){
        if(player.hp==player.maxhp)return;
        if(player.hp+num<player.maxhp)player.hp+=num;
        else player.hp=player.maxhp;
        printc(Default,L"[");
        nat color;
        if(player.hp<player.maxhp*0.3333333f)color=Red|Bright;
        else if(player.hp<player.maxhp*0.6666667f)color=Yellow|Bright;
        else color=Green|Bright;
        printc(color,L"%" PRIdFAST64,player.hp);
        printc(Default,L"/%" PRIdFAST64 "]\n",player.maxhp);
    }
    else{
        if(player.hp+num>0){
            player.hp+=num;
            printc(Default,L"[");
            nat color;
            if(player.hp<player.maxhp*0.3333333f)color=Red|Bright;
            else if(player.hp<player.maxhp*0.6666667f)color=Yellow|Bright;
            else color=Green|Bright;
            printc(color,L"%" PRIdFAST64,player.hp);
            printc(Default,L"/%" PRIdFAST64 "]\n",player.maxhp);
        }
        else pdie();
    }
}
void pdie(){
    printc(White|Bright,msg->player_die);
    // should be teleported back to the nearest spawn point
    printc(White|Bright,msg->player_die_xplost,(bat)(player.exp-(bat)player.exp*0.9f));
    player.exp*=0.9f;
    player.hp=player.maxhp*0.7f;
    { // drop money and item
        nat dropm=inventory.money*0.1f;
        if(dropm>0&&inventory.money>0){
            inventory.money-=dropm;
            struct et_room *etr=&et_rooms[player.roomid-1];
            if(!etr){
                printc(Red,msg->db_retidnullexceptionerror);
                return;
            }
            etr->money+=dropm;
            printc(White|Bright,msg->db_retmoneydrop,dropm);
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
                        printc(Red|Bright,msg->db_ietidnullexceptionerror);
                        return;
                    }
                    etitem_rebind(inventory.items[i],player.roomid);
                    printc(White|Bright,msg->db_retitemdrop,idb->name);
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
        player.maxhp+=player.stats.con*player.lvl/2.85f;
        player.maxhp+=player.stats.con*player.lvl*player.lvl/32.52f;
        player.maxhp+=player.stats.con*player.stats.con*player.lvl/25972.142f;
        if(player.maxhp<1)player.maxhp=1;
        if(player.hp>player.maxhp)player.hp=player.maxhp;
    }
    { // stats
        if(player.stats.atk>99999)player.stats.atk=99999;
        if(player.stats.def>99999)player.stats.def=99999;
        if(player.stats.acc>99999)player.stats.acc=99999;
        if(player.stats.dod>99999)player.stats.dod=99999;
        if(player.stats.wis>99999)player.stats.wis=99999;
        if(player.stats.act>99999)player.stats.act=99999;
        if(player.stats.con>99999)player.stats.con=99999;
        if(player.bstats.atk>99999)player.bstats.atk=99999;
        if(player.bstats.def>99999)player.bstats.def=99999;
        if(player.bstats.acc>99999)player.bstats.acc=99999;
        if(player.bstats.dod>99999)player.bstats.dod=99999;
        if(player.bstats.wis>99999)player.bstats.wis=99999;
        if(player.bstats.act>99999)player.bstats.act=99999;
        if(player.bstats.con>99999)player.bstats.con=99999;
        cbp.calcstats.atk=player.stats.atk+player.bstats.atk;
        cbp.calcstats.def=player.stats.def+player.bstats.def;
        cbp.calcstats.acc=player.stats.acc+player.bstats.acc;
        cbp.calcstats.dod=player.stats.dod+player.bstats.dod;
        cbp.calcstats.wis=player.stats.wis+player.bstats.wis;
        cbp.calcstats.act=player.stats.act+player.bstats.act;
        cbp.calcstats.con=player.stats.con+player.bstats.con;
        paddgearstats();
    }
}
void pshowstats(){
    pcalcstats();
    printr(Default,
        msg->player_info,
        player.name,
        ranks[player.rnk],
        player.hp,player.maxhp,(player.hp*100.0f/player.maxhp),
        player.lvl,player.exp,exp2next[player.lvl-1],(player.exp*100.0f/exp2next[player.lvl-1]),
        cbp.calcstats.atk,cbp.calcstats.def,
        cbp.calcstats.acc,cbp.calcstats.dod,
        cbp.calcstats.wis,cbp.calcstats.act,
        cbp.calcstats.con,player.stats.pts
    );
}
void pshowabl(){printr(Default,msg->player_abl);}
void pshowinv(){
    nat invitemscount=0;
    for(nat i=0;i<64;i++){
        if(inventory.items[i]!=0)invitemscount++;
    }
    printr(Default,
        msg->player_inv,
        inventory.money,
        invitemscount,inventory.unlocked
    );
    if(invitemscount==0)printr(Default,msg->player_inv_none);
    else{
        for(nat i=0,j=0;i<64;i++){
            if(inventory.items[i]!=0){
                struct et_item *eti=&et_items[inventory.items[i]-1];
                itemdb *idb=db_ifindwithid(eti->itemid);
                if(j>0)printr(Default,L"\n               ");
                if(inventory.weapon==i+1){
                    printr(Cyan|Bright,msg->player_inv_wielding);
                }
                if(inventory.armor==i+1){
                    printr(Cyan|Bright,msg->player_inv_wearing);
                }
                for(nat k=0;k<5;k++)if(inventory.accessories[k]==i+1){
                    printr(Cyan|Bright,msg->player_inv_equipping);
                    break;
                }
                printrp(Default,L"                ",L"%ls ",idb->name);
                if(idb->type&db_itemtype_stackable_mask&&eti->qnty>1){
                    printrp(Default,L"                ",L"(x%" PRIdFAST32 ")",eti->qnty);
                }
                invitemscount--;
                j++;
                if(invitemscount==0)break;
            }
        }
    }
    printr(Default,L"\n%ls",msg->line);
}
void pshowexp(){
    printr(Default,msg->player_exp,player.lvl,player.exp,exp2next[player.lvl-1],(player.exp*100.0f/exp2next[player.lvl-1]));
}
void pmove(enum direction dir){ // ready for special exits
    roomdb *rm=db_rfindwithid(player.roomid);
    if(rm==NULL){
        printr(Red,msg->db_ridnullexceptionerror);
        return;
    }
    if(!rm->exits[dir]){printr(Default,msg->player_walkno);return;}
    if(db_rfindwithid(rm->exits[dir])==NULL){printr(Default,msg->player_walkno);return;}
#ifndef CB_REALTIME
    timepass(30);
    if(cbp.playerdead){
        cbp.playerdead=false;
        return;
    }
#endif
    player.roomid=rm->exits[dir];
    switch(dir){
    case dir_East:
        printr(Green,msg->player_walkeast);
        pmovesuccess();
        return;
    case dir_West:
        printr(Green,msg->player_walkwest);
        pmovesuccess();
        return;
    case dir_North:
        printr(Green,msg->player_walknorth);
        pmovesuccess();
        return;
    case dir_South:
        printr(Green,msg->player_walksouth);
        pmovesuccess();
        return;
    case dir_Up:
        printr(Green,msg->player_walkup);
        pmovesuccess();
        return;
    case dir_Down:
        printr(Green,msg->player_walkdown);
        pmovesuccess();
        return;
    default:
        break;
    }
    printr(Default,msg->player_walkno);
}
static void pmovesuccess(){
    db_rshowdesc(player.roomid);
    roomdb *rm=db_rfindwithid(player.roomid);
    { // enemies are waiting
        struct et_room *etr=et_findroomwithid(player.roomid);
        for(nat i=0;i<DBE_ENEMYCAP;i++){
            struct et_enemy *ete=&et_enemies[etr->etenemy[i]-1];
            if(ete->attackcd<=1)ete->attackcd+=genRandLong(&mtrand)%5+1;
        }
    }
    if(rm->type==db_roomtype_birth&&player.spawn!=player.roomid){
        player.spawn=player.roomid;
        printr(Cyan|Bright,msg->player_spawnupdate,rm->name);
    }
}
void pattack(nat entityid){
    if(cbp.attackcd>0){
        printr(Default,msg->player_cantattack);
        cbp.attackcd=cbp.calcstats.cd;
        return;
    }
    struct et_enemy *ete=&et_enemies[entityid-1];
    if(!ete->available){
        printc(Red,msg->db_eetidnullexceptionerror);
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
        printc(White,msg->db_eetyouattackmiss,edb->name);
    }else{
        nat bdmg=cbp.calcstats.atk*DMG_RATIO,edef=edb->stats.def;
        { // player base damage
            nat delta=cbp.calcstats.max_-cbp.calcstats.min_;
            bdmg+=cbp.calcstats.min_;
            if(delta!=0){
                if(delta<0)delta=0-delta;
                bdmg+=genRandLong(&mtrand)%(delta)+cbp.calcstats.min_;
            }
            if(genRandLong(&mtrand)%10000<cbp.calcstats.crit){
                bdmg+=cbp.calcstats.max_;
            }
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
        if(dmg)printc(Green|Bright,msg->db_eetyouattack,edb->name,dmg);
        else printc(White,msg->db_eetyouattackblocked,edb->name);
        etenemy_takedamage(entityid,dmg);
    }
#ifndef CB_REALTIME
    timepass(cbp.calcstats.cd);
#else
    cbp.attackcd=cbp.calcstats.cd;
#endif
}
void ptrain(){
    roomdb *rm=db_rfindwithid(player.roomid);
    if(rm==NULL){
        printr(Red,msg->db_ridnullexceptionerror);
        return;
    }
    if(rm->type!=db_roomtype_train){
        printr(Default,msg->player_canttrain);
        return;
    }
    if(player.lvl==LVL_CAP){
        printr(Default,msg->player_canttrain_maxlvl);
        return;
    }
    if(player.exp<exp2next[player.lvl-1]){
        printr(Default,msg->player_canttrain_noexp);
    }else{
        plvlup();
    }
}
void peditstats(){
    if(db_rfindwithid(player.roomid)->type!=db_roomtype_train){
        printc(Default,msg->player_canteditstats);
        return;
    }
    if(player.stats.pts||player.bstats.pts){
        cbp.editstats=true;
        printr(Default,msg->player_editstatshint);
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
    }else{
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.wis,player.stats.act,
            player.stats.con,player.stats.pts);
        printc(Default,msg->player_editstatsnopoints);
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
//    printc(Cyan,"Regen: +%d (extra +%d)\n",regennum,cbp.calcstats.regen);
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
