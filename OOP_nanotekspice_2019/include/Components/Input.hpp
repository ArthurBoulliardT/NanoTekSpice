/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Input
*/

#pragma once

#include <memory>
#include "Component.hpp"

namespace nts {
    namespace comp {
        class Input : public Component
        {
            public:
                Input(const std::string &name);
                void compute() noexcept final;
                void setInput(Tristate newValue);
                bool enoughLink(void) const noexcept final;

            private:
                virtual std::vector<std::shared_ptr<Pin>> createPins();
                std::shared_ptr<nts::Pin> createPin(const nts::Pin::PinType &type);
        };
    }
}