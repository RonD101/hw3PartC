//
// Created by Ron Dahan on 22/06/2020.
//

#include "Soldier.h"

using namespace mtm;
using std::shared_ptr;

#define AMMO_RELOAD 3

std::shared_ptr<Character> mtm::Soldier::clone() const {
    return shared_ptr<Character>(new Soldier(*this));
}

int mtm::Soldier::reload() const {
    return AMMO_RELOAD;
}
