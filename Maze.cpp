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

vector<Cell> Maze::buildRowWall(int length) {
    vector<Cell> w;
    w.reserve(length);
    for (int i = 0; i < length; i++) {
        w.push_back(WALL);
    }
    return w;
}

vector<Cell> Maze::buildCyclicWall(int length){
    vector<Cell> w;
    w.reserve(length);
    for (int i = 0; i < length; i++) {
        if(i % 2 == 0)
            w.push_back(WALL);
        else
            w.push_back(EMPTY);
    }
    return w;
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
            maze.push_back(buildCyclicWall(size));
        }
    }
}

