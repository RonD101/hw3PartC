//
// Created by Ron Dahan on 26/06/2020.
//

#ifndef HW3PARTC_EXCEPTION_H
#define HW3PARTC_EXCEPTION_H

#include <iostream>

namespace mtm{
    class Exception : public std::exception{};
    class GameException : public Exception{};

    class IllegalArgument  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalCell";
        }
    };
    class CellEmpty  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: CellEmpty";
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
    class OutOfRange  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: OutOfRange";
        }
    };
    class OutOfAmmo  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: OutOfAmmo";
        }
    };
    class IllegalTarget  : public mtm::GameException {
    public:
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalTarget";
        }
    };
}

#endif //HW3PARTC_EXCEPTION_H
