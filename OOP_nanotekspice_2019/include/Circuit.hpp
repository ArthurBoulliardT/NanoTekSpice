/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Circuit
*/

#pragma once

#include <unordered_map>
#include <map>
#include <memory>
#include <functional>
#include "Component.hpp"

namespace nts {
    class Circuit : public log::Logs {
        public:
            Circuit(): Logs(ERROR_FILE), _circuit() {};
            ~Circuit() {};

            void createComponent(const std::string &name, const std::string &value);
            void setLink(int pin1, int pin2, const std::string &nameComp1, const std::string &nameComp2);
            std::map <std::string, std::unique_ptr<Component>> &getCircuit() noexcept { return _circuit; };
            bool doesAllInputCompGotValues();
            bool isCompleteCircuit();
            void putAllUncompted();

            void compute();

            void dump() const noexcept;

        private:
            //Private Methods
            void computeInputs();

            std::unique_ptr<Component> createA(const std::string &name, const std::string &value) const noexcept;
            static std::unique_ptr<Component>createInput(const std::string &name);
            static std::unique_ptr<Component>createTrue(const std::string &name);
            static std::unique_ptr<Component>createFalse(const std::string &name);
            static std::unique_ptr<Component>createClock(const std::string &name);
            static std::unique_ptr<Component>createOutput(const std::string &name);
            static std::unique_ptr<Component>create4081(const std::string &name);
            static std::unique_ptr<Component>create4071(const std::string &name);
            static std::unique_ptr<Component>create4069(const std::string &name);
            static std::unique_ptr<Component>create4040(const std::string &name);
            static std::unique_ptr<Component>create4030(const std::string &name);
            static std::unique_ptr<Component>create4011(const std::string &name);
            static std::unique_ptr<Component>create4001(const std::string &name);

            //Private attributs
            std::map <std::string, std::unique_ptr<Component>> _circuit;
            static inline std::unordered_map <std::string, std::function<std::unique_ptr<Component>(const std::string &)>> _factory 
            =   { 
                {"input", createInput},
                {"true", createTrue},
                {"false", createFalse},
                {"clock", createClock},
                {"output", createOutput},
                {"4081", create4081},
                {"4071", create4071},
                {"4069", create4069},
                {"4040", create4040},
                {"4030", create4030},
                {"4011", create4011},
                {"4001", create4001}
                };
    };
}