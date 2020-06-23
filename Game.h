//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_GAME_H
#define HW3PARTC_GAME_H
#include "Auxiliaries.h"
#include "Matrix.h"
#include "Character.h"

namespace mtm{
    class Game{
        Matrix<std::shared_ptr<Character>> board;
        std::shared_ptr<Character> getCharacter(const GridPoint& coordinates);
    public:
        Game(int height, int width);
        void reload(const GridPoint & coordinates);
    };
}
#endif //HW3PARTC_GAME_H
