//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_CHARACTER_H
#define HW3PARTC_CHARACTER_H

#include <memory>
#include "Auxiliaries.h"

namespace mtm{
    class Character{
    protected:
        units_t health;
        units_t ammo;
        units_t range;
        units_t power;
    public:
        virtual ~Character();
        virtual std::shared_ptr<Character> clone() const = 0;
        void addAmmo(int add_ammo);
        virtual int reload() const = 0;
        virtual char getTypeChar() const= 0;
        virtual CharacterType getType() const= 0;
    };
}

#endif //HW3PARTC_CHARACTER_H
