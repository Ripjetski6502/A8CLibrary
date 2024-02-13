// --------------------------------------------------
// Library: a8libmisc.c
// Desc...: Atari 8 Bit Misc Library
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.c
//          -Converted from Action!
//          -Type byte is synonymous with unsigned char (a8defines.h)
// Require: string.h
// Revised:
// --------------------------------------------------

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "a8defines.h"
#include <peekpoke.h>


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
byte IKC2ATA(byte bN);
byte WaitYN(byte bD);
word WaitKCX(byte bI);


// ------------------------------------------------------------
// Func...: byte IKC2ATA(byte bS)
// Desc...: Converts internal key code to ATASCII
// Param..: bN = Internal code
// Return.: ATASCII code for IKC<192
//          bN for IKC>191
//          199 for no mapping
// Notes..: Does not change if IKC>191
// ------------------------------------------------------------
byte IKC2ATA(byte bN)
{
    byte bR;
    unsigned char cL[192] = {
        108, 106,  59, 199, 199, 107,  43,  42, 111, 199,
        112, 117, 155, 105,  45,  61, 118, 199,  99, 199,
        199,  98, 120, 122,  52, 199,  51,  54, 199,  53,
         50,  49,  44,  32,  46, 110, 199, 109,  47, 199,
        114, 199, 101, 121, 199, 116, 119, 113,  57, 199,
         48,  55, 199,  56,  60,  62, 102, 104, 100, 199,
        199, 103, 115,  97,  76,  74,  58, 199, 199,  75,
         92,  94,  79, 199,  80,  85, 199,  73,  95, 124,
         86, 199,  67, 199, 199,  66,  88,  90,  36, 199,
         35,  38, 199,  37,  34,  33,  91,  32,  93,  78,
        199,  77,  63, 199,  82, 199,  69,  89, 199,  84,
         87,  81,  40, 199,  41,  39, 199,  64, 199, 199,
         70,  72,  68, 199, 199,  71,  83,  65,  12,  10,
        123, 199, 199,  11, 199, 199,  15, 199,  16,  21,
        199,   9, 199, 199,  22, 199,   3, 199, 199,   2,
         24,  26, 199, 199, 199, 199, 199, 199, 199, 199,
        199, 199,  96,  14, 199,  13, 199, 199,  18, 199,
          5,  25, 199,  20,  23,  17, 199, 199, 199, 199,
        199, 199, 199, 199,   6,   8,   4, 199, 199,   7,
         19,   1
    };

    // Get ATASCII from array if icode<192
    if (bN < 192) {
        bR = cL[bN];
    }
    // Else dont change it
    else {
        bR = bN;
    }

    return(bR);
}


// ------------------------------------------------------------
// Func...: byte WaitYN(byte bD)
// Desc...: Waits for Y or N keypress
// Param..: bD = WON to print Y or N, or WOFF for no echo
// Return.: 1=Yes, 0=No
// ------------------------------------------------------------
byte WaitYN(byte bD)
{
    byte bR = 0, bK = 0;

    // Loop until keypress matches yYnN
    do {
        // Wait for keypress
        while (! kbhit()) {};

        // Get keypress and debounce
        bK = PEEK(KEYPCH);
        POKE(KEYPCH, KNONE);
    } while ((bK != 43) && (bK != 107) && (bK != 35) && (bK != 99));

    // If Yy then set return 1
    if ((bK == 43) || (bK == 107)) {
        bR = 1;
    }

    // If echo asked for
    if (bD == WON) {
        // If Y, print Y
        if (bR == 1) {
            cputc('Y');
        }
        else {
            cputc('N');
        }
    }

    return(bR);
}


// ------------------------------------------------------------
// Func...: word WaitKCX(byte bI)
// Desc...: Waits for any key, console, or help key press.
// Param..: bI = WON to allow inverse toggle, else WOFF.
// Return.: keycode pressed
// Notes..: XL/XE only
// ------------------------------------------------------------
word WaitKCX(byte bI)
{
    word cR = 0;
    byte bK, bC, bH, bU;

    // Wait for one of the keys
    while((PEEK(KEYPCH) == KNONE) && (PEEK(CONSOL) == KCNON) && (PEEK(HELPFG) == 0)) {}

    // Grab the register values
    bK = PEEK(KEYPCH);
    bC = PEEK(CONSOL);
    bH = PEEK(HELPFG);

    // Process console key
    if (bC != KCNON) {
        cR = bC + 256;
    }
    // Process help key, must debounce
    else if (bH > 0) {
        cR = KFHLP;
        POKE(HELPFG, 0);
    }
    // Toggle CAPS
    else if (bK == KCAP) {
        cR = bK;

        // Get current reg value, flip it, and put it back.
        bU = PEEK(SHFLOK);
        bU ^= 64;
        POKE(SHFLOK, bU);
    }
    // Toggle Inverse
    else if (bK == KINV) {
        cR = bK;

        // Toggle if allowed
        if (bI == WON) {
            // Get current reg value, flip it, and put it back.
            bU = PEEK(INVFLG);
            bU ^= 128;
            POKE(INVFLG, bU);
        }
    }
    // All else
    else {
        cR = bK;
    }

    // Debounce key
    POKE(KEYPCH, KNONE);

    return(cR);
}
