//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_GAME_H
#define HW3PARTC_GAME_H
#include "Auxiliaries.h"
#include "Character.h"
#include "Matrix.h"

/**
* Implements class Game under namespace mtm.
* Uses Matrix<std::shared_ptr<Character>> from Matrix.h to
* implement the board.
*
* The following functions are available:
*   constructor and copy constructor.
*   getCharacter    - Return smart pointer for the contents of the board in the coordinates param.
*   distance		- Return an int of the distance between src_coordinates and dst_coordinates.
*   clearDeads		- Removes all characters on the board with health <= 0.
*   addCharacter	- Adds an existing character to the game.
*   makeCharacter   - Creates a new character with all the required character parameters
*   move  	        - Moves a character in the game from src_coordinates to dst_coordinates
*   attack		    - Makes character in src_coordinates attack character in dst_coordinates
*   isOver	        - Return true the game has been won, return false if not.
*
* The following operators are available:
*   operator=      - Assignment of one game to the other
*   operator<<     - Return an ostream value to print
*/

namespace mtm{
    class Game{
        Matrix<std::shared_ptr<Character>> board;

        /**	getCharacter: Returns a smart pointer of a character in a board.
       *
       * @param
       * coordinates - the coordinates from which to return the smart pointer
       * @return
       * 	Smart pointer of the character in the coordinates.
       * @exceptions
       *    Return IllegalCell if the coordinates are outside the board limits
       */
        std::shared_ptr<Character> getCharacter(const GridPoint& coordinates) const;

        /**	distance: Return distance between two sets of coordinates
        *
        * @param
        * src_coordinates - the first set of coordinates
        * dst_coordinates - the second set of coordinates
        * @return
        * 	Int of the distance between the coordinates
        */
        static int distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        /**	clearDeads: Clears the board of all characters with health lower or equal to 0
        *
        * @param
        * @return
        */
        void clearDeads();
        static const char space = ' ';
    public:

        /**	Constructor: create a new game
        *
        * @param
        * height - The number of rows for the new game board
        * width - The number of columns for the new game board
        * @return
        * 	The new game
        */
        Game(int height, int width);

        /**
        *	Copy Constructor: create a copy game
        *
        * @param
        * game - The game which we copy the board from.
        * @return
        * 	The copied game
        */
        Game(const Game& game);

        /**	operator=: assign game
        *
        * @param
        * other - The game which we copy the board from.
        * @return
        * 	The assigned game
        */
        Game &operator=(const Game& other);

        /**	addCharacter: Adds an existing character to the game
        *
        * @param
        * coordinates - the coordinates of where to place the character in the board
        * character - the character to add to the game
        * @return
        * @exceptions
        *    return IllegalCell if the coordinates are out of range
        *    return CellOccupied if the the coordinates are occupied
         */
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);

        /**	makeCharacter: creates a new character
        *
        * @param
        * type - the type of the character (soldier, sniper. medic)
        * team - the character's team
        * health - the character's health
        * ammo - the character's ammo
        * range - the character's range
        * power - the character's power
        * @return
        * Smart pointer of the new character
        * @exceptions
        *    return IllegalArgument if one of the params are negative or if health isn't positive
        */
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);

        /**	reload: adds ammo to a character
        *
        * @param
        * coordinates - the coordinates of the character
        * @return
        * @exceptions
        *    return CellEmpty if the coodinates param is not pointing to a character
        */
        void reload(const GridPoint & coordinates);

        /**	move: moves a character from one coordinates to another
        *
        * @param
        * src_coordinates - the coordinates of the character
        * dst_coordinates - the coordinates we wish to move the character to
        * @return
        * @exceptions
        *    return CellEmpty if src_coordinates param is not pointing to a character
        *    return MoveTooFar if destination is too far
        *    return CellOccupied if the destination is occupied by another character
        */
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);

        /**	attack: makes a character attack another character
        *
        * @param
        * src_coordinates - the coordinates of the character
        * dst_coordinates - the coordinates we wish to attack
        * @return
        * @exceptions
        *   return CellEmpty if src_coordinates or dst_character are empty
        *   return IllegalCell if src_coordinates or dst_character are outside the game board
        *   return OutOfRange if dst_character is out of range of the attacker
        *   return OutOfAmmo if character in src_coordinates dosn't have enough ammo to attack
        *   return IllegalTarget if:
        *   medic tries to attack itself or an empty cell
        *   sniper tries to attack a teammate or an empty cell
        *   soldier tries to attack a cell not in its row or column
        */
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);

        /**	operator<<: Returns a osstream to print.
        *
        * @param
        * os - ostream for the message to print
        * game - the game to print
        * @return
        * 	The ostream
        */
        friend std::ostream& operator<<(std::ostream& os, const Game &game);

        /**	isOver: Return a bool to show if game is won by a team
        *
        * @param
        * winningTeam - if this param is not null, and function returns true, this pointer will now have the identity of the winning team.
        *               otherwise, the param is not updated
        * @return
        * true if only characters from one team are still in the game
        * false if characters from both teams are still in the game or if no characters are in the game
        */
        bool isOver(Team* winningTeam = NULL) const;
    };
    std::ostream& operator<<(std::ostream& os, const Game &game);
}
#endif //HW3PARTC_GAME_H
