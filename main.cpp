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
    std::shared_ptr<Character> player2 = Game::makeCharacter(SOLDIER,PYTHON,3,4,4,3);
    std::shared_ptr<Character> player3 = Game::makeCharacter(MEDIC,CPP,3,4,4,3);
    std::shared_ptr<Character> player4 = Game::makeCharacter(MEDIC,PYTHON,3,4,4,3);
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
        g.move(GridPoint(1,0),GridPoint(0,1));

    }catch (mtm::GameException& e){
        cout << e.what() << endl;
    }
    try {
        g.move(GridPoint(1,0),GridPoint(0,1));

    }catch (mtm::GameException& e){
        cout << e.what() << endl;
    }
    cout << g << endl;
    g.move(GridPoint(1,0),GridPoint(0,0));
    cout << g << endl;
    cout << player1->getTeam() << endl; // print 1
    cout << g.isOver() << endl; // true
    Team t;
    Game g4(4,4);
    cout << g4.isOver() << endl; // false
    g4.addCharacter(GridPoint(0,0),player1);
    cout << g4.isOver(&t) << endl; // true
    cout << "win: " <<t << endl; // print 0
    g4.addCharacter(GridPoint(2,2),player4);
    cout << g4.isOver() << endl; // false
    //g.attack(GridPoint(0,0),GridPoint(0,1));
    cout << g << endl;
    cout << "####################################################"<<endl;
    Game g5(10,10);
    std::shared_ptr<Character> sniperP = Game::makeCharacter(SNIPER,PYTHON,6,4,4,3);
    std::shared_ptr<Character> sniperC = Game::makeCharacter(SNIPER,CPP,3,4,4,3);
    std::shared_ptr<Character> soldierC = Game::makeCharacter(SOLDIER,CPP,3,4,4,3);
    std::shared_ptr<Character> soldierP = Game::makeCharacter(SOLDIER,PYTHON,3,4,4,3);
    std::shared_ptr<Character> medicC = Game::makeCharacter(MEDIC,CPP,3,4,4,3);
    std::shared_ptr<Character> medicP = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    g5.addCharacter(GridPoint(0,3),sniperP);
    g5.addCharacter(GridPoint(2,3),sniperC);
    g5.addCharacter(GridPoint(5,3),soldierP);
    g5.addCharacter(GridPoint(0,8),soldierC);
    g5.addCharacter(GridPoint(3,7),medicC);
    g5.addCharacter(GridPoint(5,5),medicP);
    Game g6(g);
    g6 = g5;
    cout << g5 << endl;
    try {
        g5.move(GridPoint(0,3),GridPoint(4,4));
    }catch (mtm::GameException& e)
    {
        cout << e.what() << endl;
    }
    try {
        g5.move(GridPoint(0,7),GridPoint(3,7));
    }catch (mtm::GameException& e)
    {
        cout << e.what() << endl;
    }
    try {
        g5.attack(GridPoint(5,5),GridPoint(3,7));
    }catch (mtm::GameException& e)
    {
        cout << e.what() << endl;
    }
    Game g7(g5);
    g5.attack(GridPoint(5,5),GridPoint(5,3));
    g5.attack(GridPoint(5,5),GridPoint(5,3));
    g5.attack(GridPoint(5,5),GridPoint(5,3));
    cout << g5 << endl;
    g5.attack(GridPoint(2,3),GridPoint(5,3));
    g5.attack(GridPoint(2,3),GridPoint(5,3));
    g7.attack(GridPoint(2,3),GridPoint(0,3));
    cout << g7 << endl;
    g5.attack(GridPoint(2,3),GridPoint(5,3));
    cout << g5 << endl;
    g5.move(GridPoint(3,7),GridPoint(0,7));
    std::shared_ptr<Character> soldierP2 = Game::makeCharacter(SOLDIER,CPP,3,4,4,3);
    std::shared_ptr<Character> medicP2 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    std::shared_ptr<Character> medicP3 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    std::shared_ptr<Character> medicP4 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    std::shared_ptr<Character> medicP5 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    std::shared_ptr<Character> medicP6 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    std::shared_ptr<Character> medicP7 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    std::shared_ptr<Character> medicP8 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    std::shared_ptr<Character> medicP9 = Game::makeCharacter(MEDIC,PYTHON,3,0,4,3);
    g5.addCharacter(GridPoint(5,2),soldierP2);
    g5.addCharacter(GridPoint(5,6),medicP2);
    g5.addCharacter(GridPoint(4,5),medicP3);
    g5.addCharacter(GridPoint(4,6),medicP4);
    g5.addCharacter(GridPoint(5,7),medicP5);
    g5.addCharacter(GridPoint(3,5),medicP6);
    g5.addCharacter(GridPoint(3,7),medicP7);
    g5.addCharacter(GridPoint(4,7),medicP7);
    g5.addCharacter(GridPoint(3,6),medicP7);
    cout << g5 << endl;
    g5.attack(GridPoint(5,2),GridPoint(5,5));
    g5.attack(GridPoint(5,2),GridPoint(5,5));
    cout << g5 << endl;
    cout << g6 << endl;
    g6 = g5;
    cout << g6 << endl;
    g5.move(GridPoint(0,3),GridPoint(0,4));
    cout << g5 << endl;


    return 0;
}