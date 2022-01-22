#ifndef Corburt_Messages_h_Include_Guard
#define Corburt_Messages_h_Include_Guard
#include <inttypes.h>
#include <wchar.h> // prepared for translations. :)
const wchar_t *msg_global_welcome=L"Welcome to Corburt.\n\n";
const wchar_t *msg_global_splash=L"   @@@@                @@\n"
"  @@  @@               @@                  @@\n"
"  ##      ####  # ###  ####  ##  ## # ###  ####\n"
"  ##     ##  ## ##  ## ## ## ##  ## ##  ## ##\n";
const wchar_t *msg_global_splash2=L"  $$  $$ $$  $$ $$     $$ $$ $$  $$ $$     $$\n"
"   $$$$   $$$$  $$     $$$    $$$$  $$      $$$\n\n";
const wchar_t *msg_global_corburtversion=L"demo v0.0.1";
const wchar_t *msg_global_nosave=L"No save files found.\n";
const wchar_t *msg_global_scansave=L"Scanning the save file...\n";
const wchar_t *msg_global_saveempty=L"Save file is empty.\n";
const wchar_t *msg_global_savefound=L"Save found.\n";
const wchar_t *msg_global_savecount=L"%" PRIuFAST32 " save found.\n";
const wchar_t *msg_global_savecounts=L"%" PRIuFAST32 " saves found.\n";
const wchar_t *msg_global_enteryourname=L"Please enter your name.\n";
const wchar_t *msg_global_nametooshort=L"Your name may not be shorter than 2 characters.\n";
const wchar_t *msg_global_confirmyourname=L"Are you sure to name yourself as %s? [Y/N]\n";
const wchar_t *msg_global_welcome_=L"Welcome, %ls.\n";

const wchar_t *msg_trace_endianess_le=L"Machine is little endian.\n";
const wchar_t *msg_trace_endianess_be=L"Machine is big endian.\n";
const wchar_t *msg_trace_rnginit=L"RNG initialization\n";
const wchar_t *msg_trace_rngseed=L"- Seed: %" PRIuFAST32 "\n";
const wchar_t *msg_trace_rngtest=L"- RNG test: %" PRIuFAST32 "\n";
const wchar_t *msg_trace_malloced=L"%" PRIuFAST32 " bytes of memory is allocated.\n";
const wchar_t *msg_trace_realloced=L"%" PRIuFAST32 " bytes of memory is reallocated.\n";
const wchar_t *msg_trace_freed=L"Pointer freed.\n";
const wchar_t *msg_trace_pointerinuse=L"Number of pointers in use: %" PRIuFAST32 "\n";

const wchar_t *msg_error_cannotmalloc=L"Fatal error: Cannot allocate memory.";
const wchar_t *msg_error_cannotrealloc=L"Fatal error: Cannot reallocate memory.";
const wchar_t *msg_error_unknown=L"Fatal error: An unknown fatal error occured.";
const wchar_t *msg_error_badcharbit=L"Fatal error: Macro CHAR_BIT is not 8.";

const wchar_t *msg_line=L"\n-------------------------------------------------------------------\n";

const wchar_t *msg_player_info=L"---------------------------- Your Stats ---------------------------\n"
"Name:          %ls\n"
"Rank:          %ls\n"
"Hit Points:    %" PRIuFAST32 "/%" PRIuFAST32 " (%.2f%%)\n"
"Level:         %" PRIuFAST32 "\n"
"Expierence:    %" PRIuFAST64 "/%" PRIuFAST64 " (%.2f%%)\n\n"
"Attack Damage: %-08" PRIuFAST32 "            Damage Absorb: %-08" PRIuFAST32 "\n"
"Accuracy:      %-08" PRIuFAST32 "            Dodging:       %-08" PRIuFAST32 "\n"
"Stealth:       %-08" PRIuFAST32 "            Activity:      %-08" PRIuFAST32 "\n"
"Constitution:  %-08" PRIuFAST32 "            Stat Points:   %-08" PRIuFAST32 "\n"
"-------------------------------------------------------------------\n";
const wchar_t *msg_player_inv=L"-------------------------- Your Inventory -------------------------\n"
"Money:         %-08" PRIuFAST64 "\n"
"Weapon:        %ls\n"
"Armor:         %ls\n"
"Capacity:      %" PRIuFAST32 "/%" PRIuFAST32 "\n"
"Items: ";
const wchar_t *msg_player_abl=L"-------------------------- Your Abilities -------------------------\n"
"%ls\n"
"-------------------------------------------------------------------\n";
const wchar_t *msg_player_say=L"%ls says: ";
#endif
