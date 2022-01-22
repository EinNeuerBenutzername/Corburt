#ifndef Corburt_Player_h_Include_Guard
#define Corburt_Player_h_Include_Guard
#include "dbitem.h"
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
    [118]=235743211399
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
void pshowstats();
void pshowinventory();
void pshowexp();
enum direction{
    dir_East,dir_West,dir_North,dir_South,dir_Up,dir_Down
};
void pmove(enum direction dir);
void pattack();
void ptrain();
void peditstats();
void pshowstats(){
    printc(Default,
        msg_player_info,
        player.name,
        ranks[player.rnk],
        player.hp,player.maxhp,(player.hp*100.0f/player.maxhp),
        player.lvl,player.exp,exp2next[player.lvl-1],(player.exp*100.0f/exp2next[player.lvl-1]),
        player.stats.atk,player.stats.def,
        player.stats.acc,player.stats.dod,
        player.stats.stl,player.stats.act,
        player.stats.con,player.stats.pts
    );
}
void pshowinventory(){
    wchar_t *itemname=mallocpointer(128*sizeof(wchar_t));
    wchar_t *itemname2=mallocpointer(128*sizeof(wchar_t));
    wmemset(itemname,0,128);
    wmemset(itemname2,0,128);
    nat itemscount=0;
    for(nat i=0;i<64;i++){
        if(inventory.items[i]!=0)itemscount++;
    }
    getitemname(inventory.weapon,itemname);
    getitemname(inventory.armor,itemname2);
    printc(Default,
        msg_player_inv,
        inventory.money,
        itemname,
        itemname2,
        itemscount,inventory.unlocked
    );
    for(nat i=0;i<64;i++){
        if(inventory.items[i]!=0){
            wmemset(itemname,0,128);
            getitemname(inventory.items[i],itemname);
            if(itemscount>1)printc(Default,L"%ls, ",itemname);
            else printc(Default,L"%ls",itemname);
            itemscount--;
            if(itemscount==0)break;
        }
    }
    printc(Default,msg_line);
    freepointer(itemname);
    freepointer(itemname2);
}
void pshowexp(){}
void pmove(enum direction dir){nat n=dir;n++;if(n<5)return;}
void pattack(){}
void ptrain(){}
void peditstats(){}
#endif
