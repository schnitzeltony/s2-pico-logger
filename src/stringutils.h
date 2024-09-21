#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>
#include <vector>

class StringUtils {
public:
    static std::string toUpper(const std::string &str);
    static std::string toLower(const std::string &str);
    static bool startsWith(const std::string &str, const std::string &strSearch);
    static std::vector<std::string> split(const std::string &text, char delimiter);
    static std::vector<std::string> removeEmpty(const std::vector<std::string> &stringList);
};

#endif // STRINGUTILS_H
