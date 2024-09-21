#ifndef STRINGUTILS_H
#define STRINGUTILS_H

#include <string>

class StringUtils {
public:
    static void toUpper(std::string &str);
    static void toLower(std::string &str);
    static bool startsWith(const std::string &str, const std::string &strSearch);
};

#endif // STRINGUTILS_H
