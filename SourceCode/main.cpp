#include <string>
using namespace std;
#include "auto_document.h"

int main()
{
    AutoDocument auto_document;
    auto_document.Analyze("test.h");
    getchar();
    return 0;
}