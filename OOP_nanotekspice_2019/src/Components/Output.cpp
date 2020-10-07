/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4081
*/

#include "Component.hpp"
#include "Output.hpp"

namespace nts::comp
{
    Output::Output(const std::string &name) : Component(name, createPins(), "output") {}

    void Output::compute() noexcept
    {
        _pins[0]->compute();
    }

    std::shared_ptr<nts::Pin> Output::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this);
    }

    std::vector<std::shared_ptr<nts::Pin>> Output::createPins()
    {
        std::vector<std::shared_ptr<nts::Pin>> pins =
            {
                createPin(nts::Pin::INPUT)
            };
        return pins;
    }

    void Output::setOutput(nts::Tristate newValue) 
    { 
        std::string tristate = (newValue == TRUE ? "true" : "false");

        _pins.at(0)->refresh(newValue, true);
        file("Setting Output value to " + tristate);
    }

    bool Output::enoughLink(void) const noexcept
    {
        return _pins.at(0)->isMoreLinkThan(0);
    }

}