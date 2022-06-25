#pragma once


pair<int, int> TargetSumTwoPtr(const vector<int>& arr, int targetSum) 
{
    int first = 0;
    int last = arr.size() - 1;

    while (first < last)
    {
        int sum = arr[first] + arr[last];
        if (sum == targetSum)
            break;
        else if (sum < targetSum)
            ++first;
        else
            --last;
    }

    return first <= last ? make_pair(first, last) : make_pair(-1, -1);
}

int RemoveDuplicates(vector<int>& arr)
{
    int KhaliPlot = 1;

    for (size_t i = 2; i < arr.size(); i++)
    {
        if(arr[i] != arr[KhaliPlot - 1])
        { 
            if (i != KhaliPlot)
                arr[KhaliPlot] = arr[i];
            ++KhaliPlot;
        }
    }

    return KhaliPlot;
}

vector<int> SquareOfSortedArray(const vector<int>& arr)
{
    vector<int> res;
    res.reserve(arr.size());

    int fwd = 0;
    int bkd = 0;

    while (arr[fwd++] < 0);
    bkd = fwd - 1;

    while (bkd >= 0 || fwd < arr.size())
    {
        if (bkd >= 0 && fwd < arr.size())
        {
            if(arr[fwd] * arr[fwd] < arr[bkd] * arr[bkd])
            { 
                res.push_back(arr[fwd] * arr[fwd]);
                ++fwd;
            }
            else
            {
                res.push_back(arr[bkd] * arr[bkd]);
                --bkd;
            }
        }
        else if (bkd >= 0)
        {
            res.push_back(arr[bkd] * arr[bkd]);
            --bkd;
        }
        else
        {
            res.push_back(arr[fwd] * arr[fwd]);
            ++fwd;
        }
    }

    return res;
}

vector<vector<int>> TripletSum(vector<int>& arr)
{
    vector<vector<int>> res;

    std::sort(arr.begin(), arr.end());

    for (size_t i = 0; i < arr.size(); i++)
    {
        if (i > 0 && arr[i - 1] == arr[i])
            continue;

        int target = arr[i] * -1;
        int first = i + 1;
        int last = arr.size() - 1;
        while (first <= last)
        {
            int sum = arr[first] + arr[last];

            if (sum == target)
            {
                res.push_back({ arr[i], arr[first], arr[last] });
                --last;
                ++first;
            }
            else if (sum > target)
                --last;
            else
                ++first;
        }
    }
    return res;
}

int RemoveNumbersInPlace(vector<int>& arr, const int target)
{
    int khaliPlot = 0;
    for (size_t i = 0; i < arr.size(); i++)
    {
        if (arr[i] != target)
        {
            if (i != khaliPlot)
                arr[khaliPlot] = arr[i];

            ++khaliPlot;
        }
    }
    return khaliPlot;
}

int DoubleSumCloseToTarget(const vector<int>& arr, const int target)
{
    int start = 0;
    int end = arr.size() - 1;
    int minDist = INT_MAX;
    int minSum = INT_MAX;

    while (start < end)
    {
        int distance = target - (arr[start] + arr[end]);
        bool bPzt = true;
        if (distance < 0)
        {
            distance *= -1;
            bPzt = false;
        }

        if(distance == 0)
        {
            minDist = distance;
            minSum = target;
            break;
        }
        else
        {
            if (distance > minDist)
                return minSum;
            else if (distance == minDist)
                minSum = min(minSum, arr[start] + arr[end]);
            else
            {
                minDist = distance;
                minSum = arr[start] + arr[end];
            }
            (bPzt) ? ++start : --end;
        }
    }

    return minSum;
}

int TripleSumCloseToTarget(const vector<int>& arr, const int target)
{
    int minCloseSum = INT_MAX;
    int minDist = INT_MAX;

    for (size_t i = 0; i < arr.size() - 2; i++)
    {
        if (i > 0 && arr[i] == arr[i - 1])
            continue;

        int dSum = DoubleSumCloseToTarget(std::vector(arr.begin() + i + 1, arr.end()), target - arr[i]);
        int distance = std::abs(target - arr[i] - dSum);

        if (distance < minDist)
        {
            minDist = distance;
            minCloseSum = arr[i] + dSum;
        }
        else if (distance == minDist)
            minCloseSum = std::min(minCloseSum, arr[i] + dSum);
    }

    return minCloseSum;
}

// WRONG APPROACH & WRONG RESULT
bool ConsecutiveSubsequencesOfThree(vector<int>& nums)
{
    unordered_set<int> hSet;

    auto TryGetCSeq = [&](const int i)->bool
    {
        int counter = 1;
        int prev = nums[i];
        int first = nums[i];
        nums[i] = -1;

        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[j] == -1)    continue;

            int diff = nums[j] - prev;
            if (diff == 1)
            {
                prev = nums[j];
                nums[j] = -1;
                if (++counter == 3)
                {
                    if (hSet.find(prev) == hSet.end())
                        hSet.insert(prev);
                    break;
                }
            }
            else if (diff > 1) break;
        }

        if(counter != 3)
        { 
            if (hSet.find(first - 1) != hSet.end())
            {
                hSet.erase(first - 1);
                hSet.insert(prev);
            }
            else return false;
        }

        return true;
    };

    for (int i = 0; i < nums.size(); i++)
    {
        if (nums[i] == -1)                continue;

        if (false == TryGetCSeq(i))  return false;
    }

    return true;
}

void testTwoPointers()
{
    /*auto x = TargetSumTwoPtr({1, 2, 3, 4, 7}, 6);
    //                  0,1,2,3,4,5,6,7, 8, 9, 10
    vector<int> vec = { 1,2,3,3,4,4,4,10,20,20,99 };
    RemoveDuplicates(vec);

    auto x = SquareOfSortedArray({ -3,-1,0,1,2 });
    auto x = SquareOfSortedArray({ -8,-4,-2,-1,0 });
    auto x = SquareOfSortedArray({ 1, 8, 9, 17, 22, 85 });
    auto x = SquareOfSortedArray({ -2,-1,0,2,3 });
    vector<int> vec = { -2,-1,0,2,3 };
    vector<int> vec = { -5, 2, -1, -2, 3 };
    auto x = TripletSum(vec);
    vector<int> vec = { 3,1,87,34,99,11,23,45,34,34 };
    auto x = RemoveNumbersInPlace(vec, 34);
    TripleSumCloseToTarget({ 2, 4, 6, 8, 14 }, 7);
    TripleSumCloseToTarget({ 1, 4, 6, 8, 14 }, 500);
    TripleSumCloseToTarget({ 1, 4, 6, 8, 14 }, 22);
    TripleSumCloseToTarget({ 1, 2, 3, 4, 14 }, 12);
    TripleSumCloseToTarget({ -2,0,1,2 }, 2);

    vector<int> arr = { 1,2,3,3,4,5 };
    ConsecutiveSubsequencesOfThree(arr);
    arr = { 1,2,3,3,4,4,5,5 };
    ConsecutiveSubsequencesOfThree(arr);
    arr = { 1,2,3,4,4,5 };
    ConsecutiveSubsequencesOfThree(arr);
    arr = { 1,2,3,4,6,7,8,9,10,11 };
    ConsecutiveSubsequencesOfThree(arr);*/
}