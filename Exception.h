//
// Created by Ron Dahan on 26/06/2020.
//

#ifndef HW3PARTC_EXCEPTION_H
#define HW3PARTC_EXCEPTION_H

#include <iostream>

namespace mtm{
    class Exception : public std::exception{};
    class GameException : public Exception{};
}

#endif //HW3PARTC_EXCEPTION_H
