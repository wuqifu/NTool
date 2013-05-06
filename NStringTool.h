/*
* $Id: NStringTool.h 254 2010-05-21 04:16:29Z qfwu $
* $Rev: 254 $
* $Author: qfwu $
*
*/

#include <vector>
#include <string>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <map>
#include <iterator>

namespace NStringTool
{
    using std::not1;
    using std::ptr_fun;
    using std::isspace;

    // vecSub��Ϊ��������ֵ��������޸ĵ����ò������ĸ������أ�
    void StringTokenize(const std::string& strSrc, const std::string& strDelimit, std::vector<std::string>& vecSub)
    {
        if (strSrc.empty() || strDelimit.empty())
        {
            throw "tokenize: empty string\n";
        }
        vecSub.clear();

        std::size_t nCurPos = 0;
        std::size_t nNextPos = 0;
        while ((nCurPos = strSrc.find_first_not_of(strDelimit, nNextPos)) != std::string::npos)
        {
            nNextPos = strSrc.find_first_of(strDelimit, nCurPos + 1);
            vecSub.push_back(strSrc.substr(nCurPos, nNextPos - nCurPos));   
        }
    }

    void StringTokenize_Word(const std::string& strSrc, const std::string& strDelimit, std::vector<std::string>& vecSub)
    {
        if (strSrc.empty() || strDelimit.empty())
        {
            throw "tokenize: empty string\n";
        }
        vecSub.clear();

        std::size_t nCurPos = 0;
        std::size_t nNextPos = 0;
        if (strSrc.find(strDelimit) != std::string::npos)
        {
            vecSub.push_back(strSrc.substr(0, strSrc.find(strDelimit)));
            while((nCurPos = strSrc.find(strDelimit, nNextPos)) != std::string::npos)
            {
                nNextPos = strSrc.find(strDelimit, nCurPos + 1);
                vecSub.push_back(strSrc.substr(nCurPos + strDelimit.length(), nNextPos - nCurPos - strDelimit.length()));  
            }
        }
        else
        {
            vecSub.push_back(strSrc);
        }
    }

    void TestStringToken()
    {
        std::string strToken(" C \t C++ | Python; C#...CPP");
        std::string strDelimit(" \t|;.");
        std::vector<std::string> vecSub;
        StringTokenize(strToken, strDelimit, vecSub);
        std::copy(vecSub.begin(), vecSub.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

        StringTokenize("abc", strDelimit, vecSub);
        assert(vecSub[0] == "abc");
        StringTokenize("..\t | ; . |", strDelimit, vecSub);
        assert(vecSub.empty());
    }


    // ����std::string& ���� void �ĸ���������? ��ʽ���ʽ�ô��뿴ȥ����Ȼ��
    std::string& StringTrim(std::string& strSrc, const std::string& strTarget = " \t\n")
    {
        // "  hello, world ", "Hello", "        "
        std::size_t nStart  = strSrc.find_first_not_of(strTarget);
        if (nStart != std::string::npos)
        {
            std::size_t nEnd    = strSrc.find_last_not_of(strTarget);
            strSrc.swap(strSrc.substr(nStart, nEnd - nStart + 1));      // swapС����
        }
        else                                // �տ�ʼû�п��ǵ�else��������ǲ��ܰ�
        {
            std::string().swap(strSrc);     // strSrcȫ����strTargetԪ����ɣ����strSrc                         
        }
        return strSrc;
    }

    void TestStringTrim()
    {
        std::string strTest("  \t Hello, World.\t\n  ");
        StringTrim(strTest);
        assert(strTest == "Hello, World.");

        strTest = ("Hello, World.");
        StringTrim(strTest);
        assert(strTest == "Hello, World.");

        strTest = "  \t\t  \t\n";
        StringTrim(strTest);
        assert(strTest.empty());

        strTest.clear();
        StringTrim(strTest);
        assert(strTest.empty()); 

        strTest = "******Soccer is best, but liquor is quicker!?!?!?!?!";
        StringTrim(strTest, "?!*");
        assert(strTest == "Soccer is best, but liquor is quicker");
    }

   

    inline std::string& OnlyDigits(std::string& str)
    {
        //���ֻ�������е�����
        //string a = "a3b4c!&d";
        std::string::iterator it = remove_if(str.begin(), str.end(), not1(ptr_fun(isdigit)));
        str.erase(it, str.end()); // 34
        return str;
    }


    // ����std::string& ���� void �ĸ���������? ��ʽ���ʽ�ô��뿴ȥ����Ȼ��
    std::string& StringTrimLeft(std::string& strSrc, const std::string& strTarget = " \t\n")
    {
        std::size_t nStart = strSrc.find_first_not_of(strTarget);
        if (nStart != std::string::npos)
        {
            strSrc.swap(strSrc.substr(nStart));     // swapС����
        }
        else
        {
            std::string().swap(strSrc);     // strSrcȫ����strTargetԪ����ɣ����strSrc                         
        }
        return strSrc;
    }

    void TestStringTrimLeft()
    {
        std::string strTest("  \t Hello, World.\t\n  ");
        StringTrimLeft(strTest);
        assert(strTest == "Hello, World.\t\n  ");

        strTest = ("Hello, World.");
        StringTrimLeft(strTest);
        assert(strTest == "Hello, World.");

        strTest = "  \t\t  \t\n";
        StringTrimLeft(strTest);
        assert(strTest.empty());

        strTest.clear();
        StringTrimLeft(strTest);
        assert(strTest.empty()); 

        strTest = "\t\t   ****Soccer is best!";
        StringTrimLeft(strTest, "\t *");
        assert(strTest == "Soccer is best!");
    }

    // ����std::string& ���� void �ĸ���������? ��ʽ���ʽ�ô��뿴ȥ����Ȼ��
    std::string& StringTrimRight(std::string& strSrc, const std::string& strTarget = " \t\n")
    {
        std::size_t nEnd = strSrc.find_last_not_of(strTarget);
        if (nEnd != std::string::npos)
        {
            strSrc.swap(strSrc.substr(0, nEnd + 1));    // swapС����
        }
        else
        {
            std::string().swap(strSrc);     // strSrcȫ����strTargetԪ����ɣ����strSrc                         
        }
        return strSrc;
    }

    void TestStringTrimRight()
    {
        std::string strTest("  \t Hello, World.\t\n  ");
        StringTrimRight(strTest);
        assert(strTest == "  \t Hello, World.");

        strTest = ("Hello, World.");
        StringTrimRight(strTest);
        assert(strTest == "Hello, World.");

        strTest = "  \t\t  \t\n";
        StringTrimRight(strTest);
        assert(strTest.empty());

        strTest.clear();
        StringTrimRight(strTest);
        assert(strTest.empty()); 

        strTest = "Soccer is best, but liquor is quicker!?!?!?!?!";
        StringTrimRight(strTest, "?!");
        assert(strTest == "Soccer is best, but liquor is quicker");
    }

	inline std::string& LTrim(std::string& str)
    {
        std::string::iterator p = std::find_if(str.begin(), str.end(), not1(ptr_fun(isspace)));
        str.erase(str.begin(), p);
        return str;
    }

    inline std::string& RTrim(std::string& str)
    {
        std::string::reverse_iterator p = find_if(str.rbegin(), str.rend(), not1(ptr_fun(isspace)));
        str.erase(p.base(), str.end());
        return str;
    }

    inline std::string& trim(std::string& str)
    {
        LTrim(RTrim(str));
        return str;
    }

    inline std::string& StringUpper(std::string& strSrc)
    {
        std::transform(strSrc.begin(), strSrc.end(),
            strSrc.begin(), std::toupper);          // toupper/tolower��ctype.h��
        return strSrc;
    }

    void TestStringUpper()
    {
        std::string str("abcABC123&*()");
        StringUpper(str);
        assert(str == "ABCABC123&*()");
    }

    std::string& StringLower(std::string& str)
    {
        std::transform(str.begin(), str.end(),
            str.begin(), std::tolower);
        return str;
    }

    void TestStringLower()
    {
        std::string str("abcABC123&*()");
        StringLower(str);
        assert(str == "abcabc123&*()");
    }

    inline bool StartWith(const std::string& strSrc, const std::string& strSub)
    {
        // return strSrc.find(strSub) == 0;         // find()Ч�ʱ�compare()��
        return strSrc.compare(0, strSub.size(), strSub) == 0;
    }

    inline bool EndWith(const std::string& strSrc, const std::string& strSub)
    {
        //return strSrc.rfind(strSub) == strSrc.size() - strSub.size();   // find()Ч�ʱ�compare()��
        return strSrc.compare(strSrc.size() - strSub.size(), strSub.size(), strSub) == 0;
    }

    void TestStartWith()
    {
        assert(StartWith("Hello, world", "He"));
        assert(!StartWith(" Hello ", "He"));
    }

    void TestEndWith()
    {
        assert(EndWith("Hello, world", "ld"));
        assert(EndWith(" Hello ", "o "));
    }

    bool ParseKeyValue(const std::string& strLine, std::string& strKey, std::string& strValue)
    {
        //if (strLine.empty())
        //    return false;       // ���п���

        std::size_t nPos = strLine.find('=');
        if (nPos != std::string::npos)
        {
            strKey = strLine.substr(0, nPos);
            StringTrim(strKey);
            strValue = strLine.substr(nPos + 1);    // ���� '='
            StringTrim(strValue);
            if (!strKey.empty() && !strValue.empty())
                return true;
        }

        return false;
    }

    void TestParseKeyValue()
    {
        std::string strKey, strValue;
        ParseKeyValue("name = Colin Wu ", strKey, strValue);
        assert(strKey == "name" && strValue == "Colin Wu");

        assert(!ParseKeyValue("name , Colin ", strKey, strValue));
    }

    // win32_data_path=E:\Data\LMore\;wince_data_path=\USB Disk\Disk\config file\LMoreData\;
    // AvoidFreeways=false;AvoidTollRoads=true;AvoidFerries=false;AvoidCarTrains=false;AvoidUnpavedRoads=true;AvoidUserDefinedArea=true;
    void ParseProperty(const std::string& strProperty, std::map<std::string, std::string> mapProperty)
    {
        std::vector<std::string> vecProperty;
        NStringTool::StringTokenize(strProperty, ";", vecProperty);

        for (std::vector<std::string>::const_iterator iter = vecProperty.begin();
            iter != vecProperty.end();
            ++iter)
        {
            std::string strKey, strValue;
            if (ParseKeyValue(*iter, strKey, strValue))
            {
                mapProperty.insert(std::make_pair(strKey, strValue));
            }
        }
    }

    void TestParseProperty()
    {
        std::string strTest = "win32_data_path=E:\\Data\\LMore\\;wince_data_path=\\USB Disk\\Disk\\config file\\LMoreData\\;    \
            AvoidFreeways=false;AvoidTollRoads=true;                            \
            AvoidFerries=false;AvoidCarTrains=false;AvoidUnpavedRoads=true;AvoidUserDefinedArea=true;";
        std::map<std::string, std::string> mapProperty;
        ParseProperty(strTest, mapProperty);
    }
}