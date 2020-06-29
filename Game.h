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
        std::shared_ptr<Character> getCharacter(const GridPoint& coordinates) const;
        static int distance(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void clearDeads();
        static const char space = ' ';
    public:
        Game(int height, int width);
        Game(const Game& game);

        /**	operator=: assign game
        *
        * @param
        * other - The matrix which we copy the values from.
        * @return
        * 	The assigned matrix
        */
        Game &operator=(const Game& other);
        void addCharacter(const GridPoint& coordinates, std::shared_ptr<Character> character);
        static std::shared_ptr<Character> makeCharacter(CharacterType type, Team team,
                                                        units_t health, units_t ammo, units_t range, units_t power);
        void reload(const GridPoint & coordinates);
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);
        void attack(const GridPoint & src_coordinates, const GridPoint & dst_coordinates);
        friend std::ostream& operator<<(std::ostream& os, const Game &game);
        bool isOver(Team* winningTeam = NULL) const;
    };
    std::ostream& operator<<(std::ostream& os, const Game &game);
}
#endif //HW3PARTC_GAME_H
