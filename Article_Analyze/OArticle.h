#pragma once
#include "OList.h"
#include "OString.h"
#include "OWord.h"

typedef OList<OString> WordList;
typedef OList<OWord> WordSet;
typedef size_t FileIndex;

const WordList stopwords = {
    "a", "an", "the", "and", "or", "but", "is", "are", "am", "was", "were",
    "be", "being", "been", "to", "of", "in", "on", "at", "by", "for", "with"
};

//OArticle类：
//实现了对文章的读入、分析、处理

class OArticle {
private:
    WordList wordlist;
    WordSet wordset;

    //从wordlist单词列表构建wordset单词次数统计表
    void BuildWordSet();

    //冒泡降序排序wordset
    void BSort();

public:
    static constexpr FileIndex FILE_NPOS = SIZE_MAX;

    //从文件读入文章，返回有效读入字符数（不含舍弃部分）
    FileIndex ReadFromFile(const char* filepath);

    //返回指定排名的单词
    const OWord& GetTopFreq(ListSize top) const;

    //查询某个单词的排名
    int QueryFreq(const OString& _word_) const;

    //查询某个单词的所有位置
    OList<FileIndex> QueryPosition(const OString& _word_) const;

    //调试用
    void Debug_PrintWordList();
    void Debug_PrintWordSet();
};

