#include "stringutils.h"

std::string StringUtils::toUpper(const std::string &str)
{
    std::string ret;
    const int size = str.size();
    ret.resize(size);
    for(int i=0; i<size; ++i)
        ret[i] = toupper(str[i]);
    return ret;
}

std::string StringUtils::toLower(const std::string &str)
{
    std::string ret;
    const int size = str.size();
    ret.resize(size);
    for(int i=0; i<size; ++i)
        ret[i] = tolower(str[i]);
    return ret;
}

bool StringUtils::startsWith(const std::string &str, const std::string &strSearch)
{
    return str.rfind(strSearch, 0) == 0;
}

std::vector<std::string> StringUtils::split(const std::string &text, char delimiter)
{
    std::vector<std::string> tokens;
    std::size_t start = 0, end = 0;
    while ((end = text.find(delimiter, start)) != std::string::npos) {
        tokens.push_back(text.substr(start, end - start));
        start = end + 1;
    }
    tokens.push_back(text.substr(start));
    return tokens;
}

std::vector<std::string> StringUtils::removeEmpty(const std::vector<std::string> &stringList)
{
    std::vector<std::string> ret;
    for(const auto &entry : stringList)
        if(!entry.empty())
            ret.push_back(entry);
    return ret;
}
