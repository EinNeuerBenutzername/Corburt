#ifndef Corburt_Messages_h_Include_Guard
#define Corburt_Messages_h_Include_Guard
#include <inttypes.h>
#include <wchar.h>
// prepared for future translations. :)
const wchar_t *msg_global_welcome=L"Welcome to Corburt.\n\n";
const wchar_t *msg_global_splash=L"   @@@@                @@\n"
"  @@  @@               @@                  @@\n"
"  ##      ####  # ###  ####  ##  ## # ###  ####\n"
"  ##     ##  ## ##  ## ## ## ##  ## ##  ## ##\n";
const wchar_t *msg_global_splash2=L"  $$  $$ $$  $$ $$     $$ $$ $$  $$ $$     $$\n"
"   $$$$   $$$$  $$     $$$    $$$$  $$      $$$\n\n";
const wchar_t *msg_global_corburtversion=L"v0.0.3";
const wchar_t *msg_global_nosave=L"No save files found.\n";
const wchar_t *msg_global_scansave=L"Scanning the save file...\n";
const wchar_t *msg_global_saveempty=L"Save file is empty.\n";
const wchar_t *msg_global_savefound=L"Save found.\n";
const wchar_t *msg_global_savecount=L"%" PRIdFAST32 " save found.\n";
const wchar_t *msg_global_savecounts=L"%" PRIdFAST32 " saves found.\n";
const wchar_t *msg_global_savetoomany=L"You have created too many saves!\n";
const wchar_t *msg_global_enteryourname=L"Please enter your name.\n";
const wchar_t *msg_global_nametooshort=L"Your name may not be shorter than 2 characters.\n";
const wchar_t *msg_global_confirmyourname=L"Are you sure to name yourself as %s? [Y/N]\n";
const wchar_t *msg_global_confirmchoice=L"Are you sure to play as the character '%s'? [Y/N]\n";
const wchar_t *msg_global_welcomeplayer=L"Welcome, %ls.\n";
const wchar_t *msg_global_welcomeplayer2=L"Welcome back, %ls.\n";
const wchar_t *msg_global_help=L"-------------------------------------------------------------------\n"
    "                           Commands\n"
    "abilities                  - Show player's abilities\n"
    "cls                        - Clear screen\n"
    "experience                 - Show player's expierence\n"
    "help                       - Show this list\n"
    "inventory                  - Show player's inventory\n"
    "quit                       - Save and quit game\n"
    "stats                      - Show player's statistics\n"
    " * Some commands have abbreviated forms, e.g. 'st' for 'stats'.\n"
    "-------------------------------------------------------------------\n";

const wchar_t *msg_trace_savesize=L"Size of a save is %zu bytes.\n";
const wchar_t *msg_trace_endianess_le=L"Machine is little endian.\n";
const wchar_t *msg_trace_endianess_be=L"Machine is big endian.\n";
const wchar_t *msg_trace_rnginit=L"RNG initialization\n";
const wchar_t *msg_trace_rngseed=L"- Seed: %" PRIdFAST32 "\n";
const wchar_t *msg_trace_rngtest=L"- RNG test: %" PRIdFAST32 "\n";
const wchar_t *msg_trace_malloced=L"%" PRIdFAST32 " bytes of memory is allocated.\n";
const wchar_t *msg_trace_realloced=L"%" PRIdFAST32 " bytes of memory is reallocated.\n";
const wchar_t *msg_trace_freed=L"Pointer freed.\n";
const wchar_t *msg_trace_pointerinuse=L"Number of pointers in use: %" PRIdFAST32 "\n";

const wchar_t *msg_error_cannotmalloc=L"Fatal error: Cannot allocate memory.";
const wchar_t *msg_error_cannotrealloc=L"Fatal error: Cannot reallocate memory.";
const wchar_t *msg_error_unknown=L"Fatal error: An unknown fatal error occured.";
const wchar_t *msg_error_badcharbit=L"Fatal error: Macro CHAR_BIT is not 8.";

const wchar_t *msg_line=L"\n-------------------------------------------------------------------\n";

const wchar_t *msg_player_info=L"-------------------------------------------------------------------\n"
    "                           Your Statistics\n"
    "Name:          %ls\n"
    "Rank:          %ls\n"
    "Hit Points:    %" PRIdFAST32 "/%" PRIdFAST32 " (%.2f%%)\n"
    "Level:         %" PRIdFAST32 "\n"
    "Expierence:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n\n"
    "Attack Damage: %-08" PRIdFAST32 "            Damage Absorb: %-08" PRIdFAST32 "\n"
    "Accuracy:      %-08" PRIdFAST32 "            Dodging:       %-08" PRIdFAST32 "\n"
    "Stealth:       %-08" PRIdFAST32 "            Activity:      %-08" PRIdFAST32 "\n"
    "Constitution:  %-08" PRIdFAST32 "            Stat Points:   %-08" PRIdFAST32 "\n"
    "-------------------------------------------------------------------\n";
const wchar_t *msg_player_exp=L"Level:         %" PRIdFAST32 "\n"
    "Expierence:    %" PRIdFAST64 "/%" PRIdFAST64 " (%.2f%%)\n";
const wchar_t *msg_player_inv=L"-------------------------------------------------------------------\n"
    "                           Your Inventory\n"
    "Money:         %-08" PRIdFAST64 "\n"
    "Weapon:        %ls\n"
    "Armor:         %ls\n"
    "Capacity:      %" PRIdFAST32 "/%" PRIdFAST32 "\n"
    "Items: ";
const wchar_t *msg_player_abl=L"-------------------------------------------------------------------\n"
    "                           Your Abilities\n"
    "   coming soon\n"
    "-------------------------------------------------------------------\n";
const wchar_t *msg_player_say=L"%ls says: ";
#endif
