#include "Graph.h"
#include <fstream>
#include <time.h>
using namespace std;
int main(int argc, char const *argv[])
{
    //Initialise maze
    srand (time(NULL));
    cout << "Welcome to Carters Final Project for CSCI2275!\nThis project allows you to create and randomly generate a maze, and then mess aourd with it as you please\nTo begin, please enter a width for the Maze:\n";
    int width;
    cin >> width;
    cout << "\nNow please enter a height:\n";
    int height;
    cin>>height;
    Maze maze(width, height);
    while (true)
    {
        std::string dmenu = "======Main Menu=====\n"
                    "Please enter the number of the command below you want to preform\n"
					"1. Recursively Divise the Maze\n"
					"2. Set Start Point(for pathfinding in the maze)\n"
                    "3. Set End Point\n"
                    "4. Pathfind\n"
                    "5. Print Maze\n"
                    "6. Resize\n"
                    "7. Output current maze to file\n"
					"8. Quit\n";
        int choice;
        cout << dmenu;
        while (cin >> choice)
        {
            cin.clear();
            cin.ignore();
            string fileName;
            ofstream file;
            int x, y;
            switch (choice)
            {
                case 1:
                    maze.resetPathfinding(true);
                    maze.recursiveDivision();
                    cout << dmenu;
                    break;
                case 2:
                    cout << "The top left coordinate is 1,1 and the bottom left is " << maze.width << ", " << maze.height << " \nEnter the x coordinate\n";
                    cin >> x;
                    cout << "Enter the y coordinate\n";
                    cin >> y;
                    if(x-1 < 0 || y-1 < 0 || y > maze.height|| x > maze.width)
                    {
                        cout << "There is something wrong with the coordinates you entered\n";
                    }
                    else
                    {
                        maze.resetPathfinding(false);
                        maze.setStart(x-1, y-1);
                    }
                    cout << dmenu;
                    break;
                case 3:
                    cout << "The top left coordinate is 1,1 and the bottom left is " << maze.width << ", " << maze.height << " \nEnter the x coordinate\n";
                    cin >> x;
                    cout << "Enter the y coordinate\n";
                    cin >> y;
                    if(x < 0 || y < 0 || y > maze.height - 1 || x > maze.width -1)
                    {
                        cout << "There is something wrong with the coordinates you entered\n";
                    }
                    else
                    {
                        maze.resetPathfinding(false);
                        maze.setEnd(x-1, y-1);
                    }
                    cout << dmenu;
                    break;
                case 4:
                    maze.pathFind();
                    cout << dmenu;
                    break;
                case 5:
                    maze.print();
                    cout << dmenu;
                    break;
                case 6:
                    maze.resetPathfinding(true);
                    cout << "Enter new width\n";
                    int w;
                    int h;
                    cin >> w;
                    cout << "\nEnter new height\n";
                    cin >> h;
                    if(w > 3 && h > 3)
                    {
                        maze.resizeMaze(w,h);
                        maze.resetMaze();
                    }
                    else
                    {
                        cout << "The size you entered was bad! Pleaze make it larger than 3x3.\n";
                    }
                    
                    cout << dmenu;
                    break;
                case 7:
                    cout << "Input file name (NO NOT INCLUDE .txt)\n";
                    cin >> fileName;
                    fileName += ".txt";
                    file.open(fileName);
                    file << maze.textMaze();
                    file.close();
                    cout << dmenu;
                    break;
                case 8:
                    return 0;
                    break;
                default:
                    cout << dmenu;
                    break;
            }
        }
    }
    
    return 0;
}
