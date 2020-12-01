#include "Graph.h"
using namespace std;
MazeNode::MazeNode(bool w)
{
    wall = w;
}
MazeNode::MazeNode(bool w, MazeNode* u, MazeNode* d, MazeNode* l, MazeNode* r)
{
    wall = w;
    up = u;
    down = d;
    left = l;
    right = r;
}
Maze::Maze(int w, int h)
{
    width = w;
    height = h;
    MazeNode* pleft = nullptr;
    MazeNode* pup = nullptr;
    for(int i = 0; i < width; i++)
    {
        MazeNode* topNode = nullptr;
        for(int x = 0; x < height; x++)
        {
            MazeNode* temp = new MazeNode(false);
            if(i==0&&x==0)
            {
                topLeft = temp;
            }
            if(pup == nullptr)
            {
                temp->up = nullptr;
                pup = temp;
            }
            else
            {
                temp->up = pup;
                pup->down = temp;
                pup = temp;
            }
            if(x==0)
            {
                topNode = temp;
            }
            if(pleft == nullptr)
            {
                temp->left = nullptr;
            }
            else
            {
                temp->left = pleft;
                pleft->right = temp;
                pleft = temp->left->down;
            }
            botLeft = temp;
        }
        pup = nullptr;
        pleft = topNode;
    }
    MazeNode* iterator = topLeft;
    iterator->wall = true;
    while (iterator->right != nullptr)
    {
        iterator = iterator->right;
        iterator->wall = true;
    }
    topRight = iterator;
    while (iterator->down != nullptr)
    {
        iterator = iterator->down;
        iterator->wall = true;
    }
    botRight = iterator;
    while (iterator->left != nullptr)
    {
        iterator = iterator->left;
        iterator->wall = true;
    }
    while (iterator->up != nullptr)
    {
        iterator = iterator->up;
        iterator->wall = true;
    }
    
    botLeft = iterator;
}
void Maze::print()
{
    MazeNode* iterator = topLeft;
    while(iterator!= nullptr)
    {
        MazeNode* hIterator = iterator;
        while (hIterator != nullptr)
        {
            cout<< hIterator->wall << " ";
            hIterator = hIterator->right;
        }
        iterator = iterator->down;
        cout << endl;
    }
}
int main(int argc, char const *argv[])
{
    Maze maze(10,10);
    maze.print();
    return 0;
}
