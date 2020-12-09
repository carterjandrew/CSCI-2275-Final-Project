#include "Stack.h"
#include <iostream>
//Set up a branch with the essentials, a offset from starting point and a direction. 
BranchPossibility::BranchPossibility(int o, int d)
{
    offset = o; 
    dir = d;
    //We assume new branches being entered are valid. 
    valid = true;
}
//Otherwise we set it up to have -1, an indicator we have yet to set up our maze. 
BranchPossibility::BranchPossibility()
{
    offset = -1;
    dir = -1;
    valid = true;
}
//More initialisations, a stackNode holds all the possible branchPossibilitys as well as the coordinates of the wall it represents. 
//We have to initialise all of the branch possibilitys in the correct direction.
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
//All we need when making our actual stack is to set the size. All other pointers are allready set to nullptr
Stack::Stack()
{
    size = 0;
}
//Pushing initialises a new stackNode at the start and sets our head to the new node
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
//We take off the top node, notice there is no return because we do not want to pop every time we acess the top value
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
//This actually returns the top node so we can use it in our recursive division function
StackNode Stack::top()
{
    if(size == 0)
    {
        return *new StackNode(-1,-1,-1,-1);
    }
    return *head;
}
//This was not needed in the final implimentation. I planned on loading in beaches seperately to make a recursive structure
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
//As you can guess this updates the validity of a specific branch to false. Once a branch is false it will never be true again so we dont have the option to turn it back.
void Stack::changeBranch(bool valid, int i)
{
    head->branches[i].valid = 0;
}
//Checks if our stack is empty
bool Stack::isEmpty()
{
    return(size == 0);
}