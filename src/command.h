#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <functional>
#include <vector>

class Command {
public:
    Command(std::string cmdLabel,
            int paramCount,
            std::function<bool(void* param, std::vector<std::string> cmdParams)> callback,
            void* callbackParam);
    friend class CommandParser;
private:
    std::string m_cmdLabel;
    int m_paramCount;
    std::function<bool(void*, std::vector<std::string> cmdParams)> m_callback;
    void* m_callbackParam;
};

#endif // COMMAND_H
