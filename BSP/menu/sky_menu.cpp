/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:09
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-02 19:36:57
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
