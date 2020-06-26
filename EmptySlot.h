//
// Created by Ron Dahan on 23/06/2020.
//

#ifndef HW3PARTC_EMPTYSLOT_H
#define HW3PARTC_EMPTYSLOT_H

#include <memory>
#include "Character.h"

namespace mtm{
    class EmptySlot: public Character{
        static const char typeChar = ' ';
    public:
        class EmptyCell;
        EmptySlot() = default;
        ~EmptySlot() override = default;
        std::shared_ptr<Character> clone() const override;
        virtual int reload() const override ;
        char getTypeChar() const override ;
    };

    class EmptySlot::EmptyCell  : public std::exception {};
}

#endif //HW3PARTC_EMPTYSLOT_H
