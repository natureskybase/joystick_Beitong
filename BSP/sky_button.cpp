
///*
// * @Author: skybase
// * @Date: 2024-09-25 00:06:55
// * @LastEditors: skybase
// * @LastEditTime: 2024-09-25 15:17:51
// * @Description:  ᕕ(◠ڼ◠)ᕗ​
// * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystickBeitong\BSP\sky_button.cpp
// */
#include "sky_button.h"

void button::button_update()
{
    button_is_down = !(LL_GPIO_IsInputPinSet(GpioPort, GpioPin));
}

    int button::buttonStateMachine()
{
    static int _dead_time = 0;
    button_state = 0;
    if (button_is_down && _dead_time == 0)
    {
        button_state = 1;
        _dead_time++;
        return 0;
    }
    else if (_dead_time > 0)
    {
        button_state = 2;
        _dead_time++;
    }
    if (!button_is_down && _dead_time != 0)
    {
        button_state = 3;
        _dead_time = 0;
        return 0;
    }

    return _dead_time;
}

void button::buttonStateUpdate()
{
    button_update();
    button_pressed_cal = buttonStateMachine();
    if (!!button_state)
    {
        button_call[button_state - 1](button_pressed_cal);
    }
}

void button::buttonCallRegist(ButtonEventCallbackType call, PressType type)
{
    button_call[type] = call;
}


//!*************************************************************************/

void joystick::StickStateMachine()
{
    for (uint16_t i = 0; i < eventnum; i++)
    {
        uint16_t _tag_x = eventpoint[i][0];
        uint16_t _tag_y = eventpoint[i][1];
        int judge_condtion = (dir_x <= _tag_x + dead_response && dir_x >= _tag_x - dead_response && dir_y <= _tag_y + dead_response && dir_y >= _tag_y - dead_response);
        if (judge_condtion == 1 && stick_state[i] == 0)
        {
            stick_state[i] = TOIN;
            break;
        }
        else if (judge_condtion == 1 && stick_state[i] == TOIN)
        {
            stick_state[i] = IN;
            break;
        }

        if (judge_condtion == 0 && stick_state[i] == IN)
        {
            stick_state[i] = TOOUT;
            break;
        }
        if (stick_state[i] == TOOUT)
            stick_state[i] = 0;
    }
}

void joystick::StickStateUpdate()
{
    StickStateMachine();
    for (uint16_t i = 0; i < eventnum; i++)
    {
        if (stick_state[i] != 0)
        {
            if (stick_state[i] == event_type[i])
                call[i](eventpoint[i][0], eventpoint[i][1]);
        }
    }
}

template <typename T>
void list_swap(T &a, T &b)
{
    T temp = a;
    a = b;
    b = temp;
}

void joystick::EventRegister(StickEventCallbackType callback, uint16_t x, uint16_t y, EventType type, int priority)
{
    call[eventnum] = callback;
    eventpoint[eventnum][0] = x;
    eventpoint[eventnum][1] = y;
    prioritylist[eventnum] = priority;
    event_type[eventnum] = type;

    for (uint16_t i = 0; i < eventnum; i++)
    {
        if (prioritylist[i] > prioritylist[eventnum])
        {
            list_swap(prioritylist[i], prioritylist[eventnum]);
            list_swap(call[i], call[eventnum]);
            list_swap(eventpoint[i][0], eventpoint[i][0]);
            list_swap(eventpoint[i][1], eventpoint[i][1]);
            list_swap(event_type[i], event_type[eventnum]);
        }
    }
    eventnum++;
}