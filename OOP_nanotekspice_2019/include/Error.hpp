/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Error
*/

#pragma once

#include <string>

class NanoTekSpiceError : public std::exception
{
    public:
        NanoTekSpiceError(std::string const &message,
                std::string const &component = "Unknown") noexcept : _message(message), _component(component) {};
        virtual ~NanoTekSpiceError() = default;

        std::string const &getChipset() const noexcept { return _component; };
        virtual const char *what() const noexcept override { return _message.c_str(); };

    private:
        std::string _message; // exception.what() to write when catching the error
        std::string _component; // for example -> 4081, 4071, fileContent
};

class CircuitError : public NanoTekSpiceError
{
    public:
        CircuitError(std::string const &message,
                std::string const &component = "Unknown") noexcept : NanoTekSpiceError(message, component) {};
};

class ChipsetError : public NanoTekSpiceError
{
    public:
        ChipsetError(std::string const &message,
                std::string const &component = "Unknown") noexcept : NanoTekSpiceError("Component Error: " + message, component) {};
};

class ExecutionError : public NanoTekSpiceError
{
    public:
        ExecutionError(std::string const &message) noexcept : NanoTekSpiceError("Execution Error: "+ message, "Execution") {};
};

class FileError: public NanoTekSpiceError
{
    public:
        FileError(std::string const &message) noexcept : NanoTekSpiceError("File Error: " + message, "FileContent") {};
};
