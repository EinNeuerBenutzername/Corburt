#ifndef Corburt_Database_Item_h_Include_Guard
#define Corburt_Database_Item_h_Include_Guard
#include "cbbase.h"
void getitemname(nat id,wchar_t *itemname);
void getitemname(nat id,wchar_t *itemname){
    wchar_t *p;
    switch(id){
    case 0:
        p=L"undefined behavior";
        break;
    case 1:
        p=L"Test Sword";
        break;
    case 2:
        p=L"Test Armor";
        break;
    default:
        p=L"undefined";
        break;
    }
    wcscpy(itemname,p);
}
/*{
    "ID": 1,
    "NAME": "LIES!!!@~",
    "TYPE": "HEALING",
    "MIN": 0,
    "MAX": 0,
    "SPEED": 0,
    "PRICE": 1,
    "STRENGTH": 0,
    "HEALTH": 0,
    "AGILITY": 0,
    "MAXHITPOINTS": 0,
    "ACCURACY": 0,
    "DODGING": 0,
    "STRIKEDAMAGE": 0,
    "DAMAGEABSORB": 0,
    "HPREGEN": 0
  }*/
#endif
