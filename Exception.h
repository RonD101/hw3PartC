//
// Created by Ron Dahan on 26/06/2020.
//

#ifndef HW3PARTC_EXCEPTION_H
#define HW3PARTC_EXCEPTION_H

#include <iostream>

namespace mtm{
    class Exception : public std::exception{};
    class GameException : public Exception{};

    class CellEmpty  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: CellEmpty";
        }
    };
    class IllegalCell  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalCell";
        }
    };
    class IllegalArgument  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class MoveTooFar  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: MoveTooFar";
        }
    };
    class CellOccupied  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: CellOccupied";
        }
    };
}

#endif //HW3PARTC_EXCEPTION_H
