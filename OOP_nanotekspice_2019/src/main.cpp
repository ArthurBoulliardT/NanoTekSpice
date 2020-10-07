/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** main
*/

#include <iostream>
#include <exception>
#include "Error.hpp"
#include "Parsing.hpp"
#include "Circuit.hpp"
#include "Execution.hpp"

void execution(int argc, char **argv)
{
    log::Logs log(ERROR_FILE);

    log.file("------------Build new Error logs------------");
    if (argc > 1) {
        auto circuit = std::make_unique<nts::Circuit>();
        nts::Execution execution(circuit);

        try {
            execution.readStartingInput(argc, argv);
            execution.starting();
            execution.readInput();
        }
        catch (const FileError &e) {
            log.output(e.what());
        }
        catch (const ExecutionError &e) {
            log.output(e.what());
        }
        catch (const std::exception &e) {
            log.file(e.what(), "Unpredicted error :");
            log.output("Stoping the Program");
        }
    }
    else {
        log.file("Put some Arguments: configuration file, component state, etc...");
        log.output("");
    }
}

int main(int argc, char **argv)
{
    log::Logs log(ERROR_FILE);

    log.cleanFile();
    execution(argc, argv);
    return 0;
}