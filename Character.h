//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_CHARACTER_H
#define HW3PARTC_CHARACTER_H

#include <memory>

namespace mtm{
    class Character{
    protected:
        int health;
        int ammo;
        int range;
        int power;
    public:
        virtual ~Character();
        virtual std::shared_ptr<Character> clone() const = 0;
        void addAmmo(int add_ammo);
        virtual int reload() const = 0;
    };
}

#endif //HW3PARTC_CHARACTER_H
