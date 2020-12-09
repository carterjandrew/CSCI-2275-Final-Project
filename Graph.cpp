#include "Graph.h"
#include "Stack.h"
//#include <fstream>
using namespace std;
//We can set up a maze node with all 4 of its pointers null but we can choose if it's a wall or not
MazeNode::MazeNode(bool w)
{
    wall = w;
}
//We can enter all surounding walls, if some walls don't exist just use nullptr as an arguemnt. 
MazeNode::MazeNode(bool w, MazeNode* u, MazeNode* d, MazeNode* l, MazeNode* r)
{
    wall = w;
    up = u;
    down = d;
    left = l;
    right = r;
}
//Initialising the maze means we actually have to build out every node. This is done through layeering for loops and then adding connections as we go. 
Maze::Maze(int w, int h)
{
    width = w;
    height = h;
    //pleft = previous left, pup is previous up, they are used for setting up the connecitons between the maze. 
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
    //Now, we are going to set up our for reference nodes, topLeft has allready been set up and will be used to find topRight, bottomLeft, and bottomeRight
    //We will also be setting up the outisde walls of the maze right now. 
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
//Printing is pretty simple, start up in the corner and then work your way down while couting what we find. 
//We need to check if it's start/end first because otherwise it could get printed as an empty node. 
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
//Same thing as printing except we put it into a string then returned and put into a file. 
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
//This is to handle most of the directional, up, down, left, right. We use a number to indicate the direction: 0 = up, 1 = down, 2 = left, 3 = right and so on. 
//We return a new node that we navigated to. This will return nullptr if we go off the side of the maze. 
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
//Basically this iterates in a direction through the maze until it hits a wall and then returns the distance it traveled. 
//This is used for the recursive division function to see if a wall can be put in a certain place. 
//It uses the same direction coordinates as described in move()
//Also directions are right below this comment. 
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
//Takes in coordinates and returns the cooresponding node in the maze. This is used because our stack does not have acess to our node data type
//It will handleout of bounds errors with returning a nullptr. 
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
//When we make a wall we need to do a couple of things:
//1. We need to find out how long the wall will be by using probeDepth()
//2. We need to randomly choose a hole in the wall where we wont make the node a wall
//3. We need to make the wall and set up the hole in the wall. 
void Maze:: makeWall(MazeNode* start, int dir)
{
    int dist = probeDepth(start,dir);
    if(dist == 0)
    {
        return;
    }
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
//Basically used to see if we could possibly make a wall in a given spot. 
//We expand on probeDepth by checking if there is a wall up, down, left, or right of our potental wall that could cause an invalid maze.
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
//We return a pair of coordinates used for setting up our stack. Basically we start at our node and iterate to the top left while recording our distance. 
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
    cout << height << endl;
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
//This has four possible states we need to check, if our width or height get smaller or larger. 
void Maze::resizeMaze(int w, int h)
{
    //For when we need to make the maze smaller we can simply delete them off of the end, update our edge nodes(bottomLeft..ect), then set our new width. 
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
            botRight = iterator;
            iterator = iterator->down;
        }
    }
    //For making it larger we need to add nodes on in a certain direction. This is a little bit more complicated because we need to set up our edgeNodes propely
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
    //Same thing as before but in a vertical direction now
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
            botRight = iterator;
            iterator = iterator->right;
        }
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
//This is where we actually divide the maze up, we use a stack to handle different walls we create and make sub-walls that branch off those walls.
//If we cant make any more sub-walls then we pop that wall off our stack and move back out until we have a fully completed maze. 
void Maze::recursiveDivision()
{
    //We need to make sure there isnt allready walls then we start. 
    resetMaze();
    int startX = 1;
    if(height == 0)
    {
        return;
    }
    int startY = (int)rand() % (height-1)+1;
    MazeNode* startNode = getNode(startX, startY);
    //Sets up our stakc and first wall for use. 
    Stack branchCommands;
    branchCommands.push(startX,startY,3, probeDepth(startNode, 3));
    makeWall(startNode, 3);
    while(!branchCommands.isEmpty())
    {
        //First we need to update all the possible branches
        StackNode currentBranch = branchCommands.top();
        vector<BranchPossibility> validsBranches;
        //We need to check up and down for wall that go left and right and visa versa so we need a swith command to handle each one. 
        //Basically what each of these is doing is updating the possible branches off to the side to make sure we have coorectly identified branches we can go down
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
        //Otherwize we will make a new wall and then push that onto the stack. 
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
//Used to set an end point for our maze. We dont want the maze to be on a wall so if it is we dont set it up
void Maze::setEnd(int x, int y)
{
    if(getNode(x,y)->wall)
    {
        cout << "The coordinate you entered is a wall, please enter a non wall coordinate.\n";
    }
    else
    {
        end = getNode(x,y);
    }
}
//Same thing as above but for our starting node. 
void Maze::setStart(int x, int y)
{
    if(getNode(x,y)->wall)
    {
        cout << "The coordinate you entered is a wall, please enter a non wall coordinate.\n";
    }
    else
    {
        start = getNode(x,y);
    }
}
//Use a recursive breadth first search to find the fastest path from start to end. 
//This function is initialised by pathfind() and then runs recursively
//Is eitheer the distance from start is smaller or we havent visited we will set up the maze to that new path setup
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
//Initialises our bfs from our start point to the end point
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
//The pathfinding does not interact well with functions like resize and recursive division so we need to use this to reset our path and strt/end points
//We pass in a bool to tell wether or not we should get rid of the start/end points
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