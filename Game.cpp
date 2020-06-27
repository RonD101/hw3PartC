//
// Created by Ron Dahan on 22/06/2020.
//

#include "Game.h"
#include <memory>
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

#define SPACE ' '

using std::shared_ptr;
using namespace mtm;

void mtm::Game::reload(const mtm::GridPoint &coordinates) {
    shared_ptr<Character> character = getCharacter(coordinates);
    if(character == nullptr)
    {
        throw CellEmpty();
    }

}

void mtm::Game::move(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
    shared_ptr<Character> character = getCharacter(src_coordinates);
    if(character == nullptr) // if the source coordinates are empty, throw exception
    {
        throw CellEmpty();
    }
    if(!getCharacter(dst_coordinates))
    {
        int distance = Game::distance(src_coordinates, dst_coordinates);
        if(character->legalMove(distance))
        {
            board(dst_coordinates.row,dst_coordinates.col) = board(src_coordinates.row,src_coordinates.col);
            board(src_coordinates.row,src_coordinates.col) = nullptr;
        } else
        {
            throw MoveTooFar();
        }

    }else
    {
        throw CellOccupied();
    }
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

int Game::distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    return abs(src_coordinates.row - dst_coordinates.row) +
        abs(src_coordinates.col - dst_coordinates.col);
}

std::ostream& mtm::operator<<(std::ostream &os, const Game &game) {
    std::string board_symbol;
    for (int i = 0; i < game.board.height(); ++i) {
        for (int j = 0; j < game.board.width(); ++j) {
            if(game.getCharacter(GridPoint(i,j)) == nullptr)
            {
                board_symbol += SPACE;
            }else
            {
                board_symbol += game.getCharacter(GridPoint(i,j))->getTypeChar();
            }
        }
    }
    mtm::printGameBoard(os,board_symbol.c_str(),board_symbol.c_str()+board_symbol.length(),game.board.width());
    return os;
}

void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {
    if(getCharacter(coordinates) != nullptr)
    {
        throw CellOccupied();
    }
    board(coordinates.row,coordinates.col) = character;
}

std::shared_ptr<Character>
Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {
    switch (type){
        case SOLDIER:
            return std::shared_ptr<Character>(new Soldier(type,team,health,ammo,range,power));
            break;
        case MEDIC:
            return std::shared_ptr<Character>(new Medic(type,team,health,ammo,range,power));
            break;
        case SNIPER:
            return std::shared_ptr<Character>(new Sniper(type,team,health,ammo,range,power));
            break;
    }
    return nullptr;
}

bool Game::isOver(Team *winningTeam) const {
    std::string board_symbol;
    bool board_check = false;
    Team temp_team = static_cast<Team>(NULL);
    for (int i = 0; i < this->board.height(); ++i) {
        for (int j = 0; j < this->board.width(); ++j) {
            std::shared_ptr<Character> character = getCharacter(GridPoint(i,j));
            if(character != nullptr)
            {
                if(!board_check)
                {
                    temp_team = character->getTeam();
                } else if (temp_team != character->getTeam())
                {

                }
                board_check = true;
            }else
            {
                board_symbol += this->getCharacter(GridPoint(i,j))->getTypeChar();
            }
        }
    }
    return false;
}

