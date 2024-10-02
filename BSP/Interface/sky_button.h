/*
 * @Author: skybase
 * @Date: 2024-09-25 00:06:55
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-02 23:41:40
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\Interface\sky_button.h
 */
#ifndef BUTTON_H_
#define BUTTON_H_

#include "main.h"

typedef enum
{
    BTDown = 1,
    BTContinue,
    BTUp,
} PressType;

class button
{
public:
    typedef void (*ButtonEventCallbackType)(int);



    int button_id = 0;
    int button_priority = 0;
    int button_is_down = 0;
    int button_state = 0;
    int button_pressed_cal = 0;
    int dead_delay;

    ButtonEventCallbackType button_call[3]={nullptr,nullptr,nullptr};

    GPIO_TypeDef *GpioPort;
    uint32_t GpioPin;

    button(GPIO_TypeDef *_GpioPort, uint32_t _GpioPin, int id)
    {
        GpioPort = _GpioPort;
        GpioPin = _GpioPin;
        button_id = id;
    }
    bool operator==(const button &other) const
    {
        if (this->button_id == other.button_id)
        {
            return true;
        }

        return false;
    }

    void buttonCallRegist(ButtonEventCallbackType call, int type);
    int buttonStateMachine();
    void buttonStateUpdate();

private:
    void button_update();
};

// class Buttons
// {
// public:
//     class button *bt;

//     Buttons(button _bt[], int bt_num);
//     void ButtonsUpdate();

// private:
//     int bt_num;
// };

class joystick
{
public:
    typedef enum
    {
        TOIN = 1,
        IN,
        TOOUT,
    } EventType;

    typedef void (*StickEventCallbackType)(uint16_t x, uint16_t y);
    uint16_t dir_x;
    uint16_t dir_y;
    uint16_t dead_response;

    StickEventCallbackType call[100];
    int prioritylist[100] = {0};
    uint16_t eventpoint[100][2] = {0};
    int stick_state[100] = {0};
    int event_type[100] = {0};
    uint16_t eventnum = 0;

    void EventRegister(StickEventCallbackType call, uint16_t x, uint16_t y, EventType type, int priority);
    void StickStateMachine();
    void StickStateUpdate();
};

#endif
