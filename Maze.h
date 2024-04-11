//
// Created by franc on 07/04/2024.
//

#ifndef RANDOMMAZE_MAZE_H
#define RANDOMMAZE_MAZE_H

#include <vector>
#include <string>
#include <unordered_set>
#include <set>
#include <random>
#include "utils.h"


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
    // TODO add random generator as attribute?
    vector<vector<Cell>> maze;
    int size;
    pair<int, int> exit;
    std::mt19937 rng;
public:

    explicit Maze(int size, std::mt19937 &rng);
    string toString();
    void setExit(pair<int, int> e);
    pair<int, int> getExit();
private:
    void makeGrid();
    [[nodiscard]] bool areValid(int r, int c) const;
    [[nodiscard]] bool areValid(pair<int, int> p) const;
    void generatePath(pair<int, int> currentCell, set<pair<int, int>> &visited, bool display);
    void generateMaze(bool display = false);
    set<pair<int, int>> getUnvisitedCells(pair<int, int> currentCell, set<pair<int, int>>& visited) const;
    pair<int, int> setRandomExit();
};


#endif //RANDOMMAZE_MAZE_H
