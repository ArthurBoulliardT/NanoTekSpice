/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4069
*/

#include "4069.hpp"

namespace nts::comp
{
    _4069::_4069(const std::string &name) : Component(name, createPins(), "4081") {}

    void _4069::compute() noexcept
    {
        _pins[2-1]->refresh(!computeAndGetState(2, 1), isComputed(1));
        _pins[2-1]->callNextPins();
        _pins[4-1]->refresh(!computeAndGetState(4, 3), isComputed(3));
        _pins[4-1]->callNextPins();
        _pins[6-1]->refresh(!computeAndGetState(6, 5), isComputed(5));
        _pins[6-1]->callNextPins();
        _pins[8-1]->refresh(!computeAndGetState(8, 9), isComputed(9));
        _pins[8-1]->callNextPins();
        _pins[10-1]->refresh(!computeAndGetState(10, 11), isComputed(11));
        _pins[10-1]->callNextPins();
        _pins[12-1]->refresh(!computeAndGetState(12, 13), isComputed(13));
    }

    std::shared_ptr<nts::Pin> _4069::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this);
    }

    std::vector<std::shared_ptr<nts::Pin>> _4069::createPins()
    {
        auto pins =
            {
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::ELECTRICAL),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::ELECTRICAL)
            };
        return pins;
    }

    bool _4069::enoughLink(void) const noexcept
    {
        return  checkNotGateLinks(1, 2)
                && checkNotGateLinks(3, 4)
                && checkNotGateLinks(5, 6)
                && checkNotGateLinks(9, 8)
                && checkNotGateLinks(11, 10)
                && checkNotGateLinks(13, 12);
    }
}