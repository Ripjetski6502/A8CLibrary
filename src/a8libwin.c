// --------------------------------------------------
// Library: a8libwin.c
// Desc...: Atari 8 Bit Window Library
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defwin.c
//          -Converted from Action!
//          -Type byte is synonymous with unsigned char (a8defines.h)
// Depends: a8libstr.c
// Revised: 2024.02-Added borderless window support.
// --------------------------------------------------

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include <peekpoke.h>
#include "a8defines.h"
#include "a8defwin.h"


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
void WInit(void);
void WBack(byte bN);
byte WOpen(byte x, byte y, byte w, byte h, byte bT, byte bB);
byte WClose(byte bN);
byte WStat(byte bN);
byte WPos(byte bN, byte x, byte y);
byte WPut(byte bN, byte x);
byte WPrint(byte bN, byte x, byte y, byte bI, unsigned char *pS);
byte WOrn(byte bN, byte bT, byte bL, unsigned char *pS);
byte WDiv(byte bN, byte y, byte bD);
byte WClr(byte bN);

unsigned int iSM;
unsigned int iSMr[24];


// --------------------------------------------------
// Function: void WInit(void)
// Desc....: Initialized windowing system
// --------------------------------------------------
void WInit(void)
{
    byte bL;

    // Setup cursor and screen
    POKE(ACURIN, 1);
    POKE(ALMARG, 0);
    clrscr();
    // Trick to prevent block in upper left
    gotoxy(39,24);

    // Clear window memory
    memset(baWM, 0, WBUFSZ);

    // Set index into window memory
    cpWM = baWM;

    // Work on 10 window+system handles
    for(bL=0; bL < 11; bL++) {
        // Clear window handle record vars
        baW.bU[bL] = WOFF;
        baW.bX[bL] = 0;
        baW.bY[bL] = 0;
        baW.bW[bL] = 0;
        baW.bH[bL] = 0;
        baW.bI[bL] = WOFF;
        baW.bB[bL] = WOFF;
        baW.cM[bL] = baWM;  // base storage location
        baW.cZ[bL] = 0;
    }

    // Set virtual cursor coords
    vCur.vX = 0;
    vCur.vY = 0;

    iSM = PEEKW(88);
    for (bL = 0; bL < 24; bL++) {
      iSMr[bL] = iSM + (bL * 40);
    }
}


// --------------------------------------------------
// Function: void WBack(byte bN)
// Desc....: Set screen background char
// Param...: bN = character to use
// Notes...: WBNONE for empty background
// --------------------------------------------------
void WBack(byte bN)
{
    // Fill screen memory with char
    memset(iSM, bN, 960);
}


// --------------------------------------------------
// Function: byte WOpen(byte x, byte y, byte w, byte h, byte bT, byte b)
// Desc....: Open a window
// Param...: x = column
//           y = row
//           w = width
//           h = height
//           bT = display in inverse
//                WON/WOFF
//           b = border flag
//               WON/WOFF
// Returns.: Window handle number
//           > 100 on error
// Notes...: cL is not manipulated as a string.
//           (0) is data, not size.
// --------------------------------------------------
byte WOpen(byte x, byte y, byte w, byte h, byte bT, byte b)
{
    byte bR = WENONE;
    byte bL, bD, bC;
    byte cL[41];
    word pS;

    // Cycle through handles (exluding system)
    for(bL=0; bL <= 10; bL++) {
        // If handle is not in use
        if (baW.bU[bL] == WOFF) {
            // Set handle in use
            baW.bU[bL] = WON;

            // Set storage address and size
            baW.cM[bL] = cpWM;
            baW.cZ[bL] = w * h;

            // Set other handle vars
            baW.bX[bL] = x;
            baW.bY[bL] = y;
            baW.bW[bL] = w;
            baW.bH[bL] = h;
            baW.bI[bL] = bT;
            baW.bB[bL] = b;

            // Find top left corner of window in memory
            pS = iSMr[y] + x;

            // Draw window
            for(bD=0; bD <= h-1; bD++) {
                // Build window line as string (internal char codes)
                memset(cL, 0, w);

                // If borders are on, define them
                if (b == WON) {
                    // If top or bottom line ("+-+")
                    if ((bD == 0) || (bD == h-1)) {
                        // Set solid line
                        memset(cL, 82, w);

                        // Top line corners
                        if (bD == 0) {
                            cL[0] = 81;
                            cL[w-1] = 69;
                        }
                        // Bottom line corners
                        else {
                            cL[0] = 90;
                            cL[w-1] = 67;
                        }
                        }
                    // Middle line "| |"
                    else {
                        // Set space and sides
                        memset(cL, 0, w);
                        cL[0] = 124;
                        cL[w-1] = 124;
                    }
                }

                // If inverse flag, flip line
                if (bT == WON) {
                    for (bC=0; bC <= w-1; bC++) {
                        cL[bC] ^= 128;
                    }
                }

                // Save underlying screen to win mem
                memcpy(cpWM, pS, w);
                // Inc mem ptr index by win width
                cpWM += w;
                // Move line to screen
                memcpy(pS, cL, w);
                // Inc screen by 40 to next line start
                pS += 40;
            }

            // Set return to handle number
            bR = bL;

            // Exit loop
            break;
        }
    }

    return(bR);
}


// --------------------------------------------------
// Function: byte WClose(byte bN)
// Desc....: Closes a window
// Param...: bN = window handle number
// Returns.: 0 if success
//           >100 on error
// --------------------------------------------------
byte WClose(byte bN)
{
    byte bR = WENOPN;
    byte bL;
    word pS;
    byte *pA;

    // Only if handle in use
    if (baW.bU[bN] == WON) {
        // Find top left corner of window in screen memory
        pS = iSMr[baW.bY[bN]] + baW.bX[bN];

        // Set temp ptr to start of win mem
        pA = baW.cM[bN];

        // Restore screen line by line
        for (bL=0; bL <= baW.bH[bN]-1; bL++) {
            // Restore underlying screen
            memcpy(pS, pA, baW.bW[bN]);
            // Inc mem ptr index by width
            pA += baW.bW[bN];
            // Inc screen by 40 to next line
            pS += 40;
        }

        // Clear window memory
        memset(baW.cM[bN], 0, baW.cZ[bN]);

        // Set win mem ptr to prev location
        cpWM -= baW.cZ[bN];

        // Clear handle
        baW.bU[bN] = WOFF;
        baW.bX[bN] = 0;
        baW.bY[bN] = 0;
        baW.bW[bN] = 0;
        baW.bH[bN] = 0;
        baW.bI[bN] = WOFF;
        baW.bB[bN] = WOFF;
        baW.cM[bN] = baWM;  // point as base storage
        baW.cZ[bN] = 0;

        // Set return
        bR = 0;
    }

    return(bR);
}


// --------------------------------------------------
// Function: byte WStat(byte bN)
// Desc....: Tests if window handle is open
// Param...: bN = window handle number
// Returns.: WON (in use)
//           WOFF (not used)
// --------------------------------------------------
byte WStat(byte bN)
{
    return(baW.bU[bN]);
}


// --------------------------------------------------
// Function: byte WPos(byte bN, byte x, byte y)
// Desc....: Moves cursor to x,y in window
//           or x,y of screen
// Param...: bN = window handle number
//                or WPABS for screen
// Returns.: WON (in use)
//           WOFF (not used)
// --------------------------------------------------
byte WPos(byte bN, byte x, byte y)
{
    byte bR = 0;

    // If absolute mode
    if (bN == WPABS) {
        // Set screen coords
        vCur.vX = x;
        vCur.vY = y;
    }
    // Window mode
    else {
        // Only if handle in use
        if (baW.bU[bN] == WON) {
            // Set relative window pos
            vCur.vX = baW.bX[bN] + x;
            vCur.vY = baW.bY[bN] + y;
        }
    }

    // Move actual cursor
    gotoxy(vCur.vX, vCur.vY);

    return(bR);
}


// --------------------------------------------------
// Function: byte WPut(byte bN, byte x)
// Desc....: Puts byte x in window at virtual curs coord
// Param...: bN = window handle number
//            x = ATASCII byte to display (char)
// Returns.: WON (in use)
//           WOFF (not used)
// --------------------------------------------------
byte WPut(byte bN, byte x)
{
    byte bR = WENOPN;
    byte bT;

    // Set working var
    bT = x;

    // Only if handle is used
    if (baW.bU[bN] == WON) {
        // If window is inverse, flip byte
        if (baW.bI[bN] == WON) {
            bT ^= 128;
        }

        // Put byte to screen at current cursor coord
        cputc(bT);

        // Increment virtual cursor by 1
        vCur.vX += 1;

        // Set return code
        bR = 0;
    }

    return(bR);
}


// --------------------------------------------------
// Function: byte WPrint(byte bN, byte x, byte y, byte bI, unsigned char *pS)
// Desc....: Print text in window at window pos
// Param...: bN = window handle number
//            x = column to print at
//            y = row to print at
//           bI = inverse flag (WON for inverse)
//           pS = text string pointer
// Returns.: 0 if success
//           >100 on error
// Notes...: Test will automatically be inverse if window is inverse.
// --------------------------------------------------
byte WPrint(byte bN, byte x, byte y, byte bI, unsigned char *pS)
{
    byte bR = WENOPN;
    byte bL;
    word cS;
    unsigned char cL[129];

    // Only if handle is in use
    if (baW.bU[bN] == WON) {
        // Copy string to line buffer
        strcpy(cL, pS);
        bL = strlen(cL);

        // Ensure text wont overrun
        // Check len not > width-(x-1)-2 (if frames on),
        // or len not > width-(x-1) (if frames off).
        // x is column, -1 for 0 based.
        if (bL > baW.bW[bN] - (x-1) - (baW.bB[bN] == WON ? 2 : 0)) {
            // Add terminator, get new length
            cL[baW.bW[bN] - (x-1) - (baW.bB[bN] == WON ? 2 : 0)] = '\0';
            bL = strlen(cL);
        }

        // Convert from ATA to Int
        StrAI(cL, bL);

        // Make inverse if asked
        if (bI == WON) {
            StrInv(cL, bL);
        }

        // Find row, from top left corner of window, in scrn mem (inside frame)
        cS = iSMr[baW.bY[bN] + y] + baW.bX[bN];

        // If not center, move to X pos
        if (x != WPCNT) {
            // Add x for column
            cS += x;
        }
        // Else move to centered position
        else {
            cS += ((baW.bW[bN] - bL)/2);
        }

        // Move line to screen
        memcpy(cS, cL, bL);

        // Set valid return
        bR = 0;
    }

    return(bR);
}


// --------------------------------------------------
// Function: byte WOrn(byte bN, byte bT, byte bL, unsigned char *pS)
// Desc....: Add ornament decor to window
// Param...: bN = window handle number
//           bT = Top or bottom (WPTOP/WPBOT)
//           bL = Position (WPLFT/WPRGT/WPCNT)
//           pS = Text string pointer
// Returns.: 0 if success
//           >100 on error
// Notes...: Max 36 for frame and bookends
// --------------------------------------------------
byte WOrn(byte bN, byte bT, byte bL, unsigned char *pS)
{
    byte bR = WENOPN;
    byte bS;
    word cS;
    unsigned char cL[37];

    // Only if handle in use
    if (baW.bU[bN] == WON) {
        // Create footer string
        sprintf(cL, "%c%s%c", CHSDLFT, pS, CHSDRGT);
        bS = strlen(cL);

        // Convert from ATA to Int
        StrAI(cL, bS);

        // If window inverse on, inverse all
        if (baW.bI[bN] == WON) {
            StrInv(cL, bS);
        }
        // Else, just inverse title part
        else {
            // Skip bookends
            StrInv(cL+1, bS-2);
        }

        // Find window top screen location
        cS = iSMr[baW.bY[bN]];

        // If bottom find lower location
        if (bT == WPBOT) {
            cS += ((baW.bH[bN] - 1) * 40);
        }

        // If left, add 1 (corner)
        if (bL == WPLFT) {
            cS += baW.bX[bN] + 1;
        }
        // If right, add x + width - length - 1
        else if (bL == WPRGT) {
            cS += baW.bX[bN] + baW.bW[bN] - bS - 1;
        }
        // Else center
        else {
            cS += baW.bX[bN] + ((baW.bW[bN] - bS) / 2);
        }

        // Move ornament to screen
        memcpy(cS, cL, bS);

        // Set valid return
        bR = 0;
    }

    return(bR);
}


// --------------------------------------------------
// Function: byte WDiv(byte bN, byte y, byte bD)
// Desc....: Add or remove divider
// Param...: bN = window handle number
//            y = Which row for divider
//           bD = Display On/Off flag
// Returns.: 0 if success
//           >100 on error
// --------------------------------------------------
byte WDiv(byte bN, byte y, byte bD)
{
    byte bR = WENOPN;
    byte bS, bL;
    word cS;
    unsigned char cL[41];

    // Only if window open
    if (baW.bU[bN] == WON) {
        // Get window width
        bS = baW.bW[bN];

        // Create divider string

        // If turning on, set ornaments
        if (bD == WON) {
            // Set solid line
            memset(cL, 82, bS);

            // If borders are on, set them to intersect
            if (baW.bB[bN] == WON) {
                cL[0] = 65;
                cL[bS-1] = 68;
            }
        }
        else {
            // Set blank line
            memset(cL, 0, bS);

            // If borders are on, set them to not intersect
            if (baW.bB[bN] == WON) {
                cL[0] = 124;
                cL[bS-1] = 124;
            }
        }

        // If inverse flag, flip line
        if (baW.bI[bN] == WON) {
            for (bL=0; bL <= bS-1; bL++) {
                cL[bL] ^= 128;
            }
        }

        // Find location on screen
        cS = iSMr[baW.bY[bN] + y] + baW.bX[bN];

        // Move to screen
        memcpy(cS, cL, bS);

        // Set valid return
        bR = 0;
    }

    return(bR);
}


// --------------------------------------------------
// Function: byte WClr(byte bN)
// Desc....: Clears window contents
// Param...: bN = window handle number
// Returns.: 0 if success
//           >100 on error
// --------------------------------------------------
byte WClr(byte bN)
{
    byte bR = WENOPN;
    byte bL, bS;
    word cS;
    unsigned char cL[38];

    // Only if window in use
    if (baW.bU[bN] == WON) {
        // Find top left corner of window in screen memory (inside frame)
        cS = iSMr[baW.bY[bN]] + baW.bX[bN] + 41;

        // Determine width (minus frames)
        bS = baW.bW[bN] - 2;

        // Set blank line
        memset(cL, 0, bS);

        // If window is inverse, flip line
        if (baW.bI[bN] == WON) {
            StrInv(cL, bS);
        }

        // Clear window line by line
        for (bL=1; bL <= baW.bH[bN] - 2; bL++) {
            memcpy(cS, cL, bS);
            cS += 40;
        }

        // Set valid return
        bR = 0;
    }

    return(bR);
}
