/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** IComponent
*/

#pragma once

#include "Logs.hpp"
#include <memory>

namespace nts 
{
    enum Tristate
    {
        UNDEFINED = (-true),
        TRUE = true,
        FALSE = false
    };
    
    class IComponent
    {
        public:
            virtual ~IComponent() = default;

            virtual void compute() noexcept = 0;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin) = 0;
            virtual void dump() const = 0;
};
}