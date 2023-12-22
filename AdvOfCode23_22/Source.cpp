#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;

bool isANumber(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	return false;
}

vector<int> numsFromString(string line, int pos = 0)
{
	vector<int> temp;
	int space = 0;
	while (space != -1)
	{
		space = line.find(',', pos);
		temp.push_back(stoi(line.substr(pos, space-pos)));
		pos = space + 1;
	}
	return temp;
}

vector<vector<int>> findAllBlocks(vector<vector<int>> positions)
{
	vector<vector<int>> temp;
	if (positions[0][0] != positions[1][0])
	{
		for (int i = positions[0][0]; i <= positions[1][0]; i++)
		{
			temp.push_back({ i,positions[0][1],positions[0][2] });
		}
	}
	else if (positions[0][1] != positions[1][1])
	{
		for (int i = positions[0][1]; i <= positions[1][1]; i++)
		{
			temp.push_back({positions[0][0],i,positions[0][2] });
		}
	}
	else
	{
		for (int i = positions[0][2]; i <= positions[1][2]; i++)
		{
			temp.push_back({positions[0][0],positions[0][1],i });
		}
	}
	return temp;
}

void fall(vector<vector<int>> &blocks)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		blocks[i][2]--;
	}
}

bool fallPossible(vector<vector<vector<int>>> blocks, int blockNum)
{
	
	for (int i = 0; i < blocks[blockNum].size(); i++)
	{
		vector<int> test = blocks[blockNum][i];
		test[2]--;
		if (blocks[blockNum][i][2] == 1)
		{
			return false;
		}
		
		for (int j = 0; j < blocks.size(); j++)
		{
			if (blockNum == j)
			{
				continue;
			}
			
			if (find(blocks[j].begin(), blocks[j].end(), test) != blocks[j].end())
			{
				return false;
			}
		}
	}

	return true;
}

void blocksOut(vector<vector<vector<int>>> blocks)
{
	for (int i = 0; i < blocks.size(); i++)
	{
		for (int j = 0; j < blocks[i].size(); j++)
		{
			for (int k = 0; k < 3; k++)
			{
				cout << blocks[i][j][k] << ", ";
			}
			cout << endl;
		}
		cout << endl;
	}
}

int sumVector(vector<bool> in)
{
	int temp = 0;
	for (int i = 0; i < in.size(); i++)
	{
		if (in[i])
		{
			temp++;
		}
	}
	return temp;
}

int main() {
	ifstream FileName;
	FileName.open("AOC22.txt");
	int totalCount = 0;
	int part2Total = 0;
	string lineN;
	vector<vector<vector<int>>> startEnd;
	while (getline(FileName, lineN)) {
		vector<vector<int>> temp;
		int midpoint = lineN.find('~');
		temp.push_back(numsFromString(lineN.substr(0, midpoint)));
		temp.push_back(numsFromString(lineN.substr(midpoint+1, -1)));
		startEnd.push_back(temp);
	}
	vector<vector<vector<int>>> blocks;
	for (int i = 0; i < startEnd.size(); i++)
	{
		blocks.push_back(findAllBlocks(startEnd[i]));
	}
	int fell = true;
	while (fell)
	{
		fell = false;
		for (int i = 0; i < blocks.size(); i++)
		{
			if (fallPossible(blocks, i))
			{
				fell = true;
				fall(blocks[i]);
			}
		}
	}
	cout << "FALL COMPLETE" << endl;
	for (int i = 0; i < blocks.size(); i++)
	{
		if (i % 100 == 0)
		{
			cout << "iter " << i << endl;
		}
		vector<vector<vector<int>>> temp = blocks;
		temp.erase(temp.begin()+i);
		set<int> fallen;
		int fell = true;
		
		while (fell)
		{
			fell = false;
			for (int j = 0; j < temp.size(); j++)
			{
				if (fallPossible(temp, j))
				{
					fell = true;
					fall(temp[j]);
					fallen.insert(j);
				}
			}		
			if (fallen.size() == temp.size())
			{
				break;
			}	
		}
		
		if (fallen.size() == 0)
		{
			totalCount++;
		}
		part2Total += fallen.size();
	}
	cout << totalCount << endl;
	cout << part2Total << endl;
}