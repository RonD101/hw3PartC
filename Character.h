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
* 	True if move is legal (otherwise throw appropriate exception).
* @exception
*   IllegalCell -   if character move out of board bounds.
*   CellEmpty -     if the source cell is empty.
*   MoveTooFar -    if character move to far according to personal rules.
*   CellOccupied -  if destination cell is occupied.
*/
        virtual bool legalMove(int distance) const = 0;

/**
*	legalAttack: Check if attack is legal.
*
* @param
* src - Attacker position.
* dst - Attack destination.
* distance - Distance between src and dst.
* same_team - True if the attacker and attacked character are from the same team, false otherwise.
* dst_empty - True if attack destination have no character.
* @return
* 	True if attack met character rules (otherwise throw appropriate exception).
* @exception
*   OutOfRange -    if character attack out of personal range.
*   OutOfAmmo -     if character is out of ammo.
*   IllegalTarget -  if attack doesn't meet character personal rules.
*/
        virtual bool legalAttack(const GridPoint& src, const GridPoint& dst,int distance,
                bool same_team, bool dst_empty) const = 0;

/**
*	attack: Commence character attack.
*
* @param
* dst - Attack destination.
* same_team - True if the attacker and attacked character are from the same team, false otherwise.
* dst_empty - True if attack destination have no character.
* grids_to_attack - Array of potions and attack value indicating how we should attack and by how much.
* board_size - Pair which contain board Dimension.
* @return
* 	No return value.
 * 	grids_to_attack is updated with attacks values and potion.
*/
        virtual void attack(const GridPoint& dst, bool same_team, std::vector<std::pair<GridPoint
                ,units_t >>& grids_to_attack, std::pair<int,int> board_size) = 0;

/**
*	addHealth: Add health to character.
*
* @param
* value - Amount of health to add.
* @return
* 	No return value.
 * 	grids_to_attack is updated with attacks values and potion.
*/
        void addHealth(units_t value);

/**
*	getHealth: Return character health.
*
* @return
* 	Character health.
*/
        int getHealth();
    };
}

#endif //HW3PARTC_CHARACTER_H
