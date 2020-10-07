/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Parsing
*/

#include <algorithm>
#include <string>
#include "Error.hpp"
#include "Parsing.hpp"

namespace nts
{
    void Parsing::switchMode(const ParsingMode &newMode)
    {
        if (_mode == newMode) {
            throw FileError("Cannot switch parsing mode, already got this mode");
        }
        else {
            _mode = newMode;
        }
    }

    void Parsing::switchToChipsetMode()
    {
        if (_mode != UNDEFINED) {
            file("Cannot have more than one " + _chipsetSectionName + " section");
            throw FileError("");
        }
        try {
            switchMode(CHIPSETS);
        }
        catch (const FileError &e) {
            throw FileError("");
        }
    }

    void Parsing::switchToLinkMode()
    {
        if (_mode == UNDEFINED) {
            file("Parsing: Cannot put " + _linkSectionName + " before " + _chipsetSectionName + " section");
            throw FileError(_linkSectionName + " before " + _chipsetSectionName);
        }
        try {
            switchMode(LINKS);
        }
        catch (const FileError &e) {
            file("Cannot have more than one " + _linkSectionName + " section");
            throw FileError("Got more than one " + _linkSectionName + " section");
        }
    }

    bool Parsing::getMode(const std::string &line)
    {
        if (std::regex_match(line, _chipsetRegex)) {
            try {
                // BETTER switch
                switchToChipsetMode();
            }
            catch (const FileError &e) {
                throw FileError(_chipsetSectionName + " section");
            }
            file(_chipsetSectionName, "\nSection: ");
            return true;
        }
        else if (std::regex_match(line, _linkRegex)) {
            try {
                switchToLinkMode();
            }
            catch (const FileError &e) {
                throw FileError(_linkSectionName + " section");
            }
            file(_linkSectionName, "\nSection: ");
            return true;
        }
        return false;
    }

    void Parsing::isAllSections()
    {
        if (_mode != LINKS) {
            file("Section missing");
            throw FileError("section missing");
        }
    }

    bool Parsing::isCommentary(const std::string &line)
    {
        if (line[0] != '#') {
            throw FileError("syntax: probably forgot a #");
        }
        else {
            file(line, "Parsing a commentary: ");
            return true;
        }
    }

    bool Parsing::isNotCommentary(const std::string &line)
    {
        if (line[0] == '#') {
            throw FileError("syntax: Got a commentary");
        }
        else {
            file(line, "Parsing a content: ");
            return true;
        }
    }
    
    bool Parsing::isACommentary(const std::string &line) noexcept
    {
        if (line[0] != '#') {
            return false;
        }
        else {
            file(line, "Parsing a commentary: ");
            return true;
        }
    }

    bool Parsing::isNotACommentary(const std::string &line) noexcept
    {
        if (line[0] == '#') {
            return false;
        }
        else {
            file(line, "Parsing a content: ");
            return true;
        }
    }
    
    std::string Parsing::getChipsetName(std::string &line, std::smatch &matches)
    {
        try {
            if (std::regex_search(line, matches, reg)) {
                isNotCommentary(matches.str(1));
                file(matches.str(1), "Want to create a chipset named ");
                return matches.str(1);
            }
            else
                throw FileError("Missing name for a chipset");
        }
        catch (const FileError &e) {
            file(e.what());
            throw FileError("Wrong chipset name format");
        }
        catch (const std::exception &e) {
            file(e.what());
            throw std::runtime_error(e.what());
        }
        return "";
    }

    bool Parsing::getChipsetContent(Circuit &c, std::string &line, std::smatch &matches)
    {
        (void)c;
        std::string match;
        std::string name = "";

        for (const auto &type : _chipsetsTypeNames) {
            if (line == type) {
                file(type, "Got a chipset with type: ");
                line = matches.suffix().str();

                name = getChipsetName(line, matches);
                c.createComponent(name, type);
                line = matches.suffix().str();

                if (std::regex_search(line, matches, reg)) {
                    isCommentary(matches.str(1));
                }
                break;
            }
        }
        if (name.empty()) {
            throw FileError("Unknow chipset format");
        }
        return true;
    }

    bool Parsing::getChipset(Circuit &c, std::smatch &matches)
    {
        std::string line = matches.str(1);

        try {
            if (isNotACommentary(line))
                return getChipsetContent(c, line, matches);
        }
        catch (const FileError &e) {
            file(e.what());
            throw FileError("Wrong format for " + _chipsetSectionName + " section");
        }
        catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
        return false;
    }

    int Parsing::getLinkPinNumber(std::string &pinNbStr)
    {
        std::smatch matches;
        std::regex reg("(\\d+)");
        std::regex regCheck("([a-zA-Z:/\\?])");

        if(!std::regex_search(pinNbStr, matches, regCheck)) {
            if (std::regex_search(pinNbStr, matches, reg)) {
                file(matches.str(1), "want to link is pin number ");
                return std::stoi(matches.str(1));
            }
        }
        else {
            throw FileError("Unknow link format: cannot get the pin number");
        }
        return 0;
    }

    std::string Parsing::getCompName(Circuit &c, std::string &aName)
    {
        std::string compName = "";
        auto &map = c.getCircuit();

        for (const auto &elem : map) {
            if (elem.first == aName) {
                file(aName, "want to link a pin of ");
                compName = aName;
            }
        }
        if (compName.empty()) {
            throw FileError("Unknow link format: cannot get an existing name");
        }
        return compName;
    }

    std::pair<std::string, int> Parsing::getALink(Circuit &c, std::string &line, std::smatch &matches, std::regex &reg)
    {
        std::string match;
        std::string nameComp = "";
        int pin = -1;

        if ( std::regex_search(line, matches, reg)) {
            match = matches.str(1);
            nameComp = getCompName(c, match);

            line = matches.suffix().str();
            if (std::regex_search(line, matches, reg)) {
                match = matches.str(1);
                pin = getLinkPinNumber(match);
            }
        }
        return std::pair<std::string, int>(nameComp, pin);
    }

    bool Parsing::getLinkContent(Circuit &c, std::string &line, std::smatch &matches)
    {
        std::regex reg2("([a-zA-Z0-9-_]+)");
        std::smatch matches2;
        std::string match;
        std::pair<std::string, int> linkFirstPin;
        std::pair<std::string, int> linkSecondPin;

        linkFirstPin = getALink(c, line, matches2, reg2);
        line = matches.suffix().str();
        if (std::regex_search(line, matches, reg)) {

            match = matches.str(1);
            linkSecondPin = getALink(c, match, matches2, reg2);
            line = matches.suffix().str();
        }
        c.setLink(linkFirstPin.second, linkSecondPin.second, linkFirstPin.first, linkSecondPin.first);
        if (std::regex_search(line, matches, reg)) {
            isCommentary(matches.str(1));
        }
        return true;
    }

    bool Parsing::getLink(Circuit &c, std::smatch &matches)
    {
        std::string line = matches.str(1);

        try {
            if (isNotACommentary(line))
                return getLinkContent(c, line, matches);
        }
        catch (const FileError &e) {
            file(e.what());
            throw FileError("Wrong format for " + _linkSectionName + " section");
        }
        catch (const ChipsetError &e) {
            throw FileError("Wrong format for " + _linkSectionName + " section");
        }
        catch (const std::runtime_error &e) {
            throw std::runtime_error(e.what());
        }
        return false;
    }

    void Parsing::openFile()
    {
        if (_aReadFile.is_open())
            _aReadFile.close();
        _aReadFile.open(_fileName);
    }

    void Parsing::closeFile()
    {
        if (_aReadFile.is_open())
            _aReadFile.close();
    }

    void Parsing::readFile(Circuit &c)
    {
        std::string line;
        std::smatch matches;

        file("Parsing the File:\n");
        try {
            while (_aReadFile.is_open() && std::getline(_aReadFile, line)) {
                for (int i = 0; std::regex_search(line, matches, reg) && i < 2; i++) {
                    if (getMode(matches.str(1))) {
                        line = matches.suffix().str();
                        if (std::regex_search(line, matches, reg)) {
                            isCommentary(matches.str(1));
                        }
                        break;
                    }
                    if (_mode == CHIPSETS) {
                        file("");
                        getChipset(c, matches);
                        break;
                    }
                    else if (_mode == LINKS) {
                        file("");
                        if (getLink(c, matches) == false)
                            break;
                    }
                    else {
                        isCommentary(matches.str(1));
                        break;
                    }
                    line = matches.suffix().str();
                }
            }
            isAllSections();
        }
        catch (const FileError &e) {
            file(e.what());
            throw FileError("stoping the program");
        }
    }
}
