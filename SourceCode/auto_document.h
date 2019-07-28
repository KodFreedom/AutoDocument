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

    // �R�����g���ǂ����̉��
    // //�̏ꍇ��0
    // /*�̏ꍇ��1
    // */�̏ꍇ��-1
    // ����max��Ԃ�
    int AnalyzeComment(string& buffer);

    void DeleteKeywordsFromString(const list<string>& keywords, string& buffer);

    // �N���X���O�ƌp�������
    void AnalyzeClassNameAndInherits(string& buffer);

    // �p�������
    void AnalyzeInheritances(string& buffer);

    // .h����N���X���
    void AnalyzeClass(ifstream& file);

    size_t           m_curly_bracket_counter = 0; // `{`�̊K�w�J�E���^�[
    list<ClassInfo*> m_classes = {}; // head�t�@�C���ɐ錾���ꂽ�N���X
};