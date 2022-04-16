#ifndef Corburt_Player_h_Include_Guard
#define Corburt_Player_h_Include_Guard
//#define LVL_CAP 120
#define LVL_CAP 20
#define DMG_RATIO 0.2f
#include "dbmap.h"
const bat exp2next[]={
    [0]=20,
    [1]=60,
    [2]=130,
    [3]=250,
    [4]=430,
    [5]=700,
    [6]=1090,
    [7]=1640,
    [8]=2400,
    [9]=3430,
    [10]=4790,
    [11]=6570,
    [12]=8870,
    [13]=11810,
    [14]=15530,
    [15]=20190,
    [16]=25980,
    [17]=33130,
    [18]=41890,
    [19]=52550,
    [20]=65450,
    [21]=80980,
    [22]=99580,
    [23]=121760,
    [24]=148080,
    [25]=179190,
    [26]=215820,
    [27]=258790,
    [28]=309020,
    [29]=367540,
    [30]=435510,
    [31]=514220,
    [32]=605120,
    [33]=709810,
    [34]=830070,
    [35]=967880,
    [36]=1125430,
    [37]=1305150,
    [38]=1509710,
    [39]=1742070,
    [40]=2005490,
    [41]=2303540,
    [42]=2640160,
    [43]=3019670,
    [44]=3446810,
    [45]=3926760,
    [46]=4465190,
    [47]=5068300,
    [48]=5742860,
    [49]=6496250,
    [50]=7336510,
    [51]=8272390,
    [52]=9313400,
    [53]=10469890,
    [54]=11753090,
    [55]=13175180,
    [56]=14749360,
    [57]=16489920,
    [58]=18412340,
    [59]=20533340,
    [60]=22871010,
    [61]=25444860,
    [62]=28275960,
    [63]=31387020,
    [64]=34802510,
    [65]=38548790,
    [66]=42654230,
    [67]=47149330,
    [68]=52066880,
    [69]=57442110,
    [70]=63312830,
    [71]=69719620,
    [72]=76706000,
    [73]=84318600,
    [74]=92607390,
    [75]=101625850,
    [76]=111431230,
    [77]=122084750,
    [78]=133651860,
    [79]=146202500,
    [80]=159811360,
    [81]=174558170,
    [82]=190528000,
    [83]=207811590,
    [84]=226505670,
    [85]=246713320,
    [86]=268544320,
    [87]=292115560,
    [88]=317551440,
    [89]=344984290,
    [90]=374554850,
    [91]=406412690,
    [92]=440716770,
    [93]=477635900,
    [94]=517349330,
    [95]=560047310,
    [96]=605931680,
    [97]=655216530,
    [98]=708128820,
    [99]=764909110,
    [100]=825812270,
    [101]=891108230,
    [102]=961082810,
    [103]=1036038520,
    [104]=1116295450,
    [105]=1202192180,
    [106]=1294086730,
    [107]=1392357580,
    [108]=1497404700,
    [109]=1609650630,
    [110]=1729541670,
    [111]=1857549020,
    [112]=1994170080,
    [113]=2139929710,
    [114]=2295381630,
    [115]=2461109820,
    [116]=2637730020,
    [117]=2825891280,
    [118]=3026277580,
    [119]=3239609520,
};
const wchar_t *ranks[]={
    L"The Condemned",
    L"Regular",
    L"King",
    L"God",
    L"Void",
    L"Admin",
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
        cbp.calcstats.stl+=idb->stats.stl;
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
        cbp.calcstats.cd=10;
        cbp.calcstats.crit=0;
    }
    if(inventory.armor!=0){
        struct et_item *eti=&et_items[inventory.items[inventory.armor-1]-1];
        itemdb *idb=db_ifindwithid(eti->itemid);
        cbp.calcstats.atk+=idb->stats.atk;
        cbp.calcstats.def+=idb->stats.def;
        cbp.calcstats.acc+=idb->stats.acc;
        cbp.calcstats.dod+=idb->stats.dod;
        cbp.calcstats.stl+=idb->stats.stl;
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
            cbp.calcstats.stl+=idb->stats.stl;
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
        putc('[',stdout);
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
            printf("[");
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
    }
    { // stats
        if(player.stats.atk>99999)player.stats.atk=99999;
        if(player.stats.def>99999)player.stats.def=99999;
        if(player.stats.acc>99999)player.stats.acc=99999;
        if(player.stats.dod>99999)player.stats.dod=99999;
        if(player.stats.stl>99999)player.stats.stl=99999;
        if(player.stats.act>99999)player.stats.act=99999;
        if(player.stats.con>99999)player.stats.con=99999;
        if(player.bstats.atk>99999)player.bstats.atk=99999;
        if(player.bstats.def>99999)player.bstats.def=99999;
        if(player.bstats.acc>99999)player.bstats.acc=99999;
        if(player.bstats.dod>99999)player.bstats.dod=99999;
        if(player.bstats.stl>99999)player.bstats.stl=99999;
        if(player.bstats.act>99999)player.bstats.act=99999;
        if(player.bstats.con>99999)player.bstats.con=99999;
        cbp.calcstats.atk=player.stats.atk+player.bstats.atk;
        cbp.calcstats.def=player.stats.def+player.bstats.def;
        cbp.calcstats.acc=player.stats.acc+player.bstats.acc;
        cbp.calcstats.dod=player.stats.dod+player.bstats.dod;
        cbp.calcstats.stl=player.stats.stl+player.bstats.stl;
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
        cbp.calcstats.stl,cbp.calcstats.act,
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
    if(invitemscount==0)printr(Default,L"(none)");
    else{
        for(nat i=0,j=0;i<64;i++){
            if(inventory.items[i]!=0){
                struct et_item *eti=&et_items[inventory.items[i]-1];
                itemdb *idb=db_ifindwithid(eti->itemid);
                if(j>0)printr(Default,L"\n               ");
                if(inventory.weapon==i+1){
                    printr(Magenta|Bright,msg->player_inv_wielding);
                }
                if(inventory.armor==i+1){
                    printr(Magenta|Bright,msg->player_inv_wearing);
                }
                for(nat k=0;k<5;k++)if(inventory.accessories[k]==i+1){
                    printr(Magenta|Bright,msg->player_inv_equipping);
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
    if(!rm->exitsid[dir]){
        timepass(30);
        if(cbp.playerdead){
            cbp.playerdead=false;
            return;
        }
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
    }else{
        // special exits
    }
}
static void pmovesuccess(){
    db_rshowdesc(player.roomid);
    roomdb *rm=db_rfindwithid(player.roomid);
    if(rm->type==db_roomtype_birth&&player.spawn!=player.roomid){
        player.spawn=player.roomid;
        printr(Cyan|Bright,msg->player_spawnupdate,rm->name);
    }
}
void pattack(nat entityid){
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
    timepass(cbp.calcstats.cd);

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
            player.stats.stl,player.stats.act,
            player.stats.con,player.stats.pts);
    }else{
        printc(Default,msg->player_points,
            player.stats.atk,player.stats.def,
            player.stats.acc,player.stats.dod,
            player.stats.stl,player.stats.act,
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
        player.hp-=dmg;
        printf("[");
        nat color;
        if(player.hp<player.maxhp*0.3333333f)color=Red|Bright;
        else if(player.hp<player.maxhp*0.6666667f)color=Yellow|Bright;
        else color=Green|Bright;
        printc(color,L"%" PRIdFAST64,player.hp);
        printc(Default,L"/%" PRIdFAST64 "]\n",player.maxhp);
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
