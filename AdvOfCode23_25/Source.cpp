#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
#include <set>
using namespace std;

vector<int> addVectors(vector<int> first, vector<int> second)
{
	vector<int> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

void drawVector(vector<vector<int>> input)
{
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[0].size(); j++)
		{
			int out = input[i][j];
			if (out > 99)
			{
				cout << " " << out;
			}
			else if (out > 9)
			{
				cout << "  " << out;
			}
			else
			{
				cout << "   " << out;
			}
		}
		cout << endl;
	}
	cout << endl;
}

int findMinPath(int start, int end, int numSteps, vector<vector<int>> connections, vector<int> visited, vector<vector<int>>& edgeUsed,vector<vector<int>>&minPath,int currentMin)
{	
	int total = currentMin;
	if (numSteps >= total)
	{
		return numSteps;
	}
	if (connections[start][end] == 1)
	{
		edgeUsed[start][end]++;
		return numSteps + 1;
	}
	for (int i = 0; i < visited.size(); i++)
	{
		if (visited[i] == 0 && connections[start][i] == 1)
		{
			vector<int> tempVisited = visited;
			tempVisited[i] = 1;
			vector<vector<int>>tempUsed = minPath;
			tempUsed[start][i]++;
			int temp = findMinPath(i, end, numSteps + 1, connections, tempVisited, tempUsed,minPath,total);
			if (temp < total)
			{
				total = temp;
				edgeUsed = tempUsed;
			}
		}
	}
	return total;
	
}

vector<int> getMaxCoords(vector<vector<int>>input)
{
	int max = 0;
	int x=-1, y=-1;
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = i + 1; j < input.size(); j++)
		{
			int num = input[j][i];
			if (num > max)
			{
				max = num;
				x = i;
				y = j;
			}
		}
	}
	return { x,y };
}

int main() {
	ifstream FileName;
	FileName.open("AOC25.txt");
	int totalCount = 0;
	string lineN;
	vector<vector<string>>connections;
	vector<string> nodes;
	set<string> nodesUnique;
	int lineNum = 0;
	while (getline(FileName, lineN)) {
		int c = lineN.find(':');
		nodes.push_back(lineN.substr(0,c ));
		int pos = c + 2;
		vector<string> temp;
		int space = 0;
		while (space != -1)
		{
			space = lineN.find(' ', pos);
			string node = lineN.substr(pos, space - pos);
			temp.push_back(node);
			nodesUnique.insert(node);
			pos = space + 1;
		}
		connections.push_back(temp);
	}
	FileName.close();
	for (auto it = nodesUnique.begin(); it != nodesUnique.end(); ++it)
	{
		string node = *it;
		if (find(nodes.begin(), nodes.end(), node) == nodes.end())
		{
			nodes.push_back(node);
		}
	}
	vector<vector<int>> links(nodes.size(), vector<int>(nodes.size(), 0));
	for (int i = 0; i < connections.size(); i++)
	{
		for (int j = 0; j < links.size(); j++)
		{
			if (find(connections[i].begin(), connections[i].end(), nodes[j]) != connections[i].end())
			{
				links[i][j] = 1;
				links[j][i] = 1;
			}
		}
	}
	//drawVector(links);
	/*
	ofstream outFileName;
	outFileName.open("AOCOut.txt");
	for (int i = 0; i < links.size(); i++)
	{
		for (int j = 0; j < links.size(); j++)
		{
			outFileName << links[i][j] << " ";
		}
		outFileName << "\n";
	}
	*/
	//The below (commented out) code ran for the test input but then took too long to run for th real input. 
	//So exported my graph of links to a text file, imported it to matlab, and looked at the resulting graph. This gave me the nodes needed trivially.
	cout << "WRITE FINISH" << endl;
	/*598-536
	1409-794
	1132-247*/
	cout << nodes[597] << ", " << nodes[535] << endl;
	cout << nodes[1408] << ", " << nodes[793] << endl;
	cout << nodes[1131] << ", " << nodes[246] << endl;
	links[597][535] = 0;
	links[535][597] = 0;
	links[1408][793] = 0;
	links[793][1408] = 0;
	links[1131][246] = 0;
	links[246][1131] = 0;
	/*
	vector<int> visited(links.size(), 0);
	for (int iter = 0; iter < 3; iter++)
	{
		vector<vector<int>> edgeUsed(links.size(), vector<int>(links.size(), 0));
		
		int numNodes = links.size();
		for (int i = 0; i < 1; i++)
		{
			vector<vector<int>> minPath = edgeUsed;
			int start = rand() % numNodes;
			int end = rand() % numNodes;
			while (end == start)
			{
				end = rand() % numNodes;
			}
			findMinPath(start, end, 0, links, visited, edgeUsed,minPath,1000);
		}
		vector<vector<int>> lowerTriangle(numNodes, vector<int>(numNodes, 0));
		for (int i = 0; i < numNodes; i++)
		{
			for (int j = i + 1; j < numNodes; j++)
			{
				lowerTriangle[j][i] = edgeUsed[i][j] + edgeUsed[j][i];
			}
		}
		//drawVector(lowerTriangle);
		vector<int>remove = getMaxCoords(lowerTriangle);
		int x = remove[0], y = remove[1];
		cout << x << ", " << y << endl;
		cout << nodes[x] << ", " << nodes[y] << endl;
		links[x][y] = 0;
		links[y][x] = 0;
	}
	*/
	int startIndex = 0;
	stack<int> nextIndex;
	nextIndex.push(startIndex);
	set<int> visitedUnique;
	visitedUnique.insert(startIndex);
	while (nextIndex.size() > 0)
	{
		int index = nextIndex.top();
		nextIndex.pop();
		for (int i = 0; i < links.size(); i++)
		{
			if (links[index][i] && find(visitedUnique.begin(), visitedUnique.end(),i)==visitedUnique.end())
			{
				nextIndex.push(i);
				visitedUnique.insert(i);
				
			}
		}
	}
	cout << visitedUnique.size() * (nodes.size()-visitedUnique.size()) << endl;
}