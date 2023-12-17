#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include <queue>
#include<algorithm>

const vector<vector<int>> shifts = { {0, -1}, {1,0}, {0,1},{-1,0} };

void drawVector(vector<vector<int>> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[0].size(); j++)
		{
			int num = input[i][j];
			if (num >= 0 && num < 10)
			{
				cout<< "   " << input[i][j];
			}
			else if(num>99)
			{
				cout << " " << input[i][j];
			}
			else
			{
				cout<< "  " << input[i][j];
			}
		}
		cout << endl;
	}
	cout << endl;
}

bool inBounds(int coord, int vectorSize)
{
	if (coord >= 0 && coord < vectorSize)
	{
		return true;
	}
	return false;
}

vector<int> addVectors(vector<int> first, vector<int> second)
{
	vector<int> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

bool inBounds(vector<int> coords, int vectorXSize, int vectorYSize)
{
	int x = coords[0], y = coords[1];
	if (x >= 0 && x < vectorXSize && y >= 0 && y < vectorYSize)
	{
		return true;
	}
	return false;
}

int main() {
	ifstream FileName;
	FileName.open("AOC17.txt");
	int totalCount = 0;
	string lineN;
	vector<vector<int>>grid;
	while (getline(FileName, lineN)) {
		vector<int>temp;
		for (int i = 0; i < lineN.size(); i++)
		{
			temp.push_back(lineN[i] - '0');
		}
		grid.push_back(temp);
	}
	int maxMove = 10;
	vector<vector<int>> positions;
	make_heap(positions.begin(), positions.end());
	const int xSize = grid[0].size();
	positions.push_back({ 0,0,0,1,0}); // x y current_heat direction_moved num_of_dir_moved
	push_heap(positions.begin(), positions.end());
	vector<vector<vector<vector<int>>>>heat;
	heat.resize(grid[0].size(), vector<vector<vector<int>>>(grid.size(), vector<vector<int>>(4, vector<int>(maxMove+1,-1))));
	int numIters = 0;
	while (positions.size() != 0)
	{
		numIters++;
		if (numIters % 10000 == 0)
		{
			cout << "On iteration " << numIters << endl;
		}
		if (numIters % 1000 == 0) //computationally expenses, do as little as possible
		{
			sort_heap(positions.begin(), positions.end());
		}
		vector<int> startPoint = positions[0];
		positions.erase(positions.begin());	
		int x = startPoint[1], y = startPoint[2],currHeat = startPoint[0],heading=startPoint[3],numHeading=startPoint[4];
		if (heat[x][y][heading][numHeading] != -1)
		{
			if (heat[x][y][heading][numHeading] > currHeat)
			{
				heat[x][y][heading][numHeading] = currHeat;
			}
			continue;
		}
		heat[x][y][heading][numHeading] = currHeat;
		for (int i = 0; i < 4; i++)
		{
			vector<int> currentPos = addVectors({x,y}, shifts[i]);
			if (!inBounds(currentPos, grid[0].size(), grid.size()))
			{
				continue;
			}
			int newX = currentPos[0], newY = currentPos[1];
			int newHeat = currHeat + grid[newY][newX];
			int newHeading;
			if (i != heading)
			{
				newHeading = 1;
			}
			else
			{
				newHeading = numHeading + 1;
			}
			bool reverse = false;
			if (i == ((heading + 2) % 4))
			{
				reverse = true;
			}
			/* PART 1
			if (newHeading <= maxMove && !reverse)
			{		
				positions.push_back({ newHeat, newX, newY,i,newHeading });
			}
			*/
			// PART 2
			if (newHeading <= maxMove && !reverse && (i == heading || numHeading >= 4 ||numHeading==0))
			{
				positions.push_back({ newHeat, newX, newY,i,newHeading });
			}
		}
	}
	int minHeat = 10000;
	vector<vector<int>> final = heat[heat.size() - 1][heat[0].size() - 1];
	for (int i = 0; i < final.size(); i++)
	{
		for (int j = 4; j < final[i].size(); j++) //j=0 for part 1, j=4 for part 2
		{
			if (final[i][j] != -1 && final[i][j] < minHeat)
			{
				minHeat = final[i][j];
			}
		}
	}
	cout << minHeat << endl;
}