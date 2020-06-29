//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_CHARACTER_H
#define HW3PARTC_CHARACTER_H

#include <memory>
#include "Auxiliaries.h"
#include <vector>

/**
* Implements abstract class Character under namespace mtm.
*
* Character is and abstract class which all character type inherit there basic function.
*
* The following functions are available:
*   constructor ,destructor and copy constructor (all default).
*   clone[virtual]    - Return a smart pointer for independent object.
*   removeShot		- Subtract character ammo.
*   reload[virtual]		- Reload character ammo.
*   getTypeChar[virtual]	- Return character type.
*   getTeam[virtual]   - Return character team.
*   legalMove[virtual]  - Check if character intent move is legal.
*   legalAttack[virtual]		    - Check if character can attack is legal.
*   attack[virtual]	        - commence character attack.
*   addHealth	        - Add to character health.
*   getHealth	        - Return character health.
*
*/


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

/**
*	Character destructor: pure virtual function which destroy and free
 *	    all of the character data.
* @return
* 	No return Value
*/
        virtual ~Character() = default;

/**
*	clone: clone all of character info
*
* @return
*   Smart pointer for independent object.
*/
        virtual std::shared_ptr<Character> clone() const = 0;

/**
*	removeShot: Subtract one ammo.
*
* @param
* index - The index of the element
* @return
* 	No return value
*/
        void removeShot();

/**
*	reload: Reload character ammo by different amount per character type.
*
* @return
* 	No return value
*/
        virtual void reload() = 0;

/**
*	getTypeChar: Return the char symbol of the player depending of is type and team.
*
* @return
* 	Character symbol.
*/
        virtual char getTypeChar() const= 0;

/**
*	getTeam: Return a character team.
*
* @return
* 	Character team
*/
        virtual Team getTeam() const= 0;

/**
*	legalMove: Check if the character intent move is legal.
*
* @param
* distance - the distance between current location to destination.
* @return
* 	True if move is legal (otherwise throw appropriate exception)
* @exception
*   IllegalCell -   if character move out of board bounds.
*   CellEmpty -     if the source cell is empty.
*   MoveTooFar -    if character move to far according to personal rules.
*   CellOccupied -  id destination cell is occupied.
*/
        virtual bool legalMove(int distance) const = 0;

/**
*	legalAttack: Check if attack is legal.
*
* @param
* src - Attacker postion
* index - The index of the element
* index - The index of the element
* index - The index of the element
* @return
* 	Reference to the const element
* @exception
*   Return BadAccess for invalid read of memory.
*/
        virtual bool legalAttack(const GridPoint& src, const GridPoint& dst,int distance,
                bool same_team, bool dst_empty) const = 0;
        virtual void attack(const GridPoint& dst, bool same_team, std::vector<std::pair<GridPoint
                ,units_t >>& grids_to_attack, std::pair<int,int> board_size) = 0;
        void addHealth(int value);
        int getHealth();
    };
}

#endif //HW3PARTC_CHARACTER_H
