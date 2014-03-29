//
//  LP.h
//  Searing
//
//  Created by WangCHX on 3/23/14.
//  Copyright (c) 2014 WangCHX. All rights reserved.
//

#ifndef __Searing__LP__
#define __Searing__LP__

#include <iostream>
#include <unordered_map>
#include <string>
#include <fstream>
#include <vector>
#include "vbyte.h"
using namespace std;
typedef struct {int docNum; int chunkNum; int postingNum;} wordInfo;
typedef struct {int chunk_last_wordid; int chunk_last_docid; int filenum; int offset;} chunk;
unordered_map<int, string> docMap;
unordered_map<string, int> lexMap;
unordered_map<int, wordInfo> wordIndex;
unordered_map<int, chunk> chunkIndex;
const int MAXDID = 1000000000;
class LP {
public:
    int    word_id;
	int    doc_num;
	int	   start_chunk;
	int    start_posting_num;
	int    end_posting_num;
	int    num_of_chunks;
	int    cur_posting_docid;
	int	   cur_posting_freq;
	int    cur_first_pos;
	vector <chunk> chunkvector;
    LP* openList(int wordid);
    void closeList(LP *t);
    int nextGEQ(LP *t, int num);
    int getFreq(LP *t);
};
#endif /* defined(__Searing__LP__) */
