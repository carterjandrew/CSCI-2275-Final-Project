#include <vector>
using namespace std;
#ifndef QUEUE_H
#define QUEUE_H
struct BranchPossibility{
    public:
    int offset;
    int dir;//follows same rules
    bool valid;
    BranchPossibility();
    BranchPossibility(int o, int d);
};
struct StackNode
{
    public:
    int size;
    int x = -1;
    int y = -1;
    int dir = -1;//follows same rules as outlined in the graph
    StackNode* next;
    StackNode* prev;
    BranchPossibility* branches;
    StackNode(int xpos, int ypos, int dir, int size);
};
class Stack
{
    private:
    StackNode* head = nullptr;
    public:
        int size;
        void push(int x, int y, int dir, int size);
        void pop();
        StackNode top();//Array with x, y, dir
        void changeBranch(bool valid, int i);
        Stack();
        bool isEmpty();
};
#endif