#include "class_info.h"
#include <iostream>

void ClassInfo::SetName(const string& name)
{
    m_name = name;
}

void ClassInfo::AddInheritance(const string& name)
{
    m_inheritances.push_back(name);
}

void ClassInfo::Output() const
{
    cout << "Class name : " << m_name << endl;
}