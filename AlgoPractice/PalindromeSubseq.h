#pragma once


int longestPalindromeSubseq(const string& s)
{
	int COUNT = 0;
	vector<vector<int>> memChc(s.size() + 1, vector<int>(s.size() + 1, -1));
	function<int(int, int)> maxPSS = [&](const int left, const int right)->int
	{
		++COUNT;
		/*if(left == right)				return 1;
		if (memChc[left][right] != -1)	return memChc[left][right];
		if (s[left] == s[right])		return (right - left == 1) ? 2 : 2 + maxPSS(left + 1, right - 1);

		return memChc[left][right] = max(
			maxPSS(left + 1, right),
			maxPSS(left, right - 1)
		);*/

		if (left == right)				
			return 1;
		if(memChc[left][right] == -1)
		{ 
			if (s[left] == s[right])
				memChc[left][right] = (right - left == 1) ? 2 : 2 + maxPSS(left + 1, right - 1);
			else
				memChc[left][right] = max(maxPSS(left + 1, right), maxPSS(left, right - 1));
		}
		return memChc[left][right];
	};

	return s.empty() ? 0 : maxPSS(0, s.size() - 1);
}

int longestPalindromeSubStringLength(const string& s)
{
	vector<vector<int>> memChc(s.size() + 1, vector<int>(s.size() + 1, -1));

	function<int(int, int)> getPSS = [&](const int left, const int right)->int
	{
		if (memChc[left][right] != -1)	
			return memChc[left][right];		// Cache hit

		if (left == right)				
			return 1;						// Last character in the middle is palindrome itself (odd length)
		
		int matchedLen = INT_MIN;
		if (s[left] == s[right])
		{
			if (right - left != 1)			// Even length palindrome
			{
				matchedLen = getPSS(left + 1, right - 1);
				matchedLen = (matchedLen == right - left - 1) ? 2 + matchedLen : matchedLen; // Only include "2 <our len>" when all of the inner char are palindrome too
			}
			else matchedLen = 2;
		}

		return memChc[left][right] = max(
			matchedLen, max(
				getPSS(left + 1, right),
				getPSS(left, right - 1)
			)
		);
	};

	return s.empty() ? 0 : getPSS(0, s.size() - 1);
}

// Not the most optimized solution, worst case when there are many duplicates
string longestPalindromeSubString(const string s)
{
	int COUNT = 0;
	vector<vector<string>> memChc(s.size(), vector<string>(s.size() + 1, ""));

	function<string(int, int)> getLongPSbS = [&](const int left, const int right)->string
	{
		if (left == right)							return string(1, s[left]);

		if (memChc[left][right].empty()) 
		{
				++COUNT;
			string subSMatch;
			if (s[left] == s[right])
			{
				if (right - left == 1)
				{
					subSMatch = string(1, s[left])+ s[right];
				}
				else
				{
					int remLen = right - left - 1;
					string subS = getLongPSbS(left + 1, right - 1);

					if (subS.size() == remLen)
						subS = s[left] + subS + s[right];

					subSMatch = subS;
				}
			}
			string subS1 = getLongPSbS(left + 1, right);
			string subS2 = getLongPSbS(left, right - 1);

			string maxSub12 = (subS1.size() > subS2.size()) ? subS1 : subS2;
			memChc[left][right] = (subSMatch.size() > maxSub12.size()) ? subSMatch : maxSub12;
		}

		return memChc[left][right];
	};

	cout << s << ":- ";
	string res = getLongPSbS(0, s.size() - 1);
	cout << res << endl;
	return res;
}

int countPalindromicSubstrings(string s) 
{
	int nPalindromes = 0;
	vector<vector<int>> memChc(s.size(), vector<int>(s.size(), -1));

	function<int(int, int)> countPSSs = [&](const int left, const int right)->int
	{
		if (memChc[left][right] == -1)
		{
			if (left == right)
				nPalindromes += memChc[left][right] = 1;
			else 
			{
				int matchedPaliLen = INT_MIN;
				if (s[left] == s[right])
				{
					if (right - left == 1)
					{
						nPalindromes++;
						matchedPaliLen = 2;
					}
					else
					{
						int remLen = right - left - 1;
						matchedPaliLen = countPSSs(left + 1, right - 1);
						if (remLen == matchedPaliLen)
						{
							++nPalindromes;
							matchedPaliLen += 2;
						}
					}
				}

				int res1 = max(matchedPaliLen, countPSSs(left + 1, right));
				memChc[left][right] = max(res1, countPSSs(left, right - 1));
			}
		}
		
		return memChc[left][right];
	};

	countPSSs(0, s.size() - 1);
	return nPalindromes;
}

int minDelToMakePalindrome(const string& s)
{
	vector<vector<int>> memChc(s.size(), vector<int>(s.size(), -1));

	function<int(int, int)> largestPaliSubSeq = [&](const int left, const int right)->int
	{
		if(memChc[left][right] == -1)
		{ 
			if (left == right)
				memChc[left][right] = 1;
			else if(s[left] == s[right])
			{ 
				if (right - left == 1)
					memChc[left][right] = 2;
				else
					memChc[left][right] = 2 + largestPaliSubSeq(left + 1, right - 1);
			}
			else
				memChc[left][right] = max(largestPaliSubSeq(left + 1, right), largestPaliSubSeq(left, right - 1));
		}

		return memChc[left][right];
	};

	return s.size() - largestPaliSubSeq(0, s.size() - 1);
}

bool Is_K_Palindrome(const string& s, const int k)
{
	vector<vector<int>> memChc(s.size(), vector<int>(s.size(), -1));

	function<int(int, int)> largestPaliSubSeq = [&](const int left, const int right)->int 
	{
		if (memChc[left][right] == -1)
		{
			if (left == right)
				memChc[left][right] = 1;
			else if (s[left] == s[right])
			{
				if (right - left == 1)
					memChc[left][right] = 2;
				else
					memChc[left][right] = 2 + largestPaliSubSeq(left + 1, right - 1);
			}
			else
				memChc[left][right] = max(largestPaliSubSeq(left + 1, right), largestPaliSubSeq(left, right - 1));
		}

		return memChc[left][right];
	};

	return s.size() - largestPaliSubSeq(0, s.size() - 1) <= k;
}

void testPalindromeSubseq()
{
	/*longestPalindromeSubseq("bxdb");
	longestPalindromeSubseq("GEEKSFORGEEKS"); //1467 v 115 v 112
	longestPalindromeSubseq("BBABCBCAB");
	longestPalindromeSubseq("bbbab");
	longestPalindromeSubseq("cbbd");

	
	* 2046426362
	*	  v
	*     205249	
	longestPalindromeSubseq("euazbipzncptldueeuechubrcourfpftcebikrxhybkymimgvldiwqvkszfycvqyvtiwfckexmowcxztkfyzqovbtmzpxojfofbvwnncajvrvdbvjhcrameamcfmcoxryjukhpljwszknhiypvyskmsujkuggpztltpgoczafmfelahqwjbhxtjmebnymdyxoeodqmvkxittxjnlltmoobsgzdfhismogqfpfhvqnxeuosjqqalvwhsidgiavcatjjgeztrjuoixxxoznklcxolgpuktirmduxdywwlbikaqkqajzbsjvdgjcnbtfksqhquiwnwflkldgdrqrnwmshdpykicozfowmumzeuznolmgjlltypyufpzjpuvucmesnnrwppheizkapovoloneaxpfinaontwtdqsdvzmqlgkdxlbeguackbdkftzbnynmcejtwudocemcfnuzbttcoew");

	longestPalindromeSubseq("AZTXA");
	
	longestPalindromeSubStringLength("AZTXA");
	longestPalindromeSubStringLength("GEEKSFORGEEKS");
	longestPalindromeSubStringLength("GEEKSNSKEZZ");
	longestPalindromeSubStringLength("121");
	longestPalindromeSubStringLength("EKSNSKE");
	longestPalindromeSubStringLength("babad");
	longestPalindromeSubStringLength("cbbd");
	longestPalindromeSubStringLength("113211");
	
	longestPalindromeSubString("AZTXA");
	longestPalindromeSubString("GEEKSFORGEEKS");
	longestPalindromeSubString("GEEKSNSKEZZ");
	longestPalindromeSubString("121");
	longestPalindromeSubString("EKSNSKE");
	longestPalindromeSubString("babad");
	longestPalindromeSubString("cbbd");

	longestPalindromeSubString("forgeeksskeegfor");
	longestPalindromeSubString("geeks");
	longestPalindromeSubString("aacabdkacaa");

	longestPalindromeSubString("aaabbbbbcccccccddddeee");  // 2799227 v 231

	countPalindromicSubstrings("abc");
	countPalindromicSubstrings("aaa");
	countPalindromicSubstrings("abdbca");
	countPalindromicSubstrings("cddpd");
	countPalindromicSubstrings("pqr");

	minDelToMakePalindrome("aebcbda");
	minDelToMakePalindrome("geeksforgeeks");
	minDelToMakePalindrome("abdbca");
	minDelToMakePalindrome("cddpd");
	minDelToMakePalindrome("pqr");*/

	Is_K_Palindrome("abcdecba", 1);
	Is_K_Palindrome("abcdeca", 2);
	Is_K_Palindrome("acdcb", 1);

	/*
	* https://www.geeksforgeeks.org/edit-distance-dp-5/
	* https://leetcode.com/problems/minimum-deletions-to-make-string-balanced/
	* https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/
	* https://leetcode.com/problems/minimum-number-of-moves-to-make-palindrome/
	* https://leetcode.com/problems/construct-k-palindrome-strings/
	* https://leetcode.com/problems/palindrome-partitioning-iv
	*/
}