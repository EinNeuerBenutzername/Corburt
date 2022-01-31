# Corburt

## About

Corburt is a pretty simple text-based RPG game developed based on the ideas of *SimpleMUD*. The original codebase for SimpleMUD was written in C++ by Ron Penton, the author of MUD Game Programming book.

Inspirations come from a game called [93 Realms](http://windows93.net:8083/), which my friends and I had a great time playing in 2021.

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

## Bug report

When reporting bugs (if you came across any), please clarify:

- what's the version of Corburt?
  - if it is not the latest version, test on the latest version.
- if you compiled Corburt yourself, what compiler are you using?
  - if you're using compilers that don't actually support C99, I might just ignore you.
  - btw, GCC doesn't actually **totally** support C99.
- what had you done before the bug occurred?
- were there any error messages?
- were any error log files generated?
- did the game crash?

## Typo report

Please report if you find any typos or grammar mistakes.

## Version history
### Demo Version

- **0.1.7** (WiP)
  - typos fixed.
  
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