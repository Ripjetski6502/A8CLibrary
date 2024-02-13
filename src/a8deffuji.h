// --------------------------------------------------
// Library: a8deffuji.h
// Desc...: Atari 8 Bit Library FujiNet definitions
// Author.: Wade Ripkowski
// Date...: 2023.02
// License: GNU General Public License v3.0
// Note...:
// Revised:
// --------------------------------------------------

#ifndef A8DEFFUJI_H
#define A8DEFFUJI_H

// --------------------------------------------------
// Definitions
// --------------------------------------------------

// FujiNet Devices
#define FNRAWID 0x70
#define FNDEVID 0x71

// FujiNet Commands - Device $70 (raw)
#define FNRWFSTAT  0xFA
#define FNRGCONFIG 0xE8

// FujiNet Commands - Device $71
#define FNCCLOSE 'C'
#define FNCHASH  'H'
#define FNCOPEN  'O'
#define FNCPARSE 'P'
#define FNCQUERY 'Q'
#define FNCREAD  'R'
#define FNCSTAT  'S'
#define FNCTRAN  'T'
#define FNCWRITE 'W'
#define FNCTIMER 'Z'

// FujiNet Commands - TCP
#define FNPACCEPT 'A'
#define FNPCLOSE  'c'
#define FNPUDP    'D'
#define FNPHTTPCH 'M'

// FujiNet Translation Modes
#define FNTRNONE 0
#define FNTRCR   1
#define FNTRLF   2
#define FNTRCRLF 3

// FujiNet Aux Modes
#define FNAXREAD    4
#define FNAXWRITE   8
#define FNAXUPDATE 12

// FujiNet Device WiFi Status
#define FNDSIDLE     0
#define FNDSNOSSID   1
#define FNDSSCANC    2
#define FNDSACTIVE   3
#define FNDSLCFAIL   4
#define FNDSWIFILOST 5
#define FNDSWIFIDISC 6

// FujiNet Function Errors/Status
#define FNSOK     1
#define FNEDISCO -1

// Library Encoding/Decoding parameter support
#define FNLENCODE  'E'
#define FNLDECODE  'D'

// FujiNet Adapter Config structure
#define FNCONFIGSZ 140
typedef struct {
    char ssid[33];
    char hostname[64];
    unsigned char ip[4];
    unsigned char gateway[4];
    unsigned char netmask[4];
    unsigned char dns[4];
    unsigned char mac[6];
    unsigned char bssid[6];
    char version[15];
} td_fncfg;


// --------------------------------------------------
// Function Prototypes
// --------------------------------------------------
unsigned char FNStatus(void);
void FNTrans(unsigned char bM, unsigned char bD);
unsigned char FNOpen(char *cB);
unsigned char FNClose(void);
unsigned short FNCheck(void);
unsigned char FNRead(unsigned short iS, unsigned char *cB);
unsigned char FNWrite(unsigned char *cB);
unsigned char FNGConfig(td_fncfg *sC);

#endif
