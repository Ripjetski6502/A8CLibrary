// --------------------------------------------------
// Library: a8libfujib64.c
// Desc...: Atari 8 Bit FujiNet Base64 Library
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
#include "a8deffujib64.h"


// -----------------------------------
// Proc..: unsigned char FNB64Inp(char cT, char *cB, unsigned short iS)
// Desc..: Set Base64 Enc/Dec Input (set)
// Params: cT = operation type (enc/dec)
//         cB = pointer to string to encode/decode
//         iS = # of bytes to encode/decode (size)
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNB64Inp(char cT, char *cB, unsigned short iS)
{
    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = (cT == FNLENCODE ? FNRB64ENCINP : FNRB64DECINP);
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
// Proc..: unsigned char FNB64Cmp(char cT)
// Desc..: Compute Base64 Enc/Dec on current input buffer
// Params: cT = operation type (enc/dec)
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNB64Cmp(char cT)
{
    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = (cT == FNLENCODE ? FNRB64ENCCMP : FNRB64DECCMP);
    OS.dcb.dstats = DCBNONE;
    OS.dcb.dbuf   = NULL;
    OS.dcb.dbyt   = 0;
    OS.dcb.daux   = 0;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned char FNB64Len(char cT, unsigned long *iS)
// Desc..: Get Base64 Enc/Dec Length (retrieve)
// Params: cT = operation type (enc/dec)
//         iS = pointer to length as 4 bytes (32 bits)
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNB64Len(char cT, unsigned long *iS)
{
    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = (cT == FNLENCODE ? FNRB64ENCLEN : FNRB64DECLEN);
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = iS;
    OS.dcb.dbyt   = 4;   // sizeof(unsigned long)
    OS.dcb.daux   = 0;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned char FNB64Out(char cT, char *cB, unsigned short iS)
// Desc..: Get Base64 Enc/Dec Output (retrieve)
// Params: cT = operation type (enc/dec)
//         cB = pointer to string to encode/decode
//         iS = # of bytes to encode/decode (size)
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNB64Out(char cT, char *cB, unsigned short iS)
{
    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = (cT == FNLENCODE ? FNRB64ENCOUT : FNRB64DECOUT);
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = cB;
    OS.dcb.dbyt   = iS;
    OS.dcb.daux   = iS;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}
