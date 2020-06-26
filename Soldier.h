//
// Created by Ron Dahan on 22/06/2020.
//

#ifndef HW3PARTC_SOLDIER_H
#define HW3PARTC_SOLDIER_H

#include "Character.h"
#include <memory>

namespace mtm{
class Soldier: public Character{
    static const char type = 'S';
public:
        std::shared_ptr<Character> clone() const override;
        virtual int reload() const override ;
        char getType() const override ;
    };

}
#endif //HW3PARTC_SOLDIER_H
