#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include <chrono>
#include <queue>

const vector<char> dirs = { 'U', 'R', 'D', 'L' };
const vector<vector<int>> shifts = { {0, -1}, {1,0}, {0,1},{-1,0} };

void drawVector(vector<vector<int>> input)
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

vector<int> addVectors(vector<int> first, vector<int> second)
{
	vector<int> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

vector<vector<int>> checkMove(vector<int> move, vector<string> grid)
{
	vector<vector<int>> temp;
	int x = move[0], y = move[1];
	int dir = move[2];
	if (grid[y][x] == '.')
	{
		temp.push_back(addVectors({ x,y }, shifts[dir]));
		temp[0].push_back(dir);
	}
	else if (grid[y][x] == '|')
	{
		if (dir == 0 || dir == 2)
		{
			temp.push_back(addVectors({ x,y }, shifts[dir]));
			temp[0].push_back(dir);
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				temp.push_back(addVectors({ x,y }, shifts[2*i]));
				temp[i].push_back(2*i);
			}
		}
	}
	else if (grid[y][x] == '-')
	{
		if (dir == 1 || dir == 3)
		{
			temp.push_back(addVectors({ x,y }, shifts[dir]));
			temp[0].push_back(dir);
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				temp.push_back(addVectors({ x,y }, shifts[1+(2 * i)]));
				temp[i].push_back(1+(2 * i));
			}
		}
	}
	else if (grid[y][x] == '/')
	{
		int prevTwo = 2 * (int)(dir / 2);
		int rem = dir % 2;
		int nextDir = prevTwo + (1 - rem);
		temp.push_back(addVectors({ x,y }, shifts[nextDir]));
		temp[0].push_back(nextDir);
	}
	else if (grid[y][x] == '\\')
	{
		int nextDir = 3 - dir;
		temp.push_back(addVectors({ x,y }, shifts[nextDir]));
		temp[0].push_back(nextDir);
	}
	return temp;
}


int runSimulation(vector<int> startInstruction,vector<string>grid)
{
	queue<vector<int>> instructions; //x coord, y coord, direction
	instructions.push(startInstruction);
	vector<vector<int>>energised;
	vector<vector<int>> pastMoves;
	energised.resize(grid.size(), vector<int>(grid[0].size(), 0));
	while (instructions.size() != 0)
	{
		vector<int> instruction = instructions.front();
		pastMoves.push_back(instruction);
		energised[instruction[1]][instruction[0]] = 1;


		vector<vector<int>> temp = checkMove(instruction, grid);
		for (int i = 0; i < temp.size(); i++)
		{
			if (inBounds(temp[i][0], grid[0].size()) && inBounds(temp[i][1], grid.size()))
			{
				if (find(pastMoves.begin(), pastMoves.end(), temp[i]) == pastMoves.end())
				{
					instructions.push(temp[i]);
				}
			}
		}
		instructions.pop();
	}
	int total = 0;
	for (int i = 0; i < energised.size(); i++)
	{
		for (int j = 0; j < energised[0].size(); j++)
		{
			total += energised[i][j];
		}
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC16.txt");
	int totalCount = 0;
	string lineN;
	vector<string> grid;
	while (getline(FileName, lineN)) {
		grid.push_back(lineN);
	}
	auto start = chrono::high_resolution_clock::now();
	totalCount = runSimulation({ 0,0,1 }, grid);
	std::cout << "Part 1: " << totalCount << endl;

	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::milliseconds > (stop - start);
	cout <<"Part 1 took "<< duration.count() <<" milliseconds" << endl;
	cout << endl;
	start = chrono::high_resolution_clock::now();
	int part2Total = 0;
	int xSize = grid[0].size();
	int ySize = grid.size();
	cout << "Size of grid = " << xSize << ", " << ySize << endl;
	cout << "Checking Rows" << endl;
	for (int i = 0; i < ySize; i++)
	{
		int temp1 = runSimulation({ 0,i,1 }, grid);
		int temp2 = runSimulation({ xSize-1,i,3 }, grid);
		if (temp1 > part2Total)
		{
			part2Total = temp1;
		}
		if (temp2 > part2Total)
		{
			part2Total = temp2;
		}
	}
	cout << "Checking Columns" << endl;
	for (int i = 0; i < xSize; i++)
	{
		int temp1 = runSimulation({ i,0,2 }, grid);
		int temp2 = runSimulation({ i,ySize-1,0 }, grid);
		if (temp1 > part2Total)
		{
			part2Total = temp1;
		}
		if (temp2 > part2Total)
		{
			part2Total = temp2;
		}
	}

	cout << "Part 2: " << part2Total << endl;
	stop = chrono::high_resolution_clock::now();
	duration = chrono::duration_cast<chrono::milliseconds> (stop - start);
	cout << "Part 2 took " << duration.count() << " milliseconds" << endl;
}