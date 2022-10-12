#pragma once

template <class T>
struct ListNodeT {
	T val;
	ListNodeT* next;
	ListNodeT() : val(0), next(nullptr) {}
	ListNodeT(T x) : val(x), next(nullptr) {}
	ListNodeT(T x, ListNodeT* next) : val(x), next(next) {}

	void Print()
	{
		ListNodeT* tmp = this;
		cout << endl;
		while (tmp)
		{
			cout << tmp->val << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}
};

using IListNode = ListNodeT<int>;
using ListNode = ListNodeT<int>;

ListNode* CreateLL(const vector<int> vec)
{
	ListNode *head = nullptr, *crnt = nullptr;

	for (int x : vec)
	{
		if (!head)
		{
			head = crnt = new ListNode(x);
		}
		else
		{
			crnt->next = new ListNode(x);
			crnt = crnt->next;
		}
	}

	return head;
}

template <typename T>
void PrintVecOfVec(const vector<vector<T>>& vOv, const string& sep = "\n")
{
    for (auto& v : vOv)
    {
        for (auto& x : v)
            cout << x << " ";
        cout << sep;
    }
    cout << endl;
}

template <typename T>
void PrintVec(const vector<T>& v)
{
    for (auto& x : v)
        cout << x << " ";
    cout << endl;
}

template<typename T>
void PrintLL(ListNodeT<T>* head)
{
	while (head) {
		cout << head->val << " - ";
		head = head->next;
	}
	cout << "NULL" << endl;
}

void PrintCompareLL(ListNode* head, function<void(ListNode*)> func)
{
	cout << "Input:-  ";
	PrintLL(head);
	func(head);
	cout << "Output:- ";
	PrintLL(head);
	cout << endl;
}

void SwapInString(string& str, const int i1, const int i2)
{
    if (i1 == i2)   return;

    char tmp = str[i1];
    str[i1] = str[i2];
    str[i2] = tmp;
}


template<typename T>
struct HashPair
{
	unsigned int operator()(const pair<T, T>& pr) const
	{
		auto hashA = hash<T>{}(pr.first);
		auto hashB = hash<T>{}(pr.second);

		return (hashA == hashB) ? hashA : hashA ^ hashB;
	}
};
