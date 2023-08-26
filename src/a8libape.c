// --------------------------------------------------
// Library: a8libape.c
// Desc...: Atari 8 Bit ApeTime Library
// Author.: Wade Ripkowski
// Date...: 2023.02
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.h, a8defape.h, a8libsio.c
//          Also FujiNet, SIO2PC, or other APETIME provider.
// Revised:
// --------------------------------------------------

#include <atari.h>
#include "a8defines.h"
#include "a8defape.h"


// -----------------------------------
// Proc..: void ApeTimeG(char *cB)
// Desc..: Get date/time via APETIME protocol
// Return: 6 bytes DMYHMS into cB
// -----------------------------------
void ApeTimeG(char *cB)
{
    // Setup DCB
    // APETime=Device 69 ($45), Unit 1
    // Time command=147 ($93)
    // Get 6 bytes, timeout just over 15s
    OS.dcb.ddevic = APEDEVID;
    OS.dcb.dunit  = 1;
    OS.dcb.dcomnd = APEGTIME;
    OS.dcb.dstats = DCBREAD;
    OS.dcb.dbuf   = cB;
    OS.dcb.dbyt   = 6;
    OS.dcb.daux   = 0;
    OS.dcb.dtimlo = 15;
//    OS.dcb.dunuse = 0;

    // Call SIO
    SIOV();
}
