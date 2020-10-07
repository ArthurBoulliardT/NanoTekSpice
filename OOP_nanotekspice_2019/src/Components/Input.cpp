/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4081
*/

#include "Component.hpp"
#include "Input.hpp"

namespace nts::comp
{
    Input::Input(const std::string &name) : Component(name, createPins(), "input") {}

    void Input::compute() noexcept
    {
        _pins[0]->setUsageStatusComputed();
    }

    std::shared_ptr<nts::Pin> Input::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this);
    }

    std::vector<std::shared_ptr<nts::Pin>> Input::createPins()
    {
        std::vector<std::shared_ptr<nts::Pin>> pins =
            {
                createPin(nts::Pin::OUTPUT)
            };
        return pins;
    }

    void Input::setInput(nts::Tristate newValue) {
        std::string tristate = (newValue == TRUE ? "1" : "0");

        _pins.at(0)->refresh(newValue, true);
        file("Setting Input value to " + tristate);

    };

    bool Input::enoughLink(void) const noexcept
    {
        return _pins.at(0)->isMoreLinkThan(0);
    }


}