#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <queue>
using namespace std;
const vector<vector<int>> shifts = { {0, -1}, {1,0}, {0,1},{-1,0} };

vector<int> addVectors(vector<int> first, vector<int> second)
{
	vector<int> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

void drawVector(vector<string> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[0].size(); j++)
		{
			cout << input[i][j];
		}
		cout << endl;
	}
	cout << endl;
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
		space = line.find(' ', pos);
		temp.push_back(stoull(line.substr(pos, -1)));
		pos = space + 1;
	}
	return temp;
}

queue<vector<int>> setToQueue(set<vector<int>> input)
{
	queue<vector<int>>temp;
	set<vector<int>>::iterator it;
	for (it = input.begin(); it != input.end(); ++it)
	{
		temp.push(*it);
	}
	return temp;
}

int sumGrid(vector<string> grid, char toCount)
{
	int temp = 0;
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			if (grid[i][j] == toCount)
			{
				temp++;
			}
		}
	}
	return temp;
}

vector<string> makeBigGrid(vector<string>grid, int scaleFactor)
{
	vector<string>bigGrid;
	int numIters = 2 * scaleFactor + 1;
	int ySize = grid.size();
	for (int i = 0; i < numIters; i++)
	{
		for (int j = 0; j < grid.size(); j++)
		{
			bigGrid.push_back(grid[j]);
			for (int k = 1; k < numIters; k++)
			{
				bigGrid[i* ySize+j] += grid[j];
			}
		}
	}
	return bigGrid;
}

long long polynomial(int in, vector<int>polynomialCoeffs)
{
	//implementation of a Lagrange Interpolating Polynomial
	long long x = (long long)in;
	long long total = 0;
	for (int i = 0; i < polynomialCoeffs.size(); i++)
	{
		long long temp = polynomialCoeffs[i];
		for (int j = 0; j < polynomialCoeffs.size(); j++)
		{
			if (j != i)
			{
				temp *= (long long)(x - j - 1) / (i - j);
			}
		}
		total += temp;
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC21.txt");
	int totalCount = 0;
	string lineN;
	vector<string> grid;
	queue<vector<int>> positions;
	set<vector<int>> nextPositions;
	vector<int>nums;
	int lineNum = 0;
	while (getline(FileName, lineN)) {
		grid.push_back(lineN);
		int s = lineN.find('S');
		if (s != -1)
		{
			positions.push({ s,lineNum });
			grid[lineNum][s] = '.';
		}
		lineNum++;
	}
	int totalSteps = 64;
	int ySize = grid.size();
	int xSize = grid[0].size();

	vector<int> startPoint = positions.front();
	vector<string> startGrid = grid;

	for (int i = 0; i < totalSteps; i++)
	{
		while (positions.size() > 0)
		{
			vector<int> currPos = positions.front();
			positions.pop();
			int x = currPos[0], y = currPos[1];
			grid[y][x] = '.';
			for (int j = 0; j < 4; j++)
			{
				vector<int> nextPos = addVectors(currPos, shifts[j]);
				if (inBounds(nextPos, xSize, ySize) && grid[nextPos[1]][nextPos[0]] != '#')
				{
					nextPositions.insert(nextPos);
					grid[nextPos[1]][nextPos[0]] = 'O';
				}
			}
		}
		positions = setToQueue(nextPositions);
		nextPositions.clear();
	}


	totalCount = sumGrid(grid, 'O');
	cout << "PART 1: " << totalCount << endl;


	positions = queue<vector<int>>();
	positions.push(startPoint);
	vector<int>polynomialCoeffs;

	totalSteps = xSize * 3;
	for (int i = 0; i < totalSteps; i++)
	{
		while (positions.size() > 0)
		{
			vector<int> currPos = positions.front();
			positions.pop();
			for (int j = 0; j < 4; j++)
			{
				vector<int> nextPos = addVectors(currPos, shifts[j]);
				int x = nextPos[0] % xSize, y = nextPos[1] % ySize;
				if (x < 0) { x += xSize; }
				if (y < 0) { y += ySize; }
				if (grid[y][x] != '#')
				{
					nextPositions.insert(nextPos);
				}
			}
		}
		positions = setToQueue(nextPositions);
		nextPositions.clear();

		int iter = i - (xSize / 2 - 1);
		if (iter % xSize == 0)
		{
			polynomialCoeffs.push_back(positions.size());
		}
	}
	
	int TotalIterations = 26501365;
	int xToFind = (TotalIterations - (xSize/2)) / xSize;

	long long total = polynomial(xToFind+1, polynomialCoeffs); //iterations start from 0, but polynomial starts from 1. The +1 here gets around that.
	cout << "PART 2: " << total << endl;
}