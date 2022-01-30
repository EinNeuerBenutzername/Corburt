#ifndef Corburt_Player_h_Include_Guard
#define Corburt_Player_h_Include_Guard
//#define LVL_CAP 120
#define LVL_CAP 20
#include "dbitem.h"
#include "dbmap.h"
const bat exp2next[]={
    [0]=20,
    [1]=64,
    [2]=132,
    [3]=225,
    [4]=344,
    [5]=490,
    [6]=665,
    [7]=871,
    [8]=1110,
    [9]=1384,
    [10]=1696,
    [11]=2050,
    [12]=2450,
    [13]=2902,
    [14]=3412,
    [15]=3988,
    [16]=4639,
    [17]=5376,
    [18]=6212,
    [19]=7163,
    [20]=8248,
    [21]=9490,
    [22]=10916,
    [23]=12559,
    [24]=14458,
    [25]=16660,
    [26]=19222,
    [27]=22212,
    [28]=25712,
    [29]=29820,
    [30]=34653,
    [31]=40352,
    [32]=47086,
    [33]=55058,
    [34]=64512,
    [35]=75740,
    [36]=89093,
    [37]=104992,
    [38]=123942,
    [39]=146550,
    [40]=173543,
    [41]=205794,
    [42]=244351,
    [43]=290471,
    [44]=345663,
    [45]=411737,
    [46]=490865,
    [47]=585654,
    [48]=699232,
    [49]=835353,
    [50]=998522,
    [51]=1194144,
    [52]=1428706,
    [53]=1709992,
    [54]=2047343,
    [55]=2451968,
    [56]=2937318,
    [57]=3519534,
    [58]=4217985,
    [59]=5055914,
    [60]=6061212,
    [61]=7267349,
    [62]=8714489,
    [63]=10450829,
    [64]=12534205,
    [65]=15034020,
    [66]=18033558,
    [67]=21632759,
    [68]=25951552,
    [69]=31133851,
    [70]=37352353,
    [71]=44814295,
    [72]=53768361,
    [73]=64512972,
    [74]=77406233,
    [75]=92877870,
    [76]=111443554,
    [77]=133722090,
    [78]=160456045,
    [79]=192536499,
    [80]=231032747,
    [81]=277227944,
    [82]=332661876,
    [83]=399182286,
    [84]=479006466,
    [85]=574795166,
    [86]=689741286,
    [87]=827676306,
    [88]=993198002,
    [89]=1191823705,
    [90]=1430174212,
    [91]=1716194480,
    [92]=2059418457,
    [93]=2471286881,
    [94]=2965528637,
    [95]=3558618388,
    [96]=4270325729,
    [97]=5124374174,
    [98]=6149231940,
    [99]=7379060887,
    [100]=8854855247,
    [101]=10625808099,
    [102]=12750951137,
    [103]=15301122394,
    [104]=18361327510,
    [105]=22033573253,
    [106]=26440267744,
    [107]=31728300729,
    [108]=38073939903,
    [109]=45688706499,
    [110]=54826425998,
    [111]=65791688976,
    [112]=78950004125,
    [113]=94739981875,
    [114]=113687954743,
    [115]=136425521748,
    [116]=163710601714,
    [117]=196452697229,
    [118]=235743211399,
    [119]=235743211399
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
struct {
    struct calcstats{
        nat atk;
        nat def;
        nat acc;
        nat dod;
        nat stl;
        nat act;
        nat con;
        nat pts;
    } calcstats;
} cbp;

static void plvlup();
static void paddgearstats();
void paddexp(nat add);
void pcalcstats();
void pshowstats();
void pshowabl();
void pshowinv();
void pshowexp();
void pmove(enum direction dir);
void pattack();
void ptrain();
void peditstats();

static void plvlup(){
    if(player.lvl>=LVL_CAP)return;
    player.lvl++;
    player.stats.pts+=4;
    player.stats.pts+=player.lvl/9.257f;
    player.maxhp=10;
    player.maxhp+=player.lvl*player.lvl/1.942f;
    player.maxhp+=player.stats.con*player.lvl/2.85f;
    player.maxhp+=player.stats.con*player.lvl*player.lvl/32.52f;
    player.maxhp+=player.stats.con*player.stats.con*player.lvl/25972.142f;
    printr(Green|Bright,msg_player_trainsuccess,player.lvl);
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
        }
    }
}
void paddexp(nat add){
    if(add>0)player.exp+=add;
    else if(add<0&&player.exp+add>0)player.exp+=add;
    if(player.exp>exp2next[LVL_CAP-1])player.exp=exp2next[LVL_CAP-1];
}
void pcalcstats(){
    if(player.stats.atk>99999)player.stats.atk=99999;
    if(player.stats.def>99999)player.stats.def=99999;
    if(player.stats.acc>99999)player.stats.acc=99999;
    if(player.stats.dod>99999)player.stats.dod=99999;
    if(player.stats.stl>99999)player.stats.stl=99999;
    if(player.stats.act>99999)player.stats.act=99999;
    if(player.stats.con>99999)player.stats.con=99999;
    cbp.calcstats.atk=player.stats.atk;
    cbp.calcstats.def=player.stats.def;
    cbp.calcstats.acc=player.stats.acc;
    cbp.calcstats.dod=player.stats.dod;
    cbp.calcstats.stl=player.stats.stl;
    cbp.calcstats.act=player.stats.act;
    cbp.calcstats.con=player.stats.con;
    paddgearstats();
}
void pshowstats(){
    pcalcstats();
    printr(Default,
        msg_player_info,
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
void pshowabl(){printr(Default,msg_player_abl);}
void pshowinv(){
    nat invitemscount=0;
    for(nat i=0;i<64;i++){
        if(inventory.items[i]!=0)invitemscount++;
    }
    printr(Default,
        msg_player_inv,
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
                    printr(Magenta|Bright,msg_player_inv_wielding);
                }
                if(inventory.armor==i+1){
                    printr(Magenta|Bright,msg_player_inv_wearing);
                }
                for(nat k=0;k<5;k++)if(inventory.accessories[k]==i+1){
                    printr(Magenta|Bright,msg_player_inv_equipping);
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
    printr(Default,L"\n%ls",msg_line);
}
void pshowexp(){
    printr(Default,msg_player_exp,player.lvl,player.exp,exp2next[player.lvl-1],(player.exp*100.0f/exp2next[player.lvl-1]));
}
void pmove(enum direction dir){ // ready for special exits
    roomdb *rm=db_rfindwithid(player.roomid);
    if(rm==NULL){
        printr(Red,msg_db_ridnullexceptionerror);
        return;
    }
    if(!rm->exits[dir]){printr(Default,msg_player_walkno);return;}
    if(db_rfindwithid(rm->exits[dir])==NULL){printr(Default,msg_player_walkno);return;}
    if(!rm->exitsid[dir]){
        player.roomid=rm->exits[dir];
        switch(dir){
        case dir_East:
            printr(Green,msg_player_walkeast);
            db_rshowdesc(player.roomid);
            return;
        case dir_West:
            printr(Green,msg_player_walkwest);
            db_rshowdesc(player.roomid);
            return;
        case dir_North:
            printr(Green,msg_player_walknorth);
            db_rshowdesc(player.roomid);
            return;
        case dir_South:
            printr(Green,msg_player_walksouth);
            db_rshowdesc(player.roomid);
            return;
        case dir_Up:
            printr(Green,msg_player_walkup);
            db_rshowdesc(player.roomid);
            return;
        case dir_Down:
            printr(Green,msg_player_walkdown);
            db_rshowdesc(player.roomid);
            return;
        default:
            break;
        }
        printr(Default,msg_player_walkno);
    }else{
        // special exits
    }
}
void pattack(){}
void ptrain(){
    roomdb *rm=db_rfindwithid(player.roomid);
    if(rm==NULL){
        printr(Red,msg_db_ridnullexceptionerror);
        return;
    }
    if(rm->type!=db_roomtype_train){
        printr(Default,msg_player_canttrain);
        return;
    }
    if(player.lvl==LVL_CAP){
        printr(Default,msg_player_canttrain_maxlvl);
        return;
    }
    if(player.exp<exp2next[player.lvl-1]){
        printr(Default,msg_player_canttrain_noexp);
    }else{
        plvlup();
    }
}
void peditstats(){}
#endif
