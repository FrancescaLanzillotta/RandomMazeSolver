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
public:
    explicit Maze(int size);
    static vector<Cell> buildRowWall(int length);
    vector<Cell> buildCyclicWall(int length);
    string toString();
    void initializeMaze();  // TODO change to private
    void set_exit(int row, int col);
    [[nodiscard]] bool areValid(int r, int c) const;
    [[nodiscard]] bool areValid(pair<int, int> p) const;
    void generatePath(pair<int, int> currentCell, set<pair<int, int>>& visited, std::mt19937 &rng);
    auto getUnvisitedCells(pair<int, int> currentCell, set<pair<int, int>>& visited) const;
};


#endif //RANDOMMAZE_MAZE_H
