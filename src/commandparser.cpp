#include "commandparser.h"
#include "stringutils.h"

CommandParser::CommandParser(std::function<void(const std::string &cmdResponse)> callbackCmdResponse) :
    m_callbackCmdResponse(callbackCmdResponse)
{
}

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
                    outCmdResponse(cmdLabel.data(), true, "");
                else
                    outCmdResponse(cmdLabel.data(), false, "Command execution failed");
                return cmdSucceeded;
            }
            else
                outCmdResponse(cmdLabel.data(), false, "Wrong parameter count");
        }
    }
    return false;
}

void CommandParser::outCmdResponse(const char *cmdLabel, bool cmdSucceeded, const char *resultDetails)
{
    std::string result;
    bool hasDetails = resultDetails && *resultDetails;
    // see https://github.com/ZeraGmbH/simple-parser
    if(cmdSucceeded) {
        result = std::string("OK");
        if(hasDetails)
            result += std::string(",") + resultDetails;
    }
    else {
        result = std::string("ERROR");
        if(hasDetails)
            result += std::string(": ") + resultDetails;
    }
    const std::string cmdResponse = std::string(cmdLabel) + "," + result;
    puts(cmdResponse.data());
}
