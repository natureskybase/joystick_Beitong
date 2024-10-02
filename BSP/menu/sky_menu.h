/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:29
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-02 19:40:03
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\sky_menu.h
 */
#ifndef MENU_H_
#define MENU_H_

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

    node(int id) { this->id = id; }
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
};

#endif
