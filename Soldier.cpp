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
