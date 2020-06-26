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
        std::shared_ptr<Character> clone() const override;
        int reload() const override ;
        bool legalMove(int distance) const override ;
//        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) const override;
        char getTypeChar() const override ;
        CharacterType getType() const override ;
    };
}
#endif //HW3PARTC_SNIPER_H
