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
        static const CharacterType type = SNIPER;
    public:
        std::shared_ptr<Character> clone() const override;
        virtual int reload() const override ;
        char getTypeChar() const override ;
        CharacterType getType() const override ;
    };
}
#endif //HW3PARTC_SNIPER_H
