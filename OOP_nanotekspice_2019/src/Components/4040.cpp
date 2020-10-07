/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4040
*/

#include "Component.hpp"
#include "4040.hpp"

namespace nts::comp
{
    _4040::_4040(const std::string &name) : Component(name, createPins(), "4040") {

    }

    Tristate _4040::toTristate(unsigned int i) const noexcept
    {
        if (i)
            return TRUE;
        else
            return FALSE;
    }

    void _4040::set_all_pins(Tristate new_state)
    {
        _count = 0;
        for (int i = 1; i < 8; i++) {
            _pins[i - 1]->refresh(new_state, true);
        }
        _pins[9 - 1]->refresh(new_state, true);
        for (int i = 12; i < 16; i++) {
            _pins[i - 1]->refresh(new_state, true);
        }
    }

    void _4040::compute_nb()
    {
        _count += 1;

        _pins[9 - 1]->refresh(toTristate(_count % 2), true);
        _pins[7 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[6 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[5 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[3 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[2 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[4 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[13 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[12 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[14 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[15 - 1]->refresh(toTristate((_count >> 1) % 2), true);
        _pins[1 - 1]->refresh(toTristate((_count >> 1) % 2), true);
    }

    void _4040::compute() noexcept
    {
        auto clock_state = computeAndGetState(10, 9);
        auto reset_state = computeAndGetState(11, 9);

        if (clock_state == UNDEFINED || reset_state == UNDEFINED) {
            set_all_pins(UNDEFINED);
        }
        else if (reset_state == TRUE) {
            set_all_pins(FALSE);
        }
        else if (_prev_clock == TRUE && clock_state == FALSE) {
            compute_nb();
        }
        _prev_clock = clock_state;
    }

    std::shared_ptr<nts::Pin> _4040::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this);
    }

    std::vector<std::shared_ptr<nts::Pin>> _4040::createPins()
    {
        auto pins =
            {
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::ELECTRICAL),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::ELECTRICAL)
            };
        return pins;
    }

    bool _4040::enoughLink(void) const noexcept
    {
        return true;
    }

}