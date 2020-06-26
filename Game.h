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
        std::shared_ptr<Character> getCharacter(const GridPoint& coordinates) const;
    public:
        Game(int height, int width);
        Game(const Game& game):board(game.board){}
        Game &operator=(const Game& other);
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        void reload(const GridPoint & coordinates);
        friend std::ostream& operator<<(std::ostream& os, const Game game);
    };
    std::ostream& operator<<(std::ostream& os, const Game game);
}
#endif //HW3PARTC_GAME_H
