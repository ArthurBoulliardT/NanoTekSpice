/*
** EPITECH PROJECT, 2020
** OOP_nanotekspice_2019
** File description:
** Parsing
*/

#pragma once

#include <string>
#include <fstream>
#include <regex>
#include "Circuit.hpp"

namespace nts {
    class Parsing : public log::Logs
    {
        public:
            enum ParsingMode {
                CHIPSETS,
                LINKS,
                UNDEFINED
            };
    
            //Ctors
            Parsing(const std::string &fileName = "",
                    const std::string &chipsetSectionName = ".chipsets",
                    const std::string &linkSectionName = ".links"): 
                        Logs(ERROR_FILE),
                        _fileName(fileName),
                        _aReadFile(),
                        _aWriteFile(),
                        _chipsetSectionName(chipsetSectionName),
                        _linkSectionName(linkSectionName),
                        _chipsetRegex(chipsetSectionName + ":"),
                        
                        _linkRegex(linkSectionName + ":")
                    { 
                        _aReadFile.open(fileName);
                    };

            //Dtors
            ~Parsing() {};

            //Actions
            void readFile(Circuit &c);
            void openFile();
            void closeFile();

            //Booleans
            bool isCommentary(const std::string &line);
            bool isNotCommentary(const std::string &line);
            bool isACommentary(const std::string &line) noexcept;
            bool isNotACommentary(const std::string &line) noexcept;
            void isNewName(const std::string &line);

            //Setters
            void setFileName(const std::string &fileName) noexcept {  _fileName = fileName; };
            void setChipsetSectionName(const std::string &chipsetSectionName) noexcept { _chipsetSectionName = chipsetSectionName; };
            void setLinkSectionName(const std::string &linkSectionName) noexcept { _linkSectionName = linkSectionName; };

            //Getters
            const std::string &getFileName() const noexcept { return _fileName; };
            const std::string &getChipsetSectionName() const noexcept { return _chipsetSectionName; };
            const std::string &getLinkSectionName() const noexcept { return _linkSectionName; };
            ParsingMode getModeState() const noexcept { return _mode; };

        protected:
        private:
            inline static const std::vector<std::string> _chipsetsTypeNames 
                = {
                    "input",    "output",
                    "true",    "false",
                    "clock",    "4081",
                    "4071",     "4069",
                    "4040",
                    "4030",     "4011",
                    "4001"
                    };
            inline static const std::regex reg = std::regex("([#\\.]?[a-zA-Z0-9#:+-_]+)");
            std::string _fileName;
            std::ifstream _aReadFile;
            std::ofstream _aWriteFile;
            std::string _chipsetSectionName;
            std::string _linkSectionName;
            std::regex _chipsetRegex;
            std::regex _linkRegex;
            ParsingMode _mode = UNDEFINED;


            //private methods
            bool getMode(const std::string &line);
            void switchMode(const ParsingMode &newMode);
            void switchToChipsetMode();
            void switchToLinkMode();

            bool getChipset(Circuit &c, std::smatch &matches);
            bool getChipsetContent(Circuit &c, std::string &line, std::smatch &matches);
            std::string getChipsetName(std::string &, std::smatch &matches);

            bool getLink(Circuit &c, std::smatch &matches);
            bool getLinkContent(Circuit &c, std::string &line, std::smatch &matches);

            std::pair<std::string, int> getALink(Circuit &c, std::string &line, std::smatch &matches, std::regex &reg);
            int getLinkPinNumber(std::string &pinNbStr);
            std::string getCompName(Circuit &c, std::string &aName);

            void isAllSections();

    };
}