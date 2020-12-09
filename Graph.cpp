#include "Graph.h"
#include "Stack.h"
//#include <fstream>
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
    botLeft = iterator;
    while (iterator->up != nullptr)
    {
        iterator = iterator->up;
        iterator->wall = true;
    }
}
void Maze::print()
{
    MazeNode* iterator = topLeft;
    while(iterator!= nullptr)
    {
        MazeNode* hIterator = iterator;
        while (hIterator != nullptr)
        {
            if(hIterator == start)
            {
                cout <<  "SS";
            }
            else if(hIterator == end)
            {
                cout <<  "EE";
            }
            else if(hIterator->path == true)
            {
                cout <<  "PP";
            }
            else if(hIterator->wall)
            {
                cout << "WW";
            }
            else
            {
                cout << "  ";
            }
            
            hIterator = hIterator->right;
        }
        iterator = iterator->down;
        cout << endl;
    }
}
string Maze::textMaze()
{
    MazeNode* iterator = topLeft;
    string output = "";
    while(iterator!= nullptr)
    {
        MazeNode* hIterator = iterator;
        while (hIterator != nullptr)
        {
            
            if(hIterator == start)
            {
                output += "SS";
            }
            else if(hIterator == end)
            {
                output += "EE";
            }
            else if(hIterator->path == true)
            {
                output += "PP";
            }
            else if(hIterator->wall)
            {
                output += "WW";
            }
            else
            {
                output += "  ";
            }
            
            hIterator = hIterator->right;
        }
        iterator = iterator->down;
        output += "\n";
    }
    return output;
}
MazeNode* move(MazeNode* start, int d, int dist)
{
    switch (d)
    {
    case 0:
        for(int i = 0; i < dist; i++)
        {
            start = start->up;
        }
        break;
    case 1:
        for(int i = 0; i < dist; i++)
        {
            start = start->down;
        }
        break;
    case 2:
        for(int i = 0; i < dist; i++)
        {
            start = start->left;
        }
        break;
    case 3:
        for(int i = 0; i < dist; i++)
        {
            start = start->right;
        }
        break;
    default:
        break;
    }
    return start;
}

int Maze::probeDepth(MazeNode* start, int dir)
{
    //0 means up
    //1 means down
    //2 means left
    //3 means right
    int dist = 0;
    switch (dir)
    {
    case 0:
        while (start->up != nullptr && !start->wall)
        {
            dist++;
            start = start->up;
        }
        break;
    case 1:
        while (start->down != nullptr && !start->wall)
        {
            dist++;
            start = start->down;
        }
        break;
    case 2:
        while (start->left != nullptr && !start->wall)
        {
            dist++;
            start = start->left;
        }
        break;
    case 3:
        while (start->right != nullptr && !start->wall)
        {
            dist++;
            start = start->right;
        }
    }
    return dist;
}
MazeNode* Maze::getNode(int x, int y)
{
    if(x > width || y > height)
    {
        return nullptr;
    }
    MazeNode* iterator = topLeft;
    for(int i = 0; i < x; i++)
    {
        iterator = iterator->right;
    }
    for(int i = 0; i < y; i++)
    {
        iterator = iterator->down;
    }
    return iterator;
}
void Maze:: makeWall(MazeNode* start, int dir)
{
    int dist = probeDepth(start,dir);
    int hole = (int)rand() % dist;
    for(int i = 0; i < dist; i++)
    {
        if(i != hole)
        {
            start->wall = true;
        }
        switch (dir)
        {
        case 0:
            start = start->up;
            break;
        case 1:
            start = start->down;
            break;
        case 2:
            start = start->left;
            break;
        case 3:
            start = start->right;
            break;
        }
    }
}
bool Maze::checkValid(MazeNode* start, int dir)
{
    //bool valid = true;
    MazeNode* moved = move(start, dir, 1);
    int dist = probeDepth(moved, dir);
    if(dist < 2)
    {
        return false;
    }
    switch (dir)
    {
    case 0:
        start = start->up;
        if(!start->down->wall)
        {
            return false;
        }
        for(int i = 0; i < dist; i++)
        {
            if(start->left->wall || start->right->wall)
            {
                return false;
            }
            start = start->up;
        }
        break;
    case 1:
        start = start->down;
        if(!start->up->wall)
        {
            return false;
        }
        for(int i = 0; i < dist; i++)
        {
            if(start->left->wall || start->right->wall)
            {
                return false;
            }
            start = start->down;
        }
        break;
    case 2:
        start = start->left;
        if(!start->right->wall)
        {
            return false;
        }
        for(int i = 0; i < dist; i++)
        {
            if(start->up->wall || start->down->wall)
            {
                return false;
            }
            start = start->left;
        }
        break;
    case 3:
        start = start->right;
        if(!start->left->wall)
        {
            return false;
        }
        for(int i = 0; i < dist; i++)
        {
            if(start->up->wall || start->down->wall)
            {
                return false;
            }
            start = start->right;
        }
        break;
    }
    return true;
}
xy Maze::getCoords(MazeNode* node)
{
    xy retVal;
    while (node->up != nullptr)
    {
        retVal.y++;
        node = node->up;
    }
    while (node->left != nullptr)
    {
        retVal.x++;
        node = node->left;
    }
    return retVal;
}
void Maze::resetMaze()
{
    for(int i = 1; i < height - 1; i++)
    {
        MazeNode* iterator = move(topLeft, 1, i);
        iterator = iterator->right;
        for(int z = 1; z < width - 1; z++)
        {
            iterator->wall = false;
            iterator = iterator->right;
        }
    }
}
void Maze::resizeMaze(int w, int h)
{
    if(w < width)
    {
        MazeNode* iterator = topRight;
        for(int i = 0; i < width - w; i++)
        {
            MazeNode* left = iterator->left;
            for(int x = 0; x < height; x++)
            {
                MazeNode* down = iterator->down;
                MazeNode* anotherLeft = iterator->left;
                anotherLeft->right = nullptr;
                if(down != nullptr)
                {
                    down->up = nullptr;
                }
                delete iterator;
                iterator = down;
            }
            iterator = left;
            topRight = left;
        }
        iterator = topRight;
        for(int i = 0; i < height; i++)
        {
            iterator->wall = true;
            iterator = iterator->down;
        }
    }
    else if(w > width)
    {
        MazeNode* iterator;
        for(int i = 0; i < w-width; i++)
        {
            iterator = topRight;
            for(int x = 0; x < height; x++)
            {
                iterator->right = new MazeNode(true);
                iterator->right->left = iterator;
                if(iterator->up != nullptr)
                {
                    iterator->up->right->down = iterator->right;
                    iterator->right->up = iterator->up->right;
                }
                iterator = iterator->down;
            }
            topRight = topRight->right;
            botRight = botRight->right;
        }
        iterator = topRight;
        for(int i = 0; i < height; i++)
        {
            iterator->wall = true;
            iterator = iterator->down;
        }
    }
    width = w;
    if(h < height)
    {
        MazeNode* iterator = botLeft;
        for(int i = 0; i < height - h; i++)
        {
            iterator = botLeft;
            botLeft = botLeft->up;
            for(int x = 0; x < width; x++)
            {
                MazeNode* up = iterator->up;
                MazeNode* right = iterator->right;
                up->down = nullptr;
                delete iterator;
                iterator = right;
            }
        }
        iterator = botLeft;
        for(int i = 0; i < width; i++)
        {
            iterator->wall = true;
            iterator = iterator->right;
        }
        height = h;
    }
    else if(h > height)
    {
        MazeNode* iterator;
        for(int i = 0; i < h-height; i++)
        {
            iterator = botLeft;
            for(int x = 0; x < width; x++)
            {
                iterator->down = new MazeNode(true);
                iterator->down->up = iterator;
                if(iterator->left != nullptr)
                {
                    iterator->left->down->right = iterator->down;
                    iterator->down->left = iterator->left->down;
                }
                iterator = iterator->right;
            }
            botLeft = botLeft->down;
            botRight = botRight->down;
        }
        iterator = botLeft;
        for(int i = 0; i < width; i++)
        {
            iterator->wall = true;
            iterator = iterator->right;
        }
    }
    height = h;
}
void Maze::recursiveDivision()
{
    resetMaze();
    int startX = 1;
    int startY = (int)rand() % (height-1)+1;
    MazeNode* startNode = getNode(startX, startY);
    Stack branchCommands;
    branchCommands.push(startX,startY,3, probeDepth(startNode, 3));
    makeWall(startNode, 3);
    while(!branchCommands.isEmpty())
    {
        //First we need to update all the possible branches
        StackNode currentBranch = branchCommands.top();
        vector<BranchPossibility> validsBranches;
        switch (currentBranch.dir)
        {
        case 0:
            for(int i = 0; i < currentBranch.size * 2; i++)
            {
                MazeNode* temp = getNode(currentBranch.x, currentBranch.y - currentBranch.branches[i].offset);
                currentBranch.branches[i].valid = checkValid(temp, currentBranch.branches[i].dir);
                if(currentBranch.branches[i].valid)
                {
                    validsBranches.push_back(currentBranch.branches[i]);
                }
            }
            break;
        case 1:
            for(int i = 0; i < currentBranch.size * 2; i++)
            {
                MazeNode* temp = getNode(currentBranch.x, currentBranch.y + currentBranch.branches[i].offset);
                currentBranch.branches[i].valid = checkValid(temp, currentBranch.branches[i].dir);
                if(currentBranch.branches[i].valid)
                {
                    validsBranches.push_back(currentBranch.branches[i]);
                }
            }
            break;
        case 2:
            for(int i = 0; i < currentBranch.size * 2; i++)
            {
                MazeNode* temp = getNode(currentBranch.x - currentBranch.branches[i].offset, currentBranch.y);
                currentBranch.branches[i].valid = checkValid(temp, currentBranch.branches[i].dir);
                if(currentBranch.branches[i].valid)
                {
                    validsBranches.push_back(currentBranch.branches[i]);
                }
            }
            break;
        case 3:
            for(int i = 0; i < currentBranch.size * 2; i++)
            {
                MazeNode* temp = getNode(currentBranch.x + currentBranch.branches[i].offset, currentBranch.y);
                currentBranch.branches[i].valid = checkValid(temp, currentBranch.branches[i].dir);
                if(currentBranch.branches[i].valid)
                {
                    validsBranches.push_back(currentBranch.branches[i]);
                }
            }
            break;
        }
        //If there is nowhere else to split off with the branch then we shouldnt look at that branch anymore
        if(validsBranches.size() == 0)
        {
            branchCommands.pop();
        }
        else
        {
            int nextBranch = (int) rand() % validsBranches.size();
            xy updated;
            int depth;
            MazeNode* currentNode;
            int x;
            int y;
            switch (currentBranch.dir)
            {
            case 0:
                x = currentBranch.x;
                y = currentBranch.y - validsBranches[nextBranch].offset;
                currentNode = getNode(x,y);
                currentNode = move(currentNode, validsBranches[nextBranch].dir, 1);
                depth = probeDepth(currentNode, validsBranches[nextBranch].dir);
                makeWall(currentNode, validsBranches[nextBranch].dir);
                branchCommands.push(x,y,validsBranches[nextBranch].dir, depth);
                break;
            case 1: 
                x = currentBranch.x;
                y = currentBranch.y + validsBranches[nextBranch].offset;
                currentNode = getNode(x,y);
                currentNode = move(currentNode, validsBranches[nextBranch].dir, 1);
                depth = probeDepth(currentNode, validsBranches[nextBranch].dir);
                makeWall(currentNode, validsBranches[nextBranch].dir);
                branchCommands.push(x,y,validsBranches[nextBranch].dir, depth);
                break;
            case 2:
                x = currentBranch.x - validsBranches[nextBranch].offset;
                y = currentBranch.y;
                currentNode = getNode(x,y);
                currentNode = move(currentNode, validsBranches[nextBranch].dir, 1);
                depth = probeDepth(currentNode, validsBranches[nextBranch].dir);
                makeWall(currentNode, validsBranches[nextBranch].dir);
                branchCommands.push(x,y,validsBranches[nextBranch].dir, depth);
                break;
            case 3:
                x = currentBranch.x + validsBranches[nextBranch].offset;
                y = currentBranch.y;
                currentNode = getNode(x,y);
                currentNode = move(currentNode, validsBranches[nextBranch].dir, 1);
                depth = probeDepth(currentNode, validsBranches[nextBranch].dir);
                makeWall(currentNode, validsBranches[nextBranch].dir);
                branchCommands.push(x,y,validsBranches[nextBranch].dir, depth);
                break;
            }
        }
    }
}
void Maze::setEnd(int x, int y)
{
    if(getNode(x,y)->wall)
    {
        cout << "The coordinate you entered is a wall, please enter a non wall coordinate.";
    }
    else
    {
        end = getNode(x,y);
    }
}
void Maze::setStart(int x, int y)
{
    if(getNode(x,y)->wall)
    {
        cout << "The coordinate you entered is a wall, please enter a non wall coordinate.";
    }
    else
    {
        start = getNode(x,y);
    }
}
void Maze::BFS(MazeNode* current, int dist)
{
    current->visited = true;
    current->dist = dist;
    if((!current->left->visited && !current->left->wall) || current->left->dist > dist)
    {
        current->left->prev = current;
        BFS(current->left, dist + 1);
    }
    if((!current->right->visited && !current->right->wall) || current->right->dist > dist)
    {
        current->right->prev = current;
        BFS(current->right, dist + 1);
    }
    if((!current->down->visited && !current->down->wall) || current->down->dist > dist)
    {
        current->down->prev = current;
        BFS(current->down, dist + 1);
    }
    if((!current->up->visited && !current->up->wall) || current->up->dist > dist)
    {
        current->up->prev = current;
        BFS(current->up, dist + 1);
    }
}
void Maze::pathFind()
{
    if(!start || !end || start == end)
    {
        cout << "\nEither the start/end dont exist or start = end\n";
        return;
    }
    BFS(start, -1);
    MazeNode* iterator = end;
    while (iterator->prev)
    {
        iterator->path = true;
        iterator = iterator->prev;
    }
    iterator = topLeft;
    MazeNode* down = iterator->down;
    while (down)
    {
        while (iterator)
        {
            iterator->dist = -1;
            iterator->visited = false;
            iterator->prev = nullptr;
            iterator = iterator->right;
        }
        iterator = down;
        down = down->down;
    }
}
void Maze::resetPathfinding(bool killStart)
{
    if(killStart)
    {
        start = nullptr;
        end = nullptr;
    }
    MazeNode* iterator = topLeft;
    MazeNode* down = iterator->down;
    while(down)
    {
        while (iterator)
        {
            iterator->path = false;
            iterator->visited = false;
            iterator->prev = nullptr;
            iterator->dist = -1;
            iterator = iterator->right;
        }
        iterator = down;
        down = down->down;
    }
}
/*
int main(int argc, char const *argv[])
{
    srand (time(NULL));
    Maze maze(500,500);
    maze.recursiveDivision();
    //ofstream file;
    //file.open("Maze.txt");
    //file << maze.textMaze();
    //file.close();
    maze.print();
    return 0;
}
*/