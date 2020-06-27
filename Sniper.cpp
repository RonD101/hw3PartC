//
// Created by Ron Dahan on 22/06/2020.
//

#include "Sniper.h"
#include "Game.h"

#define AMMO_RELOAD 2
#define STEPS_NUM 4

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

char Sniper::getTeam() const {
    return this->team;
}


