/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** False
*/

#pragma once

#include <memory>
#include "Component.hpp"

namespace nts {
    namespace comp {
        class False : public Component
        {
            public:
                False(const std::string &name);
                void compute() noexcept final;
                bool enoughLink(void) const noexcept final;

            private:
                virtual std::vector<std::shared_ptr<Pin>> createPins();
                std::shared_ptr<nts::Pin> createPin(const nts::Pin::PinType &type);
        };
    }
}