#pragma once
#include <string>
#include <list>
using namespace std;

namespace KodFreedom
{
    class ClassInfo
    {
    public:
        ClassInfo() {}
        ~ClassInfo() {}

        void SetName(const string& name);
        void SetClassComment(const list<string>& comment);
        void AddInheritance(const string& name);
        void Output() const;

        const string& Name() const { return m_name; }

    private:
        list<string> m_class_comment = {}; // クラスのコメント
        string       m_name = {}; // クラス名
        list<string> m_inheritances = {}; // 継承クラス
    };
}