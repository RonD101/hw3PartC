//
// Created by Ron Dahan on 26/06/2020.
//

#ifndef HW3PARTC_EXCEPTIONS_H
#define HW3PARTC_EXCEPTIONS_H

#include <iostream>

/**
* Implements Game's exception
*
* All of Game exception are in this file.
*
* The following exception are available:
*   Exceptions.
*   Exceptions::GameException.
*   Exceptions::GameException::IllegalArgument.
*   Exceptions::GameException::IllegalCell.
*   Exceptions::GameException::CellEmpty.
*   Exceptions::GameException::CellOccupied.
*   Exceptions::GameException::MoveTooFar.
*   Exceptions::GameException::OutOfRange.
*   Exceptions::GameException::OutOfAmmo.
*   Exceptions::GameException::IllegalTarget.
*
*/

namespace mtm{
    class Exceptions : public std::exception{
    public:
        ~Exceptions() override = default;
    };
    class GameException : public Exceptions{
    public:
        ~GameException() override = default;
    };

    class IllegalArgument  : public mtm::GameException {
    public:
        ~IllegalArgument() override = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalArgument";
        }
    };
    class IllegalCell  : public mtm::GameException {
    public:
        ~IllegalCell() override = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalCell";
        }
    };
    class CellEmpty  : public mtm::GameException {
    public:
        ~CellEmpty() override = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: CellEmpty";
        }
    };
    class CellOccupied  : public mtm::GameException {
    public:
        ~CellOccupied() override = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: CellOccupied";
        }
    };
    class MoveTooFar  : public mtm::GameException {
    public:
        ~MoveTooFar() override = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: MoveTooFar";
        }
    };
    class OutOfRange  : public mtm::GameException {
    public:
        ~OutOfRange() override = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: OutOfRange";
        }
    };
    class OutOfAmmo  : public mtm::GameException {
    public:
        ~OutOfAmmo() override  = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: OutOfAmmo";
        }
    };
    class IllegalTarget  : public mtm::GameException {
    public:
        ~IllegalTarget() override = default;
        const char* what() const noexcept override
        {
            return "A game related error has occurred: IllegalTarget";
        }
    };
}

#endif //HW3PARTC_EXCEPTIONS_H
