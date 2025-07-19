/*!
 * \file    charlcd_private.h
 * \brief   Character LCD function prototypes and defintions
 * \date    Copyright (c) 1996-2004 ARM Limited. All rights reserved.
 *
 *  Provides definitions for the Character LCD
 */

/*
 * Revision $Revision: 8197 $
 * Checkin $Date: 2006-10-03 13:55:22 +0100 (Tue, 03 Oct 2006) $
 */

#ifndef _CHARLCD_H
#define _CHARLCD_H

#define CHARLCD_COM     0x00
#define CHARLCD_DAT     0x04
#define CHARLCD_RD      0x08
#define CHARLCD_RAW     0x0C
#define CHARLCD_MASK    0x10
#define CHARLCD_STAT    0x14

#define CHARLCD_BASE    0x4000C000

#define CHARLCD_COM_PTR     *((volatile uint32_t *)(CHARLCD_BASE + CHARLCD_COM))
#define CHARLCD_DAT_PTR     *((volatile uint32_t *)(CHARLCD_BASE + CHARLCD_DAT))
#define CHARLCD_RD_PTR      *((volatile uint32_t *)(CHARLCD_BASE + CHARLCD_RD))
#define CHARLCD_RAW_PTR     *((volatile uint32_t *)(CHARLCD_BASE + CHARLCD_RAW))
#define CHARLCD_MASK_PTR    *((volatile uint32_t *)(CHARLCD_BASE + CHARLCD_MASK))
#define CHARLCD_STAT_PTR    *((volatile uint32_t *)(CHARLCD_BASE + CHARLCD_STAT))

#define CHARLCD_RS     (1 << 7)
#define CHARLCD_RnW    (1 << 6)
#define CHARLCD_E      (1 << 5)
#define CHARLCD_D4     (1 << 4)
#define CHARLCD_D5     (1 << 3)
#define CHARLCD_D6     (1 << 2)
#define CHARLCD_D7     (1 << 1)

#define CHARLCD_BUSY_FLAG     0x80

#define CHARLCD_CLR_DISPLAY    1
#define CHARLCD_HOME           2
#define CHARLCD_ENTRY_MODE_SET 4
#define CHARLCD_DISP_CTRL      8
#define CHARLCD_CUR_DIS_SHIFT  16
#define CHARLCD_FUNC_SET       32
#define CHARLCD_CGRAM_ADDR     64
#define CHARLCD_DDRAM_ADDR     128

// Entry mode set functions
#define CHARLCD_INC             2                             
#define CHARLCD_DEC             0
#define CHARLCD_COM_DIS_SHIFT   1

// Display control functions
#define CHARLCD_DISP_ON         4
#define CHARLCD_CURS_ON         2
#define CHARLCD_BLINK_ON        1
#define CHARLCD_DISP_OFF        0
#define CHARLCD_CURS_OFF        0
#define CHARLCD_BLINK_OFF       0

// Cursor or display shift functions
#define CHARLCD_DISP_SHIFT      8
#define CHARLCD_CURS_SHIFT      0
#define CHARLCD_SHIFT_RIGHT     4
#define CHARLCD_SHIFT_LEFT      0

// Function set commands
#define CHARLCD_IF4BIT          0
#define CHARLCD_IF8BIT          0x10
#define CHARLCD_NUMLINES2       8
#define CHARLCD_NUMLINES1       0
#define CHARLCD_FONT5X10        4
#define CHARLCD_FONT5X8         0

#define CHARLCD_CLEAR	   0x01

#define CHARLCD_MAX_CHARS  0x14 //20 dec
#define CHARLCD_CLR_LINE   0x28	//40 dec

#define CHARLCD_SPACE_CHAR 0x20       
#define CHARLCD_PAUSE      1000

#define CHARLCD_WRTIMEOUT  10          // Write time of 1mS max
#define CHARLCD_BSYTIMEOUT 50          // Busy time of 50mS max

//#define CHARLCD_MODE4BIT

typedef struct
{
    int current_position;
    int init;
}
_charlcd_t;


extern int test;

void delay(unsigned int msecs);
int charlcd_init(void);
void charlcd_write_string ( char *str );
void charlcd_clear(void);
void charlcd_cursor_right(unsigned int shift);
void charlcd_cursor_left(unsigned int shift);



#endif

// end of file charlcd_private.h
