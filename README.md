# Corburt

## About

Corburt is a pretty simple text-based RPG game developed based on the ideas of *SimpleMUD*. The original codebase for SimpleMUD was written in C++ by Ron Penton, the author of MUD Game Programming book.

## Features/Highlights

- written in plain C code (C99).
- multi-platform support: should work on Windows, Linux, MacOS and several \*nixes.
- no external dependencies (hopefully).
- open source.
- easy to compile: only one .c file, all other files are headers.

## Drawbacks

- it's in a very early stage of development.
- might not be finished.
- might not work properly on non-Windows platforms.
- not yet C++-compatible.
- I am lazy and might not be available for improvements and bug fixes.

## Requirements

- your compiler should support C95 for these standard C libraries:
  - <time.h>
  - <wchar.h> (C95)
  - <locale.h>
  - <stdarg.h>
  - <stdlib.h>
  - you may also remove the <wchar.h> dependency and complie in ANSI C.
  - it is recommended to use GCC compiler.
- your platform should support the [Crossline](https://github.com/jcwangxp/Crossline) library.
  - it is said to support Windows, Linux, Unix, and MacOS.

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
