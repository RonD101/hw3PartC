//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_SOLDIER_H
#define HW3PARTC_SOLDIER_H

#include "Character.h"
#include <memory>

/**
* Implements the soldier class.
*
* Soldier inherits many of its functions from Character class.
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
*   The following functions are not inherited:
*   constructor
*   distance    - Return an int of the distance between src_coordinates and dst_coordinates.
*
*/

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

    /**	Constructor: create a new soldier class character
    *
    * @param
    * c_type - the type of the character (soldier)
    * c_team - the character's team
    * c_health - the character's health
    * c_ammo - the character's ammo
    * c_range - the character's range
    * c_power - the character's power
    */
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

    /**	distance: Return distance between two sets of coordinates
    *
    * @param
    * src_coordinates - the first set of coordinates
    * dst_coordinates - the second set of coordinates
    * @return
    * 	Int of the distance between the coordinates
    */
    static int distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
};

}
#endif //HW3PARTC_SOLDIER_H
