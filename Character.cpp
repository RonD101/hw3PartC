//
// Created by Ron Dahan on 22/06/2020.
//

#include "Character.h"

void mtm::Character::removeShot() {
    ammo--;
}

void mtm::Character::addHealth(int value) {
    health += value;
}

int mtm::Character::getHealth() {
    return health;
}
