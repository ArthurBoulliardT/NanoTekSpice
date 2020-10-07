/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** True
*/

#include "True.hpp"
#include "Component.hpp"

namespace nts::comp
{
    True::True(const std::string &name) : Component(name, createPins(), "true") {}

    void True::compute() noexcept
    {
        _pins[0]->setUsageStatusComputed();
    }

    std::shared_ptr<nts::Pin> True::createPin(const nts::Pin::PinType &type)
    {
        return std::make_shared<nts::Pin>(type, this, nts::Tristate::TRUE);
    }

    std::vector<std::shared_ptr<nts::Pin>> True::createPins()
    {
        std::vector<std::shared_ptr<nts::Pin>> pins =
            {
                createPin(nts::Pin::OUTPUT)
            };
        return pins;
    }

    bool True::enoughLink(void) const noexcept
    {
        return _pins.at(0)->isMoreLinkThan(0);
    }
}