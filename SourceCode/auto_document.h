#pragma once
#include <list>
#include <string>
using namespace std;

class ClassInfo;

class AutoDocument
{
public:
    AutoDocument() {}
    ~AutoDocument();

    void Analyze(const string& file_path);

private:
    static const size_t sc_line_max = 256;

    struct LineInfo
    {
        size_t       pos;
        string       buffer;
        list<string> log;
        list<string> comment;
    };

    void Analyze(ifstream& file);
    bool FindClass(ifstream& file);
    bool GetLineUntil(ifstream& file, const string& keyword, LineInfo& out_line_info);

    // コメントかどうかの解析
    // //の場合は0
    // /*の場合は1
    // */の場合は-1
    // 他はmaxを返す
    int AnalyzeComment(string& buffer);

    void DeleteKeywordsFromString(const list<string>& keywords, string& buffer);

    // クラス名前と継承を解析
    void AnalyzeClassNameAndInherits(string& buffer);

    // 継承を解析
    void AnalyzeInheritances(string& buffer);

    // .hからクラス解析
    void AnalyzeClass(ifstream& file);

    size_t           m_curly_bracket_counter = 0; // `{`の階層カウンター
    list<ClassInfo*> m_classes = {}; // headファイルに宣言されたクラス
};