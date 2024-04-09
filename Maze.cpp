//
// Created by franc on 07/04/2024.
//

#include <iostream>
#include "Maze.h"

using namespace std;
Maze::Maze(int size){
    if(size % 2 == 0){
        this->size = size + 1;
        printf("Size of the maze has to be an odd number. New maze size is (%d, %d)\n", this->size, this->size);
    } else
        this->size = size;
    maze.reserve(this->size);
}

string Maze::toString() {
    string s = "\n";
    for(const auto& row : maze){
        for(Cell c : row){
            switch (c) {
                case WALL:
                    s += "# ";
                    break;
                case EMPTY:
                    s += "  ";
                    break;
                case START:
                    s += "! ";
                    break;
                case EXIT:
                    s += "  ";
                    break;
                case DOT:
                    s += "o ";
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

void Maze::initializeMaze() {
    for(int row = 0; row < size; row++){
        vector<Cell> mazeRow;
        mazeRow.reserve(size);
        for (int col= 0; col < size; col++) {
            if((row % 2 == 0 ) || (col % 2 == 0))
                mazeRow.push_back(WALL);
            else
                mazeRow.push_back(EMPTY);
        }
        maze.push_back(mazeRow);
    }
}

// TODO: figure out how to properly set the exit randomly
void Maze::set_exit(int row, int col) {
    maze[row][col] = EXIT;
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

void Maze::generatePath(pair<int, int> currentCell, set<pair<int, int>>& visited, std::mt19937 &rng) {
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

        maze[wall_r][wall_c] = EMPTY;   // remove the wall between currentCell and nextCell
        visited.insert(make_pair(wall_r, wall_c));

        // this_thread::sleep_for(chrono::milliseconds(500));
        delayedCLS(100);
        cout << toString();
        generatePath(nextCell, visited, rng);
    }
}

pair<int, int> Maze::setRandomExit(mt19937 &rng){
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
    maze[r][c] = EXIT;
    return make_pair(r, c);
}

/*
* Given a current cell as a parameter
*      Mark the current cell as visited
*      While the current cell has any unvisited neighbour cells
*          Choose one of the unvisited neighbours
*          Remove the wall between the current cell and the chosen cell
*          Invoke the routine recursively for the chosen cell
*/





