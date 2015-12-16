//============================================================================
// Name        : cinarra.cpp
// Author      : yanwei
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <string.h>
#include "CampTargeter.h"
using namespace std;

int main(int argc, char *argv[]) {
	if(argc<2){
		cout << "data file required" << endl; // prints !!!Hello World!!!
		return 0;
	}
	string filename=string(argv[1]);
	CampTargeter targeter(filename);
	string line;
	while(getline(cin, line)){
		if(line.empty()) return 0;
		cout<<targeter.getCampaign(line)<<endl;;
	}
	return 0;
}
