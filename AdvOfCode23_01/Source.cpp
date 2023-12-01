#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const vector<string> words = { "zero", "one", "two", "three", "four","five","six","seven","eight","nine" };
int main() {
	ifstream FileName;
	FileName.open("AOC1.txt");
	int totalCount = 0;
	string lineN;

	while (getline(FileName, lineN)) 
	{
		vector<int> nums;
		for (int i = 0; i < lineN.length(); i++)
		{
			char toRead = lineN[i];
			if (toRead >= '0' && toRead <= '9')
			{
				nums.push_back(toRead - '0');
			}
			else //new for part 2
			{
				for (int j = 0; j < words.size(); j++)
				{
					if (lineN.substr(i,-1).find(words[j]) == 0)
					{
						nums.push_back(j);
					}
				}
			}
		}
		totalCount += (10 * nums[0] + nums[nums.size() - 1]);
		cout<< nums[0]<< ", "<< nums[nums.size() - 1] << endl;
		cout << (10 * nums[0] + nums[nums.size() - 1]) << endl;
	}
	
	cout << totalCount << endl;
	
	
}