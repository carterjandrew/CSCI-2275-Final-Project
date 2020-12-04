#include "Graph.h"
#include <fstream>
using namespace std;
int main(int argc, char const *argv[])
{
    //Initialise maze
    cout << "Welcome to Carters Final Project for CSCI2275! Please enter a width for the Maze:\n";
    int width;
    cin >> width;
    cout << "\nNow please enter a height:\n";
    int height;
    cin>>height;
    Maze maze(width, height);
    while (true)
    {
        std::string dmenu = "======Main Menu=====\n"
					"1. Recursively Divise the Maze\n"
					"2. Set Start Point\n"
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
            switch (choice)
            {
                case 1:
                    maze.recursiveDivision();
                    cout << dmenu;
                    break;
                case 2:
                    return 0;
                    cout << dmenu;
                    break;
                case 3:
                    return 0;
                    cout << dmenu;
                    break;
                case 4:
                    return 0;
                    cout << dmenu;
                    break;
                case 5:
                    maze.print();
                    cout << dmenu;
                    break;
                case 6:
                    cout << "Enter new width\n";
                    int w;
                    int h;
                    cin >> w;
                    cout << "\nEnter new height\n";
                    cin >> h;
                    maze.resizeMaze(w,h);
                    maze.resetMaze();
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
            }
        }
    }
    
    return 0;
}
