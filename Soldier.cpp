//
// Created by Ron Dahan on 22/06/2020.
//

#include "Soldier.h"

#define AMMO_RELOAD 3
#define STEPS_NUM 3

using namespace mtm;
using std::shared_ptr;

std::shared_ptr<Character> mtm::Soldier::clone() const {
    return shared_ptr<Character>(new Soldier(*this));
}

int mtm::Soldier::reload() const {
    return AMMO_RELOAD;
}

char Soldier::getTypeChar() const {
    return typeChar;
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

