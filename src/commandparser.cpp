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
                Logger::logOutput(cmdLabel.data(), "Supi Dupi");
            }
            else
                Logger::logOutput(cmdLabel.data(), "Parameter count wrong");
        }
    }
    return false;
}

