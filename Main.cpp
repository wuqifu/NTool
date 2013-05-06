/*
 *  $Id: Main.cpp 344 2010-06-07 02:57:18Z qfwu $
 *  $Rev$
 *
 */

#include "NStringTool.h"
#include "NFileTool.h"

int main()
{
    using namespace NStringTool;
    using namespace NFileTool;

    //TestStringToken();
    //TestStringTrim();
    //TestStringTrimLeft();
    //TestStringTrimRight();
//     TestStringUpper();
//     TestStringLower();
    //TestStartWith();
    //TestEndWith();
    TestReadFile();
    //TestParseKeyValue();
    //TestParseProperty();
    //TestReadFile2();
    TestReadFile_Line();



    std::cout << "Pass testing..." << std::endl;
}