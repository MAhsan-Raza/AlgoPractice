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

void FloorAndCeiling(const vector<int>& arr, const int target, int& floor, int& ceil)
{
    int left = 0;
    int right = arr.size() - 1;

    while (left < right)
    {
        int mid = left + (right - left) / 2;
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

    // here left must == right
    if (target == arr[left])
    {
        floor = ceil = target;
    }
    else if (target < arr[left])
    {
        ceil = arr[left];
        floor = left > 0 ? arr[left - 1] : -1;
    }
    else    // target > arr[left]
    {
        ceil = left < arr.size() - 1 ? arr[left + 1] : -1;
        floor = arr[left];
    }
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

    int peakIndexInMountainArray(const vector<int>& arr)
    {
        return this->FindPeekInternal(arr, std::bind(&Solution::GetDirectionInMountain,
            this, std::placeholders::_1, std::placeholders::_2));
    }

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
int peakIndexInMountainArray(MountainArray& mountainArr)
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

    /*int peek = this->

        return -1;*/
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
    FloorAndCeiling({ 1, 2, 8, 10, 10, 12, 19 }, 0, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1, 2, 8, 10, 10, 12, 19 }, 1, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1, 2, 8, 10, 10, 12, 19 }, 5, floor, ceil);
    floor = ceil = 0;
    FloorAndCeiling({ 1, 2, 8, 10, 10, 12, 19 }, 20, floor, ceil);

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
    Solution().findPeakElement({ 1,2,1,3,5,6,4 });*/
}