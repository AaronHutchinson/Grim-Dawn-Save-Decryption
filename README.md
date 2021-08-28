# Grim-Dawn-Save-Decryption
Decryption tools for save files for the PC game Grim Dawn. These files are an updated version of those written by "Christopher" and found at https://www.lost.org.uk/grimdawn.html, and nearly all credit for these tools goes to them.

**Compatibility**: These tools were updated to be compatible with Grim Dawn version 1.1.9.1 with both Ashes of Malmouth and Forgotten Gods expansions and Crucible DLC. The code is almost certainly incompatible with vanilla GD without the expansions/DLC.

**File Correspondence**:
* `decrypt-player.cpp` is the updated version of `decryptsave.cc`.
* `decrypt-transfer.cpp` is the updated version of `decryptstash.cc`.
* I haven't updated `decryptquests` and am unsure if I ever will.

**Major changes** from original version:
* updated "version number" checks throughout to match current GD encoding versions
* an additional byte "3" is read after the header
* `character_stash` was updated to read/write multiple stash tabs, as AoM changed personal stash to have multiple tabs
* `ui_settings` reads/writes an additional 10 integers at the end of the block. The usage/interpretation of these integers is unknown to me, and in all of my testing all but the last were equal to 4294967295.
* `play_stats` reads/writes some additional data along with 13 bytes, which it seems are related to Shattered Realm.
* to help with debugging and out of my own curiosity, I wrote primitive print functions for many of the classes to actually see what the data is.
* exception handling was updated to report more information about where runtime errors occur.
* changed a few variable names to be more accurate or descriptive about what information they're holding.

**Acknowledgements**:
* Nearly all credit goes to "Christopher" of https://www.lost.org.uk, as (as far as I know) they wrote the original file. I merely updated it.
* Thanks to "mamba" for sharing some of their GD Stash code and giving insight on how to read/interpret some of the new data.

**Disclaimer**: I am not responsible if these tools corrupt your game files. Make backups of all of your files before using this tool.
