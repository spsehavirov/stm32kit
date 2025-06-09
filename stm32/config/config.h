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

// <q>Use I2C LCD backend
// <i> Enable support for LCD modules connected via I2C expander
#ifndef LCD_USE_I2C
 #define LCD_USE_I2C   0
#endif

// <o>LCD I2C address <0-255>
// <i> 7bit address of the I2C LCD expander
#ifndef LCD_I2C_ADDR
 #define LCD_I2C_ADDR  0x27
#endif

// <o>LCD I2C port <1-3>
// <i> Choose the I2C peripheral used for the LCD backend
#ifndef LCD_I2C_PORT
 #define LCD_I2C_PORT  1
#endif

// </h>

// <h> I2C
// ===============================
// <o>Default I2C bus speed <1000-400000>
// <i> Target I2C bus frequency in Hz
// <i> Default: 100000
#ifndef I2C_SPEED
 #define I2C_SPEED 100000U
#endif

// <e>I2C1
// <q>Enable I2C1
// <i> Include support for I2C1 peripheral
// <i> Default: 1
#ifndef I2C1_ENABLE
 #define I2C1_ENABLE 1
#endif
// <o>Pin pack <0-2>
// <i> Select pin pack used for I2C1 pins
// <i> Default: 0
#ifndef I2C1_PINPACK
 #define I2C1_PINPACK 0
#endif
// <o>Speed <1000-400000>
// <i> Bus speed in Hz
// <i> Default: I2C_SPEED
#ifndef I2C1_SPEED
 #define I2C1_SPEED I2C_SPEED
#endif
// <q>Master mode
// <i> Set to 1 for master mode operation
// <i> Default: 1
#ifndef I2C1_MASTER
 #define I2C1_MASTER 1
#endif
// <q>10-bit addressing
// <i> Enable 10-bit addressing mode
// <i> Default: 0
#ifndef I2C1_ADDR10
 #define I2C1_ADDR10 0
#endif
// <q>Dual address mode
// <i> Respond to second own address
// <i> Default: 0
#ifndef I2C1_DUAL
 #define I2C1_DUAL 0
#endif
// <o>Second address <0-1023>
// <i> Secondary address used when dual mode enabled
// <i> Default: 0
#ifndef I2C1_SECOND_ADDRESS
 #define I2C1_SECOND_ADDRESS 0
#endif
// <q>General Call enable
// <i> Respond to general call 0x00
// <i> Default: 0
#ifndef I2C1_GEN_CALL
 #define I2C1_GEN_CALL 0
#endif
// <q>No stretch
// <i> Disable clock stretching
// <i> Default: 0
#ifndef I2C1_NOSTRETCH
 #define I2C1_NOSTRETCH 0
#endif
// <q>Fast duty cycle 16/9
// <i> Use 16/9 duty cycle in Fast mode
// <i> Default: 0
#ifndef I2C1_DUTY
 #define I2C1_DUTY 0
#endif
// <o>Own address <0-1023>
// <i> Primary own address of I2C1
// <i> Default: 0x00
#ifndef I2C1_OWN_ADDRESS
 #define I2C1_OWN_ADDRESS 0x00
#endif
// </e>

// <e>I2C2
// <q>Enable I2C2
// <i> Include support for I2C2 peripheral
// <i> Default: 1
#ifndef I2C2_ENABLE
 #define I2C2_ENABLE 1
#endif
// <o>Pin pack <0-2>
// <i> Select pin pack used for I2C2 pins
// <i> Default: 0
#ifndef I2C2_PINPACK
 #define I2C2_PINPACK 0
#endif
// <o>Speed <1000-400000>
// <i> Bus speed in Hz
// <i> Default: I2C_SPEED
#ifndef I2C2_SPEED
 #define I2C2_SPEED I2C_SPEED
#endif
// <q>Master mode
// <i> Set to 1 for master mode operation
// <i> Default: 1
#ifndef I2C2_MASTER
 #define I2C2_MASTER 1
#endif
// <q>10-bit addressing
// <i> Enable 10-bit addressing mode
// <i> Default: 0
#ifndef I2C2_ADDR10
 #define I2C2_ADDR10 0
#endif
// <q>Dual address mode
// <i> Respond to second own address
// <i> Default: 0
#ifndef I2C2_DUAL
 #define I2C2_DUAL 0
#endif
// <o>Second address <0-1023>
// <i> Secondary address used when dual mode enabled
// <i> Default: 0
#ifndef I2C2_SECOND_ADDRESS
 #define I2C2_SECOND_ADDRESS 0
#endif
// <q>General Call enable
// <i> Respond to general call 0x00
// <i> Default: 0
#ifndef I2C2_GEN_CALL
 #define I2C2_GEN_CALL 0
#endif
// <q>No stretch
// <i> Disable clock stretching
// <i> Default: 0
#ifndef I2C2_NOSTRETCH
 #define I2C2_NOSTRETCH 0
#endif
// <q>Fast duty cycle 16/9
// <i> Use 16/9 duty cycle in Fast mode
// <i> Default: 0
#ifndef I2C2_DUTY
 #define I2C2_DUTY 0
#endif
// <o>Own address <0-1023>
// <i> Primary own address of I2C2
// <i> Default: 0x00
#ifndef I2C2_OWN_ADDRESS
 #define I2C2_OWN_ADDRESS 0x00
#endif
// </e>

// <e>I2C3
// <q>Enable I2C3
// <i> Include support for I2C3 peripheral
// <i> Default: 1
#ifndef I2C3_ENABLE
 #define I2C3_ENABLE 1
#endif
// <o>Pin pack <0-2>
// <i> Select pin pack used for I2C3 pins
// <i> Default: 0
#ifndef I2C3_PINPACK
 #define I2C3_PINPACK 0
#endif
// <o>Speed <1000-400000>
// <i> Bus speed in Hz
// <i> Default: I2C_SPEED
#ifndef I2C3_SPEED
 #define I2C3_SPEED I2C_SPEED
#endif
// <q>Master mode
// <i> Set to 1 for master mode operation
// <i> Default: 1
#ifndef I2C3_MASTER
 #define I2C3_MASTER 1
#endif
// <q>10-bit addressing
// <i> Enable 10-bit addressing mode
// <i> Default: 0
#ifndef I2C3_ADDR10
 #define I2C3_ADDR10 0
#endif
// <q>Dual address mode
// <i> Respond to second own address
// <i> Default: 0
#ifndef I2C3_DUAL
 #define I2C3_DUAL 0
#endif
// <o>Second address <0-1023>
// <i> Secondary address used when dual mode enabled
// <i> Default: 0
#ifndef I2C3_SECOND_ADDRESS
 #define I2C3_SECOND_ADDRESS 0
#endif
// <q>General Call enable
// <i> Respond to general call 0x00
// <i> Default: 0
#ifndef I2C3_GEN_CALL
 #define I2C3_GEN_CALL 0
#endif
// <q>No stretch
// <i> Disable clock stretching
// <i> Default: 0
#ifndef I2C3_NOSTRETCH
 #define I2C3_NOSTRETCH 0
#endif
// <q>Fast duty cycle 16/9
// <i> Use 16/9 duty cycle in Fast mode
// <i> Default: 0
#ifndef I2C3_DUTY
 #define I2C3_DUTY 0
#endif
// <o>Own address <0-1023>
// <i> Primary own address of I2C3
// <i> Default: 0x00
#ifndef I2C3_OWN_ADDRESS
 #define I2C3_OWN_ADDRESS 0x00
#endif
// </e>


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
