#include <iostream>
#include "OArticle.h"
#include "OString.h"

using std::cout;
using std::endl;
using std::cin;

int main() {
    OArticle article;

    FileIndex fsize = article.ReadFromFile("article.txt");
    if (fsize == OArticle::FILE_NPOS) {
        cout << "Failed reading file";
        return -1;
    }
    cout << fsize << " char(s) read" << endl;
    cout << endl;

    cout << "Top 10 Most Frequency Words: " << endl;
    for (int i = 0; i < 10; i++) {
        cout << article.GetTopFreq(i).getWord();
        cout << " : " << article.GetTopFreq(i).getCount() << endl;
    }

    cout << endl << "Enter a word to query its frequency and position: ";
    OString wordInput;
    cin >> wordInput;

    int wordcount = article.QueryFreq(wordInput);
    if (wordcount != -1) {
        cout << wordInput << " : " << wordcount << endl;

        OList<FileIndex> poslist = article.QueryPosition(wordInput);
        cout << "Appeared at: ";
        MFOREACHLIST(poslist, i) {
            cout << poslist[i] << ", ";
        }
        cout << endl;
    }
    else {
        cout << "Word not found" << endl;
    }
    return 0;
}