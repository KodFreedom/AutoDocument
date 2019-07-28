#include <algorithm>
#include "utility.h"
using namespace KodFreedom;

string Utility::GetLine(ifstream& file)
{
    string buffer;
    buffer.resize(sc_line_max);
    file.getline(&buffer[0], sc_line_max);
    DeleteKeywordFromString('\0', buffer);
    return buffer;
}

void Utility::DeleteKeywordFromString(const char keyword, string& buffer)
{
    auto begin = std::remove(buffer.begin(), buffer.end(), keyword);
    if (begin != buffer.end())
    {
        buffer.erase(begin, buffer.end());
    }
}

void Utility::DeleteKeywordsFromString(const list<string>& keywords, string& buffer)
{
    for (auto& keyword : keywords)
    {
        while (1)
        {
            size_t pos = buffer.find(keyword);
            if (pos == string::npos) break;
            buffer.erase(pos, keyword.size());
        }
    }
}

int Utility::IsComment(const string& buffer)
{
    size_t pos = buffer.find("//");
    size_t pos_1 = buffer.find("/*");
    size_t pos_2 = buffer.find("*/");
    if (pos != string::npos)
    {// //
        string check(buffer.begin(), buffer.begin() + pos);
        if (check.find_first_not_of(' ') == string::npos)
        {
            return 0;
        }
    }
    else if (pos_1 != string::npos && pos_2 != string::npos)
    {// /**/
        string check(buffer.begin(), buffer.begin() + pos_1);
        if (check.find_first_not_of(' ') == string::npos)
        {
            return 0;
        }
    }
    else if (pos_1 != string::npos)
    {// /*
        string check(buffer.begin(), buffer.begin() + pos_1);
        if (check.find_first_not_of(' ') == string::npos)
        {
            return 1;
        }
    }
    else if (pos_2 != string::npos)
    {// */
        return -1;
    }

    return INT_MAX;
}

bool Utility::IsClass(const string& buffer)
{
    auto pos = buffer.find("class");
    if (pos == string::npos) return false;
    if (buffer.find(';') != string::npos) return false; // 前方宣言

    string check(buffer.begin(), buffer.begin() + pos);
    if (check.find_first_not_of(' ') != string::npos) return false; // classの前にスペース以外のものがある
    return true;
}