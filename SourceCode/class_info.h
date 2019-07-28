#pragma once
#include <string>
#include <list>
using namespace std;

class ClassInfo
{
public:
    ClassInfo() {}
    ~ClassInfo() {}

    void SetName(const string& name);
    void AddInheritance(const string& name);
    void Output() const;

    const string& Name() const { return m_name; }

private:
    string m_name = {}; // クラス名
    list<string> m_inheritances = {}; // 継承クラス
};