//
// Created by Ron Dahan on 22/06/2020.
//

#include "Medic.h"
#include "Game.h"
#define AMMO_RELOAD 5
#define STEPS_NUM 5

int mtm::Medic::reload() const {
    return AMMO_RELOAD;
}

std::shared_ptr<mtm::Character> mtm::Medic::clone() const {
    return std::shared_ptr<Character>(new Medic(*this));
}

char mtm::Medic::getTypeChar() const {
    return typeChar;
}

mtm::CharacterType mtm::Medic::getType() const {
    return MEDIC;
}

bool mtm::Medic::legalMove(const mtm::GridPoint src, const mtm::GridPoint dst) const {
    return Game::distance(src, dst) <= STEPS_NUM;
}
