#include "ts.h"

button button_A = button(A_GPIO_Port, A_Pin);
uint32_t button_state = 0x0000;
uint32_t button_state_extence = 0x0000;
spindle joystick_spin = {0};