#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include<queue>
const bool logging = false;

vector<int> addVectors(vector<int> first, vector<int> second)
{
	vector<int> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}


vector<int> runPulses(queue<string> locations, queue<int> pulseTypes, vector<string> modules, vector<int> types,vector<vector<string>>links,vector<string>flipFlops,vector<bool>&flipFlopStatus,vector<string> conjunctions, vector<vector<string>>conjunctionInputs, vector<vector<int>>&conjunctionPrevs,queue<string>prev, int iterNum=0)
{
	vector<int> total = { 1,0,0};
	int iter = 0;
	vector<int> numRxPushes = { 0,0 };
	while (locations.size() > 0)
	{
		iter++;
		string current = locations.front();
		locations.pop();
		int pulseType = pulseTypes.front();
		pulseTypes.pop();
		string previous = prev.front();
		prev.pop();
		int index = find(modules.begin(), modules.end(), current) - modules.begin();

		if (current == "rx")
		{
			numRxPushes[pulseType]++;
		}


		if(index>=0&&index< modules.size())
		{
			int type = types[index];
			if (type == 0)
			{
				for (int j = 0; j < links[index].size(); j++)
				{
					if (logging) { cout << current << " -low-> " << links[index][j] << endl; }
					total[0]++;
					locations.push(links[index][j]);
					pulseTypes.push(0);
					prev.push(current);
					int newIndex = find(modules.begin(), modules.end(), links[index][j]) - modules.begin();
				}
			}
			if (type == 1)
			{
				int fIndex = find(flipFlops.begin(), flipFlops.end(), current) - flipFlops.begin();
				if (pulseType == 0)
				{
					bool newStatus = !flipFlopStatus[fIndex];
					flipFlopStatus[fIndex] = newStatus;
					for (int j = 0; j < links[index].size(); j++)
					{
						total[newStatus]++;
						locations.push(links[index][j]);
						pulseTypes.push(newStatus);
						prev.push(current);
						if (logging) {
							if (newStatus)
							{
								cout << current << " -high-> " << links[index][j] << endl;
							}
							else
							{
								cout << current << " -low-> " << links[index][j] << endl;
							}
						}
						int newIndex = find(modules.begin(), modules.end(), links[index][j]) - modules.begin();
					}
				}
			}
			if (type == 2)
			{
				int cIndex = find(conjunctions.begin(), conjunctions.end(), current) - conjunctions.begin();
				conjunctionPrevs[cIndex][find(conjunctionInputs[cIndex].begin(), conjunctionInputs[cIndex].end(), previous) - conjunctionInputs[cIndex].begin()] = pulseType;
				int conjTotal = 0;
				for (int i = 0; i < conjunctionPrevs[cIndex].size(); i++)
				{
					conjTotal += conjunctionPrevs[cIndex][i];
				}
				bool sendPulseType = 1;
				if (conjTotal == conjunctionPrevs[cIndex].size())
				{
					sendPulseType = 0;
				}
				else if(iterNum>0 && /*current == "mp"  || current == "qt"  || current == "qb"||*/ current == "ng"  )
				{
					cout << iterNum << ": " << current << " high at " << iter << endl;
					//This line is used to find the iterations where each of the modules is high. This loops, so we know that each is high at all iterations following the rule a+bx, for some a,b and all x. Then we just need to solve the chinese remainder theorem with the 4 diophantine equations obtained.
				}
				for (int j = 0; j < links[index].size(); j++)
				{
					total[sendPulseType]++;
					locations.push(links[index][j]);
					pulseTypes.push(sendPulseType);
					prev.push(current);
					if (logging) {
						if (sendPulseType == 1)
						{
							cout << current << " -high-> " << links[index][j] << endl;
						}
						else
						{
							cout << current << " -low-> " << links[index][j] << endl;
						}
					}
				}
			}
		}
	}
	vector<int> winner = { 1,0 };
	if (numRxPushes[0] != 0 )
	{
		cout << numRxPushes[0]<<", "<< numRxPushes[1] << endl;
	}
	if (numRxPushes == winner)
	{
		total[2] = 1;
	}
	return total;
}



int main() {
	ifstream FileName;
	FileName.open("AOC20Copy.txt");
	int totalCount = 0;
	string lineN;
	vector<string> modules;
	vector<int> types;
	vector<vector<string>>links;
	vector<string> flipFlops;
	vector<bool> flipFlopStatus;
	vector<string> conjunctions;
	vector<vector<string>>conjunctionInputs;
	vector<vector<int>>conjunctionPrevs;

	while (getline(FileName, lineN)) {
		char type = lineN[0];
		int pos = lineN.find('>')+2;
		if (type == 'b')
		{
			modules.push_back("broadcaster");
			types.push_back(0);
			
		}
		else if (type == '%')
		{
			int space = lineN.find(' ');
			string name = lineN.substr(1, space - 1);
			modules.push_back(name);
			types.push_back(1);
			flipFlops.push_back(name);
			flipFlopStatus.push_back(false);
		}
		else if (type == '&')
		{
			int space = lineN.find(' ');
			string name = lineN.substr(1, space - 1);
			modules.push_back(name);
			types.push_back(2);
			conjunctions.push_back(name);
		}
		int comma = 0;
		vector<string>temp;
		while (comma != -1)
		{
			comma = lineN.find(',', pos);
			temp.push_back(lineN.substr(pos, comma - pos));
			pos = comma + 2;
		}
		links.push_back(temp);
	}
	for (int i = 0; i < conjunctions.size(); i++)
	{
		vector<string> temp;
		vector<int> temp2;
		for (int j = 0; j < modules.size(); j++)
		{	
			if (find(links[j].begin(), links[j].end(), conjunctions[i]) != links[j].end())
			{
				temp.push_back(modules[j]);
				temp2.push_back(0);
			}
			
		}
		conjunctionInputs.push_back(temp);
		conjunctionPrevs.push_back(temp2);
	}

	string start = "broadcaster";
	int pulse = 0;
	string button = "button";
	vector<int> total = { 0,0 };
	queue<string>locations;
	queue<int>pulses;
	queue<string>prev;
	locations.push(start);
	pulses.push(pulse);
	prev.push(button);

	

	for (int i = 0; i < 1000; i++)
	{
		if (logging) {
			cout << "button -low-> broadcaster" << endl;
		}
		vector<int> currentRun = runPulses(locations, pulses, modules, types, links, flipFlops, flipFlopStatus, conjunctions, conjunctionInputs, conjunctionPrevs, prev);
		
		if (logging) {
			cout << currentRun[0] << ", " << currentRun[1] << endl;
		}
		total = addVectors(total, currentRun);
	}
	
	totalCount = total[0] * total[1];
	cout << "PART 1: " << totalCount << endl;
	int iter = 0;
	while (true)
	{
		iter++;
		vector<int> currentRun = runPulses(locations, pulses, modules, types, links, flipFlops, flipFlopStatus, conjunctions, conjunctionInputs, conjunctionPrevs, prev,iter);
		if (currentRun[2] == 1)
		{
			cout << "PART 2 SOLVED AT ITERATION " << iter+ 1 << endl;
			break;
		}
	}
}