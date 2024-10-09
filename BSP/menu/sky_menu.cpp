/*
 * @Author: skybase
 * @Date: 2024-10-02 15:53:09
 * @LastEditors: skybase
 * @LastEditTime: 2024-10-09 22:24:50
 * @Description:  ᕕ(◠ڼ◠)ᕗ​
 * @FilePath: \MDK-ARMd:\Project\Embedded_project\Stm_pro\joystick_Beitong\BSP\menu\sky_menu.cpp
 */
#include "sky_menu.h"

void Animation::SetFps(int _fps)
{
    fps = _fps;
    exeCount = 1000 / _fps * timerPhase;
}
void Animation::SetSpeed(float spd)
{
    LinearSpeed = spd;
}
void Animation::SetAnimation(int ex, int ey)
{
    x_target = ex;
    y_target = ey;
}
void Animation::CalculateNextFrame(Interpolation_Type type)
{
    if (type == Linear)
    {
        if (countNow++ > exeCount)
        {
            x_now += (x_target - x_now) * LinearSpeed;
            y_now += (y_target - y_now) * LinearSpeed;
            countNow = 0;
        }
    }
}

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

void node::DrawElem(Elem_type type)
{
    m_x = ElemAnimator->x_now;
    m_y = ElemAnimator->y_now;
    if (type == Tile_Cube)
    {
        ElemDrawer->DrawCube(m_x, m_y, m_length, m_width, BLACK);
    }
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
        menuRoot = rootElem;
        now_MenuElem = rootElem;
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

int Menu::ElemNumCheck(node *elem)
{
    int num = 1;
    if (elem->parent == nullptr)
        return 0; // 说明这是根节点,不进行操作
    node *firstElem = elem->parent->children;
    while (firstElem->next != nullptr)
    {
        num++;
        firstElem = firstElem->next;
    }
    return num;
}

int Menu::ELemOrderCheck(node *elem)
{
    int num = 0;
    if (elem->parent == nullptr)
        return 0; // 根节点不进行操作

    node *nowElem = elem->parent->children;

    while (nowElem != nullptr && nowElem != elem)
    {
        num++;
        nowElem = nowElem->next;
    }

    if (nowElem == nullptr)
    {
        return -1; // 元素未在父节点的子节点列表中找到
    }

    return num;
}

void Menu::AnimaCla()
{
    node *_Elem = now_MenuElem->parent->children;
    int num = ElemNumCheck(now_MenuElem);
    int order = ELemOrderCheck(now_MenuElem);
    for (int i = 0; i < num; i++)
    {
        _Elem->ElemAnimator->x_target = menu_center[0] + Tile_distence * (i - order);
        _Elem->ElemAnimator->y_target = menu_center[1];
        if (_Elem->next != nullptr)
            _Elem = _Elem->next;
    }
}

void Menu::AnimaUpdate()
{
    node *_Elem = now_MenuElem->parent->children;
    int num = ElemNumCheck(now_MenuElem);

    for (int i = 0; i < num; i++)
    {
        _Elem->ElemAnimator->CalculateNextFrame(Linear);
        _Elem->DrawElem(Tile_Cube);
        if (_Elem->next != nullptr)
            _Elem = _Elem->next;
    }
}