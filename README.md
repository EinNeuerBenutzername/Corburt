# Corburt

**IMPORTANT**

* **For academic reasons, Corburt's update has been suspended. Development will resume in June this year. According to the plan, I will probably release Corburt Lite in August.**

## About

### General

Corburt is a pretty simple text-based RPG game developed based on the ideas of *SimpleMUD*. The original codebase for SimpleMUD was written in C++ by Ron Penton, the author of MUD Game Programming book.

Inspirations come from a game called [93 Realms](https://windows93.net:8083/), which my friends and I had a great time playing.

### Dev Roadmap

**Important notes**: Corburt will undergo a huge overhaul in these versions, so a lot of the original content will be removed. Currently, there are no enemies or items in game, but please do not worry. They will be added back when their update is complete.

Items marked by "🔸" are implemented but untested.

**DEV ROADMAP TO CORBURT LITE**

Corburt Lite includes 3 or 4 major regions with 2 questlines. Corburt is not quest-driven, so there is no "main quest" in Corburt Lite. It should introduce most of the mechanisms planned in the official release, but the amount of data will be about *one-tenth (a very unreliable estimation)* of it.

- **Code & data**
  - [x] ***REMOVE WCHAR DEPENDENCY!!!***
    - *(Should've used UTF-8 at the first place)*
  - [x] Remove game database from source code to make hot updates easier.
  - [ ] Remake Nameless City:
    - [x] Map revision
    - [ ] Instances revision
    - [ ] *Secret Areas*
  - [ ] Enemy database reworks.
  - [ ] Item database reworks.
  - [ ] Implement interactable database.
  - [ ] Add regions:
    - [ ] Forests of Wrath
    - [ ] Southwest Coast
    - [ ] **[SPOILER ALERT]**
    - [ ] **[VERY HEAVY SPOILER ALERT]**

- **Mechanisms**
  - [ ] Implement bosses.
  - [ ] **Reimplement stats!!!**
  - [ ] Implement new battle mechanisms:
    - [x] 🔸Ready
    - [ ] Breach stun
    - [ ] Break / Counter
    - [ ] Dodge
    - [ ] Parry
    - [ ] Sight
    - [ ] Abilities
      - [ ] Talents
      - [ ] Skills
      - [ ] Spells
    - [ ] *Enemy AI*
    - [ ] *Combos*
  - [ ] Rework formulas:
    - [x] EXP formula
    - [ ] Stat formula
    - [ ] Skill / Spell scaling formula
  - [ ] Implement events.
  - [ ] Implement interactables:
    - [ ] NPCs
    - [ ] Doors
    - [ ] Mobility
    - [ ] Containers
    - [ ] Hazards
    - [ ] Mechanisms
    - [ ] Switches
  - [ ] Implement miscellaneous items:
    - [ ] Rank
    - [ ] Debuffs
    - [ ] Blessings & Curses
    - [ ] Standard boosts
    - [ ] Item affixes and power sources
    - [ ] *Gameplay modifiers?*
- [ ] **Might or might not**
  - [ ] *Implement achievements.*


## Features/Highlights

- **Written in plain C code** (C99).
- **Multi-platform support**: expected to work properly on Windows, Linux, MacOS and several other \*nixes.
- **No external dependencies** (hopefully).
- **Open source**.
- **Easy to compile**: only two .c files, all other files are headers. friendly for C amateurs.

## Please might that Corburt...

- is in an **early stage of development**.
- might **not** be finished.
- might **not** work properly on non-Windows platforms.
  - Might not even work properly on Windows platforms other than Windows 10.
  - For this reason, please report if you encounter any problem.
- **not** C++-compatible.
  - Actually, C++ compatibility is never taken into consideration.
- **won't** receive updates frequently enough to implement all improvements and bug fixes. 

## Requirements

### Compiling

- Your computer should either be **non-prehistorical Windows** or **POSIX-compliant \*nix**.
  - This is largely because Corburt's curses library rely on platform-specific headers.
- On your computer, a byte **must** contain exactly 8 bits.
  - **Bit-wise endianness**, **non-ASCII interchange codes** (e.g. EBCDIC), et cetera, are **not** allowed.
- It is recommended to use GCC compiler.
  - It's especially recommended to use Code::Blocks to compile. I am using Code::Blocks to develop Corburt and would upload my C::B project files along with the source.
  - I might ignore any MSVC-exclusive issues. MSVC just has too many of them.

### Performance

- **System Resources**
  - Naturally, Corburt is a lightweight and lightspeed game. On a regular modern PC, Corburt's memory and CPU power usage should be negligible and lags should not present unless disk I/O is blocked by other programs.
    - \*Please note that Corburt is a game that heavily relies on disk I/O. Running Corburt while you are compressing or decompressing files, for example, is not recommended because it is likely to ruin your game experience.
- **Graphics**
  - Corburt is designed to run in PC's console terminals with 68 or more columns. Word wrapping is handled by Corburt, but fixed-width-character output (which should be the case on most terminals) is necessary, otherwise the game would look "broken".
  - The character limit for the word wrap could be changed in the code. It is not recommended to set it into a number that is too big because it makes it harder for gamers to rapidly glance down lines.

## How to
### Compile and Launch Corburt
- Please compile `cbinput.c` and `corburt.c` separately into 2 binary/executable files.
  - `cb.dat`,  `cbinput` and `corburt` should all be under the same directory. 
- Then launch the two programs simultaneously.
- Send your input at `cbinput` and the main Corburt program should be able to receive and process it.
- Please do not run two or more instances of `corburt`  simultaneously. That might cause unwanted consequences, i.e. destroy your save file.
- If you encounter problems, please report.

### Port Corburt to Other Platforms
- It shouldn't be hard for Corburt to be ported to other platforms as long as they support C99. Currently, there are only two files that rely on OS-specific headers. One is `cbcurses.h` and the other is `cbsys.h`.
  - However, Corburt opens and reads/writes one single file with two programs simultaneously. This might not work on certain systems.
- Generally, Corburt is expected to work on Windows, Linux, Mac and many other \*nixes. If that's not the case, please report.

## Acknowledgements

- For inspiration:
  - **Ron Penton**, author of *MUD Game Programming*
  - **Jankenpopp** and other developers of *93 Realms*
- For libraries:
  - **JC Wang** (@jcwangxp) for [Crossline](https://github.com/jcwangxp/Crossline)
  - **Evan Sultanik** (@ESultanik) for [MTwister](https://github.com/ESultanik/mtwister)
- For dev:
  - My friend **emf** and **Jack Q** for supporting me, giving valuable advice, contributing to Corburt and testing it.
- You, probably ;)

## Report

If you are not sure what kind of report you are sending, or if your report contains more than one of the following types at the same time, you may just simply state "**Report**".

Will your report be seen? Very probably...

- I may not have time to review your report and your content may be ignored.
- Also, if the advice isn't given in a language I can use, or it's clearly incomplete, or I don't know how to implement it, I'll ignore it.
- Even if I like your suggestion a lot, I might not be able to implement it if it's too difficult to implement due to my very limited programming ability.
- Since I'm busy, if I can't or don't plan to implement a suggestion, I'll probably just ignore it or close it.

### Bug Report

**When reporting bugs (if you came across any), please clarify:**

- What's the version of Corburt?
  - If it is not the latest version, test on the latest version.
- If you compiled Corburt yourself, what compiler are you using?
  - If you're using compilers that don't support C99, I might just ignore you.
  - Btw, GCC doesn't actually **totally** support C99.
- What had you done before the bug occurred?
  - You can copy & paste your input history from the `cbinput` window.
- Were there any error messages?
- Were any error log files generated?
- Did the game crash?

### Typo Report

**Please report if you find typos or grammar mistakes** in game or in this document.

### Balancing Feedback

If you find an unbalanced design in **the latest version of Corburt** and **a) it's not a joke or a trap**, and **b) it's adversely affecting gameplay**, please report it.

If you wish to add new content, see "**Suggestions**".

- **When giving a balancing feedback, please**
  - make sure you are very familiar with what you are proposing to modify.
  - make sure that what you propose to amend will not be offensive to others.
  - explain what you think is bad in the original design.
    - e.g. *"The difficulty of the new area does not match with the stated threat level."*
  - [optional, but suggested] explain how you think it would improve the game experience.
    - e.g. *"It will ease the difficulty curve."*
  - provide detailed alternatives or suggested modifications.
    - e.g. *"$400 is a little too much, make it $250."*
- **Examples of what you are welcome to suggest include:**
  - increase the cost of items to prevent abuse.
  - increase enemy experience drops when leveling up is unnecessarily difficult.
  - adjust bosses' difficulty to suit most players.

### Suggestions

This mainly refers to suggestions for new content. If it is an adjustment to existing content, see "**Balancing feedback**".

- What you should think carefully before suggesting include:
  - Major changes to the map
  - New mechanisms
  - Any web- or multiplayer-related content

## Version History
###  Lite Dev
- **0.3.2** (April 30, 2023)
  - **What's new**: **`<wchar.h>` dependency removed**
  - Also removed `<wchar.h>` dependency from `input.c`.
  - Changed player's stat types to prepare for future updates. All related functions are updated as well.
  - Split the command `stats` into two.
  - Changed the level-capping mechanism. The level cap for Corburt Lite should still be 20, though.
  - Made preparations for the Pulse mechanism.
- **0.3.1** (Jul 9, 2022)
  - **Important notes**: Corburt will undergo a huge overhaul in these versions, so a lot of the original content will be removed. Currently, there are no enemies or items in game, but please do not worry. They will be added back when their update is complete.
  - **What's new**: **new map**
  - Made balancing improvements.
  - The new critical damage calculation formula implemented.
  - Fixed the bug that player's health regen value increases on each regen.
  - The whole map of the Nameless City completely remade.
- **0.3.0** (May 3, 2022)
  - **What's new**: **forest** (removed in v0.3.1)
  - Fixed the bug that enemies' hit points overflow.
  - Database is now generated as a file.
  - Fixed the bug that Corburt runs a busy loop when waiting for input.
  - Minor improvements on `cbinput`.
  - Fixed the bug that the last character of loaded strings aren't initialized and might therefore produce corrupt strings.
  - Console output is now fully buffered for faster output.
  - Attacking before the cooldown is over would cause cooldown time to reset.
  - The new region "Forest of Wrath" is in development, and half of its rooms are done and accessible by now.
###  Demo

- **0.2.4** (Apr 23, 2022)
  - **What's new**: Money loot and **real-time combat**
  - Money can be taken from and dropped to the ground.
    - For this reason, players will not start with money in their inventory in order to prevent exploitation of the mechanism.
  - The stealth stat changed into wisdom.
  - Weapon stats revised.
  - Combat has been made real-time!
    - To run the game, please open both `Corburt` and `cbinput`, and type your commands at `cbinput`. `Corburt` should then be able to receive the commands.
  - Player hit points regenerate once per 30 seconds and enemies respawn every two minutes.
- **0.2.3** (Apr 16, 2022)
  - **What's new**: Stat edits
  - Hint message for selling items fixed.
  - Counters for enemies and items fixed.
  - Players can now edit stats.
    - Type "editstats" at the training room to edit stats.
    - Sadly, several stats have little to no use so far.
  - Calculation formulas for damage and defense revised.
  - Experience mechanics revised to prevent players from leveling up too fast.
- **0.2.2** (Apr 16, 2022)
  - **What's new**: Enemy item loot
  - Enemy entity data saving/loading functions implemented.
  - Map glitches fixed with CBME.
  - Enemies can respawn (currently once per 50 rounds).
  - Enemies are equipped with weapons and armors.
    - These could be dropped on their deaths and they contribute to enemies' stats.
  - Player's and enemies' death drops implemented.
    - On death, player loses 10% of their experience and money and one of their items.
  - Enemy stats slightly revised.
  - Player and enemies can now attack each other.
  - Functions accessing databases are revised and are more performant now.
  - Player hit points now regenerate once per 25 rounds.
- **0.2.1** (Apr 10, 2022)
  - **What's new**: Enemy attacks
  - Item stats slightly revised.
  - Implemented player death and revival (at specific spawn points).
  - Player's arrival to a new spawn point will be recorded.
  - Player's hit points slowly regenerate (once per 50 turns).
  - Map remade with [Corburt Map Editor](https://github.com/EinNeuerBenutzername/Corburt-Map-Editor).
- **0.2.0** (Mar 12, 2022)
  - **What's new**: Turns
  - Item stats slightly revised.
  - Version control improved.
  - Player stats structure revised.
  - Implemented the new command "time".
  - Currently, moving to another room takes 1 turn (30 ticks).
- **0.1.7** (Feb 4, 2022)
  - **What's new**: Selling items
  - Typos fixed.
  - Stability fix for commands: "buy", "take" and "drop".
  - Implemented the new command "sell".
  - Added a function to detect the version of the save file. 
    - Forward-compatibility is not yet taken into account, because Corburt is in a very early stage of development, meaning that the structure of save files would change many times in the future.
- **0.1.6** (Jan 30, 2022)
  - **What's new**: Taking & dropping items
  - "Use" function on consumable items implemented.
  - File I/O bug fixed.
  - The take & drop commands added.
  - Implemented a function to delete item entities.
  - Word wrap bug fixed.
- **0.1.5** (Jan 30, 2022)
  - **What's new**: Buying multiple items at once
    - Just send `buy 10 potion`.
  - "Buy" function bugs fixed.
  - Shop list display made ready for items with names that exceed the width limit.
  - Typedef replacements for database data types.
  - Inventory data saving & loading implemented.
  - Item entity data saving & loading implemented.
- **0.1.4** (Jan 29, 2022)
  - **What's new**: Visual & security improvements
  - Word wrap now detects CJK full-width characters.
  - Minor improvements on visual effects.
  - Weapon/armor bonus are added onto your stats.
  - Implemented brutal leak check for memory management. Corburt will now free all pointers at exit.
  - Free() and realloc() check whether the pointer is a malloc()'ed pointer.
  - Message "you can't afford it" fixed.
- **0.1.3** (Jan 29, 2022)
  - **What's new**: Purchasing stackable items is now possible
  - Word wrap improved.
  - Map fixed.
  - Stackable items can now be correctly pushed into inventory, thus now purchasable.
  - Directly pressing return without any input repeats your last command.
  - Items and enemies in a room are shown.
  - Added several checks for null exceptions.
- **0.1.2** (Jan 28, 2022)
  - **What's new**: Entities
  - Stackable items are temporarily unavailable for purchase.
    - This is because the merging feature of stackable items has not yet been implemented.
  - Implemented item entities and enemy entities.
  - Updated the function 'match' for stability and security.
  - Inventory layout remade.
  - The 'use' command added.
  - Enemies are now shown in room descriptions with brutal line breaks.
- **0.1.1** (Jan 27, 2022)
  - **What's new**: Shops
  - Finished shop lists.
  - Made item database for the goods.
  - The 'buy' command added: the first command with targets.
  - Fixed the function 'match' and tested name-matching.
  - Opened 'dbfio_.h' for database output. haven't yet put into use.
  - Room exits' structure revised to leave space for future updates; typo-fixed.
  - Enemy database opened. enemies might be added in the 0.1.2 update.
- **0.1.0** (Jan 25, 2022)
  - **What's new**: Region - Nameless City
  - Visual effect on windows terminal fixed (I guess).
  - Added several basic commands.
  - Typo & grammar fixes.
  - Added the first region: Nameless City (9kb database).
  - Map revised.
- **0.0.3** (Jan 23, 2022)
  - **What's new**: Basic commands
  - File I/O functions' portability greatly improved.
  - Basic curses library revised and finished.
  - Save / load functions implemented, only player stats are saved/loaded.
  - Added several basic commands.
  - Basic inventory information implemented.
  - Typo fixes.
  - Typedef revised: Corburt would now use signed 32- and 64-bit integers to store integer values.
  - Stability fixes on file I/O.
- **0.0.2** (Jan 22, 2022)
  - **What's new**: Basic game structure implementation
  - Added `<inttypes.h>` and `<stdbool.h>` dependencies for stability and portability.
  - Basic inventory functions implemented.
  - Basic curses library mostly finished.
  - Added trace log levels for info and debugging: 0 is none, and 2 is force explicit logging.
  - Commented several obsolete functions and fixed several functions with overflow risks.
  - Platform endianness detection added, enabling file I/O functions to convert data endianness.
  - Several empty databases created.
  - Several bugs fixed and several new bugs introduced.
- **0.0.1** (Dec 19, 2021)
  - **What's new**: Game interface
  - The very beginning of Corburt!
  - Basic file I/O functions implemented.
  - Basic player information implemented.
  - Added trace logs for info and debugging.
  - Several bugs introduced.