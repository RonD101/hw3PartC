//
// Created by Ron Dahan on 22/06/2020.
//

#include "Game.h"
#include <memory>
#include "Exception.h"

using std::shared_ptr;
using namespace mtm;

void mtm::Game::reload(const mtm::GridPoint &coordinates) {
    shared_ptr<Character> character = getCharacter(coordinates);
    if(character == nullptr)
    {
        throw CellEmpty();
    }
//    try {
//        character->addAmmo(character->reload());
//    }catch (EmptySlot::EmptyCell&)
//    {
//        throw CellEmpty();
//    }

}

std::shared_ptr<mtm::Character> mtm::Game::getCharacter(const mtm::GridPoint& coordinates) const{
    try {
        return board(coordinates.row,coordinates.col);
    }catch(Matrix<std::shared_ptr<Character>>::AccessIllegalElement&)
    {
        throw IllegalCell();
    }

}

mtm::Game::Game(int height, int width) : board((height <=0 || width <= 0) ? throw IllegalArgument() :
    Matrix<std::shared_ptr<Character>>(Dimensions(height,width), nullptr)){}

mtm::Game& mtm::Game::operator=(const mtm::Game &other)
{
    if(this == & other)
    {
        return *this;
    }
    this->board = other.board;
    return *this;
}

std::ostream& mtm::operator<<(std::ostream &os, const Game game) {
    std::string board_symbol;
    for (int i = 0; i < game.board.height(); ++i) {
        for (int j = 0; j < game.board.width(); ++j) {
            board_symbol += game.getCharacter(GridPoint(i,j))->getTypeChar();
        }
    }
    mtm::printGameBoard(os,board_symbol.c_str(),board_symbol.c_str()+board_symbol.length(),game.board.width());
    return os;
}

void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {

}

