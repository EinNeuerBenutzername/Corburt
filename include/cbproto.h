#ifndef __CBPROTO
#define __CBPROTO

#include "cbsys.h"

// DECLARATION
// Prototypes and instances

// Prototypes do not hold pointers to objects.
// Object relationships are instead stored as IDs (of i32 type)

typedef struct ItemData ItemData;
typedef struct EntityData EntityData;
typedef struct PropData PropData;
typedef struct NPCData NPCData;
typedef struct RoomData RoomData;
typedef struct RegionData RegionData;

typedef struct AbilityData AbilityData;
typedef struct BuffData BuffData;

struct ItemData { // tbd
    i32 id;
    i32 type;
    i32 value;
    char *name;
    char *tooltip;
};

enum enum_itemtype {
    ITTYPE_MASK_STACKABLE=16,
    ITTYPE_MASK_EQUIP=32,
    ITTYPE_WEAPON=0|ITTYPE_MASK_EQUIP,
    ITTYPE_ARMOR=1|ITTYPE_MASK_EQUIP,
    ITTYPE_ACCESS=2|ITTYPE_MASK_EQUIP, // accessory
    ITTYPE_KEY,
    ITTYPE_CONSUME=0|ITTYPE_MASK_STACKABLE,
    ITTYPE_COLLECT=1|ITTYPE_MASK_STACKABLE,
    ITTYPE_AMMO=2|ITTYPE_MASK_STACKABLE
};

struct EntityData { // tbd
    i32 id;
    i32 type;
    char *name;
    char *desc;
    i32 lvl;
    i32 exp;
    struct {
        i32 hpmax;
        i32 stmax;
        i32 mpmax;
        i32 sanmax;
        i32 dpmax;
    } res; // resources
    struct {
        i32 con; // constitution
        i32 str; // strength
        i32 wis; // wisdom
        i32 wil; // willpower
        i32 agi; // agility
        i32 luc; // luck
        i32 div; // divinity
    } stats;
};

enum enum_entitytype {
    ENTYPE_MOB,
    ENTYPE_ELITE,
    ENTYPE_MIDBOSS,
    ENTYPE_BOSS,
    ENTYPE_MISC
};

struct PropData { // tbd
    i32 id;
    i32 type;
};

enum enum_proptype {
    PRTYPE_DOOR,
    PRTYPE_SWITCH,
    PRTYPE_CHEST,
    PRTYPE_TRAP,
    PRTYPE_TP,
    PRTYPE_HAZARD,
    PRTYPE_CONTAINER
};

struct NPCData { // tbd
    i32 id;
    i32 entityid; // entity data is accessed in NPCInstance -> EntityInstance -> entity
    // Create an entity with [entityid], and give its reference to NPCInstance.
};

struct RoomData {
    i32 regionid;
    struct {
        i32 x;
        i32 y;
        i32 z;
    } pos;
    char *name;
    char *desc;
    i32 type;
    i32 exits[6];
    i32 tags[16];
    i32 table[32];
};

enum enum_roomtype {
    RMTYPE_PLAIN,
    RMTYPE_BIRTH,
    RMTYPE_SHOP,
    RMTYPE_STORE=RMTYPE_SHOP,
    RMTYPE_TRAIN
};

enum enum_directions {
    DIR_EAST,
    DIR_WEST,
    DIR_NORTH,
    DIR_SOUTH,
    DIR_UP,
    DIR_DOWN
};

struct RegionData {
    i32 id;
    char *name;
    i32 threat;
};

enum enum_threat {
    THR_SECURE=1,
    THR_LOW=2,
    THR_MODERATE=4,
    THR_SUBSTANTIAL=8,
    THR_CRITICAL=16,
    THR_EXTREME=32,
    THR_OBLITERATION=64
};

// Instances

typedef struct ItemInstance ItemInstance;
typedef struct EntityInstance EntityInstance;
typedef struct PropInstance PropInstance;
typedef struct NPCInstance NPCInstance;
typedef struct RoomInstance RoomInstance;
typedef struct RegionInstance RegionInstance;

typedef struct AbilityEffect AbilityEffect;
typedef struct BuffEffect BuffEffect;

struct ItemInstance {
    i32 id;
    Node *node;
    ItemData *proto;
    LList *affixes;
};

struct EntityInstance {
    i32 id;
    Node *node;
    EntityData *proto;
    i32 aggro;
    LList *inventory;
};

struct PropInstance {
    i32 id;
    Node *node;
    PropData *proto;
};

struct NPCInstance {
    i32 id;
    Node *node;
    NPCData *proto;
    EntityInstance *entity;
};

struct RoomInstance {
    i32 id;
    i32 explored;
    Node *node;
    RoomData *proto;
    LList *items;
    LList *entities;
    LList *props;
    LList *npcs;
    i32 rmbuff[16];
};

struct RegionInstance {
    i32 id;
    Node *node;
    RegionData *proto;
    LList *rooms;
};

#endif
