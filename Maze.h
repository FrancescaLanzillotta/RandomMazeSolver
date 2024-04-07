//
// Created by franc on 07/04/2024.
//

#ifndef RANDOMMAZE_MAZE_H
#define RANDOMMAZE_MAZE_H

#include <vector>
#include <string>

using namespace std;
enum Cell {
    WALL,
    EMPTY,
    START,
    EXIT,
    DOT,
};

class Maze {
private:
    vector<vector<Cell>> maze;
    int size;
public:
    explicit Maze(int size);
    static vector<Cell> buildRowWall(int length);
    vector<Cell> buildCyclicWall(int length);
    string toString();
    void initializeMaze();  // TODO change to private
    void set_exit(int row, int col);
};


#endif //RANDOMMAZE_MAZE_H
