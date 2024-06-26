//
// Created by franc on 07/04/2024.
//

#include <iostream>
#include "Maze.h"

using namespace std;

Maze::Maze(int size, std::mt19937 &rng): rng(rng){
    if(size % 2 == 0){
        this->size = size + 1;
        printf("Size of the maze has to be an odd number. New maze size is (%d, %d)\n", this->size, this->size);
    } else
        this->size = size;

    maze.reserve(this->size);
    makeGrid();
    setRandomExit();
    float sCoord = static_cast<float>(size) / 2;
    setStart(make_pair(ceil(sCoord), ceil(sCoord)));
}

string Maze::toString() {
    string s = "\n";
    for(const auto& row : maze){
        for(auto c : row){
            if (c.second > 0)   // particles on the cell
                s += "o ";
            else
                switch (c.first) {
                    case WALL:
                        s += "# ";
                        break;
                    case EMPTY:
                        s += "  ";
                        break;
                    case START:
                        s += "@ ";
                        break;
                    case EXIT:
                        s += "  ";
                        break;
                    case PATH:
                        s += ". ";
                        break;
                    case ERROR:
                        s += "! ";
                        break;
                }
        }
        s += "\n";
    }
    return s;
}

bool Maze::areValid(int r, int c) const{
    return ((r >= 0) && (r < size) && (c >= 0) && (c < size));
}

bool Maze::areValid(pair<int, int> p) const {
    return areValid(p.first, p.second);
}
void Maze::setCell(int r, int c, Cell type, int nParticles) {
    if (areValid(r, c))
        maze[r][c] = make_pair(type, nParticles);
}

void Maze::setCell(pair<int, int> c, Cell type, int nParticles) {
    setCell(c.first, c.second, type, nParticles);
}

pair<Cell, int> Maze::getCell(int r, int c) const {
    if (areValid(r, c)){
        return maze[r][c];
    } else
        return pair<Cell, int>();
}


pair<Cell, int> Maze::getCell(pair<int, int> c) const {
    return getCell(c.first, c.second);
}

void Maze::setCellType(int r, int c, Cell type) {
    if (areValid(r, c))
        maze[r][c].first = type;
}

void Maze::setCellType(pair<int, int> c, Cell type) {
    setCellType(c.first, c.second, type);
}

Cell Maze::getCellType(int r, int c) const{
    if (areValid(r, c)){
        return maze[r][c].first;
    }
    else
        return ERROR;
}

Cell Maze::getCellType(pair<int, int> c) const {
    return getCellType(c.first, c.second);
}

void Maze::setParticles(int r, int c, int n) {
    if (areValid(r, c)){
        maze[r][c].second = n;
    }
}

void Maze::setParticles(pair<int, int> c, int n) {
    setParticles(c.first, c.second, n);
}

int Maze::getParticles(int r, int c) const {
    if (areValid(r, c)){
        return maze[r][c].second;
    } else
        return -1;
}

int Maze::getParticles(pair<int, int> c) const {
    return getParticles(c.first, c.second);
}


void Maze::removeParticle(int r, int c) {
    if (areValid(r, c)){
        int n = getParticles(r, c);
        if (n > 0)
            setParticles(r, c, n - 1);
    }
}

void Maze::removeParticle(pair<int, int> c) {
    removeParticle(c.first, c.second);

}

void Maze::addParticle(int r, int c) {
    if (areValid(r, c)){
        setParticles(r, c, getParticles(r, c) + 1);
    }

}

void Maze::addParticle(pair<int, int> c) {
    addParticle(c.first, c.second);
}


void Maze::makeGrid() {
    for(int row = 0; row < size; row++){
        vector<pair<Cell, int>> mazeRow;
        mazeRow.reserve(size);
        for (int col= 0; col < size; col++) {
            if((row % 2 == 0 ) || (col % 2 == 0))
                mazeRow.emplace_back(WALL, 0);
            else
                mazeRow.emplace_back(EMPTY, 0);
        }
        maze.push_back(mazeRow);
    }
}

void Maze::setExit(pair<int, int> e) {
    setCellType(exit, WALL);
    exit = e;
    setCellType(exit, EXIT);
}

pair<int, int> Maze::getExit() {
    return exit;
}

void Maze::setRandomExit(){
    int r, c;
    uniform_int_distribution<> distrib(1, size - 2);
    std::bernoulli_distribution b(0.5);

    if (b(rng) == 0){
        if(b(rng) == 0)
            r = 0;          // exit is on the left side
        else
            r = size - 1;   // exit in on the right side
        do {
            c = distrib(rng);
        } while (c % 2 == 0);   // avoid placing exit in the middle of walls
    } else {
        if (b(rng) == 0)
            c = 0;          // exit is on the top side
        else
            c = size - 1;   // exit is on the bottom side
        do {
            r = distrib(rng);
        } while (r % 2 == 0);   // avoid placing exit in the middle of walls
    }
    setExit(make_pair(r, c));
}

const pair<int, int> &Maze::getStart() const {
    return start;
}

void Maze::setStart(pair<int, int> c) {
    if (areValid(c)) {
        pair<int, int> s;
        if (getCellType(c) == EMPTY)
            s = c;
        else if (getCellType(c.first - 1, c.second) == EMPTY)
            s = make_pair(c.first - 1, c.second);
        else if (getCellType(c.first, c.second - 1) == EMPTY)
            s = make_pair(c.first, c.second -1);
        else if (getCellType(c.first + 1, c.second) == EMPTY)
            s = make_pair(c.first + 1, c.second);
        else if (getCellType(c.first, c.second + 1) == EMPTY)
            s = make_pair(c.first, c.second + 1);
        else
            s = make_pair(c.first - 1, c.second - 1);

        if (start != make_pair(0, 0))   // if start wasn't initialized it contains (0, 0)
            setCellType(start, EMPTY);
        start = s;
        setCellType(start, START);

    }

}

set<pair<int, int>> Maze::getUnvisitedCells(pair<int, int> currentCell, set<pair<int, int>>& visited) const{
    set<pair<int, int>> adj;
    // insert all cells adjacent to the current cell
    adj.insert(make_pair(currentCell.first - 2, currentCell.second));
    adj.insert(make_pair(currentCell.first, currentCell.second + 2));
    adj.insert(make_pair(currentCell.first + 2, currentCell.second));
    adj.insert(make_pair(currentCell.first, currentCell.second - 2));

    set<pair<int, int>> unvisited;
    for(auto c : adj){
        // add cells only if their coordinates are valid and they haven't been visited yet
        if (areValid(c) && visited.find(c) == visited.end())
            unvisited.insert(c);
    }
    return unvisited;
}

void Maze::generatePath(pair<int, int> currentCell, set<pair<int, int>> &visited, int ms) {
    visited.insert(currentCell);

    // special case for exit cell
    if(currentCell.first == 0)
        currentCell.first += 1;
    if (currentCell.first == size - 1)
        currentCell.first -= 1;
    if (currentCell.second == 0)
        currentCell.second += 1;
    if (currentCell.second == size - 1)
        currentCell.second -= 1;

    // it's a set, there are no duplicates
    visited.insert(currentCell);


    while (!getUnvisitedCells(currentCell, visited).empty()){   // stops if all neighbouring cells have been visited

        set<pair<int, int>> unvisited = getUnvisitedCells(currentCell, visited);

        // Choose one of the unvisited neighbours randomly
        uniform_int_distribution<int> distrib(0, unvisited.size() - 1);
        auto itr = unvisited.begin();       // set iterator to first position
        advance(itr, distrib(rng));     // advance iterator of random number of positions
        pair<int, int> nextCell = unvisited.extract(itr).value();    // extract random cell from unvisited neighbours

        // we have to determine the coordinates of the wall to remove
        int wall_r;
        int wall_c;
        if(currentCell.first == nextCell.first){     // nextCell is either on the left-hand or right-hand side of the current cell
            int offset = currentCell.second > nextCell.second ? -1 : 1;
            wall_r = currentCell.first;
            wall_c = currentCell.second + offset;

        } else {                                    // nextCell is either above or below the current cell
            int offset = currentCell.first > nextCell.first ? -1 : 1;
            wall_r = currentCell.first + offset;
            wall_c = currentCell.second;
        }

        setCellType(wall_r, wall_c, EMPTY); // remove the wall between currentCell and nextCell
        visited.insert(make_pair(wall_r, wall_c));

        // this_thread::sleep_for(chrono::milliseconds(500));
        if (ms > 0){
            delayedCLS(ms);
            cout << toString();
        }
        generatePath(nextCell, visited, ms);
    }
}

void Maze::generateMaze(int ms) {
    set<pair<int, int>> visited;
    generatePath(getExit(), visited, ms);
}

const vector<pair<int, int>> &Maze::getSolution() const {
    return solution;
}

void Maze::setSolution(const vector<pair<int, int>> &solution) {
    Maze::solution = solution;
}

void Maze::resetMaze() {
    for(auto &row : maze){
        for(auto &c : row){
            if (c.second > 0)
                c.second = 0;
        }
    }
    // cout << "All particles removed from maze" << endl;
}













/*
* Given a current cell as a parameter
*      Mark the current cell as visited
*      While the current cell has any unvisited neighbour cells
*          Choose one of the unvisited neighbours
*          Remove the wall between the current cell and the chosen cell
*          Invoke the routine recursively for the chosen cell
*/





