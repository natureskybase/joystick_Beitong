/*
 * @Author: skybase
 * @Date: 2024-08-14 03:55:47
 * @LastEditors: skybase
 * @LastEditTime: 2024-08-14 04:23:27
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystickBeitong\code\lcd_init.h
 */
#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"

#define USE_HORIZONTAL 2

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 80
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 80
#endif

#define LCD_SCLK_Clr() LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_10) // SCL=SCLK
#define LCD_SCLK_Set() LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10)

#define LCD_MOSI_Clr() LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_12) // SDA=MOSI
#define LCD_MOSI_Set() LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_12)

#define LCD_RES_Clr() LL_GPIO_ResetOutputPin(GPIOD, LL_GPIO_PIN_2) // RES
#define LCD_RES_Set() LL_GPIO_SetOutputPin(GPIOD, LL_GPIO_PIN_2)

#define LCD_DC_Clr() LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_11) // DC
#define LCD_DC_Set() LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_11)

#define LCD_CS_Clr()
#define LCD_CS_Set()

#define LCD_BLK_Clr()
#define LCD_BLK_Set()

void LCD_GPIO_Init(void);
void LCD_Writ_Bus(u8 dat);
void LCD_WR_DATA8(u8 dat);
void LCD_WR_DATA(u16 dat);
void LCD_WR_REG(u8 dat);
void LCD_Address_Set(u16 x1, u16 y1, u16 x2, u16 y2);
void LCD_Init(void);

#ifdef __cplusplus
}
#endif

#endif

