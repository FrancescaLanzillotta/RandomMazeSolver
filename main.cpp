#include <iostream>
#include "utils.h"
using namespace std;


int main() {

    for(int i = 0; i < 100; i++){
        cout << "--" << endl;
        delayedCLS(100);
        cout << "-" << endl;
        delayedCLS(100);
    }
    return 0;
}
