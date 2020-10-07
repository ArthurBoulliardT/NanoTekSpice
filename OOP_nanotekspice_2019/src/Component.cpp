/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Component
*/

#include <iomanip>
#include <algorithm>
#include "Component.hpp"
#include "Error.hpp"

namespace nts {

    bool Component::checkAndGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept
    {
        if (    _pins.at(pin1-1)->isMoreLinkThan(0)
                || _pins.at(pin2-1)->isMoreLinkThan(0)
                || _pins.at(pin3-1)->isMoreLinkThan(0)) 
        {
            return  _pins.at(pin1-1)->isMoreLinkThan(0)
                && _pins.at(pin2-1)->isMoreLinkThan(0)
                && _pins.at(pin3-1)->isMoreLinkThan(0);
        }
        return true;
    }

    bool Component::checkNAndGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept
    {
        if (    _pins.at(pin1-1)->isMoreLinkThan(0)
                || _pins.at(pin2-1)->isMoreLinkThan(0)
                || _pins.at(pin3-1)->isMoreLinkThan(0)) 
        {
            return  _pins.at(pin1-1)->isMoreLinkThan(0)
                && _pins.at(pin2-1)->isMoreLinkThan(0)
                && _pins.at(pin3-1)->isMoreLinkThan(0);
        }
        return true;
    }

    bool Component::checkOrGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept
    {
        if (    _pins.at(pin1-1)->isMoreLinkThan(0)
                || _pins.at(pin2-1)->isMoreLinkThan(0)
                || _pins.at(pin3-1)->isMoreLinkThan(0)) 
        {
            return  _pins.at(pin1-1)->isMoreLinkThan(0)
                && _pins.at(pin2-1)->isMoreLinkThan(0)
                && _pins.at(pin3-1)->isMoreLinkThan(0);
        }
        return true;
    }

    bool Component::checkNOrGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept
    {
        if (    _pins.at(pin1-1)->isMoreLinkThan(0)
                || _pins.at(pin2-1)->isMoreLinkThan(0)
                || _pins.at(pin3-1)->isMoreLinkThan(0)) 
        {
            return  _pins.at(pin1-1)->isMoreLinkThan(0)
                && _pins.at(pin2-1)->isMoreLinkThan(0)
                && _pins.at(pin3-1)->isMoreLinkThan(0);
        }
        return true;
    }

    bool Component::checkXOrGateLinks(size_t pin1, size_t pin2, size_t pin3) const noexcept
    {
        if (    _pins.at(pin1-1)->isMoreLinkThan(0)
                || _pins.at(pin2-1)->isMoreLinkThan(0)
                || _pins.at(pin3-1)->isMoreLinkThan(0)) 
        {
            return  _pins.at(pin1-1)->isMoreLinkThan(0)
                && _pins.at(pin2-1)->isMoreLinkThan(0)
                && _pins.at(pin3-1)->isMoreLinkThan(0);
        }
        return true;
    }

    bool Component::checkNotGateLinks(size_t pin1, size_t pin2) const noexcept
    {
        if (_pins.at(pin1-1)->isMoreLinkThan(0) 
            || _pins.at(pin2-1)->isMoreLinkThan(0)) 
        {
            return  _pins.at(pin1-1)->isMoreLinkThan(0)
                    && _pins.at(pin2-1)->isMoreLinkThan(0);
        }
        return true;
    }

    void Component::compute() noexcept
    {
    }

    bool Component::isANewPin(std::shared_ptr<Pin> &newPin) const
    {
        return !std::any_of(_pins.begin(), _pins.end(), [&newPin](const auto &ptr1) {
            return ptr1 == newPin;
        });
    }

    bool Component::isComputed(size_t pin) const
    {
        const auto &ptrPin = _pins.at(pin-1);

        return ptrPin->isComputed();
    }

    bool Component::isLoopPins(size_t pin1, size_t pin2)
    {
        const auto &ptrPin1 = _pins.at(pin1-1);
        const auto &ptrPin2 = _pins.at(pin2-1);
        std::shared_ptr<Pin> input;
        std::shared_ptr<Pin> output;

        if (ptrPin1->getType() != ptrPin2->getType()) {
            if (ptrPin1->getType() == nts::Pin::INPUT) {
                input = ptrPin1;
                output = ptrPin2;
            }
            else {
                input = ptrPin2;
                output = ptrPin1;
            }
            if (input->isLinkTo(output))
                return true;
        }
        return false;
    }

    void Component::addPins(std::vector<std::shared_ptr<Pin>> &pins)
    {
        for (auto &p : pins) {
            addPin(p);
        }
    }

    void Component::addPin(std::shared_ptr<Pin> &pin) 
    {
        if (isANewPin(pin))
            _pins.push_back(pin); 
    }
    
    void Component::setUncompted()
    {
        for (const auto &pin : _pins) {
            pin->setUsageStatusUnComputed();
        }
    }

    std::weak_ptr<Pin> Component::getPinAtIndex(size_t index)
    {
        std::weak_ptr<Pin> result;

        try {
            result = _pins.at(index);
        }
        catch (const std::exception &e) {
            file(index+1, "Cannot get pin at index ");
            throw ChipsetError("Cannot get pin at index " + std::to_string(index));
        }
        return result;
    }

    Tristate Component::computeAndGetState(size_t pin1, size_t pin2)
    {
        auto &ptrPin1 = _pins.at(pin1-1);
        auto &ptrPin2 = _pins.at(pin2-1);

        if (ptrPin1->getType() != ptrPin2->getType()) {
            if (ptrPin1->getType() == nts::Pin::INPUT) {
                auto &input = ptrPin1;
                auto &output = ptrPin2;

                if (isLoopPins(pin1, pin2)) {
                    if (!input->isComputed()) {
                        input->refresh(output->getState(), true);
                    }
                }
                return input->getState();
            }
            else {
                auto &input = ptrPin2;
                auto &output = ptrPin2;

                if (isLoopPins(pin1, pin2)) {
                    if (!input->isComputed()) {
                        input->refresh(output->getState(), true);
                    }
                }
                return input->getState();
            }
        }
        throw ExecutionError("Cannot compute an gate state of 2 same type pins");
    }

    void Component::setLink(std::size_t pin, IComponent &other, std::size_t otherPin)
    {
        try {
            Component otherComp = static_cast<Component &>(other);
            std::weak_ptr<Pin> ptrPin = this->getPinAtIndex(pin-1);
            std::weak_ptr<Pin> ptrOtherPin = otherComp.getPinAtIndex(otherPin-1);

            if (auto thePin = ptrPin.lock()) {
                if (auto theOtherPin = ptrOtherPin.lock()) {
                    if (thePin->getType() != theOtherPin->getType()) {
                        if (thePin->getType() != Pin::ELECTRICAL && theOtherPin->getType() != Pin::ELECTRICAL) {
                            thePin->addLink(ptrOtherPin);                
                            theOtherPin->addLink(ptrPin);
                        }
                        else {
                            throw FileError("Cannot link electrical pins of a component");
                        }
                    }
                    else {
                        throw FileError("Cannot link pins of same type");
                    }
                }
                else {
                    throw ExecutionError("Component Error: Trying to link to an inexisting Pin");
                }
            }
            else {
                throw ExecutionError("Component Error: Trying to link to an inexisting Pin");
            }
        }
        catch (const ExecutionError &e) {
            file("Pin at index " + std::to_string(pin) + " doesn't exist");
            throw ChipsetError("Trying to link to an inexisting Pin");
        }
        catch (const FileError &e) {
            file(e.what());
            throw ChipsetError(e.what());
        }
    }

    void Component::dump() const
    {
        std::cout << "Component '" << _name << "':" << std::endl;

        if (_pins.empty()) {
            output(" empty");
        }
        for (const auto &p : _pins) {
            if (p) {
                std::cout << std::setw(16) << *p.get() << std::endl;
            }
        }
    }
    
    void Component::removePins()
    {
        for (auto &p : _pins) {
            p->removePinLinks();
        }
    }

    void Component::removeSelfPins() noexcept
    {
        for (auto &p : _pins) {
            p->resetLinks();
        }
    }

    void Component::reset()
    {
        this->removePins();
        this->removeSelfPins();
        _pins.clear();
    }

    //Operator override
    Component &Component::operator=(const Component &aComp) noexcept
    {
        _pins = aComp._pins;
        return *this;
    }
}

//Operators override

std::ostream &operator<<(std::ostream &stream, const nts::Component &comp)
{
    return stream << comp.getPins();
}
