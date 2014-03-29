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
};

#endif /* defined(__Searing__MainSearch__) */
