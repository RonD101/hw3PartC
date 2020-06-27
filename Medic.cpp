//
// Created by Ron Dahan on 22/06/2020.
//

#include "Medic.h"
#include "Exception.h"

#define AMMO_RELOAD 5
#define STEPS_NUM 5
#define AMMO_PER_SHOT 1

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

bool mtm::Medic::legalMove(int distance) const {
    return distance <= STEPS_NUM;
}

mtm::Medic::Medic(mtm::CharacterType c_type, mtm::Team c_team, mtm::units_t c_health, mtm::units_t c_ammo,
                  mtm::units_t c_range, mtm::units_t c_power) {
        team = c_team;
        type = c_type;
        health = c_health;
        ammo = c_ammo;
        range = c_range;
        power = c_power;

}

mtm::Team mtm::Medic::getTeam() const {
    return this->team;
}

bool mtm::Medic::legalAttack(const mtm::GridPoint &src,
        const mtm::GridPoint &dst, int distance,bool same_team, bool dst_empty) const {
    if (distance > range)
    {
        throw OutOfRange();
    }
    if (ammo < AMMO_PER_SHOT && !same_team)
    {
        throw OutOfAmmo();
    }
    if(src == dst || dst_empty)
    {
        throw  IllegalTarget();
    }
    return true;
}
