					   // Header:
// File Name: charlcd.c	
// Author: Drew Barbier
// Date:
#include <stdio.h>
#include <ctype.h>
#include "charlcd.h"
#ifdef    CM0
#include "MPS_CM0.H"                        /* MPS Cortex-M0 definitions          */
#endif
#ifdef    CM3
#include "MPS_CM3.H"                        /* MPS Cortex-M3 definitions          */
#endif

static _charlcd_t charlcd; 

/*! \brief  delay in ms ***not exact
 *
 *  \param  msec NotExact number of mSecs to busy wait
 *
 */
void delay(unsigned int msecs)
{	 
  //load timer with cycles to delay
  TIM0->Timer1Load = (int)msecs*192;
  TIM0->Timer1Control = 0x83; //enable; 1-shot; 32bit
  while(TIM0->Timer1Value);
}

static void __platform_charlcd_busy( void )
{
    int wrtimeout, bsytimeout, readyflag;

    bsytimeout = CHARLCD_BSYTIMEOUT;

    // Wait for display busy flag
    do {
        // Start read of busy flag
        delay(1);
        
        // Read from command register to initiate status register access
        // returns value latter in CHAR_RAW and CHAR_RD
        readyflag = CHARLCD_COM_PTR;
        
        wrtimeout = CHARLCD_WRTIMEOUT;
    
        // Wait until busy flag is valid (max 1mS)
        do {
            delay(1);
            wrtimeout--;
        } while (wrtimeout && (!(CHARLCD_RAW_PTR & 0x100)));
    
        // Clear the data valid flag
        CHARLCD_RAW_PTR = 0;

        // Wait until display is not busy (max 50mS)
//        _platform_delay(1000);

        readyflag = CHARLCD_RD_PTR;
          
    } while (bsytimeout-- && (readyflag & CHARLCD_BUSY_FLAG));
}

static void __platform_charlcd_regwrite( unsigned char dat, unsigned char rs )
{
    // Wait for display
    __platform_charlcd_busy();


    // Write a data or command value
    if (rs) 
    {
        CHARLCD_DAT_PTR = (uint32_t)(dat & 0xff);
    }
    else
    {
        CHARLCD_COM_PTR = (uint32_t)(dat & 0xff);
    }     

}

/*! \brief  Writes a character to the debug lcd
 *
 *  \param  c Character to write to the lcd
 *
 */
static void __platform_charlcd_tx_char ( char c )
{
    // Check for a carriage return
    if (c != '\n')
    {   // Write character to lcd
        __platform_charlcd_regwrite( c, 1 );
        // increment position count
        charlcd.current_position++;
    }
    else
    {   // Display blanks for the rest of the line
        while ( charlcd.current_position < CHARLCD_MAX_CHARS)
        {   // Write a space to the lcd
            __platform_charlcd_regwrite( CHARLCD_SPACE_CHAR, 1 );
            charlcd.current_position++;
        }
    }

    // If the maximum number of characters has been displayed
    // reset to the start of the lcd.
    if (charlcd.current_position == CHARLCD_MAX_CHARS)
    {
        while ( charlcd.current_position < CHARLCD_CLR_LINE)
        {
            __platform_charlcd_regwrite( CHARLCD_SPACE_CHAR, 1 );
            charlcd.current_position++;
        }

        charlcd.current_position = 0;
    }
}

/*! \brief  clears entire charlcd display
 *
 *  \param  
 *
 */
void charlcd_clear()
{
	 __platform_charlcd_regwrite(CHARLCD_CLEAR, 0);
	 delay(1);


}

/*! \brief  shifts character lcd cursor right
 *
 *  \param  shift Number of positions to shift
 *
 */
void charlcd_cursor_right(unsigned int shift)
{
	 while(shift--)	{
	 	__platform_charlcd_regwrite(0x14, 0);
	 	charlcd.current_position++;

		
		// If the maximum number of characters has been displayed
	    // reset to the start of the lcd.
	    if (charlcd.current_position == CHARLCD_MAX_CHARS)
	    {
	        while ( charlcd.current_position < CHARLCD_CLR_LINE)
	        {
	            __platform_charlcd_regwrite( CHARLCD_SPACE_CHAR, 1 );
	            charlcd.current_position++;
	        }
	
	        charlcd.current_position = 0;
	    }
	 }

	 delay(1);
}

/*! \brief  shifts character lcd cursor left
 *
 *  \param  shift Number of positions to shift
 *
 */
void charlcd_cursor_left(unsigned int shift)
{
	 while(shift--)	{  
	 	__platform_charlcd_regwrite(0x10, 0);

		//if left shifting off the end of a line
		//set to begining of previouse line
	 	if(charlcd.current_position != 0)	{
			charlcd.current_position--;
		}else {
			charlcd.current_position = CHARLCD_MAX_CHARS;
			while(charlcd.current_position-- > 0)
			{
	 			__platform_charlcd_regwrite(0x10, 0); //shift left
			}
			charlcd.current_position = CHARLCD_MAX_CHARS-1;

		}
	 	


	 }

	 delay(1);
}

/*! \brief  Writes a string to the debug lcd
 *
 *  \param  str Pointer to the character string
 *
 */
void charlcd_write_string ( char *str )
{
    char c;

    while ((c = *str++) != NULL)
    {
        __platform_charlcd_tx_char(c);
    }
}


/*! \brief  initializes character lcd
 *
 *  \param  none
 *
 */

int charlcd_init()
{
	      // Perform software reset
    CHARLCD_COM_PTR = (CHARLCD_FUNC_SET       | CHARLCD_IF8BIT);
    delay(5);

     CHARLCD_COM_PTR = (CHARLCD_FUNC_SET       | CHARLCD_IF8BIT);
   delay(1);

    CHARLCD_COM_PTR = (CHARLCD_FUNC_SET       | CHARLCD_IF8BIT);
    delay(1);


    __platform_charlcd_regwrite(CHARLCD_FUNC_SET       | CHARLCD_IF8BIT | CHARLCD_NUMLINES2 | CHARLCD_FONT5X8  , 0);
    __platform_charlcd_regwrite(CHARLCD_DISP_CTRL      | CHARLCD_DISP_ON | CHARLCD_CURS_OFF  | CHARLCD_BLINK_OFF, 0);
    __platform_charlcd_regwrite(CHARLCD_ENTRY_MODE_SET | CHARLCD_INC, 0);
		
  	__platform_charlcd_regwrite(CHARLCD_CLEAR, 0);
	 delay(1);

	return 1;
}

