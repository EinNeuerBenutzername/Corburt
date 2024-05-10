# Corburt

## Overview

**General**

**Corburt** is a pretty simple real-time text-based RPG game developed based on the ideas of *SimpleMUD* initially, the codebase for which was written in C++ by Ron Penton, the author of *MUD Game Programming* book. It was directly inspired by the game *[93 Realms](https://windows93.net:8083/)*, which my friends and I had a great time playing.

The game draws heavy influence from [Traditional Roguelikes](https://roguebasin.com) and [Interactive Fictions](https://www.ifarchive.org/), and aims to create a somewhat novel yet nostalgic atmosphere and gameplay experience. For portability and personal preference, Corburt is written in C99, and theoretically it supports Windows and most POSIX-compliant platforms.

<br>

**Current state of development**

Corburt is undergoing a major refactor starting from February 2024. Every line in Corburt's codebase would get rewritten. Up till now, Corburt is in a state of complete unplayability.

Time remaining before completion is unknown. Maybe it would never get finished; don't get your hopes too high.

I am an indie developer and would **not** fix issues, receive feedbacks or accept collabs or PRs (if there could ever possibly be any). This repo serves merely as an archive for Corburt's codebases, and if my development ends eventually, a tomb for it to rest.

<br>

## Guide to

**Compile**

- Your platform should satisfy the following:
  - A byte is exactly **8 bits**.
  - Endianness very probably doesn't matter, but bit-wise endianness should **not** exist.
  - Is **Windows**, or **POSIX-compliant**.
  - Is at least **32-bit**.
  - **Has** a file system, case sensitivity does not matter.
  - Fast multiple **simultaneous** access to the same file on **disk** is possible.
- Your C/C++ environment should satisfy the following:
  - Supports all ASCII characters.
  - Supports C99.
  - `CHAR_BIT` is **8**.
  - Supports **exact-width integers** in `<inttypes.h>`.
  
- Compile `cbinput.c` and `corburt.c` separately into 2 binary/executable files. There are no other source files in Corburt's codebase.
  - Simply `make cbinput` and `make corburt` if you have `make` installed. Alternatively, compile them with *Code::Blocks* (very recommended) or other C/C++ IDEs.

<br>

**Before launching**

- Corburt relies on disk I/O, so please avoid running Corburt while disk I/O is occupied (i.e. when copying, compressing or searching for files).
- Corburt is designed to run in PC's console terminals that supports:
  - Display with more than **20 rows** and more than **64 columns**.
  - **4-bit color** displays, ideally with **black as background color and white as foreground**. Other colors (i.e. blue in Windows Powershell) are not welcomed.
  - **Fixed-width font**.
- None of the above are mandatory, but it might heavily affect Corburt's graphic displays.

<br>

**Launch**

- Run `cbinput` first, and then open `corburt`. The order **might** matter on certain platforms.
- Please do **not** run multiple instances of `corburt` or `cbinput` simultaneously.
- Send input in `cbinput`, end line and send with return. The input **should** be received by `corburt`.
- To end game session, type `quit` in `cbinput` and return. The main game will close at the command and normally does not need to be closed manually.

<br>

**Port Corburt to other platforms**

- As long as the target system supports C99, it should be possible for Corburt to be ported to the target platform.
- Corburt's system dependency should only exist in `cbcurses.h` and `cbsys.h`. Add support for the target platform in the two headers.
- For platforms without support for `<inttypes.h>`'s exact-width integers but still have integral variable types with exact widths of 32 and 64 bits, it is still possible to port Corburt to them through changing typedefs and macros for variable types.
- Endianness issues are currently not a problem to consider. Nor are non 8-bit bytes or non 8-bit chars, or lack of support for 32-bit and 64-bit integral types whatsoever.
- Any portability issue not listed in this list are not taken into consideration.

<br>

## Acknowledgements

- Ideas:
  - **Ron Penton**, author of *MUD Game Programming*
  - **Jankenpopp** and other developers of *93 Realms*
- Libraries:
  - **JC Wang** (@jcwangxp) for [Crossline](https://github.com/jcwangxp/Crossline), where I snatched snippets to make `cbcurses.h`.
- Dev:
  - My friend **emf** and **Jack Q** for supporting me all the time, giving valuable advice, contributing to Corburt and testing it.
- And you, probably ;)

<br>

## Updates

**v0.4.1** on May 10, 2024

- `CBSYS`: Indicate a fatal error and force exit on allocation failure. Also fixed the problem that the wrapping of time measurement is incorrect.
- `CBIO`: Implemented colored word wrap with inline color indicator support. Color indicators in the middle of words do not affect the behavior of word wrapping.
- `CBPALETTE`: Setup palette templates.
- `CBRNG`: Tested and probably stable.

**v0.4.0** on Feb 12, 2024

- `CBCURSES`: Complete and probably stable.
- `CBSYS`: Stable and probably complete.
- `CBFIO`: Implemented working directory setup and `fopen()` with relative path (which is not the default behavior on MacOS).
- `CBIO`: Implemented two matching commands.
- `CBPROTO`: Setup typedefs.
- `CBRNG`: Implemented MT19937 and MT19937-64.
- `CBUTILS`: FPS hint and RNG.
