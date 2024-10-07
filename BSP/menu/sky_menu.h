/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:29
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-08 01:05:03
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\sky_menu.h
 */
#ifndef MENU_H_
#define MENU_H_

#include "main.h"
#include "drawer.h"


class node
{
public:
    int id;
    node *parent = nullptr;
    node *children = nullptr;
    node *next = nullptr;

    node(int id) : id(id) {};
    void AddNode(node *parent);
    node *FindNode(node *rootnode, int id);
};

class Menu
{
public:
    Drawer *drawer = nullptr;

    node *now_MenuElem = nullptr;
    node *menuRoot = nullptr;
    int elemNum = 0;

    void Add_Elem(int id);
    node *Find_Elem(int id);

    int menu_type = 0;

    // if the menu_type is tiles
    int Tile_num;
    int Tile_size = 30;
    int Tile_distence = 40;
    int menu_center[2] = {80, 40};

    Menu() {};
    Menu(Drawer *drawer) : drawer(drawer) {};

};

#endif
