#pragma once
#include <list>
#include <string>
using namespace std;

namespace KodFreedom
{
    class ClassInfo;

    class AutoDocument
    {
    public:
        AutoDocument() {}
        ~AutoDocument();

        void Analyze(const string& file_path);

    private:
        struct LineInfo
        {
            list<string> log;
            list<string> comment;
        };

        void Analyze(ifstream& file);
        bool FindClass(ifstream& file);
        bool GetLineUntil(ifstream& file, const list<string>& keywords, LineInfo& out_line_info);
        bool IsClass(ifstream& file, LineInfo& line_info);

        // �N���X���O�ƌp�������
        void AnalyzeClassNameAndInherits(string& buffer);

        // �p�������
        void AnalyzeInheritances(string& buffer);

        // .h����N���X���
        void AnalyzeClass(ifstream& file);

        size_t           m_curly_bracket_counter = 0; // `{`�̊K�w�J�E���^�[
        list<ClassInfo*> m_classes = {}; // head�t�@�C���ɐ錾���ꂽ�N���X
    };
}