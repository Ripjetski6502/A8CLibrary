// ------------------------------------------------------------
// Program: stubmenh.c
// Desc...: A8 Library Horizontal Menu Stub Program
// Author.: Wade Ripkowski
// Date...: 20240211
// License: GNU General Public License v3.0
// Notes..: cl65 -v [-O] -t atari stubmenh.c -o stubmenh.xex
// ------------------------------------------------------------

// Pull in include files
#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <atari.h>

#include "a8defines.h"
#include "a8defwin.h"
#include "a8libmisc.c"
#include "a8libstr.c"
#include "a8libwin.c"
#include "a8libgadg.c"
#include "a8libmenu.c"

// ------------------------------------------------------------
// Func...: void main(void)
// Desc...: Main routine
// ------------------------------------------------------------
void main(void)
{
    // Variables
    byte bW1, bC, bD = FALSE;
    unsigned char cL[41];
    unsigned char *pcM[5] =
      { " File ", " Edit ", " Help ", " Exit " };

    // Init Window System
    WInit();

    // Set background
    WBack(14);

    // Set line character for menu bar
    memset(cL, 18, 40);

    // Open full width shallow height borderless window
    bW1 = WOpen(0, 0, 40, 2, WON, WOFF);
    WPrint(bW1, 0, 1, WOFF, cL);

    // Loop until done (Exit selected)
    while (! bD) {
        // Call menu
        bC = Menu(bW1, 1, 0, GHORZ, WON, 1, 4, pcM);

        // Process choice
        switch (bC)
        {
            case 1: GAlert("File Menu selected.");
                    break;

            case 2: GAlert("Edit Menu selected.");
                    break;

            case 3: GAlert("Help Menu selected.");
                    break;

            case 4: bD = TRUE;
                    break;
        }
    }

    // Close last windows
    WClose(bW1);

    // Exit
    return;
}
