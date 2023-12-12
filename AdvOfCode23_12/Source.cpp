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
	int space = 0;
	while (space != -1)
	{
		space = line.find(',', pos);
		temp.push_back(stoull(line.substr(pos, -1)));
		pos = space + 1;
	}
	return temp;
}

int isPossible(string report, vector<int>springs,int pos, int spring)
{
	if (spring == springs.size())
	{
		for (int i = pos; i < report.size(); i++)
		{
			if (report[i] == '#')
			{
				return 0;
			}
		}
		return 1;
	}
	int sizeOfSpring = springs[spring];
	int total = 0;
	int startPos = pos;
	while (pos < report.size())
	{
		char curr = report[pos];
		if (curr != '.')
		{
			bool possible = true;
			for (int i = sizeOfSpring-1; i > 0; i--)
			{
				if ((pos+i)>=report.size() || report[pos + i] == '.')
				{
					possible = false;
					break;
				}			
			}
			if (pos>0&&report[pos - 1] == '#')
			{
				possible = false;
			}

			for (int i = startPos; i < pos; i++)
			{
				if (report[i] == '#')
				{
					possible = false;
				}
			}
			int next = pos + sizeOfSpring;

			if (possible&&(next<report.size())&&report[next]!='#')
			{
				total += isPossible(report, springs, next + 1, spring + 1);
			}
			if (possible && next == report.size() && spring == (springs.size() - 1))
			{
				total++;
			}
			if (possible && next > report.size() && spring == (springs.size() - 1))
			{
				return total;
			}

		}
		pos++;
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC12.txt");
	int totalCount = 0;
	string lineN;
	vector<string> reports;
	vector<vector<int>> springs;
	while (getline(FileName, lineN)) {
		int space = lineN.find(' ');
		reports.push_back(lineN.substr(0, space));
		springs.push_back(numsFromString(lineN, space));
	}

	for (int i = 0; i < reports.size(); i++)
	{
		int reportOptions;
		reportOptions = isPossible(reports[i], springs[i], 0, 0);
		totalCount += reportOptions;
		cout << "line " << i << " has numberOfOptions "<<reportOptions << endl;;
	}
	cout << totalCount << endl;

	//PART 2
	int64_t part2Total = 0;
	for (int i = 0; i < reports.size(); i++)
	{
		int vectorSize = springs[i].size();
		string baseReport = reports[i];
		for (int j = 0; j < 4; j++)
		{
			reports[i] += ('?' + baseReport);
			for (int k = 0; k < vectorSize; k++)
			{
				springs[i].push_back(springs[i][k]);
			}
		}


		
		int reportOptions;
		reportOptions = isPossible(reports[i], springs[i], 0, 0);
		part2Total += reportOptions;
		cout << "line " << i << " has numberOfOptions " << reportOptions << endl;
		
	}
	cout << part2Total << endl;
}