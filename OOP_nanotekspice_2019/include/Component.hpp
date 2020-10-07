/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Component
*/

#pragma once

#include <vector>
#include "Pin.hpp"

namespace nts {
    class Component : public IComponent, public log::Logs
    {
        public:
            Component(const std::string &name = "", std::vector<std::shared_ptr<Pin>> pins = std::vector<std::shared_ptr<Pin>>(), const std::string &type = ""): Logs(ERROR_FILE), _name(name), _pins(pins), _type(type) {};
            Component(const Component &comp): Logs(ERROR_FILE), _pins(comp._pins) {};
            virtual ~Component() {};

            //Overload operators
            Component &operator=(const Component &aComp) noexcept;

            //Compare fonction
            bool isANewPin(std::shared_ptr<Pin> &newPin) const;
            bool isLoopPins(size_t pin1, size_t pin2);
            bool isComputed(size_t pin) const;

            //Actions
            void reset();
            void removePins();
            void removeSelfPins(void) noexcept;
            virtual void dump() const;
            virtual void compute() noexcept;
            virtual void setLink(std::size_t pin, nts::IComponent &other, std::size_t otherPin);
            Tristate computeAndGetState(size_t pin1, size_t pin2);
            virtual bool enoughLink(void) const noexcept { return true; }; // Have to be implemented by child components
            bool checkAndGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept;
            bool checkNAndGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept;
            bool checkOrGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept;
            bool checkNOrGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept;
            bool checkXOrGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept;
            bool checkNotGateLinks(size_t pin1, size_t pin2) const noexcept;

            //Setters
            void addPins(std::vector<std::shared_ptr<Pin>> &pins);
            void addPin(std::shared_ptr<Pin> &pin);
            void setUncompted();
            
            //Getters
            std::weak_ptr<Pin> getPinAtIndex(size_t index);
            std::vector<std::shared_ptr<Pin>> getPins() const noexcept { return _pins; };
            size_t getNumberOfSharedPtr() const noexcept { return _pins.size(); };
            std::string getType() const noexcept { return _type; };
            std::string getName() const noexcept { return _name; };

        protected:
            std::string _name;
            std::vector<std::shared_ptr<Pin>> _pins;
            std::string _type;
    };
}

std::ostream &operator<<(std::ostream &stream, const nts::Component &comp);
nts::Tristate operator&&(nts::Tristate a, nts::Tristate b);
nts::Tristate operator||(nts::Tristate a, nts::Tristate b);
nts::Tristate operator^(nts::Tristate a, nts::Tristate b);
nts::Tristate operator!(nts::Tristate a);
