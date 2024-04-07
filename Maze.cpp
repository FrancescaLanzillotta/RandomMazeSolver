//
// Created by franc on 07/04/2024.
//

#include "Maze.h"

using namespace std;
Maze::Maze(int size) : size(size) {
    maze.reserve(size);
}

vector<Cell> Maze::buildRowWall(int length) {
    vector<Cell> w;
    w.reserve(length);
    for (int i = 0; i < length; i++) {
        w.push_back(WALL);
    }
    return w;
}

string Maze::toString() {
    string s;
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
                    s += "!";
                    break;
                case EXIT:
                    s += " ";
                    break;
                case DOT:
                    s += "o";
                    break;
            }
        }
        s += "\n";
    }
    return s;
}

void Maze::initializeMaze() {
    for(int row = 0; row < size; row++){
        if(row % 2 == 0)
            maze.push_back(buildRowWall(size));
        else{
            vector<Cell> r;
            for(int cell = 0; cell < size; cell++){
                if(cell % 2 == 0)
                    r.push_back(WALL);
                else
                    r.push_back(EMPTY);
            }
            maze.push_back(r);
        }
    }
}

