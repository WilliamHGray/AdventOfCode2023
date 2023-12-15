#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

int hashString(string line)
{
	int total = 0;
	for (int i = 0; i < line.size(); i++)
	{
		char curr = line[i];
		total += curr;
		total *= 17;
		total = total % 256;
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC15.txt");
	int totalCount = 0;
	string lineN;
	vector<string>inputs;
	vector<vector<string>>boxes;
	boxes.resize(256);
	vector<vector<int>>lenses;
	lenses.resize(256);
	while (getline(FileName, lineN)) {
		int pos = 0;
		while (pos < lineN.size())
		{
			int comma = lineN.find(',', pos);
			if (comma != -1)
			{
				inputs.push_back(lineN.substr(pos, comma - pos));
				pos = comma + 1;
			}
			else
			{
				inputs.push_back(lineN.substr(pos, -1));
				pos = lineN.size();
			}
		}
	}
	for (int i = 0; i < inputs.size(); i++)
	{
		totalCount += hashString(inputs[i]);
		string line = inputs[i];
		if (line.find('=') != -1)
		{
			string part2Label = line.substr(0, line.size() - 2);
			int hashP2 = hashString(part2Label);
			int focalLength = line[line.size() - 1] - '0';
			vector<string>::iterator currentPos = find(boxes[hashP2].begin(),boxes[hashP2].end(),part2Label);
			if (currentPos != boxes[hashP2].end())
			{
				int index = currentPos - boxes[hashP2].begin();
				boxes[hashP2][index] = part2Label;
				lenses[hashP2][index] = focalLength;
			}
			else
			{
				boxes[hashP2].push_back(part2Label);
				lenses[hashP2].push_back(focalLength);
			}
		}
		else
		{
			string part2Label = line.substr(0, line.size() - 1);
			int hashP2 = hashString(part2Label);
			vector<string>::iterator currentPos = find(boxes[hashP2].begin(), boxes[hashP2].end(), part2Label);
			if (currentPos != boxes[hashP2].end())
			{
				int index = currentPos - boxes[hashP2].begin();
				for (int i = index + 1; i < boxes[hashP2].size(); i++)
				{
					boxes[hashP2][i - 1] = boxes[hashP2][i];
					lenses[hashP2][i - 1] = lenses[hashP2][i];
				}
				boxes[hashP2].pop_back();
				lenses[hashP2].pop_back();
			}
		}
	}

	int totalPart2 = 0;
	for (int i = 0; i < boxes.size(); i++)
	{
		for (int j = 0; j < boxes[i].size(); j++)
		{
			totalPart2 += (i + 1) * (j + 1) * lenses[i][j];
		}
	}
	cout << totalCount << endl;
	cout << totalPart2 << endl;
}