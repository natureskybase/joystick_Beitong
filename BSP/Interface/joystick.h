/*
 * @Author: skybase
 * @Date: 2024-08-14 00:52:25
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-18 18:48:58
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\Interface\joystick.h
 */
#ifndef JOYSTICK_H_
#define JOYSTICK_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "adc.h"
#include "usart.h"

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
    LB = 1,
    RB = 2,
    Beitong = 4,
    Thrbo = 8,
    Clear = 0x10,
}GamepadButtonFlags_expand;

#pragma pack(1)
typedef struct
{
    uint16_t VL;
    uint16_t HL;
    uint16_t VR;
    uint16_t HR;

} spindle;
#pragma pack()


extern uint32_t button_state;
extern uint32_t button_state_extence;
extern spindle joystick_spin;
extern uint16_t adc_vals[5];
void JoystickDataTransmit();

#ifdef __cplusplus
}
#endif

#endif
