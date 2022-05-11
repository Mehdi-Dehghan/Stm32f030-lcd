#ifndef LCD_H
#define LCD_H
/*************************************************************************
 Title	:   C include file for the HD44780U LCD library (lcd.c)
 Author:    Peter Fleury <pfleury@gmx.ch>  http://tinyurl.com/peterfleury
 File:	    $Id: lcd.h,v 1.14.2.4 2015/01/20 17:16:07 peter Exp $
 Software:  AVR-GCC 4.x
 Hardware:  any AVR device, memory mapped mode only for AVR with 
            memory mapped interface (AT90S8515/ATmega8515/ATmega128)
***************************************************************************/
#include "stm32f0xx.h"
#include "main.h"
#include "stm32f0xx_hal.h"

#ifndef LCD_LINES
#define LCD_LINES           2     /**< number of visible lines of the display */
#endif
#ifndef LCD_DISP_LENGTH
#define LCD_DISP_LENGTH    16     /**< visibles characters per line of the display */
#endif
#ifndef LCD_LINE_LENGTH
#define LCD_LINE_LENGTH  0x40     /**< internal line length of the display    */
#endif
#ifndef LCD_START_LINE1
#define LCD_START_LINE1  0x00     /**< DDRAM address of first char of line 1 */
#endif
#ifndef LCD_START_LINE2
#define LCD_START_LINE2  0x40     /**< DDRAM address of first char of line 2 */
#endif
#ifndef LCD_START_LINE3
#define LCD_START_LINE3  0x14     /**< DDRAM address of first char of line 3 */
#endif
#ifndef LCD_START_LINE4
#define LCD_START_LINE4  0x54     /**< DDRAM address of first char of line 4 */
#endif
#ifndef LCD_WRAP_LINES
#define LCD_WRAP_LINES      0     /**< 0: no wrap, 1: wrap at end of visibile line */
#endif


/**
 * @name Definitions for 4-bit IO mode
 *
 * The four LCD data lines and the three control lines RS, RW, E can be on the 
 * same port or on different ports. 
 * Change LCD_RS_PORT, LCD_RW_PORT, LCD_E_PORT if you want the control lines on
 * different ports. 
 *
 * Normally the four data lines should be mapped to bit 0..3 on one port, but it
 * is possible to connect these data lines in different order or even on different
 * ports by adapting the LCD_DATAx_PORT and LCD_DATAx_PIN definitions.
 *
 * Adjust these definitions to your target.\n 
 * These definitions can be defined in a separate include file \b lcd_definitions.h instead modifying this file by 
 * adding \b -D_LCD_DEFINITIONS_FILE to the \b CDEFS section in the Makefile.
 * All definitions added to the file lcd_definitions.h will override the default definitions from lcd.h
 *  
 */
#define LCD_IO_MODE      1            /**< 0: memory mapped mode, 1: IO port mode */

#if LCD_IO_MODE
/*
#define		LCD_PORT	GPIOA

#define		LCD_RS		GPIO_PIN_12
#define		LCD_RW		GPIO_PIN_11
#define		LCD_E		GPIO_PIN_10
#define		LCD_DB4 	GPIO_PIN_0
#define		LCD_DB5 	GPIO_PIN_1
#define		LCD_DB6 	GPIO_PIN_2
#define		LCD_DB7 	GPIO_PIN_3
*/

#ifndef LCD_PORT
#define LCD_PORT         	        /**< port for the LCD lines   */
#endif
#ifndef LCD_DATA0_PORT
#define LCD_DATA0_PORT   GPIOB     /**< port for 4bit data bit 0 */
#endif
#ifndef LCD_DATA1_PORT
#define LCD_DATA1_PORT   GPIOB     /**< port for 4bit data bit 1 */
#endif
#ifndef LCD_DATA2_PORT
#define LCD_DATA2_PORT   GPIOA     /**< port for 4bit data bit 2 */
#endif
#ifndef LCD_DATA3_PORT
#define LCD_DATA3_PORT   GPIOA     							/**< port for 4bit data bit 3 */
#endif
#ifndef LCD_DATA0_PIN
#define LCD_DATA0_PIN    GPIO_PIN_4							/**< pin for 4bit data bit 0  */
#endif
#ifndef LCD_DATA1_PIN
#define LCD_DATA1_PIN    GPIO_PIN_3            	/**< pin for 4bit data bit 1  */
#endif
#ifndef LCD_DATA2_PIN
#define LCD_DATA2_PIN    GPIO_PIN_15           	/**< pin for 4bit data bit 2  */
#endif
#ifndef LCD_DATA3_PIN
#define LCD_DATA3_PIN    GPIO_PIN_12           	/**< pin for 4bit data bit 3  */
#endif
#ifndef LCD_RS_PORT
#define LCD_RS_PORT      GPIOB     						 	/**< port for RS line         */
#endif
#ifndef LCD_RS_PIN
#define LCD_RS_PIN       GPIO_PIN_7            	/**< pin  for RS line         */
#endif
#ifndef LCD_RW_PORT
#define LCD_RW_PORT      GPIOB     						 	/**< port for RW line         */
#endif
#ifndef LCD_RW_PIN
#define LCD_RW_PIN       GPIO_PIN_6            	/**< pin  for RW line         */
#endif
#ifndef LCD_E_PORT
#define LCD_E_PORT       GPIOB     							/**< port for Enable line     */
#endif
#ifndef LCD_E_PIN
#define LCD_E_PIN        GPIO_PIN_5            	/**< pin  for Enable line     */
#endif
// RS - PORTC Bit 6
// RD - PORTC Bit 5
// EN - PORTC Bit 4
// D4 - PORTC Bit 3
// D5 - PORTC Bit 2
// D6 - PORTC Bit 1
// D7 - PORTC Bit 0

/*
 * memory mapped mode is only supported when the device has an external data memory interface
 */
#define LCD_IO_DATA      0xC000    /* A15=E=1, A14=RS=1                 */
#define LCD_IO_FUNCTION  0x8000    /* A15=E=1, A14=RS=0                 */
#define LCD_IO_READ      0x0100    /* A8 =R/W=1 (R/W: 1=Read, 0=Write   */

#else
#error "external data memory interface not available for this device, use 4-bit IO port mode"

#endif


/**
 * @name Definitions of delays
 * Used to calculate delay timers.
 * Adapt the F_CPU define in the Makefile to the clock frequency in Hz of your target
 *
 * These delay times can be adjusted, if some displays require different delays.\n 
 * These definitions can be defined in a separate include file \b lcd_definitions.h instead modifying this file by 
 * adding \b -D_LCD_DEFINITIONS_FILE to the \b CDEFS section in the Makefile.
 * All definitions added to the file lcd_definitions.h will override the default definitions from lcd.h
 */
#ifndef LCD_DELAY_BOOTUP
#define LCD_DELAY_BOOTUP   					160   /**< delay in micro seconds after power-on  */
#endif
#ifndef LCD_DELAY_INIT
#define LCD_DELAY_INIT      				50    /**< delay in micro seconds after initialization command sent  */
#endif
#ifndef LCD_DELAY_INIT_REP
#define LCD_DELAY_INIT_REP    			64    /**< delay in micro seconds after initialization command repeated */
#endif
#ifndef LCD_DELAY_INIT_4BIT
#define LCD_DELAY_INIT_4BIT   			64    /**< delay in micro seconds after setting 4-bit mode */ 
#endif
#ifndef LCD_DELAY_BUSY_FLAG
#define LCD_DELAY_BUSY_FLAG    			4     /**< time in micro seconds the address counter is updated after busy flag is cleared */
#endif
#ifndef LCD_DELAY_ENABLE_PULSE
#define LCD_DELAY_ENABLE_PULSE 			1     /**< enable signal pulse width in micro seconds */
#endif


/**
 * @name Definitions for LCD command instructions
 * The constants define the various LCD controller instructions which can be passed to the 
 * function lcd_command(), see HD44780 data sheet for a complete description.
 */

/* instruction register bit positions, see HD44780U data sheet */
#define LCD_CLR               0      /* DB0: clear display                  */
#define LCD_HOME              1      /* DB1: return to home position        */
#define LCD_ENTRY_MODE        2      /* DB2: set entry mode                 */
#define LCD_ENTRY_INC         1      /*   DB1: 1=increment, 0=decrement     */
#define LCD_ENTRY_SHIFT       0      /*   DB2: 1=display shift on           */
#define LCD_ON                3      /* DB3: turn lcd/cursor on             */
#define LCD_ON_DISPLAY        2      /*   DB2: turn display on              */
#define LCD_ON_CURSOR         1      /*   DB1: turn cursor on               */
#define LCD_ON_BLINK          0      /*     DB0: blinking cursor ?          */
#define LCD_MOVE              4      /* DB4: move cursor/display            */
#define LCD_MOVE_DISP         3      /*   DB3: move display (0-> cursor) ?  */
#define LCD_MOVE_RIGHT        2      /*   DB2: move right (0-> left) ?      */
#define LCD_FUNCTION          5      /* DB5: function set                   */
#define LCD_FUNCTION_8BIT     4      /*   DB4: set 8BIT mode (0->4BIT mode) */
#define LCD_FUNCTION_2LINES   3      /*   DB3: two lines (0->one line)      */
#define LCD_FUNCTION_10DOTS   2      /*   DB2: 5x10 font (0->5x7 font)      */
#define LCD_CGRAM             6      /* DB6: set CG RAM address             */
#define LCD_DDRAM             7      /* DB7: set DD RAM address             */
#define LCD_BUSY              7      /* DB7: LCD is busy                    */

/* set entry mode: display shift on/off, dec/inc cursor move direction */
#define LCD_ENTRY_DEC            0x04   /* display shift off, dec cursor move dir */
#define LCD_ENTRY_DEC_SHIFT      0x05   /* display shift on,  dec cursor move dir */
#define LCD_ENTRY_INC_           0x06   /* display shift off, inc cursor move dir */
#define LCD_ENTRY_INC_SHIFT      0x07   /* display shift on,  inc cursor move dir */

/* display on/off, cursor on/off, blinking char at cursor position */
#define LCD_DISP_OFF             0x08   /* display off                            */
#define LCD_DISP_ON              0x0C   /* display on, cursor off                 */
#define LCD_DISP_ON_BLINK        0x0D   /* display on, cursor off, blink char     */
#define LCD_DISP_ON_CURSOR       0x0E   /* display on, cursor on                  */
#define LCD_DISP_ON_CURSOR_BLINK 0x0F   /* display on, cursor on, blink char      */

/* move cursor/shift display */
#define LCD_MOVE_CURSOR_LEFT     0x10   /* move cursor left  (decrement)          */
#define LCD_MOVE_CURSOR_RIGHT    0x14   /* move cursor right (increment)          */
#define LCD_MOVE_DISP_LEFT       0x18   /* shift display left                     */
#define LCD_MOVE_DISP_RIGHT      0x1C   /* shift display right                    */

/* function set: set interface data length and number of display lines */
#define LCD_FUNCTION_4BIT_1LINE  0x20   /* 4-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_4BIT_2LINES 0x28   /* 4-bit interface, dual line,   5x7 dots */
#define LCD_FUNCTION_8BIT_1LINE  0x30   /* 8-bit interface, single line, 5x7 dots */
#define LCD_FUNCTION_8BIT_2LINES 0x38   /* 8-bit interface, dual line,   5x7 dots */


#define LCD_MODE_DEFAULT     ((1<<LCD_ENTRY_MODE) | (1<<LCD_ENTRY_INC) )



/** 
 *  @name Functions
 */


/**
 @brief    Initialize display and select type of cursor
 @param    dispAttr \b LCD_DISP_OFF display off\n
                    \b LCD_DISP_ON display on, cursor off\n
                    \b LCD_DISP_ON_CURSOR display on, cursor on\n
                    \b LCD_DISP_ON_CURSOR_BLINK display on, cursor on flashing             
 @return  none
*/
extern void lcd_init(uint8_t dispAttr);


/**
 @brief    Clear display and set cursor to home position
 @return   none
*/
extern void lcd_clrscr(void);
#define lcd_clear	lcd_clrscr

/**
 @brief    Set cursor to home position
 @return   none
*/
extern void lcd_home(void);


/**
 @brief    Set cursor to specified position
 
 @param    x horizontal position\n (0: left most position)
 @param    y vertical position\n   (0: first line)
 @return   none
*/
extern void lcd_gotoxy(uint8_t x, uint8_t y);


/**
 @brief    Display character at current cursor position
 @param    c character to be displayed                                       
 @return   none
*/
extern void lcd_putc(char c);
#define lcd_putchar	lcd_putc

/**
 @brief    Display string without auto linefeed
 @param    s string to be displayed                                        
 @return   none
*/
extern void lcd_puts(const char *s);


/**
 @brief    Display string from program memory without auto linefeed
 @param    progmem_s string from program memory be be displayed                                        
 @return   none
 @see      lcd_puts_P
*/
extern void lcd_puts_p(const char *progmem_s);


/**
 @brief    Send LCD controller instruction command
 @param    cmd instruction to send to LCD controller, see HD44780 data sheet
 @return   none
*/
extern void lcd_command(uint8_t cmd);


/**
 @brief    Send data byte to LCD controller 
 
 Similar to lcd_putc(), but without interpreting LF
 @param    data byte to send to LCD controller, see HD44780 data sheet
 @return   none
*/
extern void lcd_data(uint8_t data);


/**
 @brief macros for automatically storing string constant in program memory
*/
#define lcd_puts_P(__s)         lcd_puts_p(PSTR(__s))

/**@}*/

#endif //LCD_H
