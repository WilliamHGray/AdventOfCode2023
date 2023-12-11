#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const int ageMod = 999999; //Note: this is number of times bigger -1; For part 1, equals 1

void drawMap(vector<string> map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			cout << map[i][j];
		}
		cout << endl;
	}
}

int absDiff(vector<int> posA, vector<int>posB)
{
	int xDiff = abs(posA[0] - posB[0]);
	int yDiff = abs(posA[1] - posB[1]);
	return xDiff + yDiff;
}

int64_t extraDiff(vector<int> posA, vector<int>posB,vector<int> vert, vector<int>horiz)
{
	int64_t total = 0;
	int x1 = posA[0], x2 = posB[0], y1 = posA[1], y2 = posB[1];
	if (x1 > x2)
	{
		int temp = x1;
		x1 = x2;
		x2 = temp;
	}
	if (y1 > y2)
	{
		int temp = y1;
		y1 = y2;
		y2 = temp;
	}
	for (int i = 0; i < vert.size(); i++)
	{
		if (vert[i] > y1 && vert[i] < y2)
		{
			total += ageMod;
		}
	}
	for (int i = 0; i < horiz.size(); i++)
	{
		if (horiz[i] > x1 && horiz[i] < x2)
		{
			total += ageMod;
		}
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC11.txt");
	int64_t totalCount = 0;
	vector<string> space;
	string lineN;
	vector<vector<int>> galaxies;
	vector<int>vertEmpty, horizEmpty;
	int lineNum = 0;
	while (getline(FileName, lineN)) {
		space.push_back(lineN);
		bool empty = true;
		for (int i = 0; i < lineN.size(); i++)
		{
			if (lineN[i] == '#')
			{
				empty = false;
				break;
			}
		}
		if (empty)
		{
			vertEmpty.push_back(lineNum);
		}
		lineNum++;
	}
	for (int i = 0; i < space[0].size(); i++)
	{
		bool empty = true;
		for (int j = 0; j < space.size(); j++)
		{
			char curr = space[j][i];
			if (curr == '#')
			{
				empty = false;
				break;
			}
		}
		if (empty)
		{
			horizEmpty.push_back(i);
		}
	}

	for (int y = 0; y < space.size(); y++)
	{
		for (int x = 0; x < space[0].size(); x++)
		{
			if (space[y][x] == '#')
			{
				galaxies.push_back({ x,y });
			}
		}
	}

	for (int i = 0; i < galaxies.size(); i++)
	{
		for (int j = i + 1; j < galaxies.size(); j++)
		{
			int64_t baseDiff = absDiff(galaxies[i], galaxies[j]);
			int64_t totalDiff = baseDiff + extraDiff(galaxies[i], galaxies[j],vertEmpty,horizEmpty);
			totalCount += totalDiff;
		}
	}

	cout << totalCount << endl;
}