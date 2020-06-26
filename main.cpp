#include <iostream>
#include "Game.h"

using namespace mtm;
using std::cout;
using std::endl;

int main() {
//    Matrix<int> m(Dimensions(2,3));
//    m(2,3) = 5;
//    cout << m << endl;
    Game g(4,4);
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
    std::shared_ptr<Character> player1 = Game::makeCharacter(SNIPER,CPP,3,4,4,3);
    std::shared_ptr<Character> player2 = Game::makeCharacter(SOLDIER,CPP,3,4,4,3);
    std::shared_ptr<Character> player3 = Game::makeCharacter(MEDIC,CPP,3,4,4,3);
    try {
        g.addCharacter(GridPoint(-2,0), player1);

    }catch (mtm::GameException& e){
        cout << e.what() << endl;
    }
    g.addCharacter(GridPoint(0,0),player1);
    g.addCharacter(GridPoint(1,0),player2);
    g.addCharacter(GridPoint(2,0),player3);
    cout << g << endl;
    g.move(GridPoint(0,0),GridPoint(0,1));
    cout << g << endl;
    try {
        g.addCharacter(GridPoint(0,1),player1);

    }catch (mtm::GameException& e){
        cout << e.what() << endl;
    }
    try {
        g.move(GridPoint(1,0),GridPoint(0,-1));

    }catch (mtm::GameException& e){
        cout << e.what() << endl;
    }
    try {
        g.move(GridPoint(1,0),GridPoint(0,1));

    }catch (mtm::GameException& e){
        cout << e.what() << endl;
    }
    g.move(GridPoint(1,0),GridPoint(0,0));
    cout << g << endl;
    return 0;
}