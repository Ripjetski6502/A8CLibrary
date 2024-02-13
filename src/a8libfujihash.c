// --------------------------------------------------
// Library: a8libfujihash.c
// Desc...: Atari 8 Bit FujiNet Hash Library
// Author.: Wade Ripkowski
// Date...: 2023.08
// License: GNU General Public License v3.0
// Note...: -Requires: a8deffuji.h, a8defines.h, a8libsio.c
//          -N: does not need to be loaded.
// Revised:
// --------------------------------------------------
// Portions are derivative works based on nio.c as
// found in many of the FujiNet application sources
// with GPL license.
// --------------------------------------------------

#include <atari.h>
#include "a8defines.h"
#include "a8defsio.h"
#include "a8deffuji.h"
#include "a8deffujihash.h"


// -----------------------------------
// Proc..: unsigned char FNHashInp(char *cB, unsigned short iS)
// Desc..: Set Hash Input
// Params: cB = pointer to string to hash
//         iS = # of bytes to hash (size)
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNHashInp(char *cB, unsigned short iS)
{
    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNRHASHINP;
    OS.dcb.dstats = DCBWRITE;
    OS.dcb.dbuf   = cB;
    OS.dcb.dbyt   = iS;
    OS.dcb.daux   = iS;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned char FNHashCmp(byte bT)
// Desc..: Compute Hash on current input buffer
// Params: bT = hash type
//              0 = MD5    (FNHASHMD5)  (not implemented)
//              1 = SHA1   (FNHASHSHA1)
//              2 = SHA256 (FNHASHSHA2)
//              5 = SHA512 (FNHASHSHA5)
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNHashCmp(byte bT)
{
    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNRHASHCMP;
    OS.dcb.dstats = DCBNONE;
    OS.dcb.dbuf   = NULL;
    OS.dcb.dbyt   = 0;
    OS.dcb.daux1  = bT;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned char FNHashOut(byte bT, byte bH, char *cB)
// Desc..: Get Base64 Enc/Dec Output (retrieve)
// Params: bT = hash type (MUST be same as last FNHashCmp call)
//              0 = MD5    (FNHASHMD5)
//              1 = SHA1   (FNHASHSHA1)
//              2 = SHA256 (FNHASHSHA2)
//              5 = SHA512 (FNHASHSHA5)
//         bH = output type
//              0 = binary (FNHASHOBIN)
//              1 = hex    (FNHASHOHEX)
//         cB = pointer to string for hash (must be big enough to hold hash)
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNHashOut(byte bT, byte bH, char *cB)
{
    unsigned short iS = 0;

    // Determine size of hash based on type of hash and desired output
    switch (bT) {
        // For each case, set binary size if binary requested, else set hex size (double)
        case FNHASHSHA1 : iS = (bH == FNHASHOBIN ? FNHASHLENBSHA1 : FNHASHLENHSHA1);
                          break;
        case FNHASHSHA2 : iS = (bH == FNHASHOBIN ? FNHASHLENBSHA2 : FNHASHLENHSHA2);
                          break;
        case FNHASHSHA5 : iS = (bH == FNHASHOBIN ? FNHASHLENBSHA5 : FNHASHLENHSHA5);
                          break;
    }

    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNRHASHOUT;
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = cB;
    OS.dcb.dbyt   = iS;
    OS.dcb.daux1  = bH;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}
