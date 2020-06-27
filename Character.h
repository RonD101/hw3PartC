//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_CHARACTER_H
#define HW3PARTC_CHARACTER_H

#include <memory>
#include "Auxiliaries.h"
#include "TemArray.h"
#include <vector>

namespace mtm{
    class Character{
    protected:
        Team team;
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
        CharacterType type;
    public:
        virtual ~Character() = default;
        virtual std::shared_ptr<Character> clone() const = 0;
        void removeShot();
        virtual void reload() = 0;
        virtual char getTypeChar() const= 0;
        virtual Team getTeam() const= 0;
        virtual bool legalMove(int distance) const = 0;
        virtual bool legalAttack(const GridPoint& src, const GridPoint& dst,int distance,
                bool same_team, bool dst_empty) const = 0;
        virtual void attack(const GridPoint& dst, bool same_team, std::vector<std::pair<GridPoint
                ,units_t >>& grids_to_attack, std::pair<int,int> board_size) = 0;
        void addHealth(int value);
        int getHealth();
    };
}

#endif //HW3PARTC_CHARACTER_H
