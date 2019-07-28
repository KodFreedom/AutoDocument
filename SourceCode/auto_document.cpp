#include <fstream>
#include <iostream>
#include <assert.h>
#include <algorithm>
#include "auto_document.h"
#include "class_info.h"

//----------------------------------------------------------------------
// Public
AutoDocument::~AutoDocument()
{
    for (auto class_info : m_classes)
    {
        delete class_info;
    }
    m_classes.clear();
}

void AutoDocument::Analyze(const string& file_path)
{
    // Todo : check if it's .h file
    cout << "////////// " + file_path + "��͒� //////////" << endl;
    ifstream file(file_path);
    if (!file.is_open())
    {
        cout << ">> " + file_path + "�J���܂���I�I" << endl;
    }
    else
    {
        Analyze(file);
        file.close();
    }
    cout << "////////// " + file_path + "��͏I�� //////////" << endl;
}

//----------------------------------------------------------------------
// Private
void AutoDocument::Analyze(ifstream& file)
{
    while (FindClass(file))
    {
        AnalyzeClass(file);
        m_classes.back()->Output();
    }
}

bool AutoDocument::FindClass(ifstream& file)
{
    LineInfo line_info;
    while (GetLineUntil(file, "class", line_info))
    {
        if (line_info.buffer.find(';') != string::npos)
        {// �O���錾
            continue;
        }

        string check(line_info.buffer.begin(), line_info.buffer.begin() + line_info.pos);
        if (check.find_first_not_of(' ') != string::npos)
        {// class�̑O�ɃX�y�[�X�ȊO�̂��̂�����
            continue;
        }

        // �N���X�����쐬
        ClassInfo* class_info = new ClassInfo();
        m_classes.push_back(class_info);

        if (line_info.buffer.find('{') == string::npos)
        {// ���s�����A�u{�v�܂Ń`�F�b�N����
            string buffer2;
            buffer2.resize(sc_line_max);
            file.getline(&buffer2[0], sc_line_max);
            assert(buffer2.find('{') != string::npos);
        }

        // �K�w�J�E���g����
        ++m_curly_bracket_counter;

        // �N���X���ƌp������͂���
        AnalyzeClassNameAndInherits(line_info.buffer);

        return true;
    }
    return false;
}

bool AutoDocument::GetLineUntil(ifstream& file, const string& keyword, LineInfo& out_line_info)
{
    out_line_info.pos = string::npos;
    out_line_info.buffer.clear();
    out_line_info.log.clear();
    out_line_info.comment.clear();
    int comment_step = 0; // /*���R�����g�����o���邽��
    size_t comment_stop_counter = 0; // �A���R�����g���o
    size_t comment_continue_counter = 0; // �A���R�����g���o

    while (!file.eof())
    {
        // Line�擾
        string buffer;
        buffer.resize(sc_line_max);
        file.getline(&buffer[0], sc_line_max);

        // \0����
        auto begin = std::remove(buffer.begin(), buffer.end(), '\0');
        if (begin != buffer.end())
        {
            buffer.erase(begin, buffer.end());
        }

        // ���O�ɕۑ�
        out_line_info.log.push_back(buffer); 

        // comment check
        int result = AnalyzeComment(buffer);
        if (result < INT_MAX)
        {
            if (comment_stop_counter > 1)
            {// �R�����g���f�����̂ŁA�O�̂���̂Ă�
                comment_stop_counter = 0;
                comment_continue_counter = 0;
                out_line_info.comment.clear();
            }

            comment_step += result;
            assert(comment_step >= 0);
            out_line_info.comment.push_back(buffer);
            ++comment_continue_counter;
            if (comment_step > 0) continue; // �R�����g��
        }
        else
        {
            ++comment_stop_counter;
        }

        // keyword check
        out_line_info.pos = buffer.find(keyword);
        if (out_line_info.pos != string::npos)
        {
            out_line_info.buffer = buffer;
            return true;
        }
    }
    return false;
}

int AutoDocument::AnalyzeComment(string& buffer)
{
    size_t pos_1 = buffer.find("//");
    // TODO : /**/�̑Ή�
    //size_t pos_2 = buffer.find("/*");
    //size_t pos_3 = buffer.find("*/");

    if (pos_1 != string::npos)
    {
        return 0;
    }

    //if (pos_3 != string::npos && pos_2 != string::npos)
    //{
    //    return 0;
    //}

    return INT_MAX;
}

void AutoDocument::DeleteKeywordsFromString(const list<string>& keywords, string& buffer)
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

void AutoDocument::AnalyzeClassNameAndInherits(string& buffer)
{
    ClassInfo* class_info = m_classes.back();

    // ����Ȃ�����������
    DeleteKeywordsFromString({ " ", "{","class" }, buffer);
    
    size_t pos = buffer.find(':');
    if (pos != string::npos)
    {// �p��������A��͂���
        string inherrit_info = string(buffer.begin() + pos, buffer.end());
        buffer.erase(pos, buffer.size() - pos);
        AnalyzeInheritances(inherrit_info);
    }

    class_info->SetName(buffer);
}

void AutoDocument::AnalyzeInheritances(string& buffer)
{
    ClassInfo* class_info = m_classes.back();
}

void AutoDocument::AnalyzeClass(ifstream& file)
{

}