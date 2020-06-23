//
// Created by Ron Dahan on 22/06/2020.
//

#include "Game.h"
#include "EmptySlot.h"
#include <memory>

using std::shared_ptr;

void mtm::Game::reload(const mtm::GridPoint &coordinates) {
    shared_ptr<Character> character = getCharacter(coordinates);

    try {
        character->addAmmo(character->reload());
    }catch (EmptySlot::EmptyCell&)
    {
        throw Game::CellEmpty();
    }

}

std::shared_ptr<mtm::Character> mtm::Game::getCharacter(const mtm::GridPoint& coordinates) {
    try {
        return board(coordinates.row + 1,coordinates.col + 1);
    }catch(Matrix<std::shared_ptr<Character>>::AccessIllegalElement&)
    {
        throw IllegalCell();
    }

}

mtm::Game::Game(int height, int width) : board(Matrix<std::shared_ptr<Character>>
          (Dimensions(height,width),std::shared_ptr<Character>(new EmptySlot()))){}
