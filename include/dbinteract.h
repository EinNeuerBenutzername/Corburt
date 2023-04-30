#ifndef Corburt_Database_Interact_h_Include_Guard
#define Corburt_Database_Interact_h_Include_Guard
#include "cbbase.h"
interdb *db_intfindwithid(nat interid);

interdb *db_intfindwithid(nat interid){
    if(interdbs[interid-1].id==interid)return &interdbs[interid-1];
    for(nat i=0;;i++){
        if(interdbs[i].id==interid){
            return &interdbs[i];
            break;
        }
        if(interdbs[i].id==0)break;
    }
    return NULL;
}


#endif
