#pragma once

int lengthOfLongestCommonSubString(const string& s1, const string& s2)
{
	long long REC_CALLS = 0;
	int maxCSS = 0;
	vector<vector<int>> memChc(s1.size(), vector<int>(s2.size(), -1));

	function<int(int, int)> getLCSS = [&](const int iS1, const int iS2)->int
	{
		++REC_CALLS;
		if (iS1 == s1.size() || iS2 == s2.size())		return 0;
		if (memChc[iS1][iS2] != -1)						return memChc[iS1][iS2];

		if (s1[iS1] == s2[iS2])
		{
			// Since we are matching substring (not SubSeqs), so cache & return only the matched length, 
			// otherwise (if current char breaks the substring) return 0
			// basically we are returning the length of consicutive matched chars from this point only
			memChc[iS1][iS2] = 1 + getLCSS(iS1 + 1, iS2 + 1);
			maxCSS = max(maxCSS, memChc[iS1][iS2]);
		}
		else memChc[iS1][iS2] = 0;

		// Exploring all the other combinations to fillup there respected places in cache & looking for substring we miss during above, 
		// e.g. "abxc" vs "aab"
		// we do not consider the length until the chars start to match
		getLCSS(iS1 + 1, iS2), 
		getLCSS(iS1, iS2 + 1);

		return memChc[iS1][iS2];
	};

	getLCSS(0, 0);
	return maxCSS;
}

int MaximumLengthRepeatedSubarray(const vector<int>& nums1, const vector<int>& nums2)
{

	int maxRSA = 0;
	vector<vector<int>> memChc(nums1.size(), vector<int>(nums2.size(), -1));

	function<int(int, int)> calcMaxRSA = [&](const int iS1, const int iS2)->int
	{
		if (iS1 == nums1.size() || iS2 == nums2.size())		return 0;
		if (memChc[iS1][iS2] != -1)							return memChc[iS1][iS2];

		if (nums1[iS1] == nums2[iS2])
		{
			// Since we are matching substring (not SubSeqs), so cache & return only the matched length, 
			// otherwise (if current char breaks the substring) return 0
			// basically we are returning the length of consicutive matched chars from this point only
			memChc[iS1][iS2] = 1 + calcMaxRSA(iS1 + 1, iS2 + 1);
			maxRSA = max(maxRSA, memChc[iS1][iS2]);
		}
		else memChc[iS1][iS2] = 0;

		// Exploring all the other combinations, we do not consider the length until the chars start to match
		calcMaxRSA(iS1 + 1, iS2),
		calcMaxRSA(iS1, iS2 + 1);

		
		return memChc[iS1][iS2];
	};

	calcMaxRSA(0, 0);
	return maxRSA;
}

string findLongestCommonSubString(const string& s1, const string& s2)
{
	vector<char> tmpCSS;
	tmpCSS.reserve(s1.size());
	string LCSS;
	vector<vector<int>> memChc(s1.size(), vector<int>(s2.size(), -1));
	cout << s1 << " V " << s2 << ":- ";

	function<int(int, int)> calcLCSS = [&](const int iS1, const int iS2)->int
	{
		if (iS1 == s1.size() || iS2 == s2.size())		return 0;

		if (memChc[iS1][iS2] == -1)
		{
			if (s1[iS1] == s2[iS2])
			{
				tmpCSS.push_back(s1[iS1]);
				memChc[iS1][iS2] = 1 + calcLCSS(iS1 + 1, iS2 + 1);
			}
			else memChc[iS1][iS2] = 0;

			if (tmpCSS.size() > LCSS.size())
				LCSS = string(tmpCSS.begin(), tmpCSS.end());
			tmpCSS.clear();

			calcLCSS(iS1 + 1, iS2);
			calcLCSS(iS1, iS2 + 1);
		}
		else if(false == tmpCSS.empty())
		{
			for (int i = iS1; i < iS1 + memChc[iS1][iS2]; i++)
				tmpCSS.push_back(s1[i]);

			if (tmpCSS.size() > LCSS.size())
				LCSS = string(tmpCSS.begin(), tmpCSS.end());
		}

		return memChc[iS1][iS2];
	};

	calcLCSS(0, 0);
	cout << LCSS << endl;
	return LCSS;
}

int longestCommonSubsequence(const string& text1, const string& text2)
{
	vector<vector<int>> memChc(text1.size(), vector<int>(text2.size(), -1));

	function<int(int, int)> getLCSSeq = [&](const int it1, const int it2)->int
	{
		if (it1 == text1.size() || it2 == text2.size())      return 0;

		if (memChc[it1][it2] == -1)
		{
			if (text1[it1] == text2[it2])
				memChc[it1][it2] = 1 + getLCSSeq(it1 + 1, it2 + 1);
			else
				memChc[it1][it2] = max(getLCSSeq(it1 + 1, it2), getLCSSeq(it1, it2 + 1));
		}

		return memChc[it1][it2];
	};

	return getLCSSeq(0, 0);
}

//Minimum Deletions & Insertions to Transform a String into another
void findMDI(const string& s1, const string& s2) 
{
	int LCSSeq = -1;
	vector<vector<int>> memChc(s1.size(), vector<int>(s2.size(), -1));

	function<int(int, int)> findLCSSeq = [&](const int iS1, const int iS2)->int
	{
		if (iS1 == s1.size() || iS2 == s2.size())		return 0;

		if (memChc[iS1][iS2] == -1)
		{
			if (s1[iS1] == s2[iS2])
				memChc[iS1][iS2] = 1 + findLCSSeq(iS1 + 1, iS2 + 1);
			else
				memChc[iS1][iS2] = max(findLCSSeq(iS1 + 1, iS2), findLCSSeq(iS1, iS2 + 1));
		}

		return memChc[iS1][iS2];
	};

	LCSSeq = findLCSSeq(0, 0);

	cout << s1 << " V " << s2 << ":-\t\t D[" << s1.size() - LCSSeq << "] I[" << s2.size() - LCSSeq << "]\n";
}

//Given two strings word1 and word2, return the minimum number of steps required to make word1 and word2 the same.
int minDistance(const string& word1, const string& word2)
{
	vector<vector<int>> memChc(word1.size(), vector<int>(word2.size(), -1));

	function<int(int, int)> calcLCSSeq = [&](const int iW1, const int iW2)->int
	{
		if (iW1 == word1.size() || iW2 == word2.size())      return 0;

		if (memChc[iW1][iW2] == -1)
		{
			if (word1[iW1] == word2[iW2])
				memChc[iW1][iW2] = 1 + calcLCSSeq(iW1 + 1, iW2 + 1);
			else
				memChc[iW1][iW2] = max(calcLCSSeq(iW1 + 1, iW2), calcLCSSeq(iW1, iW2 + 1));
		}

		return memChc[iW1][iW2];
	};

	int LCSSeq = calcLCSSeq(0, 0);
	return (word1.size() - LCSSeq) + (word2.size() - LCSSeq);
}


/*
* This solution is:-	O(N*N) time & O(N*N) space
* GeekForGeeks:-		O(N*N) time & O(N) space
* Optimal (GfG):-		O(N*LogN) time & 
*/
int lengthOfLIS(const vector<int>& nums1) 
{
	int i = 0;
	set<int> ht;
	for (; i < nums1.size(); i++)
		ht.insert(nums1[i]);

	vector<int> nums2(ht.size(), 0);

	i = 0;
	auto itrHT = ht.begin();
	while (itrHT != ht.end())
	{
		nums2[i++] = *itrHT;
		++itrHT;
	}
	ht.clear();

	vector<vector<int>> memChc(nums1.size(), vector<int>(nums2.size(), -1));
	function<int(int, int)> longestCommonSubSeq = [&](const int iN1, const int iN2)->int
	{
		if (iN1 == nums1.size() || iN2 == nums2.size())		return 0;

		if (memChc[iN1][iN2] == -1)
		{
			if (nums1[iN1] == nums2[iN2])
			{
				memChc[iN1][iN2] = 1 + longestCommonSubSeq(iN1 + 1, iN2 + 1);
			}
			else
			{
				memChc[iN1][iN2] = max(
					longestCommonSubSeq(iN1 + 1, iN2    ),
					longestCommonSubSeq(iN1    , iN2 + 1)
				);
			}
		}

		return memChc[iN1][iN2];
	};

	return longestCommonSubSeq(0, 0);
}

void testLongestCommonSubString()
{

	/*lengthOfLongestCommonSubString("axab", "ab");
	lengthOfLongestCommonSubString("abxc", "aab");
	lengthOfLongestCommonSubString("123zzzz5123456zz", "q523zGeGe123456sdfsd2");	// 4,056,303,536 v 697  -> 6
	lengthOfLongestCommonSubString("ab", "xyz");
	lengthOfLongestCommonSubString("ab", "xyzabv");
	lengthOfLongestCommonSubString("ab", "ab");
	lengthOfLongestCommonSubString("cccab", "xyzabv");
	lengthOfLongestCommonSubString("abxxxkfc", "abvvkfc");
	lengthOfLongestCommonSubString("abcdxyz", "xyzabcd");
	lengthOfLongestCommonSubString("", "dabz");
	lengthOfLongestCommonSubString("t", "xyz");
	lengthOfLongestCommonSubString("01111", "10101");

	longestCommonSubsequence("axab", "ab");
	longestCommonSubsequence("abxc", "aab");
	longestCommonSubsequence("123zzzz5123456zz", "q523zGeGe123456sdfsd2");	// 4,056,303,536 v 697  -> 6
	longestCommonSubsequence("ab", "xyz");
	longestCommonSubsequence("ab", "xyzabv");
	longestCommonSubsequence("ab", "ab");
	longestCommonSubsequence("cccab", "xyzabv");

	findLongestCommonSubString("axab", "ab");
	findLongestCommonSubString("abxc", "aab");
	findLongestCommonSubString("123zzzz5123456zz", "q523zGeGe123456sdfsd2");	// 4,056,303,536 v 697  -> 6
	findLongestCommonSubString("ab", "xyz");
	findLongestCommonSubString("ab", "xyzabv");
	findLongestCommonSubString("ab", "ab");
	findLongestCommonSubString("cccab", "xyzabv");
	findLongestCommonSubString("abxxxkfc", "abvvkfc");
	findLongestCommonSubString("abcdxyz", "xyzabcd");
	findLongestCommonSubString("", "dabz");
	findLongestCommonSubString("t", "xyz");
	findLongestCommonSubString("01111", "10101");

	findMDI("abc", "fbc");
	findMDI("abdca", "cbda");
	findMDI("passport", "ppsspt");
	findMDI("heap", "pea");
	findMDI("geeksforgeeks", "geeks");
	findMDI("sea", "eat");
	findMDI("leetcode", "etco");*/

	lengthOfLIS({ 4,10,4,5,6,8 });
	lengthOfLIS({ 4,5,4,8,9 });
	lengthOfLIS({ 2,7,3,4,5 });
	lengthOfLIS({ 10,9,2,5,3,7,101,18 });
	lengthOfLIS({ 0,1,0,3,2,3 });
	lengthOfLIS({ 7,7,7,7,7,7,7 });
	lengthOfLIS({ 4,2,3,6,10,1,12 });
	lengthOfLIS({ -4,10,3,7,15 });
	lengthOfLIS({ 10, 22, 9, 33, 21, 50, 41, 60, 80 });
	lengthOfLIS({ 3, 10, 2, 1, 20 });
	lengthOfLIS({ 3, 2 });
	lengthOfLIS({ 50, 3, 10, 7, 40, 80 });
	lengthOfLIS({ 4,10,4,3,8,9 });

	/*
	* https://leetcode.com/problems/longest-common-subpath/
	* https://leetcode.com/problems/shortest-common-supersequence/
	* https://leetcode.com/problems/minimum-ascii-delete-sum-for-two-strings/
	* https://leetcode.com/problems/maximize-number-of-subsequences-in-a-string/
	* https://leetcode.com/problems/edit-distance/
	* https://leetcode.com/problems/russian-doll-envelopes/
	* https://leetcode.com/problems/maximum-length-of-pair-chain/
	* https://leetcode.com/problems/minimum-number-of-removals-to-make-mountain-array/
	* https://leetcode.com/problems/find-the-longest-valid-obstacle-course-at-each-position/
	* https://leetcode.com/problems/longest-ideal-subsequence/
	* https://leetcode.com/problems/shortest-common-supersequence/
	* https://leetcode.com/problems/maximize-number-of-subsequences-in-a-string/submissions/
	* 
	* https://leetcode.com/problems/longest-increasing-subsequence-ii/
	* https://leetcode.com/problems/number-of-longest-increasing-subsequence/
	*/
}