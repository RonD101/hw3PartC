//
// Created by Ron Dahan on 22/06/2020.
//

#include "Game.h"
#include <memory>

void mtm::Game::reload(const mtm::GridPoint &coordinates) {
//    std::shared_ptr<Character> character =
}

std::shared_ptr<mtm::Character> mtm::Game::getCharacter(const mtm::GridPoint coordinates) {
    std::shared_ptr<Character> c(&board(coordinates.row,coordinates.col));
    return c;
}
