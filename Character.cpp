//
// Created by Ron Dahan on 22/06/2020.
//

#include "Character.h"

mtm::Character::~Character() {

}

void mtm::Character::addAmmo(int add_ammo) {
    ammo += add_ammo;
}

void mtm::Character::addHealth(int value) {
    health += value;
}

int mtm::Character::getHealth() {
    return health;
}
