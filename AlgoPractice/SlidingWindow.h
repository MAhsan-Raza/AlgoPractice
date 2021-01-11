#pragma once

#include<iostream>
#include<vector>
#include<functional>

using namespace std;

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
			crntsum += arr[i];

			if(i >= k -1)
			{
				mxsum = std::max(mxsum, crntsum);
				crntsum -= arr[i - k + 1];
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
			crntsum += arr[i];

			if (i >= k - 1)
			{
				mxAvg = std::max(mxAvg, crntsum/double(k));
				crntsum -= arr[i - k + 1];
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
				functor(EnWndPos::STARTING, result, current, 0, arr[i]);
			}
			else
			{
				functor(EnWndPos::RUNNING, result, current, arr[i-k], arr[i]);
			}
		}

		functor(EnWndPos::LAST, result, current, 0, 0);

		return result;
	}

	void testFixedLenWndWithLambda()
	{
		auto mxSum = [](EnWndPos pos, int& resVal, int& crntVal, int old, int crnt) mutable {
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

};

void testSlidingWindow()
{
	SlidingWindow sw;

	//cout << sw.MaxOfSubArrays(3, { 1, -5, 7, 4, 11, -20 }) << endl;
	//sw.testFixedLenWndWithLambda();
	cout << sw.MaxAvgOfSubArrays(3, { 1, -5, 7, 4, 11, -20 }) << endl;
}