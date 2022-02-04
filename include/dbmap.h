#ifndef Corburt_Database_Map_h_Include_Guard
#define Corburt_Database_Map_h_Include_Guard
#include "cbbase.h"
enum db_roomtype{
    db_roomtype_plain,
    db_roomtype_birth,
    db_roomtype_store,
    db_roomtype_shop=db_roomtype_store,
    db_roomtype_train,
    db_roomtype_gate
};
enum db_roomregion{
    db_roomregion_nlcity, // nameless city
    db_roomregion_forest, // forests of wrath
};
typedef const struct {
    nat id;
    enum db_roomregion region;
    wchar_t *name;
    wchar_t *desc;
    enum db_roomtype type;
    nat exits[6];
    nat exitsid[6];
    nat table[32];
    nat buff[4];
} roomdb;

roomdb roomdbs[]={
    {.id=1,
        .region=db_roomregion_nlcity,
        .name=L"Town Square of the Nameless City",
        .desc=L"You have come to the town square of a nameless city. It lies in the "
                "center of the city.",
        .type=db_roomtype_birth,
        .exits={[dir_North]=2,[dir_West]=5,[dir_South]=13,[dir_East]=19}
    },
    {.id=2,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"This ordinary street runs south and north, passing through the "
                "center of the city. There are few pedestrians on the street.",
        .type=db_roomtype_plain,
        .exits={[dir_North]=10,[dir_West]=3,[dir_South]=1,[dir_East]=23}
    },
    {.id=3,
        .region=db_roomregion_nlcity,
        .name=L"Alley",
        .desc=L"The Alley leads to the park in the city. The reason the park was "
                "built had disappeared along with the city's name.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=4,[dir_East]=2}
    },
    {.id=4,
        .region=db_roomregion_nlcity,
        .name=L"Park Entrance",
        .desc=L"You stand at the entrance of the park. Stone statues of two guards "
                "stand on either side of the entrance.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=3,[dir_South]=6,[dir_North]=7,[dir_West]=9}
    },
    {.id=5,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"You see old houses on both sides of the street, some are inhabited.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=1,[dir_South]=20,[dir_West]=6}
    },
    {.id=6,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"Houses around seems to get older and older.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=5,[dir_South]=16,[dir_North]=4,[dir_West]=49}
    },
    {.id=7,
        .region=db_roomregion_nlcity,
        .name=L"Park",
        .desc=L"The weeds are growing tall and apparently not managed well, among "
                "which exotic plants are sparsely visible. The roads are lined with "
                "wooden guardrails, apparently made of precious wood.",
        .type=db_roomtype_plain,
        .exits={[dir_South]=4,[dir_North]=51,[dir_West]=8}
    },
    {.id=8,
        .region=db_roomregion_nlcity,
        .name=L"Park",
        .desc=L"You see woods with transparent amber leaves, trees with leaves that "
                "look like pure gold, shrub with crimson vines that bleed, herbs "
                "with blooming fantastic flowers that flickers, et cetera.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=7,[dir_South]=9}
    },
    {.id=9, // shop
        .region=db_roomregion_nlcity,
        .name=L"Park Shop",
        .desc=L"A shop can be seen among the lush vegetation.",
        .type=db_roomtype_shop,
        .exits={[dir_East]=4,[dir_North]=8},
        .table={8,9,10,11,12,13,14,15,1}
    },
    {.id=10,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"There are two stores on the sides of this part of the street, great "
                "for novice adventurers.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=22,[dir_South]=2,[dir_North]=11,[dir_West]=21}
    },
    {.id=11,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"The street goes further north.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=42,[dir_South]=10,[dir_North]=12,[dir_West]=50}
    },
    {.id=12, // gate // wip
        .region=db_roomregion_nlcity,
        .name=L"City Entrance",
        .desc=L"You have arrived at the entrance of this small city. The city does "
                "not have a name, but it can also be said that its name is exactly "
                "\"the Nameless City\".\n"
                "No one guards this entrance. A row of stone statues of soldiers "
                "stand here, and they look as if they were still alive.",
        .type=db_roomtype_gate,
        .exits={[dir_South]=11}
    },
    {.id=13,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"There is a not-so-thick layer of dust on the floor of the street. "
                "The wind picks up dust when it blows.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=36,[dir_South]=14,[dir_North]=1,[dir_West]=20}
    },
    {.id=14,
        .region=db_roomregion_nlcity,
        .name=L"Street Intersection",
        .desc=L"This is a small intersection. The road to the west seems to lead to "
                "a dark path.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=37,[dir_South]=15,[dir_North]=13,[dir_West]=18}
    },
    {.id=15, // gate // wip
        .region=db_roomregion_nlcity,
        .name=L"City Gate",
        .desc=L"You are at the southern gate of the city. A group of stone soldiers "
                "salute to the south.",
        .type=db_roomtype_gate,
        .exits={[dir_North]=14}
    },
    {.id=16,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"It looks a little dark.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=20,[dir_South]=17,[dir_North]=6}
    },
    {.id=17,
        .region=db_roomregion_nlcity,
        .name=L"Darker Path",
        .desc=L"This path is very dark, definitely not the safest place to go.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=18,[dir_North]=16,[dir_West]=47},
        .table={1,2,2}
    },
    {.id=18,
        .region=db_roomregion_nlcity,
        .name=L"Dark Path",
        .desc=L"The path is dark. The low eaves of the houses block light that "
                "comes in.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=17,[dir_East]=14,[dir_North]=20,[dir_South]=45},
        .table={1}
    },
    {.id=19,
        .region=db_roomregion_nlcity,
        .name=L"Training Grounds",
        .desc=L"An elderly swordsman stood in the room practicing his myriad arts "
                "techniques. He looks more like a machine or a golem than a human.",
        .type=db_roomtype_train,
        .exits={[dir_West]=1}
    },
    {.id=20,
        .region=db_roomregion_nlcity,
        .name=L"Residential Area",
        .desc=L"You walk through the residential area in the city. There are not "
                "many residents here, and two thirds of the houses are empty.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=13,[dir_South]=18,[dir_North]=5,[dir_West]=16}
    },
    {.id=21, // shop
        .region=db_roomregion_nlcity,
        .name=L"Adventurer's Shop",
        .desc=L"A man sits at the counter. He has a large scar on his face.",
        .type=db_roomtype_shop,
        .exits={[dir_East]=10},
        .table={2,3,6,4,7,5,  16,17,18,19,20,21,22,23,24}
    },
    {.id=22, // shop
        .region=db_roomregion_nlcity,
        .name=L"Mad Alchemist's Shop",
        .desc=L"The mad alchemist stares at you. In his hand he holds a bottle of "
                "potion that kept changing colors. Looks toxic.",
        .type=db_roomtype_shop,
        .exits={[dir_West]=10,[dir_South]=23,[dir_East]=24},
        .table={26,27,25,28}
    },
    {.id=23, // shop
        .region=db_roomregion_nlcity,
        .name=L"Market",
        .desc=L"Various cheap items are available in the market.",
        .type=db_roomtype_shop,
        .exits={[dir_West]=2,[dir_North]=22,[dir_East]=25},
        .table={31,29,33,30,32,6,34,35,36,37}
    },
    {.id=24,
        .region=db_roomregion_nlcity,
        .name=L"Side Street Junction",
        .desc=L"The side street ends here. You can see a path to the east.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=22,[dir_East]=26,[dir_South]=25}
    },
    {.id=25,
        .region=db_roomregion_nlcity,
        .name=L"Side Street",
        .desc=L"The side street runs parallel to main street, which connects the "
                "entrance and the southern gate of the city.",
        .type=db_roomtype_plain,
        .exits={[dir_North]=24,[dir_South]=32,[dir_West]=23}
    },
    {.id=26,
        .region=db_roomregion_nlcity,
        .name=L"Path",
        .desc=L"To the east is the cemetery.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=24,[dir_North]=44,[dir_East]=27}
    },
    {.id=27,
        .region=db_roomregion_nlcity,
        .name=L"Cemetery Path",
        .desc=L"You stand at the end of the narrow path that leads to the cemetery. "
                "The cemetery is on low ground and you can see most of the cemetery "
                "from this location. Yet the eastern part of the cemetery is "
                "shrouded in darkness.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=26,[dir_East]=28}
    },
    {.id=28,
        .region=db_roomregion_nlcity,
        .name=L"Cemetery",
        .desc=L"There are tombstones all around. Apparently, the number of "
                "tombstones is far greater than the number of inhabitants of the "
                "town.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=27,[dir_East]=31,[dir_South]=29}
    },
    {.id=29,
        .region=db_roomregion_nlcity,
        .name=L"Cemetery",
        .desc=L"Tombstones are crowded.",
        .type=db_roomtype_plain,
        .exits={[dir_North]=28,[dir_East]=30}
    },
    {.id=30,
        .region=db_roomregion_nlcity,
        .name=L"Cemetery",
        .desc=L"Do not disturb the peace of the dead.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=29,[dir_North]=31},
        .table={6,6}
    },
    {.id=31,
        .region=db_roomregion_nlcity,
        .name=L"Cemetery",
        .desc=L"Is it because the city was once too prosperous, or because it is "
                "too decadent now? Or is it neither, just because the history here "
                "is too old?",
        .type=db_roomtype_plain,
        .exits={[dir_West]=28,[dir_South]=30},
        .table={6}
    },
    {.id=32,
        .region=db_roomregion_nlcity,
        .name=L"Side Street",
        .desc=L"This is another T-junction on the side street.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=33,[dir_South]=35,[dir_North]=25}
    },
    {.id=33,
        .region=db_roomregion_nlcity,
        .name=L"Alley",
        .desc=L"It's not very clean and there is some unknown garbage on the ground.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=32,[dir_South]=34}
    },
    {.id=34,
        .region=db_roomregion_nlcity,
        .name=L"Alley Dead End",
        .desc=L"Cascading houses prevent you from going further south.",
        .type=db_roomtype_plain,
        .exits={[dir_North]=33},
        .table={1}
    },
    {.id=35,
        .region=db_roomregion_nlcity,
        .name=L"Side Street Curve",
        .desc=L"Some robbers like to crouch at the bend of the road to rob.",
        .type=db_roomtype_plain,
        .exits={[dir_North]=32,[dir_West]=36},
        .table={5}
    },
    {.id=36,
        .region=db_roomregion_nlcity,
        .name=L"Side Street Curve",
        .desc=L"How is the law and order maintained here? No one is patrolling the "
                "streets at all.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=13,[dir_East]=35,[dir_South]=37}
    },
    {.id=37,
        .region=db_roomregion_nlcity,
        .name=L"Side Street",
        .desc=L"Here the side street merges with the main road, leading to the gate "
                "to the south.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=14,[dir_North]=36,[dir_South]=38}
    },
    {.id=38,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"It can be seen that this lake used to be a standard circle.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=39,[dir_North]=37,[dir_South]=41}
    },
    {.id=39,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"There are many fish in the lake. Obviously, each of them is very "
                "valuable.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=38,[dir_South]=40}
    },
    {.id=40,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"The water is relatively clear and you can see the deep bottom of "
                "the lake. Apart from precious fish and aquatic plants, there is "
                "not much to see. What have kept the water clear here?",
        .type=db_roomtype_plain,
        .exits={[dir_West]=41,[dir_North]=39}
    },
    {.id=41,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"Some wooden boats are moored here. They are badly decayed and "
                "overgrown with shellfish and algae.",
        .type=db_roomtype_plain,
        .exits={[dir_North]=38,[dir_East]=40}
    },
    {.id=42,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"It feels strange that there are not many pedestrians on such a "
                "wide road.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=11,[dir_East]=43}
    },
    {.id=43,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"Such a wide road might have been prepared for a huge carriage "
                "parade.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=42,[dir_East]=44}
    },
    {.id=44,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"The road came to an abrupt end.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=43,[dir_South]=26}
    },
    {.id=45,
        .region=db_roomregion_nlcity,
        .name=L"Gangsters' Corner",
        .desc=L"Gang members frequent this corner.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=46,[dir_North]=18},
        .table={3,3}
    },
    {.id=46,
        .region=db_roomregion_nlcity,
        .name=L"Gang Base",
        .desc=L"All the gang members give hostile glances.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=45},
        .table={4,3,3,3,3,3,3,3}
    },
    {.id=47,
        .region=db_roomregion_nlcity,
        .name=L"Yet Darker Path",
        .desc=L"It is still dark here. This is probably the darkest spot on the "
                "path. No one came at all, maybe the darkness scared the gangs "
                "away.",
        .type=db_roomtype_plain,
        .exits={[dir_East]=17,[dir_North]=48}
    },
    {.id=48,
        .region=db_roomregion_nlcity,
        .name=L"Darker Path",
        .desc=L"The path is too dark.",
        .type=db_roomtype_plain,
        .exits={[dir_North]=49,[dir_South]=47}
    },
    {.id=49,
        .region=db_roomregion_nlcity,
        .name=L"Dark Path",
        .desc=L"Are the streets of this city without street lights?",
        .type=db_roomtype_plain,
        .exits={[dir_South]=48,[dir_East]=6},
        .table={2}
    },
    {.id=50,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"Even large armies can easily travel on this wide road.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=51,[dir_East]=11}
    },
    {.id=51,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"The wind blew in from the west gate and blew across the road.",
        .type=db_roomtype_plain,
        .exits={[dir_West]=52,[dir_South]=7,[dir_East]=50}
    },
    {.id=52, // gate // wip
        .region=db_roomregion_nlcity,
        .name=L"City Gate",
        .desc=L"There are many more stone statues here than at the northern gate. "
                "Their armor and weapons also seem to be more refined than the "
                "stone soldiers in front of the other two gates.",
        .type=db_roomtype_gate,
        .exits={[dir_East]=51}
    },
    {
        .id=0
//              -------------------------------------------------------------------\n"
    }
};

#include "dbentity.h"

roomdb *db_rfindwithid(nat roomid);
void db_rshowdesc(nat roomid);
void db_rshowtable(nat roomid);
roomdb *db_rfindwithid(nat roomid){
    for(nat i=0;;i++){
        if(roomdbs[i].id==roomid){
            return &roomdbs[i];
            break;
        }
        if(roomdbs[i].id==0)break;
    }
    return NULL;
}
void db_rshowdesc(nat roomid){
    roomdb *rm=db_rfindwithid(roomid);
    if(rm==NULL){
        printr(Red,msg->db_ridnullexceptionerror);
        return;
    }
    printr(White|Bright,L"\n%ls\n",rm->name);
    printr(Cyan|Bright,L"%ls\n",rm->desc);
    printr(Green|Bright,L"exits: ");
    if(rm->exits[dir_North])printr(Green|Bright,L"NORTH  ");
    if(rm->exits[dir_East])printr(Green|Bright,L"EAST  ");
    if(rm->exits[dir_South])printr(Green|Bright,L"SOUTH  ");
    if(rm->exits[dir_West])printr(Green|Bright,L"WEST  ");
    struct et_room *etr=et_findroomwithid(roomid);
    if(etr==NULL){
        printr(Red,msg->db_retidnullexceptionerror);
    }
    else{
        for(nat i=0,first=1;i<DBE_ENEMYCAP;i++){
            if(etr->etenemy[i]!=0){
                enemydb *edb=et_getenemydb(etr->etenemy[i]);
                if(first){
                    printr(Red|Bright,L"\nenemies: %ls",edb->name);
                }else{
                    printr(Red|Bright,L", %ls",edb->name);
                }
                first=0;
            }
        }
        for(nat i=0,first=1;i<DBE_ITEMCAP;i++){
            if(etr->etitem[i]!=0){
                struct et_item *eti=&et_items[etr->etitem[i]-1];
                if(eti->available==false){
                    printr(Red,msg->db_ietidnullexceptionerror);
                    continue;
                }
                itemdb *idb=db_ifindwithid(eti->itemid);
                if(idb==NULL){
                    printr(Red,msg->db_iidnullexceptionerror);
                    continue;
                }
                if(first){
                    if(!(idb->type&db_itemtype_stackable_mask))printr(Yellow|Bright,L"\nitems: %ls",idb->name,etr->etitem[i]);
                    else{
                        if(eti->qnty==1)printr(Yellow|Bright,L"\nitems: %ls",idb->name);
                        else printr(Yellow|Bright,L"\nitems: %ls (x%" PRIdFAST32 ")",idb->name,eti->qnty);
                    }
                }else{
                    if(!(idb->type&db_itemtype_stackable_mask))printr(Yellow|Bright,L", %ls",idb->name,etr->etitem[i]);
                    else{
                        if(eti->qnty==1)printr(Yellow|Bright,L", %ls",idb->name);
                        else printr(Yellow|Bright,L", %ls (x%" PRIdFAST32 ")",idb->name,eti->qnty);
                    }
                }
                first=0;
            }
            if(i==DBE_ITEMCAP-1&&first==0)printf("\n");
        }
    }
    printr(Default,L"\n\n");
}
void db_rshowtable(nat roomid){
    roomdb *rm=db_rfindwithid(roomid);
    if(rm==NULL){
        printr(Red,msg->db_ridnullexceptionerror);
        return;
    }
    if(rm->type!=db_roomtype_shop){
        printr(Default,msg->db_notinstore);
        return;
    }
    printr(Default,msg->line);
    for(nat i=0;i<32;i++){
        if(rm->table[i]!=0){
            itemdb *idb=db_ifindwithid(rm->table[i]);
            if(idb==NULL){
                printr(Red,msg->db_iidnullexceptionerror);
                return;
            }
            printrp(Default,L"            | ",msg->db_listitem,idb->price,idb->name);
        }else break;
    }
    printr(Default,msg->line);
}
#endif
