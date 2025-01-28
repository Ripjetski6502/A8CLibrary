// --------------------------------------------------
// Library: a8libstr.c
// Desc...: Atari 8 Bit String Library
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.c
//          -Converted from Action!
//          -Type byte is synonymous with unsigned char (a8defines.h)
// Require: string.h
// Revised: 2025.01.10-Added StrTrm.
// --------------------------------------------------

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include "a8defines.h"


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
void StrInv(unsigned char *pS, byte bS);
void StrAI(unsigned char *pS, byte bS);
void StrIA(unsigned char *pS, byte bS);
void StrTrm(unsigned char *pS);


// ------------------------------------------------------------
// Func...: void StrInv(unsigned char *pS, byte bS)
// Desc...: Inverses chars of a string from start
// Param..: pS = pointer to string to inverse
//          bS = size (number) of chars in string to inverse
// ------------------------------------------------------------
void StrInv(unsigned char *pS, byte bS)
{
    byte bL;

    // Loop through number of requested chars
    for (bL=0; bL < bS; bL++) {
        // Dereference, change char value by 128, increment pointer
        *(pS++) ^= 128;
    }
}


// ------------------------------------------------------------
// Func...: void StrAI(unsigned char *pS, byte bS)
// Desc...: Converts string from ATASCII code to internal code
// Param..: pS = pointer to string to convert
//          bS = size (number) of chars in string to convert
// Notes..: Manual iteration so we can process space which has
//          0 as internal code (c string terminator).
// ------------------------------------------------------------
void StrAI(unsigned char *pS, byte bS)
{
    byte bL;

    // Process each element
    for (bL=0; bL < bS; bL++) {
        if (*(pS) < 128) {
            if (*(pS) < 32) {
                *(pS) += 64;
            }
            else if (*(pS) < 96) {
                *(pS) -= 32;
            }
        }
        else {
            if (*(pS) < 160) {
                *(pS) += 64;
            }
            else if (*(pS) < 224) {
                *(pS) -= 32;
            }
        }

        // Increment pointer to next char
        *pS++;
    }
}


// ------------------------------------------------------------
// Func...: void StrIA(unsigned char *pS, byte bS)
// Desc...: Converts string from internal code to ATASCII code
// Param..: pS = pointer to string to convert
//          bS = size (number) of chars in string to convert
// Notes..: Manual iteration so we can process space which has
//          0 as internal code (c string terminator).
// ------------------------------------------------------------
void StrIA(unsigned char *pS, byte bS)
{
    byte bL;

    // Process each element
    for (bL=0; bL < bS; bL++) {
        if (*(pS) < 64) {
            *(pS) += 32;
        }
        else if (*(pS) <= 96) {
            *(pS) -= 64;
        }
        else if ((*(pS) >= 128) && (*(pS) <= 154)) {
            *(pS) += 32;
        }
        else if ((*(pS) >= 160) && (*(pS) <= 191)) {
            *(pS) += 32;
        }
        else if ((*(pS) >= 192) && (*(pS) <= 223)) {
            *(pS) -= 64;
        }

        // Incement pointer to next char
        *pS++;
    }
}


// ------------------------------------------------------------
// Func...: void StrTrm(unsigned char *pS)
// Desc...: Trims trailing space from string.
// Param..: pS = pointer to string to inverse
// ------------------------------------------------------------
void StrTrm(unsigned char *pS)
{
    byte bL;

    // Get string length
    bL = strlen(pS) - 1;

    // Remove trailing whitespace
    while ((bL >= 0) && (pS[bL] == CHSPACE)) {
        pS[bL] = '\0';
        bL--;
    }
}
