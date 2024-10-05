/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:09
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-05 14:57:13
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\sky_menu.cpp
 */
#include "sky_menu.h"

void NodeManager::add_node(node *now_node, node *father, node *child, node *left_node, node *right_node)
{
    this->node_list[this->node_num] = now_node;
    now_node->child = child;
    now_node->father = father;
    now_node->left_node = left_node;
    now_node->right_node = right_node;
    this->node_num++;
}

int NodeManager ::node_check_num()
{
    node *_node = now_node;
    int id = _node->id;
    int num = 1;

    int _safe_count = 100;
    while (_safe_count--)
    {
        _node = _node->left_node;
        if (_node->id != id)
        {
            num++;
        }
        else
        {
            break;
        }
    }
    return num;
}

/// @brief 单纯根据兄弟节点之间的id大小进行排序
/// @brief 顺序由0开始计算
/// @return
int NodeManager::node_check_order()
{
    int order = 0;
    node *_node = now_node;
    int num = node_check_num();
    for (int i = 0; i < num; i++)
    {
        if (_node->left_node->id <= _node->id) // 反转遍历顺序
        {
            break;
        }
        _node = _node->left_node;
        order++;
    }
    return order;
}

int NodeManager::node_check_order(node *_node_)
{
    int order = 0;
    node *_node = _node_;
    int num = node_check_num();
    int order_count = 0;
    for (int i = 0; i < num; i++)
    {
        if (_node->left_node->id > _node->id)
        {
            break;
        }
        order++;
        _node = _node->left_node;
    }
    return order;
}

void Menu::draw_menu(void)
{
    node *_node = node_manager->now_node;
    int num = node_manager->node_check_num();
    int now_ordor = node_manager->node_check_order(_node);

    for (int i = 0; i < num; i++)
    {
        int order = node_manager->node_check_order(_node);
        _node->node_drawer.draw_cube(menu_center[0] + (order - now_ordor) * Tile_distence, menu_center[1], Tile_size, 2, BLACK, Overwrite);
        _node = _node->right_node;
        if (_node == nullptr)
            break;
    }
}