//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_SNIPER_H
#define HW3PARTC_SNIPER_H

#include "Character.h"
#include <memory>

namespace mtm{
    class Sniper: public Character{
        static const char typeCharCpp = 'N';
        static const char typeCharPython = 'n';
        int attack_count = 1;
    public:
        Sniper(CharacterType c_type,Team c_team, units_t c_health, units_t c_ammo, units_t c_range, units_t c_power);
        std::shared_ptr<Character> clone() const override;
        ~Sniper() override = default;
        void reload() override ;
        bool legalMove(int distance) const override ;
        char getTypeChar() const override ;
        CharacterType getType() const override ;
        Team getTeam() const override ;
        bool legalAttack(const GridPoint& src, const GridPoint& dst,int distance,
                bool same_team, bool dst_empty) const override;
        void attack(const GridPoint& dst, bool same_team, std::vector<std::pair<GridPoint
                ,units_t >>& grids_to_attack, std::pair<int,int> board_size) override;
    };
}
#endif //HW3PARTC_SNIPER_H
