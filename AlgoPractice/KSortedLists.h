#pragma once


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
	using ArrayElemLoc = struct _ArrayElemLoc
	{
		int val;
		int array;
		int index;

		_ArrayElemLoc(int v, int a, int i) : val(v), array(a), index(i) {}
	};

	int res = -1;

	priority_queue<ArrayElemLoc, vector<ArrayElemLoc>, 
		function<bool(const ArrayElemLoc&, const ArrayElemLoc&)>> minPQ(
			[](const ArrayElemLoc& b, const ArrayElemLoc& a)->bool
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
			res = elem.val;
			break;
		}
		minPQ.pop();
		if (elem.index + 1 < lists[elem.array].size())
			minPQ.push(ArrayElemLoc(lists[elem.array][elem.index + 1], elem.array, elem.index + 1));
	}

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

	MergeKSortedLists({})->Print();*/

	findKthSmallest({ {2, 6, 8}, {3, 6, 7}, {1, 3, 4} }, 5);
	findKthSmallest({ {5, 8, 9}, {1, 7} }, 3);
}