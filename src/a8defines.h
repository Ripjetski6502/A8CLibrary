// Library: a8defines.h
// Desc...: Atari 8 Bit Library Definitions
// Author.: Wade Ripkowski
// Date...: 2022.08
// License: GNU General Public License v3.0
// Note...: Requires: a8defwin.c
//          -Converted from Action!
// Revised:

#ifndef A8DEFINES_H
#define A8DEFINES_H

// Version
#define LIB_VERSION "1.0.0"

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

// Menu Exits
#define XESC  253
#define XTAB  254
#define XNONE 255

// OS Registers
#define DMACTL 559
#define COLDST 580
#define GPRIOR 623
#define INVFLG 694
#define SHFLOK 702
#define HELPFG 732
#define KEYPCH 764
#define GRACTL 53277U
#define CONSOL 53279U
#define PMBASE 54279U

// PM Registers
#define HPOSP0 53248U
#define HPOSP1 53249U
#define HPOSP2 53250U

// Screen Bits
#define ALMARG 82
#define RSCRN  88
#define PCOLR0 704
#define PCOLR1 705
#define PCOLR2 706
#define PCOLR3 707
#define AFOREG 709
#define ABACKG 710
#define ABORDR 712
#define ACURIN 752

// Colors
#define CBLACK  0
#define CWHITE  14
#define CGREEN  210
#define CBLUE   146
#define CRED    50
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
#define KEYB   21
#define KEYC   18
#define KEYD   58
#define KEYH   57
#define KEYN   35
#define KEYP   10
#define KEYR   40
#define KEYS   62
#define KEYT   45

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
#define CHBTRGT 3
#define CHTPRGT 5
#define CHTPLFT 17
#define CHBTLFT 26
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

#endif
