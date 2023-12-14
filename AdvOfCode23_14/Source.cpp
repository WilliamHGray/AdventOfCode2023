#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include <chrono>

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

bool inBounds(int coord, int vectorSize)
{
	if (coord >= 0 && coord < vectorSize)
	{
		return true;
	}
	return false;
}

vector<vector<int>> findRocks(vector<string>grid)
{
	vector<vector<int>> temp;
	for (int y = 0; y < grid.size();y++)
	{
		for (int x = 0; x < grid[0].size(); x++)
		{
			if (grid[y][x] == 'O')
			{
				temp.push_back({ x, y });
			}
		}
	}
	return temp;
}

void shiftNorth(vector<string>&grid, int startX, int startY)
{
	int y = startY;
	while (inBounds(y - 1, grid.size()) && grid[y - 1][startX] == '.')
	{
		y--;
	}
	grid[startY][startX] = '.';
	grid[y][startX] = 'O';
}

void shiftSouth(vector<string>& grid, int startX, int startY)
{
	int y = startY;
	while (inBounds(y + 1, grid.size()) && grid[y + 1][startX] == '.')
	{
		y++;
	}
	grid[startY][startX] = '.';
	grid[y][startX] = 'O';
}

void shiftEast(vector<string>& grid, int startX, int startY)
{
	int x = startX;
	while (inBounds(x + 1, grid[0].size()) && grid[startY][x + 1] == '.')
	{
		x++;
	}
	grid[startY][startX] = '.';
	grid[startY][x] = 'O';
}

void shiftWest(vector<string>&grid, int startX, int startY)
{
	int x = startX;
	while (inBounds(x - 1, grid[0].size()) && grid[startY][x - 1] == '.')
	{
		x--;
	}
	grid[startY][startX] = '.';
	grid[startY][x] = 'O';
}

int findTotal(vector<string> grid,int vertSize)
{
	vector<vector<int>>coords = findRocks(grid);
	int runningTotal = 0;
	for (int i = 0; i < coords.size(); i++)
	{
		runningTotal += (vertSize - coords[i][1]);
	}
	return runningTotal;
}

void shift(vector<string>&grid, vector<vector<int>>rocks, char dir)
{
	if (dir == 'N')
	{
		for (int i = 0; i < rocks.size(); i++)
		{
			shiftNorth(grid, rocks[i][0], rocks[i][1]);
		}
	}
	else if (dir == 'S')
	{
		for (int i = rocks.size() - 1; i >= 0; i--)
		{
			shiftSouth(grid, rocks[i][0], rocks[i][1]);
		}
	}
	else if (dir == 'E')
	{
		for (int i = rocks.size() - 1; i >= 0; i--)
		{
			shiftEast(grid, rocks[i][0], rocks[i][1]);
		}
	}
	else if (dir == 'W')
	{
		for (int i = 0; i < rocks.size(); i++)
		{
			shiftWest(grid, rocks[i][0], rocks[i][1]);
		}
	}
}

int main() {
	ifstream FileName;
	FileName.open("AOC14.txt");
	int totalCount = 0;
	string lineN;
	vector<string>grid;
	while (getline(FileName, lineN)) {
		grid.push_back(lineN);
	}
	vector<char> cycle = { 'N','W','S','E' };
	vector<vector<int>>rocks;
	vector<vector<string>>prevGrids;
	int TotalIters = 1000000000;
	auto start = chrono::high_resolution_clock::now();
	int startLoop, endLoop;
	bool looped = false;
	for (int i = 0; i < TotalIters; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rocks = findRocks(grid);
			shift(grid, rocks, cycle[j]);
			if (i == 0&&j==0)
			{
				totalCount += findTotal(grid, grid.size());
				cout << "Part 1: " << totalCount << endl;
			}
		}
		prevGrids.push_back(grid);
		int prevLoop = find(prevGrids.begin(), prevGrids.end(), grid)-prevGrids.begin();
		if (prevLoop != i)
		{
			if (looped)
			{
				cout << prevLoop<<" loops to " << i << endl;
				int skip = (TotalIters - prevLoop-1)/(i - prevLoop);
				startLoop = prevLoop + (skip * (i - prevLoop))+1;
				cout << "Start next loop at " << startLoop << endl;
				break;
			}
			else
			{
				looped = true;
			}
		}
		else {
			looped = false;
		}
	}

	for (int i = startLoop; i < TotalIters; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			rocks = findRocks(grid);
			shift(grid, rocks, cycle[j]);
		}
		int part2Count = findTotal(grid, grid.size());
	}
	int part2Count = findTotal(grid, grid.size());
	cout << "Part 2: " << part2Count << endl;
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << duration.count() << endl;
}