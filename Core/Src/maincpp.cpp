#ifdef __cplusplus

extern "C"
{
#endif

#include "maincpp.h"
#include "sky_button.h"
#include "sky_menu.h"
#include "drawer.h"
#include "lcd.h"
#include "joystick.h"

#include <stdio.h>
#include <cstdio>

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

	Menu menu = Menu();

	inline float remap(float x, float y, float x1, float y1, float value)
	{
		return x1 + (value - x) * (y1 - x1) / (y - x);
	}

	void InterfaceStateUpdate(void)
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

		Stick_L.StickStateUpdate();
		Stick_R.StickStateUpdate();
	}

	//*Button的注册函数
	void MenuElemSwitch(int i)
	{
		if (button_LEFT.button_state == BTDown)
		{
			menu.ElemToLast();
			LCD_ShowString(0, 60, (uint8_t *)menu.now_MenuElem->text, RED, WHITE, 16, 0);
		}

		if (button_RIGHT.button_state == BTDown)
		{
			menu.ElemToNext();
			LCD_ShowString(0, 60, (uint8_t *)menu.now_MenuElem->text, RED, WHITE, 16, 0);
		}
		if (button_UP.button_state == BTDown)
		{
			menu.ElemToParent();
			LCD_ShowString(0, 60, (uint8_t *)menu.now_MenuElem->text, RED, WHITE, 16, 0);
		}
		if (button_DOWN.button_state == BTDown)
		{
			menu.ElemToChild();
			LCD_ShowString(0, 60, (uint8_t *)menu.now_MenuElem->text, RED, WHITE, 16, 0);
		}
	}

	void MenuElemInAndOutFunction(int i)
	{
		if (button_START.button_state == BTDown)
		{
			menu.ElemInFunction();
		}
		if (button_BACK.button_state == BTDown)
		{
			menu.ElemOutFunction();
		}
	}

	// >3秒后进入休眠
	void McuToIdel(int i)
	{
		if (button_HOME.button_state == BTContinue && i >= 600)
		{
			LCD_Fill(0, 0, 160, 80, BLACK);

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

			menu.AnimaUpdate();
			menu.CallUpdate();
		}
	}
	//* 摇杆的注册函数
	// void McuToIdel(uint16_t x, uint16_t y)
	// {
	// 	LCD_Fill(0, 0, 160, 80, BLACK);

	// 	// set HOME as awake trigger
	// 	{
	// 		LL_GPIO_InitTypeDef GPIO_InitStruct = {0};
	// 		LL_EXTI_InitTypeDef EXTI_InitStruct = {0};

	// 		GPIO_InitStruct.Pin = HOME_Pin;
	// 		GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	// 		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	// 		LL_GPIO_Init(HOME_GPIO_Port, &GPIO_InitStruct);

	// 		LL_SYSCFG_SetEXTISource(LL_SYSCFG_EXTI_PORTA, LL_SYSCFG_EXTI_LINE5);

	// 		EXTI_InitStruct.Line_0_31 = LL_EXTI_LINE_5;
	// 		EXTI_InitStruct.LineCommand = ENABLE;
	// 		EXTI_InitStruct.Mode = LL_EXTI_MODE_EVENT;
	// 		EXTI_InitStruct.Trigger = LL_EXTI_TRIGGER_FALLING;
	// 		LL_EXTI_Init(&EXTI_InitStruct);
	// 	}

	// 	LL_TIM_DisableCounter(TIM2);
	// 	LL_TIM_DisableIT_UPDATE(TIM2);
	// 	HAL_SuspendTick(); // 停止系统滴答计时器
	// 	// CLEAR_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);//失能系统滴答定时器
	// 	HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFE); // 电压调节器为低功耗模式，WFE指令进入停止模式
	// 	SystemClock_Config();												// 重新配置系统时钟

	// 	// SET_BIT(SysTick->CTRL, SysTick_CTRL_ENABLE_Msk);//使能系统滴答定时器
	// 	HAL_ResumeTick(); // 恢复系统滴答计时器
	// 	LCD_Fill(0, 0, 160, 80, WHITE);
	// 	// set HOME back to input
	// 	{
	// 		LL_GPIO_InitTypeDef GPIO_InitStruct = {0};

	// 		GPIO_InitStruct.Pin = HOME_Pin;
	// 		GPIO_InitStruct.Mode = LL_GPIO_MODE_INPUT;
	// 		GPIO_InitStruct.Pull = LL_GPIO_PULL_UP;
	// 		LL_GPIO_Init(HOME_GPIO_Port, &GPIO_InitStruct);
	// 	}
	// 	LL_TIM_EnableCounter(TIM2);
	// 	LL_TIM_EnableIT_UPDATE(TIM2);
	// }

	// *menu的回调函数
	void GeDouBojiCallBack()
	{
		JoystickDataTransmit();
		// TODO  写help文档
	} 



	// *C++在C中的接口
	int MainCppInit(void)
	{
		// Stick_L.EventRegister(McuToIdel, 1000, 1000, Stick_L.TOIN, 0);
		// Stick_R.EventRegister(McuToIdel, 1000, 1000, Stick_L.TOIN, 0);
		button_HOME.buttonCallRegist(McuToIdel, BTContinue);

		button_LEFT.buttonCallRegist(MenuElemSwitch, BTDown);
		button_UP.buttonCallRegist(MenuElemSwitch, BTDown);
		button_DOWN.buttonCallRegist(MenuElemSwitch, BTDown);
		button_RIGHT.buttonCallRegist(MenuElemSwitch, BTDown);

		button_START.buttonCallRegist(MenuElemInAndOutFunction, BTDown);
		button_BACK.buttonCallRegist(MenuElemInAndOutFunction, BTDown);

		menu.Add_Elem(1, JoystickDataTransmit, "jinengsai");
		menu.Add_Elem(2, nullptr, "GeDouBoji");
		menu.Add_Elem(3, nullptr, "XBOX     ");

		menu.ElemToChild();
		LCD_ShowString(0, 60, (uint8_t *)menu.now_MenuElem->text, RED, WHITE, 16, 0);
		return 0;
	}

	int MainCppLoop(void)
	{
		Stick_L.dead_response = 500;
		Stick_L.dir_x = adc_vals[0];
		Stick_L.dir_y = adc_vals[1];
		Stick_R.dead_response = 500;
		Stick_R.dir_x = adc_vals[2];
		Stick_R.dir_y = adc_vals[3];

		// *timer1在C++中的回调
		if (TIM2_FLAG == 1)
		{
			TIM2_FLAG = 0;

			menu.AnimaUpdate();
			menu.CallUpdate();
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif
