#include "command.h"
#include "stringutils.h"

Command::Command(std::string cmdLabel, 
                 int paramCount, 
                 std::function<bool(void *, std::vector<std::string> cmdParams)> callback, 
                 void *callbackParam) :
    m_cmdLabel(StringUtils::toUpper(cmdLabel)),
    m_paramCount(paramCount),
    m_callback(callback),
    m_callbackParam(callbackParam)
{
}
