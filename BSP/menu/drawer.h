/*
 * @Author: skybase
 * @Date: 2024-10-04 10:13:48
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-04 11:20:21
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\drawer.h
 */
#ifndef DRAWER_H_
#define DRAWER_H_

#include "main.h"
#include "lcd.h"

class Drawer
{
public:
    typedef void (*PointdrawCall)(uint16_t, uint16_t, uint16_t);

    PointdrawCall pointdraw = LCD_DrawPoint;
    int display_size_x = 180;
    int display_size_y = 60;
    Drawer() {};
    Drawer(PointdrawCall pointcall)
    {
        this->pointdraw = pointcall;
    };

    void draw_line(int x1, int y1, int x2, int y2, uint16_t color);
    void draw_cube(int x, int y, int length, int width, uint16_t color);
    void draw_circle(int x, int y, int r, int width, uint16_t color);
};

#endif
