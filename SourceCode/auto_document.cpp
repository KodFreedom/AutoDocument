#include <iostream>
#include <assert.h>
#include "auto_document.h"
#include "class_info.h"
#include "utility.h"
using namespace KodFreedom;

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
    cout << "////////// " + file_path + "解析中 //////////" << endl;
    ifstream file(file_path);
    if (!file.is_open())
    {
        cout << ">> " + file_path + "開けません！！" << endl;
    }
    else
    {
        Analyze(file);
        file.close();
    }
    cout << "////////// " + file_path + "解析終了 //////////" << endl;
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
    while (GetLineUntil(file, { "class" }, line_info))
    {
        if (!IsClass(file, line_info)) continue;

        auto& current_line = line_info.log.back();
        if (current_line.find('{') == string::npos)
        {// 改行した、「{」までチェックする
            LineInfo line_info2;
            if (GetLineUntil(file, { "{" }, line_info2))
            {
                assert(line_info2.comment.size() == 0);
                for (auto& line : line_info2.log)
                {
                    current_line += line;
                }
            }
        }

        // 階層カウントする
        ++m_curly_bracket_counter;

        // クラス情報を作成
        ClassInfo* class_info = new ClassInfo();
        m_classes.push_back(class_info);
        class_info->SetClassComment(line_info.comment);

        // クラス名と継承を解析する
        AnalyzeClassNameAndInherits(current_line);
        return true;
    }
    return false;
}

bool AutoDocument::GetLineUntil(ifstream& file, const list<string>& keywords, LineInfo& out_line_info)
{
    out_line_info.log.clear();
    out_line_info.comment.clear();
    int comment_step = 0; // /*式コメントを検出するため
    size_t comment_stop_counter = 0; // 連続コメント検出

    while (!file.eof())
    {
        // Line取得
        string buffer = Utility::GetLine(file);

        // ログに保存
        out_line_info.log.push_back(buffer); 

        // comment check
        int result = Utility::IsComment(buffer);
        if (result < INT_MAX)
        {
            if (comment_stop_counter > 1)
            {// コメント中断したので、前のやつを捨てる
                comment_stop_counter = 0;
                out_line_info.comment.clear();
            }

            comment_step += result;
            assert(comment_step >= 0);
            out_line_info.comment.push_back(buffer);
            continue; // コメント中
        }
        else if (comment_step > 0)
        {// /*中
            continue;
        }
        else
        {
            ++comment_stop_counter;
        }

        // keyword check
        for (auto& keyword : keywords)
        {
            if (buffer.find(keyword) != string::npos)
            {
                return true;
            }
        }
    }
    return false;
}

bool AutoDocument::IsClass(ifstream& file, LineInfo& line_info)
{
    auto& current_line = line_info.log.back();
    if (current_line.find("template") != string::npos)
    {// template classかも、次の行を検出してみる
        string buffer = Utility::GetLine(file);
        if (Utility::IsClass(buffer))
        {
            line_info.log.push_back(buffer);
            return true;
        }
        return false;
    }
    return Utility::IsClass(current_line);
}

void AutoDocument::AnalyzeClassNameAndInherits(string& buffer)
{
    ClassInfo* class_info = m_classes.back();

    // いらない符号を消す
    Utility::DeleteKeywordsFromString({ " ", "{","class" }, buffer);
    
    size_t pos = buffer.find(':');
    if (pos != string::npos)
    {// 継承がある、解析する
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