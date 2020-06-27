//
// Created by Ron Dahan on 22/06/2020.
//

#include "Sniper.h"
#include "Game.h"
#include "Exception.h"

#define AMMO_RELOAD 2
#define STEPS_NUM 4
#define AMMO_PER_SHOT 1
#define DIVISOR 2
#define THIRD_ATTACK 3
#define DOUBLE_DAMAGE 2

using namespace mtm;
using std::shared_ptr;

std::shared_ptr<Character> mtm::Sniper::clone() const {
    return shared_ptr<Character>(new Sniper(*this));
}

// returns 2 (ammo reload of sniper)
void mtm::Sniper::reload() {
    ammo += AMMO_RELOAD;
}

// returns 'N' if in CPP team or 'n' if in PYTHON team
char Sniper::getTypeChar() const {
    if(team == PYTHON)
        return typeCharPython;
    return typeCharCpp;
}

// returns SNIPER
CharacterType Sniper::getType() const {
    return SNIPER;
}

// function checks if distance param is smaller than STEPS_NUM
bool Sniper::legalMove(int distance) const {
    return distance <= STEPS_NUM;
}

// constructor
Sniper::Sniper(CharacterType c_type, Team c_team, units_t c_health,
        units_t c_ammo, units_t c_range, units_t c_power) {
    team = c_team;
    type = c_type;
    health = c_health;
    ammo = c_ammo;
    range = c_range;
    power = c_power;
}

// returns the team this character belongs to
Team Sniper::getTeam() const {
    return this->team;
}

/** function returns true if character in src can attack character in dst and no exception was thrown
    if target is out of character's range, throws exception OutOfRange
    if character's out of ammo throws exception OutOfAmmo
    if target is on the same team as the attacker, or if dst is empty, throes exception IllegalTarget
 */
bool Sniper::legalAttack(const GridPoint &src, const GridPoint &dst,
        int distance, bool same_team, bool dst_empty) const {
    units_t half_range = static_cast<int>(std::ceil(double(range)/DIVISOR));
    if (distance > range || distance < half_range)
    {
        throw OutOfRange();
    }
    if (ammo < AMMO_PER_SHOT)
    {
        throw OutOfAmmo();
    }
    if(same_team || dst_empty)
    {
        throw  IllegalTarget();
    }

    return true;
}

/** function calculates damage done by an attack. every third attack damage is doubled
    calls function removeShot from Character.h to reduce ammo by 1
 */
void Sniper::attack(const GridPoint &dst, bool same_team, std::vector<std::pair<GridPoint,
        units_t >>& grids_to_attack, std::pair<int,int> board_size) {
    units_t damage = -power;
    if(attack_count % THIRD_ATTACK == 0)
    {
        damage *= DOUBLE_DAMAGE;
    }
    attack_count++;
    grids_to_attack.push_back(std::pair<GridPoint, units_t >(dst, damage));
    this->removeShot();
    return;
}



