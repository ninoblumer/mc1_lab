/* ----------------------------------------------------------------------------
 * --  _____       ______  _____                                              -
 * -- |_   _|     |  ____|/ ____|                                             -
 * --   | |  _ __ | |__  | (___    Institute of Embedded Systems              -
 * --   | | | '_ \|  __|  \___ \   Zurich University of                       -
 * --  _| |_| | | | |____ ____) |  Applied Sciences                           -
 * -- |_____|_| |_|______|_____/   8401 Winterthur, Switzerland               -
 * ----------------------------------------------------------------------------
 * --
 * -- Project     : CT2 Lab Matrix-Keypad
 * -- Description : Modul handles the reading of the keypad
 * --
 * -- $Id: keypad.c 1440 2018-08-21 15:51:07Z ruan $
 * ------------------------------------------------------------------------- */

#include "keypad.h"
#include "hal_gpio.h"
#include "reg_ctboard.h"


/* -- Macros, type definitions and function prototypes
 * --------------------------------------------------------------------------*/
 
/// STUDENTS: To be programmed




/// END: To be programmed

/* internal variable definitions ------------------------------------------- */

static const int key_array [4][4] = { { 0x1, 0x2, 0x3, 0xF },
                                      { 0x4, 0x5, 0x6, 0xE },
                                      { 0x7, 0x8, 0x9, 0xD },
                                      { 0xA, 0x0, 0xB, 0xC } };

																			

/* public function definitions --------------------------------------------- */
                                      
/*
 * See header file
 */
uint8_t scan_keypad_cbc(void)
{
    uint8_t ret_val = NOKEY_PRESSED;
		/// STUDENTS: To be programmed
		uint8_t col = 1;
		uint8_t row = 0;
		uint8_t mask;
		uint8_t i,j;
	
	
		hal_gpio_output_t col_output = {	0x000F, 
																			HAL_GPIO_PUPD_UP,
                                      HAL_GPIO_OUT_SPEED_2MHZ,
                                      HAL_GPIO_OUT_TYPE_PP 
		};
		hal_gpio_input_t  row_input =  { 	0x00F0,
                                   HAL_GPIO_PUPD_UP
		};
		 
		hal_gpio_init_output(GPIOB, col_output);
    hal_gpio_init_input(GPIOB, row_input);
		
		hal_gpio_bit_set(GPIOB, 0x000F );			// set all cols to 1 
																	 
		for(  i = 0; i < 4 ;  i++) {
			hal_gpio_bit_set(GPIOB, 0x000F );			// set all cols to 1
			
			hal_gpio_bit_reset(GPIOB,col);
			
			row = hal_gpio_input_read(GPIOB);
	
			row = ~row;
			row >>= 4;
			row &= 0x000F;
			
			if( row != 0x00) {
				mask = 1;
				for(j = 0;  j < 4;  j++) {
					if( mask  & row) {
						ret_val = key_array[j][i];
						break;
					}
					mask <<= 1;
				}
				
				goto ret;
			}
			
			
			col <<= 1;
		}



    /// END: To be programmed
ret:   return ret_val;
}

/*
 * See header file
 */
uint8_t scan_keypad_fast(void)
{
    uint8_t ret_val = NOKEY_PRESSED;
    /// STUDENTS: To be programmed
		uint8_t row, col, mask;
		uint8_t  i, j;
		hal_gpio_output_t col_output = {	0x000F, 
																			HAL_GPIO_PUPD_UP,
                                      HAL_GPIO_OUT_SPEED_2MHZ,
                                      HAL_GPIO_OUT_TYPE_PP 
		};
		hal_gpio_input_t  col_input =  { 	0x000F,
                                   HAL_GPIO_PUPD_UP
		};
		hal_gpio_output_t row_output = {	0x00F0, 
																			HAL_GPIO_PUPD_UP,
                                      HAL_GPIO_OUT_SPEED_2MHZ,
                                      HAL_GPIO_OUT_TYPE_PP 
		};
		hal_gpio_input_t  row_input =  { 	0x00F0,
                                   HAL_GPIO_PUPD_UP
		};
		
		 
		hal_gpio_init_output(GPIOB, col_output);
    hal_gpio_init_input(GPIOB, row_input);
		hal_gpio_bit_reset(GPIOB,0x0F);
		row = hal_gpio_input_read(GPIOB);
		row = ~row;
		row >>= 4;
		row &= 0x000F;
		
		hal_gpio_init_output(GPIOB, row_output);
    hal_gpio_init_input(GPIOB, col_input);
		hal_gpio_bit_reset(GPIOB,0xF0);
		col = hal_gpio_input_read(GPIOB);
		col = ~col;
		col &= 0x000F;
		
		
		if( (row == 0x00) || (col == 0x00) ) {
			ret_val = NOKEY_PRESSED;
		} else {
				mask = 1;
				for(j = 0;  j < 4;  j++) {
					if( mask  & row) {
						
						break;
					}
					mask <<= 1;
				}
				
				mask = 1;
				for(i = 0;  i < 4;  i++) {
					if( mask  & col) {
						break;
					}
					mask <<= 1;
				}
				
				ret_val = key_array[j][i];
			}



    /// END: To be programmed
    return ret_val;
}

/* internal functions definitions ------------------------------------------ */
/// STUDENTS: To be programmed




/// END: To be programmed

