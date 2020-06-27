//
// Created by Ron Dahan on 22/06/2020.
//
#include "Game.h"
#include <memory>
#include <vector>
#include "Soldier.h"
#include "Medic.h"
#include "Sniper.h"

#define SPACE ' '

using std::shared_ptr;
using namespace mtm;

// constructor for Game. creates an empty board with given height and witdth.
// If one of the params is <= 0, throws exception IllegalArgument
mtm::Game::Game(int height, int width) : board((height <=0 || width <= 0) ? throw IllegalArgument() :
               Matrix<std::shared_ptr<Character>>(Dimensions(height,width), nullptr)){}

Game::Game(const Game &game): board(game.board){
    //making sure the games are separated
    for (int i = 0; i < board.height() ; ++i)
    {
        for (int j = 0; j < board.width(); ++j)
        {
            if(game.board(i,j) != nullptr)
            {
                board(i, j) = game.board(i, j)->clone();
            }
        }
    }
}

// reload method adds ammo to character in the coordinates passed
void mtm::Game::reload(const mtm::GridPoint &coordinates) {
    shared_ptr<Character> character = getCharacter(coordinates);
    if(character == nullptr) //if reload was attempted on an empty space in the board, throw CellEmpty exception
    {
        throw CellEmpty();
    }
    character->reload();
}

/** move method moves one character in the src_coordinates param to dst_coordinates.
     if the source coordinates are empty, throw exception CellEmpty
     function legalMove returns false if destination is to far. Exception MoveTooFar is thrown
     if the destination is occupied, throws exception CellOccupied
*/
void mtm::Game::move(const mtm::GridPoint &src_coordinates, const mtm::GridPoint &dst_coordinates) {
    shared_ptr<Character> character = getCharacter(src_coordinates);
    if(character == nullptr)
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

// function tries to return the content of the board at the coordinates passed.
// if the coordinates are outside the board, throws exception IllegalCell
std::shared_ptr<mtm::Character> mtm::Game::getCharacter(const mtm::GridPoint& coordinates) const{
    try {
        return board(coordinates.row,coordinates.col);
    }catch(Matrix<std::shared_ptr<Character>>::AccessIllegalElement&)
    {
        throw IllegalCell();
    }

}

// operator= for game
mtm::Game& mtm::Game::operator=(const mtm::Game &other)
{
    if(this == & other)
    {
        return *this;
    }
    //changing the dimension of board and doing a 'soft' copy
    this->board = other.board;
    //making sure the games are separated
    for (int i = 0; i < board.height() ; ++i)
    {
        for (int j = 0; j < board.width(); ++j)
        {
            if(other.board(i,j) != nullptr)
            {
                board(i, j) = other.board(i, j)->clone();
            }
        }
    }
    return *this;
}

// function to measure distance between 2 sets of coordinates using the formula: |x1-x2| + |y1-y2|
int Game::distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    return abs(src_coordinates.row - dst_coordinates.row) +
        abs(src_coordinates.col - dst_coordinates.col);
}

// Output function uses printGameBoard to print onto the screen the game board. In an emty cell, ' ' is printed.
// In an empty cell, ' ' is printed. In an occupied cell prints the character corresponding  to the character in it.
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

/** function adds an existing character to the game at the coordinates passed.
    if the coordinates are out of range, getCharacter throws exception IllegalCell
    if the the coordinates are occupied, function throws exception CellOccupied
*/
void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {
    if(getCharacter(coordinates) != nullptr)
    {
        throw CellOccupied();
    }
    board(coordinates.row,coordinates.col) = character;
}

// creates a new character with params passed. If health param is 0 or lower, throws exception IllegalArgument
std::shared_ptr<Character>
Game::makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {
    if( health <= 0)
    {
        throw IllegalArgument();
    }
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

/** function to check if currently there is a winning team
if a nullptr is passed return if there is a winning team, but doesn't update winningTeam param
if a non null arg was passed, also return if there is a winning team. if there is, update winningTeam param */
bool Game::isOver(Team *winningTeam) const {
    bool board_check = false;
    Team temp_team = CPP;
    for (int i = 0; i < board.height(); ++i) {
        for (int j = 0; j < board.width(); ++j) {
            std::shared_ptr<Character> character = getCharacter(GridPoint(i, j));
            if (character != nullptr) // first non-empty space on the board
            {
                if (!board_check)
                { //if found a character, save his team into a temporary var to later return as winner
                    temp_team = character->getTeam();
                } // if characters from more than one team were found, return false
                if (temp_team != character->getTeam()) {
                    return false;
                }
                board_check = true; // if a single character was found, set board_check to false
            }
        }
    }
    // if no character belonging to any team was found, return false
    if(!board_check)
    {
        return false;
    } else{ // if only characters from one team were found, make their team the winner and return true
        if(winningTeam) // if winningTeam was not passed as null, update the winner
        {
            *winningTeam = temp_team;
        }
        return true;
    }
}

/** attack method makes character in src_coordinates attack character in dst_coordinates
    if src_coordinates is empty, throws exception CellEmpty.
    if src_coordinates or dst_character are empty, getCharacter function throws exception IllegalCell
    if dst_character is out of range of the attacker, legalAttack function throws exception OutOfRange
    if character in src_coordinates dosn't have enough ammo to attack, legalAttack function throws exception OutOfAmmo
    legalAttack function throws exception IllegalTarget if:
        medic tries to attack itself or an empty cell
        sniper tries to attack a teammate or an empty cell
        soldier tries to attack a cell not in its row or column
    in the end of successful attack, calls function clearDeads
 */
void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    shared_ptr<Character> src_character = getCharacter(src_coordinates);
    if(src_character == nullptr)
    {
        throw CellEmpty();

    }
    shared_ptr<Character> dst_character = getCharacter(dst_coordinates);
    bool dst_empty = false;
    bool same_team = false;
    if(dst_character == nullptr)
    {
        dst_empty = true;

    }else if(src_character->getTeam() == dst_character->getTeam())
    {
        same_team = true;
    }
    src_character->legalAttack(src_coordinates, dst_coordinates,
            distance(src_coordinates, dst_coordinates), same_team, dst_empty);
    std::vector<std::pair<GridPoint,units_t >> grids_to_attack;
    std::pair<int,int> board_size(board.height(),board.width());
    src_character->attack(dst_coordinates, same_team,grids_to_attack,board_size);
    for (int i = 0; i < static_cast<int>(grids_to_attack.size()); ++i) {
        std::shared_ptr<Character> temp_character = getCharacter(grids_to_attack[i].first);
        if(temp_character != nullptr)
        {
            //healing a character
            if(src_character->getTeam() == temp_character->getTeam() && grids_to_attack[i].second > 0)
            {
                temp_character->addHealth(grids_to_attack[i].second);
            }
            //damaging opponent
            else if(src_character->getTeam() != temp_character->getTeam())
            {
                temp_character->addHealth(grids_to_attack[i].second);
            }
        }
    }
    this->clearDeads();
}

// function sets all non-empty cells on board with health <= 0 to nullptr
void Game::clearDeads() {
    for (Matrix<shared_ptr<Character>>::iterator it = board.begin(); it != board.end(); ++it) {
        if(*it != nullptr && (*it)->getHealth() <= 0)
        {
            *it = nullptr;
        }
    }
}

