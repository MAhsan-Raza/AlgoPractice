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
int need_to_carry(string s1, string s2) {

    const int NPRCL_TYPS = 26;
    vector<int> ht(NPRCL_TYPS, 0);

    for (int i = 0; i < s1.size(); i++)
        ht[s1[i] - 'a'] += 1;

    for (int i = 0; i < s2.size(); i++)
        ht[s2[i] - 'a'] -= 1;

    int count = 0;
    for (int i = 0; i < NPRCL_TYPS; i++)
    {
        if (ht[i] > 0)
            count += ht[i];
        else
            count += abs(ht[i]);
    }

    return count;
}
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
