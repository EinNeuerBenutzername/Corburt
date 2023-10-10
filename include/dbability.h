#ifndef Corburt_Database_Ability_h_Include_Guard
#define Corburt_Database_Ability_h_Include_Guard
#include "cbbase.h"
#include "cbplayer.h"
enum db_abifx { // effects
    db_abifx_change_cd,
    db_abifx_change_critrate,
    db_abifx_change_basedmg,
    db_abifx_change_hp,
    db_abifx_change_regen,
    db_abifx_change_debuff,
    db_abifx_change_invincibility,
    db_abifx_change_invisibility,
    db_abifx_change_unknowability,
    db_abifx_change_expdrop,
    db_abifx_change_itemdroprate,
    db_abifx_change_inventorycapacity,
    db_abifx_change_abilityslots,
    db_abifx_change_exploss,
    db_abifx_change_moneyloss,
    db_abifx_revive,
    db_abifx_spreaddebuff,
    db_abifx_instakill,
    db_abifx_damagetarget
};
enum db_abiac { // activation condition
    db_abiac_always,
    db_abiac_death,
    db_abiac_strike,
    db_abiac_initstrike,
    db_abiac_ishit,
    db_abiac_roomisempty,
    db_abiac_targethasdebuff,
    db_abiac_inactive,
    db_abiac_enemydeath,
    db_abiac_enterroom,
};
enum db_abitag {
    db_abitag_breakondeath=1
};
struct abilitydb {
    int ac;
    int ac_2;
    int fx;
    int fx_arg;
    int tag;
    int status;
};
#endif
