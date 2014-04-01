//
//  LP.cpp
//  Searing
//
//  Created by WangCHX on 3/23/14.
//  Copyright (c) 2014 WangCHX. All rights reserved.
//

//int    word_id;
//int    doc_num;
//int	   start_chunk;
//int    start_posting_num;
//int    end_posting_num;
//int    num_of_chunks;
//int    cur_posting_docid;
//int	   cur_posting_freq;
//int    cur_first_pos;
#ifndef x
#define x
#include "LP.h"
#include "vbyte.h"
inline LP* openList(int wordid) {
    LP *res = new LP;
    res->word_id = wordid;
    res->doc_num = wordIndex[wordid].docNum;
    res->start_chunk = wordIndex[wordid].chunkNum;
    res->start_posting_num = wordIndex[wordid].postingNum;
    res->end_posting_num = wordIndex[wordid + 1].postingNum - 1;
    res->num_of_chunks = wordIndex[wordid + 1].chunkNum - wordIndex[wordid].chunkNum + 1;
    res->cur_posting_docid = res->start_posting_num;
    int begin = res->start_chunk;
    for (int i = 0;i < res->num_of_chunks;i ++) {
        chunk temp;
        temp.chunk_last_docid = chunkIndex[begin + i].chunk_last_docid;
        temp.chunk_last_wordid = chunkIndex[begin + i].chunk_last_wordid;
        temp.filenum = chunkIndex[begin + i].filenum;
        temp.offset = chunkIndex[begin + i].offset;
        res->chunkvector.push_back(temp);
    }
    return res;
}

inline int nextGEQ(LP *t, int search_docid) {
    int docid = 0;
	int start_chunk_num;
	int start_posting_num = 1;
	int end_posting_num = 128;
	int posting_num = 1;
	int filenum;
	int offset;
	int i;
	int chunk_size;
	int total_len = 0;
	int len = 0;
	int n;
	int test;
	unsigned int res1;
	unsigned int res2;
	unsigned int res3;
	unsigned int* res_arr;
	int last_docid = 0;
	string file="/Users/apple/Developer/INDEX/result/";
	char filename[50]={0};
	char* chunk;
	unsigned char* uchunk;
    
	start_chunk_num = t->start_chunk;
    
	for (i=0; i< t->num_of_chunks-1;i++){
		if(t->chunkvector.at(i).chunk_last_docid>=search_docid){
			start_chunk_num = t->start_chunk + i;
			break;
		}
		end_posting_num = t->end_posting_num+1;
	}
    start_chunk_num = t->start_chunk + i;
    
    if(i==0)
		start_posting_num = t->start_posting_num+1;
    
    //cout<<"start_chunk_num: "<<start_chunk_num<<endl;
    
    if(chunkIndex[start_chunk_num].filenum == chunkIndex[start_chunk_num+1].filenum){
        //cout<<"chunk didn't cross file"<<endl;
        chunk_size = chunkIndex[start_chunk_num+1].offset - chunkIndex[start_chunk_num].offset;
        chunk = new char[chunk_size];
        uchunk = new unsigned char[chunk_size];
        sprintf (filename, "data%d", chunkIndex[start_chunk_num].filenum);
        file = file + filename;
        ifstream myFile (file.c_str(), ios::in | ios::binary);
        myFile.seekg(chunkIndex[start_chunk_num].offset, ios::beg);
        myFile.read(chunk,chunk_size);
        memcpy(uchunk, chunk, chunk_size);
    }
    
    if(chunkIndex[start_chunk_num].filenum < chunkIndex[start_chunk_num+1].filenum){
        int num_of_files = chunkIndex[start_chunk_num+1].filenum - chunkIndex[start_chunk_num].filenum-1;
        chunk_size = (1200000 - chunkIndex[start_chunk_num].offset) + chunkIndex[start_chunk_num+1].offset + 1200000*num_of_files;
        chunk = new char[chunk_size];
        uchunk = new unsigned char[chunk_size];
        sprintf (filename, "data%d", chunkIndex[start_chunk_num].filenum);
        file = file + filename;
        ifstream myFile1 (file.c_str(), ios::in | ios::binary);
        myFile1.seekg(chunkIndex[start_chunk_num].offset, ios::beg);
        myFile1.read(chunk,1200000 - chunkIndex[start_chunk_num].offset);
        file = "/Users/apple/Developer/INDEX/result/";
        int chunk_offset = 1200000 - chunkIndex[start_chunk_num].offset;
        
        for(int k=0; k<num_of_files; k++){
            sprintf (filename, "data%d", chunkIndex[start_chunk_num].filenum+1+k);
            file = file + filename;
            ifstream myFile2 (file.c_str(), ios::in | ios::binary);
            myFile2.read(chunk+chunk_offset,1200000);
            chunk_offset = chunk_offset + 1200000;
            file = "/Users/apple/Developer/INDEX/result/";
        }
        
        sprintf (filename, "data%d", chunkIndex[start_chunk_num+1].filenum);
        file = file + filename;
        ifstream myFile3 (file.c_str(), ios::in | ios::binary);
        myFile3.read(chunk+chunk_offset,chunkIndex[start_chunk_num+1].offset);
        chunk_offset = chunk_offset + chunkIndex[start_chunk_num+1].offset;
        file = "/Users/apple/Developer/INDEX/result/";
        memcpy(uchunk, chunk, chunk_size);
    }
    
    //cout<<"start_posting_num: "<<start_posting_num<<endl;
    //cin>>test;
    
    while(posting_num<=128){
        if(posting_num<start_posting_num){
            len = readVbyte(uchunk+total_len, res1);
            total_len = total_len + len;
            //cout<<"docid diff: "<<res1<<endl;
            len = readVbyte(uchunk+total_len, res2);
            total_len = total_len + len;
            //		 cout<<"freq: "<<res2<<endl;
            
            for(int h = 0; h<res2; h++){
                len = readVbyte(uchunk+total_len, res3);
                total_len = total_len + len;
                //			 cout<<"pos diff: "<<res3<<endl;
            }
            //  cout<<"total_len: "<<total_len<<endl;
        }
        
        if(posting_num>=start_posting_num){
			// cout<<"when posting_num equals start_posting_num"<<endl;
            len = readVbyte(uchunk+total_len, res1);
            //cout<<"total_len: "<<total_len<<endl;
            total_len = total_len + len;
            //cout<<"total_len: "<<total_len<<endl;
            //cout<<"res1: "<<res1<<endl;
            last_docid = last_docid + res1;
            //cout<<"docid: "<<last_docid<<endl;
            len = readVbyte(uchunk+total_len, res2);
            total_len = total_len + len;
            //cout<<"freq: "<<res2<<endl;
            
            
            if (last_docid>=search_docid){
                t->cur_posting_docid = last_docid;
                t->cur_posting_freq = res2;
                len = readVbyte(uchunk+total_len, res3);
                total_len = total_len + len;
                t->cur_first_pos = res3;
                return t->cur_posting_docid;
            }
            
            for(int h = 0; h<res2; h++){
			 	len = readVbyte(uchunk+total_len, res3);
			 	total_len = total_len + len;
			 	//cout<<"pos diff: "<<res3<<endl;
            }
            
		}
        //		 res_arr = new unsigned int[res2];
		// cout<<"posting_num: "<<posting_num<<endl;
        posting_num++;
    }
    
    //	filenum = chunk_index[start_chunk_num].filenum;
    //	offset = chunk_index[start_chunk_num].offset;
    //	cout<<"start_chunk_num: "<<start_chunk_num<<" filenum: "<<filenum<<" offset: "<<offset<<" chunk_size: "<<chunk_size<<endl;
    //	return docid;

    //return MAXDID;
    return 100000000;
}

inline int getFreq(LP *t){
    return t->cur_posting_freq;
}

#endif