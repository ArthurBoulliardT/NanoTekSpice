/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Pin
*/

#pragma once

#include <vector>
#include "IComponent.hpp"

namespace nts {
    class Pin : public log::Logs
    {
        public:
            enum PinType {
                ELECTRICAL, // useless type of pin, thow error if this type
                INPUT,
                OUTPUT
            };

            enum UsageStatus {
                COMPUTED,
                UNCOMPUTED
            };

            Pin(PinType type = ELECTRICAL,
                IComponent *parentComp = nullptr,
                Tristate state = nts::Tristate::UNDEFINED, 
                const std::vector<std::weak_ptr<Pin>> &links = std::vector<std::weak_ptr<Pin>>()) noexcept;
            Pin(const Pin &pin): Logs(ERROR_FILE), _type(pin._type), _state(pin._state), _links(pin._links), _parentComp(pin._parentComp) {};
            ~Pin() noexcept {};

            //Overload operators
            bool operator==(const Pin &aPin) noexcept;
            bool operator!=(const Pin &aPin) noexcept;
            Pin &operator=(const Pin &aPin) noexcept;
            Pin &operator=(const std::vector<std::weak_ptr<Pin>> &pins);

            //Compare fonction
            bool isEqual(const std::weak_ptr<Pin> &aPin) const noexcept;
            bool isANewPin(std::weak_ptr<Pin> &newPin) const;
            bool isANewPin(const std::shared_ptr<Pin> &newPin) const;
            bool isLinkTo(const std::shared_ptr<Pin> &aPin) const;
            bool isLinkTo(std::weak_ptr<Pin> &aPin) const;
            bool isMoreLinkThan(size_t numberLinks) const noexcept;
            bool isComputed() const noexcept;

            // Action
            void addLink(std::weak_ptr<Pin> &newPin);
            void addLink(const std::shared_ptr<Pin> &newPin);
            void compute();
            void resetLinks() noexcept;
            void removePin(const std::shared_ptr<Pin> &aPin);
            void removePin(const Pin &aPin);
            void removePinLinks();
            void callNextPins() noexcept;
            void callPreviousPins() noexcept;


            void test();


            // Setters
            void setType(const PinType &type) noexcept { _type = type; };
            void refresh(const Tristate &newState, bool couldYouUpdate) noexcept;
            void setLinks(const std::vector<std::weak_ptr<Pin>> &link) noexcept { *this = link; };
            void setUsageStatus(UsageStatus newStatus) noexcept { _usageStatus = newStatus; };
            void setUsageStatusComputed() noexcept { _usageStatus = COMPUTED; };
            void setUsageStatusUnComputed() noexcept  { _usageStatus = UNCOMPUTED; };

            // Getters
            Tristate getState() const noexcept { return _state; };
            PinType getType() const noexcept { return _type; };
            const std::vector<std::weak_ptr<Pin>> &getLinks() const noexcept { return _links; };
            size_t getLinksNumber() const noexcept;
            size_t getNumberOfWeakPtr() const noexcept { return _links.size(); };
            UsageStatus getUsageStatus() const noexcept { return _usageStatus; };

        private:
            PinType _type;
            Tristate _state;
            // STD::LIST POUR LES LINKS
            std::vector<std::weak_ptr<Pin>> _links;
            UsageStatus _usageStatus = UNCOMPUTED;
            IComponent *_parentComp;

            //Private Methods
            void addSharedPtr(const std::shared_ptr<Pin> &newPin);

    };
}

bool operator==(const std::weak_ptr<nts::Pin> &pin1, const std::weak_ptr<nts::Pin> &pin2) noexcept;
bool operator!=(std::weak_ptr<nts::Pin> &pin1, std::weak_ptr<nts::Pin> &pin2) noexcept;

std::ostream &operator<<(std::ostream &stream, const nts::Pin &aPin);
std::ostream &operator<<(std::ostream &stream, const std::vector<std::shared_ptr<nts::Pin>> pins);
std::ostream &operator<<(std::ostream &stream, const std::weak_ptr<nts::Pin> aPin);