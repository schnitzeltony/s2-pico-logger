#include "commandparser.h"
#include "stringutils.h"
#include "logger.h"

void CommandParser::addCmd(const Command &cmd)
{
    m_commands.push_back(cmd);
}

bool CommandParser::decodeExecuteLine(const char *line)
{
    std::string strLine(line);
    std::vector<std::string> tokens = StringUtils::split(strLine, ',');
    std::string cmdLabel = StringUtils::toUpper(tokens[0]);
    for(auto &cmd : m_commands) {   
        if(cmdLabel == cmd.m_cmdLabel) {
            int paramCount = tokens.size()-1;
            if(paramCount == cmd.m_paramCount) {
                std::vector<std::string> params = tokens;
                params.erase(params.begin());
                bool cmdSucceeded = cmd.m_callback(cmd.m_callbackParam, params);
                if(cmdSucceeded)
                    finishCmd(cmdLabel.data(), true, "");
                else
                    finishCmd(cmdLabel.data(), false, "Command execution failed");
                return cmdSucceeded;
            }
            else
                finishCmd(cmdLabel.data(), false, "Wrong parameter count");
        }
    }
    return false;
}

void CommandParser::finishCmd(const char* cmdLabel, bool cmdSucceeded, const char *errorDetails)
{
    if(cmdSucceeded)
        printf("%s,OK\r\n", cmdLabel);
    else
        printf("%s,ERROR: %s\r\n", cmdLabel, errorDetails);
}
