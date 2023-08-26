// --------------------------------------------------
// Library: a8deffujihash.h
// Desc...: Atari 8 Bit Library FujiNet Hash definitions
// Author.: Wade Ripkowski
// Date...: 2023.08
// License: GNU General Public License v3.0
// Note...:
// Revised:
// --------------------------------------------------

#ifndef A8DEFFUJIHASH_H
#define A8DEFFUJIHASH_H

// --------------------------------------------------
// Definitions
// --------------------------------------------------

// FujiNet Commands - Device $70 (raw)
// Hash
#define FNRHASHINP 0xC8
#define FNRHASHCMP 0xC7
#define FNRHASHLEN 0xC6   // Implementation removed
#define FNRHASHOUT 0xC5

// Parameter Support
// Hash selection
#define FNHASHMD5  0   // Not implemented
#define FNHASHSHA1 1   // SHA1
#define FNHASHSHA2 2   // SHA256
#define FNHASHSHA5 3   // SHA512
// Output type selection
#define FNHASHOBIN 0
#define FNHASHOHEX 1
// Internal function binary hash sizes
#define FNHASHLENBMD5  16
#define FNHASHLENBSHA1 20
#define FNHASHLENBSHA2 32
#define FNHASHLENBSHA5 64
// Internal function hex hash sizes
#define FNHASHLENHMD5   32
#define FNHASHLENHSHA1  40
#define FNHASHLENHSHA2  64
#define FNHASHLENHSHA5 128


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
unsigned char FNHashInp(char *cB, unsigned short iS);
unsigned char FNHashCmp(byte bT);
unsigned char FNHashOut(byte bT, byte bH, char *cB);

#endif
