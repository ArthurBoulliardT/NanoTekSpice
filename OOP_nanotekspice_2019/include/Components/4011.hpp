/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4011
*/

#pragma once

#include <memory>
#include "Component.hpp"

namespace nts {
    namespace comp {
        class _4011 : public Component
        {
            public:
                _4011(const std::string &name);
                void compute() noexcept final;
                bool enoughLink(void) const noexcept final;

            private:
                virtual std::vector<std::shared_ptr<Pin>> createPins();
                std::shared_ptr<nts::Pin> createPin(const nts::Pin::PinType &type);
                
        };
    }
}