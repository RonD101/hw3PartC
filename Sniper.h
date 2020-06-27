//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_SNIPER_H
#define HW3PARTC_SNIPER_H

#include "Character.h"
#include <memory>

namespace mtm{
    class Sniper: public Character{
        static const char typeChar = 'N';
    public:
        Sniper(CharacterType c_type,Team c_team, units_t c_health, units_t c_ammo, units_t c_range, units_t c_power);
        std::shared_ptr<Character> clone() const override;
        int reload() const override ;
        bool legalMove(int distance) const override ;
        char getTypeChar() const override ;
        CharacterType getType() const override ;
        Team getTeam() const override ;
    };
}
#endif //HW3PARTC_SNIPER_H
