//
// Created by Ron Dahan on 22/06/2020.
//

#include "Medic.h"
#define AMMO_RELOAD 5

int mtm::Medic::reload() const {
    return AMMO_RELOAD;
}

std::shared_ptr<mtm::Character> mtm::Medic::clone() const {
    return std::shared_ptr<Character>(new Medic(*this));
}
