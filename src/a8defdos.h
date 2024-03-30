// --------------------------------------------------
// Library: a8defdos.h
// Desc...: Atari 8 Bit Library SpartaDOS definitions
// Author.: Wade Ripkowski
// Date...: 2024.03
// License: GNU General Public License v3.0
// Note...:
// Revised:
// --------------------------------------------------

#ifndef A8DEFDOS_H
#define A8DEFDOS_H

// --------------------------------------------------
// Definitions
// --------------------------------------------------

// Locations
#define DOSID *((word *) 0x0F31)

// Date/Time function buffer elements
#define ASD_DT_DY  0
#define ASD_DT_MO  1
#define ASD_DT_YR  2
#define ASD_DT_HR  3
#define ASD_DT_MN  4
#define ASD_DT_SC  5


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
unsigned char IsSD(void);
void SDGDate(unsigned char *bD);

#endif
