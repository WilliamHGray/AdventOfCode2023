#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;
const int padding = 9;

int getScore(string line)
{
	set<int> numbers;
	int start = line.find(':') + 1;
	for (int i = start; i < line.size(); i += 3)
	{
		if (line[i + 1] == '|')
		{
			i += 2;
		}
		numbers.insert(stoi(line.substr(i, i + 2)));
	}
	int totalNums = (line.size() - padding) / 3;
	int winners = totalNums - numbers.size();
	return winners;
}

int main() {
	ifstream FileName;
	FileName.open("AOC4.txt");
	int totalCount = 0;
	int totalScore = 0;
	vector<int> repeats = { 1 };
	string lineN;
	int lineNum = 0;
	while (getline(FileName, lineN)) 
	{
		int winners = (getScore(lineN));
		int score = pow(2, winners - 1);
		totalCount += score;
		cout << lineNum << endl;
		while (lineNum >= repeats.size())
		{
			repeats.push_back(1);
		}
		for (int i = 0; i < winners; i++)
		{
			if (lineNum == 15)
			{
				cout << " rep " << i << endl;
			}
			int numStored = repeats.size();
			cout << numStored << endl;
			int pos = lineNum + i + 1;
			cout << pos << endl;
			if (pos < numStored)
			{
				repeats[pos] += repeats[lineNum];
			}
			else
			{
				repeats.push_back(repeats[lineNum]+1);
			}
		}
		lineNum++;
	}
	while (lineNum > repeats.size())
	{
		repeats.push_back(1);
	}
	for (int i = 0; i < lineNum; i++)
	{
		//cout << "card " << i << " wins " << repeats[i] << endl;
		totalScore += repeats[i];
	}
	cout << totalCount << endl;
	cout << totalScore << endl;
}