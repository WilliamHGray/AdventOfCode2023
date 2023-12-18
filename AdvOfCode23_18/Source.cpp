#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#include <queue>

const vector<vector<int>> shifts = { {0, -1}, {1,0}, {0,1},{-1,0} };
const vector<char> directions = { 'U','R','D','L' };

void drawVector(vector<vector<char>> input)
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

vector<int> addVectors(vector<int> first, vector<int> second)
{
	vector<int> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

vector<long long> addVectors(vector<long long> first, vector<long long> second)
{
	vector<long long> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

bool inBounds(int coord, int vectorSize)
{
	if (coord >= 0 && coord < vectorSize)
	{
		return true;
	}
	return false;
}

int total(vector<vector<char>> input)
{
	int totalCount = 0;
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[0].size(); j++)
		{
			if (input[i][j] != ' ')
			{
				totalCount++;
			}
		}
	}
	return totalCount;
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

vector<vector<char>>fillOutside(vector<vector<char>>input)
{
	vector<vector<char>>output = input;
	output[0][0] = ' ';
	queue<vector<int>> coords;
	int xSize = input[0].size(), ySize = input.size();
	coords.push({ 0,0 });
	while (coords.size() > 0)
	{
		vector<int> coord = coords.front();
		coords.pop();
		for (int i = 0; i < 4; i++)
		{
			vector<int> next = addVectors(coord, shifts[i]);
			int x = next[0], y = next[1];
			if (inBounds(next, xSize, ySize) && output[y][x] == '.')
			{
				coords.push(next);
				output[y][x] = ' ';
			}
		}
	}
	return output;
}

vector<long long>scalarMult(int x, vector<int> y)
{
	vector<long long> temp;
	for (int i = 0; i < y.size(); i++)
	{
		temp.push_back(y[i] * x);
	}
	return temp;
}

int main() {
	ifstream FileName;
	FileName.open("AOC18.txt");
	int totalCount = 0;
	string lineN;
	vector<int> num;
	vector<char> dir;
	vector<vector<int>>coords;
	vector<vector<char>> grid;
	vector<string> hex;
	while (getline(FileName, lineN)) {
		dir.push_back(lineN[0]);
		int space = lineN.find(' ', 2);

		num.push_back(stoi(lineN.substr(2, space - 2)));
		hex.push_back(lineN.substr(space + 1, -1));
	}
	vector<int>current = { 0,0 };
	coords.push_back(current);
	for (int i = 0; i < dir.size(); i++)
	{
		int index = find(directions.begin(), directions.end(), dir[i]) - directions.begin();
		for (int j = 0; j < num[i]; j++)
		{
			current = addVectors(current, shifts[index]);
			coords.push_back(current);
		}
	}
	int maxX = 0, maxY = 0, minX = 0, minY = 0;
	for (int i = 0; i < coords.size(); i++)
	{
		int x = coords[i][0], y = coords[i][1];
		if (x < minX)
		{
			minX = x;
		}
		if (x > maxX)
		{
			maxX = x;
		}
		if (y < minY)
		{
			minY = y;
		}
		if (y > maxY)
		{
			maxY = y;
		}
	}
	cout << minX << " to " << maxX << endl;
	cout << minY << " to " << maxY << endl;
	grid.resize(maxY - minY + 1 + 2, vector<char>(maxX - minX + 1 + 2, '.'));
	for (int i = 0; i < coords.size(); i++)
	{
		int x = coords[i][0]-minX+1, y = coords[i][1]-minY+1;
		grid[y][x] = '#';
	}
	vector<vector<char>> output = fillOutside(grid);
	cout << "Finding sum" << endl;
	totalCount = total(output);
	//drawVector(grid);
	cout << totalCount << endl;







	//PART 2
	long long total2 = 0;
	vector<vector<long long>> vertexes;
	vertexes.push_back({ 0,0 });
	for (int i = 0; i < hex.size(); i++)
	{
		string num = hex[i];
		int dir = num[num.size() - 2]-'0';
		int hexNum = stoi(num.substr(2, num.size() - 4),nullptr, 16);
		vertexes.push_back(addVectors(vertexes[i], scalarMult(hexNum, shifts[(dir + 1) % 4])));
	}
	for (int i = 0; i < hex.size(); i++)
	{
		long long x1 = vertexes[i][0], y1 = vertexes[i][1];
		long long x2, y2;
		if (i < hex.size() - 1)
		{
			x2 = vertexes[i + 1][0];
			y2 = vertexes[i + 1][1];
		}
		else
		{
			x2 = vertexes[i + 1][0];
			y2 = vertexes[i + 1][1];
		}
		total2 += (x1 * y2 - y1 * x2)+abs(x1-x2+y1-y2);  //calculation obtained from https://www.mathopenref.com/coordpolygonarea.html
														// then just add the perimeter
	}
	cout << total2 / 2 +1; //off by one error? seen in both test and real. Bodge by adding plus 1 to end
}