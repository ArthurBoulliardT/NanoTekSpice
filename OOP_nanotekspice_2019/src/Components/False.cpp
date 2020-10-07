/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** False
*/

#include "False.hpp"
#include "Component.hpp"

namespace nts::comp
{
    False::False(const std::string &name) : Component(name, createPins(), "false") {}

    void False::compute() noexcept
    {
        _pins[0]->setUsageStatusComputed();
    }

    std::shared_ptr<nts::Pin> False::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this, nts::Tristate::FALSE);
    }

    std::vector<std::shared_ptr<nts::Pin>> False::createPins()
    {
        std::vector<std::shared_ptr<nts::Pin>> pins =
            {
                createPin(nts::Pin::OUTPUT)
            };
        return pins;
    }

    bool False::enoughLink(void) const noexcept
    {
        return _pins.at(0)->isMoreLinkThan(0);
    }
}