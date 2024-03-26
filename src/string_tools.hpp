#ifndef __STRING_TOOLS_HPP__
#define __STRING_TOOLS_HPP__

#include <string>
#include <vector>

namespace prim
{
    inline std::vector<std::string> splitString(std::string str, std::string delimiter)
    {
        std::vector<std::string> strings;
        size_t pos = 0, prevPos = 0;
        while ((pos = str.find(delimiter, pos + 1)) != std::string::npos)
        {
            strings.emplace_back(std::move(str.substr(prevPos, pos)));
            prevPos = pos;
        }
        strings.push_back(std::move(str.substr(prevPos + delimiter.length())));

        return strings;
    }

    inline std::vector<std::string> splitString(const std::string& str, const char delimiter)
    {
        std::vector<std::string> strings;
        int pos = -1, prevPos = -1;
        while ((pos = str.find(delimiter, pos + 1)) != std::string::npos)
        {
            ++prevPos;
            std::string substr = str.substr(prevPos, pos - prevPos);
            if (!substr.empty()) strings.emplace_back(std::move(substr));
            prevPos = pos;
        }
        strings.push_back(std::move(str.substr(++prevPos)));

        return strings;
    }

    inline bool startsWith(const std::string& source, const std::string& str)
    {
        if(source.length() < str.length()) return false;

        for(int i = 0; i < str.length(); ++i)
        {
            if(source[i] != str[i]) return false;
        }
        return true;
    }

    inline std::string toLower(const std::string& str)
    {
        std::string lowerStr;
        lowerStr.reserve(str.size());
        for (const char& c : str) lowerStr.push_back(std::tolower(c));
        return lowerStr;
    }
    
    inline bool contains(const std::string& str, const std::string& substr) 
    {
        size_t substrLength = substr.length();
        if(str.length() < substr.length()) return false;

        size_t searchIdx = 0;
        for(size_t i = 0; i < str.length(); ++i)
        {
            if(str[i] == substr[searchIdx]) ++searchIdx;
            if(searchIdx == substrLength) return true;
        }
        return false;
    }
}

#endif // __STRING_TOOLS_HPP__