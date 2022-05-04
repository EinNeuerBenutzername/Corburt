#ifndef Corburt_Database_Interact_h_Include_Guard
#define Corburt_Database_Interact_h_Include_Guard
#include "cbbase.h"
enum db_intertype {
    db_intertype_door
};
typedef struct interdb {
    int id;
    int initroom;
    int intertype;
    int status;
} interdb;
#endif
