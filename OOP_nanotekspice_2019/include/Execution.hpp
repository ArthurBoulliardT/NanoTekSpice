/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Execution
*/

#pragma once

#include <memory>

#include "Circuit.hpp"
#include "Parsing.hpp"

namespace nts {
    class Execution : public log::Logs
    {
        public:
            enum CommandType {
                EXIT,
                DISPLAY,
                INPUT,
                SIMULATE,
                LOOP,
                DUMP
            };

            Execution(std::unique_ptr<nts::Circuit> &circuit): Logs(ERROR_FILE), _aCircuit(std::make_unique<nts::Circuit>()), _parser(), _commandFunctions() {
                _aCircuit.swap(circuit);
                initStartExecutionCommandFunctions();
            };
            ~Execution() {};

            void readStartingInput(int argc, char **argv);
            void readInput();
            void readCommands(const std::vector<std::string> &allCommands);
            void starting() noexcept;

            void dump() const noexcept { _aCircuit->dump(); };

            //Getters
            std::unique_ptr<Circuit> &getCircuit() noexcept { return _aCircuit; };
            Parsing &getParser() noexcept { return _parser; }

        private:
            static inline std::regex regFile = std::regex("(\\..+)");
            static inline std::unordered_map <CommandType, std::regex> _commandsInterpreter
            =   { 
                {EXIT, std::regex("(exit)") },
                {DISPLAY, std::regex("(display)")},
                {INPUT, std::regex("((\\w+)?=(\\d+)?)")},
                {SIMULATE, std::regex("(simulate)")},
                {LOOP, std::regex("(loop)")},
                {DUMP, std::regex("(dump)")},
                };

            std::unique_ptr<Circuit> _aCircuit;
            Parsing _parser;
            std::unordered_map<CommandType, std::function<bool(std::string &line, std::smatch &matches)>> _commandFunctions;

            // private methods
            std::vector<std::string> putInContainer(int argc, char **argv);

            void initRunTimeExecutionCommandFunctions(void);
            void initStartExecutionCommandFunctions(void);
            bool interpretCommand(const std::string &command);
            void readFileFromStartedInput(std::vector<std::string> &allCommands);

            bool exitCommand(std::string &line, std::smatch &matches) noexcept;
            bool displayCommand(std::string &line, std::smatch &matches) noexcept;
            bool inputCommand(std::string &line, std::smatch &matches);
            bool simulateCommand(std::string &line, std::smatch &matches) noexcept;
            bool loopCommand(std::string &line, std::smatch &matches) noexcept;
            bool dumpCommand(std::string &line, std::smatch &matches) noexcept;

            void printRegex(CommandType type) noexcept;

    };
}