#include <iostream>
#include <vector>
#include "utils.h"
using namespace std;

enum Cell {
    WALL,
    EMPTY,
    START,
    EXIT,
    DOT,
};
int main() {
    int size = 21;
    vector<vector<Cell>> maze;
    for(int row = 0; row < size; row++){
        vector<Cell> mazeRow;
        if(row % 2 == 0){
            for (int col = 0; col < size; col++) {
                mazeRow.push_back(WALL);
            }
        } else {
            for (int col = 0; col < size; col++) {
                if(col % 2 == 0)
                    mazeRow.push_back(WALL);
                else
                    mazeRow.push_back(EMPTY);
            }
        }
        maze.push_back(mazeRow);

    }

    string smaze;
    for( const auto& row : maze){
        for(auto c : row){
            switch (c) {
                case WALL:
                    smaze += "# ";
                    break;
                case EMPTY:
                    smaze += "  ";
                    break;
                case START:
                    smaze += "!";
                    break;
                case EXIT:
                    smaze += " ";
                    break;
                case DOT:
                    smaze += "o";
                    break;
            }
        }
        smaze += "\n";
    }
    cout << smaze;
    return 0;
}
