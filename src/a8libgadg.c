// --------------------------------------------------
// Library: a8libgadg.c
// Desc...: Atari 8 Bit Gadget Library
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.c
//          -Converted from Action!
//          -Type byte is synonymous with unsigned char (a8defines.h)
// Require: a8libwin.c
//          a8libstr.c
//          a8libmisc.c
//          unistd.h (cc65)
// Revised: 2023.03.13-Revised SPACE in GCheck.
//                     Added ENTER to GCheck.
//                     Revised TAB in GCheck, GRadio, GSpin for consistency.
//          2023.07.28-Set GAlert min string width to 8.
//          2024.02.15-Added GList.
//          2024.02.18-Added GUPPER to GInput().
//          2024.02.20-Changed GList navigation to make more sense.
//          2024.03.12-Added GStat().
//          2025.01.03-Added GConf(), mod GAlert title.
//          2025.01.05-Fix GInput FNAME to allow 0 and space.
//          2025.01.11-Alter GAlert to GAlertM.
// --------------------------------------------------

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "a8defines.h"


// --------------------------------------------------
// Defines to preserve backward call compatability.
// --------------------------------------------------
#define GAlert(a) GAlertM(GAALERT,a)

// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
void GAlertM(byte bT, unsigned char *pS);
byte GConf(unsigned char *pS);
void GStat(byte bT, unsigned char *pS);
void GProg(byte bN, byte x, byte y, byte bS);
byte GButton(byte bN, byte x, byte y, byte bD, byte bS, unsigned char **pA);
byte GCheck(byte bN, byte x, byte y, byte bI, byte bD);
byte GRadio(byte bN, byte x, byte y, byte bD, byte bE, byte bI, byte bS, unsigned char **pS);
byte GSpin(byte bN, byte x, byte y, byte bL, byte bM, byte bI, byte bE);
byte GInput(byte bN, byte x, byte y, byte bT, byte bS, unsigned char *pS);
byte GList(byte bN, byte x, byte y, byte bE, byte bS, byte bM, byte bC, unsigned char **pS);


// ------------------------------------------------------------
// Func...: void GAlertM(byte bT, unsigned char *pS)
// Desc...: Displays centered alert on screen
// Param..: bT = Type of message to display
//
//          pS = Message string
// Notes..: 38 characters max
// ------------------------------------------------------------
void GAlertM(byte bT, unsigned char *pS)
{
    byte bW, bL, bR;
    word bK;
    unsigned char cL[11];

    // Determine ornament type
    switch (bT) {
        case GAALERT : strcpy(cL, " Alert! ");
                       break;
        case GAINFO  : strcpy(cL, " Info ");
                       break;
        case GAWARN  : strcpy(cL, " Warning! ");
                       break;
        case GAERR   : strcpy(cL, " Error! ");
                       break;
    }

    // Find string length
    bR = strlen(pS);

    // Ensure min window width met
    if (bR < 12) {
        bR = 12;
    }

    // Find left window position
    bL = ((38 - bR) / 2);

    // Show window
    bW = WOpen(bL, 10, bR + 2, 5, WOFF, WON);
    WOrn(bW, WPTOP, WPCNT, cL);
    WPrint(bW, WPCNT, 1, WOFF, pS);
    WPrint(bW, WPCNT, 3, WON, " OK ");

    // Wait for key
    bK = WaitKCX(WOFF);

    // Close window
    WClose(bW);
}


// ------------------------------------------------------------
// Func...: byte GConf(unsigned char *pS)
// Desc...: Displays message and gets confirmation
// Params.: pS = Message string
// Returns: Button number choice (1 = GCYES, 2 = GCNO)
// Notes..: 38 characters max
// ------------------------------------------------------------
byte GConf(unsigned char *pS)
{
    byte bW, bL, bR;
    unsigned char *paB[3] = { "[ Yes ]", "[ No ]" };

    // Find string length
    bR = strlen(pS);

    // Ensure min window width met
    if (bR < 14) {
        bR = 14;
    }

    // Find left window position
    bL = ((38 - bR) / 2);

    // Show window
    bW = WOpen(bL, 8, bR + 2, 8, WOFF, WON);
    WOrn(bW, WPTOP, WPCNT, " Confirm ");
    WPrint(bW, WPCNT, 2, WOFF, pS);
    WPrint(bW, 1, 4, WOFF, "Are you sure?");

    // Show buttons
    bR = GButton(bW, bR - 12, 6, GEDIT, 2, paB);

    // Close window
    WClose(bW);

    return(bR);
}


// ------------------------------------------------------------
// Func...: void GStat(byte bT, unsigned char *pS)
// Desc...: Displays a simple presized status window.
// Params.: bT = Open/Close flag
//               WON = Open (turn on)
//               WOFF = Close (turn off)
//          pS = String to display (28 char limit)
// ------------------------------------------------------------
void GStat(byte bT, unsigned char *pS)
{
    static unsigned char bSW = 0;

    // Open if asked
    if (bT == WON) {
        // Open status window
        bSW = WOpen(5, 10, 30, 3, WOFF, WON);

        // Display message
        WPrint(bSW, WPCNT, 1, WOFF, pS);
    } else {
        // Close window
        WClose(bSW);
    }
}


// ------------------------------------------------------------
// Func...: void GProg(byte bN, byte x, byte y, byte bS)
// Desc...: Displays centered alert on screen
// Param..: bN = Window handle number
//           x = Window column to display at
//           y = Window row to display at
//          bS = Bar size (percent complete, 0-100)
// Notes..: 38 characters max
// ------------------------------------------------------------
void GProg(byte bN, byte x, byte y, byte bS)
{
    unsigned int iL;
    unsigned char cL[21];

    // Set default and block line
    strcpy(cL, "                    ");

    // Update bar contents
    // Div by 5 since bar is 1/5 of 100
    iL = bS / 5;
    memset(cL, CHINVSP, iL);

    // Display new bar
    WPrint(bN, x, y, WOFF, cL);
}


// ------------------------------------------------------------
// Func...: byte GButton(byte bN, byte x, byte y, byte bD, byte bS, unsigned char **pA)
// Desc...: Displays buttons and get choice
// Param..: bN = Window handle number
//           x = Column of window to place buttons
//           y = Row of window to place buttons
//          bD = Initial selected button (0 to display and exit)
//          bS = Number of buttons
//          pS = Array of button strings
// Returns: button number choice (1 based) or XESC,XTAB
// Notes..: Button ornaments should be defined in strings.
//          Max length of all buttons is 38.
// ------------------------------------------------------------
byte GButton(byte bN, byte x, byte y, byte bD, byte bS, unsigned char **pA)
{
    byte bF = FALSE;
    byte bR, bL, bK, bP;

    // Set default return
    bR = bD;

    // Continue until exit
    while (! bF) {
        // Set drawing position offset
        bP = 0;

        // Display buttons
        for (bL=0; bL < bS; bL++) {
            // Display button (inverse if the selected one)
            WPrint(bN, x+bP, y, (bR == (bL + 1) ? WON : WOFF), pA[bL]);

            // Increase drawing position by button length
            bP += strlen(pA[bL]);
        }

        // If display item is 0, exit
        if (bD == GDISP) {
            bF = TRUE;
        }
        else {
            // Get a keystroke
            bK = WaitKCX(WOFF);

            // Process keystroke
            if ((bK == KLEFT) || (bK == KPLUS) || (bK == KUP) || (bK == KMINUS)) {
                // Decrement and check for underrun
                bR -= 1;
                if (bR < 1) {
                    bR = bS;
                }
            }
            else if ((bK == KRIGHT) || (bK == KASTER) || (bK == KDOWN) || (bK == KEQUAL)) {
                // Increment and check for overrun
                bR += 1;
                if (bR > bS) {
                    bR = 1;
                }
            }
            else if (bK == KESC) {
                bR = XESC;
                bF = TRUE;
            }
            else if (bK == KTAB) {
                bR = XTAB;
                bF = TRUE;
            }
            else if (bK == KENTER) {
                bF = TRUE;
            }
        }
    }

    return(bR);
}


// ------------------------------------------------------------
// Func...: byte GCheck(byte bN, byte x, byte y, byte bI, byte bD)
// Desc...: Displays check box and get choice
// Param..: bN = Window handle number
//           x = Column of window to place buttons
//           y = Row of window to place buttons
//          bI = Display Only indicator
//          bD = Default (initial value)
// Notes..: Associated text string should be drawn seperately.
// ------------------------------------------------------------
byte GCheck(byte bN, byte x, byte y, byte bI, byte bD)
{
    byte bF = FALSE;
    byte bR, bK, bC;

    // Set default return and current value to the passed default
    bR = bD;
    bC = bD;

    // Draw check frame
    WPrint(bN, x, y, WOFF, "[ ]");

    // Continue until finished
    while (! bF) {
        // If ON then add marker, else space, and inverse it
        WPrint(bN, x+1, y, WON, (bC == GCON ? "X" : " "));

        // If display only, exit
        if (bI == GDISP) {
            bF = TRUE;
        }
        else {
            // Get keystroke
            bK = WaitKCX(WOFF);

            // Process keystroke
            if (bK == KESC) {
                // Set esc exit and exit flag
                bR = XESC;
                bF = TRUE;
            }
            else if ((bK == KTAB) || (bK == KENTER)){
                // Accept value and exit
                bR = bC;
                bF = TRUE;
            }
            else if ((bK == KSPACE) || (bK == KEYX) || (bK == KEYX_S)) {
                // Toggle value
                bC = (bC == GCON ? GCOFF : GCON);
                bR = bC;
            }
        }
    }

    // If current and return are same
//    if (bR == bC) {
        // Show exit value
        WPrint(bN, x+1, y, WOFF, (bC == GCON ? "X" : " "));
//    }
//    else {
        // Show default value (no change)
//        WPrint(bN, x+1, y, WOFF, (bD == GCON ? "X" : " "));
//    }

    return(bR);
}


// ------------------------------------------------------------
// Func...: byte GRadio(byte bN, byte x, byte y, byte bD, byte bE, byte bI, byte bS, unsigned char **pS)
// Desc...: Display radio buttons and get choice
// Param..: bN = Window handle number
//           x = Column of window to place buttons
//           y = Row of window to place buttons
//          bD = Direction of button placement
//          bE = Edit or display indicator (0 to display and exit)
//          bI = Initial selected button
//          bS = Number of buttons
//          pS = Pointer to array of radio button strings
// ------------------------------------------------------------
byte GRadio(byte bN, byte x, byte y, byte bD, byte bE, byte bI, byte bS, unsigned char **pS)
{
    byte bF = FALSE;
    byte bR, bL, bK, bC, xp, yp;

    // Set default return and current button tod default passed in
    bR = bI;
    bC = bI;

    // Loop until exit
    while (! bF) {
        // Set drawing position
        xp = 0;
        yp = 0;

        // Display buttons
        for (bL=0; bL < bS; bL++) {
            // If current item then add pointer, else space
            WPos(bN, x+xp, y+yp);
            if (((bL + 1) == bC) && (bE != GDISP)) {
                WPut(bN, CHRGT_I);
            }
            else {
                WPut(bN, CHSPACE);
            }

            // If selected then add filled circle, else unfilled
            WPos(bN, x+xp+1, y+yp);
            WPut(bN, (bL + 1) == bR ? CHBALL : CHO_L);

            // Display button label
            WPrint(bN, x+xp+3, y+yp, WOFF, pS[bL]);

            // Compute next button location
            if (bD == GHORZ) {
                // Increase X position
                xp += strlen(pS[bL]) + 4;
            }
            else {
                // Increase Y position
                yp += 1;
            }
        }

        // If initial item is display only, set exit flag
        if (bE == GDISP) {
            bF = TRUE;
        }
        // Not display, edit, do it.
        else {
            // Get keystroke
            bK = WaitKCX(WOFF);

            // Process keystrokes
            // Up or left
            if ((bK == KLEFT) || (bK == KPLUS) || (bK == KUP) || (bK == KMINUS)) {
                // Decrement and check for underrun
                bC -= 1;
                if (bC < 1) {
                    bC = bS;
                }
            }
            // Down or right
            else if ((bK == KRIGHT) || (bK == KASTER) || (bK == KDOWN) || (bK == KEQUAL)) {
                // Increment and check for overrun
                bC += 1;
                if (bC > bS) {
                    bC = 1;
                }
            }
            // ESC
            else if (bK == KESC) {
                bR = XESC;
                bF = TRUE;
            }
            // Space
            else if (bK == KSPACE) {
                bR = bC;
            }
            // Tab or Enter
            else if ((bK == KTAB) || (bK == KENTER)) {
                bR = bC;
                bF = TRUE;
            }
        }
    }

    return(bR);
}


// ------------------------------------------------------------
// Func...: byte GSpin(byte bN, byte x, byte y, byte bL, byte bM, byte bI, byte bE)
// Desc...: Display value and spin 0 to 100
// Param..: bN = Window handle number
//           x = Column of window to place buttons
//           y = Row of window to place buttons
//          bL = Lowest allowed value
//          bM = Max allowed value
//          bI = Initial value
//          bE = GDISP to display only, GEDIT to edit
// Return.: selected value or XESC
// Notes..: Max is 250 (above are form control values)
// ------------------------------------------------------------
byte GSpin(byte bN, byte x, byte y, byte bL, byte bM, byte bI, byte bE)
{
    byte bD, bK, bR;
    byte bF = FALSE;
    unsigned char cL[4];

    // Set working value to initial value
    bD = bI;

    // Ensure max is not greater than 250
    if (bM > 250) {
        bM = 250;
    }

    // If display only, just copy to string and set exit flag
    if (bE == GDISP) {
        sprintf(cL, "%3d", bD);
        bF = TRUE;
    }

    // Loop until exit
    while (! bF) {
        // Convert to string and display in inverse
        sprintf(cL, "%3d", bD);
        WPrint(bN, x, y, WON, cL);

        // Only adjust if in edit mode
        if (bE == GEDIT) {
            // Get key
            bK = WaitKCX(WOFF);

            // Process keystroke
            if ((bK == KLEFT) || (bK == KPLUS) || (bK == KDOWN) || (bK == KEQUAL)) {
                // Decrement only if not 0, then check for underrun
                bD -= (bD == 0 ? 0 : 1);
                if (bD < bL) {
                    bD = bL;
                }
            }
            else if ((bK == KRIGHT) || (bK == KASTER) || (bK == KUP) || (bK == KMINUS)) {
                // Increment and check for overrun
                bD += 1;
                if (bD > bM) {
                    bD = bM;
                }
            }
            else if (bK == KESC) {
                bR = XESC;
                bF = TRUE;
                sprintf(cL, "%3d", bI);
            }
            else if ((bK == KTAB) || (bK == KENTER)) {
                bR = bD;
                bF = TRUE;
                sprintf(cL, "%3d", bD);
            }
        }
    }

    // Redisplay value post edit, or initially for display only
    WPrint(bN, x, y, WOFF, cL);

    return(bR);
}


// ------------------------------------------------------------
// Func...: byte GInput(byte bN, byte x, byte y, byte bT, byte bS, unsigned char *pS)
// Desc...: Gets string with type restrictions
// Param..: bN = Window handle number
//           x = Column of window to place buttons
//           y = Row of window to place buttons
//          bT = Allowed character type
//          bS = Display size for string (max 40)
//          pS = Pointer to string to edit (max 128)
// ------------------------------------------------------------
byte GInput(byte bN, byte x, byte y, byte bT, byte bS, unsigned char *pS)
{
    // Defaults for return, start display and edit postions, and loop exit
    byte bR = FALSE, bD = 0, bE = 0, bF = FALSE;
    byte bK, bC, bL, bP, bZ, bI;
    unsigned char cD[41], cE[128];

    // Get string size
    bZ = strlen(pS);

    // Copy original string to edit buffer
    strcpy(cE, pS);

    // Loop until exit (ESC or RETURN)
    while (! bF) {
        // Copy display string from edit buffer
        strncpy(cD, cE + bD, bS);
        cD[bS] = '\0';

        // Inverse the cursor char & make sure it doesnt run past visible end
        bI = bE - bD;
        if (bI > bS - 1) {
            bI = bS - 1;
        }
        cD[bI] ^= 128;

        // Display editable portion of string in inverse
        WPrint(bN, x, y, WON, cD);

        // Wait for keystroke
        bK = WaitKCX(WOFF);

        // Get ATASCII version of keystroke
        bC = IKC2ATA(bK);

        // Is internal code RIGHT?
        if (bK == KRIGHT) {
            bE += 1;
        }
        // Is internal code LEFT?
        else if (bK == KLEFT) {
            // Decrement only if not 0 already
            bE -= (bE == 0 ? 0 : 1);
        }
        // Is internal code Ctrl-Shft-S (start of string)?
        else if (bK == KEYS_CS) {
            bE = 0;
        }
        // Is internal code Ctrl-Shft-E (end of string)?
        else if (bK == KEYE_CS) {
            bE = bZ;
        }
        // Is internal code DEL?
        // Set char to space, move position
        else if (bK == KDEL) {
            // Move edit and display positions if > 1
            if (bE > 0) {
                bE -= 1;
                cE[bE] = CHSPACE;
            }
        }
        // Is internal code Shift_Del?  (clear line)
        else if (bK == KDEL_S) {
            memset(cE, CHSPACE, bZ);
        }
        // Is internal code Ctrl-Del? (right delete)
        else if (bK == KDEL_C) {
            // Copy each char to the char before
            for (bL=bE; bL < bZ - 1; bL++) {
                cE[bL] = cE[bL+1];
            }

            // Set last char to space
            cE[bZ-1] = CHSPACE;
            cE[bZ] = '\0';
        }
        // Is internal code INS? (right insert)
        else if (bK == KINS) {
            // Only insert if not at end
            if (bE < bZ) {
                // Copy each char to the char after work from end
                for (bL=bZ; bL < bE + 1; bL--) {
                    cE[bL] = cE[bL-1];
                }

                // Put space in current position
                cE[bE] = CHSPACE;
            }
        }
        // Is internal code ENTER?
        else if (bK == KENTER) {
            // Copy edit buffer to original string
            strcpy(pS, cE);
            bR = TRUE;
            bF = TRUE;
        }
        // Is internal code ESC?
        else if (bK == KESC) {
            // Restore original string
            strcpy(cE, pS);
            bR = XESC;
            bF = TRUE;
        }
        // Is internal code TAB?
        else if (bK == KTAB) {
            // Restore original string
            strcpy(cE, pS);
            bR = XTAB;
            bF = TRUE;
        }
        // Is ATASCII code a printing char?
        // 0 (heart) is not possible
        else if ((bC >= 1) && (bC <= 191)) {
            // Set add flag to false
            bP = FALSE;

            // ----- Apply Type Restrictions -----

            // For ANY, allow all but cursor keys
            if ((bT == GANY) && ((bC <= 28) || (bC >= 32))) {
                bP = TRUE;
            }
            // For ALNUM, allow _ 0-9 A-Z a-z
            else if (bT == GALNUM) {
                if ((bC == 32) || ((bC >= 48) && (bC <= 57)) ||
                                  ((bC >= 65) && (bC <= 90)) ||
                                  ((bC >= 97) && (bC <= 122))) {
                    bP = TRUE;
                }
            }
            // For ALPHA, allow _ A-Z a-z
            else if (bT == GALPHA) {
                if ((bC == 32) || ((bC >= 65) && (bC <= 90)) ||
                                  ((bC >= 97) && (bC <= 122))) {
                    bP = TRUE;
                }
            }
            // For UPPER, allow (no space) A-Z
            else if (bT == GUPPER) {
                // Force upper case if lower typed
                if ((bC >= 97) && (bC <= 122)) {
                    bC -= 32;
                }
                // Check only A-Z
                if ((bC >= 65) && (bC <= 90)) {
                    bP = TRUE;
                }
            }
            // For LOWER, allow (no space) a-z
            else if (bT == GLOWER) {
                // Force lower case if lower typed
                if ((bC >= 65) && (bC <= 90)) {
                    bC += 32;
                }
                // Check only a-z
                if ((bC >= 97) && (bC <= 122)) {
                    bP = TRUE;
                }
            }
            // For NUMBER, allow . - 0-9
            else if (bT == GNUMER) {
                if ((bC == 45) || (bC == 46) ||
                    ((bC >= 48) && (bC <= 57))) {
                    bP = TRUE;
                }
            }
            // For FNAME, allow A-Z 1-8 * : . <space>
            else if (bT == GFNAME) {
                // Force upper case if lower typed
                if ((bC >= 97) && (bC <= 122)) {
                    bC -= 32;
                }
                // Check only valid chars
                if (((bC >= 65) && (bC <= 90)) ||
                    ((bC >= 48) && (bC <= 56)) ||
                    (bC == 42) || (bC == 58) || (bC == 46) || (bC == 32)) {
                    bP = TRUE;
                }
            }

            // Replace char in edit buffer at edit position if  allowed
            if (bP == TRUE) {
                cE[bE] = bC;
                bE += 1;
            }
        }

        // Check edit & display position extents

        // If edit > max len (-1=0 based), set equal (-1)
        if (bE > bZ - 1) {
            bE = bZ - 1;
        }

        // If edit >= display size, then display = edit - size + 1
        if (bE >= bS) {
            bD = bE - bS + 1;
        }
        // Else if edit < display size then display = 0
        else if (bE < bS) {
            bD = 0;
        }
    }

    // Get display string and print
    strncpy(cD, cE, bS);
    cD[bS] = '\0';
    WPrint(bN, x, y, WOFF, cD);

    return(bR);
}


// ------------------------------------------------------------
// Func...: byte GList(byte bN, byte x, byte y, byte bE, byte bS, byte bM, byte bC, unsigned char **pS)
// Desc...: List control
// Param..: bN = Window handle number
//           x = window column for cursor
//           y = window row for cursor
//          bE = Display or Edit flag
//               GDISP = Display only
//               GEDIT = Edit
//          bS = Start item number
//          bM = Max items to display at one time
//          bC = Number of items
//          pS = pointer to array of item strings
// Return.: Selected item #, ESC (XESC), or TAB (XTAB)
// ------------------------------------------------------------
byte GList(byte bN, byte x, byte y, byte bE, byte bS, byte bM, byte bC, unsigned char **pS)
{
    byte bF = FALSE, bL = 0, bI = 0, bR = 0;
    byte bK;
    unsigned char cL[41];

    // For display only, set start index to start item
    if (bE == GDISP) {
        // Set start index to start item #
        bI = bS - 1;
    } else {
        bR = bS;
    }

    // Continue until finished
    while (! bF) {
        // Display each item
        for (bL=0; bL < bM; bL++) {
            // Get item from array
            strcpy(cL, pS[bI + bL]);

            // Display item at row count
            if (bE == GDISP) {
                // Dont inverse on display only
                WPrint(bN, x, y + bL, WOFF, cL);
            } else {
                // Inverse if selected item
                WPrint(bN, x, y + bL, (bR == bL + 1 ? WON : WOFF), cL);
            }
        }

        // Only get if editing
        if (bE == GEDIT) {
            // Get key (no inverse key)
            bK = WaitKCX(WOFF);

            // Process key
            if ((bK == KDOWN) || (bK == KEQUAL) || (bK == KRIGHT) || (bK == KASTER)) {
                // If hilite row < max display
                if (bR < bM) {
                    // Increase hilite row
                    if (bR < bC) {
                        bR += 1;
                    }
                } else {
                    // If start index < elements - max display
                    if (bI < bC - bM) {
                        // Increase start index
                        bI += 1;
                    }
                }
            }
            else if ((bK == KUP) || (bK == KMINUS) || (bK == KLEFT) || (bK == KPLUS)) {
                // If hilite row > 1
                if (bR > 1) {
                    // Decrease row
                    bR -= 1;
                } else {
                    // If start index > 0
                    if (bI > 0) {
                        // Decrease start index
                        bI -= 1;
                    }
                }
            }
            // Ctrl-Shft-S (start of list)
            else if (bK == KEYS_CS) {
                // Set hilite row to 1, and index to 0
                bR = 1;
                bI = 0;
            }
            // Ctrl-Shft-E (end of list)
            else if (bK == KEYE_CS) {
                // If element count > max display
                if (bC > bM) {
                    // Set hilite row to max display, set index to cound - max display
                    bR = bM;
                    bI = bC - bM;
                } else {
                    // Set hilite row to field count, set index to 0
                    bR = bC;
                    bI = 0;
                }
            }

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
        } else {
            bF = TRUE;
        }
    }

    return(bR);
}
