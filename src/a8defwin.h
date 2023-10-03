// Library: a8defwin.h
// Desc...: Atari 8 Bit Library Global Window definitions
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defines.c
//          -Converted from Action!
//          -Unsigned char is synonymous with byte (from a8defines.h)
// Revised:

#ifndef A8DEFWIN_H
#define A8DEFWIN_H

#define NUM_WIN 11

// Window handle info
typedef struct {
    unsigned char bU,bX,bY,bW,bH,bI;
    unsigned char *cM;
    unsigned int cZ;
} td_wnrec;

td_wnrec baW[NUM_WIN];
//td_wnrec *pWn;


// Window position - virtual cursor
typedef struct {
    unsigned char vX,vY;
} td_wnpos;

td_wnpos vCur;


// Window handle and memory storage
//unsigned char baW[110], baWM[WBUFSZ];
unsigned char baWM[WBUFSZ];
unsigned char *cpWM;

#endif
