//
// Created by Ron Dahan on 22/06/2020.
//

#include "Game.h"
#include "EmptySlot.h"
#include <memory>

void mtm::Game::reload(const mtm::GridPoint &coordinates) {
//    std::shared_ptr<Character> character =
}

std::shared_ptr<mtm::Character> mtm::Game::getCharacter(const mtm::GridPoint& coordinates) {
    return board(coordinates.row + 1,coordinates.col + 1);
}

mtm::Game::Game(int height, int width) : board(Matrix<std::shared_ptr<Character>>
          (Dimensions(height,width),std::shared_ptr<Character>(new EmptySlot()))){}
