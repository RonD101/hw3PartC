//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_GAME_H
#define HW3PARTC_GAME_H
#include "Auxiliaries.h"
#include "Character.h"
#include "Matrix.h"

namespace mtm{
    class Game{
        Matrix<std::shared_ptr<Character>> board;
        std::shared_ptr<Character> getCharacter(const GridPoint& coordinates);
    public:
//        class Exception;
//        class CellEmpty;
//        class IllegalCell;
        Game(int height, int width);
        Game(const Game& game):board(game.board){}
        Game &operator=(const Game& other);
        void reload(const GridPoint & coordinates);
    };

//    class Game::Exception  : public mtm::Exception {};
//
//    class Game::CellEmpty  : public mtm::Game::Exception {
//    public:
//        const char* what() const noexcept override
//        {
//            return "A game related error has occurred: CellEmpty";
//        }
//    };
//    class Game::IllegalCell  : public mtm::Game::Exception {
//    public:
//        const char* what() const noexcept override
//        {
//            return "A game related error has occurred: IllegalCell";
//        }
//    };
}
#endif //HW3PARTC_GAME_H
