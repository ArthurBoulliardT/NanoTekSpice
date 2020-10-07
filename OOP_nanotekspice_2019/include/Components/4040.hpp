/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4030
*/

#pragma once

#include <memory>
#include "Component.hpp"

namespace nts {
    namespace comp {
        class _4040 : public Component
        {
            public:
                _4040(const std::string &name);
                void compute() noexcept final;
                bool enoughLink(void) const noexcept final;
                void set_all_pins(Tristate);
                void compute_nb();

            private:
                virtual std::vector<std::shared_ptr<Pin>> createPins();
                std::shared_ptr<Pin> createPin(const Pin::PinType &type);
                Tristate toTristate(unsigned int i) const noexcept;

                unsigned int _count = 0;
                Tristate _prev_clock = FALSE;
        };
    }
}