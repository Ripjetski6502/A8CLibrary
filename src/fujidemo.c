// ------------------------------------------------------------
// Program: fujidemo.c
// Desc...: A8 FujiNet Binding Demo Application
// Author.: Wade Ripkowski
// Date...: 20230825
// License: GNU General Public License v3.0
// Notes..: cl65 -v [-O] -t atari fujidemo.c -o fujidemo.com
// ------------------------------------------------------------

// Pull in include files
#include <stdio.h>
#include <conio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <atari.h>

#include "a8defines.h"
#include "a8defwin.h"
#include "a8defsio.h"
#include "a8libmisc.c"
#include "a8libstr.c"
#include "a8libwin.c"
#include "a8libgadg.c"
#include "a8libmenu.c"
#include "a8libfuji.c"
#include "a8libfujib64.c"
#include "a8libfujihash.c"


// Prototypes
void About(void);
void TestCfg(void);
void TestCon(void);
void TestB64(void);
void TestHash(void);


// Globals
static unsigned char cU[256] = "N:HTTP://68k.news:80/";


// ------------------------------------------------------------
// Func...: void About(void)
// Desc...: About Dialog
// ------------------------------------------------------------
void About(void)
{
    byte bW;

    // Show window
    bW = WOpen(1, 6, 38, 10, WOFF);
    WOrn(bW, WPTOP, WPLFT, "About");
    WPrint(bW, WPCNT, 1, WOFF, "FujiNet Binding Demo");
    WPrint(bW, WPCNT, 2, WOFF, "Version 1.00");
    WPrint(bW, WPCNT, 3, WOFF, "(C) 2023  Wade Ripkowski");
    WPrint(bW, WPCNT, 5, WOFF, "A8 C-Library FujiNet");
    WPrint(bW, WPCNT, 6, WOFF, "binding demonstration.");
    WPrint(bW, WPCNT, 8, WON, " Ok ");

    // Wait for key
    WaitKCX(WOFF);

    // Close window
    WClose(bW);
}


// ------------------------------------------------------------
// Func...: void TestCon(void)
// Desc...: Open, get and Close test.
// ------------------------------------------------------------
void TestCfg(void)
{
    td_fncfg sC;
    unsigned char bS, cL[33];
    byte bW;

    // Clear memory
    memset(cL, 0, 32);

    // Get config into structure
    bS = FNGConfig(&sC);

    // Check status and report
    if (bS != FNSOK) {
        GAlert("Connect: Failed to get config!");
    } else {
        // Open window
        bW = WOpen(3, 5, 34, 17, WOFF);
        WOrn(bW, WPTOP, WPLFT, "Configuration");
        WPrint(bW, 1, 2, WON, "Version");
        WPrint(bW, 1, 5, WON, "Hostname");
        WPrint(bW, 1, 8, WON, "IP");
        WPrint(bW, 1, 11, WON, "SSID");

        // Fill in values from the returned structure
        // Version
        WPrint(bW, 1, 3, WOFF, sC.version);

        // Hostname, copy up to 32 chars for window constraints
        strncpy(cL, sC.hostname, 32);
        WPrint(bW, 1, 6, WOFF, cL);

        // IP address, clear the line buffer and build new string from the bytes
        memset(cL, 0, 32);
        sprintf(cL, "%03d.%03d.%03d.%03d", sC.ip[0], sC.ip[1], sC.ip[2], sC.ip[3]);
        WPrint(bW, 1, 9, WOFF, cL);

        // SSID, clear the line buffer, copy up to 32 chars for window constraint
        memset(cL, 0, 32);
        strncpy(cL, sC.ssid, 32);
        WPrint(bW, 1, 12, WOFF, cL);

        // OK "button"
        WPrint(bW, WPCNT, 14, WON, " Ok ");

        // Wait for key
        WaitKCX(WOFF);

        // Close window
        WClose(bW);
    }

}


// ------------------------------------------------------------
// Func...: void TestCon(void)
// Desc...: Open, get and Close test.
// ------------------------------------------------------------
void TestCon(void)
{
    byte bW;
    unsigned char *cB;
    unsigned char cL[37];
    unsigned char bS = 0, bL = 0;

    // Get some memory and clear it
    cB = malloc(768);
    memset(cB, 0, 767);
    memset(cL, 0, 36);

    // Open window
    bW = WOpen(1, 1, 38, 22, WOFF);
    WOrn(bW, WPTOP, WPLFT, "Connect Demo");
    WPrint(bW, 1, 1, WOFF, "URL:");
    WPrint(bW, 6, 1, WOFF, cU);
    WDiv(bW, 2, WON);
    WPrint(bW, WPCNT, 2, WON, " Page Source ");
    WDiv(bW, 19, WON);
    WPrint(bW, WPCNT, 20, WON, " Ok ");

    // Open connection
    bS = FNOpen(cU);

    // Set translation mode
    FNTrans(FNTRLF, FNAXUPDATE);

    // Check status and report
    if (bS != FNSOK) {
        GAlert("Connect: Failed to open!");
    }

    // Get data
    bS = FNRead(598, cB);

    // Check status and report
    if (bS != FNSOK) {
        GAlert("Connect: Failed to read!");
    }

    // Close connection
    bS = FNClose();

    // Check status and report
    if (bS != FNSOK) {
        GAlert("Connect: Failed to close!");
    }

    // Display data
    for (bL = 0; bL < 16; bL ++) {
        strncpy(cL, cB + (bL * 36), 36);
        WPrint(bW, 1, 3 + bL, WOFF, cL);
    }

    // Wait for key
    WaitKCX(WOFF);

    // Close window
    WClose(bW);

    // Free memory
    free(cB);
}


// ------------------------------------------------------------
// Func...: void TestB64(void)
// Desc...: Base64 test (encodes then decodes).
// ------------------------------------------------------------
void TestB64(void)
{
    unsigned char *cS = "InverseATASCII";
    unsigned long iS;
    unsigned char cB[FNHASHLENHSHA5 + 1], cL[33];
    byte bW;

    // Clear memory
    memset(cB, 0, FNHASHLENHSHA5);
    memset(cL, 0, 32);

    // Open output window
    bW = WOpen(3, 8, 34, 9, WOFF);
    WOrn(bW, WPTOP, WPLFT, "Base64 Demo");
    WPrint(bW, 1, 1, WOFF, "Text:");
    WPrint(bW, 7, 1, WOFF, cS);
    WDiv(bW, 2, WON);
    WPrint(bW, WPCNT, 2, WON, " Encoded ");
    WDiv(bW, 4, WON);
    WPrint(bW, WPCNT, 4, WON, " Decoded ");
    WDiv(bW, 6, WON);
    WPrint(bW, WPCNT, 7, WON, " Ok ");

    // ----- Encode the string -----
    // Push the unencoded string to the FN input buffer
    FNB64Inp(FNLENCODE, cS, strlen(cS));

    // Perform the encode
    FNB64Cmp(FNLENCODE);

    // Get the length of the result
    FNB64Len(FNLENCODE, &iS);

    // Get the encoded string from FN
    FNB64Out(FNLENCODE, cB, iS);

    // Show encoded
    WPrint(bW, 1, 3, WOFF, cB);

    // ----- Decode the string -----
    // Push the encoded string to the FN input buffer
    FNB64Inp(FNLDECODE, cB, iS);

    // Perform the decode
    FNB64Cmp(FNLDECODE);

    // Get the length of the result
    FNB64Len(FNLDECODE, &iS);

    // Clear buffer before getting result
    memset(cB, 0, 128);

    // Get decoded string from FN
    FNB64Out(FNLDECODE, cB, iS);

    // Show decoded
    WPrint(bW, 1, 5, WOFF, cB);

    // Wait for key
    WaitKCX(WOFF);

    // Close window
    WClose(bW);
}


// ------------------------------------------------------------
// Func...: void TestHash(void)
// Desc...: Hash test (SHA1).
// ------------------------------------------------------------
void TestHash(void)
{
    unsigned char *cS = "InverseATASCII";
    unsigned char cB[165], cL[33];
    byte bW;

    // Clear memory
    memset(cB, 0, 164);
    memset(cL, 0, 32);

    // Open output window
    bW = WOpen(3, 4, 34, 16, WOFF);
    WOrn(bW, WPTOP, WPLFT, "Hash Demo");
    WPrint(bW, 1, 1, WOFF, "Text:");
    WPrint(bW, 7, 1, WOFF, cS);
    WDiv(bW, 2, WON);
    WPrint(bW, WPCNT, 2, WON, " SHA1 ");
    WDiv(bW, 5, WON);
    WPrint(bW, WPCNT, 5, WON, " SHA256 ");
    WDiv(bW, 8, WON);
    WPrint(bW, WPCNT, 8, WON, " SHA512 ");
    WDiv(bW, 13, WON);
    WPrint(bW, WPCNT, 14, WON, " Ok ");

    // ----- SHA1 -----
    // Push the string to the FN input buffer
    FNHashInp(cS, strlen(cS));

    // Perform the hash
    FNHashCmp(FNHASHSHA1);

    // Get the hash string from FN as hex
    FNHashOut(FNHASHSHA1, FNHASHOHEX, cB);

    // Show hash across 2 lines
    strncpy(cL, cB, 20);
    WPrint(bW, 1, 3, WOFF, cL);
    strncpy(cL, cB+20, 20);
    WPrint(bW, 1, 4, WOFF, cL);

    // Clear memory
    memset(cB, 0, FNHASHLENHSHA5);

    // ----- SHA256 -----
    // Push the string to the FN input buffer
    FNHashInp(cS, strlen(cS));

    // Perform the hash
    FNHashCmp(FNHASHSHA2);

    // Get the hash string from FN as hex
    FNHashOut(FNHASHSHA2, FNHASHOHEX, cB);

    // Show hash across 2 lines
    strncpy(cL, cB, 32);
    WPrint(bW, 1, 6, WOFF, cL);
    strncpy(cL, cB+32, 32);
    WPrint(bW, 1, 7, WOFF, cL);

    // Clear memory
    memset(cB, 0, FNHASHLENHSHA5);

    // ----- SHA512 -----
    // Push the string to the FN input buffer
    FNHashInp(cS, strlen(cS));

    // Perform the hash
    FNHashCmp(FNHASHSHA5);

    // Get the hash string from FN as hex
    FNHashOut(FNHASHSHA5, FNHASHOHEX, cB);

    // Show hash across 4 lines
    strncpy(cL, cB, 32);
    WPrint(bW, 1, 9, WOFF, cL);
    strncpy(cL, cB+32, 32);
    WPrint(bW, 1, 10, WOFF, cL);
    strncpy(cL, cB+64, 32);
    WPrint(bW, 1, 11, WOFF, cL);
    strncpy(cL, cB+96, 32);
    WPrint(bW, 1, 12, WOFF, cL);

    // Wait for key
    WaitKCX(WOFF);

    // Close window
    WClose(bW);
}


// ------------------------------------------------------------
// Func...: void main(void)
// Desc...: Main routine
// ------------------------------------------------------------
void main(void)
{
    // Variables
    byte bW1, bW2;
    byte bC = 1, bD = FALSE;
    unsigned char *pcM[8] =
      { " Get Config   ", " Wi-Fi Status ", " Connect Demo ", " Base64 Demo  ", " Hash Demo    ", " About        ", " Exit         " };
    unsigned char bS = 0;

    // Setup screen
    WInit();

    // Set Background
    WBack(14);

    // Open header window
    bW1 = WOpen(0, 0, 40, 3, WON);
    WPrint(bW1, WPCNT, 1, WOFF, "FujiNet Binding Demo");

    // Open menu window
    bW2 = WOpen(12, 7, 16, 11, WOFF);
    WOrn(bW2, WPTOP, WPCNT, "Menu");

    // Loop until done (Exit selected)
    while (! bD) {
        // Call menu
        bC = MenuV(bW2, 1, 2, WOFF, bC, 7, pcM);

        // Process choice
        switch (bC) {
            // Get config
            case 1: TestCfg();
                    break;

            // Get device status
            case 2: bS = FNStatus();
                    switch (bS) {
                        case FNDSIDLE: GAlert("FujiNet Idle");
                                       break;
                        case FNDSNOSSID: GAlert("FujiNet No SSID");
                                         break;
                        case FNDSSCANC: GAlert("FujiNet Scan Complete");
                                        break;
                        case FNDSACTIVE: GAlert("FujiNet Active");
                                         break;
                        case FNDSLCFAIL: GAlert("FujiNet Last Connect Failed");
                                         break;
                        case FNDSWIFILOST: GAlert("FujiNet WiFi Connect Lost");
                                           break;
                        case FNDSWIFIDISC: GAlert("FujiNet WiFi Disconnected");
                                           break;
                    }
                    break;

            // Open and close test
            case 3: TestCon();
                    break;

            // Base64 test
            case 4: TestB64();
                    break;

            // Hash test
            case 5: TestHash();
                    break;

            // About box
            case 6: About();
                    break;

            // Exit
            case 7: bD = TRUE;
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

    // Set Background
    WBack(0);

    // Exit
    return;
}
