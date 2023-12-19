#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;
const map<char, int> xmas = { {'x',0},{'m',1},{'a',2},{'s',3} };

vector<string> rulesFromString(string line, int pos = 0)
{
	vector<string> temp;
	int space = 0;
	line = line.substr(0, line.size() - 1);
	while (space != -1)
	{
		space = line.find(',', pos);
		temp.push_back(line.substr(pos,space-pos));
		pos = space + 1;
	}
	return temp;
}

string findNextLocation(vector<string>rules, vector<int> properties)
{
	int rule = 0;
	while (rule < rules.size()-1)
	{
		string currRule = rules[rule];
		int property = properties[xmas.at(currRule[0])];
		char op = currRule[1];
		int colon = currRule.find(':');
		int comparison = stoi(currRule.substr(2, colon-2));
		string location = currRule.substr(colon + 1, -1);
		if (op == '<'&&property<comparison)
		{
			return location;
		}
		else if(op =='>'&&property>comparison)
		{
			return location;
		}
		rule++;
	}
	return rules[rules.size() - 1];
}

int sumVector(vector<int> vect)
{
	int temp = 0;
	for (int i = 0; i < vect.size(); i++)
	{
		temp += vect[i];
	}
	return temp;
}

bool checkWorkflow(vector<int> properties, int workflow, vector<vector<string>>rules, vector<string>locations)
{
	while (true)
	{
		string strWorkflow = findNextLocation(rules[workflow], properties);
		if (strWorkflow == "R")
		{
			return false;
		}
		else if (strWorkflow == "A")
		{
			return true;
		}
		workflow = find(locations.begin(), locations.end(), strWorkflow) - locations.begin();
	}
}

long long numRanges(vector<int>ranges)
{
	long long temp = 1;
	for (int i = 0; i < 4; i++)
	{
		temp *= ranges[2 * i + 1] - ranges[2 * i] + 1;
	}
	return temp;
}

vector<vector<int>> checkPart2Workflow(vector<int>ranges, int workflow, vector<vector<string>>rules, vector<string>locations)
{
	vector<vector<int>>goodRanges;
	vector<string> currentRules = rules[workflow];
	int rule = 0;
	
	while (rule < currentRules.size() - 1)
	{
		int done = 0;
		string currRule = currentRules[rule];
		int property = xmas.at(currRule[0]);
		char op = currRule[1];
		int colon = currRule.find(':');
		int comparison = stoi(currRule.substr(2, colon - 2));
		string location = currRule.substr(colon + 1, -1);
		if (location == "A")
		{
			done = 1;
		}
		if (location == "R")
		{
			done = 2;
		}
		int newWorkflow = find(locations.begin(), locations.end(), location) - locations.begin();

		if (op == '<')
		{
			vector<int>newRanges = ranges;
			newRanges[property * 2 + 1] = comparison - 1;
			ranges[property * 2] = comparison;
			if (done == 1)
			{
				goodRanges.push_back(newRanges);
			}
			else if (done == 0)
			{
				vector<vector<int>> temp = (checkPart2Workflow(newRanges, newWorkflow, rules, locations));
				
				for (int i = 0; i < temp.size(); i++)
				{
					goodRanges.push_back(temp[i]);
				}
				
			}
		}
		else if (op == '>')
		{
			vector<int>newRanges = ranges;
			newRanges[property * 2] = comparison + 1;
			ranges[property * 2 + 1] = comparison;
			if (done == 1)
			{
				goodRanges.push_back(newRanges);
			}
			else if (done == 0)
			{
				vector<vector<int>> temp = (checkPart2Workflow(newRanges, newWorkflow, rules, locations));
				for (int i = 0; i < temp.size(); i++)
				{
					goodRanges.push_back(temp[i]);
				}
				
			}
		}
		rule++;
	}
	string last = currentRules[currentRules.size() - 1];
	
	if (last == "A")
	{
		
		goodRanges.push_back(ranges);
		
	}
	else if (last !="R")
	{
		int newWorkflow = find(locations.begin(), locations.end(), last) - locations.begin();
		vector<vector<int>> temp =  checkPart2Workflow(ranges, newWorkflow, rules, locations);
		for (int i = 0; i < temp.size(); i++)
		{
			goodRanges.push_back(temp[i]);
		}
		
	}	
	return goodRanges;
}

long long getNumGoodRanges(vector<vector<int>> goodRanges)
{
	long long total=0;
	
	for (int i = 0; i < goodRanges.size(); i++)
	{
		vector<vector<int>> num;
		num.resize(4, vector<int>(4000, 0));
		for (int j = 0; j < 4; j++)
		{
			for (int k = goodRanges[i][j * 2]; k <= goodRanges[i][j * 2 + 1]; k++)
			{
				num[j][k - 1] = 1;
			}
		}
		vector<int> numEach = { 0,0,0,0 };
		for (int i = 0; i < 4000; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				numEach[j] += num[j][i];
			}
		}
		long long ruleRange = (long long)numEach[0] * (long long)numEach[1] * (long long)numEach[2] * (long long)numEach[3];
		total += ruleRange;
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC19.txt");
	int totalCount = 0;
	string lineN;
	bool ruleSection = true;
	vector<string> locations;
	vector<vector<string>>rules;
	vector<vector<int>> properties;
	while (getline(FileName, lineN)) {
		if (ruleSection)
		{
			if (lineN.size() == 0)
			{
				ruleSection = false;
				continue;
			}
			int pos = lineN.find('{');
			locations.push_back(lineN.substr(0, pos));
			rules.push_back(rulesFromString(lineN.substr(pos + 1, -1)));
		}
		else
		{
			vector<int> temp;
			int pos = 3;
			string line = lineN.substr(0, lineN.size() - 1);
			for (int i = 0; i < 4; i++)
			{
				int comma = line.find(',', pos);
				temp.push_back(stoi(line.substr(pos, comma - pos)));
				pos = comma + 3;
			}
			properties.push_back(temp);
		}
	}
	int startPoint = find(locations.begin(), locations.end(), "in") - locations.begin();
	for (int i = 0; i < properties.size(); i++)
	{
		if (checkWorkflow(properties[i], startPoint,rules,locations))
		{
			totalCount += sumVector(properties[i]);
		}
	}
	cout << totalCount << endl;
	vector<int> part2 = { 1, 4000, 1, 4000, 1, 4000, 1, 4000 };
	
	vector<vector<int>> goodRanges = checkPart2Workflow(part2, startPoint, rules, locations);
	long long part2Total = getNumGoodRanges(goodRanges);
	cout << part2Total << endl;
}