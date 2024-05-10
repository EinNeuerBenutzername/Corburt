#ifndef __CBPALETTE
#define __CBPALETTE

#include "cbcurses.h"

#define __CB_PALETTE_MAX_IND_LENGTH 7
#define __CB_PALETTE_MAXCOLORS 100

const struct {
    struct {
        const char *ind;
        int color;
        int width;
    } colors[__CB_PALETTE_MAXCOLORS];
} __CBPALETTE_data={
    {
        {"o", Default, 1}, // Original; is a meta indicator
        {"d", Default, 1}, // Default
        {"+", Green|Bright, 1}, // Success
        {"!", Red|Bright, 1}, // Fail
        {">", White|Bright, 1}, // Hint
        {":", Default|Bright, 1}, // Message (:, msg)

        {"HP", Red|Bright, 2}, // Hit points
        {"MP", Blue|Bright, 2}, // Magicka
        {"ST", Cyan|Bright, 2}, // Stamina
        {"DP", Yellow|Bright, 2}, // Divinity
        {"SAN", Magenta|Bright, 3}, // Sanity

        {"msg", Default|Bright, 3}, // Message (:, msg)
        {"key", Yellow|Bright, 3}, // Keyword
        {"spell", Blue|Bright, 5}, // Magic spell

        {"THR0", Cyan|Bright, 4}, // Secure
        {"THR1", Green|Bright, 4}, // Low threat
        {"THR2", Yellow|Bright, 4}, // Moderate threat
        {"THR3", Red|Bright, 4}, // Substantial threat
        {"THR4", Red, 4}, // Critical threat
        {"THR5", Magenta|Bright, 4}, // Extreme threat
        {"THR6", Default|Bright, 4}, // Obliteration

        {"RHint", Default|Bright, 5}, // Room hint
        {"RDesc", Default, 5}, // Room description
        {"RExit", Green|Bright, 5}, // Room exit

        {"IHint", Yellow|Bright, 5}, // Item hint
        {"IIntr", Cyan|Bright, 5}, // Item interaction

        {"NHint", Cyan|Bright, 5}, // NPC hint

        {"EHint", Red|Bright, 5}, // Enemy hint

        {"CBlogoU", White|Bright, 7}, // Corburt splash logo - upper part
        {"CBlogoL", Yellow, 7}, // Corburt splash logo lower - part
    }
};

/* TEST SUITE

    IO.printf( "{$CBlogoU}  @@@@@@             @@                       \n"
                         "    @@               @@                       \n"
                         "    ##  # ### ##  ## ####   # ###  ####   ####\n"
                         "    ##  ##    ##  ## ##  ## ##    ##  ## ##   \n"
               "{$CBlogoL}    $$  $$    $$  $$ $$  $$ $$    $$  $$ $$   \n"
                         "    $$  $$     $$$$  $$$$   $$     $$$$   $$$${$d}\n\n");

    for(i32 i=0; i<500; i++)IO.printf("{$THR6}{$d}");

    IO.printf("{$msg}- Current threat level: {$THR0}SECURE{$o} -\n{$d}");
//    IO.printf("{$msg}- Current threat level: {$THR2}MODERATE{$o} -\n{$d}");
//    IO.printf("{$msg}- Current threat level: {$THR3}SUBSTANTIAL{$o} -\n{$d}");
//    IO.printf("{$msg}- Current threat level: {$THR4}CRITICAL{$o} -\n{$d}");
//    IO.printf("{$msg}- Current threat level: {$THR5}EXTREME{$o} -\n{$d}");
//    IO.printf("{$msg}- Current threat level: {$THR6}OBLITERATION{$o} -\n{$d}");

    IO.printf("\n{$RHint}Test Room{$d}\n");
    IO.printf("{$RDesc}  You find yourself in the middle of nowhere. No exits can be seen in this confined place, and nothing can be seen except for a smiling man standing in front of you.\n  \"{$msg}My name is Lasta,{$o}\" he says, \"{$msg}greetings.{$o}\"{$d}\n");
    IO.printf("{$RExit}Exits: -{$d}\n");

    IO.printf("\n{$NHint}Lasta says:{$d} {$msg}You journey shall begin now - I will send you to {$key}The City{$o} with my spell.{$d}\n");
    IO.printf("{$NHint}Lasta says:{$d} {$spell}|:.||'|:.\":''|.:\"'.'{$d}\n\n");

    IO.printf("{$msg}- Current threat level: {$THR1}LOW{$o} -\n{$d}");

    IO.printf("\n{$RHint}Town Square{$d}\n");
    IO.printf("{$RDesc}  You are on the town square of the nameless city. This is the center of this dilapidated and forsaken place. In the middle of the square stands a broken statue, and in the front of it is a sign.\n  You can {$key}read{$o} what's on the sign.{$d}\n");
    IO.printf("{$IHint}Items: $1{$d}\n");
    IO.printf("{$EHint}Enemies: Vagrant, Wanderer{$d}\n");
    IO.printf("{$RExit}Exits: NORTH   EAST   SOUTH   WEST{$d}\n");

*/

#endif
