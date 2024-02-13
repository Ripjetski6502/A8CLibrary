// ------------------------------------------------------------
// Program: stubwin.c
// Desc...: A8 Library Stub Window Program
// Author.: Wade Ripkowski
// Date...: 20220826
// License: GNU General Public License v3.0
// Notes..: cl65 -v [-O] -t atarixl stubwin.c -o stubwin.xex
// ------------------------------------------------------------

// Pull in include files
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <atari.h>

#include "a8defines.h"
#include "a8defwin.h"
#include "a8libstr.c"
#include "a8libwin.c"
#include "a8libmisc.c"


// ------------------------------------------------------------
// Func...: void main(void)
// Desc...: Main routine
// ------------------------------------------------------------
void main(void)
{
    // Variables
    byte bW1, bW2, bW3;

    // Init Window System
    WInit();

    // Set background
    WBack(14);

    // Open normal window
    bW1 = WOpen(8, 3, 24, 9, WOFF, WON);
    WOrn(bW1, WPTOP, WPLFT, "Stub");
    WPrint(bW1, 5, 2, WOFF, "Inverse");
    WPrint(bW1, 12, 2, WON, "ATASCII");
    WPrint(bW1, WPCNT, 4, WOFF, "Unfinished Bitness");
    WPrint(bW1, WPCNT, 6, WON, " Ok ");

    // Open full width shallow height borderless window
    bW2 = WOpen(0, 0, 40, 2, WON, WOFF);
    WPrint(bW2, WPCNT, 0, WON,  "Borderless Window");

    // Open inversed borderless window
    bW3 = WOpen(8, 13, 24, 9, WON, WOFF);
    WPrint(bW3, 5, 2, WON, "Inverse");
    WPrint(bW3, 12, 2, WOFF, "ATASCII");
    WPrint(bW3, WPCNT, 4, WON, "Unfinished Bitness");
    WPrint(bW3, WPCNT, 6, WOFF, " Ok ");

    // Wait for a keystroke or console key
    WaitKCX(WOFF);

    // Close last windows
    WClose(bW3);
    WClose(bW2);
    WClose(bW1);

    // Exit
    return;
}
