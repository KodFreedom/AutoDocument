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

        // クラス名前と継承を解析
        void AnalyzeClassNameAndInherits(string& buffer);

        // 継承を解析
        void AnalyzeInheritances(string& buffer);

        // .hからクラス解析
        void AnalyzeClass(ifstream& file);

        size_t           m_curly_bracket_counter = 0; // `{`の階層カウンター
        list<ClassInfo*> m_classes = {}; // headファイルに宣言されたクラス
    };
}