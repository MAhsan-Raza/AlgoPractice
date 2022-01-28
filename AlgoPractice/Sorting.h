#pragma once

void MergeSortedCntgsSubArrays(vector<int>& arr, const int offset, const int SubArrSize) 
{
	vector<int> result;
	result.reserve(SubArrSize * 2);
	int lOffset = offset;
	int rOffset = lOffset + SubArrSize;
	int lBound = lOffset + SubArrSize;
	int rBound = rOffset + SubArrSize;

	while (lOffset < lBound || rOffset < rBound)
	{
		if (lOffset < lBound && rOffset < rBound)
		{
			if (arr{lOffset] < arr{rOffset])
				result.push_back(arr{lOffset++]);
			else
				result.push_back(arr{rOffset++]);
		}
		else if (lOffset < lBound)
			result.push_back(arr{lOffset++]);
		else
			result.push_back(arr{rOffset++]);
	}
	memcpy(&*(arr.begin() + offset), &(*result.begin()), result.size() * sizeof(int));
}

void MergeSort(vector<int>& arr, const int offset, const int subarrsz) 
{
	/*vector arr = {6, 7, 1, 2};
	MergeSortedCntgsSubArrays(arr, 0, 2);
	arr = {0, 0, 0, 6, 7, 1, 2, 0, 0, 0, 0};
	MergeSortedCntgsSubArrays(arr, 3, 2);*/

	if (subarrsz == 1)	return;

	const int half = subarrsz / 2;
	MergeSort(arr, offset, half);
	MergeSort(arr, offset + half, subarrsz - half);

	MergeSortedCntgsSubArrays(arr, offset, half);
}

int GetRotationalIndex(const vector<int>& arr) // in a sorted array
{
	int ri = 0;

	while (ri<arr.size() - 1 && arr{ri]>arr{ri + 1])
		++ri;

	return ri;
}

int CalcRotatedIndex(const int rIndx, const int rDegree, const int maxIndx) 
{
	int actualIndex = 0;
	actualIndex = maxIndx - rDegree + rIndx;
	return actualIndex;
}

int BinarySearch_REC(const vector<int>& arr, const int left, const int right, int elem)
{
	if (left <= right) 
	{

		int mid = (left + right) / 2;

		if (arr{mid] == elem)
			return mid;
		else if (arr{mid] < elem)
			return BinarySearch_REC(arr, mid + 1, right, elem);
		else
			return BinarySearch_REC(arr, left, mid - 1, elem);
	}
	return -1;
}

bool FindPairSumInSortedArray(const vector<int>& arr, const int reqSum, vector<int>& res)
{
	int sIndx = 0;
	int eIndx = arr.size() - 1;

	while (sIndx < eIndx)
	{
		auto sum = arr{sIndx] + arr{eIndx];

		if (sum == reqSum)
		{
			res.push_back(arr{sIndx]);
			res.push_back(arr{eIndx]);
			return true;
		}
		else if (sum > reqSum)
			--eIndx;
		else
			++sIndx;
	}

	return false;
}

void testSorting()
{
	vector<int> arr = { 7, 2, 11, 1, 0, 5, 20, 100, 9, 1, 36, 4 };
	MergeSort(arr, 0, arr.size());
	//int indx = BinarySearch_REC(arr, 0, arr.size() - 1, 20);
	//vector<int> res;
	//FindPairSumInSortedArray(arr, -1/*40*//*3*/, res);

	std::rotate(arr.begin(), arr.begin() + 3, arr.end());
}