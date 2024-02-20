// --------------------------------------------------
// Library: a8libmenu.c
// Desc...: Atari 8 Bit Menu Library
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.c
//          -Converted from Action!
//          -Type byte is synonymous with unsigned char (a8defines.h)
// Require: a8libwin.c
//          a8libstr.c
//          a8libmisc.c
// Revised: 2024.02.20-Correct GVERT dehilite location.
// --------------------------------------------------

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "a8defines.h"


// --------------------------------------------------
// Defines to preserve backward call compatability.
// --------------------------------------------------
#define MenuV(a,b,c,d,e,f,g) Menu(a,b,c,GVERT,d,e,f,g)


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
byte Menu(byte bN, byte x, byte y, byte bO, byte bI, byte bS, byte bC, unsigned char **pS);


// ------------------------------------------------------------
// Func...: byte Menu(byte bN, byte x, byte y, byte bO, byte bI, byte bS, byte bC, unsigned char **pS)
// Desc...: Vertical or Horizontal menu
// Param..: bN = Window handle number
//           x = window column for cursor
//           y = window row for cursor
//          bO = Orientation
//               GHORZ = Horizontal (1 line)
//               GVERT = Vertical   (stacked)
//          bI = Inverse flag (WON = leave on at selection)
//          bS = Start item number
//          bC = Number of menu items
//          pS = pointer to array of menu item strings
// Return.: Selected item #, ESC (XESC), or TAB (XTAB)
// ------------------------------------------------------------
byte Menu(byte bN, byte x, byte y, byte bO, byte bI, byte bS, byte bC, unsigned char **pS)
{
    byte bF = FALSE;
    byte bL, bR, bK;
    unsigned char cL[41];

    // Set default return to start item #
    bR = bS;

    // Continue until finished
    while (! bF) {
        // Display each item
        for (bL=0; bL<bC; bL++) {
            strcpy(cL, pS[bL]);

            // Highlight selection based on orientation
            if (bO == GHORZ) {
                // Display item at row count - inverse if start item
                WPrint(bN, x+(bL*strlen(cL)), y, (bL+1 == bR ? ! baW.bI[bN] : baW.bI[bN]), cL);
            } else {
                // Display item at row count - inverse if start item
                WPrint(bN, x, y+bL, (bL+1 == bR ? WON : WOFF), cL);
            }
        }

        // Get key (no inverse key)
        bK = WaitKCX(WOFF);

        // Process key
        if ((bK == KDOWN) || (bK == KEQUAL) || (bK == KRIGHT) || (bK == KASTER)) {
            // Increment (move down list)
            bR += 1;

            // Check for overrun and roll to top
            if (bR > bC) {
                bR = 1;
            }
        }
        else if ((bK == KUP) || (bK == KMINUS) || (bK == KLEFT) || (bK == KPLUS)) {
            // Decrement (move up list)
            bR -= 1;

            // Check for underrun and roll to bottom
            if (bR < 1) {
                bR = bC;
            }
        }

        // Set last selected item before checking for ESC/TAB/ENTER
        bL = bR;

        // If ESC, set choice to XESC
        if (bK == KESC) {
            bR = XESC;
            bF = TRUE;
        }
        // For TAB, set choice to XTAB
        else if (bK == KTAB) {
            bR = XTAB;
            bF = TRUE;
        }
        // For enter, just exit
        else if (bK == KENTER) {
            bF = TRUE;
        }
    }

    // Uninverse last selection if needed
    if (bI == WOFF) {
        strcpy(cL, pS[bL-1]);

        // Unhighlight selection based on orientation
        if (bO == GHORZ) {
            WPrint(bN, x+((bL-1)*strlen(cL)), y, WOFF, cL);
        } else {
            WPrint(bN, x, y+bL-1, WOFF, cL);
        }
    }

    return(bR);
}
