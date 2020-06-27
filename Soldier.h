//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_SOLDIER_H
#define HW3PARTC_SOLDIER_H

#include "Character.h"
#include <memory>

namespace mtm{
class Soldier: public Character{
    static const char typeChar = 'S';
public:
    Soldier(CharacterType c_type,Team c_team, units_t c_health, units_t c_ammo, units_t c_range, units_t c_power);
    std::shared_ptr<Character> clone() const override;
    virtual int reload() const override ;
    char getTypeChar() const override ;
    CharacterType getType() const override ;
    Team getTeam() const override ;
    bool legalMove(int distance) const override ;
};

}
#endif //HW3PARTC_SOLDIER_H
