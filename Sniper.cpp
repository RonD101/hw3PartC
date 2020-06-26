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


