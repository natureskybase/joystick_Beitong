/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:29
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-09 17:37:53
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\sky_menu.h
 */
#ifndef MENU_H_
#define MENU_H_

#include "main.h"
#include "drawer.h"

typedef enum
{
    Linear = 0,
} Interpolation_Type;

// typedef enum
// {
//     AnimaNone = 0,
//     AnimaStart,
//     AnimaContinu,
//     AnimaEnd,
// } AnimaStateType;

class Animation
{
public:
    int fps = 60;
    uint32_t timerPhase = 5; // 用于刷屏的定时器周期 (以毫秒为单位)
    int exeCount = 3;
    int countNow = 0;

    float LinearSpeed = 0.15; //(像素/ms)

    int x_target = 160;
    int y_target = 40;

    int x_now;
    int y_now;

    Animation() {};
    Animation(int fps, uint32_t timerPhase) : fps(fps), timerPhase(timerPhase) {};
    void SetFps(int _fps);
    void SetSpeed(float spd);
    void SetAnimation(int ex, int ey);
    void CalculateNextFrame(Interpolation_Type type);
};

typedef enum
{
    Tile_Cube = 0,
    Tile_Circle,
} Elem_type;

class node
{
public:
    int id;
    node *parent = nullptr;
    node *children = nullptr;
    node *next = nullptr;
    node *last = nullptr;

    Drawer *ElemDrawer;
    Elem_type elem_type = Tile_Cube;
    int m_x = 0;
    int m_y = 0;
    int m_length = 30;
    int m_width = 3;

    Animation *ElemAnimator;

    typedef void (*NodeCall)(void);
    NodeCall eventCallBack = nullptr;
    node(int id) : id(id)
    {
        ElemDrawer = new Drawer();
        ElemAnimator = new Animation();
    }
    void AddNode(node *parent);
    node *FindNode(node *rootnode, int id);
    void DrawElem(Elem_type type);
};

class Camera
{
    int x = 80;
    int y = 40;

    Camera() {};
    Camera(int x, int y) : x(x), y(y) {};
};

class Menu
{
public:
    node *now_MenuElem = nullptr;
    node *menuRoot = nullptr;
    int elemNum = 0;

    void Add_Elem(int id);
    void Add_Elem(int parentId, int id);
    void ElemToNext();
    void ElemToLast();
    void ElemToParent();
    void ElemToChild();
    node *FindElem(int id);
    node *LocateElem(int id);

    int ElemNumCheck(node *elem);
    int ELemOrderCheck(node *elem);
    void AnimaCla();
    void AnimaUpdate();

    // if the menu_type is tiles
    int Tile_num;
    int Tile_size = 30;
    int Tile_distence = 40;
    int menu_center[2] = {80, 40};

    Menu() {};
};

#endif
