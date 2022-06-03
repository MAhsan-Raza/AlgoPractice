#pragma once

template <typename T>
int Basic_BSearch(const vector<T>& nums, const T& target)
{
    if (nums.empty())		                                return -1;
    if (target < nums.front() || target > nums.back())		return -1;

    int first = 0;
    int last = nums.size() - 1;

    while (first < last)
    {
        //near max value of first&last can cause an INT overflow
        //int mid = (first + last) / 2;
        int mid = first + (last - first) / 2;

        if (target < nums[mid])
            last = mid - 1;             //if we assign exact mid we will stuck in an infinite loop
        else if (target > nums[mid])
            first = mid + 1;             //if we assign exact mid we will stuck in an infinite loop
        else
            return mid;
    }

    if (target == nums[first])
        return first;

    return -1;
}

template <typename T>
int OrderAgnostic_BinarySearch(const vector<T>& nums, const T& target)
{
    if (nums.empty())		                                return -1;

    int first = 0;
    int last = nums.size() - 1;
    bool isAsc = nums.front() <= nums.back();

    if (isAsc)
    {
        if (target < nums.front() || target > nums.back())
            return -1;
    }
    else
    {
        if (target > nums.front() || target < nums.back())
            return -1;
    }

    auto lFuncIsMoveUp = [&](const int mid) 
    {
        if (isAsc)  return target > nums[mid];
        else        return target < nums[mid];
    };

    while (first < last)
    {
        int mid = first + (last - first) / 2;
        if (lFuncIsMoveUp(mid))
            first = mid + 1;
        else if (target == nums[mid])
            return mid;
        else//Move down
            last = mid - 1;
    }

    if (target == nums[first])
        return first;

    return -1;
}

class ArrayReader 
{
public:
    ArrayReader(const vector<int>& arr) { this->arr = arr; }

    virtual int get(int index) const
    {
        if (index >= arr.size()) {
            return numeric_limits<int>::max();
        }
        return arr[index];
    }

private:
    vector<int> arr;
};

int UnknownSize_BinarySearch(const ArrayReader& infNums, const int target)
{
    int lowestOut = 1;

    // finding lowest index outside of array
    while (infNums.get(lowestOut) != numeric_limits<int>::max())
        lowestOut *= 2;

    // finding last index of the array
    int tL = lowestOut / 2;
    int tR = lowestOut;

    int first = 0;
    int last = 0;

    while (tL < tR)
    {
        int tMid = tL + (tR - tL) / 2;
        if (infNums.get(tMid) == numeric_limits<int>::max())
        {
            tR = tMid - 1;
            if (infNums.get(tR) != numeric_limits<int>::max())
            {
                last = tR;
                break;
            }
        }
        else
        {
            tL = tMid + 1;
            if (infNums.get(tL) == numeric_limits<int>::max())
            {
                last = tMid;
                break;
            }
        }
    }

    // perfomance enhancing safe checks
    if (target < infNums.get(first))    return -1;
    if (target > infNums.get(last))     return -1;
    if (0 == last)                      return infNums.get(0) == target ? 0 : -1;

    // basic binary search
    while (first < last)
    {
        //near max value of first&last can cause an INT overflow
        //int mid = (first + last) / 2;
        int mid = first + (last - first) / 2;

        if (target < infNums.get(mid))
            last = mid - 1;
        else if (target > infNums.get(mid))
            first = mid + 1;
        else
            return mid;
    }

    if (target == infNums.get(first))
        return first;

    return -1;
}

// NOT WORKING ALGO ------>>>>>> WRONG ALGO
int CeilingOfNumber(const vector<int>& nums, const int target)
{
    if (nums.empty())		    return -1;
    if (target < nums.front())  return 0;
    if (target > nums.back())	return -1;

    int first = 0;
    int last = nums.size() - 1;

    while (first < last)
    {
        //near max value of first&last can cause an INT overflow
        //int mid = (first + last) / 2;
        int mid = first + (last - first) / 2;

        if (target < nums[mid])
            last = mid - 1;             //if we assign exact mid we will stuck in an infinite loop
        else if (target > nums[mid])
            first = mid + 1;             //if we assign exact mid we will stuck in an infinite loop
        else
            return mid;
    }

    return first;
}

char GetNextLetterCircular(const vector<char>& ltrs, const char key)
{
    if (ltrs.empty())                               return 0;
    if (key<ltrs.front() || key>ltrs.back())        return ltrs.front();

    size_t left = 0;
    size_t right = ltrs.size() - 1;

    while (left < right)
    {
        size_t mid = left + (right - left) / 2;

        if (ltrs[mid] > key)
        {
            right = mid - 1;
        }
        else if (ltrs[mid] < key)
        {
            left = mid + 1;
        }
        else
        {
            if (mid < ltrs.size() - 1)
                return ltrs[mid + 1];
            else
                ltrs.front();
        }
    }

    if (ltrs[right] <= key)
        return right < ltrs.size() - 1 ? ltrs[right + 1] : ltrs.front();

    return ltrs[right];
}

//If found exact match return it ELSE find floor & ceiling
void FloorAndCeiling(const vector<int>& arr, const int target, int& floor, int& ceil)
{
    if (arr.empty()) { floor = ceil = -1; return; }

    int left = 0;
    int right = arr.size() - 1;
    int mid = 0;

    while (left <= right)
    {
        mid = left + (right - left) / 2;
        if (arr[mid] > target)
        {
            right = mid - 1;
        }
        else if (arr[mid] < target)
        {
            left = mid + 1;
        }
        else    // arr[mid] == target
        {
            floor = ceil = target;
            return;
        }
    }

    if (target < arr[mid])
    {
        ceil = arr[mid];
        floor = mid > 0 ? arr[mid - 1] : -1;
    }
    else if(target > arr[mid])
    {
        ceil = mid < arr.size() - 1 ? arr[mid + 1] : -1;
        floor = arr[mid];
    }
    //“ == ” case was handled in above while
}

void FloorAndCeiling_UnSortedArry(const vector<int>& arr, const int target, int& floor, int& ceil)
{
    floor = -1;
    ceil = numeric_limits<int>::max();

    for (size_t i = 0; i < arr.size(); i++)
    {
        if (target < arr[i])   //ceil candidate
        {
            ceil = min(ceil, arr[i]);
        }
        else if (target > arr[i])     //floor candidate
        {
            floor = max(floor, arr[i]);
        }
        else    //found exact match
        {
            floor = ceil = target;
            return;
        }
    }
}

// This will achive O(log N) time while prev algo was O(N)
int BinarySearchNearest(const vector<int>& arr, const int target)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (arr[mid] < target)
            left = mid + 1;
        else if (arr[mid] > target)
            right = mid - 1;
        else
            return mid;
    }
    return left;
}

// It doesn't work when we have duplicates of Floor or Ceil values
pair<int, int> GetRange_BinarySearch(const vector<int>& arr, const int target)
{
    auto res = make_pair(-1, -1);

    int low = BinarySearchNearest(arr, target - 1);
    if (arr[low] == target)
        res.first = low;
    else if (low != arr.size() - 1 && arr[low + 1] == target)
        res.first = low + 1;
    
    int high = BinarySearchNearest(arr, target + 1);
    if (arr[high] == target)
        res.second = high;
    else if (high > 0 && arr[high - 1] == target)
        res.second = high - 1;

    return res;
}

void GetFloorCeilIdex_WithDUPS(const vector<int>& nums, const int target, int& floor, int& ceil)
{
    floor = ceil = -1;
    if (nums.empty()) return;

    auto OnResultEqual = [&](const bool GetFloor, const int tmid, int& left, int& right) -> bool
    {

        if (GetFloor)
        {
            if (tmid == nums.size() - 1 || nums[tmid + 1] >= target)
                return true;
            else
                left = tmid + 1;
        }
        else
        {
            if (tmid > 0 && nums[tmid - 1] <= target)
                return true;
            else
                right = tmid - 1;
        }
        return false;
    };

    auto GetTargetBound = [&](const bool GetFloor, int left, int right) -> int
    {
        int mid = -1;
        while (left <= right)
        {
            mid = left + (right - left) / 2;

            if (GetFloor)
            {
                if (nums[mid] >= target)
                    right = mid - 1;
                else if (OnResultEqual(GetFloor, mid, left, right))
                    break;
            }
            else
            {
                if (nums[mid] <= target)
                    left = mid + 1;
                else if (OnResultEqual(GetFloor, mid, left, right))
                    break;
            }
        }
        return mid;
    };

    floor = GetTargetBound(true, 0, nums.size() - 1);    
    ceil = GetTargetBound(false, 0, nums.size() - 1);

    floor = floor == 0 && target <= nums.front() ? -1 : floor;
    ceil = ceil == nums.size() - 1 && target >= nums.back() ? -1 : ceil;
}

pair<int, int> GetRange_BinarySearch_WithDUPS(const vector<int>& nums, const int target)
{
    int ceil, floor;
    auto rez = make_pair<int, int>(-1, -1);
    if (nums.empty())    return rez;

    GetFloorCeilIdex_WithDUPS(nums, target, floor, ceil);

    if (floor < int(nums.size())-1 && nums[floor + 1] == target)
    {
        rez.first = floor + 1;

        rez.second = ((ceil == -1)) ? nums.size() - 1 : ceil - 1;
    }

    return rez;
}

//This will not work if we needed to return INDEX instead of actual value (b/c of DUPS)
char nextGreatestLetter(vector<char>& letters, char target)
{
    int left = 0;
    int right = letters.size() - 1;
    int mid = -1;
    ++target;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (letters[mid] > target)
            right = mid - 1;
        else if (letters[mid] < target)
            left = mid + 1;
        else
            break;
    }

    if (target <= letters[mid])
        return letters[mid];
    else
    {
        if (mid >= letters.size() - 1)
            return letters.front();
        else
            return letters[mid + 1];
    }
}

/*vector<int> searchRange(vector<int>& nums, int target)
{
    vector<int> res = { -1, -1 };
    if (nums.empty() || nums.front() > target || nums.back() < target) return res;

    int index = BSearch(nums, target);
    if (index == -1)     return res;
    res[0] = res[1] = index;

    while (res.front() > 0 && nums[res.front() - 1] == target)
        --res.front();

    while (res.back() < nums.size() - 1 && nums[res.back() + 1] == target)
        ++res.back();

    return res;
}

int BSearch(const vector<int>& nums, const int target)
{
    int left = 0;
    int right = nums.size() - 1;

    while (left < right)
    {
        int mid = left + (right - left) / 2;

        if (nums[mid] > target)
            right = mid - 1;
        else if (nums[mid] < target)
            left = mid + 1;
        else
            return mid;
    }
    return nums[left] == target ? left : -1;
}*/

using namespace std::placeholders;

// OLD CODE
class Solution
{
    using EnDirection = enum class ENDIRC
    {
        UPWARDS = 0,
        DOWNWARDS,
        PEAK
    };

    using FindDirectionFunc = std::function<EnDirection(const vector<int>&, const int)>;

public:

    // OLD CODE
    int peakIndexInMountainArray(const vector<int>& arr)
    {
        return this->FindPeekInternal(arr, std::bind(&Solution::GetDirectionInMountain,
            this, std::placeholders::_1, std::placeholders::_2));
    }

    // OLD CODE
    int findPeakElement(const vector<int>& arr)
    {
        if (arr.empty() || 1 == arr.size())        return 0;

        return this->FindPeekInternal(arr, std::bind(&Solution::GetDirectionInArray,
            this, std::placeholders::_1, std::placeholders::_2));
    }

protected:

    virtual int FindPeekInternal(const vector<int>& arr, FindDirectionFunc findDirectionFunc)
    {
        int left = 0;
        int right = arr.size() - 1;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            EnDirection dirc = findDirectionFunc(arr, mid);

            if (dirc == EnDirection::PEAK)
                return mid;
            else if (left == right)
                break;
            else if (dirc == EnDirection::UPWARDS)
                left = mid + 1;
            else
                right = mid - 1;
        }
        return -1;
    }

    virtual EnDirection GetDirectionInArray(const vector<int>& arr, const int index)const
    {
        if (index == arr.size() - 1)
        {
            if (arr[index - 1] < arr[index])
                return EnDirection::PEAK;
            return EnDirection::DOWNWARDS;
        }
        else if (index == 0)
        {
            if (arr[index + 1] < arr[index])
                return EnDirection::PEAK;
            return EnDirection::UPWARDS;
        }
        else if (arr[index - 1] < arr[index] && arr[index + 1] < arr[index])
            return EnDirection::PEAK;
        else if (arr[index - 1] < arr[index])
            return EnDirection::UPWARDS;
        else
            return EnDirection::DOWNWARDS;
    }

    virtual EnDirection GetDirectionInMountain(const vector<int>& arr, const int index)const
    {
        if (index == arr.size() - 1)
            return EnDirection::DOWNWARDS;
        else if (index == 0)
            return EnDirection::UPWARDS;
        else if (arr[index - 1] < arr[index] && arr[index + 1] < arr[index])
            return EnDirection::PEAK;
        else if (arr[index - 1] < arr[index])
            return EnDirection::UPWARDS;
        else
            return EnDirection::DOWNWARDS;
    }

};

class MountainArray
{
public:

    MountainArray(const vector<int>& arrarg) : arr(arrarg) {}

    int get(int index)
    {
        return arr[index];
    }

    int length()
    {
        return arr.size();
    }

private:
    vector<int> arr;
};

//no vector
/*int peakIndexInMountainArray(MountainArray& mountainArr)
{}

int OrderAgnostic_BinarySearch(int target, MountainArray& mountainArr)
{}

int findInMountainArray(int target, MountainArray& mountainArr)
{
    std::function<int(const int, const int)> binSearch = [&](const int left, const int right) -> int
    {
        int mid = left + (right - left) / 2;
        if (target == mountainArr.get(mid))
            return mid;
        else if (left == right)
            return -1;
        else if (target > mountainArr.get(mid))
            return binSearch(mid + 1, right);
        else
            return binSearch(left, mid - 1);
    };

    int peek = this->

        return -1;
}*/

int GetNearestValue(const vector<int>& arr, const int target)
{
    if (arr.empty())     return -1;

    int left = 0;
    int right = arr.size() - 1;
    int mid = 0;

    while (left <= right)
    {
        mid = left + (right - left) / 2;

        if (arr[mid] < target)
            left = mid + 1;
        else if (arr[mid] > target)
            right = mid - 1;
        else
            return arr[mid];
    }

    int ceil = 0;
    int floor = 0;
    if (arr[mid] > target)
    {
        ceil = arr[mid];
        floor = (mid == 0) ? -1 : arr[mid - 1];
    }
    else
    {
        ceil = (mid == arr.size() - 1) ? -1 : arr[mid + 1];
        floor = arr[mid];
    }

    if (floor == -1)     return ceil;
    if (ceil == -1)      return floor;

    if (target - floor < ceil - target)
        return floor;
    else return ceil;
}

int SearchInSortedRotatedArray(const vector<int>& nums, const int target)
{
    int rez = -1;
    if (nums.empty()) return rez;

    auto GetRtdPeek = [&]() -> int
    {
        int rleft = 0;
        int rright = nums.size() - 1;
        int mid = 0;

        while (rleft <= rright)
        {
            mid = rleft + (rright - rleft) / 2;

            if (nums[mid] < nums.front())
                rright = mid - 1;
            else
            {
                if (mid == nums.size() - 1 || nums[mid] > nums[mid + 1])
                    break;
                if (nums[rleft] > nums[rleft + 1])
                    return rleft;
                
                if (nums[mid] == nums[rleft] && nums[mid] == nums[rright])
                {
                    ++rleft;    --rright;
                }
                else   rleft = mid + 1;
            }
        }

        return mid;
    };

    std::function<int(const int,const int)> BSrchEx = [&](const int left, const int right)->int 
    {
        if (left > right)
            return -1;

        int mid = left + (right - left) / 2;
        
        if (nums[mid] < target)
            return BSrchEx(mid + 1, right);
        else if (nums[mid] > target)
            return BSrchEx(left, mid - 1);
        else
            return mid;
    };

    int pkIndx = GetRtdPeek();
    if ((rez = BSrchEx(0, pkIndx)) != -1)
        return rez;

    return BSrchEx(pkIndx+1, nums.size()-1);
}

int search_NODUP(const vector<int>& nums, int target) {

    auto GetRtdPeek = [&]()->int
    {
        int rleft = 0;
        int rright = nums.size() - 1;
        int mid = 0;

        while (rleft <= rright)
        {
            mid = rleft + (rright - rleft) / 2;

            if (nums[mid] < nums.front())    //mid has crossed the PEEK
                rright = mid - 1;
            else
            {
                if (mid == nums.size() - 1 || nums[mid + 1] < nums[mid])
                    break;
                else
                    rleft = mid + 1;
            }
        }

        return mid;
    };

    std::function<int(const int, const int)> BSrchEx = [&](const int left, const int right)->int
    {
        if (left > right)    return -1;
        int mid = left + (right - left) / 2;

        if (nums[mid] > target)
            return BSrchEx(left, mid - 1);
        else if (nums[mid] < target)
            return BSrchEx(mid + 1, right);

        return mid;
    };

    if (nums.empty()) return -1;

    int peek = GetRtdPeek();

    int rez = BSrchEx(0, peek);
    if (rez == -1)
        rez = BSrchEx(peek + 1, nums.size() - 1);
    return rez;
}


bool search(const vector<int>& nums, int target)
{
    bool rez = false;
    if (nums.empty())    return rez;

    auto GetRtnPeekDup = [&]()->int
    {
        int rl = 0;
        int rr = nums.size() - 1;
        int mid = 0;

        while (rl <= rr)
        {
            mid = rl + (rr - rl) / 2;

            if (nums[mid] < nums.front())
                rr = mid - 1;
            else
            {
                if (mid == nums.size() - 1 || nums[mid] > nums[mid + 1])
                    break;
                else
                {
                    if (nums[mid] == nums.front() && nums[mid] == nums.back())
                    {
                        if (nums[rl] > nums[rl + 1])
                            break;

                        ++rl;   --rr;
                    }
                    else
                        rl = mid + 1;
                }
            }
        }

        return mid;
    };

    std::function<bool(int, int)> BSrchEx = [&](const int left, const int right)->bool
    {
        if (left > right)    return false;

        int mid = left + (right - left) / 2;
        if (nums[mid] > target)
            return BSrchEx(left, mid - 1);
        else if (nums[mid] < target)
            return BSrchEx(mid + 1, right);

        return true;
    };

    int peek = GetRtnPeekDup();

    rez = BSrchEx(0, peek);
    if (rez == false)
        rez = BSrchEx(peek + 1, nums.size() - 1);

    return rez;
}

void testBSearch()
{
	/*vector<int> x = { 1,2,3,4,5,6,7,8,10 };
	int index = OrderAgnostic_BinarySearch(x, 1);
	std::reverse(x.begin(), x.end());
    index = OrderAgnostic_BinarySearch(x, 1);
    index = OrderAgnostic_BinarySearch(x, 4);
    int index = UnknownSize_BinarySearch(ArrayReader({ 1,2,3,4,5,6,7,8,10 }), 8);
    index = UnknownSize_BinarySearch(ArrayReader({ 1,2,3,4,5,6,7,8,10 }), 9);
    index = UnknownSize_BinarySearch(ArrayReader({ 3,10 }), 3);
    index = UnknownSize_BinarySearch(ArrayReader({ 3,10 }), 6);
    index = UnknownSize_BinarySearch(ArrayReader({ 3,10 }), 10);
    cout << endl << CeilingOfNumber({ 3,10 }, 10);
    cout << endl << CeilingOfNumber({ 4, 6, 10 }, 6);
    cout << endl << CeilingOfNumber({ 1, 3, 8, 10, 15 }, 12);
    cout << endl << CeilingOfNumber({ 4, 6, 10 }, 17);
    cout << endl << CeilingOfNumber({ 4, 6, 10 }, -1);

    int ceil = 0;
    int floor = 0;
    FloorAndCeiling_UnSortedArry({ 5, 6, 8, 9, 6, 5, 5, 6 }, 7, floor, ceil);    
    FloorAndCeiling_UnSortedArry({ 5, 6, 8, 9, 6, 5, 5, 6 }, 6, floor, ceil);
    FloorAndCeiling_UnSortedArry({ 5, 6, 8, 9, 6, 5, 5, 6 }, 10, floor, ceil);

    GetNextLetterCircular({ 'a', 'c', 'f', 'h' }, 'f');
    GetNextLetterCircular({ 'a', 'c', 'f', 'h' }, 'b');
    GetNextLetterCircular({ 'a', 'c', 'f', 'h' }, 'm');
    GetNextLetterCircular({ 'a', 'c', 'f', 'h' }, 'h');

    GetRange_BinarySearch({ 4, 6, 6, 6, 9 }, 6);
    GetRange_BinarySearch({ 1, 3, 8, 10, 15 }, 10);
    GetRange_BinarySearch({ 1, 3, 8, 10, 15 }, 12);
    GetRange_BinarySearch({ 2, 2 }, 2);
    
    MountainArray().peakIndexInMountainArray({1, 3, 8, 12, 4, 2});
    PeekInArray().peakIndexInMountainArray({ 1, 1, 1, 1, 1 });
    PeekInArray().peakIndexInMountainArray({ 0, 1, 0 });
    PeekInArray().peakIndexInMountainArray({ 0, 2, 1, 0 });
    PeekInArray().peakIndexInMountainArray({ 3, 8, 3, 1 });
    PeekInArray().peakIndexInMountainArray({ 18, 29, 38, 59, 98, 100, 99, 98, 90 });
    Solution().findPeakElement({ 1,2,1,3,5,6,4 });


    int ceil = 0;
    int floor = 0;
    FloorAndCeiling({1, 2, 8, 10, 10, 12, 19}, 0, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1, 2, 8, 10, 10, 12, 19 }, 1, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1, 2, 6, 8, 10, 10, 12, 19 }, 5, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1, 2, 8, 10, 10, 12, 19 }, 20, floor, ceil);
    FloorAndCeiling({ 1 }, 0, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1 }, 1, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1 }, 2, floor, ceil);
    floor = ceil = 0;

    cout << GetNearestValue({ 1, 2, 8, 10, 10, 12, 19 }, 11) << endl;
    cout << GetNearestValue({ 1, 2, 8, 10, 10, 12, 19 }, 13) << endl;
    cout << GetNearestValue({ 1, 2, 8, 10, 10, 12, 19 }, 0) << endl;
    cout << GetNearestValue({ 1, 2, 8, 10, 10, 12, 19 }, 200) << endl;
    cout << GetNearestValue({ 1, 4, 7, 8, 10, 10, 12, 19 }, 5) << endl;
    cout << GetNearestValue({ 1, 2, 7, 8, 10, 10, 12, 19 }, 6) << endl;

    cout << SearchInSortedRotatedArray({ 45, 100, 1, 3, 4, 8, 11, 20, 22 }, 11) << endl;
    cout << SearchInSortedRotatedArray({45, 100, 1, 3, 4, 8, 11, 20, 22}, 45) << endl;
    cout << SearchInSortedRotatedArray({ 45, 100, 1, 3, 4, 8, 11, 20, 22 }, 100) << endl;
    cout << SearchInSortedRotatedArray({ 45, 100, 1, 3, 4, 8, 11, 20, 22 }, 1) << endl;
    cout << SearchInSortedRotatedArray({ 45, 100, 1, 3, 4, 8, 11, 20, 22 }, 20) << endl;
    cout << SearchInSortedRotatedArray({ 45, 100, 4, 4, 4, 0, 4, 4, 4, 4 }, 0) << endl;
    cout << SearchInSortedRotatedArray({ 45, 100, 4, 4, 4, 0, 4, 4, 4, 4 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 4, 4, 0, 4, 4, 4, 4 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 4, 4, 4, 4, 0, 4, 4 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 4, 4, 4, 4, 4, 0, 4, 4 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 4, 4, 4, 4, 4, 4, 4, 0 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 4, 4, 4, 4, 4, 4, 4 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 45, 100, 1, 1, 10 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 1, 0, }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 0, }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 0, 1 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 0, 1, 2, 3, 4 }, 4) << endl;
    cout << SearchInSortedRotatedArray({ 0, 1, 2, 3, 4, 5 }, 4) << endl;

    cout << SearchInSortedRotatedArray({ 1,1,1,1,1,1,1,1,1,13,1,1,1,1,1,1,1,1,1,1,1,1 }, 13);

    //GetRange_BinarySearch_WithDUPS({ 1,2,3,3,3,4,4,4,4,7,7,7,7,9,10 }, 7);


    int ceil, floor;
    GetFloorCeilIdex_WithDUPS({ 1, 2, 8, 10, 10, 12, 19 }, 0, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1, 2, 8, 10, 10, 12, 19 }, 1, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1, 2, 6, 8, 10, 10, 12, 19 }, 5, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1, 2, 8, 10, 10, 12, 19 }, 20, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1 }, 0, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1 }, 1, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1 }, 2, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 4, 6, 6, 6, 9 }, 6, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1, 3, 8, 10, 15 }, 10, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1, 3, 8, 10, 15 }, 12, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 2, 2 }, 2, floor, ceil);
    GetFloorCeilIdex_WithDUPS({ 1,2,3,3,3,4,4,4,4,7,7,7,7,9,10 }, 7, floor, ceil);*/


    GetRange_BinarySearch_WithDUPS({ 1, 2, 8, 10, 10, 12, 19 }, 0);
    GetRange_BinarySearch_WithDUPS({ 1, 2, 8, 10, 10, 12, 19 }, 10);
    GetRange_BinarySearch_WithDUPS({ 1, 2, 6, 8, 10, 10, 12, 19 }, 5);
    GetRange_BinarySearch_WithDUPS({ 1, 2, 8, 10, 10, 12, 19 }, 20);
    GetRange_BinarySearch_WithDUPS({ 1 }, 0);
    GetRange_BinarySearch_WithDUPS({ 1 }, 1);
    GetRange_BinarySearch_WithDUPS({ 1 }, 2);
    GetRange_BinarySearch_WithDUPS({ 4, 6, 6, 6, 9 }, 6);
    GetRange_BinarySearch_WithDUPS({ 1, 3, 8, 10, 15 }, 10);
    GetRange_BinarySearch_WithDUPS({ 1, 3, 8, 10, 15 }, 12);
    GetRange_BinarySearch_WithDUPS({ 2, 2 }, 2);
    GetRange_BinarySearch_WithDUPS({ 1,2,3,3,3,4,4,4,4,7,7,7,7,9,10 }, 7);
}