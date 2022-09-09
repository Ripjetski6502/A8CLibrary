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
    byte bW1;

    // Init Window System
    WInit();

    // Open window
    bW1 = WOpen(8, 5, 24, 9, WOFF);
    WOrn(bW1, WPTOP, WPLFT, "Stub");
    WPrint(bW1, 5, 2, WOFF, "Inverse");
    WPrint(bW1, 12, 2, WON, "ATASCII");
    WPrint(bW1, WPCNT, 4, WOFF, "Unfinished Bitness");
    WPrint(bW1, WPCNT, 6, WON, " Ok ");

    // Wait for a keystroke or console key
    WaitKCX(WOFF);

    // Close window
    WClose(bW1);

    // Exit
    return;
}
