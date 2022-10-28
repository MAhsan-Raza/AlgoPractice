#pragma once

/*vector<int> missingNumInUnSortedWDups(vector<int> nums)
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
}*/

void swapInVec(const int src, const int dest, vector<int>& nums)
{
    const int tmp = nums[src];
    nums[src] = nums[dest];
    nums[dest] = tmp;
}

void cyclicSort(vector<int>& nums) 
{
    for (size_t i = 0; i < nums.size(); i++)
    {
        while (i + 1 != nums[i])
            swapInVec(i, nums[i] - 1, nums);
    }
}

int missingNumber(vector<int>& nums)
{
    int lastIndxNegc = 0;
    nums.push_back(-1);

    for (int i = 0; i < nums.size(); i++)
    {
        while (nums[i] != i)
        {
            if (nums[i] == -1)
            {
                lastIndxNegc = i;
                break;
            }

            int nxtIndx = nums[i];
            nums[i] = nums[nxtIndx];
            nums[nxtIndx] = nxtIndx;
        }
    }

    return lastIndxNegc;
}

int findDuplicate(vector<int>& nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        while (i != nums[i] - 1)
        {
            int nextIndx = nums[i] - 1;
            if (nums[i] == nums[nextIndx])
                return nums[i];
            int tmp = nums[nextIndx];
            nums[nextIndx] = nums[i];
            nums[i] = tmp;
        }
    }
    return 0;
}

vector<int> findErrorNums(vector<int>& nums)
{
    vector<int> res;

    for (int i = 0; i < nums.size(); i++)
    {
        while (i != nums[i] - 1)
        {
            int nextIndx = nums[i] - 1;
            if (nums[i] == nums[nextIndx])
            {
                res = { nums[i], i + 1 };
                break;
            }

            int tmp = nums[i];
            nums[i] = nums[nextIndx];
            nums[nextIndx] = tmp;
        }
    }

    return res;
}

inline vector<int> findAllDuplicates(vector<int>& nums)
{
    vector<int> res;

    for (int i = 0; i < nums.size(); i++)
    {
        while (nums[i] - 1 != i)
        {
            if (nums[i] == -1 || nums[i] == -2)
                break;

            int actualIndx = nums[i] - 1;

            if (nums[i] == nums[actualIndx])
            {
                res.push_back(nums[i]);
                nums[i] = nums[actualIndx] = -1;
                break;
            }

            nums[i] = nums[actualIndx];
            nums[actualIndx] = actualIndx + 1;
        }
    }

    return res;

    /*
    if found -2 or -1 on crnt index skip it
    if found -2 or -1 on actual index just swap
    if found dup
        place -1 on both indices
        push it to the res array
        skip that index
    on fwd any item came to that index & find -1 or -2
        place that item in its correct index & put -2 in crnt index
    */
}

// O(N) time, O(1) space, result space doesn't count
inline vector<int> findDisappearedNumbers_CyclicSort(vector<int>& nums)
{
    for (int i = 0; i < nums.size(); i++)
    {
        while (nums[i] - 1 != i)
        {
            int nxtIndx = nums[i] - 1;

            if (nums[i] == nums[nxtIndx])
                nums[i] = -1; // we are not pushing it to res since the array is unsorted & the element at this loc might still be present in some futher index (& that index might be the missing num)
            else
            {
                nums[i] = nums[nxtIndx];
                nums[nxtIndx] = nxtIndx + 1;
            }

            if (nums[i] == -1)
                break; //still not confirmed that this is the missing num
        }
    }

    // now all -1s should be the missing nums

    vector<int> res;
    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == -1)
            res.push_back(i + 1);
    }

    return res;

    /*
        while crntIndx doesnt have the right Val
            try to move the misplaced valu to its correct index ( val - 1 )
            if there is already same num (DUP found)
                set -1 to current index only & leave the other
            else:- swap both values
            if(num[i] == -1)
                break;
    */
}

/*
*  Should O(N) time & O(1) space
*  can have out of bound numbers (negatives, 0 &/or greator then N ) & duplicates
*/
int firstMissingPositive(vector<int>& nums) 
{
    for (int i = 0; i < nums.size(); i++)
    {
        while (nums[i] > 0 && nums[i] < nums.size() && nums[nums[i] - 1] != nums[i]) // The duplicate check covers both b/c when the correct element gets to this index it will prevent further loop too 
        {
            int crntVal = nums[i] ;
            nums[i] = nums[crntVal - 1];
            nums[crntVal - 1] = crntVal;
        }
    }

    for (int i = 0; i < nums.size(); i++)
    {
        if (long(nums[i]) - 1 != i)  // to prevent int overflow
            return i + 1;
    }

    return nums.size() + 1;
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
    auto y = findDuplicates(x);
    //vector<int> x =;
    findMissingPositive({ 7,8,9,11,12 });
    findMissingPositive({ 1,1,2 });*/

    vector<int> x;
    cyclicSort(x = { 8,6,4,2,3,5,7,1 });

    missingNumber(x = { 0, 1 });
    missingNumber(x = { 3, 0, 1 });
    missingNumber(x = { 9,6,4,2,3,5,7,0,1 });

    findDuplicate(x = { 1,3,4,2,2 });
    findDuplicate(x = { 3,1,3,4,2 });

    findErrorNums(x = { 1, 2, 2, 4 });
    findErrorNums(x = {1, 1});
    findErrorNums(x = {3, 2, 2});

    findAllDuplicates(x = { 4,3,2,7,8,2,3,1 });

    findDisappearedNumbers_CyclicSort(x = { 4,3,2,7,8,2,3,1 });

    firstMissingPositive(x = { -1,4,2,1,9,10 });
    firstMissingPositive(x = { -2147483648 });

    /*
    * https://leetcode.com/problems/replace-elements-in-an-array/
    * https://leetcode.com/problems/couples-holding-hands/
    */
}
