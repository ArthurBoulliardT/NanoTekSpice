/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Tristate
*/

#include "IComponent.hpp"

nts::Tristate operator&&(nts::Tristate a, nts::Tristate b) noexcept
{
    if (a == nts::TRUE && b == nts::TRUE)
        return nts::TRUE;
    else if (a == nts::FALSE || b == nts::FALSE)
        return nts::FALSE;
    return nts::UNDEFINED;
}

nts::Tristate operator||(nts::Tristate a, nts::Tristate b) noexcept
{
    if (a == nts::TRUE || b == nts::TRUE)
        return nts::TRUE;
    else if (a == nts::FALSE && b == nts::FALSE)
        return nts::FALSE;
    return nts::UNDEFINED;
}

nts::Tristate operator^(nts::Tristate a, nts::Tristate b) noexcept
{
    if (a == b) {
        if (a == nts::UNDEFINED)
            return nts::UNDEFINED;
        return nts::FALSE;
    } else if (a == nts::UNDEFINED || b == nts::UNDEFINED)
        return nts::UNDEFINED;
    return nts::TRUE;
}

nts::Tristate operator!(nts::Tristate a) noexcept
{
    if (a == nts::Tristate::FALSE)
        return nts::Tristate::TRUE;
    else if (a == nts::Tristate::TRUE)
        return nts::Tristate::FALSE;
    return nts::Tristate::UNDEFINED;
}