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
    /*int KhaliPlot = 1;

    for (size_t i = 2; i < arr.size(); i++)
    {
        if(arr[i] != arr[KhaliPlot - 1])
        { 
            if (i != KhaliPlot)
                arr[KhaliPlot] = arr[i];
            ++KhaliPlot;
        }
    }

    return KhaliPlot;*/

    int p1 = 1, p2 = 1;

    for (; p2 < arr.size(); p2++)
    {
        if (arr[p2] == arr[p2 - 1])
            continue;

        arr[p1++] = arr[p2];
    }

    return p1;
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

class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums)
    {
        if (nums.empty())    return nums;
        vector<int> res;
        res.reserve(nums.size());

        auto GetStrtIndx = [&nums]()->int {
            int i = 0;
            while (i < nums.size() && nums[i] <= 0)    ++i;
            return i - 1;
        };

        auto MakeAMove = [&nums, &res](int& li, int& ri)->int {
            if (li >= 0 && ri < nums.size())
            {
                return std::abs(nums[li]) < std::abs(nums[ri]) ? li-- : ri++;
            }
            else if (li >= 0)
                return li--;
            else if (ri < nums.size())
                return ri++;

            return -1;
        };

        int lItr, rItr, selIndx;
        lItr = rItr = GetStrtIndx();

        while ((selIndx = MakeAMove(lItr, rItr)) != -1)
        {
            res.push_back(std::pow(nums[selIndx], 2));
        }
        return std::move(res);
    }
};

// solving using sorting & 2pointer approach
/*inline vector<vector<int>> threeSumToZero(vector<int>& nums)
{
    vector<vector<int>> res;
    if (nums.empty())    return res;
    const int Target = 0;
    vector<bool> SkipList(nums.size(), false);

    auto TwoSum = [&nums, &SkipList](const int SubTarget, const int actualLeft, vector<int>& resLine) {
        int left = 0, right = nums.size() - 1;

        while (left < right)
        {
            if (left == actualLeft)
            {
                ++left;
                continue;
            }
            else if (right == actualLeft)
            {
                --right;
                continue;
            }

            const int SubSum = nums[left] + nums[right];
            if (SubSum == SubTarget)
            {
                SkipList[left] = SkipList[right] = true;
                resLine.push_back(nums[left]);
                resLine.push_back(nums[right]);
                return;
            }
            else if (SubSum > SubTarget)
                --right;
            else
                ++left;
        }
    };

    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++)
    {
        if (SkipList[i])     continue;
        if(i > 0 && nums[i] == nums[i-1])   continue;

        const int SubTarget = Target - nums[i];
        vector<int> resLine;
        TwoSum(SubTarget, i, resLine);
        if (resLine.size() == 2)
        {
            resLine.push_back(nums[i]);
            res.emplace_back(resLine);
        }
    }

    return res;
}*/

inline vector<vector<int>> threeSumToZero(vector<int>& nums)
{
    const int Target = 0;
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    int left, right;

    for (int i = 0; i < nums.size() - 2; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])   continue;

        const int SubTarget = Target - nums[i];

        left = i + 1;
        right = nums.size() - 1;

        while (left < right)
        {
            const int TwoSum = nums[left] + nums[right];
            if (TwoSum < SubTarget)
                ++left;
            else if (TwoSum > SubTarget)
                --right;
            else
            {
                res.push_back({ nums[i], nums[left], nums[right] });
                ++left; --right;
            }

            while (left < right && nums[left] == nums[left + 1])
                ++left;
            while (right > left && nums[right] == nums[right - 1])
                --right;
        }
    }

    return move(res);
}

int threeSumClosest(vector<int>& nums, int target) 
{
    int left, right;
    int minSum = INT_MAX, minDist = INT_MAX;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 2; i++)
    {
        const int SubTar = target - nums[i];
        left = i + 1;
        right = nums.size() - 1;

        while (left < right)
        {
            const int TSum = nums[left] + nums[right];
            const int TripleSum = nums[i] + TSum;
            const int TDist = abs(target - TripleSum);
            if (TDist < minDist)
            {
                minDist = TDist;
                minSum = TripleSum;
            }
            else if (TDist == minDist)
                minSum = min(minSum, TripleSum);

            if (TSum > SubTar)
                --right;
            else if (TSum < SubTar)
                ++left;
            else return target;
        }
    }
    return minSum;
}

int MaxTwoSumSamallerThanTarget(vector<int>& nums, int target)
{
    int maxSum = -1;
    sort(nums.begin(), nums.end());

    int left = 0;
    int right = nums.size() - 1;

    while (left < right)
    {
        const int TSum = nums[left] + nums[right];

        if (TSum >= target)
            --right;
        else
        {
            maxSum = max(TSum, maxSum);
            ++left;
        }
    }
    return maxSum;
}

int CountTripletswithSmallerSum(vector<int> nums, int target)
{
    int nTPz = 0;
    sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size() - 2; i++)
    {
        int left = i + 1;
        int right = nums.size() - 1;
        const int SubTar = target - nums[i];

        while (left < right)
        {
            const int TSum = nums[left] + nums[right];
            if (TSum >= SubTar)
                --right;
            else
            {
                /*
                * Since we have a sorted array & we found a value at 'right' for which a sum with value at 'Left' will smaller than SubTar
                * Therefore the pair sum of all the element below the 'right' upto 'left' will also have smaller than the SubTar
                * including the current one so we are saved from back-iterating
                */
                nTPz += right - left;
                ++left;
            }
        }
    }

    return nTPz;
}

vector<vector<int>> GetTripletswithSmallerSum(vector<int> nums, int target)
{
    vector<vector<int>> res;
    return res;
}

// Very slow while using the 2ptr approach, we should use sliding window
int numSubarrayProductLessThanK_2Ptr(vector<int>& nums, int k)
{
    int nMulPirs = 0;
    //std::sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++)
    {
        int j = i + 1;
        int mulPir = 1;

        while (nums[i] * mulPir < k)
        {
            ++nMulPirs;

            if (j < nums.size())
                mulPir *= nums[j++];
            else    break;
        }
    }
    return nMulPirs;
}

// The sliding window approach
int numSubarrayProductLessThanK_wrong(vector<int>& nums, int k)
{
    int wStart = 0, wEnd = 0;
    int subPro = 1, nPrds = 0;

    // for full array
        // add new element at wEnd
        // while condition not matches
            // remove element at wStart from window
        // here we have condition satisfied & optimal result for this window
        // update the main-result

    for (; wEnd < nums.size(); wEnd++)
    {
        if(nums[wEnd] != 1)
            subPro *= nums[wEnd];

        while (subPro >= k && wStart <= wEnd)
        {
            const int vStart = nums[wStart];
            if(vStart < k) // or wStart < wEnd-1
                ++nPrds;

            if(vStart != 1)
                subPro /= vStart;
            ++wStart;
        }

        if (wStart <= wEnd)
            ++nPrds;
    }

    while (wStart < wEnd)
    {
        ++nPrds;    ++wStart;
    }

    return nPrds;
}

// Solved with sliding window since it IS a sliding window problem
int numSubarrayProductLessThanK(const vector<int>& nums, int k)
{
    int nSSPanserDivisions = 0, crntPrdc = 1;
    int wStart = 0, wEnd = 0;

    for (; wEnd < nums.size(); wEnd++)
    {
        crntPrdc *= nums[wEnd];

        while (crntPrdc >= k)
        {
            crntPrdc /= nums[wStart];
            if (wStart++ == wEnd)
                break;
        }

        nSSPanserDivisions += (wEnd - wStart + 1);
    }

    return nSSPanserDivisions;
}

vector<vector<int>> findSubarrays_ProductLessThanK(const vector<int>& arr, int target)
{
    vector<vector<int>> res;
    int wStart = 0, wEnd = 0, crntPrdc = 1;
    auto GetCombinations = [&]()
    {
        for (int wCrnt = wEnd; wCrnt >= wStart; wCrnt--)
        {
            res.emplace_back(vector<int>(arr.begin() + wCrnt, arr.begin() + wEnd + 1));
        }
    };

    for (; wEnd < arr.size(); wEnd++)
    {
        crntPrdc *= arr[wEnd];

        while (crntPrdc >= target)
        {
            crntPrdc /= arr[wStart];
            if (wStart++ == wEnd)
                break;
        }

        GetCombinations();
    }

    return res;
}

void DutchNationalFlag(vector<int>& nums)
{
    auto SortByDigit = [&nums](const int digi, int& startPos)
    {
        for (int crntPos = startPos; crntPos < nums.size(); crntPos++)
        {
            if (nums[crntPos] == digi)
            {
                int tmp = nums[startPos];
                nums[startPos] = nums[crntPos];
                nums[crntPos] = tmp;
                ++startPos;
            }
        }
    };

    int crntPos = 0;
    SortByDigit(0, crntPos);
    SortByDigit(1, crntPos);
}

vector<vector<int>> fourSum(vector<int>& nums, int target) 
{
    vector<vector<int>> res;

    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < nums.size(); i++)
    {
        int subTar = target - nums[i];
        for (int j = i + 1; j < nums.size(); j++)
        {
            int subTarJr = subTar - nums[j];

            int left = j + 1, right = nums.size() - 1;

            while (left < right)
            {
                int tmpSum = nums[left] + nums[right];

                if (tmpSum < subTarJr)          ++left;
                else if (tmpSum > subTarJr)     --right;
                else                            
                    res.push_back({ nums[i], nums[j], nums[left++], nums[right--] });
            }
        }
    }

    return res;
}

//can have a valid PALI after removing just one char?
bool validPalindrome(string s)
{
    int left = 0;
    int right = s.size() - 1;

    function<bool(int, int)> IsSubPalinm = [&s](int l, int r)->bool
    {
        while (l < r)
        {
            if (s[l++] != s[r--])
                return false;
        }
        return true;
    };

    while (left < right)
    {
        if (s[left] != s[right])
            return IsSubPalinm(left + 1, right) || IsSubPalinm(left, right - 1);

        ++left;
        --right;
    }
    return true;
}

void testTwoPointers()
{
    vector<int> vec = { 1,2,3,3,4,4,4,10,20,20,99 };
    /*auto x = TargetSumTwoPtr({1, 2, 3, 4, 7}, 6);
    //                  0,1,2,3,4,5,6,7, 8, 9, 10    
    RemoveDuplicates(vec);

    *//*auto x = SquareOfSortedArray({-3,-1,0,1,2});
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
    ConsecutiveSubsequencesOfThree(arr);

    Solution s;
    vector<int> v = { -4,-1,0,3,10 };
    s.sortedSquares(v);

    vector<vector<int>> vVec;
    //v = { 1,2,-2,-1 };
    v = { -1,0,1,2,-1,-4 };
    vVec = threeSumToZero(v);

    vec = { -1,2,1,-4 };
    threeSumClosest(vec, 1);
    vec = { 0,0,0 };
    threeSumClosest(vec, 1);
    vec = { -2, 0, 1, 2 };
    threeSumClosest(vec, 2);
    vec = { -3, -1, 1, 2 };
    threeSumClosest(vec, 1);
    vec = { 1, 0, 1, 1 };
    threeSumClosest(vec, 100);
    vec = { 1, 2, 3, 4, -5 };
    threeSumClosest(vec, 10);
    vec = { 1, 1, 1, 0 };
    threeSumClosest(vec, -100);

    vec = { 30, 20, 50 };
    MaxTwoSumSamallerThanTarget(vec, 70);
    vec = { 5, 20, 110, 100, 10 };
    MaxTwoSumSamallerThanTarget(vec, 85);
    vec = { 34,23,1,24,75,33,54,8 };
    MaxTwoSumSamallerThanTarget(vec, 60);
    vec = { 10,20,30 };
    MaxTwoSumSamallerThanTarget(vec, 15);

    vec = { 5, 1, 3, 4, 7 };
    CountTripletswithSmallerSum(vec, 12);
    vec = { -1, 4, 2, 1, 3 };
    CountTripletswithSmallerSum(vec, 5);
    vec = { -2,0,1,3 };
    CountTripletswithSmallerSum(vec, 2);

    vec = { 10,5,2,6 };
    numSubarrayProductLessThanK(vec, 100);//8
    vec = { 1,2,3 };
    numSubarrayProductLessThanK(vec, 0);
    vec = { 2, 5, 3, 10 };
    numSubarrayProductLessThanK(vec, 30);//6
    vec = { 8, 2, 6, 5 };
    numSubarrayProductLessThanK(vec, 50);//7

    vec = { 10,9,10,4,3,8,3,3,6,2,10,10,9,3 };
    numSubarrayProductLessThanK(vec, 19);

    vec = { 10,5,2,6 };
    auto x = findSubarrays_ProductLessThanK(vec, 100);//8
    vec = { 1,2,3 };
    x = findSubarrays_ProductLessThanK(vec, 0);
    vec = { 2, 5, 3, 10 };
    x = findSubarrays_ProductLessThanK(vec, 30);//6
    vec = { 8, 2, 6, 5 };
    x = findSubarrays_ProductLessThanK(vec, 50);//7

    vec = { 10,9,10,4,3,8,3,3,6,2,10,10,9,3 };
    x = findSubarrays_ProductLessThanK(vec, 19);

    vec = { 4, 1, 2, -1, 1, -3 };
    auto x = fourSum(vec, 1);
    vec = { 2, 0, -1, 1, -2, 2 };   // -2 -1 0 1 2 2
    x = fourSum(vec, 2);
    vec = { 1,0,-1,0,-2,2 };
    x = fourSum(vec, 0);
    vec = { 2,2,2,2,2 };
    x = fourSum(vec, 8);*/

    validPalindrome("acxcybycxcxa");
}