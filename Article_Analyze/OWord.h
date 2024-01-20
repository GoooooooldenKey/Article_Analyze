#pragma once
#include "OString.h"

//OWord�ࣺ
//ʵ���˶Ե��ʳ��ִ����Ĵ��棬���ṩ�˱ȽϷ�����

class OWord{
private:
    OString word;
    unsigned int count;
public:
    OWord(const OString& _word_) {
        word = _word_;
        count = 1;
    }

    OWord() {
        word = "";
        count = 0;
    }

    //���ʼ���+1
    void hit() {
        count++;
    }

    const OString& getWord() const {
        return word;
    }

    const int getCount() const {
        return count;
    }

    //�ж�����OWord�Ƿ�Ϊͬһ���ʣ����жϵ��ʣ�
    bool operator==(const OWord& rWord) const { return word == rWord.word; }

    //�ж�����OWord���ִ����Ĵ�С
    bool operator<(const OWord& rWord) const { return count < rWord.count; }
    bool operator>(const OWord& rWord) const { return rWord < *this; }
    bool operator>=(const OWord& rWord) const { return !(*this < rWord); }
    bool operator<=(const OWord& rWord) const { return !(*this > rWord); }
};