#include "Stack.h"
#include <iostream>
BranchPossibility::BranchPossibility(int o, int d)
{
    offset = o; 
    dir = d;
    valid = true;
}
BranchPossibility::BranchPossibility()
{
    offset = -1;
    dir = -1;
    valid = true;
}
StackNode::StackNode(int xpos, int ypos, int d, int s)
{
    x = xpos;
    y = ypos;
    dir = d;
    size = s;
    branches = new BranchPossibility[size * 2];
    for(int i = 0; i < (size-1) * 2; i+=2)
    {
        switch (d)
        {
        case 0:
            branches[i].dir = 2;
            branches[i+1].dir = 3;
            branches[i].offset = i/2;
            branches[i+1].offset = i/2;
            break;
        case 1:
            branches[i].dir = 2;
            branches[i+1].dir = 3;
            branches[i].offset = i/2;
            branches[i+1].offset = i/2;
            break;
        case 2:
            branches[i].dir = 0;
            branches[i+1].dir = 1;
            branches[i].offset = i/2;
            branches[i+1].offset = i/2;
            break;
        case 3:
            branches[i].dir = 0;
            branches[i+1].dir = 1;
            branches[i].offset = i/2;
            branches[i+1].offset = i/2;
            break;
        }

    }
}
Stack::Stack()
{
    size = 0;
}
void Stack::push(int x, int y, int dir, int s)
{
    size++;
    if(head == nullptr)
    {
        head = new StackNode(x,y,dir,s);
        head->next = nullptr;
        head->prev = nullptr;
        return;
    }
    StackNode* temp = new StackNode(x,y,dir,s);
    temp->next = head;
    head->prev = temp;
    temp->prev = nullptr;
    head = temp;
}
void Stack::pop()
{
    if(size == 0)
    {
        return;
    }
    if(size == 1)
    {
        delete head;
        size--;
        head = nullptr;
        return;
    }
    size--;
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
}
StackNode Stack::top()
{
    if(size == 0)
    {
        return *new StackNode(-1,-1,-1,-1);
    }
    return *head;
}
/*
int* Stack::topBranch(int i)
{
    if(size == 0)
    {
        int retval[] = {-1,-1,-1};
        return retval;
    }
    switch (head->dir)
    {
    case 0:
        int retval[] = {head->x, head->y - head->branches[i].offset, head->branches[i].dir};
        return retval;
        break;
    case 1:
        int retval[] = {head->x, head->y + head->branches[i].offset, head->branches[i].dir};
        return retval;
        break;
    case 2:
        int retval[] = {head->x - head->branches[i].offset, head->y, head->branches[i].dir};
        return retval;
        break;
    case 3:
        int retval[] = {head->x + head->branches[i].offset, head->y, head->branches[i].dir};
        return retval;
        break;
    }
    int retval[] = {-1,-1,-1};
    return retval;
}
*/
void Stack::changeBranch(bool valid, int i)
{
    head->branches[i].valid == 0;
}
bool Stack::isEmpty()
{
    return(size == 0);
}