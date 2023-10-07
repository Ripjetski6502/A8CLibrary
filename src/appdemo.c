// ------------------------------------------------------------
// Program: appdemo.c
// Desc...: A8 Library Demo Application
// Author.: Wade Ripkowski
// Date...: 20220825
// License: GNU General Public License v3.0
// Notes..: cl65 -v [-O] -t atarixl appdemo.c -o appdemo.xex
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

#define PERF_TEST

// Prototypes
void DoSpin(void);
byte FormInput(void);
void ProgTest(void);
void About(void);


// ------------------------------------------------------------
// Func...: void FormInput(void)
// Desc...: Demo use of input gadgets
// Returns: TRUE if accepted, else FALSE
// Notes..: Maximum local variable stack space is 256 bytes.
//          MUST use pragma static-locals to move variables to
//          BSS segment due to total size in this function.
// ------------------------------------------------------------
#pragma static-locals(push, on)
byte FormInput(void)
{
    byte bR = FALSE, bRA = 1, bRB = 1, bChap = GCOFF, bChbp = GCON, bChcp = GCOFF, bV = 10;
    byte bW1, bW2, bM, bA, bB, bC, bD, bVp, bRAp, bRBp, bCha, bChb, bChc, bL = 0;
    // Regular buttons, radio buttons, and data field names
    unsigned char *paB[3] = { "[ Ok ]", "[Cancel]" },
                  *prA[4] = { "One", "Two", "Three" },
                  *prB[4] = { "Choice A", "Choice B", "Choice C" },
                  *paD[5] = { "Numer", "Alpha", "AlNum", "Any.." };
    // Input strings & navigation strings
    unsigned char cA[41], cB[41], cC[41], cD[41],
                  cF[15], cI[15], cR[15], cX[15],
                  cT[15];

    // Define navigation strings
    sprintf(cF, "Nav:%c%c%c%c%c%c%c   ", CHUP, CHDN, CHLFT, CHRGT, CHTAB, CHESC, CHBTRGT);
    sprintf(cI, "Nav:%c%c%c%c^cS^cE", CHLFT, CHRGT, CHESC, CHBTRGT);
    sprintf(cR, "Nav:%c%c%c%c%c%c %c  ", CHUP, CHDN, CHLFT, CHRGT, CHTAB, CHESC, CHBTRGT);
    sprintf(cX, "Nav:X %c%c%c     ", CHTAB, CHESC, CHBTRGT);

    // Define input string defaults
    strcpy(cA,  "-100.00                                 ");
    strcpy(cB,  "This string has something to edit in it!");
    strcpy(cC,  "                                        ");
    sprintf(cD, "%cAny character string!%c                 ", CHBALL, CHBALL);

    // Set radio button and spinner previous selection defaults
    bRAp = bRA;
    bRBp = bRB;
    bVp = bV;

    // Reset clock
    OS.rtclok[1] = 0;
    OS.rtclok[2] = 0;

    // Open window & draw form
    bW1 = WOpen(2, 4, 36, 18, WOFF);
    WOrn(bW1, WPTOP, WPLFT, "Input Form");
    WOrn(bW1, WPTOP, WPRGT, "Edit");
    WOrn(bW1, WPBOT, WPLFT, cF);

    WPrint(bW1, 1, 1, WOFF, "Data Fields");
    WPrint(bW1, 2, 2, WOFF, "Numer:");
    WPrint(bW1, 2, 3, WOFF, "Alpha:");
    WPrint(bW1, 2, 4, WOFF, "AlNum:");
    WPrint(bW1, 2, 5, WOFF, "Any..:");
    WPrint(bW1, 2, 6, WOFF, "Spin.:");
    GSpin(bW1, 8, 6, 0, 100, bVp, GDISP);

    WPrint(bW1, 1, 8, WOFF, "Radio Buttons (h)");
    GRadio(bW1, 2, 9, GHORZ, GDISP, bRAp, 3, prA);

    WPrint(bW1, 1, 11, WOFF, "Radio Buttons (v)");
    GRadio(bW1, 2, 12, GVERT, GDISP, bRBp, 3, prB);

    WPrint(bW1, 20, 11, WOFF, "Check Boxes");
    WPrint(bW1, 25, 12, WOFF, "Milk");
    WPrint(bW1, 25, 13, WOFF, "Bread");
    WPrint(bW1, 25, 14, WOFF, "Butter");
    GCheck(bW1, 21, 12, GDISP, bChap);
    GCheck(bW1, 21, 13, GDISP, bChbp);
    GCheck(bW1, 21, 14, GDISP, bChcp);

    GButton(bW1, 21, 16, GDISP, 2, paB);

    // Display fields as is
    WPrint(bW1, 8, 2, WOFF, cA);
    WPrint(bW1, 8, 3, WOFF, cB);
    WPrint(bW1, 8, 4, WOFF, cC);
    WPrint(bW1, 8, 5, WOFF, cD);

    // ----- Performance Test Display Begin -----
    // Open progress bar window
    bW2 = WOpen(7, 10, 24, 4, WOFF);
    WPrint(bW2, 2, 1, WOFF, "Timing:");

    // Display initial progress bar
    GProg(bW2, 2, 2, 0);

    // Cycle border through 100 colors
    for (bL = 0; bL < 100; bL++) {
        // Change color and update progress bar
        OS.color4 = bL;
        GProg(bW2, 2, 2, bL);
    }

    // Reset border color
    OS.color4 = 0;

    // Close progress bar window
    WClose(bW2);

    // Display time it took to draw screen
    sprintf(cT, "Jiffies: %5d", OS.rtclok[2] + OS.rtclok[1] * 256);
    GAlert(cT);
    // ----- Performance Test Display End -----

    // Loop until form accepted
    do {
        // ----- Display Input Fields -----
        // Show navigation info
        WOrn(bW1, WPBOT, WPLFT, cI);

        // Edit fields
        bA = GInput(bW1, 8, 2, GNUMER, 27, cA);
        bB = GInput(bW1, 8, 3, GALPHA, 27, cB);
        bC = GInput(bW1, 8, 4, GALNUM, 27, cC);
        bD = GInput(bW1, 8, 5, GANY, 27, cD);

        // ----- Spinner Input -----
        bV = GSpin(bW1, 8, 6, 0, 100, bVp, GEDIT);
        if (bV != XESC) {
            bVp = bV;
        }

        // ----- Display Radio Buttons - horizontal -----
        // Show navigation info
        WOrn(bW1, WPBOT, WPLFT, cR);

        // Process buttons
        bRA = GRadio(bW1, 2, 9, GHORZ, GEDIT, bRAp, 3, prA);

        // If not bypass, set previous selected value
        if (bRA != XESC) {
            bRAp = bRA;
        }

        // Redisplay buttons
        GRadio(bW1, 2, 9, GHORZ, GDISP, bRAp, 3, prA);

        // ----- Display Radio Buttons - vertical -----
        bRB = GRadio(bW1, 2, 12, GVERT, GEDIT, bRBp, 3, prB);

        // If not bypass, set previous selected value
        if (bRB != XESC) {
            bRBp = bRB;
        }

        // Redisplay buttons
        GRadio(bW1, 2, 12, GVERT, GDISP, bRBp, 3, prB);

        // ----- Display Check Boxes -----
        // Set footer
        WOrn(bW1, WPBOT, WPLFT, cX);

        // Display checkbox and get choice
        bCha = GCheck(bW1, 21, 12, GEDIT, bChap);

        // If not ESC, set previous value
        if (bCha != XESC) {
            bChap = bCha;
        }

        GCheck(bW1, 21, 12, GDISP, bChap);

        // Display checkbox and get choice
        bChb = GCheck(bW1, 21, 13, GEDIT, bChbp);

        // If not ESC or TAB, set previous value
        if (bChb != XESC) {
            bChbp = bChb;
        }

        // Display checkbox and get choice
        bChc = GCheck(bW1, 21, 14, GEDIT, bChcp);

        // If not ESC or TAB, set previous value
        if (bChc != XESC) {
            bChcp = bChc;
        }

        // Set footer
        WOrn(bW1, WPBOT, WPLFT, cF);

        // Prompt to accept form and redisplay buttons
        bM = GButton(bW1, 21, 16, GEDIT, 2, paB);
        GButton(bW1, 21, 16, GDISP, 2, paB);
    } while (bM == XTAB);

    // Check for acceptance (OK button), and set exit flag
    if (bM == 1) {
        bR = TRUE;
        GAlert("Doing something with entered data...");
    }

    // Close window
    WClose(bW1);

    return(bR);
}
#pragma static-locals(pop)


// ------------------------------------------------------------
// Func...: void ProgTest(void)
// Desc...: Demos window status and progress bar.
// ------------------------------------------------------------
void ProgTest(void)
{
    byte bW1, bW2, bL, bS;
    unsigned int iV;

    // Open status window
    bW1 = WOpen(9, 2, 20, 14, WOFF);
    WOrn(bW1, WPTOP, WPLFT, "Status");
    WPrint(bW1, 1, 1, WOFF, "Window Status");
    WPrint(bW1, 1, 2, WOFF, "------ ------");

    // Open progress bar window
    bW2 = WOpen(7, 18, 24, 4, WOFF);
    WPrint(bW2, 2, 1, WOFF, "Progress:");

    // Display initial progress bar
    GProg(bW2, 2, 2, 0);

    // Loop through each window handle
    for (bL=0; bL < 10; bL+=1) {
        // Get the window status
        bS = WStat(bL);

        // Print the window handle #
        WPos(bW1, 6, 3+bL);
        WPut(bW1, bL+48);

        // Print the window handle status
        WPrint(bW1, 8, 3+bL, WOFF, (bS == WON ? "Used" : "Free"));

        // Update progress bar
        iV = ((bL + 1) % 10) * 10;
        if (iV == 0) {
            iV = 100;
        }
        GProg(bW2, 2, 2, (byte) iV);

        // Wait 1 second
        sleep(1);
    }

    GAlert(" Press a key to continue. ");

    // Close windows
    WClose(bW2);
    WClose(bW1);

    return;
}


// ------------------------------------------------------------
// Func...: void About(void)
// Desc...: About Dialog
// ------------------------------------------------------------
void About(void)
{
    byte bW1;

    // Show window
    bW1 = WOpen(1, 6, 38, 14, WOFF);
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
// Func...: void SubMenu(void)
// Desc...: Sub menu routine
// ------------------------------------------------------------
void SubMenu(void)
{
    byte bW1, bC = 1;
    byte bD = FALSE;
    unsigned char *pcM[4] = { " Sub-Item 1 ", " Sub-Item 2 ", " Sub-Item 3 " };

    // Open window
    bW1 = WOpen(16, 10, 14, 5, WOFF);
    WOrn(bW1, WPTOP, WPLFT, "Sub-Menu");

    // Loop until exit
    while (! bD) {
        // Display menu and get choice
        bC = MenuV(bW1, 1, 1, WOFF, bC, 3, pcM);

        // Process choice
        switch (bC)
        {
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
    byte bW1, bW2, bC = 1;
    byte bD = FALSE;
    unsigned char *pcM[6] =
      { " Input Form   ", " Progress Bar ", " Sub-Menu     ", " About        ", " Exit         " };

    // Setup screen
    WInit();
    WBack(14);

    // Open header window
    bW1 = WOpen(0, 0, 40, 3, WON);
    WPrint(bW1, WPCNT, 1, WOFF, "D E M O N S T R A T I O N");

    // Open menu window
    bW2 = WOpen(12, 7, 16, 9, WOFF);
    WOrn(bW2, WPTOP, WPCNT, "Menu");

    // Loop until done (Exit selected)
    while (! bD) {
        // Call menu
        bC = MenuV(bW2, 1, 2, WON, bC, 5, pcM);

        // Process choice
        switch (bC) {
            case 1: FormInput();
                    break;

            case 2: ProgTest();
                    break;

            case 3: SubMenu();
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
