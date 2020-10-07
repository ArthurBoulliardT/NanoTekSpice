/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4081
*/

#include "Component.hpp"
#include "4081.hpp"

namespace nts::comp
{
    _4081::_4081(const std::string &name) : Component(name, createPins(), "4081") {}

    void _4081::compute() noexcept
    {
        _pins[3-1]->refresh(computeAndGetState(3, 1) && computeAndGetState(3, 2), isComputed(1) && isComputed(2));
        _pins[3-1]->callNextPins();
        _pins[4-1]->refresh(computeAndGetState(4, 5) && computeAndGetState(4, 6), isComputed(5) && isComputed(6));
        _pins[4-1]->callNextPins();
        _pins[10-1]->refresh(computeAndGetState(10, 8) && computeAndGetState(10, 9), isComputed(8) && isComputed(9));
        _pins[10-1]->callNextPins();
        _pins[11-1]->refresh(computeAndGetState(11, 12) && computeAndGetState(11, 13), isComputed(12) && isComputed(13));
        _pins[11-1]->callNextPins();
    }

    std::shared_ptr<nts::Pin> _4081::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this);
    }

    std::vector<std::shared_ptr<nts::Pin>> _4081::createPins()
    {
        auto pins =
            {
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::ELECTRICAL),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::OUTPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::INPUT),
                createPin(nts::Pin::ELECTRICAL)
            };
        return pins;
    }

    bool _4081::enoughLink(void) const noexcept
    {
        return  checkAndGateLinks(1, 2, 3) 
                && checkAndGateLinks(5, 6, 4) 
                && checkAndGateLinks(8, 9, 10) 
                && checkAndGateLinks(12, 13, 11);
    }
}