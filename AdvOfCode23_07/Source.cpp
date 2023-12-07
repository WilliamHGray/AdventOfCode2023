#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
using namespace std;
const bool logging = true;

bool isANumber(char c)
{
	if (c >= '0' && c <= '9')
	{
		return true;
	}
	return false;
}

int rankHand(vector<int> hand)
{
	set<int> numsInHand(hand.begin(), hand.end());
	int mostRepeats = 1;
	for (set<int>::iterator iter = numsInHand.begin(); iter!= numsInHand.end();iter++)
	{
		int temp = 0;
		for (int j = 0; j < hand.size(); j++)
		{
			if (hand[j] == *iter)
			{
				temp++;
			}
			//part 2
			
			else if (hand[j] == 0)
			{
				temp++;
			}
		}
		if (temp > mostRepeats)
		{
			mostRepeats = temp;
		}
	}
	numsInHand.erase(0);
	switch (numsInHand.size()) {
		case 5:
			return 0;
		case 4:
			return 1;
		case 3:
			if (mostRepeats == 3)
			{
				return 3;
			}
			else
			{
				return 2;
			}
		case 2:
			if (mostRepeats == 4)
			{
				return 5;
			}
			else
			{
				return 4;
			}
		case 1:
			return 6;
		case 0:
			return 6;
	}

}

bool isHigher(int hand1Rank, int hand2Rank, vector<int>hand1, vector<int>hand2)
{
	if (hand1Rank > hand2Rank)
	{
		return true;
	}
	else if (hand1Rank == hand2Rank)
	{
		int pos = 0;
		while (hand1[pos] == hand2[pos])
		{
			pos++;
		}
		if (hand1[pos] > hand2[pos])
		{
			return true;
		}
	}
	return false;

}

int main() {
	ifstream FileName;
	FileName.open("AOC7.txt");
	int totalCount = 0;
	int spacePos = 5;
	string lineN;
	vector<vector<int>> hands;
	vector<int> ranks, bids;
	while (getline(FileName, lineN)) {
		vector<int>temp;
		for (int i = 0; i < spacePos; i++)
		{
			if (isANumber(lineN[i]))
			{
				temp.push_back(lineN[i]-'0');
			}
			else
			{
				switch (lineN[i]) {
				case 'T':
					temp.push_back(10);
					break;
				case 'J':
					//temp.push_back(11);
					temp.push_back(0);
					break;
				case 'Q':
					temp.push_back(12);
					break;
				case 'K':
					temp.push_back(13);
					break;
				case 'A':
					temp.push_back(14);
					break;
				}
			}
		}
		bids.push_back(stoi(lineN.substr(spacePos + 1, -1)));
		ranks.push_back(rankHand(temp));
		hands.push_back(temp);
	}
	bool sorted = false;
	while (!sorted)
	{
		sorted = true;
		for (int i = 0; i < hands.size() - 1; i++)
		{
			if (isHigher(ranks[i], ranks[i + 1], hands[i], hands[i + 1]))
			{
				sorted = false;
				int tempBid = bids[i];
				int tempRank = ranks[i];
				vector<int> tempHand = hands[i];
				bids[i] = bids[i + 1];
				ranks[i] = ranks[i + 1];
				hands[i] = hands[i + 1];
				bids[i+1] = tempBid;
				ranks[i+1] = tempRank;
				hands[i+1] = tempHand;
			}
		}
	}
	for (int i = 0; i < bids.size(); i++)
	{
		if (logging) 
		{
			for (int j = 0; j < 5; j++)
			{
				cout << hands[i][j] << " ";
			}
			cout << "rank " << ranks[i] << endl;
			totalCount += ((i + 1) * bids[i]);
		}
	}
	std::cout << totalCount << endl;
}