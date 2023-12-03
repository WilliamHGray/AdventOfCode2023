#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;
const char gear = ' * ';

int findNumbers(string prevLine, string currLine, string nextLine, set<char> uniques)
{
	int pos = 0;
	int total = 0;
	vector<string> toRead = { prevLine,currLine,nextLine };
	while (pos < currLine.size())
	{
		bool enginePart = false;
		if (currLine[pos] >= '0' && currLine[pos] <= '9')
		{
			int end = currLine.find('.', pos);
			if (end == -1)
			{
				bool found = false;
				for (int i = pos; i < currLine.size(); i++)
				{
					if (uniques.find(currLine[i]) != uniques.end())
					{
						found = true;
						end = i;
						break;
					}
				}
				if (!found)
				{
					end = currLine.size();
				}
			}
			else
			{
				bool found = false;
				for (int i = pos; i < end; i++)
				{
					if (uniques.find(currLine[i]) != uniques.end())
					{
						found = true;
						end = i;
						break;
					}
				}
			}
			for (int i = 0; i < 3; i++)
			{
				for (int j = pos - 1; j <= end; j++)
				{
					if (j != -1 && j < currLine.size())
					{
						if (uniques.find(toRead[i][j])!=uniques.end())
						{
							enginePart = true;
						}
					}
				}
			}
			if (enginePart)
			{
				total += stoi(currLine.substr(pos, end));
			}
			pos = end;
		}
		else
		{
			pos++;
		}
	}
	return total;
}


int findNums(string line, int pos, int lineNum, int relPos)
{
	if (lineNum != 1&&relPos!=-1)
	{	
		char prev = line[pos - 1];
		if (prev >= '0' && prev <= '9')
		{
			return 1;
		}
		char curr = line[pos];
		if (curr >= '0' && curr <= '9')
		{
			int end = pos + 1;
			while (end != line.size())
			{
				char endC = line[end];
				if (!(prev >= '0' && prev <= '9'))
				{
					break;
				}
				end++;
			}
			return stoi(line.substr(pos, end));
		}
		else
		{
			return 1;
		}

	}
	else
	{
		char curr = line[pos];
		if (curr >= '0' && curr <= '9')
		{
			int start = pos - 1;
			int end = pos + 1;
			while (start > -1)
			{
				char nextChar = line[start];
				if (!(nextChar >= '0' && nextChar <= '9'))
				{
					break;
				}
				start--;
			}
			while (end <line.size())
			{
				char nextChar = line[end];
				if (!(nextChar >= '0' && nextChar <= '9'))
				{
					break;
				}
				end++;
			}
			return stoi(line.substr(start+1, end));
		}
		else
		{
			return 1;
		}
	}
}

int findGears(string prevLine, string currLine, string nextLine)
{
	int total = 0;
	int pos = 0;
	vector<string> toRead = { prevLine,currLine,nextLine };
	while (pos < currLine.size())
	{
		int base = 1, nextBase = 1;
		int numGears = 0;
		if (currLine[pos] == '*')
		{
			//std::cout << "FOUND GEAR" << endl;
			for (int i = 0; i < 3; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					nextBase *= findNums(toRead[i], pos + j, i, j);
					if (base != nextBase)
					{
						//std::cout << nextBase << endl;
						numGears++;
						base = nextBase;
					}
				}
			}
		}
		if (numGears == 2)
		{
			total += base;
		}
		pos++;
		/*
		if (total != 0)
		{
			std::cout << total << endl;
		}
		*/
	}
	return total;
}

int main() {
	ifstream FileName;
	FileName.open("AOC3.txt");
	int totalCount = 0;
	int gearTotal = 0;
	string lineN;
	string prevLine, currLine;
	bool init = true;
	set<char> uniques;
	string emptyLine;
	while (getline(FileName, lineN)) {
		if (init)
		{
			int n = lineN.size();
			for (int i = 0; i < n; i++)
			{
				currLine.append(".");
				prevLine.append(".");
				emptyLine.append(".");
			}
			init = false;
		}

		for (int i = 0; i < lineN.size(); i++)
		{
			if (lineN[i] != '.' && (lineN[i] < '0' || lineN[i]>'9'))
			{
				uniques.insert(lineN[i]);
			}
		}
		totalCount += findNumbers(prevLine, currLine, lineN, uniques);
		//std::cout << totalCount << endl;
		gearTotal += findGears(prevLine, currLine, lineN);
		prevLine = currLine;
		currLine = lineN;
	}
	totalCount += findNumbers(prevLine, currLine, emptyLine, uniques);
	
	set<char>::iterator iter = uniques.begin();
	while (iter != uniques.end())
	{
		char setchar = *iter;
		std::cout << setchar;
		iter++;
	}
	std::cout << endl;
	std::cout << totalCount << endl;
	std::cout << gearTotal << endl;
}