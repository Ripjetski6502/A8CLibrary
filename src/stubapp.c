// ------------------------------------------------------------
// Program: stubapp.c
// Desc...: A8 Library Stub Application
// Author.: Wade Ripkowski
// Date...: 20220826
// License: GNU General Public License v3.0
// Notes..: cl65 -v [-O] -t atarixl stubapp.c -o stubapp.xex
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

// Prototypes
void About(void);
void SubMenu3(void);


// ------------------------------------------------------------
// Func...: void About(void)
// Desc...: About Dialog
// ------------------------------------------------------------
void About(void)
{
    byte bW1;

    // Show window
    bW1 = WOpen(1, 6, 38, 14, WOFF, WON);
    WOrn(bW1, WPTOP, WPLFT, "About");
    WPrint(bW1, WPCNT,  1, WOFF, "Demo Application");
    WPrint(bW1, WPCNT,  2, WOFF, "Version 1.00-C");
    WPrint(bW1, WPCNT,  3, WOFF, "(C) 2022  Wade Ripkowski");
    WPrint(bW1, WPCNT,  5, WOFF, "Application to demonstrate");
    WPrint(bW1, WPCNT,  6, WOFF, "the C library.");
    WPrint(bW1, WPCNT,  7, WOFF, "Converted from Action!.");
    WPrint(bW1, 4,      9, WOFF, "V1-2021-Atari8: Action!");
    WPrint(bW1, 2,     10, WOFF, "V1-C-2022-Atari8: C (CC65)");
    WPrint(bW1, WPCNT, 12, WON, " Ok ");

    // Wait for key
    WaitKCX(WOFF);

    // Close window
    WClose(bW1);

    return;
}


// ------------------------------------------------------------
// Func...: void SubMenu3(void)
// Desc...: Sub menu routine
// ------------------------------------------------------------
void SubMenu3(void)
{
    byte bW1, bC;
    byte bD = FALSE;
    unsigned char *pcM[4] = { " Sub-Item 1 ", " Sub-Item 2 ", " Sub-Item 3 " };

    // Open window
    bW1 = WOpen(16, 10, 14, 5, WOFF, WON);
    WOrn(bW1, WPTOP, WPLFT, "Sub-Menu");

    // Loop until exit
    while (! bD) {
        // Display menu and get choice
        bC = Menu(bW1, 1, 1, GVERT, WOFF, 1, 3, pcM);

        // Process choice
        switch (bC) {
            case 1: GAlert(" Sub-Item 1 selected. ");
                    break;

            case 2: GAlert(" Sub-Item 2 selected. ");
                    break;

            case 3: GAlert(" Sub-Item 3 selected. ");
                    break;

            case XESC: bD = TRUE;
                       break;
        }
    }

    // Close window
    WClose(bW1);

    return;
}


// ------------------------------------------------------------
// Func...: void main(void)
// Desc...: Main routine
// ------------------------------------------------------------
void main(void)
{
    // Variables
    byte bW1, bW2, bC;
    byte bD = FALSE;
    unsigned char *pcM[6] =
      { " Sub-Menu 1 ", " Sub-Menu 2 ", " Sub-Menu 3 ", " About      ", " Exit       " };

    // Setup screen
    WInit();

    // Set Background
    WBack(14);

    // Open header window
    bW1 = WOpen(0, 0, 40, 3, WON, WON);
    WPrint(bW1, WPCNT, 1, WON, "A P P L I C A T I O N");

    // Open menu window
    bW2 = WOpen(13, 7, 12, 9, WOFF, WON);
    WOrn(bW2, WPTOP, WPCNT, "Menu");

    // Loop until done (Exit selected)
    while (! bD) {
        // Call menu
        bC = Menu(bW2, 1, 2, GVERT, WOFF, 1, 5, pcM);

        // Process choice
        switch (bC) {
            case 1: GAlert(" Sub-Menu 1 selected. ");
                    break;

            case 2: GAlert(" Sub-Menu 2 selected. ");
                    break;

            case 3: SubMenu3();
                    break;

            case 4: About();
                    break;

            case 5: bD = TRUE;
                    break;
        }

        // Exit on ESC as well
        if (bC == XESC) {
            bD = TRUE;
        }
    }

    // Close windows
    WClose(bW2);
    WClose(bW1);

    // Exit
    return;
}
