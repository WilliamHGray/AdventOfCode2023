#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

bool isANumber(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	return false;
}

vector<long long> numsFromString(string line, int pos)
{
	vector<long long> temp;
	long long space = 0;
	while (space != -1)
	{
		space = line.find(' ', pos);
		temp.push_back(stoull(line.substr(pos, -1)));
		pos = space + 1;
	}
	return temp;
}

long long getNextPos(long long pos, vector < long long > rules)
{
	long long end = rules[0], start = rules[1], range = rules[2];
	if (pos >= start && pos < start + range)
	{
		return end + (pos - start);
	}
	return -1;
}

int main() {
	ifstream FileName;
	FileName.open("AOC5.txt");
	int totalCount = 0;
	string lineN;
	vector<vector<vector<long long>>> rules;
	vector<vector<long long>>temp;
	vector<long long> inputs;
	vector<long long> outputs;
	bool init = false;
	while (getline(FileName, lineN)) {
		if (!init)
		{
			init = true;
			inputs = numsFromString(lineN, 7);
		}
		else if (lineN.size() != 0 && isANumber(lineN[0]))
		{
			temp.push_back(numsFromString(lineN, 0));
		}
		else if (lineN.size() != 0)
		{
			rules.push_back(temp);
			temp.clear();
		}
	}
	rules.push_back(temp);
	temp.clear();
	rules.erase(rules.begin());
	for (int i = 0; i < inputs.size(); i++)
	{
			long long pos = inputs[i];
			for (int j = 0; j < rules.size(); j++)
			{
				for (int k = 0; k < rules[j].size(); k++)
				{
					long long next = getNextPos(pos, rules[j][k]);
					if (next != -1)
					{
						pos = next;
						break;
					}
				}
			}
			outputs.push_back(pos);
	}
	long long minVal = outputs[0];
	for (int i = 0; i < outputs.size(); i++)
	{
		if(outputs[i] < minVal)
		{
			minVal = outputs[i];
		}
		//cout << outputs[i] << endl;
	}
	cout << endl;
	cout << minVal<<endl;
	
    //Part 2
    outputs.clear();
    for (int i = 0; i < inputs.size(); i+=2)
	{
	    std::cout<<"starting seed "<<i<<endl;
	    std::cout<<"starting pos " << inputs[i]<<endl;
	    long long root = sqrtl(inputs[i+1]);
	    long long minim = minVal;
	    long long minPos = inputs[i];
	    for(long long iter = inputs[i];iter<inputs[i]+inputs[i+1]; iter+=root)
	    {
			long long pos = iter;
			for (int j = 0; j < rules.size(); j++)
			{
				for (int k = 0; k < rules[j].size(); k++)
				{
					long long next = getNextPos(pos, rules[j][k]);
					if (next != -1)
					{
						pos = next;
						break;
					}
				}
			}
			if(pos<minim)
			{
			    minPos=iter;
			    minim = pos;
			}
	    }
	    cout<<"least root pos is " << minPos<<endl;
	    long long nextMin=minPos;
	    for(long long iter = minPos-(root);iter<minPos+(root); iter++)
	    {
	        if(iter>=inputs[i]&&iter<inputs[i]+inputs[i+1])
	        {
    			long long pos = iter;
    			for (int j = 0; j < rules.size(); j++)
    			{
    				for (int k = 0; k < rules[j].size(); k++)
    				{
    					long long next = getNextPos(pos, rules[j][k]);
    					if (next != -1)
    					{
    						pos = next;
    						break;
    					}
    				}
    			}
    			if(pos<minim)
    			{
    			    nextMin=iter;
    			    minim = pos;
    			}
	        }
	    }
	    cout<<"least pos is " << nextMin<<endl;
	    outputs.push_back(minim);
	    cout<<endl;
	}
	minVal = outputs[0];
	for (int i = 0; i < outputs.size(); i++)
	{
		if(outputs[i] < minVal)
		{
			minVal = outputs[i];
		}
		//cout << outputs[i] << endl;
	}
	cout<<minVal<<endl;
}
