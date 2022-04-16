# Corburt

[TOC]

## About

### General

Corburt is a pretty simple text-based RPG game developed based on the ideas of *SimpleMUD*. The original codebase for SimpleMUD was written in C++ by Ron Penton, the author of MUD Game Programming book.

Inspirations come from a game called [93 Realms](http://windows93.net:8083/), which my friends and I had a great time playing in 2021.

### Plans for Corburt v0.2

- **Main**

  - [x] implement turn-based game process
  - [x] implement combat
  - [x] implement death & revival
  - [x] implement health regen
  - [x] implement enemy drops
  - [x] implement death punishments
  - [ ] implement money loot
  - [ ] implement stat edits

- **Polish**

  - [ ] make balancing improvements
  - [ ] add new item & enemy data entries

- **Optional**

  - [ ] add the new region

## Features/Highlights

- **written in plain C code** (C99).
- **multi-platform support**: should work on Windows, Linux, MacOS and several other \*nixes.
- **no external dependencies** (hopefully).
- **open source**.
- **easy to compile**: only one .c file, all other files are headers. friendly for C amateurs.

## Drawbacks

- it's in a **very early stage of development**.
- might **not** be finished.
- might **not** work properly on non-Windows platforms.
  - might not even work properly on Windows platforms other than Windows 10.
  - for this reason, please report if you encounter any problem.
- **not** yet C++-compatible.
- I am lazy and might **not** be available for improvements and bug fixes.

## Requirements

- your computer should either be **non-prehistorical Windows** or **POSIX-compliant \*nix**.
  - this is largely because Corburt's curses library rely on platform-specific headers.
  - Corburt uses **no** platform-specific headers **except for** those in `cbcurses.h`. Basically, the only thing limiting Corburt's cross-platform capabilities is the curses support.
- your compiler should support **C99** with these standard C libraries:
  - `<inttypes.h>`
    - for `uint_fastX_t` types
  - `<locale.h>`
    - for Unicode support
  - `<math.h>`
    - for math calculation
  - `<stdarg.h>`
    - for I/O
  - `<stdbool.h>`
    - for the bool type
  - `<stdio.h>`
    - for I/O
  - `<stdlib.h>`
    - for memory management
  - `<time.h>`
    - for RNG
  - `<wchar.h>`
    - for Unicode support
- on your computer, a byte **must** contain exactly 8 bits.
  - it is also suggested that the size of wchar_t is exactly 16 bits. it's okay if that's not the case, though.
  - **bit-wise endianness**, **non-ASCII interchange codes** (e.g. EBCDIC), et cetera, which are less common in my opinion, are **not** allowed, too.
- it is recommended to use GCC compiler.
  - it's especially recommended to use Code::Blocks to compile. I am using Code::Blocks to develop Corburt and would upload my C::B project files along with the source.
  - I might ignore any MSVC-exclusive issues. MSVC just has too many of them.

## Acknowledgements

- for inspiration:
  - **Ron Penton**, author of *MUD Game Programming*
  - **Jankenpopp** and other developers of *93 Realms*
- for libraries:
  - **JC Wang** (@jcwangxp) for [Crossline](https://github.com/jcwangxp/Crossline)
  - **Evan Sultanik** (@ESultanik) for [MTwister](https://github.com/ESultanik/mtwister)
- for dev:
  - My friend **emf** and **Jack Q** for supporting me, giving valuable advice, contributing to Corburt and testing it.
- You, probably ;)

## Report

If you are not sure what kind of report you are sending, or if your report contains more than one of the following types at the same time, you may just simply state "**Report**".

Will your report be seen? Very probably... Anyway,

- I may not have time to review your report and your content may be ignored.
- Also, if the advice isn't given in a language I can use, or it's clearly incomplete, or I don't know how to implement it, I'll ignore it.
- Even if I like your suggestion a lot, I might not be able to implement it if it's too difficult to implement due to my very limited programming ability.
- Since I'm busy, if I can't or don't plan to implement a suggestion, I'll probably just ignore it or close it.

### Bug report

**When reporting bugs (if you came across any), please clarify:**

- what's the version of Corburt?
  - if it is not the latest version, test on the latest version.
- if you compiled Corburt yourself, what compiler are you using?
  - if you're using compilers that don't actually support C99, I might just ignore you.
  - btw, GCC doesn't actually **totally** support C99.
- what had you done before the bug occurred?
- were there any error messages?
- were any error log files generated?
- did the game crash?

### Typo report

**Please report if you find typos or grammar mistakes.**

### Balancing feedback

If you find an unbalanced design in **the latest version of Corburt** and **a) it's not a malicious joke or a trap**, and **b) it's adversely affecting gameplay**, please report it.

If you wish to add new content, see "**Suggestions**".

- **When giving a balancing feedback, please**
  - make sure you are very familiar with what you are proposing to modify.
  - make sure that what you propose to amend will not be offensive to others.
  - explain what you think is bad in the original design.
    - e.g. "The difficulty of the new area does not match with the stated threat level."
  - [optional, but suggested] explain how you think it would improve the game experience.
    - e.g. "It will ease the difficulty curve."
  - provide detailed alternatives or suggested modifications.
    - e.g. "$400 is a little too much, make it $250."
- **Examples of what you are welcome to suggest include:**
  - increase the cost of items to prevent abuse.
  - increase enemy experience drops when leveling up is unnecessarily difficult.
  - adjust bosses' difficulty to suit most players.

### Suggestions

This mainly refers to suggestions for new content. If it is an adjustment to existing content, see "**Balancing feedback**".

- What you should think carefully before suggesting include:
  - major changes to the map
  - new mechanism
  - local multiplayer mode
  - any web-related content

## Version history
###  Demo

- **0.2.2** (Apr 16, 2022)
  - **What's new**: enemy drops
  - enemy entity data saving/loading functions implemented.
  - map errors fixed with CBME.
  - enemies can respawn (currently once per 50 rounds).
  - enemies are equipped with weapons and armors.
    - these could be dropped on their deaths and they contribute to enemies' stats.
  - player's and enemies' death drops implemented.
    - on death, player loses 10% of their exp and money and one of their items.
  - enemy stats slightly revised.
  - player and enemies can now attack each other.
  - functions accessing databases are revised and are more performant now.
  - player now regenerates once per 25 rounds.
- **0.2.1** (Apr 10, 2022)
  - **What's new**: enemy attacks
  - item stats slightly revised.
  - implemented player death and revival (at specific spawn points).
  - player's arrival to a new spawn point will be recorded.
  - player's hit points slowly regenerate (once per 50 turns).
  - map remade with [Corburt Map Editor](https://github.com/EinNeuerBenutzername/Corburt-Map-Editor).
- **0.2.0** (Mar 12, 2022)
  - **What's new**: turns
  - item stats slightly revised.
  - version control improved.
  - player stats structure revised.
  - implemented the new command "time".
  - currently, moving to another room takes 1 turn (30 ticks).
- **0.1.7** (Feb 4, 2022)
  - **What's new**: sell items
  - typos fixed.
  - stability fix for commands: "buy", "take" and "drop".
  - implemented the new command "sell".
  - added a function to detect the version of the save file. 
    - forward-compatibility is not yet taken into account, because Corburt is in a very early stage of development, meaning that the structure of save files would change many times in the future.
- **0.1.6** (Jan 30, 2022)
  - **What's new**: take & drop items
  - "use" function on consumable items implemented.
  - file I/O bug fixed.
  - the take & drop commands added.
  - implemented a function to delete item entities.
  - word wrap bug fixed.
- **0.1.5** (Jan 30, 2022)
  - **What's new**: you can buy multiple items at once
    - "buy 10 potion"
  - "buy" function bugs fixed.
  - shop list display made ready for items with names that exceed the width limit.
  - typedef replacements for database data types.
  - inventory data saving & loading implemented.
  - item entity data saving & loading implemented.
- **0.1.4** (Jan 29, 2022)
  - **What's new**: visual & security improvements
  - word wrap now detects CJK full-width characters.
  - minor improvements on visual effects.
  - weapon/armor bonus are added onto your stats.
  - implemented brutal leak check for memory management. Corburt will now free all pointers at exit.
  - free() and realloc() check whether the pointer is a malloc()'ed pointer.
  - message "you can't afford it" fixed.
- **0.1.3** (Jan 29, 2022)
  - **What's new**: purchasing stackable items is now possible
  - word wrap improved.
  - map fixed.
  - stackable items can now be correctly pushed into inventory, thus now purchasable.
  - directly pressing return without any input repeats your last command.
  - items and enemies in a room are shown.
  - added several checks for null exceptions.
- **0.1.2** (Jan 28, 2022)
  - **What's new**: entities
  - stackable items are temporarily unavailable for purchase.
    - this is because the merging feature of stackable items has not yet been implemented.
  - implemented item entities and enemy entities.
  - updated the function 'match' for stability and security.
  - inventory layout remade.
  - the 'use' command added.
  - enemies are now shown in room descriptions with brutal line breaks.
- **0.1.1** (Jan 27, 2022)
  - **What's new**: shops
  - finished shop lists.
  - made item database for the goods.
  - the 'buy' command added: the first command with targets.
  - fixed the function 'match' and tested name-matching.
  - opened 'dbfio_.h' for database output. haven't yet put into use.
  - room exits' structure revised to leave space for future updates; typo-fixed.
  - enemy database opened. enemies might be added in the 0.1.2 update.
- **0.1.0** (Jan 25, 2022)
  - **What's new**: region - Nameless City
  - visual effect on windows terminal fixed (I guess).
  - added several basic commands.
  - typo & grammar fixes.
  - added the first region: Nameless City (9kb database).
  - map revised.
- **0.0.3** (Jan 23, 2022)
  - **What's new**: basic commands
  - file I/O functions' portability greatly improved.
  - basic curses library revised and finished.
  - save/load functions implemented, only player stats are saved/loaded.
  - added several basic commands.
  - basic inventory information implemented.
  - typo fixes.
  - typedef revised: Corburt would now use signed 32- and 64-bit integers to store integer values.
  - stability fixes on file I/O.
- **0.0.2** (Jan 22, 2022)
  - **What's new**: basic game structure implementation
  - added <inttypes.h> and <stdbool.h> dependencies for stability and portability.
  - basic inventory functions implemented.
  - basic curses library mostly finished.
  - added trace log levels for info and debugging: 0 is none, and 2 is force explicit logging.
  - commented several obsolete functions and fixed several functions with overflow risks.
  - platform endianness detection added, enabling file I/O functions to convert data endianness.
  - several empty databases created.
  - several bugs fixed and several new bugs introduced.
- **0.0.1** (Dec 19, 2021)
  - **What's new**: interface
  - the very beginning of Corburt!
  - basic file I/O functions implemented.
  - basic player information implemented.
  - added trace logs for info and debugging.
  - several bugs introduced.