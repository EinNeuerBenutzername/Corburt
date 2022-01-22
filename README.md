# Corburt

## About

Corburt is a pretty simple text-based RPG game developed based on the ideas of *SimpleMUD*. The original codebase for SimpleMUD was written in C++ by Ron Penton, the author of MUD Game Programming book.

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

- your compiler should support C99 with these standard C libraries:
  - <inttypes.h>
    - for `uint_fastX_t` types
  - <locale.h>
    - for Unicode support
  - <stdarg.h>
    - for I/O
  - <stdbool.h>for the bool type
    - <stdio.h>
  - for I/O
    - <stdlib.h>for memory management
  - <time.h>
    - for RNG
  - <wchar.h>
    - for Unicode support
  - it is recommended to use GCC compiler.
    - it's especially recommended to use Code::Blocks to compile.

## Acknowledgements

- **Ron Penton**, author of *MUD Game Programming*
- **Jankenpopp** and other developers of *93 Realms*
- **JC Wang** (@jcwangxp) for [Crossline](https://github.com/jcwangxp/Crossline)
- **Evan Sultanik** (@ESultanik) for [MTwister](https://github.com/ESultanik/mtwister)
- My friend **emf** and **Jack Q** for supporting me
- You, probably ;)

## Version history
### Demo Version
- 0.0.1 (Dec 2021)
  - the very beginning of Corburt!
  - basic file IO functions implemented.
  - basic player information implemented.
  - messaging system implemented.
  - added tracelogs for info and debugging.
  - several bugs introduced.

- 0.0.2 (Jan 2022)
  - added <inttypes.h> and <stdbool.h> dependencies for stability and portability.
  - basic inventory functions implemented.
  - basic curses library mostly finished.
  - added tracelog levels for info and debugging: 0 is none, and 2 is force explicit logging.
  - removed several obsolete functionsi and fixed several functions with overflow risks.
  - platform endianess detection added, enabling file i/o functions to convert data endianess.
  - several empty databases created.
  - several bugs fixed and several new bugs introduced.
