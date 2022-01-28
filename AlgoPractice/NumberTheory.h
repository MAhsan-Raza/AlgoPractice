#pragma once

int GCD(int a, int b)
{
	if (a == 0)
		return b;

	return GCD(b % a, a);
}

int LCM(int a, int b)
{
	int gcd = GCD(a, b);
	return a * b / gcd;
}

long Factorial(int num)
{
	long res = 1;
	/*while (num-- > 1)
		res *= num;*/
	for (; num > 1; num--)
	{
		res *= num;
	}
	return res;
}

int TraillingZerosInFactorial(int num)
{
	int TZroz = 0;
	int Twozz = 0;
	int Fivez = 0;
	const int modu = 5;

	for (; num > 0 ; num--)
	{
		int tmp = num;
		do {
			if (tmp % modu == 0)
				++TZroz;
		} while ((tmp % modu == 0) && (tmp /= modu) > 0);
	}

	return TZroz;
}

//Not passing all leetcode test cases
int MaxGcdScoring(const vector<int>& arr)
{
	int maxScore = 0;

	using MMapIntTuples = multimap<int, pair<int, int>>;
	MMapIntTuples mmpScores;
	vector<bool> lookup(arr.size(), true);

	for (int i = 0; i < arr.size(); i++)
	{
		for (int j = i + 1; j < arr.size(); j++)
		{
			mmpScores.emplace(make_pair(GCD(arr[i], arr[j]), make_pair(i, j)));
		}
	}

	stack<int> scores;
	auto cItr = mmpScores.crbegin();
	while (cItr != mmpScores.crend())
	{
		if (lookup[cItr->second.first] && lookup[cItr->second.second])
		{
			int ScoreIncludedCurrent = 0;
			vector<bool> lookup2(lookup.begin(), lookup.end());
			auto cItr2 = cItr;
			while (cItr2 != mmpScores.crend())
			{
				if (lookup2[cItr2->second.first] && lookup2[cItr2->second.second])
				{
					ScoreIncludedCurrent += cItr2->first;
					lookup2[cItr2->second.first] = lookup2[cItr2->second.second] = false;
				}
				++cItr2;
			}
			int ScoreExludedCurrent = 0;
			vector<bool> lookup3(lookup.begin(), lookup.end());
			auto cItr3 = cItr;
			++cItr3;
			while (cItr3 != mmpScores.crend())
			{
				if (lookup3[cItr3->second.first] && lookup3[cItr3->second.second])
				{
					ScoreExludedCurrent += cItr3->first;
					lookup3[cItr3->second.first] = lookup3[cItr3->second.second] = false;
				}
				++cItr3;
			}

			if(ScoreIncludedCurrent > ScoreExludedCurrent)
			{
				scores.push(cItr->first);
				lookup[cItr->second.first] = lookup[cItr->second.second] = false;
			}
			else
			{
				lookup[cItr->second.first] = lookup[cItr->second.second] = true;
			}
		}
		++cItr;
	}

	int counter = 1;
	while (scores.empty() == false)
	{
		maxScore += (counter * scores.top());
		scores.pop();
		++counter;
	}

	return maxScore;
}

vector<vector<int>> GetCombinations(const int nums)
{
	vector<vector<int>> res;
	return res;
}

void testNumberTheory()
{
	/*auto x = GCD(15, 20);
	x = GCD(20, 15);
	x = LCM(15, 20);
	Factorial(5);

	Not working correctly
	TraillingZerosInFactorial(30);

	MaxGcdScoring({ 1,2 });
	MaxGcdScoring({ 3,4,6,8 });
	MaxGcdScoring({ 1,2,3,4,5,6 });
	MaxGcdScoring({ 415,230,471,705,902,87 });*/
}