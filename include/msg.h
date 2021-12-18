#ifndef Corburt_Messages_h_Include_Guard
#define Corburt_Messages_h_Include_Guard
#include <wchar.h> // prepared for translations. :)
const wchar_t *msg_global_hint=L"It is recommended to set your console's font into mono-spaced fonts, e.g. Ubuntu Mono.\n";
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
const wchar_t *msg_global_savecount=L"%d save found.\n";
const wchar_t *msg_global_savecounts=L"%d saves found.\n";
const wchar_t *msg_global_enteryourname=L"Please enter your name.\n";
const wchar_t *msg_global_nametooshort=L"Your name may not be shorter than 2 characters.\n";
const wchar_t *msg_global_confirmyourname=L"Are you sure to name yourself as %s? [Y/N]\n";
const wchar_t *msg_global_welcome_=L"Welcome, %ls.\n";

const wchar_t *msg_trace_endianess_le=L"Machine is little endian.\n";
const wchar_t *msg_trace_endianess_be=L"Machine is big endian.\n";
const wchar_t *msg_trace_rnginit=L"RNG initialization\n";
const wchar_t *msg_trace_rngseed=L"- Seed: %lu\n";
const wchar_t *msg_trace_rngtest=L"- RNG test: %lu\n";
const wchar_t *msg_trace_malloced=L"%u bytes of memory is allocated.\n";
const wchar_t *msg_trace_realloced=L"%u bytes of memory is reallocated.\n";
const wchar_t *msg_trace_freed=L"Pointer freed.\n";
const wchar_t *msg_trace_pointerinuse=L"Number of pointers in use: %u\n";

const wchar_t *msg_error_cannotmalloc=L"Fatal error: Cannot allocate memory.";
const wchar_t *msg_error_cannotrealloc=L"Fatal error: Cannot reallocate memory.";

const wchar_t *msg_player_info=L"---------------------------- Your Stats ---------------------------\n"
"Name:          %ls\n"
"Rank:          %ls\n"
"Hit Points:    %lu/%lu (%.2f%%)\n"
"Level:         %u\n"
"Expierence:    %llu/%llu (%.2f%%)\n\n"
"Attack Damage: %-08d            Damage Absorb: %-08d\n"
"Accuracy:      %-08d            Dodging:       %-08d\n"
"Stealth:       %-08d            Activity:      %-08d\n"
"Constitution:  %-08d            Stat Points:   %-08d\n"
"-------------------------------------------------------------------\n";
const wchar_t *msg_player_inv=L"-------------------------- Your Inventory -------------------------\n"
"Items:         %ls\n"
"-------------------------------------------------------------------\n";
const wchar_t *msg_player_abl=L"-------------------------- Your Abilities -------------------------\n"
"%ls\n"
"-------------------------------------------------------------------\n";
#endif
