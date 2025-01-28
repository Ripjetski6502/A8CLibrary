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
//          2025.01-Added GCYES/GCNO
//                 -Added Character Control Key ATASCII codes
//                 -Added GAlertM types
//                 -Added many XL/XE memory locaation codes
// --------------------------------------------------

#ifndef A8DEFINES_H
#define A8DEFINES_H

// Version
#define LIB_VERSION "1.5.0"

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
#define GDISP   0
#define GEDIT   1
#define GHORZ   1
#define GVERT   2
#define GCON    1
#define GCOFF   2
#define GANY    0
#define GALNUM  1
#define GALPHA  2
#define GNUMER  3
#define GUPPER  4
#define GLOWER  5
#define GFNAME  6
#define GCYES   1
#define GCNO    2
#define GAALERT 0
#define GAINFO  1
#define GAWARN  2
#define GAERR   3

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
#define KNOMAP    199
#define KNONE     255
#define KENTER    12
#define KDEL      52
#define KINS      183
#define KCLEAR    118
#define KPLUS     6
#define KASTER    7
#define KMINUS    14
#define KEQUAL    15
#define KESC      28
#define KSPACE    33
#define KINV      39
#define KTAB      44
#define KCAP      60
#define KLEFT     134
#define KRIGHT    135
#define KUP       142
#define KDOWN     143
#define KEYA      63
#define KEYB      21
#define KEYC      18
#define KEYD      58
#define KEYE      42
#define KEYF      56
#define KEYG      61
#define KEYH      57
#define KEYI      13
#define KEYJ      1
#define KEYK      5
#define KEYL      0
#define KEYM      37
#define KEYN      35
#define KEYO      8
#define KEYP      10
#define KEYQ      47
#define KEYR      40
#define KEYS      62
#define KEYT      45
#define KEYU      11
#define KEYV      16
#define KEYW      46
#define KEYX      22
#define KEYY      43
#define KEYZ      23
#define KEY0      50
#define KEY1      31
#define KEY2      30
#define KEY3      26
#define KEY4      24
#define KEY5      29
#define KEY6      27
#define KEY7      51
#define KEY8      53
#define KEY9      48

// Keystroke Shift combinations
#define KENTER_S  76
#define KESC_S    92
#define KDEL_S    116
#define KINS_S    119
#define KTAB_S    108
#define KEYA_S    127
#define KEYB_S    85
#define KEYC_S    82
#define KEYD_S    122
#define KEYE_S    106
#define KEYF_S    120
#define KEYG_S    125
#define KEYH_S    121
#define KEYI_S    77
#define KEYJ_S    65
#define KEYK_S    69
#define KEYL_S    64
#define KEYM_S    101
#define KEYN_S    99
#define KEYO_S    72
#define KEYP_S    74
#define KEYQ_S    111
#define KEYR_S    104
#define KEYS_S    126
#define KEYT_S    109
#define KEYU_S    75
#define KEYV_S    80
#define KEYW_S    110
#define KEYX_S    86
#define KEYY_S    107
#define KEYZ_S    87
#define KEY0_S    114
#define KEY1_S    95
#define KEY2_S    117
#define KEY3_S    90
#define KEY4_S    88
#define KEY5_S    93
#define KEY6_S    71
#define KEY7_S    91
#define KEY8_S    7
#define KEY9_S    112

// Keystroke Control combinations
#define KENTER_C  140
#define KESC_C    156
#define KDEL_C    180
#define KTAB_C    172
#define KEYA_C    191
#define KEYB_C    149
#define KEYC_C    146
#define KEYD_C    186
#define KEYE_C    170
#define KEYF_C    184
#define KEYG_C    189
#define KEYH_C    185
#define KEYI_C    141
#define KEYJ_C    129
#define KEYK_C    133
#define KEYL_C    128
#define KEYM_C    165
#define KEYN_C    163
#define KEYO_C    136
#define KEYP_C    138
#define KEYQ_C    175
#define KEYR_C    168
#define KEYS_C    190
#define KEYT_C    173
#define KEYU_C    139
#define KEYV_C    144
#define KEYW_C    174
#define KEYX_C    150
#define KEYY_C    171
#define KEYZ_C    151
#define KEY0_C    178
// #define KEY1_C    - HARDWARE INTERRUPT
#define KEY2_C    158
#define KEY3_C    154
#define KEY4_C    152
#define KEY5_C    157
#define KEY6_C    155
#define KEY7_C    179
#define KEY8_C    181
#define KEY9_C    176

// Keystroke Control-Shift combinations
#define KENTER_CS 204
#define KESC_CS   220
#define KDEL_CS   244
#define KTAB_CS   236
#define KMINUS_CS 206
#define KPIPE_CS  207
#define KSLASH_CS 230
#define KQUOTE_CS 222
#define KEYD_CS   250
#define KEYE_CS   234
#define KEYF_CS   248
#define KEYG_CS   253
#define KEYH_CS   249
#define KEYI_CS   205
#define KEYM_CS   229
#define KEYN_CS   227
#define KEYO_CS   200
#define KEYP_CS   202
#define KEYQ_CS   239
#define KEYR_CS   232
#define KEYS_CS   254
#define KEYT_CS   237
#define KEYU_CS   203
#define KEYY_CS   235
#define KEY0_CS   242
#define KEY1_CS   223
#define KEY2_CS   222
#define KEY3_CS   218
#define KEY4_CS   216
#define KEY5_CS   221
#define KEY6_CS   219
#define KEY7_CS   243
#define KEY8_CS   245
#define KEY9_CS   240

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

// Character Control Codes (by key)
#define CHA_C     1
#define CHB_C     2
#define CHC_C     3
#define CHD_C     4
#define CHE_C     5
#define CHF_C     6
#define CHG_C     7
#define CHH_C     8
#define CHI_C     9
#define CHJ_C    10
#define CHK_C    11
#define CHL_C    12
#define CHM_C    13
#define CHN_C    14
#define CHO_C    15
#define CHP_C    16
#define CHQ_C    17
#define CHR_C    18
#define CHS_C    19
#define CHT_C    20
#define CHU_C    21
#define CHV_C    22
#define CHW_C    23
#define CHX_C    24
#define CHY_C    25
#define CHZ_C    26
#define CHCOM_C   0
#define CHDOT_C  96
#define CHSEM_C 123

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
#define CLRTXT 709
#define CLRBKG 710
#define KRPDEL 729
#define KEYREP 730
#define NOCLIK 731
#define HELPFG 732
#define ACURIN 752
#define KEYPCH 764
#define AUDF1  53760U
#define AUDC1  53761U
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
