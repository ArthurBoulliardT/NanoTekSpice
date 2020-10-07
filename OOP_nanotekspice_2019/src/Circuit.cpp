/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Circuit
*/

#include "Error.hpp"
#include "Circuit.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "True.hpp"
#include "False.hpp"
#include "Clock.hpp"
#include "4081.hpp"
#include "4071.hpp"
#include "4069.hpp"
#include "4040.hpp"
#include "4030.hpp"
#include "4011.hpp"
#include "4001.hpp"

namespace nts
{
    void Circuit::computeInputs()
    {
        for (const auto &p : _circuit) {
            if (p.second->getType() == "input"
                || p.second->getType() == "clock"
                || p.second->getType() == "true"
                || p.second->getType() == "false") {
                p.second->compute();
            }
        }
        for (const auto &p : _circuit) {
            if (p.second->getType() == "input"
                || p.second->getType() == "clock"
                || p.second->getType() == "true"
                || p.second->getType() == "false") {
                if (const auto &ptr = p.second->getPinAtIndex(0).lock()) {
                    ptr->callNextPins();
                }
            }
        }
    }

    void Circuit::putAllUncompted()
    {
        for (const auto &p : _circuit) {
            p.second->setUncompted();
        }
    }

    void Circuit::compute()
    {
        computeInputs();
        putAllUncompted();
    }

    bool Circuit::doesAllInputCompGotValues()
    {
        for (const auto &p : _circuit) {
            if (p.second->getType() == "input"
                || p.second->getType() == "clock") {
                if (p.second->getPins().at(0)->getState() == UNDEFINED) {
                    throw ExecutionError("The component " + p.first + " haven't got any values");
                }
            }
        }
        return true;
    }

    bool Circuit::isCompleteCircuit()
    {
        for (const auto &p : _circuit) {
            if (p.second->enoughLink() == false)
                throw FileError("The component " + p.first + " is not completely link");
        }
        return true;
    }

    void Circuit::dump() const noexcept
    {
        for (auto &comp : _circuit) {
            comp.second->dump();
            std::cout << std::endl;
        }
    }

    std::unique_ptr<Component> Circuit::createA(const std::string &name, const std::string &value) const noexcept
    {
        const auto &func = _factory[value];

        return func(name);
    }

    void Circuit::createComponent(const std::string &name, const std::string &value)
    {
        (void)value;
        (void)name;
        if (_circuit.find(name) == _circuit.end()) {
            file("Creating the " + value + " component " + name);
            _circuit.insert({ name, createA(name, value)});
            file("Added it to the circuit");
        }
        else
        {
            throw FileError("Can't create a component with same name than an other one");
        }
        
    }

    void Circuit::setLink(int pin1, int pin2, const std::string &nameComp1, const std::string &nameComp2)
    {
        auto &ptrComp1 = _circuit[nameComp1];
        auto &ptrComp2 = _circuit[nameComp2];

        file("Linking " + nameComp1 + ":" + std::to_string(pin1) + " with " + nameComp2 + ":" + std::to_string(pin2));
        ptrComp1->setLink(pin1, *(ptrComp2.get()), pin2);
    }

    // static methods
    std::unique_ptr<Component> Circuit::createInput(const std::string &name)
    {
        return std::make_unique<nts::comp::Input>(name);
    }
    
    std::unique_ptr<Component> Circuit::createTrue(const std::string &name)
    {
        return std::make_unique<nts::comp::True>(name);
    }
    
    std::unique_ptr<Component> Circuit::createFalse(const std::string &name)
    {
        return std::make_unique<nts::comp::False>(name);
    }
    
    std::unique_ptr<Component> Circuit::createClock(const std::string &name)
    {
        return std::make_unique<nts::comp::Clock>(name);
    }
    
    std::unique_ptr<Component> Circuit::createOutput(const std::string &name)
    {
        return std::make_unique<nts::comp::Output>(name);
    }
    
    std::unique_ptr<Component> Circuit::create4081(const std::string &name)
    {
        return std::make_unique<nts::comp::_4081>(name);
    }

    std::unique_ptr<Component>Circuit::create4071(const std::string &name)
    {
        return std::make_unique<nts::comp::_4071>(name);
    }

    std::unique_ptr<Component>Circuit::create4069(const std::string &name)
    {
        return std::make_unique<nts::comp::_4069>(name);
    }

    std::unique_ptr<Component>Circuit::create4040(const std::string &name)
    {
        return std::make_unique<nts::comp::_4040>(name);
    }

    std::unique_ptr<Component>Circuit::create4030(const std::string &name)
    {
        return std::make_unique<nts::comp::_4030>(name);
    }

    std::unique_ptr<Component>Circuit::create4011(const std::string &name)
    {
        return std::make_unique<nts::comp::_4011>(name);
    }

    std::unique_ptr<Component>Circuit::create4001(const std::string &name)
    {
        return std::make_unique<nts::comp::_4001>(name);
    }

}