// --------------------------------------------------
// Library: a8libdos.c
// Desc...: Atari 8 Bit SpartaDOS Library
// Author.: Wade Ripkowski
// Date...: 2024.03
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.c
// Revised:
// --------------------------------------------------

// --------------------------------------------------
// Includes
// --------------------------------------------------
#include <peekpoke.h>
#include "a8defines.h"
#include "a8defdos.h"


// ------------------------------------------------------------
// Func...: byte IsSD(void)
// Desc...: Determines if SpartaDOS is present
// Returns: TRUE or FALSE
// ------------------------------------------------------------
byte IsSD(void)
{
    byte bR = FALSE;
    byte bP = DOSID;

    // Check DOSID for one of 4 bytes indicating SpartaDOS
    if ((bP == 0) || (bP == 15) || (bP == 68) || (bP ==89)) {
        bR = TRUE;
    }

    return (bR);
}


// ------------------------------------------------------------
// Func...: void SDGDate(unsigned char *bD)
// Desc...: Gets date and time from SpartaDOS
// Returns: void
// Notes..: SpartaDOS 3.4+.
// ------------------------------------------------------------
void SDGDate(unsigned char *bD)
{
    unsigned int iV = 0;

    // Get COMTAB vector
    iV = PEEKW(0x0A);

    // Get date from COMTAB
    bD[ASD_DT_YR] = PEEK(iV + 15);
    bD[ASD_DT_MO] = PEEK(iV + 14);
    bD[ASD_DT_DY] = PEEK(iV + 13);

    // Get time from COMTAB
    bD[ASD_DT_HR] = PEEK(iV + 16);
    bD[ASD_DT_MN] = PEEK(iV + 17);
    bD[ASD_DT_SC] = PEEK(iV + 18);
}
