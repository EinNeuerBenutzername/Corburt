#ifndef Corburt_Messages_h_Include_Guard
#define Corburt_Messages_h_Include_Guard
#include <inttypes.h>
struct msgtag{
    const char *global_corburtversion;
    const char *global_dataloaded;
    const char *global_input;
    const char *global_waitingforinput;
    const char *global_invalidroomcount;
    const char *global_roomcountfewer;
    const char *global_welcome;
    const char *global_splash;
    const char *global_splash2;
    const char *global_nosave;
    const char *global_scansave;
    const char *global_saveempty;
    const char *global_savefound;
    const char *global_savecount;
    const char *global_savecounts;
    const char *global_savetoomany;
    const char *global_progresssaved;
    const char *global_enteryourname;
    const char *global_nametooshort;
    const char *global_confirmyourname;
    const char *global_confirmchoice;
    const char *global_welcomeplayer;
    const char *global_welcomeplayer2;
    const char *global_help;
    const char *global_save_incompat;
    const char *global_curtime;
    const char *global_curtimert;
    const char *global_roomdbsize;
    const char *global_dbsize;
    const char *global_resetenemydata;
    const char *global_clock;
    const char *global_lag;
    const char *trace_savesize;
    const char *trace_endianess_le;
    const char *trace_endianess_be;
    const char *trace_rnginit;
    const char *trace_rngseed;
    const char *trace_rngtest;
    const char *trace_malloced;
    const char *trace_realloced;
    const char *trace_freed;
    const char *trace_pointerinuse;
    const char *trace_illegalrealloc;
    const char *trace_illegalfree;
    const char *trace_freealled;
    const char *trace_loadeti;
    const char *trace_loadete;
    const char *error_cannotmalloc;
    const char *error_cannotrealloc;
    const char *error_unknown;
    const char *error_badcharbit;
    const char *error_bufferpooloverflow;
    const char *error_cannotsave;
    const char *line;
    const char *player_walkeast;
    const char *player_walkwest;
    const char *player_walksouth;
    const char *player_walknorth;
    const char *player_walkup;
    const char *player_walkdown;
    const char *player_walkno;
    const char *player_cantattack;
    const char *player_canttrain;
    const char *player_canttrain_noexp;
    const char *player_canttrain_maxlvl;
    const char *player_trainsuccess;
    const char *player_res_hp;
    const char *player_res_fp;
    const char *player_res_st;
    const char *player_res_mp;
    const char *player_res_pp;
    const char *player_stats_1;
    const char *player_stats_2;
    const char *player_info;
    const char *player_char;
    const char *player_exp;
    const char *player_points;
    const char *player_canteditstats;
    const char *player_editstatshint;
    const char *player_editstatsnopoints;
    const char *player_editstatsunknown;
    const char *player_editstatsend;
    const char *player_inv;
    const char *player_inv_none;
    const char *player_inv_wielding;
    const char *player_inv_equipping;
    const char *player_inv_wearing;
    const char *player_inv_wear;
    const char *player_inv_wield;
    const char *player_inv_equip;
    const char *player_inv_alreadyequipped;
    const char *player_abl;
    const char *player_say;
    const char *player_die;
    const char *player_die_xplost;
    const char *player_spawnupdate;
    const char *player_isready;
    const char *player_isalready;
    const char *player_switchregionprompt;
    const char *player_switchregionpromptno;
    const char *db_notinstore;
    const char *db_inosuchitem;
    const char *db_enosuchenemy;
    const char *db_ipurchaseitemhint;
    const char *db_ipurchasemultitemhint;
    const char *db_isellitemhint;
    const char *db_isellmultitemhint;
    const char *db_icantafford;
    const char *db_icantaffordmult;
    const char *db_icantcarry;
    const char *db_iettake;
    const char *db_ietmulttake;
    const char *db_ietdrop;
    const char *db_ietmultdrop;
    const char *db_ridnullexceptionerror;
    const char *db_rgidnullexceptionerror;
    const char *db_iidnullexceptionerror;
    const char *db_eidnullexceptionerror;
    const char *db_retidnullexceptionerror;
    const char *db_ietidnullexceptionerror;
    const char *db_eetidnullexceptionerror;
    const char *db_ietfull;
    const char *db_listitem;
    const char *db_eetattack1;
    const char *db_eetattack2;
    const char *db_eetattack3;
    const char *db_eetattackmiss;
    const char *db_eetattackblocked;
    const char *db_eetyouattack1;
    const char *db_eetyouattack2;
    const char *db_eetyouattack3;
    const char *db_eetyouattackmiss;
    const char *db_eetyouattackblocked;
    const char *db_eetdie;
    const char *db_eetdieexp;
    const char *db_eetenterroom;
    const char *db_retmoneydrop;
    const char *db_retitemdrop;
    const char *db_retplayermoneydrop;
    const char *db_retplayermoneypickup;
    const char *db_retnotthatmuchmoney;
    const char *db_retplayernotthatmuchmoney;
};
struct msgtag msg_en={
    .global_corburtversion=CB_VERSIONTEXT,
    .global_dataloaded="Game data loaded.\n",
    .global_input="This is the input interface for Corburt.\nType 'help' for help and 'quit' to end the game.\n",
    .global_waitingforinput="Waiting for cbinput...\n",
    .global_invalidroomcount="Fatal error:Invalid room number.\n",
    .global_roomcountfewer="Number of rooms in this save file is fewer than expected.\nThe save file might be outdated.\n",
    .global_welcome="Welcome to Corburt.\n\n",
    .global_splash= "   @@@@                @@                      \n"
                    "  @@  @@               @@                  @@  \n"
                    "  ##      ####  # ###  ####  ##  ## # ###  ####\n"
                    "  ##     ##  ## ##  ## ## ## ##  ## ##  ## ##  \n",
    .global_splash2="  $$  $$ $$  $$ $$     $$ $$ $$  $$ $$     $$  \n"
                    "   $$$$   $$$$  $$     $$$    $$$$  $$      $$$\n\n",
    .global_nosave="No save files found.\n",
    .global_scansave="Scanning the save file...\n",
    .global_saveempty="Save file is empty.\n",
    .global_savefound="Save found.\n",
    .global_savecount="%" PRIdFAST32 " save found.\n",
    .global_savecounts="%" PRIdFAST32 " saves found.\n",
    .global_savetoomany="You have created too many saves!\n",
    .global_progresssaved="Progress saved.\n",
    .global_enteryourname="Please enter your name.\n",
    .global_nametooshort="Your name may not be shorter than 2 characters.\n",
    .global_confirmyourname="Are you sure to name yourself as %s? [Y/N]\n",
    .global_confirmchoice="Are you sure to play as the character '%s'? [Y/N]\n",
    .global_welcomeplayer="Welcome, %s.\n",
    .global_welcomeplayer2="Welcome back, %s.\n",
    .global_help="---------------------------------------------------------------\n"
                "                           Commands\n"
                "  $c<label>$o                  - command target\n"
                "  $c[label]$o                  - optional modifier\n"
                "Game\n"
                "  $c(none)$o                   - Repeat your last command\n"
                "  $ccls$o                      - Clear screen\n"
                "  $chelp$o                     - Show this list\n"
                "  $cquit$o                     - Save and quit game\n"
                "  $ctime$o                     - Show current time in-game\n"
                "  $csave$o                     - Save current progress\n"
                "Player Stats\n"
                "  $cabilities$o                - Show player's abilities\n"
                "  $ccharacter$o                - Show player's character info\n"
                "  $ceditstats$o                - Edit player stat points\n"
                "  $cexperience$o               - Show player's experience\n"
                "  $cinventory$o                - Show player's inventory\n"
                "  $cinfo$o                     - Show player's character info\n"
                "  $cstats$o                    - Show player's base stats\n"
                "  $ctrain$o                    - Train at the training grounds\n"
                "Room\n"
                "  $ceast$o ($cwest$o, $csouth$o, $cnorth$o)- Move towards certain directions\n"
                "  $clook$o                     - Show room information\n"
                "Items\n"
                "  $cbuy [quantity] <item>$o    - Buy items\n"
                "  $cdrop [quantity] <item>$o   - Drop items to the ground\n"
                "  $cget [quantity] <item>$o    - Pick up items in the room\n"
                "  $clist$o                     - Show the list of items at a store\n"
                "  $csell [quantity] <item>$o   - Sell items at a store\n"
                "  $ctake [quantity] <item>$o   - Pick up items in the room\n"
                "  $cuse <item>$o               - Use an item\n"
                "Combat\n"
                "  $cattack$o $c<[enemy name]>$o    - Attack an enemy\n"
                "  * Some commands have abbreviated forms, e.g. $cst$o for $cstats$o.\n"
                "---------------------------------------------------------------\n",
    .global_save_incompat="Incompatible save version: expected %s.\n",
    .global_curtime="Current time: %" PRIdFAST64 " turns, %" PRIdFAST32 " ticks.\n",
    .global_curtimert="Current time: %" PRIdFAST64 " h %" PRIdFAST32 " m %" PRIdFAST32 "s, %" PRIdFAST32 " ticks.\n",
    .global_roomdbsize="Size of map database: %" PRIdFAST32 " KB.\n",
    .global_dbsize="Size of database: %.2f MB.\n",
    .global_resetenemydata="Resetting enemy data...\n",
    .global_clock="You feel as if the clock hand of the world had advanced by one block.\n",
    .global_lag="Game FPS is unstable, please do not run Corburt with programs of high disk usage.\n",
    .trace_savesize="Size of a save is %zu bytes.\n",
    .trace_endianess_le="Machine is little endian.\n",
    .trace_endianess_be="Machine is big endian.\n",
    .trace_rnginit="RNG initialization\n",
    .trace_rngseed="- Seed: %" PRIdFAST32 "\n",
    .trace_rngtest="- RNG test: %" PRIdFAST32 "\n",
    .trace_malloced="%" PRIdFAST32 " bytes of memory is allocated.\n",
    .trace_realloced="%" PRIdFAST32 " bytes of memory is reallocated.\n",
    .trace_freed="Pointer freed.\n",
    .trace_pointerinuse="Number of pointers in use: %" PRIdFAST32 "\n",
    .trace_illegalrealloc="Error: Illegal realloc() target\n",
    .trace_illegalfree="Error: Illegal free() target\n",
    .trace_freealled="All pointers freed.\n",
    .trace_loadeti="%" PRIdFAST32 " item entities loaded.\n",
    .trace_loadete="%" PRIdFAST32 " enemy entities loaded.\n",
    .error_cannotmalloc="Fatal error: Cannot allocate memory.",
    .error_cannotrealloc="Fatal error: Cannot reallocate memory.",
    .error_unknown="Fatal error: An unknown fatal error occurred.",
    .error_badcharbit="Fatal error: Macro CHAR_BIT is not 8.",
    .error_bufferpooloverflow="Fatal error: Buffer pool overflow. Possible reason: memory leak.",
    .error_cannotsave="Fatal error: Cannot create save file.",
    .line="---------------------------------------------------------------\n",
    .player_walkeast="You walk EAST.\n",
    .player_walkwest="You walk WEST.\n",
    .player_walksouth="You walk SOUTH.\n",
    .player_walknorth="You walk NORTH.\n",
    .player_walkup="You go UP.\n",
    .player_walkdown="You go DOWN.\n",
    .player_walkno="You walk towards an impossible direction and failed.\n",
    .player_cantattack="You can't attack yet.\n",
    .player_canttrain="This does not look like a place for training.\n",
    .player_canttrain_noexp="You are not experienced enough for your training.\n",
    .player_canttrain_maxlvl="You have reached the limit of what you can achieve with training.\n",
    .player_trainsuccess="You are now level %" PRIdFAST32 "\n",
    .player_res_hp="$PhHit Points$o:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n",
    .player_res_fp="$PfFocus$o:         %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n",
    .player_res_st="$PsStamina$o:       %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n",
    .player_res_mp="$PmMagicka$o:       %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n",
    .player_res_pp="$PsSanity$o:        %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n",
    .player_stats_1="$@sStat Points$o:    %-08" PRIdFAST32 "\n"
                    "Primary Stats\n"
                    "  $@sAgility$o:        %-08" PRIdFAST32 "        $@sConstitution$o:  %-08" PRIdFAST32 "\n"
                    "  $@sResponsiveness$o: %-08" PRIdFAST32 "        $@sStrength$o:      %-08" PRIdFAST32 "\n"
                    "  $@sWillpower$o:      %-08" PRIdFAST32 "        $@sWisdom$o:        %-08" PRIdFAST32 "\n",
    .player_stats_2="Secondary Stats\n"
                    "  $@sAccuracy$o:       %-08" PRIdFAST32 "        $@sDodging$o:       %-08" PRIdFAST32 "\n"
                    "  $@sDefense$o:        %-08" PRIdFAST32 "        $@sVitality$o:      %-08" PRIdFAST32 "\n"
                    "  $@sReflection$o:     %-08" PRIdFAST32 "        $@sFocusing$o:      %-08" PRIdFAST32 "\n"
                    "  $@sStamina$o:        %-08" PRIdFAST32 "        $@sAttack Damage$o: %-08" PRIdFAST32 "\n"
                    "  $@sSanity$o:         %-08" PRIdFAST32 "        $@sMental Damage$o: %-08" PRIdFAST32 "\n"
                    "  $@sMagicka$o:        %-08" PRIdFAST32 "        $@sMagic Damage$o:  %-08" PRIdFAST32 "\n",

    .player_info="-------------------------------------------------------------------\n"
                "                          Your Statistics\n"
                "Name:          %s\n"
                "Rank:          %s\n"
                "Level:         %" PRIdFAST32 "\n"
                "Experience:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n\n"
                "---------------------------------------------------------------\n",
    .player_char="---------------------------------------------------------------\n"
                "                           Your Statistics\n"
                "Name:          %s\n"
                "Rank:          %s\n"
                "Level:         %" PRIdFAST32 "\n"
                "Experience:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n\n"
                "---------------------------------------------------------------\n",
    .player_exp="Level:         %" PRIdFAST32 "\n"
                "Experience:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n",
    .player_points="---------------------------------------------------------------\n"
                "                           Your Base Stats\n"
                "1) Agility:        %-08" PRIdFAST32 "      2) Constitution:   %-08" PRIdFAST32 "\n"
                "3) Responsiveness: %-08" PRIdFAST32 "      4) Strength:       %-08" PRIdFAST32 "\n"
                "5) Willpower:      %-08" PRIdFAST32 "      6) Wisdom:         %-08" PRIdFAST32 "\n"
                "Stat Points:       %-08" PRIdFAST32 "\n"
                "---------------------------------------------------------------\n",
    .player_canteditstats="You can't edit your stats outside a training room.\n",
    .player_editstatshint="Enter a number to enhance the corresponding stat, type 'exit' to return to game.\n",
    .player_editstatsnopoints="You don't have available stat points.\n",
    .player_editstatsunknown="Unknown command.\n",
    .player_editstatsend="You have no more stat points available.\n",
    .player_inv="---------------------------------------------------------------\n"
                "                           Your Inventory\n"
                "Money:         $%-08" PRIdFAST64 "\n"
                "Capacity:      %" PRIdFAST32 "/%" PRIdFAST32 "\n"
                "Items:         ",
    .player_inv_none="(none)",
    .player_inv_wielding="[WIELDING] ",
    .player_inv_equipping="[EQUIPPING] ",
    .player_inv_wearing="[WEARING] ",
    .player_inv_wear="You put on the %s.\n",
    .player_inv_wield="You wield the %s.\n",
    .player_inv_equip="You equip the %s.\n",
    .player_inv_alreadyequipped="%s already equipped!\n",
    .player_abl="---------------------------------------------------------------\n"
    "                           Your Abilities\n"
    "---------------------------------------------------------------\n",
    .player_say="%s says: ",
    .player_die="You died!\n",
    .player_die_xplost="You lost %" PRIdFAST64 " exp.\n",
    .player_spawnupdate="Your spawn point has been updated to: %s\n",
    .player_isready="You are ready for your attack.\n",
    .player_isalready="You have already prepared for your attack.\n",
    .player_switchregionprompt="You are entering a different region. Are you sure to proceed? (Y/N)\n",
    .player_switchregionpromptno="Region switch canceled.\n",
    .db_notinstore="You are not in a store.\n",
    .db_inosuchitem="There is no such item.\n",
    .db_enosuchenemy="There is no such enemy.\n",
    .db_ipurchaseitemhint="%s purchased.\n",
    .db_ipurchasemultitemhint="%s (x%" PRIdFAST32 ") purchased.\n",
    .db_isellitemhint="%s sold.\n",
    .db_isellmultitemhint="%s (x%" PRIdFAST32 ") sold.\n",
    .db_icantafford="You cannot afford the item. (missing $%" PRIdFAST32 ")\n",
    .db_icantaffordmult="You cannot afford the item. (missing $%" PRIdFAST32 ")\n",
    .db_icantcarry="You can't carry this much.\n",
    .db_iettake="You picked up the %s.\n",
    .db_ietmulttake="You picked up the %s (x%" PRIdFAST32 ").\n",
    .db_ietdrop="You dropped the %s.\n",
    .db_ietmultdrop="You dropped the %s (x%" PRIdFAST32 ").\n",
    .db_ridnullexceptionerror="Null exception error: invalid room id.\n",
    .db_rgidnullexceptionerror="Null exception error: invalid region id.\n",
    .db_iidnullexceptionerror="Null exception error: invalid item id.\n",
    .db_eidnullexceptionerror="Null exception error: invalid enemy id.\n",
    .db_retidnullexceptionerror="Null exception error: invalid room entity id.\n",
    .db_ietidnullexceptionerror="Null exception error: invalid item entity id.\n",
    .db_eetidnullexceptionerror="Null exception error: invalid enemy entity id.\n",
    .db_ietfull="%s disappeared into the pile of objects on the ground..\n",
    .db_listitem="$%-10" PRIdFAST32 " | %s\n",
    .db_eetattack1="%s hit you for ",
    .db_eetattack2="%" PRIdFAST32,
    .db_eetattack3=" damage!\n",
    .db_eetattackmiss="%s swung at you but missed!\n",
    .db_eetattackblocked="%s swung at you but is blocked!\n",
    .db_eetyouattack1="You hit %s for ",
    .db_eetyouattack2="%" PRIdFAST32,
    .db_eetyouattack3=" damage!\n",
    .db_eetyouattackmiss="You swung at %s but missed!\n",
    .db_eetyouattackblocked="You swung at %s but is blocked!\n",
    .db_eetdie="%s died!\n",
    .db_eetdieexp="You gained %" PRIdFAST64 " exp.\n",
    .db_eetenterroom="%s entered the room!\n",
    .db_retmoneydrop="$%" PRIdFAST32 " dropped to the ground.\n",
    .db_retitemdrop="%s dropped to the ground.\n",
    .db_retplayermoneydrop="You dropped $%" PRIdFAST32 " to the ground.\n",
    .db_retplayermoneypickup="You picked up $%" PRIdFAST32 " from the ground.\n",
    .db_retnotthatmuchmoney="There isn't that much money!\n",
    .db_retplayernotthatmuchmoney="You don't have that much money!\n",
};
struct msgtag *msg=&msg_en;
#endif
