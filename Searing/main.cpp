//
//  main.cpp
//  Searing
//
//  Created by WangCHX on 3/23/14.
//  Copyright (c) 2014 WangCHX. All rights reserved.
//

#include <iostream>
#include "Search.h"
#include <cstdio>
using namespace std;
int main(int argc, const char * argv[])
{
    Search demo;
    char word[100];
    while (1){
        cout << "query : ";
        cin.getline(word, 100);
        demo.doSearch(word);
        demo.printResult();
    }
    return 0;
}