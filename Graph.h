#ifndef MAZE_H
#define MAZE_H
#include <vector>
#include <iostream>
#include <string>
//The graph is designed using a maze node so that we can dynamically increase the size
//For our nodes we will limit the maximum connections to 4 in order to keep our maze easily visually representable
struct MazeNode
{
    public:
    //int weight = 1;
    bool wall = false;
    MazeNode* up = nullptr;
    MazeNode* down = nullptr;
    MazeNode* left = nullptr;
    MazeNode* right = nullptr;
    MazeNode(bool w);
    MazeNode(bool w, MazeNode* u, MazeNode* d, MazeNode* l, MazeNode* r);
};

struct xy{
    public:
    int x;
    int y;
};
class Maze{
    private:
    int width;
    int height;
    MazeNode* topLeft = nullptr;
    MazeNode* topRight = nullptr;
    MazeNode* botLeft = nullptr;
    MazeNode* botRight = nullptr;
    public:
    void print();
    Maze(int w, int h);
    void updateSize(int w, int h);
    void recursiveDivision();
    void findPath(int sx, int sy, int ex, int ey);
    int probeDepth(MazeNode* start, int dir);
    MazeNode* getNode(int x, int y);
    xy getCoords(MazeNode* node);
    void makeWall(MazeNode* start, int dir);
    bool checkValid(MazeNode* start, int dir);
    std::string textMaze();
    void resetMaze();
    void resizeMaze(int w, int h);
};
#endif