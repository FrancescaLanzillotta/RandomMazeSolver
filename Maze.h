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

class Maze {
private:
    vector<vector<Cell>> maze;
    int size;
    pair<int, int> start;
    pair<int, int> exit;
    std::mt19937 rng;
public:

    explicit Maze(int size, std::mt19937 &rng);
    string toString();
    [[nodiscard]] bool areValid(int r, int c) const;
    [[nodiscard]] bool areValid(pair<int, int> p) const;
    void setCell(pair<int, int> c, Cell type);
    void setCell(int r, int c, Cell type);
    Cell getCell(pair<int, int> c) const;
    Cell getCell(int r, int c) const;
    void setExit(pair<int, int> e);
    pair<int, int> getExit();
    [[nodiscard]] const pair<int, int> &getStart() const;
    void setStart(pair<int, int> c);
    void generateMaze(bool display = false);

private:
    void makeGrid();
    void setRandomExit();
    void generatePath(pair<int, int> currentCell, set<pair<int, int>> &visited, bool display);
    set<pair<int, int>> getUnvisitedCells(pair<int, int> currentCell, set<pair<int, int>>& visited) const;

};


#endif //RANDOMMAZE_MAZE_H
