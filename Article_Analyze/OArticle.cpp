#include "OArticle.h"
#include <iostream>
#include <fstream>
#include "OString.h"
#include "OWord.h"

using std::ifstream;
using std::ios;

void OArticle::BuildWordSet(){
    wordset.clear();
    for (ListIndex i = 0; i < wordlist.Length(); i++) {
        ListIndex pos = wordset.contains(wordlist[i]);
        if (pos == OList<OWord>::NPOS) {
            wordset.push(OWord(wordlist[i]));
        }
        else {
            wordset[pos].hit();
        }
    }
    BSort();
}

void OArticle::BSort(){
    ListIndex i, j;  
    for (i = 0; i < wordset.Length(); i++)
        for (j = 1; j < wordset.Length() - i; j++)
            if (wordset[j - 1] < wordset[j])
                wordset.swap(j - 1, j);
}

FileIndex OArticle::ReadFromFile(const char* filepath) {
    FileIndex filesize = 0;
    ifstream file;
    file.open(filepath, ios::in);
    if (!file.is_open()) {
        return FILE_NPOS;
    }

    char charbuffer;
    OString wordbuffer = "";
    wordlist.clear();

    while ((charbuffer = file.get()) != EOF) {
        if (charbuffer >= 'a' && charbuffer <= 'z' || charbuffer >= 'A' && charbuffer <= 'Z') {
            if (charbuffer >= 'A' && charbuffer <= 'Z') {
                charbuffer += 32;
            }
            wordbuffer.PushChar(charbuffer);
            filesize++;
            if (filesize < FILE_NPOS) {
                continue;
            }
            else {
                break;
            }
        }
        else {
            if (!(wordbuffer == "")) {
                if (stopwords.contains(wordbuffer) == OList<OString>::NPOS) {
                    wordlist.push(wordbuffer);
                }
                wordbuffer = "";
            }
        }
    }
    BuildWordSet();
    return filesize;
}

const OWord& OArticle::GetTopFreq(ListSize top) const
{
    return wordset[top];
}

int OArticle::QueryFreq(const OString& _word_) const
{
    ListIndex i = wordset.contains(_word_);
    if (i == OList<OWord>::NPOS) {
        return -1;
    }
    return wordset[i].getCount();
}

OList<FileIndex> OArticle::QueryPosition(const OString& _word_) const
{
    OList<FileIndex> _pos_list_;
    FileIndex startpos = 0;
    FileIndex posbuffer = 0;
    while ((posbuffer = wordlist.contains(_word_, startpos)) != OList<int>::NPOS) {
        _pos_list_.push(posbuffer);
        startpos = posbuffer + 1;
    }
    return _pos_list_;
}

void OArticle::Debug_PrintWordList(){
    MFOREACHLIST(wordlist, i) {
        std::cout << wordlist[i] << ", ";
    }
    std::cout << std::endl;
}

void OArticle::Debug_PrintWordSet()
{
    MFOREACHLIST(wordset, i) {
        std::cout << wordset[i].getWord() << ":" << wordset[i].getCount() << std::endl;
    }
}
