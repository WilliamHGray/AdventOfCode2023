#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
const vector<string> colours = { "red", "green", "blue" };
const vector<int>totals = { 12,13,14 };

void getGames(vector<string>& games, string line)
{
	line = line.substr(line.find(":") + 1, -1);
	bool cont = true;
	while (cont)
	{
		int semic = line.find(";");
		games.push_back(line.substr(0, semic));
		if (semic != -1)
		{
			line = line.substr(semic + 1, -1);
		}
		else
		{
			cont = false;
		}
	}

}

int main() {
	ifstream FileName;
	FileName.open("AOC2.txt");
	int totalCount = 0;
	int powerSum = 0;
	string lineN;
	int redTotal = 12, greenTotal = 13, blueTotal = 14;
	while (getline(FileName, lineN)) {
		vector<string> games;
		int gameNumber = stoi(lineN.substr(4, lineN.find(":")));
		getGames(games, lineN);
		bool possible = true;
		vector<int> colourMin = { 0,0,0 };
		for (int i = 0; i < games.size(); i++)
		{
			string game = games[i];
			for (int j = 0; j < colours.size(); j++)
			{
				int col = game.find(colours[j]);
				if (col != -1)
				{
					int numCol = stoi(game.substr(col - 3, col));
					if (numCol > totals[j])
					{
						possible = false;
					}
					if (numCol > colourMin[j])
					{
						colourMin[j] = numCol;
					}
				}
			}
		}
		int power = (colourMin[0] * colourMin[1] * colourMin[2]);
		//cout << power << endl;
		powerSum += power;
		if (possible)
		{
			totalCount += gameNumber;
		}

	}
	cout << totalCount << endl;
	cout << powerSum << endl;
}