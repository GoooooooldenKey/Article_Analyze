#pragma once
#include "OString.h"

//OWord类：
//实现了对单词出现次数的储存，并提供了比较方法。

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

    //单词计数+1
    void hit() {
        count++;
    }

    const OString& getWord() const {
        return word;
    }

    const int getCount() const {
        return count;
    }

    //判断两个OWord是否为同一单词（仅判断单词）
    bool operator==(const OWord& rWord) const { return word == rWord.word; }

    //判断两个OWord出现次数的大小
    bool operator<(const OWord& rWord) const { return count < rWord.count; }
    bool operator>(const OWord& rWord) const { return rWord < *this; }
    bool operator>=(const OWord& rWord) const { return !(*this < rWord); }
    bool operator<=(const OWord& rWord) const { return !(*this > rWord); }
};