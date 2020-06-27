//
// Created by Ron Dahan on 22/06/2020.
//

#include "Soldier.h"
#include "Exception.h"

#define AMMO_RELOAD 3
#define STEPS_NUM 3
#define AMMO_PER_SHOT 1
#define DIVISOR 3
#define HALF 2

using namespace mtm;
using std::shared_ptr;

std::shared_ptr<Character> mtm::Soldier::clone() const {
    return shared_ptr<Character>(new Soldier(*this));
}

void mtm::Soldier::reload() {
    ammo += AMMO_RELOAD;
}

char Soldier::getTypeChar() const {
    if(team == PYTHON)
        return typeCharPython;
    return typeCharCpp;
}

CharacterType Soldier::getType() const {
    return SOLDIER;
}

bool Soldier::legalMove(int distance) const {
    return distance <= STEPS_NUM;
}

Soldier::Soldier(CharacterType c_type, Team c_team, units_t c_health, units_t c_ammo,
            units_t c_range, units_t c_power) {
    team = c_team;
    type = c_type;
    health = c_health;
    ammo = c_ammo;
    range = c_range;
    power = c_power;
}

Team Soldier::getTeam() const {
    return this->team;
}

bool Soldier::legalAttack(const GridPoint &src, const GridPoint &dst,
        int distance,bool same_team, bool dst_empty) const {
    if (distance > range)
    {
        throw OutOfRange();
    }
    if (ammo < AMMO_PER_SHOT)
    {
        throw OutOfAmmo();
    }
    if(src.row != dst.row && src.col != dst.col)
    {
        throw IllegalTarget();
    }
    return true;
}

void Soldier::attack(const GridPoint &dst, bool same_team, std::vector<std::pair<GridPoint
        ,units_t >>& grids_to_attack, std::pair<int,int> board_size) {
    units_t damage = -power;
    units_t third_range = static_cast<int>(std::ceil(double(range)/DIVISOR));
    for (int i = 0; i < board_size.first; ++i) {
        for (int j = 0; j < board_size.second; ++j) {
            GridPoint tmp(i,j);
            if(Soldier::distance(dst,tmp) < third_range)
            {
                grids_to_attack.push_back(std::pair<GridPoint,units_t >(tmp,(tmp == dst)? damage : damage/HALF));
            }
        }
    }
    this->removeShot();
    return ;
}

int Soldier::distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {
    return abs(src_coordinates.row - dst_coordinates.row) +
           abs(src_coordinates.col - dst_coordinates.col);
}


