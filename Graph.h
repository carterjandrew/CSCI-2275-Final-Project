#ifndef MAZE_H
#define MAZE_H
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
    MazeNode* prev = nullptr;
    bool visited;
    bool path;
    int dist = -1;
};
//Coordinate data that makes passing around an x,y system easier. 
struct xy{
    public:
    int x;
    int y;
};
//Our maze has an array of functions explained in depth in Graph.cpp
//We need a couple of objects to keep the maze running
//4 poiters for each edge of the maze so we can acess from where we like to. 
//We need to store the width and height of the maze
//Then we also store start and end points for our maze pathfinding
class Maze{
    private:
    MazeNode* topLeft = nullptr;
    MazeNode* topRight = nullptr;
    MazeNode* botLeft = nullptr;
    MazeNode* botRight = nullptr;
    public:
    int width;
    int height;
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
    void setStart(int x, int y);
    void setEnd(int x, int y);
    void pathFind();
    MazeNode* start = nullptr;
    MazeNode* end = nullptr;
    void BFS(MazeNode* current, int dist);
    void resetPathfinding(bool killStart);
    bool finishedBFS = false;
};
#endif