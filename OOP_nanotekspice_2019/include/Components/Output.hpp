/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Output
*/

#pragma once

#include <memory>
#include "Component.hpp"

namespace nts {
    namespace comp {
        class Output : public Component
        {
            public:
                Output(const std::string &name);
                void compute() noexcept final;
                void setOutput(Tristate newValue);
                Tristate getOutput() { return _pins.at(0)->getState(); };
                bool enoughLink(void) const noexcept final;

            private:
                virtual std::vector<std::shared_ptr<Pin>> createPins();
                std::shared_ptr<nts::Pin> createPin(const nts::Pin::PinType &type);
        };
    }
}