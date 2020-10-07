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

void testPins(void)
{
    try {
        log::Logs log(ERROR_FILE);

        nts::Pin pin1(nts::Pin::OUTPUT, nts::Tristate::TRUE);
        nts::Pin pin2(nts::Pin::INPUT, nts::Tristate::FALSE);
        nts::Pin pin3(nts::Pin::INPUT, nts::Tristate::TRUE);
        nts::Pin pin4(nts::Pin::OUTPUT, nts::Tristate::UNDEFINED);
        
        //std::shared_ptr<nts::Pin> ptrPin1 = std::make_shared<nts::Pin>(pin1);
        std::shared_ptr<nts::Pin> ptrPin2 = std::make_shared<nts::Pin>(pin2);
        std::shared_ptr<nts::Pin> ptrPin3 = std::make_shared<nts::Pin>(pin3);
        std::shared_ptr<nts::Pin> ptrPin4 = std::make_shared<nts::Pin>(pin4);

        //std::cout << pin1 << std::endl;
        std::cout << pin2 << std::endl;
        std::cout << pin4 << std::endl;
        std::cout << pin3 << std::endl;

        //std::weak_ptr<nts::Pin> ptr1 = ptrPin1;
        std::weak_ptr<nts::Pin> ptr2 = ptrPin2;
        std::weak_ptr<nts::Pin> ptr3 = ptrPin3;
        std::weak_ptr<nts::Pin> ptr4 = ptrPin4;


        {
            std::shared_ptr<nts::Pin> ptrPin1 = std::make_shared<nts::Pin>(pin1);
            std::weak_ptr<nts::Pin> ptr1 = ptrPin1;
                {
                    if (auto newSharedPTr1 = ptr1.lock())
                    {
                        std::cout << "shared ptr 1er scope " << std::endl;
                        auto newSharedPTr2 = ptr1.lock();
                    }
                    if (auto newSharedPTr3 = ptr1.lock())
                    {
                        auto newSharedPTr4 = ptr1.lock();
                        auto newSharedPTr5 = ptr1.lock();
                    }
                }
            ptrPin1.reset();
                {
                    if (auto newSharedPTr1 = ptr1.lock())
                    {
                        std::cout << "shared ptr 2nd scope" << std::endl;
                        auto newSharedPTr2 = ptr1.lock();
                    }
                    else
                    {
                        std::cout << "deleted shared ptr " << std::endl;
                    }
                    
                    if (auto newSharedPTr3 = ptr1.lock())
                    {
                        std::cout << "shared ptr 3th scope" << std::endl;
                        auto newSharedPTr4 = ptr1.lock();
                        auto newSharedPTr5 = ptr1.lock();
                    }
                    else
                    {
                            std::cout << "deleted shared ptr " << std::endl;
                    }
                }
        }


        //ptrPin1->addLink(ptr2);
        //ptrPin1->addLink(ptr3);
        //ptrPin1->addLink(ptr4);

        //ptrPin2->addLink(ptr1);
        ptrPin2->addLink(ptr3);
        ptrPin2->addLink(ptr2);
        ptrPin2->addLink(ptr4);

        //std::cout << ptr1 << std::endl;
        std::cout << ptr2 << std::endl;
        std::cout << ptr3 << std::endl;
        std::cout << ptr4 << std::endl;

    }
    catch (const std::exception &e) {
        std::cout << e.what() << std::endl;
    }
}

void testComponent()
{
    log::Logs log(ERROR_FILE);

    nts::Pin pin1(nts::Pin::OUTPUT, nts::Tristate::TRUE);
    nts::Pin pin2(nts::Pin::INPUT, nts::Tristate::FALSE);
    nts::Pin pin3(nts::Pin::INPUT, nts::Tristate::TRUE);
    nts::Pin pin4(nts::Pin::OUTPUT, nts::Tristate::UNDEFINED);
    nts::Pin pin5(nts::Pin::INPUT, nts::Tristate::FALSE);
    nts::Pin pin6(nts::Pin::INPUT, nts::Tristate::TRUE);
    nts::Pin pin7(nts::Pin::INPUT, nts::Tristate::TRUE);
    nts::Pin pin8(nts::Pin::INPUT, nts::Tristate::TRUE);
        
    std::shared_ptr<nts::Pin> ptrPin1 = std::make_shared<nts::Pin>(pin1);
    std::shared_ptr<nts::Pin> ptrPin2 = std::make_shared<nts::Pin>(pin2);
    std::shared_ptr<nts::Pin> ptrPin3 = std::make_shared<nts::Pin>(pin3);
    std::shared_ptr<nts::Pin> ptrPin4 = std::make_shared<nts::Pin>(pin4);
    std::shared_ptr<nts::Pin> ptrPin5 = std::make_shared<nts::Pin>(pin5);
    std::shared_ptr<nts::Pin> ptrPin6 = std::make_shared<nts::Pin>(pin6);
    std::shared_ptr<nts::Pin> ptrPin7 = std::make_shared<nts::Pin>(pin7);
    std::shared_ptr<nts::Pin> ptrPin8 = std::make_shared<nts::Pin>(pin8);
    std::shared_ptr<nts::Pin> ptrPin9;

    std::vector<std::shared_ptr<nts::Pin>> comp1Vector;
    std::vector<std::shared_ptr<nts::Pin>> comp2Vector;

    comp1Vector.push_back(ptrPin1);
    comp1Vector.push_back(ptrPin2);

    comp2Vector.push_back(ptrPin4);
    comp2Vector.push_back(ptrPin5);

    nts::Component comp1("comp1", comp1Vector);
    nts::Component comp2("comp2", comp2Vector);

    comp1.dump();
    comp2.dump();
    if (ptrPin1 == comp1.getPinAtIndex(0).lock()) {
        std::cout << "good link for Pin1" << std::endl;
    }
    if (ptrPin2 == comp1.getPinAtIndex(1).lock()) {
        std::cout << "good link for Pin2" << std::endl;
    }

    if (ptrPin4 == comp2.getPinAtIndex(0).lock()) {
        std::cout << "good link for Pin3" << std::endl;
    }
    if (ptrPin5 == comp2.getPinAtIndex(1).lock()) {
        std::cout << "good link for Pin3" << std::endl;
    }
    comp1.reset();
    comp1.addPins(comp1Vector);
    comp1.addPin(ptrPin3);
    comp2.addPin(ptrPin6);
    comp1.setLink(0, comp2, 1);
    comp1.setLink(0, comp2, 2);
    log.output("\nRESETING COMP2\n");
    comp2.reset();
    comp1.dump();
    comp2.dump();
    comp2.addPins(comp2Vector);
    comp2.addPin(ptrPin6);
    comp1.dump();
    comp2.dump();
    comp1.reset();
    comp2.reset();
    comp1.dump();
    comp2.dump();
    comp1.addPins(comp1Vector);
    comp2.addPins(comp2Vector);
    comp1.addPin(ptrPin3);
    comp2.addPin(ptrPin6);
    comp2.addPin(ptrPin7);
    comp2.addPin(ptrPin8);
    comp1.setLink(0, comp2, 1);
    comp1.setLink(0, comp2, 2);
    comp1.setLink(0, comp2, 3);
    comp1.setLink(0, comp2, 4);
    comp1.addPin(ptrPin9);
    try {
        comp1.setLink(1, comp2, 4);
    }
    catch (const ChipsetError &e) {
        log.error(e.what());
    }
    comp1.dump();
    comp2.dump();

}

void testParsing(int argc, char **argv)
{
    log::Logs log(ERROR_FILE);

    if (argc > 1) {
        log.output("\n");
        auto circuit = std::make_unique<nts::Circuit>();
        nts::Parsing parser(argv[1]);

        try {
            parser.readFile(*(circuit.get()));
            circuit->dump();
        }
        catch (const FileError &e) {
            log.output(e.what());
        }
    }
}

void testExecution(int argc, char **argv)
{
    log::Logs log(ERROR_FILE);

    if (argc > 1) {
        auto circuit = std::make_unique<nts::Circuit>();
        nts::Execution execution(circuit);

        try {
            execution.readStartingInput(argc, argv);
            execution.readInput();
        }
        catch (const FileError &e) {
            log.output(e.what());
        }
        catch (const ExecutionError &e) {
            log.output(e.what());
        }
    }
}

int main(int argc, char **argv)
{
    log::Logs log(ERROR_FILE);

    log.cleanFile();
    log.file("------------Build new Error logs------------");
    //testPins();
    //testComponent();
    //testParsing(argc, argv);
    testExecution(argc, argv);
    return 0;
}