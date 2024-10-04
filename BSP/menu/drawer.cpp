#include "drawer.h"

void Drawer::draw_line(int x1, int y1, int x2, int y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; // 计算坐标增量
    delta_y = y2 - y1;
    uRow = x1; // 画线起点坐标
    uCol = y1;
    if (delta_x > 0)
        incx = 1; // 设置单步方向
    else if (delta_x == 0)
        incx = 0; // 垂直线
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; // 水平线
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; // 选取基本增量坐标轴
    else
        distance = delta_y;
    for (t = 0; t < distance + 1; t++)
    {
        if (uRow >= 0 && uRow <= display_size_x && uCol >= 0 && uCol <= display_size_y) // 检查是否在屏幕范围内
        {
            this->pointdraw(uRow, uCol, color); // 在当前点位置画点
        }
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

void Drawer::draw_cube(int x, int y, int length, int border_width, uint16_t color)
{
    int x0 = x - length / 2;
    int y0 = y - length / 2;
    int x1 = x + length / 2;
    int y1 = y + length / 2;

    for (int i = 0; i < border_width; i++)
    {
        draw_line(x0 + i, y0 + i, x1 - i, y0 + i, color);
        draw_line(x0 + i, y0 + i, x0 + i, y1 - i, color);
        draw_line(x1 - i, y0 + i, x1 - i, y1 - i, color);
        draw_line(x0 + i, y1 - i, x1 - i, y1 - i, color);
    }
}

void Drawer::draw_circle(int xc, int yc, int r, int width, uint16_t color)
{
    int outer_radius = r;
    int inner_radius = r - width;

    for (int radius = outer_radius; radius > inner_radius; --radius)
    {
        int x = radius;
        int y = 0;
        int err = 1 - radius;

        while (x >= y)
        {
            auto plot_point = [&](int px, int py)
            {
                if (px >= 0 && px < display_size_x && py >= 0 && py < display_size_y)
                {
                    this->pointdraw(px, py, color);
                }
            };

            plot_point(xc + x, yc + y);
            plot_point(xc + y, yc + x);
            plot_point(xc - y, yc + x);
            plot_point(xc - x, yc + y);
            plot_point(xc - x, yc - y);
            plot_point(xc - y, yc - x);
            plot_point(xc + y, yc - x);
            plot_point(xc + x, yc - y);

            y++;

            if (err <= 0)
            {
                err += 2 * y + 1;
            }
            else
            {
                x--;
                err += 2 * (y - x) + 1;
            }
        }
    }
}