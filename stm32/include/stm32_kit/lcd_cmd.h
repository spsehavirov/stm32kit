#ifndef STM32_KIT_LCD_CMD
#define STM32_KIT_LCD_CMD

#define LCD_CMD_CLEAR             0x01
#define LCD_CMD_HOME              0x02

/* Bits for ENTRY_MODE command */
#define LCD_ENTRY_INC             (1<<1)
#define LCD_ENTRY_DEC             0
#define LCD_ENTRY_SHIFT           (1<<0)
#define LCD_CMD_ENTRY_MODE(f)    (0x04 | ((f) & (LCD_ENTRY_INC|LCD_ENTRY_SHIFT)))

/* Bits for DISPLAY command */
#define LCD_DISP_ON               (1<<2)
#define LCD_DISP_OFF              0
#define LCD_CURSOR_ON             (1<<1)
#define LCD_CURSOR_OFF            0
#define LCD_BLINK_ON              (1<<0)
#define LCD_BLINK_OFF             0
#define LCD_CMD_DISPLAY(f)       (0x08 | ((f) & (LCD_DISP_ON|LCD_CURSOR_ON|LCD_BLINK_ON)))

/* Bits for SHIFT command */
#define LCD_SHIFT_DISPLAY         (1<<3)
#define LCD_SHIFT_CURSOR          0
#define LCD_SHIFT_RIGHT           (1<<2)
#define LCD_SHIFT_LEFT            0
#define LCD_CMD_SHIFT(f)         (0x10 | ((f) & (LCD_SHIFT_DISPLAY|LCD_SHIFT_RIGHT)))

/* Bits for FUNCTION command */
#define LCD_FUNC_8BIT             (1<<4)
#define LCD_FUNC_4BIT             0
#define LCD_FUNC_2LINE            (1<<3)
#define LCD_FUNC_1LINE            0
#define LCD_FUNC_5x10             (1<<2)
#define LCD_FUNC_5x8              0
#define LCD_CMD_FUNCTION(f)      (0x20 | ((f) & (LCD_FUNC_8BIT|LCD_FUNC_2LINE|LCD_FUNC_5x10)))

#define LCD_CMD_SET_CGRAM(addr)   (0x40 | ((addr) & 0x3F))
#define LCD_CMD_SET_DDRAM(addr)   (0x80 | ((addr) & 0x7F))

/* Legacy names kept for compatibility */
#define LCD_ON           LCD_CMD_DISPLAY(LCD_DISP_ON)
#define LCD_OFF          LCD_CMD_DISPLAY(LCD_DISP_OFF)
#define LCD_CLR          LCD_CMD_CLEAR
#define LCD_CUR_ON       LCD_CMD_DISPLAY(LCD_DISP_ON | LCD_CURSOR_ON)
#define LCD_CUR_OFF      LCD_CMD_DISPLAY(LCD_DISP_ON)
#define LCD_CUR_BLINK    LCD_CMD_DISPLAY(LCD_DISP_ON | LCD_CURSOR_ON | LCD_BLINK_ON)
#define LCD_CUR_NO_BLINK LCD_CMD_DISPLAY(LCD_DISP_ON | LCD_CURSOR_ON)
#define LCD_CUR_HOME     LCD_CMD_HOME
#define LCD_SL           LCD_CMD_SHIFT(LCD_SHIFT_DISPLAY | LCD_SHIFT_LEFT)
#define LCD_SR           LCD_CMD_SHIFT(LCD_SHIFT_DISPLAY | LCD_SHIFT_RIGHT)
#define LCD_LINE1        LCD_CMD_SET_DDRAM(0x00)
#define LCD_LINE2        LCD_CMD_SET_DDRAM(0x40)
#define LCD_LINE3        LCD_CMD_SET_DDRAM(0x14)
#define LCD_LINE4        LCD_CMD_SET_DDRAM(0x54)

#endif /* STM32_KIT_LCD_CMD */
