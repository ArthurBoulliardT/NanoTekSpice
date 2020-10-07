/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** 4069
*/

#ifndef _4069_HPP_
#define _4069_HPP_

#include "Component.hpp"

namespace nts {
    namespace comp {
        class _4069 : public Component
        {
            public:
                _4069(const std::string &name);
                void compute() noexcept final;
                bool enoughLink(void) const noexcept final;

            private:
                virtual std::vector<std::shared_ptr<Pin>> createPins();
                std::shared_ptr<nts::Pin> createPin(const nts::Pin::PinType &type);                
        };
    }
}

#endif /* !4069_HPP_ */
