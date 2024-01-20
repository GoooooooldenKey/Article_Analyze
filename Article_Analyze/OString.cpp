#include "OString.h"
#include <stdexcept>

OString::~OString(){
    delete[] string;
}

const char& OString::operator[](const StringSize index) const
{
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    return string[index];
}

bool OString::operator==(const OString& RS) const
{
    StringIndex i = 0;
    while (true) {
        if (string[i] != '\0' && RS.string[i] != '\0') {
            if (string[i] == RS.string[i]) {
                i++;
                continue;
            }
            else {
                return false;
            }
        }
        else {
            return string[i] == RS.string[i];
        }
    }
}

OString& OString::operator=(const OString& rString)
{
    size = rString.size;
    char* newstring = new char[size + 1];
    for (StringIndex i = 0; i <= size; i++) {
        newstring[i] = rString[i];
    }
    delete[] string;
    string = newstring;
    return *this;
}

OString& OString::operator=(const char* rChars)
{
    StringSize newsize;
    for (newsize = 0; rChars[newsize] != '\0'; newsize++) {
        if (SIZE_MAX - newsize < 1) {
            throw std::out_of_range("string too large!");
        }
    }
    char* newstring = new char[newsize + 1];
    for (StringIndex i = 0; i <= newsize; i++) {
        newstring[i] = rChars[i];
    }
    delete[] string;
    string = newstring;
    size = newsize;
    return *this;
}

OString& OString::operator+=(const OString& rString)
{
    if (SIZE_MAX - size < rString.size + 1) {
        throw std::out_of_range("string too large!");
    }
    StringSize newsize = size + rString.size;
    char* newstring = new char[newsize + 1];
    for (StringIndex i = 0; i < newsize; i++) {
        if (i < size) {
            newstring[i] = string[i];
        }
        else {
            newstring[i] = rString[i - size];
        }
    }
    delete[] string;
    string = newstring;
    size = newsize;
    return *this;
}

OString& OString::operator+=(const char* rChars)
{
    StringSize newsize;
    for (newsize = 0; rChars[newsize] != '\0'; newsize++) {
        if (SIZE_MAX - size < newsize + 1) {
            throw std::out_of_range("string too large!");
        }
    }
    newsize += size;
    char* newstring = new char[newsize + 1];
    for (StringIndex i = 0; i < newsize; i++) {
        if (i < size) {
            newstring[i] = string[i];
        }
        else {
            newstring[i] = rChars[i - size];
        }
    }
    delete[] string;
    string = newstring;
    size = newsize;
    return *this;
}

OString& OString::operator+=(const char rChar)
{
    PushChar(rChar);
    return *this;
}

OString::OString(StringSize length) {
    size = length;
    string = new char[size + 1];
    string[size] = '\0';
}

OString::OString(const char stringIn[]) {
    for (size = 0; stringIn[size] != '\0'; size++);
    string = new char[size + 1];
    for (StringIndex i = 0; i < size; i++) {
        string[i] = stringIn[i];
    }
    string[size] = '\0';
}

OString::OString(const OString& s)
{
    size = 0;
    string = new char[size + 1];
    string[size] = '\0';
    *this = s;
}

OString::OString(){
    size = 0;
    string = new char[size + 1];
    string[size] = '\0';
}

void OString::PushChar(const char charIn){
    if (SIZE_MAX - size < 2) {
        throw std::out_of_range("string too large!");
    }
    char *newstring = new char[size + 2];
    if(size > 0){
        for (StringIndex i = 0; i < size; i++){
            newstring[i] = string[i];
        }
    }
    newstring[size] = charIn;
    delete[] string;
    string = newstring;
    size++;
    string[size] = '\0';
}

std::ostream& operator<<(std::ostream& cout, const OString& ostring){
    cout << ostring.string;
    return cout;
}

void operator>>(std::istream& cin, OString& ostring)
{
    delete[] ostring.string;
    ostring.size = 0;
    ostring.string = new char[0];
    char cbuffer = cin.get();
    while (cbuffer != '\n') {
        ostring.PushChar(cbuffer);
        cbuffer = cin.get();
    }
}
