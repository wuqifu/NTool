#ifndef NCHARTOOL_H
#define NCHARTOOL_H

#include <Windows.h>
#include <string>

namespace NCharTool
{
    // Converting a WChar string to a ANSI string
    std::string WChar2Ansi(const std::wstring& wstrSrc, unsigned int nCodePage = CP_UTF8)
    {
        LPCWSTR pwszSrc = wstrSrc.c_str();
        int nLen = WideCharToMultiByte(nCodePage, 0, pwszSrc, -1, NULL, 0, NULL, NULL);
        if (nLen <= 0) return std::string("");
        char* pszDst = new char[nLen];      // new内存不足时默认throw bad_alloc
        WideCharToMultiByte(nCodePage, 0, pwszSrc, -1, pszDst, nLen, NULL, NULL);
        pszDst[nLen -1] = 0;
        std::string strDest(pszDst);
        delete[] pszDst;
        return strDest;
    }

    // Converting ANSI string to WCHAR string
    std::wstring Ansi2WChar(const std::string& strStr, unsigned int nCodePage = CP_UTF8)
    {
        LPCSTR pszSrc = strStr.c_str();
        //获取缓冲区的大小，并申请空间，缓冲区大小是按字符计算的
        int nSize = MultiByteToWideChar(nCodePage, 0, (LPCSTR)pszSrc, -1, NULL, 0);
        if(nSize <= 0) return std::wstring(L"");
        WCHAR *pwszDst = new WCHAR[nSize+1];     // new内存不足时默认throw bad_alloc
        MultiByteToWideChar(nCodePage, 0,(LPCSTR)pszSrc, -1, pwszDst, nSize);
        pwszDst[nSize] = 0;
        if( pwszDst[0] == 0xFEFF)   // skip Oxfeff
        {
            for(int i = 0; i < nSize; i ++)
            {
                pwszDst[i] = pwszDst[i+1];
            }
        }
        std::wstring wstrDest(pwszDst);
        delete[] pwszDst;
        return wstrDest;
    }
}
#endif
