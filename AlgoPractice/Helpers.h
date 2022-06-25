#pragma once

template <class T>
struct ListNode {
	T val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(T x) : val(x), next(nullptr) {}
	ListNode(T x, ListNode* next) : val(x), next(next) {}

	void Print()
	{
		ListNode* tmp = this;
		cout << endl;
		while (tmp)
		{
			cout << tmp->val << " ";
			tmp = tmp->next;
		}
		cout << endl;
	}
};

using IListNode = ListNode<int>;

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

void SwapInString(string& str, const int i1, const int i2)
{
    if (i1 == i2)   return;

    char tmp = str[i1];
    str[i1] = str[i2];
    str[i2] = tmp;
}