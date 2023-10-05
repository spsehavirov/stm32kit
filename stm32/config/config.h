/**
 *
 */
#include <stdint.h>
#ifndef STM32_KIT_CONFIG
#define STM32_KIT_CONFIG

#ifdef __cplusplus
extern "C" {
#endif
 
/*----------------------------------------------------------------------------
 *      STM32Kit User configuration BEGIN
 *---------------------------------------------------------------------------*/

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//
// <h>RTOS
// ===============================


// <q>Enable RTOS
// ===============================
// <i> Include RTOS config files and enable its support in project.
// <i> Note that RTOS requires RTOS examples.
#ifndef USE_RTOS
 #define USE_RTOS    0
#endif

// </h>

// <h> LCD
// ===============================
//   <o>LCD COLS <8=>     8  
//               <16=>   16
//               <20=>   20
//							 <40=>   40
//   <i> Number of characters per LCD screen line.
//   <i> Default: 8
#ifndef LCD_COLS
 #define LCD_COLS      8
#endif

//   <o>LCD ROWS <1=>   1  
//               <2=>   2
//               <4=>   4
//   <i> Number of the lines in the LCD screen.
//   <i> Default: 2 rows
#ifndef LCD_ROWS
 #define LCD_ROWS      2
#endif


// </h>

// <h> Keypad
// ===============================
//   <o>KEYPAD COLS <3=>   3
//                  <4=>   4
//   <i> Number of the buttons on KEYPAD line.
//   <i> Default: 4
#ifndef KEYPAD_COLS
 #define KEYPAD_COLS      3
#endif

//   <o>KEYPAD ROWS <3=>   3
//                  <4=>   4
//   <i> Number of the lines in the Keypad.
//   <i> Default: 4 rows
#ifndef KEYPAD_ROWS
 #define KEYPAD_ROWS      4
#endif

//   <o>STEP <0-1000000>
//   <i> Set the delay for antialiasing the keypad.
//   <i> Default: 100
#ifndef KEYPAD_STEP
 #define KEYPAD_STEP        150
#endif
// </h>

// <h> UART
// ===============================
//   <o>Baudrate <2400-1125000>
//   <i> Set the baudrate (speed) of the UART.
//   <i> Default: 9600
#ifndef UART_BAUDRATE
 #define UART_BAUDRATE        9600
#endif


//------------- <<< end of configuration section >>> -----------------------

// Defaultni rozlozeni pro 4x4 KeyPad
/*static uint8_t KeyPad_KeyMap[KEYPAD_ROWS][KEYPAD_COLS] = {
		'1', '2', '3', 'A',
		'4', '5', '6', 'B',
		'7', '8', '9', 'C',
		'*', '0', '#', 'D'
};*/

#ifdef __cplusplus
}
#endif

#endif /* STM32KIT_CONFIG */
