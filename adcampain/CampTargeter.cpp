/*
 * CampTargeter.cpp
 *
 *  Created on: Nov 26, 2015
 *      Author: yjiang
 */

#include "CampTargeter.h"
#include <fstream>
#include <sstream>
#include <iostream>

CampTargeter::CampTargeter(const string& filename) {
	// TODO Auto-generated constructor stub
	parseData(filename);
}

CampTargeter::~CampTargeter() {
	// TODO Auto-generated destructor stub
}


void CampTargeter::parseData(const string& filename){
	tr1::unordered_map<string, int> name2campid;//local map, in order to skip duplicate campaign name in data file
	ifstream myfile(filename.c_str());
	string line;
	if (myfile.is_open()){
		while ( getline (myfile,line) ){
			istringstream iss(line);
			string campName;
			if (!(iss >> campName)){//skip error line
				continue;
			}
			if(name2campid.find(campName)==name2campid.end()){
				m_campaigns.push_back(Campaign(campName));
				int campainID=(int)m_campaigns.size()-1;
				name2campid[campName]=campainID;
				int target=0;
				int targetcter=0;
				while(iss>>target){
					++targetcter;
					m_target2Camp[target].insert(campainID);
				}
				//cout<<"Regiestered "<<campName<<" to "<< targetcter <<" targets."<<endl;
			}
		}
		myfile.close();
	}
	else cout << "Unable to open file "<<filename<<endl;
}

string CampTargeter::getCampaign(string& line){
	istringstream iss(line);
	int target=0;
	tr1::unordered_map<int,int> hitcount;//compaignID->count, counting No. of appearance for campaigns
	int maxid=-1;
	while(iss>>target){
		auto it1=m_target2Camp.find(target);
		if(it1!= m_target2Camp.end()){//if it is a interested target to any campaign
			for(auto it2 = it1->second.begin(); it2!= it1->second.end();++it2){
				auto it3=hitcount.find(*it2);
				if(it3==hitcount.end()) hitcount[*it2]=1;
				else ++it3->second;

				if(maxid==-1 || hitcount[*it2]>hitcount[maxid] || //pick the one with most count
					(hitcount[*it2]==hitcount[maxid] && m_campaigns[*it2].counter <m_campaigns[maxid].counter)){//when counts are equal, pick the starving campaign
					maxid=*it2;
				}
			}
		}
	}
	if(maxid!=-1){
		++m_campaigns[maxid].counter;
		return m_campaigns[maxid].name;
	}
	return "no campaign";
}
