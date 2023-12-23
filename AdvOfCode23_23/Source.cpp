#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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

bool inBounds(vector<int> coords, int vectorXSize, int vectorYSize)
{
	int x = coords[0], y = coords[1];
	if (x >= 0 && x < vectorXSize && y >= 0 && y < vectorYSize)
	{
		return true;
	}
	return false;
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

void drawVector(vector<vector<int>> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[0].size(); j++)
		{
			int out = input[i][j];
			if (out > 9)
			{
				cout << " " << out;
			}
			else
			{
				cout << "  " << out;
			}
		}
		cout << endl;
	}
	cout << endl;
}

int makeMove(vector<int> current, vector<int> end, int numSteps, vector<string>grid)
{
	int total = 0;
	for (int i = 0; i < 4; i++)
	{
		vector<int> next = addVectors(current, shifts[i]);
		int x = next[0], y = next[1];
		if (inBounds(next, grid[0].size(), grid.size()))
		{
			char nextChar = grid[y][x];
			if (next == end)
			{
				return numSteps + 1;			
			}
			if (nextChar == '.')
			{
				vector<string> tempGrid = grid;
				tempGrid[y][x] = 'O';

				int temp = makeMove(next, end, numSteps + 1, tempGrid);
				if (temp > total)
				{
					total = temp;
				}
			}
			else if (nextChar == '>')
			{
				vector<string> tempGrid = grid;
				tempGrid[y][x] = 'O';
				next = addVectors(next, shifts[1]);
				if (next != current)
				{
					tempGrid[next[1]][next[0]] = 'O';
					int temp = makeMove(next, end, numSteps + 2, tempGrid);
					if (temp > total)
					{
						total = temp;
					}
				}	
			}
			else if (nextChar == 'v')
			{
				vector<string> tempGrid = grid;
				tempGrid[y][x] = 'O';
				next = addVectors(next, shifts[2]);
				if (next != current)
				{
					tempGrid[next[1]][next[0]] = 'O';
					int temp = makeMove(next, end, numSteps + 2, tempGrid);
					if (temp > total)
					{
						total = temp;
					}
				}
			}
		}
	}
	return total;
}

void part2Path(vector<int>current, vector<vector<int>>nodes, int numSteps, vector<string>grid, vector<vector<int>> &edges, vector<vector<bool>> &connection,vector<int> start)
{
	for (int i = 0; i < 4; i++)
	{
		vector<int> next = addVectors(current, shifts[i]);
		int x = next[0], y = next[1];
		if (inBounds(next, grid[0].size(), grid.size()))
		{
			char nextChar = grid[y][x];
			if (find(nodes.begin(), nodes.end(), next) != nodes.end() && next!=start)
			{
				int indexA = find(nodes.begin(), nodes.end(), next) - nodes.begin();
				int indexB = find(nodes.begin(), nodes.end(), start) - nodes.begin();
				connection[indexA][indexB] = true;
				edges[indexA][indexB] = numSteps+1;
				return;
			}
			if (nextChar !='#' && nextChar !='O')
			{
				vector<string> tempGrid = grid;
				tempGrid[y][x] = 'O';

				part2Path(next, nodes, numSteps + 1, tempGrid, edges, connection, start);
			}
		}
	}
}

vector<vector<int>> getNodes(vector<string> grid,vector<int>start,vector<int> end)
{
	vector<vector<int>> nodes;
	nodes.push_back(start);
	for (int i = 1; i < grid.size() - 1; i++)
	{
		for (int j = 1; j < grid[0].size() - 1; j++)
		{
			int adj = 0;
			if (grid[i][j] != '#')
			{
				for (int k = 0; k < 4; k++)
				{
					vector<int> temp = addVectors({ j,i }, shifts[k]);
					int x = temp[0], y = temp[1];
					if (grid[y][x] != '#')
					{
						adj++;
					}
				}
				if (adj > 2)
				{
					nodes.push_back({ j,i });
				}
			}
		}
	}
	nodes.push_back(end);
	return nodes;
}

int getPathFromNodes(int index, int steps, vector<vector<int>> edges, vector<vector<bool>>connection,vector<bool>visited)
{
	int total = 0;
	visited[index] = true;
	for (int i = 0; i < edges.size(); i++)
	{
		if (connection[index][i]==true&&!visited[i])
		{
			int newTotal = steps + edges[index][i];
			if (i == connection.size() - 1)
			{
				if (newTotal > total)
				{
					total = newTotal;
				}
			}
			else
			{
				newTotal = getPathFromNodes(i, newTotal, edges, connection, visited);
				if (newTotal > total)
				{
					total = newTotal;
				}
			}
		}
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC23.txt");
	int totalCount = 0;
	string lineN;
	vector<string> grid;
	int lineNum = 0;
	while (getline(FileName, lineN)) {
		grid.push_back(lineN);
	}
	vector<int> start = { 1,0 };
	vector<int> end = { (int)grid[0].size() - 2, (int)grid.size() - 1 };
	totalCount = makeMove(start, end,0, grid);
	cout << totalCount << endl;
	vector<vector<int>> nodes = getNodes(grid,start,end);
	vector<vector<int>> edges(nodes.size(), vector<int>(nodes.size(), 0));
	vector<vector<bool>> connection(nodes.size(), vector<bool>(nodes.size(), false));
	vector<bool> visited(nodes.size(), false);
	cout << "GOT NODES" << endl;
	for (int i = 0; i < nodes.size(); i++)
	{
		vector<string> tempGrid = grid;
		tempGrid[nodes[i][1]][nodes[i][0]] = 'O';
		part2Path(nodes[i], nodes, 0, tempGrid, edges, connection, nodes[i]);
	}
	cout << "GOT EDGES" << endl;
	drawVector(edges);
	int totalPart2 = getPathFromNodes(0, 0, edges, connection,visited);
	cout << totalPart2 << endl;
}	