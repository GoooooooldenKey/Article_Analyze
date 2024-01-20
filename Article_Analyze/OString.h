#pragma once
#include <iostream>

typedef size_t StringSize;
typedef size_t StringIndex;

//OString�ࣺ
//ʵ���˻������ַ���

class OString
{
    //��cin, cout��֧��
    friend std::ostream& operator<<(std::ostream& cout, const OString& ostring);
    friend void operator>>(std::istream& cin, OString& ostring);

private:
    char* string;
    StringSize size;

public:
    OString(StringSize length);
    OString(const char stringIn[]);
    OString(const OString&);
    OString();
    ~OString();

    const char& operator[](const StringSize index) const;
    bool operator==(const OString& RS) const;

    OString& operator=(const OString& rString);
    OString& operator=(const char* rChars);

    OString& operator+=(const OString& rString);
    OString& operator+=(const char* rChars);
    OString& operator+=(const char rChar);

    //���ַ���β�����һ���ַ�
    void PushChar(const char charIn);
};