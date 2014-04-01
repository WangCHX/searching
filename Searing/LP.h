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
using namespace std;
struct STRU_DOC
{
	string doc_name;
	//int file_id;
	//int offset;
	int len;
    STRU_DOC(){};
    STRU_DOC(string temp, int llen):doc_name(temp), len(llen){}
};
typedef struct {int docNum; int chunkNum; int postingNum;} wordInfo;
typedef struct {int chunk_last_wordid; int chunk_last_docid; int filenum; int offset;} chunk;
static unordered_map<int, STRU_DOC> docMap;
static unordered_map<string, int> lexMap;
static unordered_map<int, wordInfo> wordIndex;
static unordered_map<int, chunk> chunkIndex;
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
};
#endif /* defined(__Searing__LP__) */
