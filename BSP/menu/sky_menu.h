/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:29
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-05 14:13:16
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\sky_menu.h
 */
#ifndef MENU_H_
#define MENU_H_

#include "main.h"
#include "drawer.h"

#ifdef __cplusplus
extern "C"
{
#endif

#ifdef __cplusplus
}
#endif

class node
{
public:
    int id;
    node *father;
    node *child;
    node *left_node;
    node *right_node;

    Drawer node_drawer;

    node(int id) : id(id), node_drawer() {};
};

class NodeManager
{
public:
    int node_num = 0;
    int now_node_id = 0;
    node *now_node = nullptr;
    node *node_list[100] = {0};

    void add_node(node *now_node, node *father, node *child, node *left_node, node *right_node);
    void node_to_left() { now_node = now_node->left_node; }
    void node_to_right() { now_node = now_node->right_node; }
    void node_to_father() { now_node = now_node->father; }
    void node_to_child() { now_node = now_node->child; }
    // void node_find(int id);
    int node_check_num(void);   // 检查当前节点的兄弟节点有几个
    int node_check_order(void); // 检查当前节点处于兄弟节点的第几个
    int node_check_order(node *_node);
};

class Menu
{
public:
    NodeManager *node_manager = nullptr;

    node *now_node = nullptr;
    int menu_type = 0;

    // if the menu_type is tiles
    int Tile_num;
    int Tile_size = 30;
    int Tile_distence = 40;
    int menu_center[2] = {80, 40};

    Menu() {};
    Menu(NodeManager *node_manager) : node_manager(node_manager)
    {
        now_node = node_manager->now_node;
    };
    node *getNowNode()
    {
        return node_manager->now_node; // 始终获取 node_manager 的 now_node
    }

    void draw_menu(void);
};

#endif
