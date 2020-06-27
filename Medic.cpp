//
// Created by Ron Dahan on 22/06/2020.
//

#include "Medic.h"
#include "Exception.h"

#define AMMO_RELOAD 5
#define STEPS_NUM 5
#define AMMO_PER_SHOT 1

// returns 5 (ammo reload of medic)
void mtm::Medic::reload() {
    ammo += AMMO_RELOAD;
}

std::shared_ptr<mtm::Character> mtm::Medic::clone() const {
    return std::shared_ptr<Character>(new Medic(*this));
}

// returns 'M' if in CPP team or 'm' if in PYTHON team
char mtm::Medic::getTypeChar() const {
    if(team == PYTHON)
        return typeCharPython;
    return typeCharCpp;
}

// returns MEDIC
mtm::CharacterType mtm::Medic::getType() const {
    return MEDIC;
}

// function checks if distance param is smaller than STEPS_NUM
bool mtm::Medic::legalMove(int distance) const {
    return distance <= STEPS_NUM;
}

// constructor
mtm::Medic::Medic(mtm::CharacterType c_type, mtm::Team c_team, mtm::units_t c_health, mtm::units_t c_ammo,
                  mtm::units_t c_range, mtm::units_t c_power) {
        team = c_team;
        type = c_type;
        health = c_health;
        ammo = c_ammo;
        range = c_range;
        power = c_power;

}

// returns the team this character belongs to
mtm::Team mtm::Medic::getTeam() const {
    return this->team;
}

/** function returns true if character in src can attack character in dst and no exception was thrown
    if target is out of character's range, throws exception OutOfRange
    if character's out of ammo and target is on different team, throws exception OutOfAmmo
    if dst is empty or character tries to attack itself, throws exception IllegalTarget
 */
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

/** function to calculate damage.
    if target is on the same team as the attacker, the damage will be positive, ie healing them
    calls function removeShot from Character.h to reduce ammo by 1
*/
void mtm::Medic::attack(const mtm::GridPoint &dst, bool same_team, std::vector<std::pair<GridPoint
        ,units_t >>& grids_to_attack, std::pair<int,int> board_size) {
    units_t damage = power;
    if(!same_team)
    {
        this->removeShot();
        damage *= -1;
    }
    grids_to_attack.push_back(std::pair<GridPoint,units_t >(dst,damage));
    return;
}
