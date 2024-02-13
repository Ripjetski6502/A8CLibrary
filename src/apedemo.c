// ------------------------------------------------------------
// Program: apedemo.c
// Desc...: Gets date/time from APE (via FujiNet)
// Author.: Wade Ripkowski
// Date...: 2023.02.09
// Notes..: cl65 -v [-O] -t atari apedemo.c -o apedemo.xex
// ------------------------------------------------------------

// Pull in include files
#include <stdio.h>
#include <atari.h>
#include <conio.h>
#include <unistd.h>

#include "a8defsio.h"
#include "a8libape.c"


// -----------------------------------
// Main Routine
// -----------------------------------
void main(void)
{
    // Storage for 6 bytes preset to 0 : DMYHMS
    byte bDT[6]={ 0, 0, 0, 0, 0, 0 };

    // Call time routine with the storage array
    ApeTimeG(bDT);

    // What time is it?
    printf("\nAPE Time Demonstration\n\n");
    printf("Date: 20%d.%02d.%02d\n", bDT[2], bDT[1], bDT[0]);
    printf("Time: %02d:%02d:%02d\n\n", bDT[3], bDT[4], bDT[5]);

    // Wait for a keystroke
    printf("Press any key to continue...\n");
    while (! kbhit()) {};
}
