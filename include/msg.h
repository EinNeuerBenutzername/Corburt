#ifndef Corburt_Messages_h_Include_Guard
#define Corburt_Messages_h_Include_Guard
#include <inttypes.h>
#include <wchar.h>
// prepared for future translations. :)
struct msgtag{
    const wchar_t *global_corburtversion;
    const wchar_t *global_dataloaded;
    const wchar_t *global_input;
    const wchar_t *global_waitingforinput;
    const wchar_t *global_invalidroomcount;
    const wchar_t *global_roomcountfewer;
    const wchar_t *global_welcome;
    const wchar_t *global_splash;
    const wchar_t *global_splash2;
    const wchar_t *global_nosave;
    const wchar_t *global_scansave;
    const wchar_t *global_saveempty;
    const wchar_t *global_savefound;
    const wchar_t *global_savecount;
    const wchar_t *global_savecounts;
    const wchar_t *global_savetoomany;
    const wchar_t *global_progresssaved;
    const wchar_t *global_enteryourname;
    const wchar_t *global_nametooshort;
    const wchar_t *global_confirmyourname;
    const wchar_t *global_confirmchoice;
    const wchar_t *global_welcomeplayer;
    const wchar_t *global_welcomeplayer2;
    const wchar_t *global_help;
    const wchar_t *global_save_incompat;
    const wchar_t *global_curtime;
    const wchar_t *global_curtimert;
    const wchar_t *global_roomdbsize;
    const wchar_t *global_dbsize;
    const wchar_t *global_resetenemydata;
    const wchar_t *trace_savesize;
    const wchar_t *trace_endianess_le;
    const wchar_t *trace_endianess_be;
    const wchar_t *trace_rnginit;
    const wchar_t *trace_rngseed;
    const wchar_t *trace_rngtest;
    const wchar_t *trace_malloced;
    const wchar_t *trace_realloced;
    const wchar_t *trace_freed;
    const wchar_t *trace_pointerinuse;
    const wchar_t *trace_illegalrealloc;
    const wchar_t *trace_illegalfree;
    const wchar_t *trace_freealled;
    const wchar_t *trace_loadeti;
    const wchar_t *trace_loadete;
    const wchar_t *error_cannotmalloc;
    const wchar_t *error_cannotrealloc;
    const wchar_t *error_unknown;
    const wchar_t *error_badcharbit;
    const wchar_t *error_bufferpooloverflow;
    const wchar_t *error_cannotsave;
    const wchar_t *line;
    const wchar_t *player_walkeast;
    const wchar_t *player_walkwest;
    const wchar_t *player_walksouth;
    const wchar_t *player_walknorth;
    const wchar_t *player_walkup;
    const wchar_t *player_walkdown;
    const wchar_t *player_walkno;
    const wchar_t *player_cantattack;
    const wchar_t *player_canttrain;
    const wchar_t *player_canttrain_noexp;
    const wchar_t *player_canttrain_maxlvl;
    const wchar_t *player_trainsuccess;
    const wchar_t *player_info;
    const wchar_t *player_exp;
    const wchar_t *player_points;
    const wchar_t *player_canteditstats;
    const wchar_t *player_editstatshint;
    const wchar_t *player_editstatsnopoints;
    const wchar_t *player_editstatsunknown;
    const wchar_t *player_editstatsend;
    const wchar_t *player_inv;
    const wchar_t *player_inv_none;
    const wchar_t *player_inv_wielding;
    const wchar_t *player_inv_equipping;
    const wchar_t *player_inv_wearing;
    const wchar_t *player_inv_wear;
    const wchar_t *player_inv_wield;
    const wchar_t *player_inv_equip;
    const wchar_t *player_inv_alreadyequipped;
    const wchar_t *player_abl;
    const wchar_t *player_say;
    const wchar_t *player_die;
    const wchar_t *player_die_xplost;
    const wchar_t *player_spawnupdate;
    const wchar_t *db_notinstore;
    const wchar_t *db_inosuchitem;
    const wchar_t *db_enosuchenemy;
    const wchar_t *db_ipurchaseitemhint;
    const wchar_t *db_ipurchasemultitemhint;
    const wchar_t *db_isellitemhint;
    const wchar_t *db_isellmultitemhint;
    const wchar_t *db_icantafford;
    const wchar_t *db_icantaffordmult;
    const wchar_t *db_icantcarry;
    const wchar_t *db_iettake;
    const wchar_t *db_ietmulttake;
    const wchar_t *db_ietdrop;
    const wchar_t *db_ietmultdrop;
    const wchar_t *db_ridnullexceptionerror;
    const wchar_t *db_rgidnullexceptionerror;
    const wchar_t *db_iidnullexceptionerror;
    const wchar_t *db_eidnullexceptionerror;
    const wchar_t *db_retidnullexceptionerror;
    const wchar_t *db_ietidnullexceptionerror;
    const wchar_t *db_eetidnullexceptionerror;
    const wchar_t *db_ietfull;
    const wchar_t *db_listitem;
    const wchar_t *db_eetattack1;
    const wchar_t *db_eetattack2;
    const wchar_t *db_eetattack3;
    const wchar_t *db_eetattackmiss;
    const wchar_t *db_eetattackblocked;
    const wchar_t *db_eetyouattack1;
    const wchar_t *db_eetyouattack2;
    const wchar_t *db_eetyouattack3;
    const wchar_t *db_eetyouattackmiss;
    const wchar_t *db_eetyouattackblocked;
    const wchar_t *db_eetdie;
    const wchar_t *db_eetdieexp;
    const wchar_t *db_eetenterroom;
    const wchar_t *db_retmoneydrop;
    const wchar_t *db_retitemdrop;
    const wchar_t *db_retplayermoneydrop;
    const wchar_t *db_retplayermoneypickup;
    const wchar_t *db_retnotthatmuchmoney;
    const wchar_t *db_retplayernotthatmuchmoney;
};
struct msgtag msg_en={
    .global_corburtversion=CB_VERSIONTEXT,
    .global_dataloaded=L"Game data loaded.\n",
    .global_input=L"This is the input interface for Corburt.\nType 'help' for help and 'quit' to end the game.\n",
    .global_waitingforinput=L"Waiting for cbinput...\n",
    .global_invalidroomcount=L"Fatal error:Invalid room number.\n",
    .global_roomcountfewer=L"Number of rooms in this save file is fewer than expected.\nThe save file might be outdated.\n",
    .global_welcome=L"Welcome to Corburt.\n\n",
    .global_splash=L"   @@@@                @@\n"
                    "  @@  @@               @@                  @@\n"
                    "  ##      ####  # ###  ####  ##  ## # ###  ####\n"
                    "  ##     ##  ## ##  ## ## ## ##  ## ##  ## ##\n",
    .global_splash2=L"  $$  $$ $$  $$ $$     $$ $$ $$  $$ $$     $$\n"
                    "   $$$$   $$$$  $$     $$$    $$$$  $$      $$$\n\n",
    .global_nosave=L"No save files found.\n",
    .global_scansave=L"Scanning the save file...\n",
    .global_saveempty=L"Save file is empty.\n",
    .global_savefound=L"Save found.\n",
    .global_savecount=L"%" PRIdFAST32 " save found.\n",
    .global_savecounts=L"%" PRIdFAST32 " saves found.\n",
    .global_savetoomany=L"You have created too many saves!\n",
    .global_progresssaved=L"Progress saved.\n",
    .global_enteryourname=L"Please enter your name.\n",
    .global_nametooshort=L"Your name may not be shorter than 2 characters.\n",
    .global_confirmyourname=L"Are you sure to name yourself as %s? [Y/N]\n",
    .global_confirmchoice=L"Are you sure to play as the character '%s'? [Y/N]\n",
    .global_welcomeplayer=L"Welcome, %ls.\n",
    .global_welcomeplayer2=L"Welcome back, %ls.\n",
    .global_help=L"-------------------------------------------------------------------\n"
                "                           Commands\n"
                "  <label>                  - command target\n"
                "  [label]                  - optional modifier\n"
                "Game\n"
                "  (none)                   - Repeat your last command\n"
                "  cls                      - Clear screen\n"
                "  help                     - Show this list\n"
                "  quit                     - Save and quit game\n"
                "  time                     - Show current time in-game\n"
                "  * If you directly close the game, your progress will be lost.\n"
                "  save                     - Save current progress\n"
                "Player Stats\n"
//                "  abilities                - Show player's abilities\n"
                "  editstats                - Edit player stat points\n"
                "  experience               - Show player's experience\n"
                "  inventory                - Show player's inventory\n"
                "  stats                    - Show player's statistics\n"
                "  train                    - Train at the training grounds\n"
                "Room\n"
                "  east (west, south, north)- Move towards certain directions\n"
                "  look                     - Show room information\n"
                "Items\n"
                "  buy [quantity] <item>    - Buy items\n"
                "  drop [quantity] <item>   - Drop items to the ground\n"
                "  get [quantity] <item>    - Pick up items in the room\n"
                "  list                     - Show the list of items at a store\n"
                "  sell [quantity] <item>   - Sell items at a store\n"
                "  take [quantity] <item>   - Pick up items in the room\n"
                "  use <item>               - Use an item\n"
                "Combat\n"
                "  attack <[enemy name]>    - Attack an enemy\n"
                "  * Some commands have abbreviated forms, e.g. 'st' for 'stats'.\n"
                "-------------------------------------------------------------------\n",
    .global_save_incompat=L"Incompatible save version: expected %ls.\n",
    .global_curtime=L"Current time: %" PRIdFAST64 " turns, %" PRIdFAST32 " ticks.\n",
    .global_curtimert=L"Current time: %" PRIdFAST64 " h %" PRIdFAST32 " m %" PRIdFAST32 "s, %" PRIdFAST32 " ticks.\n",
    .global_roomdbsize=L"Size of map database: %" PRIdFAST32 " KB.\n",
    .global_dbsize=L"Size of database: %.2f MB.\n",
    .global_resetenemydata=L"Resetting enemy data...\n",
    .trace_savesize=L"Size of a save is %zu bytes.\n",
    .trace_endianess_le=L"Machine is little endian.\n",
    .trace_endianess_be=L"Machine is big endian.\n",
    .trace_rnginit=L"RNG initialization\n",
    .trace_rngseed=L"- Seed: %" PRIdFAST32 "\n",
    .trace_rngtest=L"- RNG test: %" PRIdFAST32 "\n",
    .trace_malloced=L"%" PRIdFAST32 " bytes of memory is allocated.\n",
    .trace_realloced=L"%" PRIdFAST32 " bytes of memory is reallocated.\n",
    .trace_freed=L"Pointer freed.\n",
    .trace_pointerinuse=L"Number of pointers in use: %" PRIdFAST32 "\n",
    .trace_illegalrealloc=L"Error: Illegal realloc() target\n",
    .trace_illegalfree=L"Error: Illegal free() target\n",
    .trace_freealled=L"All pointers freed.\n",
    .trace_loadeti=L"%" PRIdFAST32 " item entities loaded.\n",
    .trace_loadete=L"%" PRIdFAST32 " enemy entities loaded.\n",
    .error_cannotmalloc=L"Fatal error: Cannot allocate memory.",
    .error_cannotrealloc=L"Fatal error: Cannot reallocate memory.",
    .error_unknown=L"Fatal error: An unknown fatal error occurred.",
    .error_badcharbit=L"Fatal error: Macro CHAR_BIT is not 8.",
    .error_bufferpooloverflow=L"Fatal error: Buffer pool overflow. Possible reason: memory leak.",
    .error_cannotsave=L"Fatal error: Cannot create save file.",
    .line=L"-------------------------------------------------------------------\n",
    .player_walkeast=L"You walk EAST.\n",
    .player_walkwest=L"You walk WEST.\n",
    .player_walksouth=L"You walk SOUTH.\n",
    .player_walknorth=L"You walk NORTH.\n",
    .player_walkup=L"You go UP.\n",
    .player_walkdown=L"You go DOWN.\n",
    .player_walkno=L"You walk towards an impossible direction and failed.\n",
    .player_cantattack=L"You can't attack yet.\n",
    .player_canttrain=L"This does not look like a place for training.\n",
    .player_canttrain_noexp=L"You are not experienced enough for your training.\n",
    .player_canttrain_maxlvl=L"You have reached the limit of what you can achieve with training.\n",
    .player_trainsuccess=L"You are now level %" PRIdFAST32 "\n",
    .player_info=L"-------------------------------------------------------------------\n"
                "                           Your Statistics\n"
                "Name:          %ls\n"
                "Rank:          %ls\n"
                "Hit Points:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n"
                "Level:         %" PRIdFAST32 "\n"
                "Experience:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n\n"
                "Strike Power:   %-08" PRIdFAST32 "            Damage Absorb:  %-08" PRIdFAST32 "\n"
                "Accuracy:       %-08" PRIdFAST32 "            Dodging:        %-08" PRIdFAST32 "\n"
                "Wisdom:         %-08" PRIdFAST32 "            Responsiveness: %-08" PRIdFAST32 "\n"
                "Constitution:   %-08" PRIdFAST32 "            Stat Points:    %-08" PRIdFAST32 "\n"
                "-------------------------------------------------------------------\n",
    .player_exp=L"Level:         %" PRIdFAST32 "\n"
                "Experience:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n",
    .player_points=L"-------------------------------------------------------------------\n"
                "                           Your Base Stats\n"
                "1) Strike Power:   %-08" PRIdFAST32 "      2) Damage Absorb:  %-08" PRIdFAST32 "\n"
                "3) Accuracy:       %-08" PRIdFAST32 "      4) Dodging:        %-08" PRIdFAST32 "\n"
                "5) Wisdom:         %-08" PRIdFAST32 "      6) Responsiveness: %-08" PRIdFAST32 "\n"
                "7) Constitution:   %-08" PRIdFAST32 "         Stat Points:    %-08" PRIdFAST32 "\n"
                "-------------------------------------------------------------------\n",
    .player_canteditstats=L"You can't edit your stats outside a training room.\n",
    .player_editstatshint=L"Enter a number to enhance the corresponding stat, type 'exit' to return to game.\n",
    .player_editstatsnopoints=L"You don't have available stat points.\n",
    .player_editstatsunknown=L"Unknown command.\n",
    .player_editstatsend=L"You have no more stat points available.\n",
    .player_inv=L"-------------------------------------------------------------------\n"
                "                           Your Inventory\n"
                "Money:         $%-08" PRIdFAST64 "\n"
                "Capacity:      %" PRIdFAST32 "/%" PRIdFAST32 "\n"
                "Items:         ",
    .player_inv_none=L"(none)",
    .player_inv_wielding=L"[WIELDING] ",
    .player_inv_equipping=L"[EQUIPPING] ",
    .player_inv_wearing=L"[WEARING] ",
    .player_inv_wear=L"You put on the %ls.\n",
    .player_inv_wield=L"You wield the %ls.\n",
    .player_inv_equip=L"You equip the %ls.\n",
    .player_inv_alreadyequipped=L"%ls already equipped!\n",
    .player_abl=L"-------------------------------------------------------------------\n"
    "                           Your Abilities\n"
    "-------------------------------------------------------------------\n",
    .player_say=L"%ls says: ",
    .player_die=L"You died!\n",
    .player_die_xplost=L"You lost %" PRIdFAST64 " exp.\n",
    .player_spawnupdate=L"Your spawn point has been updated to: %ls\n",
    .db_notinstore=L"You are not in a store.\n",
    .db_inosuchitem=L"There is no such item.\n",
    .db_enosuchenemy=L"There is no such enemy.\n",
    .db_ipurchaseitemhint=L"%ls purchased.\n",
    .db_ipurchasemultitemhint=L"%ls (x%" PRIdFAST32 ") purchased.\n",
    .db_isellitemhint=L"%ls sold.\n",
    .db_isellmultitemhint=L"%ls (x%" PRIdFAST32 ") sold.\n",
    .db_icantafford=L"You cannot afford the item. (missing $%" PRIdFAST32 ")\n",
    .db_icantaffordmult=L"You cannot afford the item. (missing $%" PRIdFAST32 ")\n",
    .db_icantcarry=L"You can't carry this much.\n",
    .db_iettake=L"You picked up the %ls.\n",
    .db_ietmulttake=L"You picked up the %ls (x%" PRIdFAST32 ").\n",
    .db_ietdrop=L"You dropped the %ls.\n",
    .db_ietmultdrop=L"You dropped the %ls (x%" PRIdFAST32 ").\n",
    .db_ridnullexceptionerror=L"Null exception error: invalid room id.\n",
    .db_rgidnullexceptionerror=L"Null exception error: invalid region id.\n",
    .db_iidnullexceptionerror=L"Null exception error: invalid item id.\n",
    .db_eidnullexceptionerror=L"Null exception error: invalid enemy id.\n",
    .db_retidnullexceptionerror=L"Null exception error: invalid room entity id.\n",
    .db_ietidnullexceptionerror=L"Null exception error: invalid item entity id.\n",
    .db_eetidnullexceptionerror=L"Null exception error: invalid enemy entity id.\n",
    .db_ietfull=L"%ls disappeared into the pile of objects on the ground..\n",
    .db_listitem=L"$%-10" PRIdFAST32 " | %ls\n",
    .db_eetattack1=L"%ls hit you for ",
    .db_eetattack2=L"%" PRIdFAST32,
    .db_eetattack3=L" damage!\n",
    .db_eetattackmiss=L"%ls swung at you but missed!\n",
    .db_eetattackblocked=L"%ls swung at you but is blocked!\n",
    .db_eetyouattack1=L"You hit %ls for ",
    .db_eetyouattack2=L"%" PRIdFAST32,
    .db_eetyouattack3=L" damage!\n",
    .db_eetyouattackmiss=L"You swung at %ls but missed!\n",
    .db_eetyouattackblocked=L"You swung at %ls but is blocked!\n",
    .db_eetdie=L"%ls died!\n",
    .db_eetdieexp=L"You gained %" PRIdFAST64 " exp.\n",
    .db_eetenterroom=L"%ls entered the room!\n",
    .db_retmoneydrop=L"$%" PRIdFAST32 " dropped to the ground.\n",
    .db_retitemdrop=L"%ls dropped to the ground.\n",
    .db_retplayermoneydrop=L"You dropped $%" PRIdFAST32 " to the ground.\n",
    .db_retplayermoneypickup=L"You picked up $%" PRIdFAST32 " from the ground.\n",
    .db_retnotthatmuchmoney=L"There isn't that much money!\n",
    .db_retplayernotthatmuchmoney=L"You don't have that much money!\n",
};
struct msgtag *msg=&msg_en;
#endif
