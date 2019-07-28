#include "class_info.h"
#include <iostream>
using namespace KodFreedom;

void ClassInfo::SetName(const string& name)
{
    m_name = name;
}

void ClassInfo::SetClassComment(const list<string>& comment)
{
    m_class_comment = comment;
}

void ClassInfo::AddInheritance(const string& name)
{
    m_inheritances.push_back(name);
}

void ClassInfo::Output() const
{
    cout << "Class name : " << m_name << endl;
    cout << "Comment : " << endl;
    for (auto& line : m_class_comment)
    {
        cout << line << endl;
    }
    cout << "Class over" << endl << endl;
}