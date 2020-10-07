/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4081
*/

#include "Component.hpp"
#include "4011.hpp"

namespace nts::comp
{
    _4011::_4011(const std::string &name) : Component(name, createPins(), "4011") {}

    void _4011::compute() noexcept
    {
        _pins[3-1]->refresh(!(computeAndGetState(3, 1) && computeAndGetState(3, 2)), isComputed(1) && isComputed(2));
        _pins[3-1]->callNextPins();
        _pins[4-1]->refresh(!(computeAndGetState(4, 5) && computeAndGetState(4, 6)), isComputed(5) && isComputed(6));
        _pins[4-1]->callNextPins();
        _pins[10-1]->refresh(!(computeAndGetState(10, 8) && computeAndGetState(10, 9)), isComputed(9) && isComputed(9));
        _pins[10-1]->callNextPins();
        _pins[11-1]->refresh(!(computeAndGetState(11, 12) && computeAndGetState(11, 13)), isComputed(12) && isComputed(13));
        _pins[11-1]->callNextPins();
    }

    std::shared_ptr<nts::Pin> _4011::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this);
    }

    std::vector<std::shared_ptr<nts::Pin>> _4011::createPins()
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

    bool _4011::enoughLink(void) const noexcept
    {
        return  checkNAndGateLinks(1, 2, 3) 
                && checkNAndGateLinks(5, 6, 4) 
                && checkNAndGateLinks(8, 9, 10) 
                && checkNAndGateLinks(12, 13, 11);
    }

}