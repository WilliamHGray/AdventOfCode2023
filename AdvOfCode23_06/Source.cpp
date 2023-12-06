#include <iostream>
#include <fstream>
#include <vector>
#include <string>
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
	long long space = 0;
	while (space != -1)
	{
		space = line.find(' ', pos);
		temp.push_back(stoi(line.substr(pos, -1)));
		pos = space + 1;
	}
	return temp;
}

int getMinDivisor(int time, int distance)
{
	int temp = 0;
	while (temp * time <= distance)
	{
		temp++;
		time--;
	}
	return temp;
}

long long getMinDivisor(long long time, long long  distance)
{
	long long temp = 0;
	while (temp * time <= distance)
	{
		temp++;
		time--;
	}
	return temp;
}


int main() {
	ifstream FileName;
	FileName.open("Aoc6.txt");
	int totalCount = 1;
	string lineN;
	vector<int> times, distances;
	int loop = 0;
	while (getline(FileName, lineN)) {
		if (loop == 0)
		{
			times = numsFromString(lineN);
			loop++;
		}
		else
		{
			distances = numsFromString(lineN);
		}
	}
	for (int i = 0; i < times.size();i++)
	{
		int n = getMinDivisor(times[i], distances[i]);
		totalCount *= ((times[i] + 1) - (n * 2));
	}
	long long totalTime, totalDistance;
	string totalTimeTemp, totalDistanceTemp;
	for (int i = 0; i < times.size(); i++)
	{
		totalTimeTemp += to_string(times[i]);
		totalDistanceTemp += to_string(distances[i]);
	}
	totalTime = stoull(totalTimeTemp);
	totalDistance = stoull(totalDistanceTemp);
	long part2 = getMinDivisor(totalTime, totalDistance);

	cout << totalCount << endl;
	cout << (totalTime+1)-(part2*2) << endl;
}