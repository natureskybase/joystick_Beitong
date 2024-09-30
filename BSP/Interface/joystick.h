/*
 * @Author: skybase
 * @Date: 2024-08-14 00:52:25
 * @LastEditors: skybase
 * @LastEditTime: 2024-09-26 23:52:43
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystickBeitong\BSP\joystick.h
 */
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#include "main.h"
#include "adc.h"
#include "stm32g4xx_hal.h"
#include "sky_button.h"
#include "lcd.h"

typedef enum
{
    None = 0,
    DPadUp = 1,
    DPadDown = 2,
    DPadLeft = 4,
    DPadRight = 8,
    Start = 0x10,
    Back = 0x20,
    LeftThumb = 0x40,
    RightThumb = 0x80,
    LeftShoulder = 0x100,
    RightShoulder = 0x200,
    A = 0x1000,
    B = 0x2000,
    X = 0x4000,
    Y = 0x8000

} GamepadButtonFlags;

typedef enum
{
    Beitong = 1,
    Thrbo = 2,
    Clear = 4
} GamepadButtonFlags_expand;

#pragma pack(1)
typedef struct
{
    uint8_t LB;
    uint8_t RB;
    uint32_t VL;
    uint32_t HL;
    uint32_t VR;
    uint32_t HR;

} spindle;
#pragma pack()

void button_get(void);

extern uint32_t button_state;
extern uint32_t button_state_extence;
extern spindle joystick_spin;




#endif
