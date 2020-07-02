//
// Created by Ron Dahan on 22/06/2020.
//

#include "Character.h"
namespace mtm{
    void Character::removeShot() {
        ammo--;
    }

    void Character::addHealth(units_t value) {
        health += value;
    }

    int Character::getHealth() {
        return health;
    }
}
