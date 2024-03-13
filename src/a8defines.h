// --------------------------------------------------
// Library: a8defines.h
// Desc...: Atari 8 Bit Library Definitions
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defwin.c
//          -Converted from Action!
// Revised: 2023.08-Added SIO and FujiNet
//          2024.02-Added GUPPER
//          2024.02-Added GFNAME
// --------------------------------------------------

#ifndef A8DEFINES_H
#define A8DEFINES_H

// Version
#define LIB_VERSION "1.4.5"

// True & False
#ifndef TRUE
#define TRUE 0x01
#endif
#ifndef FALSE
#define FALSE 0x00
#endif

// Type shortcuts
typedef unsigned char byte;	    //  8 bits / 1 BYTE
typedef unsigned int word;		// 16 bits / 2 BYTEs

// Window Record and Memory Alloc
#define WRECSZ 10
#define WBUFSZ 2068

// Window flags
#define WON  1
#define WOFF 0

// Window Positioning
#define WPABS 128
#define WPTOP 241
#define WPBOT 242
#define WPLFT 251
#define WPRGT 252
#define WPCNT 255

// Window Error status
#define WENONE 100
#define WENOPN 101
#define WEUSED 102

// Gadget flags
#define GDISP  0
#define GEDIT  1
#define GHORZ  1
#define GVERT  2
#define GCON   1
#define GCOFF  2
#define GANY   0
#define GALNUM 1
#define GALPHA 2
#define GNUMER 3
#define GUPPER 4
#define GLOWER 5
#define GFNAME 6

// Menu Exits
#define XESC  253
#define XTAB  254
#define XNONE 255

// Colors
#define CBLACK  0
#define CWHITE  14
#define CRED    50
#define CBLUE   146
#define CGREEN  210
#define CYELLOW 222

// Keystroke Values
#define KNOMAP 199
#define KNONE  255
#define KENTER 12
#define KDEL   52
#define KDEL_S 116
#define KDEL_C 180
#define KINS   183
#define KPLUS  6
#define KASTER 7
#define KMINUS 14
#define KEQUAL 15
#define KESC   28
#define KSPACE 33
#define KINV   39
#define KTAB   44
#define KTAB_S 108
#define KCAP   60
#define KLEFT  134
#define KRIGHT 135
#define KUP    142
#define KDOWN  143
#define KEYA   63
#define KEYB   21
#define KEYC   18
#define KEYD   58
#define KEYE   42
#define KEYF   56
#define KEYG   61
#define KEYH   57
#define KEYI   13
#define KEYJ   1
#define KEYK   5
#define KEYL   0
#define KEYM   37
#define KEYN   35
#define KEYO   8
#define KEYP   10
#define KEYQ   47
#define KEYR   40
#define KEYS   62
#define KEYT   45
#define KEYU   11
#define KEYV   16
#define KEYW   46
#define KEYX   22
#define KEYY   43
#define KEYZ   23

#define KB_C   149
#define KE_C   170
#define KX     22
#define KX_S   86
#define KE_CS  234
#define KS_CS  254

// Console key value
//#define CSTART 6
#define KCNON  7
#define KCSTA  262
#define KCSEL  261
#define KCOPT  259

// Function Key Values
#define KFHLP 17
#define KF1   3
#define KF2   4
#define KF3   19
#define KF4   20

// Character Codes
#define CHSDRGT 1
#define CHBTRGT 3
#define CHSDLFT 4
#define CHTPRGT 5
#define CHTPLFT 17
#define CHBTLFT 26
#define CHHBAR  18
#define CHVBAR  124
#define CHBRUP  24
#define CHBRDN  23
#define CHBALL  20
#define CHESC   27
#define CHUP    28
#define CHDN    29
#define CHLFT   30
#define CHRGT   31
#define CHSPACE 32
#define CHDMND  96
#define CHCLS   125
#define CHBACK  126
#define CHTAB   127
#define CHENT   155
#define CHDELLN 156
#define CHINVSP 160
#define CHBUZ   253
#define CHRGT_I 159
#define CHO_L   111
#define CHI_I   201

// DCB (Device Control Block) modes
#define DCBNONE  0x00
#define DCBREAD  0x40
#define DCBWRITE 0x80
#define DCBRW    0xC0

// ----- OS Registers for PEEK (lib dependencies) -----
#define ALMARG 82
#define RSCRN  88
#define INVFLG 694
#define SHFLOK 702
#define HELPFG 732
#define ACURIN 752
#define KEYPCH 764
#define CONSOL 53279U

// ----- OS Registers -----
#define APPMHI *((word *) 0x000E)
#define RTCLOK *((byte *) 0x0012)
#define RTC2   *((byte *) 0x0013)
#define RTC3   *((byte *) 0x0014)
#define ATRACT *((byte *) 0x004D)
#define SAVMSC *((word *) 0x0058)
#define RAMTOP *((byte *) 0x006A)
#define FR0    *((word *) 0x00D4)
#define SDMCTL *((byte *) 0x022F)
#define SDLSTL *((word *) 0x0230)
#define GPRIOR *((byte *) 0x026F)
#define STICK0 *((byte *) 0x0278)
#define STRIG0 *((byte *) 0x0284)
#define COLOR0 *((byte *) 0x02C4)
#define COLOR1 *((byte *) 0x02C5)
#define COLOR2 *((byte *) 0x02C6)
#define COLOR3 *((byte *) 0x02C7)
#define COLBK  *((byte *) 0x02C8)
#define RAMSIZ *((byte *) 0x02E4)
#define MEMTOP *((byte *) 0x02E5)
#define CHBAS  *((word *) 0x02F4)
#define HPOSP0 *((byte *) 0xD000)
#define HPOSP1 *((byte *) 0xD001)
#define HPOSP2 *((byte *) 0xD002)
#define HPOSP3 *((byte *) 0xD003)
#define HPOSM0 *((byte *) 0xD004)
#define HPOSM1 *((byte *) 0xD005)
#define HPOSM2 *((byte *) 0xD006)
#define HPOSM3 *((byte *) 0xD007)
#define SIZEP0 *((byte *) 0xD008)
#define SIZEP1 *((byte *) 0xD009)
#define SIZEP2 *((byte *) 0xD00A)
#define SIZEP3 *((byte *) 0xD00B)
#define SIZEM  *((byte *) 0xD00C)
#define GRAFP0 *((byte *) 0xD00D)
#define GRAFP1 *((byte *) 0xD00E)
#define GRAFP2 *((byte *) 0xD00F)
#define GRAFP3 *((byte *) 0xD010)
#define GRAFM  *((byte *) 0xD011)
#define PCOLR0 *((byte *) 0xD012)
#define PCOLR1 *((byte *) 0xD013)
#define PCOLR2 *((byte *) 0xD014)
#define PCOLR3 *((byte *) 0xD015)
#define GRACTL *((byte *) 0xD01D)
#define HITCLR *((byte *) 0xD01E)
#define RANDOM *((byte *) 0xD20A)
#define DMACTL *((byte *) 0xD400)
#define DLISTL *((word *) 0xD402)
#define PMBASE *((word *) 0xD407)
#define WSYNC  *((byte *) 0xD40A)
#define VCOUNT *((byte *) 0xD40B)
#define NMIEN  *((byte *) 0xD40E)

#endif
