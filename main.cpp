
#include <iostream>
#include <fstream>
#include <string.h>
#include <time.h>


#include "./checkWord.h"
#include "./FileOpener.h"
#include "./HashMap.h"


void toLowerCase(std::string* word) {
    for (int i = 0; i < word->size(); i++) {
        (*word)[i] = ::tolower((*word)[i]);
    }
}

int main() {
    clock_t tStart = clock();

    HashMap<std::string, int>* wordList = new HashMap<std::string, int>(2000000);
    HashMap<std::string, int>* stopWordList = new HashMap<std::string, int>(1000);


    std::string stopWord;
    std::ifstream stopWords("./Reuters-21578/stopwords.txt");

    while (stopWords >> stopWord) {
        stopWordList->put(stopWord, 0);
    }
    stopWords.close();


    std::string word;
    std::string sgmFile = "./Reuters-21578/";


    for (int j = 0; j <= 21; ++j) {
        sgmFile += sgmStringTransporter(j);
        std::ifstream MyFile(sgmFile);
        while (MyFile >> word) {

            std::string parsedString = checkWord(word);
            toLowerCase(&parsedString);

            if (parsedString != "") {

                if (stopWordList->isExist(parsedString) == 0) {

                    if (wordList->isExist(parsedString) == 1) {
                        int previousValue = wordList->get(parsedString);
                        previousValue++;
                        wordList->put(parsedString, previousValue);
                    }
                    else {
                        wordList->put(parsedString, 1);
                    }
                }
            }
        }
        MyFile.close();
        sgmFile = "./Reuters-21578/";
    }

    wordList->calculateTopTen();

    printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

    return 0;
}

