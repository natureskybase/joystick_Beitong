/*
 * @Author: skybase
 * @Date: 2024-08-14 00:52:05
 * @LastEditors: skybase
 * @LastEditTime: 2024-09-27 02:14:14
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystickBeitong\BSP\joystick.cpp
 */
#include "joystick.h"

uint32_t button_state = 0x0000;
uint32_t button_state_extence = 0x0000;
spindle joystick_spin = {0};

uint16_t adc_vals[4] = {0};

button button_RT = button(RT_GPIO_Port, RT_Pin);
button button_RB = button(RB_GPIO_Port, RB_Pin);
button button_Y = button(Y_GPIO_Port, Y_Pin);
button button_X = button(X_GPIO_Port, X_Pin);
button button_B = button(B_GPIO_Port, B_Pin);
button button_A = button(A_GPIO_Port, A_Pin);
button button_START = button(START_GPIO_Port, START_Pin);
button button_THRBO = button(THRBO_GPIO_Port, THRBO_Pin);
button button_HOME = button(HOME_GPIO_Port, HOME_Pin);
button button_BACK = button(BACK_GPIO_Port, BACK_Pin);
button button_CLEAR = button(CLEAR_GPIO_Port, CLEAR_Pin);
button button_RS = button(RS_GPIO_Port, RS_Pin);
button button_LS = button(LS_GPIO_Port, LS_Pin);
button button_LB = button(LB_GPIO_Port, LB_Pin);
button button_LT = button(LT_GPIO_Port, LT_Pin);
button button_UP = button(UP_GPIO_Port, UP_Pin);
button button_LEFT = button(LEFT_GPIO_Port, LEFT_Pin);
button button_DOWN = button(DOWM_GPIO_Port, DOWM_Pin);
button button_RIGHT = button(RIGHT_GPIO_Port, RIGHT_Pin);

joystick Stick_L = joystick();
joystick Stick_R = joystick();
joystick sticktest = joystick();

static uint64_t test_num1 = 0, test_num2 = 0, test_num3 = 0;
// void onButtonDown(int value)
// {
//     LCD_ShowIntNum(10, 30, test_num1++, 4, RED, WHITE, 16);
// }

// void onButtonContinue(int value)
// {
//     LCD_ShowIntNum(50, 30, test_num2++, 4, RED, WHITE, 16);
// }

// void onButtonUp(int value)
// {
//     LCD_ShowIntNum(90, 30, test_num3++, 4, RED, WHITE, 16);
// }

void stickin(uint16_t x, uint16_t y)
{
    LCD_ShowIntNum(10, 30, test_num1++, 4, RED, WHITE, 16);
}

void button_init()
{
    // button_A.button_call[0] = onButtonDown;
    // button_A.button_call[1] = onButtonContinue;
    // button_A.button_call[2] = onButtonUp;

    sticktest.EventRegister(stickin, 1000, 1000, sticktest.TOIN, 0);
    sticktest.eventnum = 1;
}


void button_update_test()
{
    // button_A.buttonStateUpdate();
    sticktest.StickStateUpdate();
}

#ifdef __cplusplus

extern "C"
{
#endif

    void tim2_callback(void)
    {
        LL_TIM_ClearFlag_UPDATE(TIM2);

        // !10ms的中断用于判断按键
        button_init();
        HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_vals, 4);
        sticktest.dead_response = 500;
        sticktest.dir_x = adc_vals[0];
        sticktest.dir_y = adc_vals[1];
        
        button_update_test();
        //        static uint32_t _gpio_state_a_last = 0;
        //        static uint32_t _gpio_state_b_last = 0;
        //        static uint32_t _gpio_state_c_last = 0;

        //        uint32_t _gpio_state_a = LL_GPIO_ReadInputPort(GPIOA);
        //        uint32_t _gpio_state_b = LL_GPIO_ReadInputPort(GPIOB);
        //        uint32_t _gpio_state_c = LL_GPIO_ReadInputPort(GPIOC);

        //        // if (!(_gpio_state_a & A_Pin))
        //        // {
        //        //     button_state |= (GamepadButtonFlags)A;
        //        // }
        //        // else
        //        // {
        //        //     button_state &= ~(GamepadButtonFlags)A;
        //        // }

        //        button_state = (!(_gpio_state_a & A_Pin)) ? button_state | A : button_state & ~A;
        //        button_state = (!(_gpio_state_a & B_Pin)) ? button_state | B : button_state & ~B;
        //        button_state = (!(_gpio_state_a & BACK_Pin)) ? button_state | Back : button_state & ~Back;
        //        button_state = (!(_gpio_state_a & DOWM_Pin)) ? button_state | DPadDown : button_state & ~DPadDown;
        //        button_state = (!(_gpio_state_a & RIGHT_Pin)) ? button_state | DPadRight : button_state & ~DPadRight;
        //        button_state = (!(_gpio_state_a & START_Pin)) ? button_state | Start : button_state & ~Start;
        //        button_state_extence = (!(_gpio_state_a & CLEAR_Pin)) ? button_state_extence | Clear : button_state_extence & ~Clear;
        //        button_state_extence = (!(_gpio_state_a & THRBO_Pin)) ? button_state_extence | Thrbo : button_state_extence & ~Thrbo;
        //        button_state_extence = (!(_gpio_state_a & HOME_Pin)) ? button_state_extence | Beitong : button_state_extence & ~Beitong;

        //        button_state = (!(_gpio_state_b & RS_Pin)) ? button_state | RightShoulder : button_state & ~RightShoulder;
        //        button_state = (!(_gpio_state_b & LS_Pin)) ? button_state | LeftShoulder : button_state & ~LeftShoulder;

        //        button_state = (!(_gpio_state_c & RT_Pin)) ? button_state | RightThumb : button_state & ~RightThumb;
        //        button_state = (!(_gpio_state_c & LT_Pin)) ? button_state | LeftThumb : button_state & ~LeftThumb;
        //        button_state = (!(_gpio_state_c & X_Pin)) ? button_state | X : button_state & ~X;
        //        button_state = (!(_gpio_state_c & Y_Pin)) ? button_state | Y : button_state & ~Y;
        //        button_state = (!(_gpio_state_c & UP_Pin)) ? button_state | DPadUp : button_state & ~DPadUp;
        //        button_state = (!(_gpio_state_c & LEFT_Pin)) ? button_state | DPadLeft : button_state & ~DPadLeft;
    }

#ifdef __cplusplus
}
#endif
