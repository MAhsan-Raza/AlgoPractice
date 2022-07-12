#pragma once


using ArrayElemLoc = struct _ArrayElemLoc
{
	int val;
	int array;
	int index;

	_ArrayElemLoc(int v, int a, int i) : val(v), array(a), index(i) {}
};
using CRArrEL = const ArrayElemLoc&;


IListNode* MergeKSortedLists(const vector<IListNode*>& lists)
{
	IListNode* head = nullptr;
	IListNode* crnt = nullptr;

	priority_queue<IListNode*, vector<IListNode*>, function<bool(IListNode*, IListNode*)>> pq(
		[](IListNode* a, IListNode* b)->bool
		{
			return a->val > b->val;
		}
	);

	for_each(lists.begin(), lists.end(), [&pq](IListNode* tmp) { if (tmp) pq.push(tmp); });

	while (false == pq.empty())
	{
		IListNode* tmp = pq.top();
		pq.pop();
		if (tmp->next)
			pq.push(tmp->next);

		if (!head)
			head = crnt = new IListNode(tmp->val);
		else
		{
			crnt->next = new IListNode(tmp->val);
			crnt = crnt->next;
		}
	}

	return head;
}

int findKthSmallest(const vector<vector<int>>& lists, int k) 
{
	priority_queue<ArrayElemLoc, vector<ArrayElemLoc>, 
		function<bool(const ArrayElemLoc&, const ArrayElemLoc&)>> minPQ(
			[](const ArrayElemLoc& a, const ArrayElemLoc& b)->bool
			{
				return a.val > b.val;
			});
	
	int i = 0;
	for (; i < lists.size(); i++)
		minPQ.push(ArrayElemLoc(lists[i].front(), i, 0));

	i = 0;
	while (false == minPQ.empty())
	{
		auto elem = minPQ.top();

		if (++i == k)
		{
			return elem.val;
		}
		minPQ.pop();
		if (elem.index + 1 < lists[elem.array].size())
			minPQ.push(ArrayElemLoc(lists[elem.array][elem.index + 1], elem.array, elem.index + 1));
	}
}

int KSortedListMedian(const vector<vector<int>>& lists)
{
	int res = -1;

	priority_queue<ArrayElemLoc, vector<ArrayElemLoc>,
		function<bool(const ArrayElemLoc&, const ArrayElemLoc&)>> minPQ(
			[](const ArrayElemLoc& a, const ArrayElemLoc& b)->bool
			{
				return a.val > b.val;
			});

	int i = 0;
	int ttlSz = 0;
	for (; i < lists.size(); i++)
	{
		minPQ.push(ArrayElemLoc(lists[i].front(), i, 0));
		ttlSz += lists[i].size();
	}

	i = 0;
	int K1Index = ttlSz / 2;
	int K2Index = 1 + K1Index;

	int K1, K2;

	while (false == minPQ.empty())
	{
		ArrayElemLoc ael = minPQ.top();
		minPQ.pop();

		if (++i == K1Index)
			K1 = ael.val;
		else if (i == K2Index)
		{
			K2 = ael.val;
			break;
		}

		if (ael.index + 1 < lists[ael.array].size())
		{
			minPQ.push(ArrayElemLoc(lists[ael.array][ael.index + 1], ael.array, ael.index + 1));
		}
	}

	return (ttlSz % 2 != 0) ? K2 : (K1 + (K2 - K1) / 2);
}

vector<int> MergeKSortedVectors(const vector<vector<int>>& lists)
{
	priority_queue<ArrayElemLoc, vector<ArrayElemLoc>,
		function<bool(const ArrayElemLoc&, const ArrayElemLoc&)>> minPQ(
			[](const ArrayElemLoc& a, const ArrayElemLoc& b)->bool
			{
				return a.val > b.val;
			});
	
	int i = 0;
	int ttlSz = 0;
	for (; i < lists.size(); i++)
	{
		minPQ.push(ArrayElemLoc(lists[i].front(), i, 0));
		ttlSz += lists[i].size();
	}

	i = 0;
	vector<int> rez(ttlSz, 0);

	while(false == minPQ.empty())
	{ 
		auto x = minPQ.top();
		minPQ.pop();

		rez[i++] = x.val;

		if (x.index + 1 < lists[x.array].size())
			minPQ.push(ArrayElemLoc(lists[x.array][x.index + 1], x.array, x.index + 1));
	}

	return rez;
}

// This Matrix is sorted both row vise & col vise so our target should be at initial K*K sub-matrix, not dependent on the actual size of the matrix
// e.g. if we need to find 4th element & matrixt size is 99999*99999 we will only have to push 4*4 elemnts into the min heap (at a time only MIN(K, N))
int KthSmallestInSortedMatrix(const vector<vector<int>>& matrix, int k)
{
	priority_queue<ArrayElemLoc, vector<ArrayElemLoc>, function<bool(CRArrEL, CRArrEL)>> minPQ(
		[](CRArrEL a, CRArrEL b)->bool { return a.val > b.val; }
	);

	int i = 0;
	for (; i < matrix.size() && i < k; i++)
	{
		minPQ.push(ArrayElemLoc(matrix[i].front(), i, 0));
	}

	i = 0;
	while (false == minPQ.empty())
	{
		auto x = minPQ.top();
		minPQ.pop();

		if (++i == k)
			return x.val;

		if (x.index + 1 < matrix[x.array].size())
			minPQ.push(ArrayElemLoc(matrix[x.array][x.index + 1], x.array, x.index + 1));
	}
}

int KthSmallestInSortedMatrixGraph(const vector<vector<int>>& matrix, int k)
{
	const int N = matrix.size();

	auto GetNext2 = [&matrix,N](const int crntArr, const int crntInd, ArrayElemLoc& frst, ArrayElemLoc& scnd) 
	{
		frst.val = -1;
		scnd.val = -1;
		if (crntArr + 1 < N)
			frst = ArrayElemLoc(matrix[crntArr + 1][crntInd], crntArr + 1, crntInd);
		if (crntInd + 1 < N)
			scnd = ArrayElemLoc(matrix[crntArr][crntInd + 1], crntArr, crntInd + 1);
	};

	auto AELMinIsFrst = [](CRArrEL frst, CRArrEL scnd)->bool 
	{
		if (frst.val != -1 && scnd.val != -1)
		{
			return frst.val < scnd.val;
		}
		else if (frst.val != -1)	return true;
		else						return false;
	};

	deque<ArrayElemLoc> dq;

	int crntArr = 0;
	int crntInd = 0;
	ArrayElemLoc frst(-1, -1, -1), scnd(-1, -1, -1);

	for (int i = 1; i < k; i++)
	{
		GetNext2(crntArr, crntInd, frst, scnd);

		if(AELMinIsFrst(frst, scnd))
		{ 
			if (false == dq.empty())
			{
				if (AELMinIsFrst(dq.front(), frst))
				{
					crntArr = dq.front().array;
					crntInd = dq.front().index;
					dq.pop_front();
					continue;
				}

				if (dq.front().array == frst.array && dq.front().index == frst.index)
					dq.pop_front();
			}

			dq.push_back(scnd);
			crntArr = frst.array;
			crntInd = frst.index;
		}
		else
		{
			if (false == dq.empty())
			{
				if (AELMinIsFrst(dq.front(), scnd))
				{
					crntArr = dq.front().array;
					crntInd = dq.front().index;
					dq.pop_front();
					continue;
				}
				if (dq.front().array == scnd.array && dq.front().index == scnd.index)
					dq.pop_front();
			}

			dq.push_back(frst);
			crntArr = scnd.array;
			crntInd = scnd.index;
		}
	}

	return matrix[crntArr][crntInd];
}

vector<int, int> SmallestRangeThatCoversAll(const vector<vector<int>> lists)
{
	vector<int, int> res;
	return res;
}

void testKSortedLists()
{
	auto nwL = [](const int x, IListNode* nxt)->IListNode* { return new IListNode(x, nxt); };

	/*MergeKSortedLists({
		nwL(1, nwL(4, nwL(5, nullptr))),
		nwL(1, nwL(3, nwL(5, nullptr))),
		nwL(2, nwL(6, nullptr)),
		})->Print();

	MergeKSortedLists({})->Print();

	findKthSmallest({ {2, 6, 8}, {3, 6, 7}, {1, 3, 4} }, 5);
	findKthSmallest({ {5, 8, 9}, {1, 7} }, 3);

	KSortedListMedian({ {2, 6, 8}, {3, 6, 7}, {1, 3, 4, 200} });
	KSortedListMedian({ {5, 8, 9}, {1, 7} });
	KSortedListMedian({ {2, 60, 80}, {3, 61, 70}, {1, 3, 4, 2000} });

	auto x = MergeKSortedVectors({ {2, 6, 8}, {3, 6, 7}, {1, 3, 4, 200} });
	x = MergeKSortedVectors({ {5, 8, 9}, {1, 7} });
	x = MergeKSortedVectors({ {2, 60, 80}, {3, 61, 70}, {1, 3, 4, 2000} });*/

	KthSmallestInSortedMatrixGraph(
		{
			{2, 6, 8},
			{3, 7, 10},
			{5, 8, 11}
		}, 5);

	KthSmallestInSortedMatrixGraph(
		{ 
			{1, 5, 9},
			{10, 11, 13},
			{12, 13, 15} 
		}, 8);
}