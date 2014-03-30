//
//  MainSearch.h
//  Searing
//
//  Created by WangCHX on 3/23/14.
//  Copyright (c) 2014 WangCHX. All rights reserved.
//

#ifndef __Searing__MainSearch__
#define __Searing__MainSearch__

#include "LP.h"
#include <queue>

struct STRU_RESULT
{
	std::string _url;
	std::string _title;
	std::string _round_text;
	float _bm25;
	int _doc_id;
	int _pos;
    
	STRU_RESULT()
	{
		_url = "";
		_title = "";
		_round_text="";
		_bm25=0.0;
		_doc_id=0;
		_pos=0;
	}
    bool operator < (const STRU_RESULT &node) const{
        return this->_bm25 > node._bm25;
    }
};
const string LEXIINFO_LOCATION = "/Users/apple/Developer/INDEX/lexInfo.txt";
const string DOCINFO_LOCATION = "/Users/apple/Developer/INDEX/docInfo.txt";
const string RESULT_LOCATION = "/Users/apple/Developer/INDEX/result/";
class MainSearch{
public:
    MainSearch();
    ~MainSearch(){};
    void init();
    void doSearch();
    
private:
    double k1;
    double b;
    priority_queue<STRU_RESULT> result_array;
};

#endif /* defined(__Searing__MainSearch__) */
