#include "stringutils.h"
#include <algorithm>

void StringUtils::toUpper(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void StringUtils::toLower(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

bool StringUtils::startsWith(const std::string &str, const std::string &strSearch)
{
    return str.rfind(strSearch, 0) == 0;
}
