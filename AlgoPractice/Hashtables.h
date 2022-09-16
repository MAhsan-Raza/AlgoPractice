#pragma once


bool PairSum(const vector<int>& nums, const int k)
{}

vector<vector<int>> AllPairSum(const vector<int>& nums, const int k)
{}

int CountSubarraysEqualSum(const vector<int>& nums, const int k)
{
    int nCount = 0;
    unordered_map<int, int> preFxSMap; // Prefix sums vs occurance count
    int crntSum = 0;

    for (int i = 0; i < nums.size(); i++)
    {
        crntSum += nums[i];
        if (crntSum == k)
            ++nCount;
        nCount += preFxSMap[crntSum - k];
        ++preFxSMap[crntSum];
    }

    return nCount;
}

vector<vector<int>> AllSubarraysEqualSum(const vector<int>& nums, const int k)
{}

void testHashtables()
{
    /*
    * https://leetcode.com/problems/continuous-subarray-sum/
    * https://leetcode.com/problems/subarray-sums-divisible-by-k/
    * https://leetcode.com/problems/minimum-operations-to-reduce-x-to-zero/
    * https://leetcode.com/problems/k-radius-subarray-averages/
    * https://leetcode.com/problems/maximum-sum-score-of-array/
    */
}
