#include <iostream>
#include "Game.h"

using namespace mtm;
using std::cout;
using std::endl;

int main() {
    Game g(2,3);
    Game g2(11, 4);
    g2 = g;
    try {
        g.reload(GridPoint(0,0));
    }catch (mtm::Game::Exception& e)
    {
        cout << e.what() << endl;
    }
    try {
        g.reload(GridPoint(2,3));
    }catch (mtm::Game::Exception& e)
    {
        cout << e.what() << endl;
    }
    return 0;
}