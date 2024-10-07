/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:09
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-08 01:53:23
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
        this->last = sibling;
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
    node *newElem = new node(id);

    if (elemNum == 0)
    {
        node *rootElem = new node(255);
        menuRoot = rootElem;
        now_MenuElem = rootElem;
    }
    newElem->AddNode(menuRoot);
    elemNum++;
}

void Menu::Add_Elem(int parentId, int id)
{
    node *newElem = new node(id);

    if (elemNum == 0)
    {
        node *rootElem = new node(255);
        rootElem->AddNode(nullptr);
        menuRoot = rootElem;
    }
    else
    {
        node *parentElem = FindElem(parentId);
        newElem->AddNode(parentElem);
        elemNum++;
    }
}

void Menu::ElemToNext()
{
    if (now_MenuElem->next != nullptr)
    {
        now_MenuElem = now_MenuElem->next;
    }
    else
    {
        if (now_MenuElem->parent != nullptr)
        {
            now_MenuElem = now_MenuElem->parent->children;
        }
    }
}

void Menu::ElemToLast()
{
    if (now_MenuElem->last != nullptr)
    {
        now_MenuElem = now_MenuElem->last;
    }
    else
    {
        if (now_MenuElem->parent != nullptr)
        {
            node *temp = now_MenuElem->parent->children;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            now_MenuElem = temp;
        }
    }
}
void Menu::ElemToParent()
{
    if (now_MenuElem->parent != nullptr)
    {
        now_MenuElem = now_MenuElem->parent;
    }
}
void Menu::ElemToChild()
{
    if (now_MenuElem->children != nullptr)
    {
        now_MenuElem = now_MenuElem->children;
    }
}

node *Menu::FindElem(int id)
{
    node *_elem = menuRoot->FindNode(menuRoot, id);
    return (_elem);
}

node *Menu::LocateElem(int id)
{
    node *_elem = menuRoot->FindNode(menuRoot, id);
    now_MenuElem = _elem;
    return (_elem);
}
