//
//  MainSearch.cpp
//  Searing
//
//  Created by WangCHX on 3/23/14.
//  Copyright (c) 2014 WangCHX. All rights reserved.
//

#include "Search.h"
Search::Search(){
    init();
}

void Search::init() {
    k1 = 1.2;
    b = 0.75;
    total_size = 0;
    N = 0;
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
            int d;
            memcpy(&d, buffer + offset, sizeof(int));
            offset += sizeof(int);
            STRU_DOC val(docName, d);
            docMap[id] = val;
            total_size += d;
            N ++;
        }
        d_agv = total_size / N;
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
    
    char fileName[100] = {0};
    int wordIndexNum = 5;
    int part1, part2, part3, part4, part5;
	char temp[4];
    for (int i = 0; i < wordIndexNum; i ++) {
        sprintf(fileName, "/Users/apple/Developer/INDEX/result/word_index%d", i);
        ifstream in(fileName, ios::in|ios::binary);
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
        sprintf(fileName, "/Users/apple/Developer/INDEX/result/chunk_index%d", i);
        ifstream in(fileName, ios::in|ios::binary);
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


void Search::doSearch(char* words) {
    struct timeval start, end;
    
    gettimeofday(&start, NULL);
    
	cout<<"do searching...."<<endl<<" key words:"<<words<<endl;
	//for(int i =0; i< key_words.size();i++)
	//	cout<<key_words[i]<<" ";
	result_count = 0;
	int request_count = 0;
	string word="";
	int pos=0;
    int N = (int)docMap.size();
	vector<string> request_list;
//	while(get_one_word(words,pos,word))
//	{
//		cout<<"new:"<<word<<endl;
//		request_list.push_back(word);
//		request_count++;
//		word="";
//        
//	}
    stringstream ss;
    ss << words;
    string temp;
    while (ss >> temp) {
        request_list.push_back(temp);
        request_count ++;
    }
	if(request_count == 0)
		return;
    
	vector<LP*> p;
    //	_result.print();
	for(int i = 0 ; i < request_list.size();i++)
	{
		int word_id=lexMap[request_list[i]];
		cout<<"word: "<<request_list[i]<<" word_id:"<<word_id<<endl;
		if(word_id == 0)
			continue;
		LP* tmp = openList(word_id);
		if(tmp == NULL)
			continue;
		p.push_back(tmp);
	}
	if(p.size() == 0)
		return;
	cout<<"p.size:"<<p.size()<<endl;
	cout<<"doc_map_size: "<<docMap.size()<<endl;
	int did = 0;
	while(did < N)
	{
		int d = 0;
	 	did = nextGEQ(p[0],did);
//	 	if( did == 0)
// 		{
// 			cout<<"did = 0"<<endl;
// 			continue;
// 		}
	 	for(int i = 1; (i< p.size())&& ((d=nextGEQ(p[i],did))==did);i++);
	 	if(did> N)
	 		break;
		if(d > did) did = d-1;
		else
		{
			float bm25_all = 0.0;
			STRU_DOC one_doc = docMap[did];
			//cout<<"doc_id:"<<did<<"url:"<<one_doc.doc_name<<" file: "<<one_doc.file_id<<" offset:"<<one_doc.offset<<" len:"<<one_doc.len<<endl;
			//int target_pos = getPos(p[0]);
			for( int k = 0 ; k<p.size(); k++)
			{
			 	int freq= getFreq(p[k]);
                
			 	int ft=p[k]->doc_num;
                
			 	if(one_doc.doc_name == "")
			 		continue;
			 	//cout<<"doc_id:"<<did<<"url:"<<one_doc.doc_name<<" file: "<<one_doc.file_id<<" offset:"<<one_doc.offset<<" len:"<<one_doc.len<<endl;
			 	//cout<<"req:"<<freq<<" ft:"<<ft<<endl;
			 	//comput bm25
			 	float K = (float)k1 * (float)((1-b) + b* ((float)one_doc.len / (float)d_agv ) );
			 	float bm25 = log ( (float)(N-ft+0.5)/(float)(ft+0.5) ) * ((k1 + 1)*(float)freq)/(float)(K + freq);
			 	//cout<<"bm25:"<<bm25<<endl;
			 	bm25_all+=bm25;
	 		}
		 	if(result_count < 10)
		 	{
                STRU_RESULT temp;
				temp._url =one_doc.doc_name;
				temp._bm25=bm25_all;
				temp._doc_id = did;
				//temp._pos = target_pos;
                result_array.push(temp);
		 		result_count++;
		 	}
		 	else if(bm25_all > result_array.top()._bm25)
		 	{
                STRU_RESULT temp;
				temp._url =one_doc.doc_name;
				temp._bm25=bm25_all;
				temp._doc_id = did;
				//temp._pos = target_pos;
                result_array.pop();
                result_array.push(temp);
                
		 	}
            
	 		//sort(result_array,0,result_count-1);
	 	}
	 	//cout<<"list:";
	 	//for(int j =0; j < result_count; j++)
	 	//	cout<<"["<<j<<"] "<<result_array[j]._bm25<<endl;
        
		did++;
	}
    gettimeofday(&end, NULL);
	_searching_time  = (end.tv_sec  - start.tv_sec)*1000+ (end.tv_usec - start.tv_usec)/1000.0;
    
}
void Search::printResult() {
    cout << "time consumed: " << this->_searching_time << endl;
    cout << "top 10 results: " << endl;
    vector<STRU_RESULT> res;
    while (!result_array.empty()) {
        STRU_RESULT temp = result_array.top();
        res.insert(res.begin(), temp);
        result_array.pop();
    }
    for (int i= 0; i < res.size(); i ++) {
        cout << i + 1 << " url: " << res[i]._url << " bm25: " << res[i]._bm25 << endl;
    }
}