#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

vector<string> transpose(vector<string> base)
{
	vector<string> temp;
	temp.resize(base[0].size());
	for (int i = 0; i < base.size();i++)
	{
		for (int j = 0; j < base[0].size(); j++)
		{
			temp[j] += base[i][j];
		}
	}
	return temp;
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
}

bool assureLine(vector<string> input, int line1, int line2)
{
	int start = ((line1 + line2) / 2);
	int maxSize = input.size();
	for (int i = start; i > -1; i--)
	{	
		start++;
		if (start == maxSize)
		{
			return true;
		}
		if (input[i] != input[start])
		{
			return false;
		}
	}
	return true;
}

int findReflection(vector<string> input, int prevAnswer = -1)
{
	bool foundLine = false;
	for (int i = 1; i < input.size(); i++)
	{
		for (int j = 0; j < input.size(); j++)
		{
		    int answer = -1;
			if (j != i && input[i] == input[j] &&assureLine(input,i,j))
			{
				answer = 100 * (((i + j) / 2) + 1);
			}
			if (answer != -1 && answer != prevAnswer)
			{
			    return answer;
			}
		}
	}
	vector<string> temp = transpose(input);
	for (int i = 1; i < temp.size(); i++)
	{
		for (int j = 0; j < temp.size(); j++)
		{
		    int answer = -1;
			if (j != i && temp[i] == temp[j] && assureLine(temp, i, j))
			{
				answer = (((i + j) / 2) + 1);
			}
			if (answer != -1 && answer != prevAnswer)
			{
			    return answer;
			}
		}
	}
	return -1;
}

void swapSymbol(vector<string>& input, int i, int j)
{
	if (input[i][j] == '.')
	{
		input[i][j] = '#';
	}
	else
	{
		input[i][j] = '.';
	}
}

int findReflectionPart2(vector<string>input,int prevAnswer)
{
	vector<string> temp = input;
	for (int i = 0; i < input.size(); i++)
	{
		for (int j = 0; j < input[0].size(); j++)
		{
		    swapSymbol(temp, i, j);
			int answer1 , answer2;
			answer1 = (findReflection(temp,prevAnswer));
			//answer2 = findReflection(transpose(temp));
			if (answer1 != -1&& answer1!=prevAnswer)
			{
				//cout << j << ", " << i << endl;
				//drawVector(temp);
				return answer1;
			}
			swapSymbol(temp, i, j);
		}
	}
	return -1;
}

int main() {
	ifstream FileName;
	FileName.open("AOC13.txt");
	int totalCount = 0;
	string lineN;
	vector<string> temp;
	vector<vector<string>>inputs;
	int size = 0;
	while (getline(FileName, lineN)) {
		if (lineN.size() < 2)
		{
			inputs.push_back(temp);
			temp.clear();
			size = 0;
		}
		else
		{
		    if(size == 0)
		    {
		        size = lineN.size()-1;
		    }
			temp.push_back(lineN.substr(0,size));
		}
	}
	inputs.push_back(temp);
	vector<int>prevAnswer;
	for (int i = 0; i < inputs.size(); i++)
	{
		int answer = findReflection(inputs[i]);
		totalCount += answer;
		prevAnswer.push_back(answer);
		cout << i << " has line of reflection " << answer << endl;
	}
	cout << "Part 1: " << totalCount << endl;

	int part2Answer = 0;
	for (int i = 0; i < inputs.size(); i++)
	{
		int answer = findReflectionPart2(inputs[i], prevAnswer[i]);
		part2Answer += answer;
		cout << i << " has line of reflection " << answer << endl;
	}
	cout << "Part 2: " << part2Answer << endl;
}
