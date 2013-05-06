#ifndef NFILETOOL_H
#define NFILETOOL_H

#include <fstream>
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <exception>
#include <Windows.h>

namespace NFileTool
{    
    using namespace std;

    //istreambuf_iterator?
    std::string ReadFileContent( const char *szFileName )
    {
        FILE *ifReadFile = NULL;
        if (fopen_s(&ifReadFile, szFileName, "r") != 0)
        {
            fprintf(stderr, "File not found: %s\n", szFileName);
            throw;
        }

        // read file content
        std::string strFileContent;
        const unsigned int BUFF_SIZE = 4000;
        char buff[BUFF_SIZE + 1] = {0};
        while (fread(buff, sizeof(char), BUFF_SIZE, ifReadFile) != 0 )
        {
            strFileContent += buff;
            memset(buff, 0, BUFF_SIZE + 1);
        }    
        fclose(ifReadFile);

        return strFileContent;
    }

    std::string ReadFileContent(const string& strFileName)
    {
        ifstream ifInput(strFileName.c_str());
        if (!ifInput)
            throw exception("File not found");
        std::string strFileContent;
        std::copy(istreambuf_iterator<char>(ifInput), istreambuf_iterator<char>(), back_inserter(strFileContent));
        return strFileContent;
    }

    std::string ReadFile(const std::string& strFileName)
    {  
        std::ifstream ifFile(strFileName.c_str());
        if (!ifFile)
        {
            std::fprintf(stderr, "Open %s failed.\n", strFileName.c_str());
            throw std::exception();
        }
        std::string strFileContent;
        strFileContent.assign((istreambuf_iterator<char>(ifFile)), istreambuf_iterator<char>());
        return strFileContent;
    }

    void TestReadFile()
    {
        std::string strFileContent;
        strFileContent = ReadFile("C:\\Users\\Colin\\Project\\NTool\\NTool\\NFileTool.h");
        std::cout << strFileContent << std::endl;
    }

    // 读取整个文件内容到vector, 以行分割
    std::vector<std::string> ReadFile2(const std::string& strFileName)
    {
        std::ifstream ifFile(strFileName.c_str());
        if (!ifFile)
        {
            std::fprintf(stderr, "Open %s failed.\n", strFileName.c_str());
            throw;
        }


//         const std::size_t LINE_BUFFER_SIZE = 1024 * 5;      // 有次buff size设小了
//         while (ifFile.peek() != EOF)        // 不可以用!ifFile.eof()
//         {
//             char cBuff[LINE_BUFFER_SIZE] = {0};
// 
//             ifFile.getline(cBuff, LINE_BUFFER_SIZE, '\n');
//             vecLine.push_back(std::string(cBuff));
//         }

        std::vector<std::string> vecLine;
        std::string strLine;
        while (std::getline(ifFile, strLine, '\n'))
        {
            vecLine.push_back(strLine);
        }

        return vecLine;
    }

    void TestReadFile_Line()
    {
        vector<string> vecLine = ReadFile2("C:\\Users\\Colin\\Project\\NTool\\NTool\\NFileTool.h");
        std::copy(vecLine.begin(), vecLine.end(), ostream_iterator<string>(cout, "\n"));
    }

    int GetAllFiles(const std::wstring& strDir, const std::wstring& wstrExt, std::vector<std::wstring>& vAllFiles)
    {
        WIN32_FIND_DATA fd;

        HANDLE hFind = FindFirstFile((strDir+wstrExt).c_str(), &fd);

        if (hFind != INVALID_HANDLE_VALUE)
        {
            do 
            {
                vAllFiles.push_back(strDir + fd.cFileName);

            } while (FindNextFile(hFind, &fd));
        }
        else
        {
            printf ("Invalid file handle. Error is %u\n", GetLastError());
            return (-1);
        }

        FindClose(hFind);
        return 0;
    }
}

#endif