#ifndef Corburt_Database_AI_h_Include_Guard
#define Corburt_Database_AI_h_Include_Guard
enum db_enemyaitype {
    db_enemyaitype_fighter,
    db_enemyaitype_berserker,
    db_enemyaitype_soldier,
    db_enemyaitype_suicider,
    db_enemyaitype_weaponmaster,
    db_enemyaitype_ranger,
    db_enemyaitype_assassin,
    db_enemyaitype_coward,
    db_enemyaitype_guardian,
    db_enemyaitype_socerer,
    db_enemyaitype_apostate,
    db_enemyaitype_elemental,
    db_enemyaitype_dragon,
    db_enemyaitype_summoner
};
enum db_combo { // what am I doing??
    db_combo_break,         // 15f
    db_combo_shortbreak,    // 10f
    db_combo_shorterbreak,  // 5f
    db_combo_longbreak,     // 25f
    db_combo_longerbreak,   // 40f
    db_combo_rest,          // 75f
    db_combo_strike,        // 5f?
    db_combo_heavystrike,   // 5f?
};
#endif
