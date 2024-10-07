/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:09
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-08 01:01:06
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\sky_menu.cpp
 */
#include "sky_menu.h"

void node::AddNode(node *parent)
{
    this->parent = parent;

    if (parent->children == nullptr)
    {
        // 如果父节点没有子节点，则直接将新节点作为第一个子节点
        parent->children = this;
    }
    else
    {
        // 如果已有子节点，遍历到最后一个子节点，插入新节点
        node *sibling = parent->children;
        while (sibling->next != nullptr)
        {
            sibling = sibling->next;
        }
        sibling->next = this;
    }
}
node *node::FindNode(node *rootnode, int id)
{
    if (rootnode == nullptr)
    {
        return nullptr; // 如果当前节点为空，返回空指针
    }
    if (rootnode->id == id)
    {
        return rootnode; // 如果找到目标节点，返回该节点
    }
    // 递归在子节点中查找
    node *result = FindNode(rootnode->children, id);
    if (result != nullptr)
    {
        return result; // 如果在子节点中找到，返回结果
    }

    // 如果当前节点的子节点中没找到，在兄弟节点中继续查找
    return FindNode(rootnode->next, id);
}

void Menu::Add_Elem(int id)
{
    node* newElem = new node(id);

    if (elemNum == 0)
    {
        node* rootElem = new node(255);
        rootElem->AddNode(nullptr);
        menuRoot = rootElem;
    }
    newElem->AddNode(menuRoot);
    elemNum++;
}

node *Menu::Find_Elem(int id)
{
    node *_elem = menuRoot->FindNode(menuRoot, id);
    return (_elem);
}