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
enum db_roomreligion{
    db_roomregion_nlcity, // nameless city
    db_roomregion_forest, // forests of wrath
};
struct room{
    nat id;
    enum db_roomreligion region;
    const wchar_t *name;
    const wchar_t *desc;
    enum db_roomtype type;
    struct {
        nat north;
        nat south;
        nat east;
        nat west;
        nat up;
        nat down;
    } room_exits;
    nat table[32];
};

struct room rooms[]={
    {.id=1,
        .region=db_roomregion_nlcity,
        .name=L"Town Square of the Nameless City",
        .desc=L"You have come to the town square of a nameless city. It lies in the\n"
                "center of the city.",
        .type=db_roomtype_birth,
        .room_exits={.north=2,.west=5,.south=13,.east=19}
    },
    {.id=2,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"This ordinary street runs south and north, passing through the\n"
                "center of the city. There are few pedestrians on the street.",
        .type=db_roomtype_plain,
        .room_exits={.south=1,.west=3,.north=10,.east=23}
    },
    {.id=3,
        .region=db_roomregion_nlcity,
        .name=L"Alley",
        .desc=L"The Alley leads to the park in the city. The reason the park was\n"
                "built had disappeared along with the city's name.",
        .type=db_roomtype_plain,
        .room_exits={.west=4,.east=2}
    },
    {.id=4,
        .region=db_roomregion_nlcity,
        .name=L"Park Entrance",
        .desc=L"You stand at the entrance of the park. Stone statues of two guards\n"
                "stand on either side of the entrance.",
        .type=db_roomtype_plain,
        .room_exits={.east=3,.south=6,.north=7,.west=9}
    },
    {.id=5,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"You see old houses on both sides of the street, some are inhabited.",
        .type=db_roomtype_plain,
        .room_exits={.east=1,.west=6,.south=20}
    },
    {.id=6,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"Houses around seems to get older and older.",
        .type=db_roomtype_plain,
        .room_exits={.east=5,.north=4,.south=16,.west=49}
    },
    {.id=7,
        .region=db_roomregion_nlcity,
        .name=L"Park",
        .desc=L"The weeds are growing tall and apparently not managed well, among\n"
                "which exotic plants are sparsely visible. The roads are lined with\n"
                "wooden guardrails, apparently made of precious wood.",
        .type=db_roomtype_plain,
        .room_exits={.south=4,.west=8,.north=51}
    },
    {.id=8,
        .region=db_roomregion_nlcity,
        .name=L"Park",
        .desc=L"You see woods with transparent amber leaves, trees with leaves that\n"
                "look like pure gold, shrub with crimson vines that bleed, herbs\n"
                "with blooming fantastic flowers that flickers, et cetera.",
        .type=db_roomtype_plain,
        .room_exits={.east=7,.south=9}
    },
    {.id=9, // shop
        .region=db_roomregion_nlcity,
        .name=L"Park Shop",
        .desc=L"A shop can be seen among the lush vegetation.",
        .type=db_roomtype_shop,
        .room_exits={.north=8,.east=4},
        .table={1}
    },
    {.id=10,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"There are two stores on the sides of this part of the street, great\n"
                "for novice adventurers.",
        .type=db_roomtype_plain,
        .room_exits={.north=11,.south=2,.west=21,.east=22}
    },
    {.id=11,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"The street goes further north.",
        .type=db_roomtype_plain,
        .room_exits={.north=12,.south=10,.west=50,.east=42}
    },
    {.id=12, // gate
        .region=db_roomregion_nlcity,
        .name=L"City Entrance",
        .desc=L"You have arrived at the entrance of this small city. The city does\n"
                "not have a name, but it can also be said that its name is exactly\n"
                "\"the Nameless City\".\n"
                "No one guards this entrance. A row of stone statues of soldiers\n"
                "stand here, and they look as if they were still alive.",
        .type=db_roomtype_gate,
        .room_exits={.south=11}
    },
    {.id=13,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"There is a not-so-thick layer of dust on the floor of the street.\n"
                "The wind picks up dust when it blows.",
        .type=db_roomtype_plain,
        .room_exits={.north=1,.south=14,.west=20,.east=36}
    },
    {.id=14,
        .region=db_roomregion_nlcity,
        .name=L"Street Intersection",
        .desc=L"This is a small intersection. The road to the west seems to lead to\n"
                "a dark path.",
        .type=db_roomtype_plain,
        .room_exits={.north=13,.south=15,.west=18,.east=37}
    },
    {.id=15, // gate
        .region=db_roomregion_nlcity,
        .name=L"City Gate",
        .desc=L"You are at the southern gate of the city. A group of stone soldiers\n"
                "salute to the south.",
        .type=db_roomtype_gate,
        .room_exits={.north=14}
    },
    {.id=16,
        .region=db_roomregion_nlcity,
        .name=L"Street",
        .desc=L"It looks a little dark.",
        .type=db_roomtype_plain,
        .room_exits={.north=6,.south=17,.east=20}
    },
    {.id=17,
        .region=db_roomregion_nlcity,
        .name=L"Darker Path",
        .desc=L"This path is very dark, definitely not the safest place to go.",
        .type=db_roomtype_plain,
        .room_exits={.north=16,.east=18,.west=47}
    },
    {.id=18,
        .region=db_roomregion_nlcity,
        .name=L"Dark Path",
        .desc=L"The path is dark. The low eaves of the houses block light that\n"
                "comes in.",
        .type=db_roomtype_plain,
        .room_exits={.west=17,.east=14,.north=20,.south=45}
    },
    {.id=19,
        .region=db_roomregion_nlcity,
        .name=L"Training Grounds",
        .desc=L"An elderly swordsman stood in the room practicing his myriad arts\n"
                "techniques. He looks more like a machine or a golem than a human.",
        .type=db_roomtype_train,
        .room_exits={.west=1}
    },
    {.id=20,
        .region=db_roomregion_nlcity,
        .name=L"Residential Area",
        .desc=L"You walk through the residential area in the city. There are not\n"
                "many residents here, and two thirds of the houses are empty.",
        .type=db_roomtype_plain,
        .room_exits={.west=16,.east=13,.south=18,.north=5}
    },
    {.id=21, // shop
        .region=db_roomregion_nlcity,
        .name=L"Adventurer's Shop",
        .desc=L"A man sits at the counter. He has a large scar on his face.",
        .type=db_roomtype_shop,
        .room_exits={.east=10},
        .table={0}
    },
    {.id=22, // shop
        .region=db_roomregion_nlcity,
        .name=L"Mad Alchemist's Shop",
        .desc=L"The mad alchemist stares at you. In his hand he holds a bottle of\n"
                "potion that kept changing colors. Looks toxic.",
        .type=db_roomtype_shop,
        .room_exits={.west=10,.south=23,.east=24},
        .table={0}
    },
    {.id=23, // shop
        .region=db_roomregion_nlcity,
        .name=L"Market",
        .desc=L"Many cheap items are available in the market.",
        .type=db_roomtype_shop,
        .room_exits={.west=2,.north=22,.east=25},
        .table={0}
    },
    {.id=24,
        .region=db_roomregion_nlcity,
        .name=L"Side Street Junction",
        .desc=L"The side street ends here. You can see a path to the east.",
        .type=db_roomtype_plain,
        .room_exits={.west=22,.east=26,.south=25}
    },
    {.id=25,
        .region=db_roomregion_nlcity,
        .name=L"Side Street",
        .desc=L"The side street runs parallel to main street, which connects the\n"
                "entrance and the southern gate of the city.",
        .type=db_roomtype_plain,
        .room_exits={.north=24,.south=32,.west=23}
    },
    {.id=26,
        .region=db_roomregion_nlcity,
        .name=L"Path",
        .desc=L"To the east is the cemetery.",
        .type=db_roomtype_plain,
        .room_exits={.west=24,.north=44,.east=27}
    },
    {.id=27,
        .region=db_roomregion_nlcity,
        .name=L"Cemetary Path",
        .desc=L"You stand at the end of the narrow path that leads to the cemetary.\n"
                "The cemetery is on low ground and you can see most of the cemetery\n"
                "from this location. Yet the eastern part of the cemetery is\n"
                "shrouded in darkness.",
        .type=db_roomtype_plain,
        .room_exits={.west=26,.east=28}
    },
    {.id=28,
        .region=db_roomregion_nlcity,
        .name=L"Cemetary",
        .desc=L"There are tombstones all around. Apparently, the number of\n"
                "tombstones is far greater than the number of inhabitants of the\n"
                "town.",
        .type=db_roomtype_plain,
        .room_exits={.west=27,.east=31,.south=29}
    },
    {.id=29,
        .region=db_roomregion_nlcity,
        .name=L"Cemetary",
        .desc=L"Tombstones are crowded.",
        .type=db_roomtype_plain,
        .room_exits={.north=28,.east=30}
    },
    {.id=30,
        .region=db_roomregion_nlcity,
        .name=L"Cemetary",
        .desc=L"Do not disturb the peace of the dead.",
        .type=db_roomtype_plain,
        .room_exits={.west=29,.north=31}
    },
    {.id=31,
        .region=db_roomregion_nlcity,
        .name=L"Cemetary",
        .desc=L"Is it because the city was once too prosperous, or because it is\n"
                "too decadent now? Or is it neither, just because the history here\n"
                "is too old?",
        .type=db_roomtype_plain,
        .room_exits={.west=28,.south=30}
    },
    {.id=32,
        .region=db_roomregion_nlcity,
        .name=L"Side Street",
        .desc=L"This is another T-junction on the side street.",
        .type=db_roomtype_plain,
        .room_exits={.east=33,.south=35,.north=25}
    },
    {.id=33,
        .region=db_roomregion_nlcity,
        .name=L"Alley",
        .desc=L"It's not very clean and there is some unknown garbage on the ground.",
        .type=db_roomtype_plain,
        .room_exits={.west=32,.south=34}
    },
    {.id=34,
        .region=db_roomregion_nlcity,
        .name=L"Alley Dead End",
        .desc=L"Cascading houses prevent you from going further south.",
        .type=db_roomtype_plain,
        .room_exits={.north=33}
    },
    {.id=35,
        .region=db_roomregion_nlcity,
        .name=L"Side Street Curve",
        .desc=L"Some robbers like to crouch at the bend of the road to rob.",
        .type=db_roomtype_plain,
        .room_exits={.north=32,.west=36}
    },
    {.id=36,
        .region=db_roomregion_nlcity,
        .name=L"Side Street Curve",
        .desc=L"How is the law and order maintained here? No one is patrolling the\n"
                "streets at all.",
        .type=db_roomtype_plain,
        .room_exits={.west=13,.east=35,.south=37}
    },
    {.id=37,
        .region=db_roomregion_nlcity,
        .name=L"Side Street",
        .desc=L"Here the side street merges with the main road, leading to the gate\n"
                "to the south.",
        .type=db_roomtype_plain,
        .room_exits={.west=14,.north=36,.south=38}
    },
    {.id=38,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"It can be seen that this lake used to be a standard circle.",
        .type=db_roomtype_plain,
        .room_exits={.east=39,.north=37,.south=41}
    },
    {.id=39,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"There are many fish in the lake. Obviously,  each of them is very\n"
                "valuable.",
        .type=db_roomtype_plain,
        .room_exits={.west=38,.south=40}
    },
    {.id=40,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"The water is relatively clear and you can see the deep bottom of\n"
                "the lake. Apart from precious fish and aquatic plants, there is\n"
                "not much to see. What have kept the water clear here?",
        .type=db_roomtype_plain,
        .room_exits={.west=41,.north=39}
    },
    {.id=41,
        .region=db_roomregion_nlcity,
        .name=L"Artificial lake",
        .desc=L"Some wooden boats are moored here. They are badly decayed and\n"
                "overgrown with shellfish and algae.",
        .type=db_roomtype_plain,
        .room_exits={.north=38,.east=40}
    },
    {.id=42,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"It feels strange that there are not many pedestrians on such a\n"
                "wide road.",
        .type=db_roomtype_plain,
        .room_exits={.west=11,.east=43}
    },
    {.id=43,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"Such a wide road might have been prepared for a huge carriage\n"
                "parade.",
        .type=db_roomtype_plain,
        .room_exits={.west=42,.east=44}
    },
    {.id=44,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"The road came to an abrupt end.",
        .type=db_roomtype_plain,
        .room_exits={.west=43,.south=26}
    },
    {.id=45,
        .region=db_roomregion_nlcity,
        .name=L"Gangsters' Corner",
        .desc=L"Gang members frequent this corner.",
        .type=db_roomtype_plain,
        .room_exits={.west=46,.north=18}
    },
    {.id=46,
        .region=db_roomregion_nlcity,
        .name=L"Gang Base",
        .desc=L"All the gang members give hostile glances.",
        .type=db_roomtype_plain,
        .room_exits={.east=45}
    },
    {.id=47,
        .region=db_roomregion_nlcity,
        .name=L"Yet Darker Path",
        .desc=L"It is still dark here. This is probably the darkest spot on the\n"
                "path. No one came at all, maybe the darkness scared the gangs\n"
                "away.",
        .type=db_roomtype_plain,
        .room_exits={.east=17,.north=48}
    },
    {.id=48,
        .region=db_roomregion_nlcity,
        .name=L"Darker Path",
        .desc=L"The path is too dark.",
        .type=db_roomtype_plain,
        .room_exits={.north=49,.south=47}
    },
    {.id=49,
        .region=db_roomregion_nlcity,
        .name=L"Dark Path",
        .desc=L"Are the streets of this city without street lights?",
        .type=db_roomtype_plain,
        .room_exits={.south=48,.east=6}
    },
    {.id=50,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"Even large armies can easily travel on this wide road.",
        .type=db_roomtype_plain,
        .room_exits={.west=51,.east=11}
    },
    {.id=51,
        .region=db_roomregion_nlcity,
        .name=L"Road",
        .desc=L"The wind blew in from the west gate and blew across the road.",
        .type=db_roomtype_plain,
        .room_exits={.west=52,.south=7,.east=50}
    },
    {.id=52, // gate
        .region=db_roomregion_nlcity,
        .name=L"City Gate",
        .desc=L"There are many more stone statues here than at the northern gate.\n"
                "Their armor and weapons also seem to be more refined than the\n"
                "stone soldiers in front of the other two gates.",
        .type=db_roomtype_gate,
        .room_exits={.east=51}
    },
    {
        .id=0
//              -------------------------------------------------------------------\n"
    }
};

struct room *db_rfindwithid(nat roomid);
void db_rshowdesc(nat roomid);
void db_rshowtable(nat roomid);
struct room *db_rfindwithid(nat roomid){
    for(nat i=0;;i++){
        if(rooms[i].id==roomid){
            return &rooms[i];
            break;
        }
        if(rooms[i].id==0)break;
    }
    return NULL;
}
void db_rshowdesc(nat roomid){
    struct room *rm=db_rfindwithid(roomid);
    if(rm==NULL)return;
    printc(White|Bright,L"\n%ls\n",rm->name);
    printc(Cyan|Bright,L"%ls\n",rm->desc);
    printc(Green|Bright,L"exits: ");
    if(rm->room_exits.north)printc(Green|Bright,L"NORTH  ");
    if(rm->room_exits.east)printc(Green|Bright,L"EAST  ");
    if(rm->room_exits.south)printc(Green|Bright,L"SOUTH  ");
    if(rm->room_exits.west)printc(Green|Bright,L"WEST  ");
    printc(Default,L"\n\n");
}
void db_rshowtable(nat roomid){
    struct room *rm=db_rfindwithid(roomid);
    if(rm==NULL)return;
    if(rm->type!=db_roomtype_shop){
        printc(Default,msg_db_notinstore);
        return;
    }
    printc(Default,msg_line);
    for(nat i=0;i<32;i++){
        if(rm->table[i]!=0){
            struct itemdb *idb=db_ifindwithid(rm->table[i]);
            printc(Default,msg_db_listitem,idb->name,idb->price);
        }else break;
    }
    printc(Default,msg_line);
}
#endif
