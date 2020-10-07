/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Pin
*/

#include <iostream>
#include <fstream>
#include <algorithm>
#include "Pin.hpp"
#include "Error.hpp"

namespace nts {
    Pin::Pin(PinType type, IComponent *parentComp, Tristate state, const std::vector<std::weak_ptr<Pin>> &links) noexcept: 
            Logs(ERROR_FILE),
            _type(type),
            _state(state),
            _links(links),
            _parentComp(parentComp)
    {
    }

    void Pin::callNextPins() noexcept
    {
        for (auto &link : _links) {
            if (const auto &pin = link.lock()) {
                pin->compute();
            }
        }
    }

    void Pin::callPreviousPins() noexcept
    {
        for (auto &link : _links) {
            if (const auto &pin = link.lock()) {
                pin->compute();
            }
        }
    }

    void Pin::refresh(const Tristate &newState, bool couldYouUpdate) noexcept
    {
        if (_type == INPUT) {
            if (couldYouUpdate) {
                if (!isComputed()) {
                    setUsageStatusComputed();
                    _state = newState;
                }
            }
        }
        else if (_type == OUTPUT) {
            if (couldYouUpdate) {
                if (!isComputed()) {
                    setUsageStatusComputed();
                    _state = newState;
                }
            }
        }
    }

    void Pin::test()
    {
        if (_type == INPUT) {
            if (_links.size() > 0) {
                const auto &link = _links.at(0);

                if (const auto &theOuputLink = link.lock()) {
                    if (theOuputLink->getType() == OUTPUT) {
                        if (theOuputLink->isComputed()) {
                            refresh(theOuputLink->getState(), true);
                        }
                    }
                }
            }
        }
    }

    void Pin::compute()
    {
        if (_type == INPUT) {
            if (_links.size() > 0 && !isComputed()) {
                const auto &link = _links.at(0);

                if (const auto &theOuputLink = link.lock()) {
                    if (theOuputLink->getType() == OUTPUT) {
                        if (theOuputLink->isComputed()) {
                            refresh(theOuputLink->getState(), true);
                            if (isComputed())
                                _parentComp->compute();
                        }
                    }
                }
            }
        }
        else if (_type == OUTPUT) {
            // call component.computed
            if (!isComputed()) {
                if (_parentComp != nullptr)
                    _parentComp->compute();
            }
        }
    }

    bool Pin::isComputed() const noexcept
    {
        if (_usageStatus == COMPUTED) {
            return true;
        }
        return false;
    }

    bool Pin::isMoreLinkThan(size_t numberLinks) const noexcept
    {
        return _links.size() > numberLinks;
    }

    bool Pin::isLinkTo(const std::shared_ptr<Pin> &aPin) const
    {
        return !isANewPin(aPin);
    }

    bool Pin::isLinkTo(std::weak_ptr<Pin> &aPin) const
    {
        return !isANewPin(aPin);
    } 

    bool Pin::isANewPin(std::weak_ptr<Pin> &newPin) const
    {
        return !std::any_of(_links.begin(), _links.end(),[&newPin](const auto& ptr1) {
            return ptr1.lock() == newPin.lock();
        });
    }

    bool Pin::isANewPin(const std::shared_ptr<Pin> &newPin) const
    {
        return !std::any_of(_links.begin(), _links.end(),[&newPin](const auto& ptr1) {
            return ptr1.lock() == newPin;
        });
    }

    bool Pin::isEqual(const std::weak_ptr<Pin> &aPin) const noexcept
    {
        if (auto theNewPin = aPin.lock())
            return this == theNewPin.get();
        return false;
    }

    void Pin::addLink(std::weak_ptr<Pin> &newPin)
    {
        if (!isEqual(newPin)) {
            if (const auto &ptrPin = newPin.lock()) {
                this->addSharedPtr(ptrPin);
            }
        }
        else {
            throw ExecutionError("Tried to link the pin to himself");
        }
    }

    void Pin::addLink(const std::shared_ptr<Pin> &newPin) 
    {
        if (isANewPin(newPin)) {
            this->addSharedPtr(newPin);
        }
        else {
            throw ExecutionError("Tried to link a same pin");
        }
    }

    size_t Pin::getLinksNumber() const noexcept
    {
        size_t nb = 0;

        for (const auto &ptr : _links) {
            if (auto ptrPin = ptr.lock()) {
                nb++;
            }
        }
        return nb;
    }

    void Pin::removePin(const std::shared_ptr<Pin> &aPin)
    {
        auto it = std::_if(_links.begin(), _links.end(), [&aPin] (const auto &ptr1) {
            return aPin->isEqual(ptr1);
        });
        size_t index;
        
        if (it != _links.end()) {
            index = std::distance(_links.begin(), it);
            auto &ptr = _links.at(index);
            ptr.reset();                
        }
    }

    void Pin::removePin(const Pin &aPin)
    {
        auto it = std::find_if(_links.begin(), _links.end(), [&aPin] (const auto &ptr1) {
            return aPin.isEqual(ptr1);
        });
        size_t index;

        if (it != _links.end()) {
            index = std::distance(_links.begin(), it);
            auto &ptr = _links.at(index);
            ptr.reset();                
        }
    }

    void Pin::removePinLinks()
    {
        for (auto &ptr : _links) {
            if (auto ptrPin = ptr.lock()) {
                ptrPin->removePin(*this);
            }
        }
    }

    void Pin::resetLinks() noexcept 
    {
        for (auto &ptr : _links) {
            ptr.reset();
        }
    }

    //Operator override
    bool Pin::operator==(const Pin &aPin) noexcept
    {
        return _state == aPin.getState() && _type == aPin.getType();
    }

    bool Pin::operator!=(const Pin &aPin) noexcept
    {
        return !(*this == aPin);
    }

    Pin &Pin::operator=(const Pin &aPin) noexcept
    {
        _type = aPin.getType();
        _state = aPin.getState();
        _links = aPin.getLinks();
        return *this;
    }

    Pin &nts::Pin::operator=(const std::vector<std::weak_ptr<Pin>> &pins)
    {
        for (const auto &p : pins) {
            _links.push_back(p);
        }
        return *this;
    }

    //Private methods
    void Pin::addSharedPtr(const std::shared_ptr<Pin> &newPin)
    {
        bool added = false;
        
        for (auto &p : _links) {
            if (p.expired()) {
                p = newPin;
                added = true;
                break;
            }
        }
        if (added == false)
            _links.push_back(newPin);
    }
};

//Operators override

bool operator!=(std::weak_ptr<nts::Pin> &pin1, std::weak_ptr<nts::Pin> &pin2) noexcept
{
    return !(pin1 == pin2);
}

bool operator==(const std::weak_ptr<nts::Pin> &pin1, const std::weak_ptr<nts::Pin> &pin2) noexcept
{
    if (auto thePin1 = pin1.lock())
        if (auto thePin2 = pin2.lock())
            return thePin1.get() == thePin2.get();
    return false;
}

std::ostream &operator<<(std::ostream &stream, const nts::Pin &aPin)
{
    std::string typeString;
    std::string stateString;

    switch (aPin.getType())
    {
    case nts::Pin::OUTPUT:
        typeString = "Output";
        break;
    
    case nts::Pin::INPUT:
        typeString = "Input";
        break;

    default:
        typeString = "Electrical";
        break;
    }

    switch (aPin.getState())
    {
    case nts::Tristate::TRUE:
        stateString = "True";
        break;
    case nts::Tristate::FALSE:
        stateString = "False";
        break;
    default:
        stateString = "Undefined";
        break;
    }
    return stream << "Pin of state '" << stateString << "' and type '" << typeString << "' got " << aPin.getLinksNumber() << " connections" << " for " << aPin.getNumberOfWeakPtr() << " weak ptr!";
}

std::ostream &operator<<(std::ostream &stream, const std::vector<std::shared_ptr<nts::Pin>> pins)
{
    for (const auto &p : pins) {
        stream << p << std::endl;
    }
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const std::weak_ptr<nts::Pin> aPin)
{
    nts::Pin pin;
    log::Logs log;

    if (auto ptr = aPin.lock())
        stream << ptr;
    return stream;
}
