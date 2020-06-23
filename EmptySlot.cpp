//
// Created by Ron Dahan on 23/06/2020.
//

#include "EmptySlot.h"

using std::shared_ptr;

shared_ptr<mtm::Character> mtm::EmptySlot::clone() const {
    return shared_ptr<Character>(new EmptySlot(*this));
}

mtm::EmptySlot::~EmptySlot() {
}

mtm::EmptySlot::EmptySlot() {
}

int mtm::EmptySlot::reload() const {
    throw EmptySlot::EmptyCell();
}
