#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "command.h"
#include <string>

class CommandParser {
public:
    void addCmd(const Command &cmd);
    bool decodeExecuteLine(const char* line);
private:
    static void toUpper(std::string &str);
    static bool startsWith(const std::string str, const std::string strSearch);
    static void outCmdResponse(const char *cmdLabel, bool cmdSucceeded, const char *resultDetails);

    std::vector<Command> m_commands;
};

#endif // COMMANDPARSER_H
