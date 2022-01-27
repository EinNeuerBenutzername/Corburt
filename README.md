# Corburt

## About

Corburt is a pretty simple text-based RPG game developed based on the ideas of *SimpleMUD*. The original codebase for SimpleMUD was written in C++ by Ron Penton, the author of MUD Game Programming book.

Inspirations come from a game called [93 Realms](http://windows93.net:8083/), which my friends and I had a great time playing in 2021.

## Features/Highlights

- **written in plain C code** (C99).
- **multi-platform support**: should work on Windows, Linux, MacOS and several \*nixes.
- **no external dependencies** (hopefully).
- **open source**.
- **easy to compile**: only one .c file, all other files are headers.

## Drawbacks

- it's in a **very early stage of development**.
- might **not** be finished.
- might **not** work properly on non-Windows platforms.
  - might not even work properly on Windows platforms other than Windows 10.
- **not** yet C++-compatible.
- I am lazy and might **not** be available for improvements and bug fixes.

## Requirements

- your computer should either be non-prehistorical Windows or POSIX-compliant \*nix.
  - this is largely because Corburt's curses library rely on platform-specific headers.
- your compiler should support C99 with these standard C libraries:
  - <inttypes.h>
    - for `uint_fastX_t` types
  - <locale.h>
    - for Unicode support
  - <stdarg.h>
    - for I/O
  - <stdbool.h>
    - for the bool type
  - <stdio.h>
    - for I/O
  - <stdlib.h>
    - for memory management
  - <time.h>
    - for RNG
  - <wchar.h>
    - for Unicode support
- on your computer, a byte **must** contain exactly 8 bits.
  - it is also suggested that the size of wchar_t is exactly 16 bits. it's okay if that's not the case, though.
- it is recommended to use GCC compiler.
  - it's especially recommended to use Code::Blocks to compile.

## Acknowledgements

- For libraries:
  - **Ron Penton**, author of *MUD Game Programming*
  - **Jankenpopp** and other developers of *93 Realms*
  - **JC Wang** (@jcwangxp) for [Crossline](https://github.com/jcwangxp/Crossline)
  - **Evan Sultanik** (@ESultanik) for [MTwister](https://github.com/ESultanik/mtwister)
- My friend **emf** and **Jack Q** for supporting me and testing Corburt
- You, probably ;)

## Version history
### Latest (v0.1.1)
- News
  - You can now walk around a nameless city and purchase items.
- Future plans
  - Add entities support in the next update.
  - Add enemies and combat.

### Demo Version
- 0.0.1 (Dec 2021)
  - the very beginning of Corburt!
  - basic file I/O functions implemented.
  - basic player information implemented.
  - added tracelogs for info and debugging.
  - several bugs introduced.

- 0.0.2 (Jan 2022)
  - added <inttypes.h> and <stdbool.h> dependencies for stability and portability.
  - basic inventory functions implemented.
  - basic curses library mostly finished.
  - added tracelog levels for info and debugging: 0 is none, and 2 is force explicit logging.
  - commented several obsolete functions and fixed several functions with overflow risks.
  - platform endianess detection added, enabling file I/O functions to convert data endianess.
  - several empty databases created.
  - several bugs fixed and several new bugs introduced.

- 0.0.3 (Jan 2022)
  - file I/O functions' portability greatly improved.
  - basic curses library revised and finished.
  - save/load functions implemented, only player stats are saved/loaded.
  - added several basic commands.
  - basic inventory information implemented.
  - typo fixes.
  - typedef revised: corburt would now use signed 32- and 64-bit integers to store integer values.

- 0.1.0 (Jan 2022)
  - visual effect on windows terminal fixed (I guess).
  - added several basic commands.
  - typo & grammar fixes.
  - added the first region: Nameless City (9kb database).
  - map revised.

- 0.1.1 (Jan 2022)
  - finished shop lists.
  - made item database for the goods.
  - added the 'buy' command: the first command with targets.
  - fixed the function 'match' and tested name-matching.
  - opened 'dbfio_.h' for database output.
  - room exits' structure revised to leave space for future updates; typo-fixed.
  - enemy database opened. enemies might be added in the 0.1.2 update.

