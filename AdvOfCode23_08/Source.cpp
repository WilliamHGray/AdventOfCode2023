#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

long long gcd(long long a, long long b)
{
	while (b != 0)
	{
		long long temp = a % b;
		a = b;
		b = temp;
	}
	return a;
}

long long lcm(long long a, int b)
{
	long long second = static_cast<long long>(b);
	long long answer = (a * second / gcd(a, second));
	return answer;
}

int main() {
	ifstream FileName;
	FileName.open("AOC8.txt");
	int totalCount = 0;
	string lineN;
	vector<int> dirs;
	vector<vector<string>> map;
	vector<string> places;
	int pos = 0;
	bool init = false;
	while (getline(FileName, lineN)) {
		if (!init)
		{
			for (int i = 0; i < lineN.size(); i++)
			{
				if (lineN[i] == 'R')
				{
					dirs.push_back(1);
				}
				else
				{
					dirs.push_back(0);
				}
			}
			init = true;
		}
		else if (lineN.size() > 1)
		{
			vector<string> temp;
			places.push_back(lineN.substr(0, 3));
			temp.push_back(lineN.substr(7, 3));
			temp.push_back(lineN.substr(12, 3));
			map.push_back(temp);
		}
	}

	string start = "AAA";
	string end = "ZZZ";
	string current = start;
	while (current != end)
	{
		vector<string>::iterator iter = find(places.begin(), places.end(), current);
		int index = iter - places.begin();
		current = map[index][dirs[pos]];
		pos++;
		totalCount++;
		if (pos == dirs.size())
		{
			pos = 0;
		}
	}
	cout <<"Part 1: " << totalCount << endl;


	vector<string> ghostStart;
	for (int i = 0; i < places.size(); i++)
	{
		if (places[i][2] == 'A')
		{
			ghostStart.push_back(places[i]);
		}
	}
	vector<int> ghostCount;
	for (int i = 0; i < ghostStart.size();i++)
	{
		pos = 0;
		ghostCount.push_back(0);
		string current;
		current= ghostStart[i];
		while (current[2]!='Z')
		{
			vector<string>::iterator iter = find(places.begin(), places.end(), current);
			int index = iter - places.begin();
			current = map[index][dirs[pos]];
			pos++;
			ghostCount[i]++;
			if (pos == dirs.size())
			{
				pos = 0;
			}
		}
	}
	long long runningTotal = static_cast<long long>(ghostCount[0]);
	for (int i = 1;i<ghostCount.size();i++)
	{
		runningTotal = lcm(runningTotal, ghostCount[i]);
	}
	cout <<"Part 2: "<< runningTotal << endl;
}