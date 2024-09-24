#ifndef COMMANDPARSER_H
#define COMMANDPARSER_H

#include "command.h"
#include <string>
#include <functional>

class CommandParser {
public:
    CommandParser(std::function<void(const std::string &cmdResponse)> callbackCmdResponse);
    void addCmd(const Command &cmd);
    bool decodeExecuteLine(const char* line);
private:
    static void toUpper(std::string &str);
    static bool startsWith(const std::string str, const std::string strSearch);
    static void outCmdResponse(const char *cmdLabel, bool cmdSucceeded, const char *resultDetails);

    std::function<void(const std::string &cmdResponse)> m_callbackCmdResponse;
    std::vector<Command> m_commands;
};

#endif // COMMANDPARSER_H
