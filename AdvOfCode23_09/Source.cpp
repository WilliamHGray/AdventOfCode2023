#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

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

bool isZero(vector<int> line)
{
	for (int i = 0; i < line.size(); i++)
	{
		if (line[i] != 0)
		{
			return false;
		}
	}
	return true;
}

int getDiff(vector<int> nums, bool nextTerm = true)
{
	vector<int> temp;
	for (int i = 1; i < nums.size(); i++)
	{
		temp.push_back((nums[i] - nums[i - 1]));
	}
	if (isZero(temp))
	{
		return 0;
	}
	else if(nextTerm)
	{
		return (temp[temp.size() - 1] + getDiff(temp));
	}
	else
	{
		return (temp[0] - getDiff(temp,false));
	}
}

int main() {
	ifstream FileName;
	FileName.open("AOC9.txt");
	int totalCount = 0;
	int part2 = 0;
	int lineNum = 0;
	string lineN;
	while (getline(FileName, lineN)) {
		vector<int> line = numsFromString(lineN);
		int nthTerm = line[line.size()-1] + getDiff(line);
		int zerothTerm = line[0] - getDiff(line,false);
		cout << "Next term for line " << lineNum << " = " << nthTerm << endl;
		cout << "Zeroeth term for line " << lineNum << " = " << zerothTerm << endl;
		totalCount += nthTerm;
		part2 += zerothTerm;
		cout << endl;
		lineNum++;
	}
	cout << totalCount << endl;
	cout << part2 << endl;
}