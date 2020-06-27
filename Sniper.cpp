//
// Created by Ron Dahan on 22/06/2020.
//

#include "Sniper.h"
#include "Game.h"
#include "Exception.h"

#define AMMO_RELOAD 2
#define STEPS_NUM 4
#define AMMO_PER_SHOT 1
#define DIVISOR 2

using namespace mtm;
using std::shared_ptr;

std::shared_ptr<Character> mtm::Sniper::clone() const {
    return shared_ptr<Character>(new Sniper(*this));
}

int mtm::Sniper::reload() const {
    return AMMO_RELOAD;
}

char Sniper::getTypeChar() const {
    return typeChar;
}

CharacterType Sniper::getType() const {
    return SNIPER;
}

bool Sniper::legalMove(int distance) const {
    return distance <= STEPS_NUM;
}

Sniper::Sniper(CharacterType c_type, Team c_team, units_t c_health,
        units_t c_ammo, units_t c_range, units_t c_power) {
    team = c_team;
    type = c_type;
    health = c_health;
    ammo = c_ammo;
    range = c_range;
    power = c_power;
}

Team Sniper::getTeam() const {
    return this->team;
}

bool Sniper::legalAttack(const GridPoint &src, const GridPoint &dst,
        int distance, bool same_team, bool dst_empty) const {
    units_t half_range = static_cast<int>(std::ceil(double(range)/DIVISOR));
    if (distance > range || distance < half_range)
    {
        throw OutOfRange();
    }
    if (ammo < AMMO_PER_SHOT)
    {
        throw OutOfAmmo();
    }
    if(same_team || dst_empty)
    {
        throw  IllegalTarget();
    }

    return true;
}


