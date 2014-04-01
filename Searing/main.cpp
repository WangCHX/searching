//
//  main.cpp
//  Searing
//
//  Created by WangCHX on 3/23/14.
//  Copyright (c) 2014 WangCHX. All rights reserved.
//

#include <iostream>
#include "Search.h"
using namespace std;
int main(int argc, const char * argv[])
{
    Search demo;
    cout << "query : ";
    char word[100];
    cin >> word;
    demo.doSearch(word);
    demo.printResult();
    return 0;
}