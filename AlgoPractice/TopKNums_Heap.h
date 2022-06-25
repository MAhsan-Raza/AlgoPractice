#pragma once

void GetTopKNumbers(vector<int>& nums, int k, vector<int>& res)
{
	res.clear();

	std::make_heap(nums.begin(), nums.end());
	while (k-- > 0)
	{
		res.push_back(nums.front());
		std::pop_heap(nums.begin(), nums.end());
		nums.pop_back();
	}
}

void GetTopKNumbersNoDUPS(vector<int>& nums, int k, vector<int>& res)
{
	res.clear();

	std::make_heap(nums.begin(), nums.end());
	while (k-- > 0)
	{
		if(res.empty() || nums.front() != res.back())
			res.push_back(nums.front());
		std::pop_heap(nums.begin(), nums.end());
		nums.pop_back();
	}
}

int KthSmallestNumber(vector<int>& nums, int k)
{
	std::make_heap(nums.begin(), nums.end(), std::greater<>{});
	while (--k > 0)
	{
		std::pop_heap(nums.begin(), nums.end(), std::greater<>{});
		nums.pop_back();
	}

	return nums.front();
}

vector<vector<int>> KClosestPointstoOrigin(const vector<vector<int>>& points, int k)
{
	using Point = vector<int>;
	using PointVec = vector<Point>;

	auto ptDistSmlr = [&](const Point& a, const Point& b) -> bool 
	{
		double aDist = std::sqrt(double(std::pow(a[0], 2) + std::pow(a[1], 2)));
		double bDist = std::sqrt(double(std::pow(b[0], 2) + std::pow(b[1], 2)));
		return aDist < bDist;
	};

	vector<vector<int>> res;

	priority_queue<Point, PointVec, decltype(ptDistSmlr)> maxQ(ptDistSmlr);

	for (const auto& x : points)
	{
		if (maxQ.size() != k)
		{
			maxQ.push(x);
		}
		else
		{ 
			if(ptDistSmlr(x, maxQ.top()))
			{
				maxQ.pop();
				maxQ.push(x);
			}
		}
	}

	while (!maxQ.empty())
	{
		res.push_back(maxQ.top());
		maxQ.pop();
	}

	return res;
}

//LeetCode<HARD>:- Minimum Cost to Merge K each Stones
int MinimumCosttoMergeKeachStones(const vector<int>& nums, const int k)
{
	return 0;
}

//LeetCode<MEDIUM>:- Minimum Cost to Connect Sticks
int ConnectRopesTwoRopesAtaTime(vector<int>& nums)
{
	int TotalCost = 0;
	std::make_heap(nums.begin(), nums.end(), std::greater<>{});

	auto GetNPopQ = [&]()->int 
	{
		int res = nums.front();
		std::pop_heap(nums.begin(), nums.end(), std::greater<>{});
		nums.pop_back();
		return res;
	};

	while(nums.size() > 1)
	{ 
		int CrntCost = 0;
		CrntCost += GetNPopQ();
		CrntCost += GetNPopQ();
		TotalCost += CrntCost;

		nums.push_back(CrntCost);
		std::push_heap(nums.begin(), nums.end(), std::greater<>{});
	}

	return TotalCost;
}

vector<int> topKFrequent(const vector<int>& nums, int k) 
{
	std::unordered_map<int, int> ht;

	for (const int x : nums)
	{
		++ht[x];
	}

	auto par1stSmlr = [](const pair<int, int>& a, const pair<int, int>& b)->bool 
	{
		return a.first > b.first;
	};

	priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(par1stSmlr)> minQ(par1stSmlr);

	for (const auto& x : ht)
	{
		auto tmpPar = make_pair(x.second, x.first);

		if (minQ.size() < k)
		{
			minQ.push(tmpPar);
		}
		else
		{
			if (minQ.top().first < tmpPar.first)
			{
				minQ.pop();
				minQ.push(tmpPar);
			}
		}
	}

	vector<int> res;
	while (!minQ.empty())
	{
		res.push_back(minQ.top().second);
		minQ.pop();
	}
	return res;
}

string FrequencySortCharachters(const string& s)
{
	unordered_map<char, int> ht;

	for(const char& x : s)
	{ 
		++ht[x];
	}

	auto funcCmpr = [](const pair<int, char>& a, const pair<int, char>& b)->bool { return a.first < b.first; };

	priority_queue<pair<int, char>, vector<pair<int, char>>, decltype(funcCmpr)> maxQ(funcCmpr);

	for(const auto& x : ht)
	{ 
		maxQ.push(make_pair(x.second, x.first));
	}

	int index = 0;
	string res(s.size(), 0);
	while (!maxQ.empty())
	{
		const auto& crnt = maxQ.top();
		for (int i = 0; i < crnt.first; i++)
			res[index + i] = crnt.second;
		index += crnt.first;
		maxQ.pop();
	}

	return res;
}

vector<int> findClosestElements(const vector<int>& arr, int k, int x)
{
	if (arr.empty()) return vector<int>();

	auto BinSrchSingleMostClosestMin = [&]()->int
	{
		int left = 0;
		int right = arr.size() - 1;
		int mid = 0;

		while (left <= right)
		{
			mid = left + (right - left) / 2;

			if (arr[mid] < x)
				left = mid + 1;
			else if (arr[mid] > x)
				right = mid - 1;
			else break;
		}
		return mid;
	};

	int nearest = BinSrchSingleMostClosestMin();
	deque<int> dq;
	int back, fore;

	if (arr[nearest] == x)
	{
		dq.push_back(x);
		back = nearest - 1;
		fore = nearest + 1;
	}
	else
	{
		back = (arr[nearest] > x) ? nearest - 1 : nearest;
		fore = (arr[nearest] > x) ? nearest : nearest + 1;
	}

	auto pushToQ = [&](const bool toFront = true)
	{
		if (toFront)
		{
			dq.push_front(arr[back]);
			--back;
		}
		else
		{
			dq.push_back(arr[fore]);
			++fore;
		}
	};

	while (dq.size() < k)
	{
		if (back >= 0 && fore < arr.size())
		{
			int bDist = std::abs(x - arr[back]);
			int fDist = std::abs(x - arr[fore]);

			if (bDist <= fDist)         pushToQ();		// '<=' is placed on b/c of leetcode, logical result comes with '<' too
			else						pushToQ(false);
		}
		else if (back >= 0)				pushToQ();
		else if (fore < arr.size())		pushToQ(false);
		else                            break;
	}

	return vector<int>(dq.begin(), dq.end());
}

int MaxDistinctNumsAfterRemovingK(const vector<int>& arr, int k)
{
	unordered_set<int> US;
	unordered_set<int> DUP;

	for (int x : arr)
	{
		unordered_set<int>::const_iterator cItr = US.find(x);

		if (US.find(x) == US.end())
		{
			if (DUP.find(x) == DUP.end())
				US.insert(x);
			else
				continue; // Skip X because it has became NON-DISTINCT previously
		}
		else
		{
			if (k > 0)
			{
				--k;
				//& skip that element X, meaning we removed it
			}
			else
			{
				US.erase(x);
				DUP.insert(x);
			}
		}
	}
	return US.size() - k;
}

//We can also sort the HT by its second (i.e. occurances) & then excute main while, by this we can save space by not using HEAP
int findLeastNumOfUniqueInts(const vector<int>& arr, int k)
{
	unordered_map<int, int> HT;
	priority_queue<int, vector<int>, greater<>> minHpOccrs;

	std::for_each(arr.begin(), arr.end(), [&HT](const int x) { ++HT[x]; });
	std::for_each(HT.begin(), HT.end(), [&minHpOccrs](const auto& itr) { minHpOccrs.push(itr.second); });

	while (0 < k && false == minHpOccrs.empty())
	{
		k -= minHpOccrs.top();
		if (0 <= k)
			minHpOccrs.pop();
	}
	return minHpOccrs.size();
}

int SumBetweenK1thAndK2thSmallestElements(vector<int> arr, int k1, int k2)
{
	int sum = 0;
	make_heap(arr.begin(), arr.end(), greater<>{});

	int i = 1;
	while (false == arr.empty())
	{
		if (i == k2) break;
		else if (i > k1)
		{
			sum += arr.front();
		}
		
		pop_heap(arr.begin(), arr.end(), greater<>{});
		arr.pop_back();
		++i;
	}

	return sum;
}

string RearrangeStringNoConsicutiveDuplicates(string s)
{
	string sres(s.size(), 0);
	map<char, int> firstSMap;
	vector<pair<int, char>> ocrLookUp;	//We need a vector instead of map since we are gona decreament the key
	for_each(s.begin(), s.end(), [&firstSMap](const char c) { ++firstSMap[c]; });
	for_each(firstSMap.begin(), firstSMap.end(), [&ocrLookUp](const auto& x) { ocrLookUp.push_back(make_pair(x.second, x.first)); });

	std::sort(ocrLookUp.begin(), ocrLookUp.end(), [](const pair<int, char>& a, const pair<int, char>& b)->bool { return a.first > b.first; });

	/*int front = 0;
	int back = ocrLookUp.size() - 1;

	int sndx = 0;
	bool bFrnot = false;

	while (front <= back)
	{
		int* ndx = (bFrnot ? &front : &back);
		sres[sndx++] = ocrLookUp[*ndx].second;
		if (--ocrLookUp[*ndx].first == 0)
			*ndx = (bFrnot ? *ndx + 1 : *ndx - 1);
		bFrnot != bFrnot;
	}*/

	int sInd = 0;
	int crntOcrInd = 0;

	while (ocrLookUp[crntOcrInd].first > 1)
	{
		sres[sInd++] = ocrLookUp[crntOcrInd].second;
		--ocrLookUp[crntOcrInd].first;
		if (ocrLookUp[++crntOcrInd].first <= 1)
			crntOcrInd = 0;
	}
	
	return sres;
}

vector<string> TopKWordsAlphabeticaly(vector<string>& words, int k)
{
	vector<string> res(k, "");
	map<string, int> ht;

	using pairWrdFreq = pair<int, string>;
	auto pqCompGrtr = [](const pairWrdFreq& a, const pairWrdFreq& b)->bool
	{
		if (a.first == b.first)
			return a.second < b.second;
		return a.first > b.first;
	};

	for (const auto& x : words)
		++ht[x];

	priority_queue<pairWrdFreq, vector<pairWrdFreq>, decltype(pqCompGrtr)> pq(pqCompGrtr);

	for (const auto& x : ht)
	{
		if (pq.size() < k)
			pq.push(make_pair(x.second, x.first));
		else
		{
			if (x.second > pq.top().first)
			{
				pq.pop();
				pq.push(make_pair(x.second, x.first));
			}
		}
	}

	int i = res.size() - 1;
	while (false == pq.empty())
	{
		res[i--] = pq.top().second;
		pq.pop();
	}

	return res;

}

vector<string>& SortFeaturesbyPopularity(vector<string>& features, const vector< vector<string>>& searches)
{
	unordered_map<string, int> ht;
	for_each(features.begin(), features.end(), [&ht](const string& fet) { ht[fet] = 0; });

	for (int i = 0; i < searches.size(); i++)
	{
		for (int j = 0; j < searches[i].size(); j++)
		{
			auto itr = ht.find(searches[i][j]);
			if (itr != ht.end())
				++itr->second;
		}
	}

	auto ComprGrtr = [&ht,&features](const string& a, const string& b)->bool
	{
		int ia = ht[a];
		int ib = ht[b];
		return ht[a] > ht[b]; 
	};
	std::sort(features.begin(), features.end(), ComprGrtr);
	//make_heap(features.begin(), features.end(), ComprSmlr);

	return features;
}

priority_queue<int, vector<int>, greater<int>> minQ;
void testTopKNums_Heap()
{
	string srz = "";
	vector<int> res;
	vector<int> nums = { 3, 1, 5, 12, 2, 11 };
	
	/*GetTopKNumbers(nums, 3, res);
	nums = { 5, 12, 11, -1, 12 };
	GetTopKNumbersNoDUPS(nums, 3, res);
	nums = { 5, 12, 11, -1, 12 };
	KthSmallestNumber(nums, 2);
	nums = { 5, 12, 11, -1, 12 };
	KthSmallestNumber(nums, 5);
	nums = { 3, 1, 5, 12, 2, 11 };
	KthSmallestNumber(nums, 1);
	nums = { 3, 1, 5, 12, 2, 11 };
	KthSmallestNumber(nums, 3);

	auto rez = KClosestPointstoOrigin({ {3, 3}, { 5, 5}, { 4, 4 } }, 2);
	rez = KClosestPointstoOrigin({ {3, 3}, { 5, -1}, { -2, 4 } }, 2);

	nums = { 2,4,3 };
	ConnectRopesTwoRopesAtaTime(nums);
	nums = { 1,8,3,5 };
	ConnectRopesTwoRopesAtaTime(nums);
	nums = { 1, 3, 11, 5 };
	ConnectRopesTwoRopesAtaTime(nums);
	nums = { 3, 4, 5, 6 };
	ConnectRopesTwoRopesAtaTime(nums);
	nums = { 1, 3, 11, 5, 2 };
	ConnectRopesTwoRopesAtaTime(nums);

	res = topKFrequent({ 1,1,1,2,2,3 }, 2);
	res = topKFrequent({ 1 }, 1);
	res = topKFrequent({ 1, 3, 5, 12, 11, 12, 11 }, 2);
	res = topKFrequent({ 5, 12, 11, 3, 11 }, 2);

	srz = FrequencySortCharachters("tree");
	srz = FrequencySortCharachters("cccaaa");
	srz = FrequencySortCharachters("Aabb");
	srz = FrequencySortCharachters("Programming");
	srz = FrequencySortCharachters("abcbab");
	
	res = findClosestElements({ 1,2,3,4,5 }, 4, 3);
	res = findClosestElements({ 1,3 }, 1, 2);

	MaxDistinctNumsAfterRemovingK({ 7, 3, 5, 8, 5, 3, 3 }, 2);
	MaxDistinctNumsAfterRemovingK({ 3, 5, 12, 11, 12 }, 3);
	MaxDistinctNumsAfterRemovingK({ 1, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5 }, 2);

	res = findClosestElements({ 1,2,3,4,5 }, 4, -1);
	res = findClosestElements({ 0,1,1,1,2,3,6,7,8,9 }, 9, 4);

	findLeastNumOfUniqueInts({ 5, 5, 4 }, 1);
	findLeastNumOfUniqueInts({ 4, 3, 1, 1, 3, 3, 2 }, 3);
	findLeastNumOfUniqueInts({ 2, 2, 1, 3, 3, 3 }, 3);
	findLeastNumOfUniqueInts({ 2, 4, 1, 5, 3, 5, 1, 3 }, 2);

	SumBetweenK1thAndK2thSmallestElements({ 1, 3, 12, 5, 15, 11 }, 3, 6);
	SumBetweenK1thAndK2thSmallestElements({ 3, 5, 8, 7 }, 1, 4);
	SumBetweenK1thAndK2thSmallestElements({ 20, 8, 22, 4, 12, 10, 14 }, 3, 6);
	SumBetweenK1thAndK2thSmallestElements({ 10, 2, 50, 12, 48, 13 }, 2, 6);

	RearrangeStringNoConsicutiveDuplicates("abccee");
	RearrangeStringNoConsicutiveDuplicates("aappp");

	vector<string> words = { "i","love","leetcode","i","love","coding" };
	TopKWordsAlphabeticaly(words, 2);*/

	vector<string> strInp = { "cooler","lock","touch" };
	SortFeaturesbyPopularity(strInp, { {"i", "like", "cooler", "cooler"}, { "lock", "touch", "cool" }, { "locker", "like", "touch"} });
}