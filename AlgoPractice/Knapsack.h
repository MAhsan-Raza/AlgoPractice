#pragma once
#include "BTreeDFS.h"

int FruitBasket(const vector<int>& weights, const vector<int>& profits, const int capacity)
{
	int REC_CALLS_NODPRO = 0;
	function<void(const int, const int, const int, int&)> getMaxPOld = [&](const int indx, const int profit, const int weight, int& maxProfit)
	{
		++REC_CALLS_NODPRO;

		if (indx == weights.size() || weight > capacity)
		{
			maxProfit = max(maxProfit, (weight > capacity) ? profit - profits[indx - 1] : profit);
		}
		else
		{
			getMaxPOld(indx + 1, profit + profits[indx], weight + weights[indx], maxProfit);
			getMaxPOld(indx + 1, profit , weight , maxProfit);
		}
	};

	int REC_CALLS = 0;
	//vector<vector<int>> memoTbl(weights.size(), vector(capacity + 1, -1));
	unordered_map<pair<int, int>, int, HashPair<int>> memoTbl;
	function<int(const int, const int, const int)> getMaxP = [&](const int indx, const int profit, const int crntCap)->int
	{
		++REC_CALLS;

		if (0 > crntCap)
			return 0;
		else if (indx == weights.size())
			return profit;
		
		auto itr = memoTbl.find(make_pair(indx, crntCap));
		if (itr != memoTbl.end())
			return itr->second;
		//if (memoTbl[indx][crntCap] != -1)
			//return memoTbl[indx][crntCap];

		int crntMaxP = 
			max(
				getMaxP(indx + 1, profit + profits[indx], crntCap - weights[indx]),
				getMaxP(indx + 1, profit, crntCap)
			);
		//memoTbl[indx][crntCap] = crntMaxP;
		memoTbl[make_pair(indx, crntCap)] = crntMaxP;
		return crntMaxP;
	};

	int maxRes = 0;
	getMaxPOld(0, 0, 0, maxRes);

	return getMaxP(0, 0, capacity);
}

// Can partition the whole array into two subsets having equal SUM
bool canPartition(const vector<int>& nums)
{
	int RCV_CLS = 0;
	int CAC_HIT = 0;

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
bool hasSubsetEqualTargetSum(const vector<int>& num, int sum)
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


// For positive numbers only, if we want to include negatives we will have to apply Divide & Conqour's Meet-in-Middle technique
int minimumDifference(const vector<int>& nums)
{
	//int REV_CALLS = 0;
	// get half sum
	long ArrSum = 0;
	for (int i = 0; i < nums.size(); i++)    ArrSum += nums[i];
	long halfSum = ArrSum / 2;

	//memo
	vector<vector<long>> memChc(nums.size(), vector<long>(ArrSum + 1, -1));

	// iterate all subset & take one with min abs diff from the half of sum
	function<int(int, long)> GetCloserToTarget = [&](int indx, long crntSum)->int
	{
		//++REV_CALLS;
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

	minimumDifference({ 2,3,1,4,20,30,10,40,99,91,71,55,5,6,7 });
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
	*/
}
