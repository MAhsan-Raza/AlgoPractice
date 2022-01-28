#pragma once

class Knapsack 
{
public:

	int GetKnapsackProfit_BruteForce(const vector<int>& profits, const vector<int>& weights, const int capacity, const int index = 0) 
	{
		if (capacity <= 0 || index == profits.size())
			return 0;

		int profit1 = 0;
		if (weights[index] <= capacity)
			profit1 = profits[index] + GetKnapsackProfit_BruteForce(profits, weights, capacity - weights[index], index + 1);

		int profit2 = GetKnapsackProfit_BruteForce(profits, weights, capacity, index + 1);

		return max(profit1, profit2);
	}
};

void PrintVec(const vector<int>& vec)
{
	int sum = 0;
	for (auto x : vec)
	{
		sum += x;
		cout << x << " ";
	}
	cout << " = " << sum << endl;
}
//Not printing itself i.e. the target
vector<vector<int>> GetAllCombinationsSumsToTarget(const int target)
{
	vector<vector<int>> res;
	vector<int> tmp;

	for (size_t i = 1; i < target; i++)
	{
		for (size_t j = i; j < target; j++)
		{
			int sum = i;
			tmp.clear();
			tmp.push_back(i);
			while (sum < target)
			{
				sum += j;
				tmp.push_back(j);
			}

			if (sum == target)
				res.push_back(tmp);
		}
	}

	return res;
}

using Matrix = vector<vector<int>>;

//Correct one
void CombinationsUptoSum(const int crnt, const int num, int tsum, vector<int>& subres, Matrix& combs)
{
	if (tsum == num)
	{
		combs.push_back(vector<int>(subres.begin(), subres.end()));
	}
	else
	{
		for (int i = crnt; tsum + i <= num; i++)
		{
			subres.push_back(i);
			CombinationsUptoSum(i, num, tsum + i, subres, combs);
			subres.pop_back();
		}
	}
}

void CombinationsUptoSum(const int num) {
	Matrix combs;
	vector<int> subres;

	CombinationsUptoSum(1, num, 0, subres, combs);

	for (const auto& x : combs)
		PrintVec(x);
}

void CombinationsUptoSumArray(const vector<int>& arr, int target,
							size_t i, vector<int>& subarr, Matrix& combs)
{
	if (0 == target)
	{
		combs.emplace_back(subarr.begin(), subarr.end());
	}
	else
	{
		for (; i < arr.size() && 0 <= target - arr[i]; i++)
		{
			subarr.push_back(arr[i]);
			CombinationsUptoSumArray(arr, target - arr[i], i, subarr, combs);
			subarr.pop_back();
		}
	}
}

void CombinationUptoSumArray(const vector<int>& arr, const int target)
{
	Matrix combs;
	vector<int> subres;

	CombinationsUptoSumArray(arr, target, 0, subres, combs);

	for (const auto& x : combs)
		PrintVec(x);
}

// No duplicate combinations & Each number in candidates may only be used once in the combination.
void CombinationsUptoSumArray2(const vector<int>& arr, const int target,
								int index, vector<int>& subsres, vector<vector<int>>& res)
{
	if (0 == target)
	{
		res.push_back(subsres);
	}
	else
	{
		for (; index < arr.size() && target - arr[index] >= 0; index++)
		{
			subsres.push_back(arr[index]);
			CombinationsUptoSumArray2(arr, target - arr[index], index + 1, subsres, res);
			subsres.pop_back();

			while (index < arr.size() - 1 && arr[index + 1] == arr[index])
				++index;
		}
	}
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
	vector<vector<int>> res;
	vector<int> subres;
	sort(candidates.begin(), candidates.end());
	CombinationsUptoSumArray2(candidates, target, 0, subres, res);
	
	for (const auto& x : res)
		PrintVec(x);
	return res;
}

void CombsAndPermuts() 
{
	/*vector<int> profits = {1, 6, 10, 16};
	vector<int> weights = { 1, 3, 3, 5 };

	cout << "Profit(C=7) :- " << Knapsack().GetKnapsackProfit_BruteForce(profits, weights, 7) << endl;
	cout << "Profit(C=6) :- " << Knapsack().GetKnapsackProfit_BruteForce(profits, weights, 6) << endl;
	cout << "Profit(C=8) :- " << Knapsack().GetKnapsackProfit_BruteForce(profits, weights, 8) << endl;

	GetAllCombinationsSumsToTarget(5);
	CombinationUptoSumArray({ 2,3,6,7 }, 7);
	CombinationUptoSumArray({ 2, 3, 5 }, 8);*/
	/*vector<int> x = { 10,1,2,7,6,1,5 };
	combinationSum2(x, 8);
	vector<int> x = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	combinationSum2(x, 30);*/
	vector<int> x = { 2,5,2,1,2 };
	combinationSum2(x, 7);
}