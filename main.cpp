#include <iostream>
#include "Game.h"

using namespace mtm;
using std::cout;
using std::endl;

int main() {
//    Matrix<int> m(Dimensions(2,3));
//    m(2,3) = 5;
//    cout << m << endl;
    Game g(2,3);
    Game g2(11, 4);
    g2 = g;
    try {
        g.reload(GridPoint(0,0));
    }catch (mtm::GameException& e)
    {
        cout << e.what() << endl;
    }
    try {
        g.reload(GridPoint(2,3));
    }catch (mtm::GameException& e)
    {
        cout << e.what() << endl;
    }
    Game g3(g);
    try {
        Game g4(-2,-5);
    }catch (mtm::GameException& e)
    {
        cout << e.what() << endl;
    }
    cout << g << endl;
    return 0;
}