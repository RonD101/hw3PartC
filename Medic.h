//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_MEDIC_H
#define HW3PARTC_MEDIC_H

#include "Character.h"
#include <memory>

namespace mtm{
    class Medic: public Character{
        static const char typeChar = 'M';
        static const CharacterType type = MEDIC;
    public:
        std::shared_ptr<Character> clone() const override;
        virtual int reload() const override;
        char getTypeChar() const override ;
        CharacterType getType() const override ;
};
}
#endif //HW3PARTC_MEDIC_H
