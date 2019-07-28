#pragma once
#include <string>
#include <list>
#include <fstream>
using namespace std;

namespace KodFreedom
{
    class Utility
    {
    public:
        static const size_t sc_line_max = 256;

        static string GetLine(ifstream& file);
        static void   DeleteKeywordFromString(const char keyword, string& buffer);
        static void   DeleteKeywordsFromString(const list<string>& keywords, string& buffer);

        // �R�����g���ǂ����̉��
        // //�̏ꍇ��0
        // /*�̏ꍇ��1
        // */�̏ꍇ��-1
        // ����max��Ԃ�
        static int IsComment(const string& buffer);

        static bool IsClass(const string& buffer);
    };                
}