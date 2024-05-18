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
    vector<vector<pair<Cell, int>>> maze;
    int size;
    pair<int, int> start;
    pair<int, int> exit;
    vector<pair<int, int>> solution;
    std::mt19937 rng;

public:
    [[nodiscard]] const vector<pair<int, int>> &getSolution() const;
    void setSolution(const vector<pair<int, int>> &solution);
    explicit Maze(int size, std::mt19937 &rng);
    string toString();
    [[nodiscard]] bool areValid(int r, int c) const;
    [[nodiscard]] bool areValid(pair<int, int> p) const;
    void setCellType(pair<int, int> c, Cell type);
    void setCellType(int r, int c, Cell type);
    [[nodiscard]] Cell getCellType(pair<int, int> c) const;
    [[nodiscard]] Cell getCellType(int r, int c) const;
    void removeParticle(int r, int c);
    void removeParticle(pair<int, int> c);
    void addParticle(int r, int c);
    void addParticle(pair<int, int> c);
    void setExit(pair<int, int> e);
    pair<int, int> getExit();
    [[nodiscard]] const pair<int, int> &getStart() const;
    void setStart(pair<int, int> c);
    void generateMaze(bool display = false);


private:
    void setCell(int r, int c, Cell type, int nParticles);
    void setCell(pair<int, int> c, Cell type, int nParticles);
    [[nodiscard]] pair<Cell, int> getCell(int r, int c) const;
    pair<Cell, int> getCell (pair<int, int> c) const;
    void setParticles(int r, int c, int n);
    void setParticles(pair<int, int> c, int n);
    int getParticles(int r, int c  ) const;
    int getParticles(pair<int, int> c) const;
    void makeGrid();
    void setRandomExit();
    void generatePath(pair<int, int> currentCell, set<pair<int, int>> &visited, bool display);
    set<pair<int, int>> getUnvisitedCells(pair<int, int> currentCell, set<pair<int, int>>& visited) const;

};


#endif //RANDOMMAZE_MAZE_H
