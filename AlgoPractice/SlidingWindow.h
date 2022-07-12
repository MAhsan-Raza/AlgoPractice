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

				sum -= arr[wStart];
				++wStart;
			}
			else if (wEnd < arr.size())
			{
				sum += arr[wEnd];
				++wEnd;
			}
			else break;
		}

		if (minLen == INT_MAX)
			return 0;

		return minLen;
	}

	int MinLenEqGtrKDOUBLELOOP(const vector<int>& arr, const int k)
	{
		int minArr = INT_MAX;
		int wEnd = 0;
		int wBegin = 0;
		int arrSum = 0;

		for (int wEnd = 0; wEnd < arr.size(); wEnd++)
		{
			arrSum += arr[wEnd];

			while (arrSum >= k)
			{
				if ((minArr = std::min(minArr, wEnd - wBegin + 1)) == 1)
					return 1;
				arrSum -= arr[wBegin];
				++wBegin;
			}
		}

		return minArr == INT_MAX ? 0 : minArr;
	}


	int MinLenEqGtrK(const vector<int>& arr, const int k)
	{
		int minArr = INT_MAX;
		int wStart = 0, wEnd = 0, SASm = 0;

		while (wStart <= wEnd)		// since we want the min len
		{
			if (SASm >= k)
			{
				minArr = min(minArr, wEnd - wStart);
				SASm -= arr[wStart--];
			}
			else if (wEnd < arr.size())		SASm += arr[wEnd++];
			else							break;
		}

		return minArr == INT_MAX ? 0 : minArr;
	}

	int LongestSubstrKDistinct(const string& str, const int k)
	{
		int maxSubStr = 0;
		int wEnd = 0;
		int wStart = 0;
		unordered_map<char, int> ht(str.size());

		for (; wEnd < str.size(); wEnd++) // since we want max substr & if we hit last char there is no point shrinking the substr futher
		{
			++ht[str[wEnd]];

			while (ht.size() > k)
			{
				if (--ht[str[wStart]] == 0)
					ht.erase(str[wStart]);
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
			++ht[str[wEnd]];

			while (ht.size() > MAX_FRUIT)
			{
				if (--ht[str[wBegin]] == 0)
					ht.erase(str[wBegin]);
				++wBegin;
			}

			maxFruits = max(maxFruits, wEnd - wBegin + 1);
		}

		return maxFruits;
	}
};

int totalFruit(vector<int>& fruits) {

	int wStart = 0;
	int wEnd = 0;
	int maxFr = 0;
	unordered_map<int, int> ht;

	for (; wEnd < fruits.size(); wEnd++)
	{
		++ht[fruits[wEnd]];

		while (ht.size() > 2)
		{
			if (--ht[fruits[wStart]] == 0)
				ht.erase(fruits[wStart]);
			++wStart;
		}

		maxFr = max(maxFr, wEnd - wStart + 1);
	}

	return maxFr;
}

int maxSubStrDistinctCharsDoubleLoop(const string& str)
{
	int res = 0;
	int wStart = 0;
	int wEnd = 0;
	unordered_set<char> ht;

	while(wStart <= wEnd && wEnd < str.size())
	{ 
		if (ht.find(str[wEnd]) != ht.end())
		{
			ht.erase(str[wStart++]);
		}
		else
		{
			while (wEnd < str.size() && ht.find(str[wEnd]) == ht.end())
			{
				ht.insert(str[wEnd]);
				++wEnd;
			}
			res = max(res, wEnd - wStart);
		}
	}

	return res;
}

int maxSubStrDistinctChars(const string& str)
{
	int wStart = 0, wEnd = 0, res = 0;
	unordered_set<char> ht;

	while (wEnd < str.size())
	{
		if (ht.find(str[wEnd]) == ht.end())
		{
			ht.insert(str[wEnd]);
			++wEnd;
		}
		else
		{
			res = max(res, wEnd - wStart);
			ht.erase(str[wStart]);
			++wStart;
		}
	}

	return max(res, wEnd - wStart);
}

int minSubArrayLenDOUBLELOOP(int target, const vector<int>& nums)
{
	int wSum = 0;
	int minSubArr = INT_MAX;
	int wStart = 0;
	int wEnd = 0;

	for (; wStart < nums.size(); wStart++)
	{
		if (wStart > 0)
			wSum -= nums[wStart - 1];

		for (; wEnd < nums.size() && wSum < target; wEnd++)
			wSum += nums[wEnd];

		if (wSum >= target)
		{
			minSubArr = min(minSubArr, wEnd - wStart);
		}

	}
	return minSubArr == INT_MAX ? 0 : minSubArr;
}


int minSubArrayLen(const int k, const vector<int>& arr)
{
	int minArr = INT_MAX;
	int wStart = 0, wEnd = 0, SASm = 0;

	while (wStart <= wEnd)		// since we want the min len
	{
		if (SASm >= k)
		{
			minArr = min(minArr, wEnd - wStart);
			SASm -= arr[wStart++];
		}
		else if (wEnd < arr.size())		SASm += arr[wEnd++];
		else							break;
	}

	return minArr == INT_MAX ? 0 : minArr;
}


int LargestSubstringWithSameCharacters(const string& str)
{
	int res = 0;
	int wStart = 0;
	int wEnd = 0;

	while(wEnd < str.size())
	{
		if (str[wStart] == str[wEnd])
		{
			++wEnd;
		}
		else
		{
			res = max(res, wEnd - wStart);
			wStart = wEnd;
		}

	}

	return max(res, wEnd - wStart);
}

// This is O( N*N ) when K is nearer to N
int LongestSubstringWithSameLettersAfterReplacement_NbyN(const string& str, const int k)
{
	int res = 0;
	int wStart = 0;
	int wEnd = 0;
	int tmpK = k;
	int skpSI = 0;

	auto CalcCrntWndLen = [&str](const int ws, const int we, const int tk)->int 
	{
		int wl = we + tk - ws;
		return (wl > str.size()) ? str.size() : wl;
	};

	while (wEnd < str.size())
	{
		if (str[wStart] == str[wEnd])
		{
			++wEnd;
		}
		else if (tmpK > 0)
		{
			if (tmpK == k)
				skpSI = wEnd;
			--tmpK;
			++wEnd;
		}
		else
		{
			res = max(res, CalcCrntWndLen(wStart, wEnd, tmpK));

			if (tmpK != k)
			{
				wStart = wEnd = skpSI;
				tmpK = k;
			}
			else wStart = wEnd;
		}
	}

	return max(res, CalcCrntWndLen(wStart, wEnd, tmpK));
}

int LongestSubstringWithSameLettersAfterReplacement_ALLCHAR(const string& str, const int k)
{
        int res = 0;
        int wStart = 0, wEnd = 0;
        vector<int> ht;

        int maxFreq = 0;
        char maxChar;

        auto GetMax = [&str](const int prevMax, const int crntFreq, const char crntChar, int& newMax, char& maxChar) 
        {
            if (crntFreq > prevMax)
            {
                newMax = crntFreq;
                maxChar = crntChar;
            }
            // else do nothing since the prev is still the greater
        };

        auto GetNextMax = [&ht](int& nextMaxFrq, char& nextMaxChar)
        {
            nextMaxFrq = 0;
            for (int i=0; i<ht.size(); i++)
            {
                if (ht[i] > nextMaxFrq)
                {
                    nextMaxFrq = ht[i];
                    nextMaxChar = 'A' + i;
                }
            }
        };

        for (; wEnd < str.size(); wEnd++)
        {
            char rChr = str[wEnd];
            ++ht[rChr - 'A'];
            GetMax(maxFreq, ht[rChr - 'A'], rChr, maxFreq, maxChar);

            int wndLen = wEnd - wStart + 1;
            int expandables = wndLen - maxFreq;

            if(expandables > k)
            { 
                char lChr = str[wStart];
                --ht[lChr - 'A'];
                if(lChr == maxChar)
                    GetNextMax(maxFreq, maxChar);

                ++wStart;
                --wndLen;
            }
            res = max(res, wndLen);
        }

        return res;  
}

// Straight forward -> 2nd fastest
int LongestSubstringWithSameLettersAfterReplacement_2ndFast(const string& str, const int k)
{
	int res = 0;
	int wStart = 0, wEnd = 0;
	vector<int> ht(26, 0);

	int maxFreq = 0;
	char maxChar;

	auto GetMax = [&str](const int prevMax, const int crntFreq, const char crntChar, int& newMax, char& maxChar)
	{
		if (crntFreq > prevMax)
		{
			newMax = crntFreq;
			maxChar = crntChar;
		}
		// else do nothing since the prev is still the greater
	};

	auto GetNextMax = [&ht](int& nextMaxFrq, char& nextMaxChar)
	{
		nextMaxFrq = 0;
		for (int i = 0; i < ht.size(); i++)
		{
			if (ht[i] > nextMaxFrq)
			{
				nextMaxFrq = ht[i];
				nextMaxChar = 'A' + i;
			}
		}
	};

	for (; wEnd < str.size(); wEnd++)
	{
		char rChr = str[wEnd];
		++ht[rChr - 'A'];
		GetMax(maxFreq, ht[rChr - 'A'], rChr, maxFreq, maxChar);

		int wndLen = wEnd - wStart + 1;
		int expandables = wndLen - maxFreq;

		if (expandables > k)
		{
			char lChr = str[wStart];
			--ht[lChr - 'A'];
			if (lChr == maxChar)
				GetNextMax(maxFreq, maxChar);

			++wStart;
			--wndLen;
		}
		res = max(res, wndLen);
	}

	return res;
}

// Fastest
int LongestSubstringWithSameLettersAfterReplacement(const string& str, const int k)
{
	int res = 0;
	int wStart = 0, wEnd = 0;
	vector<int> ht(26, 0);

	int maxFreq = 0;
	for (; wEnd < str.size(); wEnd++)
	{
		maxFreq = max(maxFreq, ++ht[str[wEnd] - 'A']);
		int wndLen = wEnd - wStart + 1;
		if (wndLen - maxFreq > k)
		{
			--ht[str[wStart] - 'A'];
			++wStart;
			--wndLen;
		}
		res = max(res, wndLen);
	}

	return res;
}

/*
* Given an array which only consists of 0s and 1s. 
* Write a code to find the maximum number of consecutive 1s in an array, if we can flip at most one 0.
*/
int maxConscOnesAfterFlipSingleZero(const vector<int>& nums)
{
	int wStart = 0, wEnd = 0, nZeros = 0, res = 0;

	for (; wEnd < nums.size(); wEnd++)
	{
		if (nums[wEnd] == 0)		++nZeros;

		while (nZeros > 1)
		{
			if (nums[wStart] == 0) --nZeros;
			++wStart;
		}

		res = max(res, wEnd - wStart + 1);
	}
	return res;
}

// Second fastest still O(N + N) solutions
int maxConscOnesAfterFlipKZero2N(const vector<int>& nums, const int k)
{
	int wStart = 0, wEnd = 0, res = 0, nZeros = 0;

	for (; wEnd < nums.size(); wEnd++)
	{
		if (nums[wEnd] == 0)
			++nZeros;

		if (nZeros > k)
		{
			if (nums[wStart++] == 0)     --nZeros;
		}

		res = max(res, wEnd - wStart + 1);
	}
	return res;
}

// FASTEST
int maxConscOnesAfterFlipKZero(const vector<int>& nums, const int k)
{
	int wStart = 0, wEnd = 0, res = 0;
	queue<int> dq;

	for (; wEnd < nums.size(); wEnd++)
	{
		if (nums[wEnd] == 0)
			dq.push(wEnd);

		if (dq.size() > k)
		{
			wStart = dq.front() + 1;
			dq.pop();
		}

		res = max(res, wEnd - wStart + 1);
	}
	return res;
}

/*
* A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false. 
* He wants to confuse the students by maximizing the number of consecutive questions with the same answer (multiple trues or multiple falses in a row).
* You are given a string answerKey, where answerKey[i] is the original answer to the ith question. In addition, you are given an integer k, 
* the maximum number of times you may perform the following operation:
*	Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').
* Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the operation at most k times.
*/
int maxConsecutiveAnswers(const string& answerKey, int k)
{

	int maxConsc = 0, wStart = 0, wEnd = 0;
	int minFreq = 0, minChr = 0; // since we have only 2 possible elements, if we have all alphas we use maxFreq & maxChr
	int Ts = 0, Fs = 0;

	for (; wEnd < answerKey.size(); wEnd++)
	{
		answerKey[wEnd] == 'T' ? ++Ts : ++Fs;
		minFreq = min(Ts, Fs);

		if (minFreq > k)
		{
			answerKey[wStart++] == 'T' ? --Ts : --Fs;
			minFreq = min(Ts, Fs);
		}

		maxConsc = max(maxConsc, wEnd - wStart + 1); //No issue even if(minFreq > k) since window size remains the same
	}
	return maxConsc;
}

/*
* Given two strings s1 and s2, return true if s2 contains a permutation of s1, or false otherwise.
* In other words, return true if one of s1's permutations is the substring of s2.
*/
bool checkInclusion_Nx26(const string& ptrn, const string& str)
{
	int wStart = 0, wEnd = 0;
	unordered_map<char, int> ht;
	for_each(ptrn.begin(), ptrn.end(), [&ht](const char chr) {
			++ht[chr];
		});

	for (; wEnd < str.size(); wEnd++)
	{
		if (ht.find(str[wEnd]) != ht.end())
			--ht[str[wEnd]];
		
		if(wEnd >= ptrn.size())
		{ 
			if (ht.find(str[wStart]) != ht.end())
				++ht[str[wStart]];
			++wStart;
		}

		bool bRetTrue = true;
		for_each(ht.begin(), ht.end(), [&bRetTrue](const auto& itr) {
			if (itr.second != 0)
			{
				bRetTrue = false;
				return;
			}
			});
		if (bRetTrue)	return true;
	}
	return false;	
}

bool checkInclusion_HT(const string& ptrn, const string& str)
{
	int wStart = 0, wEnd = 0;
	unordered_map<char, int> ht;
	for_each(ptrn.begin(), ptrn.end(), [&ht](const char c) {	++ht[c];	});
	int matched = 0;

	for (; wEnd < str.size(); wEnd++)
	{
		if (ht.find(str[wEnd]) != ht.end())
		{
			if (--ht[str[wEnd]] >= 0)
				++matched;
			
		}

		if (wEnd >= ptrn.size())
		{
			if (ht.find(str[wStart]) != ht.end())
				if (ht[str[wStart]]++ >= 0)
					--matched;
			++wStart;
		}

		if (matched == ptrn.size())
			return true;
	}
	return false;
}

bool checkInclusion(const string& ptrn, const string& str)
{
	const int ptsz = ptrn.size();
	int wStart = 0, wEnd = 0;
	vector<short> ht(26, INT_MIN);
	for_each(ptrn.begin(), ptrn.end(), [&ht](const char c) {	++ht[c - 'a'];	});
	int matched = 0;

	for (; wEnd < str.size(); wEnd++)
	{
		char rC = str[wEnd];
		if (ht[rC - 'a'] != INT_MIN)
		{
			if (--ht[rC - 'a'] >= 0)
				++matched;

		}

		if (wEnd >= ptsz)
		{
			char lC = str[wStart];
			if (ht[lC - 'a'] != INT_MIN)
				if (ht[lC - 'a']++ >= 0)
					--matched;
			++wStart;
		}

		if (matched == ptsz)
			return true;
	}
	return false;
}

vector<int> findAllAnagrams(string s, string p)
{
	vector<int> res;
	int wStart = 0, wEnd = 0, matched = 0;
	unordered_map<char, int> ht;
	for_each(p.begin(), p.end(), [&ht](const char c) { ++ht[c]; });

	for (; wEnd < s.size(); wEnd++)
	{
		if (ht.find(s[wEnd]) != ht.end())
			if (--ht[s[wEnd]] >= 0)
				++matched;

		if (wEnd >= p.size())
		{
			if (ht.find(s[wStart]) != ht.end())
				if (ht[s[wStart]]++ >= 0)
					--matched;
			++wStart;
		}

		if (matched == p.size())
			res.push_back(wEnd - p.size() + 1);
	}

	return move(res);
}

string minSubstrContainingAllTargetChars(const string& s, const string& t)
{
	int wStart = 0, wEnd = 0, minLen = INT_MAX, minStrtPos = 0, minCnt = 0;
	int matched = 0;
	unordered_map<char, int> ht;
	for_each(t.begin(), t.end(), [&ht](const char c) { ++ht[c]; });

	for (; wEnd < s.size(); wEnd++)
	{
		if (ht.find(s[wEnd]) != ht.end() && --ht[s[wEnd]] >= 0)
			++matched;

		while (matched == t.size())
		{
			int wndLen = wEnd - wStart + 1;
			if (wndLen < minLen)
			{
				minStrtPos = wStart;
				minLen = minCnt = wndLen;
			}

			if (ht.find(s[wStart]) != ht.end() && ht[s[wStart]]++ >= 0)
				--matched;
			++wStart;
		}
	}

	return s.substr(minStrtPos, minCnt);
}

void testSlidingWindow()
{
	SlidingWindow sw;
	vector<int> res;
	string sres = "";

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
	sw.LongestSubstrKDistinct("cbbebi", 10);

	sw.FruitBasketContigious("ABCAC");
	sw.FruitBasketContigious("ABCBBC");

	minSubArrayLen(7, { 2,3,1,2,4,3 });
	minSubArrayLen(4, { 1,4,4 });
	minSubArrayLen(40, { 1,4,4 });

	LogestSubstrKDistinct("araaci", 2);
	LogestSubstrKDistinct("araaci", 1);
	LogestSubstrKDistinct("cbbebi", 3);
	LogestSubstrKDistinct("cbbebi", 10);

	vector<int> FRs = { 1,0,1,0,1,0,0,1,0,0,1,1,1,0,0,1,0,0,439,0,439,0,439,0,439,439,0,0,0,0,366,366,692,692,366,366,692,692,366,692,692,366,366,692,366,692,692,692,366,692,313,692,313,692,692,313,692,313,692,692,313,692,313,313,313,145,313,145,145,420,145,420,145,145,145,145,420,145,145,420,145,145,424,145,145,424,145,464,464,464,145,145,464,145,464,145,145,464,145,960,145,145,960,960,141,141,141,960,960,903,960,395,395,960,395,395,960,960,395,960,395,395,960,960,960,395,395,395,395,395,395,395,960,395,971,971,395,971,386,386,971,386,386,665,386,665,665,386,386,665,665,665,386,386,665,665,665,386,386,665,386,665,386,609,609,386,386,609,386,609,386,386,386,386,386,386,386,609,386,386,386,609,386,386,609,386,386,386,386,386,386,609,609,386,386,609,386,44,386,44,386,44,307,923,923,307,307,982,307,307,461,307,461,461,461,461,461,307,307,461,484,484,484,484,484,484,461,461,461,461,461,505,461,505,505,461,461,505,461,505,461,505,505,505,505,505,505,461,461,505,275,275,275,275,899,275,275,899,968,968,968,899,420,420,404,420,404,420,404,236,404,404,236,404,236,404,236,236,236,404,236,236,236,236,236,236,215,215,236,215,215,236,215,215,236,236,215,215,215,215,236,236,236,236,236,236,215,215,215,215,215,236,215,236,215,236,215,236,215,236,236,492,236,730,730,236,730,236,338,849,338,849,849,338,849,338,849,338,338,338,849,338,338,849,849,338,338,849,849,849,849,338,849,849,849,849,338,338,338,338,759,427,759,759,427,759,759,759,759,759,759,427,759,759,759,664,48,664,664,48,664,48,490,490,490,490,490,48,48,490,490,48,490,48,48,490,490,48,48,490,48,863,72,72,863,863,863,863,72,863,736,863,55,55,863,55,55,55,55,863,863,863,863,863,863,55,863,55,55,55,55,55,863,55,55,346,55,55,55,55,55,55,55,346,346,346,346,55,55,55,55,346,55,55,346,346,346,346,346,55,173,55,55,55,55,173,55,173,173,55,173,95,173,95,173,173,95,95,95,173,173,35,35,173,173,173,173,101,101,101,101,173,101,998,998,101,998,101,998,998,101,101,998,101,101,998,838,838,998,892,287,287,892,892,287,892,892,287,84,287,84,287,719,719,287,719,202,202,719,719,719,202,719,202,719,202,719,202,202,202,202,719,202,719,719,202,719,719,719,719,202,719,202,947,852,947,852,852,852,947,133,947,133,133,682,133,682,682,682,133,133,133,682,682,133,682,682,682,133,133,682,682,133,133,682,682,133,682,682,306,682,682,306,682,992,682,710,710,710,682,682,682,682,710,682,682,682,710,682,682,682,710,710,710,682,682,682,682,682,710,682,710,710,710,682,710,710,682,682,710,710,710,682,710,682,335,682,167,167,167,682,851,851,851,851,682,851,851,682,851,851,851,693,693,693,693,693,851,851,693,693,693,851,693,851,851,693,851,851,922,851,851,851,922,851,922,922,851,922,851,851,922,851,922,922,922,922,922,851,851,539,539,851,539,539,539,539,539,851,539,539,539,851,851,539,539,851,539,851,539,851,539,539,539,851,508,851,851,508,508,851,851,979,979,851,851,851,979,979,979,851,979,851,979,979,979,851,588,588,588,588,851,588,851,588,588,588,588,588,851,588,588,588,851,930,930,930,851,930,930,851,851,851,851,851,930,930,851,930,930,930,930,851,851,851,851,851,851,851,851,718,718,851,769,851,769,851,851,851,851,851,851,769,769,769,851,447,447,447,447,851,851,909,851,851,880,851,851,880,851,851,851,880,880,880,851,880,931,931,931,880,880,931,931,684,684,931,684,931,931,931,242,931,242,242,242,931,242,931,931,931,931,242,931,931,728,931,728,931,848,931,848,188,188,188,188,848,188,188,188,188,848,188,188,848,848,848,848,848,188,848,848,759,848,759,759,848,759,848,931,848,848,931,930,931,930,930,930,930,930,750,750,930,930,930,750,750,930,930,930,750,750,750,930,750,930,930,750,750,750,930,930,750,750,750,930,750,930,930,930,329,930,930,329,784,784,329,329,784,784,329,784,784,329,329,784,329,329,329,784,329,784,329,784,784,784,329,329,784,784,329,784,329,329,784,784,329,575,575,575,575,329,575,329,329,329,575,329,329,260,329,329,329,329,46,329,189,189,618,618,618,618,618,189,189,438,262,363,363,262,262,262,363,262,363,262,262,262,262,363 };

	totalFruit(FRs);

	maxSubStrDistinctChars("aabccbb");
	maxSubStrDistinctChars("abbbb");
	maxSubStrDistinctChars("abccde");
	maxSubStrDistinctChars("aaaaa");
	maxSubStrDistinctChars("");
	maxSubStrDistinctChars("z");
	maxSubStrDistinctChars("aabccbbxczvbnm");

	LargestSubstringWithSameCharacters("abcdddddeff");
	LargestSubstringWithSameCharacters("aabceebeee");

	LongestSubstringWithSameLettersAfterReplacement("AABCCBB", 2);
	LongestSubstringWithSameLettersAfterReplacement("ABBCB", 1);
	LongestSubstringWithSameLettersAfterReplacement("ABCCDE", 1);
	LongestSubstringWithSameLettersAfterReplacement("ABABA", 2);
	LongestSubstringWithSameLettersAfterReplacement("HHHHHH", 2000);
	LongestSubstringWithSameLettersAfterReplacement("A", 19);
	LongestSubstringWithSameLettersAfterReplacement("", 2);
	LongestSubstringWithSameLettersAfterReplacement("AAAB", 0);
	LongestSubstringWithSameLettersAfterReplacement("XAAA", 1);

	maxConscOnesAfterFlipKZero({ 1,1,0,0,1,1,1,1,1 }, 1);
	maxConscOnesAfterFlipKZero({ 1,1,0,0,1,1,1,1,1,0,1,1 }, 2);
	maxConscOnesAfterFlipKZero({ 1,1 }, 7);
	maxConscOnesAfterFlipKZero({ 0,0 }, 0);
	maxConscOnesAfterFlipKZero({ 0,0,1 }, 3);
	maxConscOnesAfterFlipKZero({ 1,1,0,0,1,1,0,0,0 }, 2);
	maxConscOnesAfterFlipKZero({ 1,1,1,0,0,0,1,1,1,1,0 }, 2);
	maxConscOnesAfterFlipKZero({ 0,0,1,1,0,0,1,1,1,0,1,1,0,0,0,1,1,1,1 }, 3);
	maxConscOnesAfterFlipKZero({ 0 }, 0);

	checkInclusion("ab", "eidbaooo");
	checkInclusion("ab", "eidboaoo");
	checkInclusion("adc", "dcda");
	checkInclusion("", "");
	checkInclusion("", "");
	checkInclusion("", "");

	res = findAllAnagrams("cbaebabacd", "abc");
	res = findAllAnagrams("abab", "ab");*/

	sres = minSubstrContainingAllTargetChars("aabdec", "abc");
	sres = minSubstrContainingAllTargetChars("aabdec", "abac");
	sres = minSubstrContainingAllTargetChars("abdbca", "abc");
	sres = minSubstrContainingAllTargetChars("adcad", "adcad");
	sres = minSubstrContainingAllTargetChars("ADOBECODEBANC", "ABC");
	sres = minSubstrContainingAllTargetChars("a", "a");
	sres = minSubstrContainingAllTargetChars("a", "aa");
	sres = minSubstrContainingAllTargetChars("cabwefgewcwaefgcf", "cae");
}