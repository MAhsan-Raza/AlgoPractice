#pragma once
#include "BTreeDFS.h"

int fibOfN(int N) {
    //return (n <= 2) ? (n <= 0) ? 0 : 1 : fib(n-1) + fib(n-2);

    vector<int> memTbl(N + 1, -1);

    // Top Down Approach - Memoaisation
    /*function<int(int)> fibLM = [&](const int n)->int
    {
        if(n < 2)               return memTbl[n] = n;
        if(memTbl[n] != -1)     return memTbl[n];

        return (memTbl[n] = fibLM(n-1) + fibLM(n-2));
    };

    return fibLM(N);*/

    // Bottom UP Approach - Tablaization
    if (N == 0)  return 0;
    memTbl[0] = 0;
    memTbl[1] = 1;
    for (int i = 2; i <= N; i++)
        memTbl[i] = memTbl[i - 1] + memTbl[i - 2];
    return memTbl[N];
}


int PizzaLove(const vector<int>& pzs)
{
	vector<int> memoTbl(pzs.size() + 1, -1);
	function<int(int)> pizzaLoveForever = [&](const int indx)->int
	{
		if (indx >= pzs.size())			return 0;
		if (memoTbl[indx] != -1)		return memoTbl[indx];

		int pckd = pzs[indx] + pizzaLoveForever(indx + 2);
		int skpd = pizzaLoveForever(indx + 1);

		return memoTbl[indx] = max(pckd, skpd);
	};

	return pizzaLoveForever(0);
}

int maxLoot(const vector<int>& hval, int n, vector<int>& dp) {

	// base case
	if (n < 0) {
		return 0;
	}

	if (n == 0) {
		return hval[0];
	}
	// If the subproblem is already solved
	// then return its value
	if (dp[n] != -1) {
		return dp[n];
	}

	/*//if current element is pick then previous cannot be picked
	int pick = hval[n] + maxLoot(hval, n - 2, dp);*/
	//if current element is not picked then previous element is picked
	int notPick = maxLoot(hval, n - 1, dp);

	//if current element is pick then previous cannot be picked
	int pick = hval[n] + maxLoot(hval, n - 2, dp);

	// return max of picked and not picked
	return dp[n] = max(pick, notPick);

}

int robCircular(const vector<int>& nums) {

	vector<int> memChc(nums.size() + 1, -1);
	function<int(int, int)> robLoot = [&](const int indx, const int N)->int
	{
		if (indx >= N)
			return 0;
		if (memChc[indx] != -1)
			return memChc[indx];

		int pckd = nums[indx] + robLoot(indx + 2, N);
		int skpd = robLoot(indx + 1, N);

		return memChc[indx] = max(pckd, skpd);
	};

	if (nums.size() == 1)        return nums.front();

	int pkdX = robLoot(0, nums.size() - 1);
	memChc = vector<int>(nums.size() + 1, -1);
	int skdX = robLoot(1, nums.size());
	return max(pkdX, skdX);
}

// "LeetCode: House Robber 3":- It is not just alternate levels problem, a nephew can be combined with Uncle since they are not directly connected
int robBinaryTree(TreeNode* root)
{
	unordered_map<TreeNode*, int> memChc;
	function<int(TreeNode*)> robMore = [&](TreeNode* crnt)->int
	{
		if (!crnt)               return 0;
		auto x = memChc.find(crnt);
		if (x != memChc.end())
			return x->second;

		int pckd = crnt->val +
			robMore(crnt->left ? crnt->left->left : nullptr) +
			robMore(crnt->left ? crnt->left->right : nullptr) +
			robMore(crnt->right ? crnt->right->left : nullptr) +
			robMore(crnt->right ? crnt->right->right : nullptr);

		int skpd = robMore(crnt->left) + robMore(crnt->right);

		return memChc[crnt] = max(pckd, skpd);
	};

	return robMore(root);
}

int climbStairs(int n)
{
	vector<int> memChc(n + 1, -1);
	function<int(int)> MaxWays = [&](const int n)->int
	{
		if (n == 0)              return 1;
		if (n < 0)               return 0;
		if (memChc[n] != -1)     return memChc[n];

		return memChc[n] = (MaxWays(n - 1) + MaxWays(n - 2) + MaxWays(n - 3));
	};

	return MaxWays(n);
}

int CountWaysToExpressANumber(int n) 
{
	vector<int> memChc(n + 1, -1);
	function<int(int)> getWaysNum = [&memChc, &getWaysNum](const int remN)->int
	{
		if (remN == 0)				return 1;	//Base Case:- Success
		if (remN < 0	)			return 0;	//Base Case: Fail
		if (memChc[remN] != -1)		return memChc[remN];	//Cache Hit

		return getWaysNum(remN - 1) + getWaysNum(remN - 3) + getWaysNum(remN - 4);
	};

	return getWaysNum(n);
}

void testFib_DynoPro()
{
	/*PizzaLove({2,7,9,3,1});
	PizzaLove({ 1,2,3,4,5 });
	PizzaLove({ 10,2,3,50 });
	PizzaLove({ 5,3,4,11,2 });

	PizzaLove({ 1,1,1 });
	PizzaLove({ 1,2,1,1 });
	PizzaLove({ 1,1,2,1 });
	PizzaLove({ 1,3,20,1 });
	PizzaLove({ 5,4,3,2,1 });

	vector<int> dp(5, -1);
	//maxLoot({ 1,3,20,1 }, 3, dp);
	maxLoot({ 5,4,3,2,1 }, 3, dp); 

		robCircular({ 2,7,9,3,1 });
	robCircular({ 200,3,140,20,10 });
	robCircular({ 1,3,1,3,100 });
	robCircular({ 100,3,1,300,100 });
	robCircular({ 2,3,2 });
	robCircular({ 2,2,2,1 });*/

	climbStairs(2);
	climbStairs(3);
	climbStairs(4);

	CountWaysToExpressANumber(4);
	CountWaysToExpressANumber(5);

	/*
	* https://www.geeksforgeeks.org/maximum-product-cutting-dp-36/
	* https://leetcode.com/problems/jump-game/
	* https://leetcode.com/problems/jump-game-ii/
	* https://leetcode.com/problems/minimum-jumps-to-reach-home/
	*/
}