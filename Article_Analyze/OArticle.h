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

//OArticle�ࣺ
//ʵ���˶����µĶ��롢����������

class OArticle {
private:
    WordList wordlist;
    WordSet wordset;

    //��wordlist�����б���wordset���ʴ���ͳ�Ʊ�
    void BuildWordSet();

    //ð�ݽ�������wordset
    void BSort();

public:
    static constexpr FileIndex FILE_NPOS = SIZE_MAX;

    //���ļ��������£�������Ч�����ַ����������������֣�
    FileIndex ReadFromFile(const char* filepath);

    //����ָ�������ĵ���
    const OWord& GetTopFreq(ListSize top) const;

    //��ѯĳ�����ʵ�����
    int QueryFreq(const OString& _word_) const;

    //��ѯĳ�����ʵ�����λ��
    OList<FileIndex> QueryPosition(const OString& _word_) const;

    //������
    void Debug_PrintWordList();
    void Debug_PrintWordSet();
};

