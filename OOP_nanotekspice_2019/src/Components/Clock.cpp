/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Clock
*/

#include "Clock.hpp"
#include "Component.hpp"

namespace nts::comp
{
    Clock::Clock(const std::string &name) : Component(name, createPins(), "clock") {}

    void Clock::compute() noexcept
    {
        auto currentTristate = _pins.at(0)->getState();
        nts::Tristate newTristate;

        if (!isComputed(1)) {
            if (currentTristate == TRUE)
                newTristate = FALSE;
            else if (currentTristate == FALSE)
                newTristate = TRUE;
            else 
                newTristate = UNDEFINED;
            _pins.at(0)->refresh(newTristate, true);
        }
        _pins[0]->setUsageStatusComputed();
    }

    std::shared_ptr<nts::Pin> Clock::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this, nts::Tristate::FALSE);
    }

    std::vector<std::shared_ptr<nts::Pin>> Clock::createPins()
    {
        std::vector<std::shared_ptr<nts::Pin>> pins =
            {
                createPin(nts::Pin::OUTPUT)
            };
        return pins;
    }

    void Clock::setClock(nts::Tristate newValue) {
        std::string tristate = (newValue == TRUE ? "1" : "0");

        _pins.at(0)->refresh(newValue, true);
        file("Setting Clock value to " + tristate);

    };

    bool Clock::enoughLink(void) const noexcept
    {
        return _pins.at(0)->isMoreLinkThan(0);
    }
}