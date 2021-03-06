//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_SNIPER_H
#define HW3PARTC_SNIPER_H

#include "Character.h"
#include <memory>

/**
* Implements the sniper class.
*
* Sniper inherits many of its functions from Character class.
*
* The following functions are inherited:
*   destructor and copy constructor (all default).
*   clone    - Return a smart pointer for independent object.
*   reload		- Reload character ammo.
*   getTypeChar	- Return character type.
*   getTeam  - Return character team.
*   legalMove  - Check if character intent move is legal.
*   legalAttack		    - Check if character can attack is legal.
*   attack	        - commence character attack.
*
*   constructor is not inheridted
*
*/

namespace mtm{
    class Sniper: public Character{
        static const char typeCharCpp = 'N';
        static const char typeCharPython = 'n';
        int attack_count = 1;
        static const int ammo_reload = 2;
        static const int steps_num =  4;
        static const int ammo_per_shot = 1;
        static const int divisor = 2;
        static const int third_attack = 3;
        static const int double_damage = 2;
    public:

        /**	Constructor: create a new sniper class character
        *
        * @param
        * c_type - the type of the character (sniper)
        * c_team - the character's team
        * c_health - the character's health
        * c_ammo - the character's ammo
        * c_range - the character's range
        * c_power - the character's power
        */
        Sniper(CharacterType c_type,Team c_team, units_t c_health, units_t c_ammo, units_t c_range, units_t c_power);
        std::shared_ptr<Character> clone() const override;
        ~Sniper() override = default;
        void reload() override ;
        bool legalMove(int distance) const override ;
        char getTypeChar() const override ;
        Team getTeam() const override ;
        bool legalAttack(const GridPoint& src, const GridPoint& dst,int distance,
                bool same_team, bool dst_empty) const override;
        void attack(const GridPoint& dst, bool same_team, std::vector<std::pair<GridPoint
                ,units_t >>& grids_to_attack, std::pair<int,int> board_size) override;
    };
}
#endif //HW3PARTC_SNIPER_H
