//
//  MainSearch.cpp
//  Searing
//
//  Created by WangCHX on 3/23/14.
//  Copyright (c) 2014 WangCHX. All rights reserved.
//

#include "MainSearch.h"
MainSearch::MainSearch(){
    init();
}

void MainSearch::init() {
    k1 = 1.2;
    b = 0.75;
    
    // load doc information
    ifstream in(DOCINFO_LOCATION);
    if (in.is_open()) {
        in.seekg(0, ios::end);
        int size = (int)in.tellg();
        char *buffer = new char[size];
        in.seekg(0, ios::beg);
        in.read(buffer, size);
        in.close();
        int offset = 0;
        while(offset < size) {
            int id;
            memcpy(&id, buffer + offset, sizeof(int));
            offset += sizeof(int);
            int len;
            memcpy(&len, buffer + offset, sizeof(int));
            offset += sizeof(int);
            char docName[len + 1];
            docName[len] = '\0';
            memcpy(docName, buffer + offset, len);
            offset += len;
            docMap[id] = string(docName);
        }
        delete buffer;
    }
    
    //load lex information
    ifstream lexin(LEXIINFO_LOCATION);
    if (lexin.is_open()) {
        lexin.seekg(0, ios::end);
        int size = (int)lexin.tellg();
        char *buffer = new char[size];
        lexin.seekg(0, ios::beg);
        lexin.read(buffer, size);
        lexin.close();
        int offset = 0;
        char word[1000];
        while(offset < size) {
            int len;
            memcpy(&len, buffer + offset, sizeof(int));
            offset += sizeof(int);
            word[len] = '\0';
            memcpy(word, buffer + offset, len);
            offset += len;
            int id;
            memcpy(&id, buffer + offset, sizeof(int));
            offset += sizeof(int);
            lexMap[string(word)] = id;
        }
        delete buffer;
    }
    
    
    //load word index
    
    char fileName[30] = {0};
    int wordIndexNum = 5;
    int part1, part2, part3, part4, part5;
	char temp[4];
    for (int i = 0; i < wordIndexNum; i ++) {
        sprintf(fileName, "word_index%d", i);
        ifstream in((RESULT_LOCATION + fileName).data(), ios::in|ios::binary);
        while (in.peek() != EOF) {
            in.read(temp, sizeof(int));
            memcpy(&part1, temp, sizeof(int));
            in.read(temp, sizeof(int));
            memcpy(&part2, temp, sizeof(int));
            in.read(temp, sizeof(int));
            memcpy(&part3, temp, sizeof(int));
            in.read(temp, sizeof(int));
            memcpy(&part4, temp, sizeof(int));
            wordInfo info = {part2, part3, part4};
            wordIndex[part1] = info;
        }
    }
    
    //load chunk index
    int chunkIndexNUM = 2;
    for (int i = 0; i < chunkIndexNUM; i ++) {
        sprintf(fileName, "chunk_index%d", i);
        ifstream in((RESULT_LOCATION + fileName).data(), ios::in|ios::binary);
        while (in.peek() != EOF) {
            in.read(temp, sizeof(int));
            memcpy(&part1, temp, sizeof(int));
            in.read(temp, sizeof(int));
            memcpy(&part2, temp, sizeof(int));
            in.read(temp, sizeof(int));
            memcpy(&part3, temp, sizeof(int));
            in.read(temp, sizeof(int));
            memcpy(&part4, temp, sizeof(int));
            in.read(temp, sizeof(int));
            memcpy(&part5, temp, sizeof(int));
            chunk info = {part2, part3, part4, part5};
            chunkIndex[part1] = info;
        }
    }
}


void MainSearch::doSearch() {






























}