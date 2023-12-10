#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <chrono>
using namespace std;
const vector<char> lefts = { '-', 'J', '7','A'};
const vector<char> ups = { '|', 'J', 'L','A' };
const vector<char> rights = { '-','L','F','A' };
const vector<char> downs = { '|','7','F','A' };

bool checkBoundary(int pos, int mapSize)
{
	if (pos < 0||pos>=mapSize)
	{
		return false;
	}
	return true;
}

void replaceS(vector<int> sPos, vector<string> &map)
{
	bool up=false, down = false, left = false, right = false;
	int x = sPos[0], y = sPos[1];
	int mapSize = map.size();
	int mapXSize = map[0].size();
	if (checkBoundary(x + 1, mapXSize) && find(lefts.begin(),lefts.end(),map[y][x + 1]) != lefts.end())
	{
		right = true;
	}
	if (checkBoundary(x - 1, mapXSize) && find(rights.begin(), rights.end(), map[y][x - 1]) != rights.end())
	{
		left = true;
	}
	if (checkBoundary(y - 1, mapSize) && find(downs.begin(), downs.end(), map[y-1][x]) != downs.end())
	{
		up = true;
	}
	if (checkBoundary(y + 1, mapSize) && find(ups.begin(), ups.end(), map[y+1][x]) != ups.end())
	{
		down = true;
	}
	
	char s;

	if (right)
	{
		if (down)
		{
			s = 'F';
		}
		else if (up)
		{
			s = 'L';
		}
		else
		{
			s = '-';
		}
	}
	else if (left)
	{
		if (down)
		{
			s = '7';
		}
		else if (up)
		{
			s = 'J';
		}
	}
	else
	{
		s = '|';
	}
	map[y][x] = s;
}

bool isNextTo(vector<int>currentPos, vector<vector<char>> map, char toSearch)
{
	int x = currentPos[0], y = currentPos[1];
	int mapYSize = map.size();
	int mapXSize = map[0].size();
	if (checkBoundary(x + 1, mapXSize) && map[y][x+1]==toSearch)
	{
		return true;
	}
	if (checkBoundary(x - 1, mapXSize) && map[y][x - 1] == toSearch)
	{
		return true;
	}
	if (checkBoundary(y - 1, mapYSize) && map[y-1][x] == toSearch)
	{
		return true;
	}
	if (checkBoundary(y + 1, mapYSize) && map[y+1][x] == toSearch)
	{
		return true;
	}
	return false;
}

string moveNext(vector<int>& currentPos, vector<string>map, string prevMove)
{
	char current = map[currentPos[1]][currentPos[0]];
	int x = currentPos[0], y = currentPos[1];
	//cout << x << ", " << y << ", " << prevMove << ", " << current << endl;
	bool up = false, down = false, left = false, right = false;
	if (current == 'F')
	{
		down = true;
		right = true;
	}
	else if (current == 'J')
	{
		up = true;
		left = true;
	}
	else if (current == 'L')
	{
		up = true;
		right = true;
	}
	else if (current == '7')
	{
		down = true;
		left = true;
	}
	else if (current == '|')
	{
		up = true;
		down = true;
	}
	else if (current == '-')
	{
		right = true;
		left = true;
	}
	if (prevMove == "up")
	{
		down=false;
	}
	else if (prevMove == "down")
	{
		up = false;
	}
	else if (prevMove == "right")
	{
		left = false;
	}
	else if (prevMove == "left")
	{
		right = false;
	}

	if (right)
	{
		currentPos[0]++;
		return "right";
	}
	else if (left)
	{
		currentPos[0]--;
		return "left";
	}
	else if (down)
	{
		currentPos[1]++;
		return "down";
	}
	else if (up)
	{
		currentPos[1]--;
		return "up";
	}

	cout << "default path reached";
}

void pushBackVectors(vector<vector<char>>& bigMap, vector<vector<char>> lines, int x, int y)
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			bigMap[(3 * y) + i][(3 * x) + j] = lines[i][j];
		}
	}
}

void upscale(vector<vector<char>>& bigMap, vector<string>map)
{
	vector<char> blank = { '.', '.', '.' };
	vector<char> up = { '.','|' ,'.' };
	vector<char> full = { '-','-','-' };
	vector<char> upright = { '.','F','-' };
	vector<char> downright = { '.','L','-' };
	vector<char> upleft = { '-','7','.' };
	vector<char> downleft = { '-','J','.' };

	int mapYSize = map.size(), mapXSize = map[0].size();
	bigMap.resize(mapYSize*3, vector<char>(mapXSize*3));
	for (int y = 0; y < mapYSize; y++)
	{
		for (int x = 0; x < mapXSize; x++)
		{
			char pipe = map[y][x];
			if (pipe == 'L')
			{
				pushBackVectors(bigMap, { up, downright, blank }, x, y);
			}
			else if (pipe == 'J')
			{
				pushBackVectors(bigMap, { up, downleft, blank }, x, y);
			}
			else if (pipe == 'F')
			{
				pushBackVectors(bigMap, { blank, upright, up }, x, y);
			}
			else if (pipe == '7')
			{
				pushBackVectors(bigMap, { blank, upleft, up }, x, y);
			}
			else if (pipe == '-')
			{
				pushBackVectors(bigMap, { blank, full, blank }, x, y);
			}
			else if (pipe == '|')
			{
				pushBackVectors(bigMap, { up, up, up }, x, y);
			}
			else
			{
				pushBackVectors(bigMap, { blank, blank, blank }, x, y);
			}
		}
	}
}

void drawMap(vector<vector<char>> map)
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

int main() {
	auto start = chrono::high_resolution_clock::now();
	ifstream FileName;
	FileName.open("AOC10.txt");
	int totalCount = 1;
	string lineN;
	vector<string> map;
	vector<int>sPos;
	vector<vector<int>>path;
	int lineNum = 0;
	while (getline(FileName, lineN)) {
		map.push_back(lineN);
		int s = lineN.find('S');
		if (s != -1)
		{
			sPos.push_back(s);
			sPos.push_back(lineNum);
		}
		lineNum++;
	}
	replaceS(sPos, map);
	vector<int>currentPos = sPos;
	string prevMove = moveNext(currentPos, map, "up");
	path.push_back(currentPos);
	while (currentPos != sPos)
	{
		totalCount++;
		prevMove = moveNext(currentPos, map, prevMove);
		path.push_back(currentPos);
	}
	cout << "Part 1 = " << totalCount / 2 << endl;

	vector<vector<char>> bigMap;


	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[0].size(); x++)
		{
			vector<int> pos = { x,y };
			if (find(path.begin(), path.end(), pos) == path.end())
			{
				map[y][x] = '.';
			}
		}
	}
	upscale(bigMap, map);

	//drawMap(bigMap);
	bigMap[0][0] = '0';
	int mapYSize = bigMap.size(), mapXSize = bigMap[0].size();
	queue<vector<int>>toLook;
	toLook.push({ 0,0 });

	while (toLook.size() > 0)
	{
		vector<int> coords = toLook.front();
		int x = coords[0], y = coords[1];
		if (checkBoundary(y - 1, mapYSize) && bigMap[y - 1][x] == '.')
		{
			bigMap[y - 1][x] = '0';
			toLook.push({ x,y - 1 });
		}
		if (checkBoundary(y + 1, mapYSize) && bigMap[y + 1][x] == '.')
		{
			bigMap[y + 1][x] = '0';
			toLook.push({ x,y + 1 });
		}
		if (checkBoundary(x+1, mapXSize) && bigMap[y][x+1] == '.')
		{
			bigMap[y][x + 1] = '0';
			toLook.push({ x + 1,y });
		}
		if (checkBoundary(x - 1, mapXSize) && bigMap[y][x - 1] == '.')
		{
			bigMap[y][x - 1] = '0';
			toLook.push({ x - 1,y });
		}
		toLook.pop();
	}
	//drawMap(bigMap);
	
	int part2Count = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (bigMap[(3 * i) + 1][(3 * j) + 1] == '.')
			{
				part2Count++;
			}
		}
	}
	cout <<"Part 2 = "<< part2Count << endl;
	auto stop = chrono::high_resolution_clock::now();
	auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
	cout << duration.count() << endl;
}