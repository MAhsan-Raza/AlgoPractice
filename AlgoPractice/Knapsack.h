#pragma once
#include "BTreeDFS.h"

int FruitBasket(const vector<int>& weights, const vector<int>& profits, const int capacity)
{
	vector<vector<int>> memChc(weights.size(), vector(capacity + 1, -1));
	function<int(const int, const int)> getMaxP = [&](const int indx, const int crntCap)->int
	{
		if (indx == weights.size())
			return 0;

		if (memChc[indx][crntCap] == -1)
		{
			if (weights[indx] <= crntCap)
				memChc[indx][crntCap] = profits[indx] + getMaxP(indx + 1, crntCap - weights[indx]);
			memChc[indx][crntCap] = max(memChc[indx][crntCap], getMaxP(indx + 1, crntCap));
		}

		return memChc[indx][crntCap];
	};

	return getMaxP(0, capacity);
}

// Can partition the whole array into two subsets having equal SUM
bool canPartition(const vector<int>& nums)
{
	int RCV_CLS = 0, CAC_HIT = 0;
	int ArrSum = 0;
	for_each(nums.begin(), nums.end(), [&ArrSum](const int x) { ArrSum += x; });

	if (ArrSum % 2 != 0)      return false;

	vector<vector<int>> memChc(nums.size(), vector<int>(ArrSum + 1, -1));
	function<bool(int, int)> HasSubset = [&](const int indx, const int crntSum)->bool
	{
		++RCV_CLS;

		if (crntSum == 0)						return true;
		if (indx >= nums.size() || crntSum < 0)	return false;
		if (memChc[indx][crntSum] != -1) {
			++CAC_HIT;  return memChc[indx][crntSum];
		}

		bool bRes = HasSubset(indx + 1, crntSum);
		//if(crntSum > nums[indx])
			bRes = bRes || HasSubset(indx + 1, crntSum - nums[indx]);
		return memChc[indx][crntSum] = bRes;
	};

	return HasSubset(0, ArrSum / 2);
}


// Constraints:- num.size > 0 AND sum > 0
bool hasSubsetEqualTargetSum_(const vector<int>& num, int sum)
{
	vector<vector<int>> memChc(num.size(), vector<int>(sum + 1, -1));
	function<bool(int, int)> haSsS = [&](const int indx, const int crntSum)->bool
	{
		if (crntSum == 0)						return true;
		if (indx >= num.size() || crntSum < 0)	return false;
		if (memChc[indx][crntSum] != -1)		return memChc[indx][crntSum];

		bool bRes = haSsS(indx + 1, crntSum);
		bRes = bRes || haSsS(indx + 1, crntSum - num[indx]);
		return memChc[indx][crntSum] = bRes;
	};

	return haSsS(0, sum);
}

// Constraints:- num.size > 0 AND sum > 0
bool hasSubsetEqualTargetSum(const vector<int>& nums, const int sum)
{
	vector<vector<int>> memChc(nums.size(), vector<int>(sum + 1, -1));

	function<bool(int, int)> haSsS = [&](const int indx, const int remSum)->bool
	{
		if (indx == nums.size())	
			return false;

		if (memChc[indx][remSum] == -1)
		{
			memChc[indx][remSum] = false;	// Remember that -1 is also a TRUE in C++

			if (remSum == nums[indx])
				memChc[indx][remSum] = true;
			else
			{
				if (remSum > nums[indx])	// If smaller then remSum the both cases are possible but if greater only Skip case is
					memChc[indx][remSum] = haSsS(indx + 1, remSum - nums[indx]);	//Pick

				memChc[indx][remSum] = memChc[indx][remSum] || haSsS(indx + 1, remSum);	// Or Skip
			}
		}

		return memChc[indx][remSum];
	};

	return haSsS(0, sum);
}

/*
	Instead of finding sum Max/Min we will have to check at each branch that
		can we reach the end (make the remTrgt 0) ? then count those branches
	Top/Down same as normal target sum but
	Instead of Pck & Skp, branch on ADD or SUBTRACT
*/
struct HashPairInts
{
	size_t operator()(const pair<int, int>& pr) const
	{
		int h1 = hash<int>{}(pr.first);
		int h2 = hash<int>{}(pr.second);

		return (h1 == h2) ? h1 : h1 ^ h2;
	}
};

/*
You are given an integer array nums and an integer target.

You want to build an expression out of nums by adding one of the symbols '+' and '-' before each integer in nums and then concatenate all the integers.

For example, if nums = [2, 1], you can add a '+' before 2 and a '-' before 1 and concatenate them to build the expression "+2-1".
Return the number of different expressions that you can build, which evaluates to target
*/
inline int findTargetSumWays(const vector<int>& nums, int target)
{
	unordered_map<pair<int, int>, int, HashPairInts> ht;

	function<int(int, int)> getSumWays = [&](const int indx, const int remTrgt)->int
	{
		if (remTrgt == 0 && indx == nums.size())
			return 1;   // Success base condition

		if (indx == nums.size())
			return 0;   // Failure base condition

		auto pr = make_pair(indx, remTrgt);
		auto itr = ht.find(pr);
		if (itr == ht.end())
		{
			// Get sum of all the bellow sub-trees
			int subRes = getSumWays(indx + 1, remTrgt - nums[indx]) + getSumWays(indx + 1, remTrgt + nums[indx]);
			ht.emplace(pr, subRes);
			return subRes;
		}
		else return itr->second;
	};

	return getSumWays(0, target);
}

// For positive numbers only, if we want to include negatives we will have to apply Divide & Conqour's Meet-in-Middle technique
int minimumDifference(const vector<int>& nums)
{
	// get half sum
	long ArrSum = 0;
	for (int i = 0; i < nums.size(); i++)    ArrSum += nums[i];
	long halfSum = ArrSum / 2;

	vector<vector<long>> memChc(nums.size(), vector<long>(ArrSum + 1, -1));

	// iterate all subset & take one with min abs diff from the half of sum
	function<int(int, long)> GetCloserToTarget = [&](int indx, long crntSum)->int
	{
		if (indx >= nums.size())             return crntSum;
		if (memChc[indx][crntSum] != -1)     return memChc[indx][crntSum];

		int pck = GetCloserToTarget(indx + 1, crntSum + nums[indx]);
		int skp = GetCloserToTarget(indx + 1, crntSum);

		if (abs(halfSum - pck) < abs(halfSum - skp))
			return memChc[indx][crntSum] = pck;
		return memChc[indx][crntSum] =  skp;
	};

	// Subtract the selected partition sum from array sum
	long CloserSum = GetCloserToTarget(0, 0);
	long ScndPartSm = ArrSum - CloserSum;
	cout << "ArrSum=" << ArrSum << ", CloserSum=" << CloserSum << ", ScndPartSm=" << ScndPartSm << endl;
	// abs(partitionSum1 - partitionSum2) is result
	return abs(CloserSum - ScndPartSm);
}

int CountSubsetsSumEqualTarget(const vector<int>& arr, const int target)
{
	int REC_CALLS = 0;
	int nSubsets = 0;

	vector<vector<int>> memChc(arr.size(), vector<int>(target + 1, -1));

	function<int(int, int)> countSSs = [&](const int indx, const int crntSum)->int
	{
		++REC_CALLS;
		if (crntSum == target)							return 1;
		if (crntSum > target || indx >= arr.size())		return 0;
		if (memChc[indx][crntSum] != -1)				return memChc[indx][crntSum];

		int nRes = countSSs(indx + 1, crntSum);
		nRes += countSSs(indx + 1, crntSum + arr[indx]);

		return memChc[indx][crntSum] = nRes;
	};

	return countSSs(0, 0);
}

int UnboundedKnapsackMaxProfit(const vector<int>& profits, const vector<int>& weights, const int Capacity)
{
	int REC_CALLS = 0;
	vector<vector<int>> memChc(profits.size(), vector<int>(Capacity + 1, -1));

	function<int(int, int)> maxPft = [&](const int indx, const int remCap)->int
	{
		++REC_CALLS;
		if (remCap <= 0 || indx >= weights.size())				
			return 0;

		if (memChc[indx][remCap] != -1)		return memChc[indx][remCap];
		
		int crntMax = 0;
		if (weights[indx] <= remCap)
			crntMax = profits[indx] + maxPft(indx, remCap - weights[indx]);

		return memChc[indx][remCap] = max(crntMax, maxPft(indx + 1, remCap));
	};

	return maxPft(0, Capacity);
}

int solveRodCutting(const vector<int>& lengths, const vector<int>& prices, const int n) 
{
	int REC_CALLS = 0;
	vector<vector<int>> memChc(lengths.size(), vector<int>(n + 1, -1));

	function<int(int, int)> getMxPrc = [&](const int indx, const int remLen)->int
	{
		++REC_CALLS;
		if (indx == lengths.size() || remLen <= 0)		return 0;
		if (memChc[indx][remLen] != -1)					return memChc[indx][remLen];

		int maxPrc = 0;
		if (lengths[indx] <= remLen)
			maxPrc = prices[indx] + getMxPrc(indx, remLen - lengths[indx]);

		return memChc[indx][remLen] = max(maxPrc, getMxPrc(indx + 1, remLen));
	};

	return getMxPrc(0, n);
}

int countCoinChange(const vector<int>& denominations, int total) 
{
	int REC_CALLS = 0;
	vector<vector<int>> memChc(denominations.size(), vector<int>(total + 1, -1));

	function<int(int, int)> CountCoins = [&](const int indx, const int remTot)->int
	{
		++REC_CALLS;
		if (remTot == 0)								return 1;
		if (indx == denominations.size() || remTot < 0)	return 0;
		if (memChc[indx][remTot] != -1)					return memChc[indx][remTot];

		int sameCoin = 0;
		if (denominations[indx] <= remTot)
			sameCoin = CountCoins(indx, remTot - denominations[indx]);

		int nextCoin = CountCoins(indx + 1, remTot);
		return memChc[indx][remTot] = sameCoin + nextCoin;
	};

	return CountCoins(0, total);
}

int minCoinChange(const vector<int>& coins, int amount) 
{
	int REC_CALLS = 0;
	bool usChc = true;
	vector<vector<int>> memChc(coins.size(), vector<int>(amount + 1, -1));

	function<int(int, int)> getMinCoin = [&](const int indx, const int remAmt)->int
	{
		++REC_CALLS;
		if (remAmt == 0)							return 0;
		if (remAmt < 0 || indx == coins.size())		return INT_MAX;
		if (usChc && memChc[indx][remAmt] != -1)				return memChc[indx][remAmt];

		int sameCoin = INT_MAX;
		if(coins[indx] <= remAmt)
		{ 
			int subBranchSameCoin = getMinCoin(indx, remAmt - coins[indx]);
			sameCoin = (subBranchSameCoin != INT_MAX) ? subBranchSameCoin + 1 : INT_MAX;
		}

		int nextCoin = getMinCoin(indx + 1, remAmt);

		return memChc[indx][remAmt] = min(sameCoin, nextCoin);
	};

	int Result = getMinCoin(0, amount);
	int DYPRO = REC_CALLS;
	REC_CALLS = usChc = 0;
	getMinCoin(0, amount);
	int BRTFC = REC_CALLS;
	return Result;
}

int countRibbonPieces(const vector<int>& ribbonLengths, int total)
{
	vector<vector<int>> memChc(ribbonLengths.size(), vector<int>(total + 1, -1));

	function<int(int, int)> getMaxCuts = [&](const int indx, const int remRbn)->int
	{
		if (remRbn == 0)					return 0;			// Base Case:- Success
		if (ribbonLengths.size() == indx)	return INT_MIN;		// Base Case:- Failed
		if (memChc[indx][remRbn] != -1)		return memChc[indx][remRbn];	// Cahce hit

		int sameLen = INT_MIN;
		if (remRbn >= ribbonLengths[indx])
		{
			int subBrnchSameLen = getMaxCuts(indx, remRbn - ribbonLengths[indx]);
			sameLen = (subBrnchSameLen == INT_MIN) ? INT_MIN : subBrnchSameLen + 1;
		}

		int nextLen = getMaxCuts(indx + 1, remRbn);

		return memChc[indx][remRbn] = max(sameLen, nextLen);
	};

	return getMaxCuts(0, total);
}

int maxProduct_RibbonAnyPieces(int total)
{
	return 0;
}


void testKnapsack() 
{
	/*FruitBasket({ 2,3,1,4,20,30,10,40,99,91,71,55,5,6,7 }, { 4,5,3,7,7,1,2,3,11,7,4,33,2,3,4 }, 5);
	FruitBasket({ 10,20,30 }, { 60,100,120 }, 50);
	FruitBasket({ 1,1,1 }, { 10,20,30 }, 2);
	FruitBasket({ 1,2,3 }, { 10,15,40 }, 2);
	FruitBasket({ 1,2,3 }, { 10,15,40 }, 3);

	canPartition({ 1,5,11,5 });
	canPartition({ 14,9,8,4,3,2 });
	canPartition({ 5,79,2,4,8,16,32,64,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100 });
	
	hasSubsetEqualTargetSum({ 1,5,11,5 }, 10);
	hasSubsetEqualTargetSum({ 14,9,8,4,3,2 }, 11);
	hasSubsetEqualTargetSum({ 1, 2, 3, 7 }, 6);
	hasSubsetEqualTargetSum({ 1, 2, 7, 1, 5 }, 10);
	hasSubsetEqualTargetSum({ 1, 3, 4, 8 }, 6);
	hasSubsetEqualTargetSum({ 3, 34, 4, 12, 5, 2 }, 9);
	hasSubsetEqualTargetSum({ 3, 34, 4, 12, 5, 2 }, 30);

	findTargetSumWays({ 1,1,1,1,1 }, 3);
	findTargetSumWays({ 1 }, 1);
*/
	/*minimumDifference({2,3,1,4,20,30,10,40,99,91,71,55,5,6,7});
	minimumDifference({ 3, 9, 7, 3 });
	//minimumDifference({ 2, -1, 0, 4, -2, -9 });
	minimumDifference({ 1, 2, 3, 9 });
	minimumDifference({ 1, 2, 7, 1, 5 });
	minimumDifference({ 1, 3, 100, 4 });
	minimumDifference({ 1, 6, 11, 5 });

	CountSubsetsSumEqualTarget({ 1,1,2,3,1,1,2,3,1,1,2,3 }, 4);
	CountSubsetsSumEqualTarget({ 1,1,2,2 }, 4);
	CountSubsetsSumEqualTarget({ 1, 2, 7, 1, 5 }, 9);
	CountSubsetsSumEqualTarget({ 1, 2, 3, 3 }, 6);
	CountSubsetsSumEqualTarget({1,1,1,1}, 1);

	UnboundedKnapsackMaxProfit({ 15,20,50 }, { 1,2,3 }, 5);
	UnboundedKnapsackMaxProfit({ 1, 30 }, { 1, 50 }, 100);
	UnboundedKnapsackMaxProfit({ 10, 40, 50, 70 }, { 1, 3, 4, 5 }, 8);

	solveRodCutting({ 1, 2, 3, 4, 5 }, { 2, 6, 7, 10, 13 }, 5);
	solveRodCutting({ 1, 2, 3, 4, 5, 6, 7, 8 }, { 1, 5, 8, 9, 10, 17, 17, 20 }, 8);
	solveRodCutting({ 1, 2, 3, 4, 5, 6, 7, 8 }, { 3, 5, 8, 9, 10, 17, 17, 20 }, 8);	//340 v 101

	countCoinChange({ 1,2,3 }, 5);
	countCoinChange({ 1,2,3 }, 4);
	countCoinChange({ 2,5,3,6 }, 10);

	minCoinChange({ 1,2,3 }, 5);
	minCoinChange({ 1,2,3 }, 3);
	minCoinChange({ 2,5,3,7 }, 10);
	minCoinChange({ 1,2,3 }, 11);
	minCoinChange({ 25, 10, 5 }, 30);
	minCoinChange({ 9, 6, 5, 1 }, 11);
	minCoinChange({ 9, 6, 5, 11 }, 1100);

	countRibbonPieces({ 2,3,5 }, 5);
	countRibbonPieces({ 2,3}, 7);
	countRibbonPieces({ 3,5,7 }, 13);
	countRibbonPieces({1}, 2);
	countRibbonPieces({1,2}, 3);*/


	/*
	* https://leetcode.com/problems/minimum-number-of-operations-to-convert-time/
	* https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/
	* https://leetcode.com/problems/minimum-cost-for-tickets/
	* https://leetcode.com/problems/maximum-value-of-k-coins-from-piles/
	* https://leetcode.com/problems/partition-to-k-equal-sum-subsets/
	* https://leetcode.com/problems/minimize-the-difference-between-target-and-chosen-elements/
	* https://leetcode.com/problems/maximum-number-of-ways-to-partition-an-array/
	* https://leetcode.com/problems/find-subarrays-with-equal-sum/
	* https://leetcode.com/problems/partition-array-into-two-arrays-to-minimize-sum-difference/
	* https://leetcode.com/problems/split-array-with-same-average/
	* https://leetcode.com/problems/tallest-billboard/
	* https://leetcode.com/problems/last-stone-weight-ii/
	* https://leetcode.com/problems/count-subarrays-with-more-ones-than-zeros/
	*/
}
