/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Execution
*/

#include <csignal>
#include <functional>
#include "Execution.hpp"
#include "Error.hpp"
#include "Input.hpp"
#include "Output.hpp"
#include "Clock.hpp"

namespace nts {
    
    bool isLooping = false;

    void Execution::initStartExecutionCommandFunctions(void)
    {
        _commandFunctions.clear();
        _commandFunctions.insert(std::make_pair(INPUT, std::bind(&Execution::inputCommand, this, std::placeholders::_1, std::placeholders::_2)));
    }

    void Execution::initRunTimeExecutionCommandFunctions(void)
    {
        _commandFunctions.clear();
        _commandFunctions.insert(std::make_pair(EXIT, std::bind(&Execution::exitCommand, this, std::placeholders::_1, std::placeholders::_2)));
        _commandFunctions.insert(std::make_pair(DISPLAY, std::bind(&Execution::displayCommand, this, std::placeholders::_1, std::placeholders::_2)));
        _commandFunctions.insert(std::make_pair(INPUT, std::bind(&Execution::inputCommand, this, std::placeholders::_1, std::placeholders::_2)));
        _commandFunctions.insert(std::make_pair(SIMULATE, std::bind(&Execution::simulateCommand, this, std::placeholders::_1, std::placeholders::_2)));
        _commandFunctions.insert(std::make_pair(LOOP, std::bind(&Execution::loopCommand, this, std::placeholders::_1, std::placeholders::_2)));
        _commandFunctions.insert(std::make_pair(DUMP, std::bind(&Execution::dumpCommand, this, std::placeholders::_1, std::placeholders::_2)));
    }

    void Execution::readInput()
    {
        std::string input;

        initRunTimeExecutionCommandFunctions();
        try {
            if (_aCircuit->doesAllInputCompGotValues() && _aCircuit->isCompleteCircuit()) {
                while (std::cin.eof() == 0) {
                    std::cout << "> ";
                    std::getline(std::cin, input);
                    if (!input.empty()) {
                        if (!interpretCommand(input))
                            break;
                    }
                }
                if (std::cin.eof() == 1) {
                    output("");
                }
            }
        }
        catch (const ExecutionError &e) {
            file(e.what());
            throw ExecutionError("Stoping the program");
        }
        catch (const FileError &e) {
            file(e.what());
            throw ExecutionError("Stoping the program");
        }
    }

    bool Execution::interpretCommand(const std::string &command)
    {
        std::smatch matches;
        std::string match;
    
        file(command, "\nReading input command line: ");
        try {
            for (const auto &interpreter : _commandsInterpreter) {
                if (std::regex_search(command, matches, interpreter.second)) {
                    if (!_commandFunctions.empty()) {
                        match = matches.str(1);
                        if (match.size() == command.size()) {
                            return _commandFunctions[interpreter.first](match, matches);
                        }
                        else {
                            throw ExecutionError("Unkonw command");
                        }
                    }
                }
            }
            throw ExecutionError("Unknow command");
        }
        catch (ExecutionError &e) {
            throw e;
        }
        catch (const std::exception &e) {
            throw ExecutionError("Unknow command");
        }
    }

    void Execution::readCommands(const std::vector<std::string> &allCommands)
    {
        for (const auto &command : allCommands) {
            if (!command.empty()) {
                interpretCommand(command);
            }
        }
    }

    void Execution::readFileFromStartedInput(std::vector<std::string> &allCommands)
    {
        std::smatch matches;
        bool runCommand = false;

        for (auto &command : allCommands) {
            if (std::regex_search(command, matches, regFile)) {
                _parser.setFileName(command);
                _parser.openFile();
                _parser.readFile(*(_aCircuit.get()));
                _parser.closeFile();
                command = "";
                runCommand = true;
            }
        }
        if (runCommand == false)
            throw ExecutionError("No provided configuration file");
    }


    void Execution::readStartingInput(int argc, char **argv)
    {
        auto allCommands = putInContainer(argc, argv);

        try {
            readFileFromStartedInput(allCommands);
            readCommands(allCommands);
        }
        catch (const ExecutionError &e) {
            file(e.what());
            throw ExecutionError("stoping the program");
        }
    }

    std::vector<std::string> Execution::putInContainer(int argc, char **argv)
    {
        std::string command;
        std::vector<std::string> allCommands(argc - 1);

        for (int i = 0; i < argc - 1; i++) {
            command = argv[i+1];
            allCommands[i] = command;
        }
        return allCommands;
    }

    void Execution::starting() noexcept
    {
        std::string nothingStr;
        std::smatch nothingMatches;

        simulateCommand(nothingStr, nothingMatches);
        displayCommand(nothingStr, nothingMatches);
    }

    bool Execution::exitCommand(std::string &line, std::smatch &matches) noexcept
    {
        (void)line;
        (void)matches;
        file("Stoping the program");
        return false;
    }

    bool Execution::displayCommand(std::string &line, std::smatch &matches) noexcept
    {
        std::string tristate;

        (void)line;
        (void)matches;

        file("display");
        for (auto &p : _aCircuit->getCircuit()) {
            if (p.second->getType() == "output") {
                auto comp = static_cast<comp::Output *>(p.second.get());
                tristate = ( comp->getOutput() == TRUE ? "1" : "0");

                output(p.first + "=" + tristate);
            }
        }
        return true;
    }

    bool Execution::inputCommand(std::string &line, std::smatch &matches)
    {
        const auto &name = matches.str(2);
        const auto &value = matches.str(3);
        Tristate pinValue;

        (void)line;
        file("set an input");
        for (auto &p : _aCircuit->getCircuit()) {
            if (p.first == name) {
                if (p.second->getType() == "input") {
                    auto comp = static_cast<comp::Input *>(p.second.get());
                    pinValue = (std::stoi(value) >= 1 ? TRUE : FALSE);

                    comp->setInput(pinValue);
                    return true;
                }
                else if (p.second->getType() == "clock") {
                    auto comp = static_cast<comp::Clock *>(p.second.get());
                    pinValue = (std::stoi(value) >= 1 ? TRUE : FALSE);

                    comp->setClock(pinValue);
                    return true;
                }
                else 
                    throw ExecutionError("Cannot bind " + value + " to component " + name + " of type " + p.second->getType());
            }
        }
        throw ExecutionError("Unknow component " + name);
    }

    bool Execution::simulateCommand(std::string &line, std::smatch &matches) noexcept
    {
        (void)line;
        (void)matches;

        file("simulate");
        _aCircuit->compute();
        return true;
    }

    void signalHandler(int signal)
    {
        (void)signal;
        isLooping = false;
    }

    bool Execution::loopCommand(std::string &line, std::smatch &matches) noexcept
    {
        signal(SIGINT, signalHandler);  

        (void)line;
        (void)matches;
        isLooping = true;
        while (isLooping) {
            _aCircuit->compute();
        }

        return true;
    }

    bool Execution::dumpCommand(std::string &line, std::smatch &matches) noexcept
    {
        (void)line;
        (void)matches;
        file("Dumping");
        _aCircuit->dump();
        return true;
    }

    void Execution::printRegex(Execution::CommandType type) noexcept
    {
        std::string aString("");

        switch (type)
        {
        case EXIT:
            aString = "EXIT";
            break;
        case DISPLAY:
            aString = "DISPLAY";
            break;
        case INPUT:
            aString = "INPUT";
            break;
        case SIMULATE:
            aString = "SIMULATE";
            break;
        case LOOP:
            aString = "LOOP";
            break;
        case DUMP:
            aString = "DUMP";
            break;
        default:
            break;
        }

        output(aString);
    }}