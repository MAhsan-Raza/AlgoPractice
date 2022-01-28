#pragma once

vector<int> missingNumInUnSortedWDups(vector<int> nums)
{
    vector<int> res;
    int next = nums[0];
    int offset = 0;
    for (size_t i = 0; i < nums.size(); i++)
    {
        size_t pos = next - 1;
        int tmp = nums[pos + offset];
        if (tmp == next)
            ++offset;
        nums[pos + offset] = next;
        next = tmp;
    }
    return res;
}

void swapInVec(const int i, const int j, vector<int>& nums)
{
    const int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

inline void CyclicSort(vector<int>& nums)
{
    for (size_t i = 0; i < nums.size(); i++)
    {
        while (i + 1 != nums[i])
            swapInVec(i, nums[i] - 1, nums);
    }
}

inline void CyclicSortWithDuplicates(vector<int>& nums)
{
    for (size_t i = 0; i < nums.size(); i++)
    {
        while (i != nums[i] - 1)
        {
            int nxtIndx = nums[i] - 1;
            if (nums[i] == nums[nxtIndx])
                break;
            swapInVec(i, nxtIndx, nums);
        }
    }
}

inline void CyclicSortWithDuplicatesIgnoreLsrOne(vector<int>& nums)
{
    for (size_t i = 0; i < nums.size(); i++)
    {
        while (i != nums[i] - 1)
        {
            if (nums[i] <= 0)
                break;
            int nxtIndx = nums[i] - 1;
            if (nums[i] == nums[nxtIndx])
                break;
            swapInVec(i, nxtIndx, nums);
        }
    }
}

vector<int> findMissingInRange(vector<int>& nums)
{
    vector<int> res;
    CyclicSortWithDuplicates(nums);
    for (size_t i = 0; i < nums.size(); i++)
    {
        if (i + 1 != nums[i])
            res.push_back(i + 1);
    }
    return res;
}

int firstMissingPositive(const vector<int>& nums)
{
    unordered_set<int> ht;
    int nmax = 0;
    std::for_each(nums.begin(), nums.end(), 
        [&ht, &nmax](const int x) 
        {
            if (x >= 1)
            {
                ht.insert(x);
                nmax = max(nmax, x);
            }
        }
    );
    int i = 1;
    for (; i <= nmax + 1; i++)
    {
        if (ht.find(i) == ht.end())
            break;
    }
    return i;
}

inline vector<int> findDuplicates(vector<int>& nums)
{
    unordered_set<int> res;

    for (size_t i = 0; i < nums.size(); i++)
    {
        while (i != nums[i] - 1)
        {
            int nxtIndx = nums[i] - 1;
            if (nums[i] == nums[nxtIndx])
            {
                res.insert(nums[i]);
                break;
            }
            swapInVec(i, nxtIndx, nums);
        }
    }

    return vector<int>(res.begin(), res.end());
}

int findMissingPositive(vector<int> arr)
{
    int i;
    for (i = 0; i < arr.size(); i++) {
        if (abs(arr[i]) - 1 < arr.size() && arr[abs(arr[i]) - 1] > 0)
            arr[abs(arr[i]) - 1] = -arr[abs(arr[i]) - 1];
    }
    for (i = 0; i < arr.size(); i++)
        if (arr[i] > 0)
            return i + 1;

    return arr.size() + 1;
}

void testCyclicSort()
{
    /*missingNumInUnSortedWDups({4,3,2,7,8,2,3,1});
    vector<int> x = { 2,6,4,3,1,5 };
    CyclicSort(x);
    CyclicSortWithDuplicates(x);
    vector<int> x = { 4,3,2,7,8,2,3,1 };
    auto y = findMissingInRange(x);
    x = { 1,1 };
    y = findMissingInRange(x);
    firstMissingPositive({ 7,8,9,11,12 });
    firstMissingPositive({ 1,2,0 });
    firstMissingPositive({ 3,4,-1,1 });*//*
    vector<int> x = { 7,8,9,11,12 };
    CyclicSortWithDuplicatesIgnoreLsrOne(x);
    x = { 3,4,-1,1 };
    CyclicSortWithDuplicatesIgnoreLsrOne(x);
    vector<int> x = {1,1,2};
    auto y = findDuplicates(x);*/
    //vector<int> x =;
    findMissingPositive({ 7,8,9,11,12 });
    findMissingPositive({ 1,1,2 });
}
