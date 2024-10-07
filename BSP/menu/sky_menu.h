/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:29
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-08 01:56:37
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
    node *last = nullptr;

    Drawer *ElemdDrawer;
    node(int id) : id(id)
    {
        ElemdDrawer = new Drawer();
    }
    void AddNode(node *parent);
    node *FindNode(node *rootnode, int id);
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

    int menu_type = 0;

    // if the menu_type is tiles
    int Tile_num;
    int Tile_size = 30;
    int Tile_distence = 40;
    int menu_center[2] = {80, 40};

    Menu() {};
};

#endif
