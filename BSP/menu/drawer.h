/*
 * @Author: skybase
 * @Date: 2024-10-04 10:13:48
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-05 16:26:53
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\drawer.h
 */
#ifndef DRAWER_H_
#define DRAWER_H_

#include "main.h"
#include "lcd.h"

typedef enum
{
    Overwrite = 0,
} drawer_enum;

class Drawer
{
public:
    typedef void (*PointdrawCall)(uint16_t, uint16_t, uint16_t);

    PointdrawCall pointdraw = LCD_DrawPoint;
    // uint16_t LCD_GRAM[160][80] = {0};

    int background_color = WHITE;
    int display_size_x = 160;
    int display_size_y = 80;
    Drawer() {};
    Drawer(PointdrawCall pointcall)
    {
        this->pointdraw = pointcall;
        for (int i = 0; i < display_size_x; ++i)
        {
            for (int j = 0; j < display_size_y; ++j)
            {
                //LCD_GRAM[i][j] = background_color;
            }
        }
    };

    void lcd_update();
    void lcd_draw(int x, int y, uint16_t color);

    void draw_line(int x1, int y1, int x2, int y2, uint16_t color);
    void draw_line(int x1, int y1, int x2, int y2, uint16_t color, drawer_enum mode);
    void draw_cube(int x, int y, int length, int width, uint16_t color);
    void draw_cube(int x, int y, int length, int width, uint16_t color, drawer_enum mode);
    void draw_circle(int x, int y, int r, int width, uint16_t color);

    
private:
    int last_cube_x = 0;
    int last_cube_y = 0;
    int last_cube_length = 0;
    int last_cube_width = 0;
};

#endif
