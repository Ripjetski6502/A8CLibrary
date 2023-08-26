// --------------------------------------------------
// Library: a8deffujib64.h
// Desc...: Atari 8 Bit Library FujiNet Base64 definitions
// Author.: Wade Ripkowski
// Date...: 2023.08
// License: GNU General Public License v3.0
// Note...:
// Revised:
// --------------------------------------------------

#ifndef A8DEFFUJIB64_H
#define A8DEFFUJIB64_H

// --------------------------------------------------
// Definitions
// --------------------------------------------------

// FujiNet Commands - Device $70 (raw)
// Base 64
#define FNRB64ENCINP 0xD0
#define FNRB64ENCCMP 0xCF
#define FNRB64ENCLEN 0xCE
#define FNRB64ENCOUT 0xCD
#define FNRB64DECINP 0xCC
#define FNRB64DECCMP 0xCB
#define FNRB64DECLEN 0xCA
#define FNRB64DECOUT 0xC9


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
unsigned char FNB64Inp(char cT, char *cB, unsigned short iS);
unsigned char FNB64Cmp(char cT);
unsigned char FNB64Len(char cT, unsigned long *iS);
unsigned char FNB64Out(char cT, char *cB, unsigned short iS);

#endif
