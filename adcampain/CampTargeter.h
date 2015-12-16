/*
 * CamTargeter.h
 *
 *  Created on: Nov 26, 2015
 *      Author: yjiang
 */

#ifndef CAMPTARGETER_H_
#define CAMPTARGETER_H_
#include <tr1/unordered_set>
#include <tr1/unordered_map>
#include <string>
#include <vector>
#include <climits>

using namespace std;

struct Campaign{
	string name;
	int counter;//keep a counter so I can prefer starving Campaigns (the one with least counter)
	Campaign(string& cname):name(cname),counter(0){};
};
//to avoid campaign starving, we can either use a random picking or keeping a counter for each campain and prefer the least used
//I pick the later method because it is faster than generating random numbers

class CampTargeter {
public:
	CampTargeter(const string& filename);
	virtual ~CampTargeter();

	string getCampaign(string& line);
private:
	//prepare the inverted index map (m_target2Camp) for quick searching
	void parseData(const string& filename);
private:
	vector<Campaign> m_campaigns;//the vector index is CampaignID
	tr1::unordered_map<unsigned short, tr1::unordered_set<int> > m_target2Camp;//inverted index: map target id to CampaignID
	//I use an unordered map because in example we have very limited number of target ids, 
	//in real application when we have close to 65535 target IDs, we can simply use a vector
};

#endif /* CAMPTARGETER_H_ */
