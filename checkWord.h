#pragma once

//
// Created by Barlas on 1/11/2021.
//

bool whenStart = false;

std::string START_WORD = "<BODY>";
std::string END_WORD = "</BODY>";

bool isStart(std::string word) {

    if (word.find(START_WORD) != std::string::npos) {
        return true;
    }
    return false;
}

bool isEnd(std::string word) {

    if (word.find(END_WORD) != std::string::npos) {
        return true;
    }

    return false;
}

std::string checkWord(std::string word) {
    std::string tempWord;
    if (isEnd(word)) {
        whenStart = false;
    }

    if (whenStart && ((word[0] >= 'a' && word[0] <= 'z') || (word[0] >= 'A' && word[0] <= 'Z'))) {
        char *next_token1;
        char* token = strtok_s(&word[0], "\",.]:'>()", &next_token1);
        return token;

    }
    if (isStart(word)) {
        whenStart = true;
        int startPos = word.find(START_WORD) + START_WORD.length();
        for (int i = startPos; i < word.size(); ++i) {
            tempWord += word[i];
        }
        word = tempWord;
        return  word;

    }
    else {
        return "";
    }
}

