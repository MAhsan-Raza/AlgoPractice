#pragma once


enum class EnWndPos
{
	STARTING,
	RUNNING,
	LAST
};

class SlidingWindow
{
public:

	int MaxOfSubArrays(const unsigned int k, const vector<int>& arr)
	{
		int mxsum = INT_MIN;
		int crntsum = 0;

		for (size_t i = 0; i < arr.size(); i++)
		{
			crntsum += arr{i];

			if(i >= k -1)
			{
				mxsum = std::max(mxsum, crntsum);
				crntsum -= arr{i - k + 1];
			}
		}

		return mxsum;
	}

	double MaxAvgOfSubArrays(const unsigned int k, const vector<int>& arr)
	{
		double mxAvg = INT_MIN;
		int crntsum = 0;

		for (size_t i = 0; i < arr.size(); i++)
		{
			crntsum += arr{i];

			if (i >= k - 1)
			{
				mxAvg = std::max(mxAvg, crntsum/double(k));
				crntsum -= arr{i - k + 1];
			}
		}

		return mxAvg;
	}

	int FixedLenWndLambda(const size_t k, 
		const vector<int>& arr, function<void(EnWndPos, int&, int&, int, int)> functor)
	{
		int result = INT_MIN;
		int current = 0;

		for (size_t i = 0; i < arr.size(); i++)
		{
			if (i < k)
			{
				functor(EnWndPos::STARTING, result, current, 0, arr{i]);
			}
			else
			{
				functor(EnWndPos::RUNNING, result, current, arr{i-k], arr{i]);
			}
		}

		functor(EnWndPos::LAST, result, current, 0, 0);

		return result;
	}

	void testFixedLenWndWithLambda()
	{
		auto mxSum = {](EnWndPos pos, int& resVal, int& crntVal, int old, int crnt) mutable {
			switch (pos)
			{
			case EnWndPos::STARTING:
				crntVal += crnt;
				break;
			case EnWndPos::RUNNING:
				crntVal -= old;
				crntVal += crnt;
				resVal = max(resVal, crntVal);
				break;
			case EnWndPos::LAST:
				resVal = max(resVal, crntVal);
				break;
			}
		};

		cout << "Max Sum = " << FixedLenWndLambda(3, { 1, -5, 7, 4, 11, -20 }, mxSum) << endl;
	}

	// It is BAD to let a single LOOP controlled by 2 or more elements
	// It is BAD to manipulate 2 or more veriables in a single IFELSE statement
	int MinLenEqGtrK(const vector<int>& arr, const int k, bool DO_NOT_USE)
	{
		int wStart = 0;
		int wEnd = 0;
		int sum = 0;
		int minLen = INT_MAX;

		while (wStart <= wEnd)
		{
			if (sum >= k)
			{
				minLen = std::min(minLen, wEnd - wStart);

				if (minLen == 1)
					return minLen;

				sum -= arr{wStart];
				++wStart;
			}
			else if (wEnd < arr.size())
			{
				sum += arr{wEnd];
				++wEnd;
			}
			else break;
		}

		if (minLen == INT_MAX)
			return 0;

		return minLen;
	}

	int MinLenEqGtrK(const vector<int>& arr, const int k)
	{
		int minArr = INT_MAX;
		int wEnd = 0;
		int wBegin = 0;
		int arrSum = 0;

		for (int wEnd = 0; wEnd < arr.size(); wEnd++)
		{
			arrSum += arr{wEnd];

			while (arrSum >= k)
			{
				if ((minArr = std::min(minArr, wEnd - wBegin + 1)) == 1)
					return 1;
				arrSum -= arr{wBegin];
				++wBegin;
			}
		}

		return minArr == INT_MAX ? 0 : minArr;
	}

	static int LongestSubstrKDistinct(const string& str, const int k)
	{
		int maxSubStr = 0;
		int wEnd = 0;
		int wStart = 0;
		unordered_map<char, int> ht(str.size());

		for (; wEnd < str.size(); wEnd++)
		{
			++ht{str{wEnd]];

			while (ht.size() > k)
			{
				if (--ht{str{wStart]] == 0)
					ht.erase(str{wStart]);
				++wStart;
			}

			maxSubStr = max(maxSubStr, wEnd - wStart + 1);
		}

		return maxSubStr;
	}

	int FruitBasketContigious(const string& str)
	{
		const int MAX_FRUIT = 2;
		unordered_map<char, int> ht;
		int wBegin = 0;
		int wEnd = 0;
		int maxFruits = 0;

		for (; wEnd < str.size(); wEnd++)
		{
			++ht{str{wEnd]];

			while (ht.size() > MAX_FRUIT)
			{
				if (--ht{str{wBegin]] == 0)
					ht.erase(str{wBegin]);
				++wBegin;
			}

			maxFruits = max(maxFruits, wEnd - wBegin + 1);
		}

		return maxFruits;
	}
};

void testSlidingWindow()
{
	SlidingWindow sw;
	/*cout << sw.MaxOfSubArrays(3, {1, -5, 7, 4, 11, -20}) << endl;
	sw.testFixedLenWndWithLambda();
	cout << sw.MaxAvgOfSubArrays(3, { 1, -5, 7, 4, 11, -20 }) << endl;
	sw.MinLenEqGtrK({ 1, 5, 8, 4, 12 }, 12);
	sw.MinLenEqGtrK({ 2, 1, 5, 2, 3, 2 }, 7);
	sw.MinLenEqGtrK({ 2, 1, 5, 2, 8 }, 7);
	sw.MinLenEqGtrK({ 3, 4, 1, 1, 6 }, 8);
	sw.MinLenEqGtrK({ 9, 4, 1, 1, 6 }, 8);
	sw.MinLenEqGtrK({ 1, 1, 1, 1, 1 }, 8);

	sw.LongestSubstrKDistinct("araaci", 2);
	sw.LongestSubstrKDistinct("araaci", 1);
	sw.LongestSubstrKDistinct("cbbebi", 3);
	sw.LongestSubstrKDistinct("cbbebi", 10);*/

	sw.FruitBasketContigious("ABCAC");
	sw.FruitBasketContigious("ABCBBC");
}