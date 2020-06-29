//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_SOLDIER_H
#define HW3PARTC_SOLDIER_H

#include "Character.h"
#include <memory>

namespace mtm{
class Soldier: public Character{
    static const char typeCharCpp = 'S';
    static const char typeCharPython = 's';
    static const int ammo_reload = 3;
    static const int steps_num = 3;
    static const int ammo_per_shot = 1;
    static const int divisor = 3;
    static const int half = 2;
public:
    Soldier(CharacterType c_type,Team c_team, units_t c_health, units_t c_ammo, units_t c_range, units_t c_power);
    ~Soldier() override = default;
    std::shared_ptr<Character> clone() const override;
    void reload() override ;
    char getTypeChar() const override ;
    Team getTeam() const override ;
    bool legalMove(int distance) const override ;
    bool legalAttack(const GridPoint& src, const GridPoint& dst,int distance,
            bool same_team, bool dst_empty) const override;
    void attack(const GridPoint& dst, bool same_team, std::vector<std::pair<GridPoint
            ,units_t >>& grids_to_attack, std::pair<int,int> board_size) override;
    static int distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
};

}
#endif //HW3PARTC_SOLDIER_H
