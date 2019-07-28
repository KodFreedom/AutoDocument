#include "auto_document.h"
using namespace KodFreedom;

int main()
{
    AutoDocument auto_document;
    auto_document.Analyze("./SourceCode/test.h");
    getchar();
    return 0;
}