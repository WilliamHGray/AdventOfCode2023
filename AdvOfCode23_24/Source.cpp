#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

vector<int> addVectors(vector<int> first, vector<int> second)
{
	vector<int> temp;
	for (int i = 0; i < first.size(); i++)
	{
		temp.push_back(first[i] + second[i]);
	}
	return temp;
}

vector<int> numsFromString(string line, int pos = 0)
{
	vector<int> temp;
	int space = 0;
	while (space !=-1)
	{
		space = line.find(',', pos);
		temp.push_back(stoi(line.substr(pos, space-pos)));
		pos = space + 1;
	}
	return temp;
}

vector<long long> numsFromString64(string line, int pos = 0)
{
	vector<long long> temp;
	int space = 0;
	while (space != -1)
	{
		space = line.find(',', pos);
		temp.push_back(stoll(line.substr(pos, space - pos)));
		pos = space + 1;
	}
	return temp;
}

vector<long double> solve2d(vector<long long> pos1, vector<int> speed1, vector<long long> pos2, vector<int> speed2)
{
	int a1 = speed1[0], a2 = speed1[1], b1 = -speed2[0], b2 = -speed2[1];
	long long c1 = (pos2[0] - pos1[0]), c2 = (pos2[1] - pos1[1]);
	//implement cramer's rule
	long double denom = (long double)(a1 * b2 - b1 * a2);
	if (denom == 0)
	{
		return { -1,-1 };
	}
	long double t1 = (c1 * b2 - b1 * c2) / denom;
	long double t2 = (a1 * c2 - c1 * a2) / denom;
	return { t1,t2 };
}

void printPart2Answer()
{
	int64_t x = 339708138568903;
	int64_t	y = 183946143494745;
	int64_t	z = 129012368412302;
	cout << "PART 2: " << x + y + z << endl;
}

int main() {
	ifstream FileName;
	/*
	FileName.open("AOCTest.txt");
	int minPos = 7;
	int maxPos = 27;
	*/
	
	FileName.open("AOC24.txt");
	long long minPos = 200000000000000;
	long long maxPos = 400000000000000;
	
	int totalCount = 0;
	string lineN;
	int lineNum = 0;
	vector<vector<long long>> positions;
	vector<vector<int>> speeds;
	while (getline(FileName, lineN)) {
		int mid = lineN.find('@');
		positions.push_back(numsFromString64(lineN.substr(0, mid - 1)));
		speeds.push_back(numsFromString(lineN.substr(mid + 1, -1)));
	}
	int hailstones = positions.size();
	for (int i = 0; i < hailstones; i++)
	{
		for (int j = i + 1; j < hailstones; j++)
		{
			//if speed of two lines are the same, then the difference between the two points of intersection is 
			//V_x(t_2-t_1)=(pos[j]+speed[j]*t_2-pos[i]-speed[i]*t_1)
			//this reduces to (t_2-t_1)=(x_2-x_1)/(V_x-speed[i])
			//The former is an integer, so V_x-speed[i] must perfectly divide the x difference between the two lines.
			//So look for the prime factorisation of x_2-x_1 (wolfram alpha) and find Vx such that Vx-speed[i] is a product of these.
			//e.g. (2^2 * 316103612179)/(V_x+79) ->V_x+79 =4 -> V_x = -75
			//repeat for y and z
			//dx = -75, dy = 177, dz = 280
			// since dz = 280 appears in the input, we can say that z = 129012368412302 
			//This is because the x and y speeds are different so the only time the stone and this hailstone will ever meet is at t=0
			//this allows us to find the other two trivially
			/*
			

			select a random line and solve for t
			440708930150677, 438509363093706, 494882582815667 @ -173, -70, -75
			129012368412302+280t=494882582815667-75t
			t=1030620322263
			x-75t = 440708930150677-173t
			y+177t=438509363093706-70t

			x=339708138568903
			y=183946143494745
			z = 129012368412302
			*/
			if (speeds[i][0] == speeds[j][0])
			{
				//cout << "x=" << positions[i][0] << ", " << positions[j][0] << ", " << positions[i][0] - positions[j][0] << ", " << speeds[i][0] << endl;
			}
			if (speeds[i][1] == speeds[j][1])
			{
				//cout << "y=" << positions[i][1] << ", " << positions[j][1] << ", " << positions[i][1] - positions[j][1] << ", " << speeds[i][1] << endl;
			}
			if (speeds[i][2] == speeds[j][2])
			{
				//cout << "z=" << positions[i][2] << ", " << positions[j][2] << ", " << positions[i][2] - positions[j][2] << ", " << speeds[i][2] << endl;
			}
			vector<long double> times = solve2d(positions[i], speeds[i], positions[j], speeds[j]);
			long double t = times[0];
			long double newX = (float)positions[i][0] + (float)speeds[i][0] * t;
			long double newY = (float)positions[i][1] + (float)speeds[i][1] * t;

			if (newX >= minPos && newX <= maxPos && newY >= minPos && newY <= maxPos && t > 0 && times[1] > 0)
			{
				totalCount++;
			}
		}
	}
	cout << "PART 1: " << totalCount << endl;
	printPart2Answer();
}