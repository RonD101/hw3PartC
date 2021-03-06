//
// Created by Ron Dahan on 22/06/2020.
//

#include "Soldier.h"
#include "Exceptions.h"

using std::shared_ptr;

namespace mtm{
    shared_ptr<Character> Soldier::clone() const {
        return shared_ptr<Character>(new Soldier(*this));
    }

// returns 3 (ammo reload of soldier)
    void Soldier::reload() {
        ammo += ammo_reload;
    }

// returns 'S' if in CPP team or 's' if in PYTHON team
    char Soldier::getTypeChar() const {
        if(team == PYTHON)
            return typeCharPython;
        return typeCharCpp;
    }

// function checks if distance param is smaller than STEPS_NUM
    bool Soldier::legalMove(int distance) const {
        return distance <= steps_num;
    }

// constructor
    Soldier::Soldier(CharacterType c_type, Team c_team, units_t c_health, units_t c_ammo,
                     units_t c_range, units_t c_power) {
        team = c_team;
        type = c_type;
        health = c_health;
        ammo = c_ammo;
        range = c_range;
        power = c_power;
    }

// returns the team this character belongs to
    Team Soldier::getTeam() const {
        return this->team;
    }

/** function returns true if character in src can attack character in dst and no exception was thrown
    if target is out of character's range, throws exception OutOfRange
    if character's out of ammo throws exception OutOfAmmo
    if target is not on the same row or column as the attacker, throws exception IllegalTarget
 */
    bool Soldier::legalAttack(const GridPoint &src, const GridPoint &dst,
                              int distance,bool same_team, bool dst_empty) const {
        if (distance > range)
        {
            throw OutOfRange();
        }
        if (ammo < ammo_per_shot)
        {
            throw OutOfAmmo();
        }
        if(src.row != dst.row && src.col != dst.col)
        {
            throw IllegalTarget();
        }
        return true;
    }

/** function to calculate damage.
    If there are enemies within a third of the range of the target, they will receive half of the damage
    calls function removeShot from Character.h to reduce ammo by 1
*/
    void Soldier::attack(const GridPoint &dst, bool same_team, std::vector<std::pair<GridPoint
            ,units_t >>& grids_to_attack, std::pair<int,int> board_size) {
        units_t damage = -power;
        units_t third_range = static_cast<int>(std::ceil(double(range)/divisor));
        for (int i = 0; i < board_size.first; ++i) {
            for (int j = 0; j < board_size.second; ++j) {
                GridPoint tmp(i,j);
                if(Soldier::distance(dst,tmp) <= third_range)
                {
                    grids_to_attack.push_back(std::pair<GridPoint,units_t >(tmp,
                                                                            (tmp == dst)? damage : static_cast<int>(std::floor(double(damage)/half))));
                }
            }
        }
        this->removeShot();
        return ;
    }

// function to measure distance between 2 sets of coordinates using the formula: |x1-x2| + |y1-y2|
    int Soldier::distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
        return abs(src_coordinates.row - dst_coordinates.row) +
               abs(src_coordinates.col - dst_coordinates.col);
    }



}
