/*
 * @Author: skybase
 * @Date: 2024-09-30 18:02:20
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-18 23:57:52
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\Core\Src\maincpp.h
 */
#ifndef __MAINCPP_H
#define __MAINCPP_H

#ifdef __cplusplus

extern "C"
{
#endif


#include "main.h"
#include "adc.h"
#include "stm32g4xx_hal.h"


    int MainCppInit(void);
    int MainCppLoop(void);


    void InterfaceStateUpdate(void);



#ifdef __cplusplus
}
#endif

#endif