#include "maincpp.h"
#include "sky_button.h"
#include "sky_menu.h"
#include "drawer.h"
#include "lcd.h"

#include <stdio.h>
#include <cstdio>

int TIM1_FLAG = 0;

uint16_t adc_vals[5] = {0};
static int bt_id = 0;
button button_RT = button(RT_GPIO_Port, RT_Pin, bt_id++);
button button_RB = button(RB_GPIO_Port, RB_Pin, bt_id++);
button button_Y = button(Y_GPIO_Port, Y_Pin, bt_id++);
button button_X = button(X_GPIO_Port, X_Pin, bt_id++);
button button_B = button(B_GPIO_Port, B_Pin, bt_id++);
button button_A = button(A_GPIO_Port, A_Pin, bt_id++);
button button_START = button(START_GPIO_Port, START_Pin, bt_id++);
button button_THRBO = button(THRBO_GPIO_Port, THRBO_Pin, bt_id++);
button button_HOME = button(HOME_GPIO_Port, HOME_Pin, bt_id++);
button button_BACK = button(BACK_GPIO_Port, BACK_Pin, bt_id++);
button button_CLEAR = button(CLEAR_GPIO_Port, CLEAR_Pin, bt_id++);
button button_RS = button(RS_GPIO_Port, RS_Pin, bt_id++);
button button_LS = button(LS_GPIO_Port, LS_Pin, bt_id++);
button button_LB = button(LB_GPIO_Port, LB_Pin, bt_id++);
button button_LT = button(LT_GPIO_Port, LT_Pin, bt_id++);
button button_UP = button(UP_GPIO_Port, UP_Pin, bt_id++);
button button_LEFT = button(LEFT_GPIO_Port, LEFT_Pin, bt_id++);
button button_DOWN = button(DOWM_GPIO_Port, DOWM_Pin, bt_id++);
button button_RIGHT = button(RIGHT_GPIO_Port, RIGHT_Pin, bt_id++);

joystick Stick_L = joystick();
joystick Stick_R = joystick();
joystick sticktest = joystick();

Drawer lcd_drawer = Drawer();
Menu menu = Menu();

float remap(float x, float y, float x1, float y1, float value)
{
	return x1 + (value - x) * (y1 - x1) / (y - x);
}

void button_state_update()
{
	button_RT.buttonStateUpdate();
	button_RB.buttonStateUpdate();
	button_Y.buttonStateUpdate();
	button_X.buttonStateUpdate();
	button_B.buttonStateUpdate();
	button_A.buttonStateUpdate();
	button_START.buttonStateUpdate();
	button_THRBO.buttonStateUpdate();
	button_HOME.buttonStateUpdate();
	button_BACK.buttonStateUpdate();
	button_CLEAR.buttonStateUpdate();
	button_RS.buttonStateUpdate();
	button_LS.buttonStateUpdate();
	button_LB.buttonStateUpdate();
	button_LT.buttonStateUpdate();
	button_UP.buttonStateUpdate();
	button_LEFT.buttonStateUpdate();
	button_DOWN.buttonStateUpdate();
	button_RIGHT.buttonStateUpdate();
}
static uint64_t test_num1 = 0;
void button_dowm(int i)
{
	if (button_LEFT.button_state == 1)
	{
		menu.ElemToLast();
	}

	if (button_RIGHT.button_state == 1)
	{
		menu.ElemToNext();
	}
	if (button_UP.button_state == 1)
	{
		menu.ElemToParent();
	}
	if (button_DOWN.button_state == 1)
	{
		menu.ElemToChild();
	}
}
void stickin(uint16_t x, uint16_t y)
{
	// LCD_ShowIntNum(10, 30, test_num1++, 4, RED, WHITE, 16);
	LCD_Fill(0, 0, 160, 80, BLACK);

	// 3.45v 1800
	// 3.54v 1860
	// 4.15v 1960

	// set HOME as awake trigger
	{
		LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
		LL_EXTI_InitTypeDef EXTI_InitStruct = {0};

		GPIO_InitStruct.Pin = HOME_Pin;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		LL_GPIO_Init(HOME_GPIO_Port, &GPIO_InitStruct);

		LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE5);

		EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_5;
		EXTI_InitStruct.LineCommand = ENABLE;
		EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
		EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
		LL_EXTI_Init(&EXTI_InitStruct);
	}

	LL_TIM_DisableCounter(TIM2);
	LL_TIM_DisableIT_UPDATE(TIM2);
	HAL_SuspendTick(); // 停止系统滴答计时器
	// CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);//失能系统滴答定时器
	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFE); // 电压调节器为低功耗模式，WFE指令进入停止模式
	SystemClock_Config();												// 重新配置系统时钟

	// SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);//使能系统滴答定时器
	HAL_ResumeTick(); // 恢复系统滴答计时器
	LCD_Fill(0, 0, 160, 80, WHITE);
	// set HOME back to input
	{
		LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

		GPIO_InitStruct.Pin = HOME_Pin;
		GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
		LL_GPIO_Init(HOME_GPIO_Port, &GPIO_InitStruct);
	}
	LL_TIM_EnableCounter(TIM2);
	LL_TIM_EnableIT_UPDATE(TIM2);
}

void button_update_test()
{
	// button_A.buttonStateUpdate();
	sticktest.StickStateUpdate();
}

void node_change(int i)
{
	LCD_Fill(0, 20, 160, 80, WHITE);
}
void gui_update()
{
	LCD_ShowIntNum(68, 30, menu.now_MenuElem->id, 2, RED, WHITE, 16);
	char battery_inf[10] = {0};
	snprintf(battery_inf, sizeof(battery_inf), "%3d%%", (int)(remap(180, 196, 0, 10, (float)(adc_vals[4] / 10))) * 10);
	LCD_ShowString(128, 0, (uint8_t *)battery_inf, GREEN, BLUE, 16, 0);
}
int maincpp(void)
{
	sticktest.EventRegister(stickin, 1000, 1000, sticktest.TOIN, 0);

	button_LEFT.buttonCallRegist(button_dowm, BTDown);
	button_UP.buttonCallRegist(button_dowm, BTDown);
	button_DOWN.buttonCallRegist(button_dowm, BTDown);
	button_RIGHT.buttonCallRegist(button_dowm, BTDown);

	menu.Add_Elem(1);
	menu.Add_Elem(2);
	// menu.Add_Elem(3);
	// menu.Add_Elem(4);
	// menu.Add_Elem(5);
	// menu.Add_Elem(5, 6);
	// menu.Add_Elem(5, 7);

	menu.now_MenuElem->ElemAnimator->AnimationStart();
	while (1)
	{
		gui_update();
		if (TIM1_FLAG == 1)
		{
			TIM1_FLAG = 0;
			menu.now_MenuElem->ElemAnimator->CalculateNextFrame();
			menu.now_MenuElem->m_x = menu.now_MenuElem->ElemAnimator->x_now;
			menu.now_MenuElem->m_y = menu.now_MenuElem->ElemAnimator->y_now;
			menu.now_MenuElem->DrawElem(Tile_Cube);

			// menu.now_MenuElem->m_x = 80;
			// menu.now_MenuElem->m_y = 40;
			// menu.now_MenuElem->DrawElem(Tile_Cube);
		}
	}

	return 0;
}

#ifdef __cplusplus

extern "C"
{
#endif

	void tim2_callback(void)
	{
		LL_TIM_ClearFlag_UPDATE(TIM2);
		TIM1_FLAG = 1;
		// !5ms的中断用于判断按键
		HAL_ADC_Start_DMA(&hadc1, (uint32_t *)adc_vals, 5);
		sticktest.dead_response = 500;
		sticktest.dir_x = adc_vals[0];
		sticktest.dir_y = adc_vals[1];

		button_update_test();
		button_state_update();

		uint32_t _gpio_state_a = LL_GPIO_ReadInputPort(GPIOA);
		uint32_t _gpio_state_b = LL_GPIO_ReadInputPort(GPIOB);
		uint32_t _gpio_state_c = LL_GPIO_ReadInputPort(GPIOC);
	}

#ifdef __cplusplus
}
#endif
