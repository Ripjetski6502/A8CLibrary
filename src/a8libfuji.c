// --------------------------------------------------
// Library: a8libfuji.c
// Desc...: Atari 8 Bit FujiNet Library
// Author.: Wade Ripkowski
// Date...: 2023.02
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
#include "a8deffuji.h"
#include "a8defsio.h"


// -----------------------------------
// Proc..: unsigned char FNStatus(void)
// Desc..: Get FujiNet device wifi status
// Return: 0 = WiFi idle
//         1 = No SSID available
//         2 = Scan completed
//         3 = Connected to network and active
//         4 = Last connect failed
//         5 = WiFi connection lost
//         6 = WiFi explicitly disconnected
// -----------------------------------
unsigned char FNStatus(void)
{
    unsigned char bS = 0;

    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNRWFSTAT;
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = &bS;
    OS.dcb.dbyt   = 1;
    OS.dcb.daux1  = 0;
    OS.dcb.daux2  = 0;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return bS;
}


// -----------------------------------
// Proc..: void FNTrans(unsigned char bM, unsigned char bD)
// Desc..: Sets translation mode for EOL
// Param.: bM = Translation mode
//              FNTRNONE = none
//              FNTRCR   = CR
//              FNTRLF   = LF
//              FNTRCRLF = CRLF
//         bD = Direction of translation
//              FNAXREAD   = Reading
//              FNAXWRITE  = Writing
//              FNAXUPDATE = Reading/Writing
// Return: n/a
// Note..: Must be called AFTER open.
// -----------------------------------
void FNTrans(unsigned char bM, unsigned char bD)
{
    // Setup DCB
    OS.dcb.ddevic = FNDEVID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNCTRAN;
    OS.dcb.dstats = DCBNONE;
    OS.dcb.dbuf   = NULL;
    OS.dcb.dbyt   = 0;
    OS.dcb.daux1  = bD;
    OS.dcb.daux2  = bM;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();
}


// -----------------------------------
// Proc..: unsigned char FNOpen(char *cB)
// Desc..: Open connection to URL
// Params: cB = URL to open (up to 256 bytes)
//              N:TCP://addr:port/
// Notes.: Open with NO translation
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNOpen(char *cB)
{
    // Setup DCB
    OS.dcb.ddevic = FNDEVID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNCOPEN;
    OS.dcb.dstats = DCBWRITE;
    OS.dcb.dbuf   = cB;           // (void *)
    OS.dcb.dbyt   = 256;
    OS.dcb.daux1  = FNAXUPDATE;
    OS.dcb.daux2  = FNTRNONE;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned char FNClose(void)
// Desc..: Closes connection
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNClose(void)
{
    // Setup DCB
    OS.dcb.ddevic = FNDEVID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNCCLOSE;
    OS.dcb.dstats = DCBNONE;
    OS.dcb.dbuf   = NULL;  // 0
    OS.dcb.dbyt   = 0;
    OS.dcb.daux1  = 0;
    OS.dcb.daux2  = 0;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned short FNCheck(void)
// Desc..: Checks for bytes waiting
// DCB returns 4 bytes: 0 = LO byte # bytes waiting
//                      1 = HI byte # bytes waiting
//                      2 = Connection State (0=Disconnected, 1=Connected)
//                      3 = Extended error code
// Return: # of bytes waiting
// -----------------------------------
unsigned short FNCheck(void)
{
    unsigned short iS = 0;
    unsigned char cS[4] = { 0, 0, 0, 0 };

    // Setup DCB
    OS.dcb.ddevic = FNDEVID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNCSTAT;
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = &cS;
    OS.dcb.dbyt   = 4;
    OS.dcb.daux1  = 0;
    OS.dcb.daux2  = 0;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    // If disconnected, return error
    if (cS[2] == 0) {
        iS = FNEDISCO;
    } else {
        // Get bytes waiting
        iS = (cS[1] << 8) + cS[0];
    }

    return iS;
}


// -----------------------------------
// Proc..: unsigned char FNRead(unsigned short iS, unsigned char *cB)
// Desc..: Reads x bytes from device
// Params: iS = # of bytes to read
//         cB = buffer to store read bytes
// DCB setup: dbyt = # of bytes to get
//            aux  = # of bytes to get
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNRead(unsigned short iS, unsigned char *cB)
{
    // Setup DCB
    OS.dcb.ddevic = FNDEVID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNCREAD;
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = cB;
    OS.dcb.dbyt   = iS;
    OS.dcb.daux   = iS;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned char FNWrite(unsigned char *cB)
// Desc..: Write buffer to device
// Params: cB = buffer to write to device
// DCB setup: dbuf = address of buffer
//            dbyt = # of bytes to write
//            aux  = # of bytes to write
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNWrite(unsigned char *cB)
{
    // Setup DCB
    OS.dcb.ddevic = FNDEVID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNCWRITE;
    OS.dcb.dstats = DCBWRITE;
    OS.dcb.dbuf   = cB;
    OS.dcb.dbyt   = strlen(cB);
    OS.dcb.daux   = strlen(cB);
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}


// -----------------------------------
// Proc..: unsigned char FNGConfig(td_fncfg *sC)
// Desc..: Get FujiNet config info
// Params: sC = pointer to FujiNet config structure
// Return: SIO status (FNSOK = Success)
// -----------------------------------
unsigned char FNGConfig(td_fncfg *sC)
{
    // Setup DCB
    OS.dcb.ddevic = FNRAWID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = FNRGCONFIG;
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = sC;
    OS.dcb.dbyt   = FNCONFIGSZ;
    OS.dcb.daux1  = 0;
    OS.dcb.daux2  = 0;
    OS.dcb.dtimlo = 15;

    // Call SIO
    SIOV();

    return OS.dcb.dstats;
}
